open Webapi.Dom;

type t('a) = {
  name: string,
  value: 'a,
};

type dropdownState =
  | Open
  | Closed;

module Styles = {
  open Css;
  let container = minimumWidth =>
    style([
      position(`relative),
      overflow(`visible),
      minWidth(minimumWidth->px),
    ]);
  let button = minimumWidth =>
    style([
      width(100.0->pct),
      wordBreak(`breakAll)->important,
      fontSize(0.9->rem)->important,
      minWidth(minimumWidth->px),
    ]);
  let searchBox = style([marginBottom(1.0->rem)]);
  let listContainer = maximumHeight =>
    style([
      boxShadow(
        Shadow.box(
          ~y=`zero,
          ~x=`zero,
          ~blur=1.5->rem,
          `rgba((0, 0, 0, 0.2)),
        ),
      ),
      position(`absolute)->important,
      left(`zero),
      top(105.0->pct),
      width(`auto)->important,
      height(`auto)->important,
      minWidth(100.0->pct)->important,
      maxHeight(maximumHeight->px)->important,
      padding2(~h=0.5->rem, ~v=0.3->rem)->important,
      overflowY(`auto)->important,
      zIndex(1),
    ]);

  let uList = style([margin(`zero), padding(`zero), listStyleType(`none)]);

  let listItem = (~theme=?, ~depth, ~isActive=false, ()) => {
    let colors = theme->StyleHelpers.colorsFromThemeVariant;
    let offset = StyleHelpers.offsetBgColor(theme);
    style([
      cursor(isActive ? `default : `pointer),
      margin(`zero),
      padding2(~h=1.5->rem, ~v=0.5->rem),
      borderRadius(Config.Misc.borderRadius),
      backgroundColor(
        isActive ? offset(depth - 1, colors.background) : `transparent,
      ),
      hover([
        backgroundColor(offset(depth + 1, colors.background)),
        active([backgroundColor(offset(depth + 2, colors.background))]),
      ]),
      ...Config.Misc.baseTransitions,
    ]);
  };
};

[@react.component]
let make =
    (
      ~theme,
      ~options,
      ~disabled=false,
      ~enableSearch=false,
      ~value: 'a,
      ~depth=1,
      ~minWidth=150,
      ~maxHeight=250,
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
    element
    ->React.Ref.current
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
    className={Styles.container(minWidth) ++ "  " ++ className}>
    <div>
      <Button
        disabled
        className={Styles.button(minWidth)}
        variant=ButtonStyles.secondary
        onClick=toggleState
        icon={<Icons.ChevronDown />}
        iconPosition=ButtonStyles.Right>
        {title->Belt.Option.mapWithDefault(<Empty />, t =>
           <> t->React.string ": "->React.string </>
         )}
        <b> name->React.string </b>
      </Button>
    </div>
    {switch (state) {
     | Open =>
       <Card
         theme
         depth
         spacing=CardStyles.tiny
         className={Styles.listContainer(maxHeight)}>
         {enableSearch
            ? <Input
                onKeyDown=possiblySubmit
                className=Styles.searchBox
                defaultValue=filter
                placeholder="Search"
                onChange={e =>
                  (e |> ReactEvent.Form.target)##value |> setFilter
                }
              />
            : <Empty />}
         <ul className=Styles.uList>
           {filteredOptions
            ->Belt.Array.map(_option =>
                <li
                  key={_option.name}
                  className={Styles.listItem(
                    ~theme,
                    ~depth,
                    ~isActive=_option.value === value,
                    (),
                  )}
                  onClick={e => {
                    toggleState(e);
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
