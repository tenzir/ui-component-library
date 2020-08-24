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
  let container = (state, variant, theme, minimumWidth) => {
    let colors = Some(theme)->StyleHelpers.colorsFromThemeVariant;
    let bgColor =
      state === Open
        ? ButtonStyles.defineBackgroundColor(
            colors,
            variant,
            UiTypes.Hovering,
          )
        : ButtonStyles.defineBackgroundColor(colors, variant, UiTypes.Base);

    let shadow =
      state === Open
        ? ButtonStyles.buttonShadow(colors, variant, UiTypes.Hovering)
        : ButtonStyles.buttonShadow(colors, variant, UiTypes.Base);

    style([
      borderRadius(Config.Misc.borderRadius),
      boxShadow(shadow),
      position(`relative),
      backgroundColor(bgColor)->important,
      overflow(`visible),
      minWidth(minimumWidth->px),
    ]);
  };
  let button = (state, minimumWidth) => {
    let openedStyle =
      switch (state) {
      | Open => [
          borderBottomLeftRadius(`zero)->important,
          borderBottomRightRadius(`zero)->important,
          boxShadow(
            Shadow.box(
              ~y=px(0),
              ~x=px(0),
              ~blur=px(5),
              `rgba((0, 0, 0, 0.0)),
            ),
          )
          ->important,
        ]
      | Closed => [
          borderBottomLeftRadius(Config.Misc.borderRadius),
          borderBottomRightRadius(Config.Misc.borderRadius),
        ]
      };
    style([
      width(100.0->pct),
      wordBreak(`breakAll)->important,
      fontSize(0.9->rem)->important,
      minWidth(minimumWidth->px),
      ...openedStyle,
    ]);
  };
  let searchBox = style([marginBottom(1.0->rem)]);
  let listContainer = (variant, theme) => {
    let bgColor =
      Some(theme)
      ->StyleHelpers.colorsFromThemeVariant
      ->ButtonStyles.baseColorDirectlyMapped(variant);
    style([
      position(`absolute)->important,
      left(`zero),
      top(100.0->pct),
      padding2(~h=0.5->rem, ~v=0.5->rem),
      width(`auto)->important,
      height(`auto)->important,
      backgroundColor(bgColor)->important,
      borderTopLeftRadius(`zero)->important,
      borderTopRightRadius(`zero)->important,
      minWidth(100.0->pct)->important,
      zIndex(1),
    ]);
  };

  let uList = (variant, theme, maximumHeight) => {
    let bgColor =
      Some(theme)
      ->StyleHelpers.colorsFromThemeVariant
      ->ButtonStyles.baseColorDirectlyMapped(variant);
    style([
      margin(`zero),
      padding(`zero),
      maxHeight(maximumHeight->px)->important,
      borderRadius(Config.Misc.borderRadius),
      overflowY(`auto)->important,
      listStyleType(`none),
      backgroundColor(bgColor),
    ]);
  };

  let listItem = (state, variant, ~theme=?, ~depth, ~isActive=false, ()) => {
    let colors = StyleHelpers.colorsFromThemeVariant(theme);
    let offset = StyleHelpers.offsetBgColor(theme);
    let bgColor = colors->ButtonStyles.baseColorDirectlyMapped(variant);
    let fontColor =
      state === Open
        ? ButtonStyles.buttonFontColor(colors, variant, UiTypes.Active)
        : ButtonStyles.buttonFontColor(colors, variant, UiTypes.Base);
    style([
      cursor(isActive ? `default : `pointer),
      margin(`zero),
      padding2(~h=1.5->rem, ~v=0.5->rem),
      color(fontColor)->important,
      borderRadius(Config.Misc.borderRadius),
      backgroundColor(isActive ? offset(depth - 2, bgColor) : `transparent),
      hover([
        backgroundColor(offset(depth - 3, bgColor)),
        active([backgroundColor(offset(depth - 3, bgColor))]),
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
      Styles.container(state, variant, theme, minWidth) ++ "  " ++ className
    }>
    <div>
      <Button
        disabled
        className={Styles.button(state, minWidth)}
        variant
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
         className={Styles.listContainer(variant, theme)}>
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
         <ul className={Styles.uList(variant, theme, maxHeight)}>
           {filteredOptions
            ->Belt.Array.map(_option =>
                <li
                  key={_option.name}
                  className={Styles.listItem(
                    state,
                    variant,
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
