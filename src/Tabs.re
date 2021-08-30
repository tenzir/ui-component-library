module Styles = TabStyles;
open Lib.Function.Infix;
open Lib.Jsx.Infix;

type t = {
  id: string,
  title: string,
};

module Helpers = {
  let create = title => {id: GenericHelpers.v4(), title};
  let createMany = arr => Belt.Array.map(arr, create);
  let add = (arr, tab) => Belt.Array.concat(arr, [|tab|]);
  let update = (arr, x) => Belt.Array.map(arr, y => y.id === x.id ? x : y);
  let removeById = (arr, id) => Belt.Array.keep(arr, x => x.id !== id);
  let removeByIndex = (arr, idx) =>
    Belt.Array.concat(
      Belt.Array.slice(arr, ~offset=0, ~len=idx),
      Belt.Array.sliceToEnd(arr, idx + 1),
    );
  let duplicateById = (arr, id) => {
    let newId = GenericHelpers.v4();
    let arr =
      Js.Array2.find(arr, x => x.id === id)
      ->Belt.Option.map(elem =>
          Belt.Array.concat(arr, [|{...elem, id: newId}|])
        )
      ->Belt.Option.getWithDefault(arr);
    (arr, newId);
  };
  let duplicateByIdx = (arr, idx) => {
    let newId = GenericHelpers.v4();
    let arr =
      Belt.Array.get(arr, idx)
      ->Belt.Option.map(elem =>
          Belt.Array.concat(arr, [|{...elem, id: newId}|])
        )
      ->Belt.Option.getWithDefault(arr);
    (arr, newId);
  };
  let move = (arr, from, to_) => {
    Belt.Array.get(arr, from)
    ->Belt.Option.map(elem => {
        let copy = Belt.Array.copy(arr);
        Js.Array2.spliceInPlace(copy, ~pos=from, ~remove=1, ~add=[||])
        ->ignore;
        Js.Array2.spliceInPlace(copy, ~pos=to_, ~remove=0, ~add=[|elem|])
        ->ignore;
        copy;
      })
    ->Belt.Option.getWithDefault(arr);
  };
};

module TabInput = {
  [@react.component]
  let make = (~defaultValue, ~onRename) => {
    let ref = React.useRef(Js.Nullable.null);

    React.useEffect0(() => {
      Lib.Jsx.focus(ref);
      None;
    });

    let handleKeyDown = e => {
      Lib.Event.Keyboard.keyWas("Enter", e)
        ? onRename(e |> Lib.Event.getValueFromEvent) : ();
    };

    <input
      className=Styles.input
      ref={ReactDOM.Ref.domRef(ref)}
      defaultValue
      onBlur={Lib.Event.getValueFromEvent >> onRename}
      onKeyUp=handleKeyDown
    />;
  };
};

type action =
  | Add(t)
  | Open(string)
  | Rename(t)
  | Close(string)
  | Duplicate(string);

module AddTab = {
  [@react.component]
  let make = (~dispatch: action => unit, ~depth: int, ~standalone, ~theme) => {
    /*
       The index below is technically incorrect. But by adding it to the
       list of draggable items, it means the placeholder will be correctly
       updated.
     */
    <Dnd.Draggable isDragDisabled=true draggableId="add-tab" index=max_int>
      <div
        key="add-tab"
        id="add-tab"
        className={
          Styles.tab(theme, standalone, depth, false, true)
          ++ " "
          ++ Styles.addTab
        }
        onClick={_ => Add(Helpers.create("New tab"))->dispatch}>
        <span className=Styles.addIcon> <Icons.Plus /> </span>
        <span className=Styles.addText> "Add"->React.string </span>
      </div>
    </Dnd.Draggable>;
  };
};
module Tab = {
  [@react.component]
  let make =
      (
        ~tab: t,
        ~dispatch: action => unit,
        ~index: int,
        ~active: bool,
        ~standalone: bool,
        ~depth: int,
        ~features,
        ~theme,
      ) => {
    let (editing, setEditing) = React.useState(Lib.Function.const(false));
    let (canOpen, canClose, canUpdate, canDuplicate, canMove) = features;
    <Dnd.Draggable draggableId={tab.id} index isDragDisabled={!canMove}>
      <div
        id={tab.id}
        className={Styles.tab(theme, standalone, depth, active, canOpen)}
        onClick={_ => Open(tab.id)->dispatch}>
        {editing
           ? <TabInput
               defaultValue={tab.title}
               onRename={title => {
                 setEditing(Lib.Function.const(false));
                 Rename({...tab, title})->dispatch;
               }}
             />
           : <span
               onClick={e => {
                 e->ReactEvent.Synthetic.stopPropagation;
                 active && canUpdate
                   ? setEditing(Lib.Function.const(true))
                   : Open(tab.id)->dispatch;
               }}
               className={Styles.text(active, canUpdate)}>
               tab.title->React.string
             </span>}
        {(!canDuplicate && !canClose)
         <&&> <Spacer.Horizontal amount={0.5->Css.rem} />}
        {canDuplicate
         <&&> <span
                onClick={e => {
                  e->ReactEvent.Synthetic.stopPropagation;
                  Duplicate(tab.id)->dispatch;
                }}
                className={Styles.roundedIconButton(
                  ~leftMargin=true,
                  theme,
                  depth,
                  active,
                )}>
                <Icons.Copy size=10 />
              </span>}
        {canClose
         <&&> <span
                onClick={e => {
                  e->ReactEvent.Synthetic.stopPropagation;
                  Close(tab.id)->dispatch;
                }}
                className={Styles.roundedIconButton(theme, depth, active)}>
                <Icons.X size=10 />
              </span>}
      </div>
    </Dnd.Draggable>;
  };
};

[@react.component]
let make =
    (
      ~standalone=true,
      ~activeTabId: string,
      ~tabs: array(t),
      ~theme,
      ~depth=0,
      ~onAdd=?,
      ~onMove=?,
      ~onOpen=?,
      ~onRename=?,
      ~onClose=?,
      ~onDuplicate=?,
    ) => {
  let onDispatch = action =>
    (
      switch (action) {
      | Add(x) => Belt.Option.map(onAdd, Lib.Function.apply(x))
      | Open(x) => Belt.Option.map(onOpen, Lib.Function.apply(x))
      | Close(x) => Belt.Option.map(onClose, Lib.Function.apply(x))
      | Rename(x) =>
        Belt.Option.map(
          onRename,
          Lib.Function.apply(x.title === "" ? {...x, title: "Untitled"} : x),
        )
      | Duplicate(x) => Belt.Option.map(onDuplicate, Lib.Function.apply(x))
      }
    )
    ->ignore;

  let onDragEnd = (e: Dnd.Context.dragEndEvent) => {
    let move =
      e.destination
      ->Js.Nullable.toOption
      ->Belt.Option.map(d => (e.source.index, d.index));

    switch (move, onMove) {
    | (Some((from, to_)), Some(fn)) => fn((from, to_))
    | _ => ()
    };
  };

  let onDragStart = (e: Dnd.Context.dragStartEvent) =>
    Belt.Option.map(onOpen, fn => {
      Belt.Array.get(tabs, e.source.index)
      ->Belt.Option.map((x => x.id) >> Lib.Function.applyF(fn))
    })
    ->ignore;

  <div className={Styles.container(standalone, theme, depth)}>
    <Dnd.Context onDragEnd onDragStart>
      <Dnd.Droppable direction=`horizontal droppableId="droppable-tabs">
        <div className=Styles.droppable>
          {tabs
           ->Belt.Array.mapWithIndex((index, tab) =>
               <Tab
                 key={tab.id}
                 index
                 tab
                 theme
                 depth
                 standalone
                 features=(
                   onOpen->Belt.Option.isSome,
                   onClose->Belt.Option.isSome,
                   onRename->Belt.Option.isSome,
                   onDuplicate->Belt.Option.isSome,
                   onMove->Belt.Option.isSome,
                 )
                 dispatch=onDispatch
                 active={tab.id === activeTabId}
               />
             )
           ->React.array}
          {onAdd->Belt.Option.isSome
           <&&> <AddTab theme depth standalone dispatch=onDispatch />}
        </div>
      </Dnd.Droppable>
    </Dnd.Context>
  </div>;
};
