open Flexboxgrid;

type t = {
  disabled: bool,
  id: string,
  title: string,
};

module Styles = {
  open Css;
  let selectorContainer = theme => {
    let colors = theme->StyleHelpers.colorsFromThemeVariant;
    style([
      backgroundColor(
        StyleHelpers.offsetBgColor(
          theme,
          2,
          StyleHelpers.rgbWithAlpha(colors.background, 0.8),
        ),
      ),
      padding2(~h=0.2->rem, ~v=0.25->rem),
      margin2(~h=`zero, ~v=0.6->rem),
      borderRadius(Config.Misc.borderRadius),
    ]);
  };

  let selectorButton = (theme, disabled, isActive) => {
    let colors = theme->StyleHelpers.colorsFromThemeVariant;
    style([
      backgroundColor(isActive ? colors.secondary : `transparent),
      color(
        isActive
          ? StyleHelpers.rgbWithAlpha(colors.black, 0.8)
          : StyleHelpers.rgbWithAlpha(colors.font, 0.8),
      ),
      textAlign(`center),
      padding2(~h=0.2->rem, ~v=0.25->rem),
      borderRadius(Config.Misc.borderRadius),
      cursor(disabled ? `notAllowed : `pointer),
      opacity(disabled ? 0.2 : 1.0),
      fontWeight(`semiBold),
      flexGrow(1.0),
      ...Config.Misc.baseTransitions,
    ]);
  };
};

[@react.component]
let make = (~segments: array(t), ~onSegmentUpdate, ~theme=?) => {
  let (active: option(string), setActive) =
    React.useState(_ =>
      segments
      ->Belt.Array.keep(x => !x.disabled)
      ->Belt.Array.get(0)
      ->Belt.Option.map(x => x.id)
    );

  React.useEffect1(
    () => {
      switch (active) {
      | Some(segment) => onSegmentUpdate(segment)
      | None => ()
      };
      None;
    },
    [|active|],
  );
  <>
    <Row around=`xs className={Styles.selectorContainer(theme)}>
      {segments
       ->Belt.Array.map(segment => {
           let isActive =
             active->Belt.Option.getWithDefault("") === segment.id;

           <a
             key={segment.title}
             className={Styles.selectorButton(
               theme,
               segment.disabled,
               isActive,
             )}
             onClick={_ =>
               segment.disabled ? () : setActive(_ => Some(segment.id))
             }>
             segment.title->React.string
           </a>;
         })
       ->React.array}
    </Row>
  </>;
};
