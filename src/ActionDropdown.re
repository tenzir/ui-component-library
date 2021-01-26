open Webapi.Dom;
open! Dropdown;

type t('a) = {
  name: string,
  value: 'a,
  action: unit => unit,
};

module Styles = {
  open! Css;
  let buttonContainer = style([display(`flex), flexDirection(`row)]);
  let actionButton = style([borderTopRightRadius(`zero)]);
  let arrowButton =
    style([
      borderTopLeftRadius(`zero)->important,
      width(4.0->rem)->important,
      padding(`zero)->important,
      margin(`zero)->important,
      minWidth(`zero)->important,
    ]);
};

[@react.component]
let make =
    (
      ~theme=Config.defaultTheme,
      ~options,
      ~disabled=false,
      ~enableSearch=false,
      ~value: 'a,
      ~callActionOnChange=false,
      ~depth=1,
      ~variant=ButtonStyles.Secondary,
      ~minWidth=150,
      ~maxHeight=200,
      ~onChange,
      ~title=?,
      ~className="",
    ) => {
  let element = React.useRef(Js.Nullable.null);
  let (state, setState) = React.useState(_ => Closed);
  let (filter, setFilter) = React.useState(_ => "");
  let (filteredOptions, setFilteredOptions) = React.useState(_ => [||]);
  let (name, setName) = React.useState(_ => "");

  let possiblyClose = e =>
    element.current
    ->Js.Nullable.toOption
    ->Belt.Option.map(domElement => {
        let targetElement =
          MouseEvent.target(e) |> EventTarget.unsafeAsElement;
        domElement |> Element.contains(targetElement)
          ? () : setState(_ => Closed);
      })
    ->ignore;

  let toggleState = _ => {
    switch (state) {
    | Open =>
      setFilter(_ => "");
      setState(_ => Closed);
      Document.removeMouseDownEventListener(possiblyClose, document);
    | Closed =>
      setState(_ => Open);
      Document.addMouseDownEventListener(possiblyClose, document);
    };
  };

  let possiblySubmit = e => {
    let head = filteredOptions->Belt.Array.get(0);
    switch (e |> ReactEvent.Keyboard.keyCode, head) {
    | (13, Some(opt)) =>
      onChange(opt.value);
      opt.action();
      toggleState();
    | _ => ()
    };
  };

  React.useEffect0(() =>
    Some(
      () => Document.removeMouseDownEventListener(possiblyClose, document),
    )
  );

  React.useEffect1(
    () => {
      options
      ->Js.Array2.find(_option => _option.value == value)
      ->Belt.Option.map(_option => _option.name)
      ->Belt.Option.getWithDefault("None")
      ->(newName => setName(_ => newName));
      None;
    },
    [|value|],
  );

  React.useEffect2(
    () => {
      options
      ->Belt.Array.keep(({name}) =>
          Js.String.includes(
            Js.String.toLowerCase(filter),
            Js.String.toLowerCase(name),
          )
        )
      ->(x => setFilteredOptions(_ => x));

      None;
    },
    (options, filter),
  );

  <div
    ref={ReactDOMRe.Ref.domRef(element)}
    className={
      Dropdown.Styles.container(state, variant, theme, minWidth)
      ++ "  "
      ++ className
    }>
    <Button.Group className=Styles.buttonContainer>
      {options
       ->Js.Array2.find(_option => _option.value == value)
       ->Belt.Option.mapWithDefault(<Empty />, currentOption =>
           <Button
             disabled
             className={
               Dropdown.Styles.button(state, minWidth)
               ++ "  "
               ++ Styles.actionButton
             }
             variant
             onClick={_ => currentOption.action()}>
             {title->Belt.Option.mapWithDefault(<Empty />, t =>
                <> t->React.string ": "->React.string </>
              )}
             <b> name->React.string </b>
           </Button>
         )}
      <Button
        disabled
        className={
          Dropdown.Styles.button(state, minWidth)
          ++ "  "
          ++ Styles.arrowButton
        }
        variant
        onClick=toggleState>
        <Icons.ChevronDown />
      </Button>
    </Button.Group>
    {switch (state) {
     | Open =>
       <Card
         theme
         depth
         spacing=CardStyles.tiny
         className={Dropdown.Styles.listContainer(variant, theme)}>
         {enableSearch
            ? <Input
                onKeyDown=possiblySubmit
                className=Dropdown.Styles.searchBox
                defaultValue=filter
                placeholder="Search"
                onChange={e =>
                  (e |> ReactEvent.Form.target)##value |> setFilter
                }
              />
            : <Empty />}
         <ul className={Dropdown.Styles.uList(variant, theme, maxHeight)}>
           {filteredOptions
            ->Belt.Array.map(_option =>
                <li
                  key={_option.name}
                  className={Dropdown.Styles.listItem(
                    state,
                    variant,
                    ~theme,
                    ~depth,
                    ~isActive=_option.value === value,
                    (),
                  )}
                  onClick={e => {
                    toggleState(e);
                    callActionOnChange ? _option.action() : ();
                    onChange(_option.value);
                  }}>
                  _option.name->React.string
                </li>
              )
            ->React.array}
         </ul>
       </Card>
     | Closed => <Empty />
     }}
  </div>;
};
