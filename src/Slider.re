open Flexboxgrid;

module Raw = {
  let sliderPosition: (string, int) => int = [%bs.raw
    {|
    function (id, width) {
      const element = document.getElementById(id);
      if(!element) return 0;

      const reversed = element.min < 0;
      const range = Math.abs(element.max - element.min);
      const offset = Math.abs((Number(element.value) / Number(range) * Number(element.clientWidth)) - (Number(element.value) / Number(range) * (width)));

      return reversed ? (element.clientWidth - offset - ( width)) : offset;
    }
  |}
  ];
};

/* CONFIG */
module Conf = {
  open Css;
  let width = 50;
  let height = 22;
  let widthPx = width->px;
  let heightPx = height->px;
  let borderRadius = 5->px;
};

type align =
  | Left
  | Center
  | Right;

[@bs.deriving accessors]
type variant =
  | Primary
  | Secondary;

let baseColorDirectlyMapped = (colors: Config.colors, variant) =>
  switch (variant) {
  | Primary => colors.primary
  | Secondary => colors.secondary
  };

module Styles = {
  open Css;
  let container =
    style([
      hover([
        selector("& div.children", [pointerEvents(`unset), opacity(1.0)]),
      ]),
      position(`relative),
      overflow(`visible),
    ]);

  let value = (theme, font) => {
    let colors = theme->StyleHelpers.colorsFromThemeVariant;
    let family =
      switch (font) {
      | UiTypes.Mono => Config.Typography.family_mono
      | UiTypes.Normal => Config.Typography.family_default
      };
    style([
      color(StyleHelpers.rgbWithAlpha(colors.black, 0.8)),
      textAlign(`center),
      fontSize(0.8->rem),
      fontFamily(`custom(family)),
    ]);
  };

  let children = (xPos, yOffset) =>
    style([
      textAlign(`center),
      borderRadius(Conf.borderRadius),
      position(`absolute),
      top((- yOffset)->px),
      paddingBottom(60->px), /* We offset the  */
      height(Conf.heightPx),
      left((xPos + Conf.width / 2)->px),
      pointerEvents(`none),
      transforms([translateX((-50.0)->pct)]),
      fontWeight(`semiBold),
      opacity(0.0),
      transitionProperty("opacity"),
      transitionDuration(200),
      transitionTimingFunction(`easeInOut),
      zIndex(999),
    ]);

  let rangeButton = (theme, variant, xPos) => {
    let colors = StyleHelpers.colorsFromThemeVariant(theme);
    style([
      textAlign(`center),
      width(Conf.widthPx),
      height(Conf.heightPx),
      lineHeight(Conf.heightPx),
      borderRadius(Conf.borderRadius),
      position(`absolute),
      pointerEvents(`none),
      top(0->px),
      left((xPos + Conf.width / 2)->px),
      transforms([translateX((-50.0)->pct)]),
      fontWeight(`semiBold),
      backgroundColor(variant |> baseColorDirectlyMapped(colors)),
      transitionProperty("opacity"),
      transitionDuration(200),
      transitionTimingFunction(`easeInOut),
    ]);
  };

  let thumb = [
    unsafe("-webkit-appearance", "none"),
    borderWidth(`zero),
    marginTop((- Conf.height / 2)->px),
    width(Conf.widthPx),
    height(Conf.heightPx),
    lineHeight(Conf.heightPx),
    borderRadius(Conf.borderRadius),
    backgroundColor(transparent),
  ];

  let track = theme => {
    let colors = StyleHelpers.colorsFromThemeVariant(theme);
    [
      width(100.0->pct),
      backgroundColor(
        StyleHelpers.offsetBgColor(theme, 2, colors.background),
      ),
      height(0.2->rem),
      hover([
        backgroundColor(
          StyleHelpers.offsetBgColor(theme, 3, colors.background),
        ),
      ]),
      ...Config.Misc.baseTransitions,
    ];
  };
  let range = theme =>
    style([
      width(100.0->pct),
      unsafe("-webkit-appearance", "none"),
      backgroundColor(`transparent),
      cursor(`pointer),
      focus([outline(`zero, `none, `transparent)]),
      selector("&::-webkit-slider-thumb", thumb),
      selector("&::-moz-range-thumb", thumb),
      selector("&::-webkit-slider-runnable-track", track(theme)),
      selector("&::-moz-range-track", track(theme)),
    ]);
};

[@react.component]
let make =
    (
      ~theme,
      ~label=UiTypes.Unlabeled,
      ~min=0,
      ~max=100,
      ~value: int,
      ~displayValue=?,
      ~align=Left,
      ~font=UiTypes.Normal,
      ~variant=Primary,
      ~id=?,
      ~onChange=?,
      ~onInput=?,
      ~className="",
      ~childrenOffset=0,
      ~children=?,
    ) => {
  let (overlayPosition, setOverlayPosition) = React.useState(_ => 0);
  let identifier = GenericHelpers.genIdentifier(id, label);

  React.useLayoutEffect1(
    () => {
      setOverlayPosition(_ => Raw.sliderPosition(identifier, Conf.width));
      None;
    },
    [|value, min, max|],
  );

  let aligned = elem =>
    switch (align) {
    | Left => <Row> elem </Row>
    | Center => <Row center=`xs> elem </Row>
    | Right => <Row _end=`xs> elem </Row>
    };

  <div>
    {aligned(<Label label identifier variant=font theme={Some(theme)} />)}
    <div className={Styles.container ++ "  " ++ className}>
      <input
        id=identifier
        ?onChange
        ?onInput
        className={Styles.range(theme->Some)}
        type_="range"
        value={value |> string_of_int}
        min={min->string_of_int}
        max={max->string_of_int}
      />
      {children->Belt.Option.mapWithDefault(<Empty />, children =>
         <div
           className={
             Styles.children(overlayPosition, yOffset) ++ " children"
           }>
           children
         </div>
       )}
      <div
        className={Styles.rangeButton(theme->Some, variant, overlayPosition)}>
        <span className={Styles.value(theme->Some, font)}>
          {displayValue
           ->Belt.Option.getWithDefault(value |> string_of_int)
           ->React.string}
        </span>
      </div>
    </div>
  </div>;
};
