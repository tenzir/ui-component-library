[@bs.deriving accessors]
type horizontal =
  | Left
  | Center
  | Right;

[@bs.deriving accessors]
type vertical =
  | Top
  | Middle
  | Bottom;

[@bs.deriving accessors]
type tPosition =
  | Top(horizontal)
  | Bottom(horizontal)
  | Left(vertical)
  | Right(vertical);

let tip = (~theme=UiTypes.light, ~tipPosition=Top(Center), value) => {
  open Css;
  let colors = StyleHelpers.colorsFromThemeVariant(theme);

  /* ---- Configuration */
  let (tooltipBackground, tooltipTextColor, tooltipShadowColor) =
    switch (theme) {
    | UiTypes.Dark => (
        colors.background,
        colors.font,
        StyleHelpers.rgbWithAlpha(colors.black, 0.8),
      )
    | UiTypes.Light => (
        colors.background,
        colors.font,
        StyleHelpers.rgbWithAlpha(colors.black, 0.2),
      )
    | UiTypes.TenzirBlue => (
        colors.background,
        colors.font,
        StyleHelpers.rgbWithAlpha(colors.black, 0.5),
      )
    };
  let tipHeight = 10; // in px
  let offset = 5; // in px
  let tipInset = 5;
  /* ---- Configuration */

  let horizontalPositioning =
      (h: horizontal, vOffset, ~rotation=0.->deg, ~addTipInset=false, ()) =>
    switch (h) {
    | Left => [
        left(0.0->pct),
        marginLeft((addTipInset ? tipInset : 0)->px),
        transforms([translateY(vOffset), rotate(rotation)]),
      ]
    | Center => [
        left(50.0->pct),
        transforms([translate((-50.)->pct, vOffset), rotate(rotation)]),
      ]
    | Right => [
        left(100.0->pct),
        marginLeft((addTipInset ? - tipInset : 0)->px),
        transforms([translate((-100.)->pct, vOffset), rotate(rotation)]),
      ]
    };

  let verticalPositioning =
      (v: vertical, hOffset, ~rotation=0.->deg, ~addTipInset=false, ()) =>
    switch (v) {
    | Top => [
        top(0.->pct),
        marginTop((addTipInset ? tipInset : 0)->px),
        transforms([translateX(hOffset), rotate(rotation)]),
      ]
    | Middle => [
        top(50.0->pct),
        transforms([translate(hOffset, (-50.)->pct), rotate(rotation)]),
      ]
    | Bottom => [
        top(100.0->pct),
        marginTop((addTipInset ? - tipInset : 0)->px),
        transforms([translate(hOffset, (-100.)->pct), rotate(rotation)]),
      ]
    };

  let positions =
    switch ((tipPosition: tPosition)) {
    | Top(h) => [
        bottom(100.->pct),
        ...horizontalPositioning(h, (- tipHeight - offset)->px, ()),
      ]
    | Bottom(h) => [
        top(100.->pct),
        ...horizontalPositioning(h, (tipHeight + offset)->px, ()),
      ]
    | Left(v) => [
        right(100.->pct),
        ...verticalPositioning(v, (- tipHeight - offset)->px, ()),
      ]
    | Right(v) => [
        left(100.->pct),
        ...verticalPositioning(v, (tipHeight + offset)->px, ()),
      ]
    };

  let tipPositions =
    switch ((tipPosition: tPosition)) {
    | Top(h) => [
        bottom(100.->pct),
        ...horizontalPositioning(
             h,
             (- tipHeight - offset - 2)->px,
             ~rotation=180.->deg,
             ~addTipInset=true,
             (),
           ),
      ]
    | Bottom(h) => [
        top(100.->pct),
        ...horizontalPositioning(h, (offset + 3)->px, ~addTipInset=true, ()),
      ]
    | Left(v) => [
        right(100.->pct),
        ...verticalPositioning(
             v,
             (- tipHeight - offset - 4)->px,
             ~rotation=90.->deg,
             ~addTipInset=true,
             (),
           ),
      ]
    | Right(v) => [
        left(100.->pct),
        ...verticalPositioning(
             v,
             (offset + 3)->px,
             ~rotation=270.->deg,
             ~addTipInset=true,
             (),
           ),
      ]
    };

  Css.(
    style([
      position(`relative),
      selector(
        "&:before",
        [
          position(`absolute),
          display(`block),
          padding2(~h=0.8->rem, ~v=0.4->rem),
          boxShadow(
            Shadow.box(~y=0->px, ~x=0->px, ~blur=10->px, tooltipShadowColor),
          ),
          fontWeight(`semiBold),
          borderRadius(Config.Misc.borderRadius),
          backgroundColor(tooltipBackground),
          color(tooltipTextColor),
          unsafe("content", "\"" ++ value ++ "\""),
          whiteSpace(`nowrap),
          zIndex(999),
          opacity(0.),
          transitionProperty("all"),
          transitionDuration(200),
          transitionTimingFunction(`easeInOut),
          ...positions,
        ],
      ),
      selector(
        "&:after",
        [
          left(`zero),
          top(`zero),
          position(`absolute),
          display(`block),
          width(0->px),
          height(0->px),
          borderLeft(6->px, `solid, `transparent),
          borderRight(6->px, `solid, `transparent),
          borderBottom(8->px, `solid, tooltipBackground),
          zIndex(100),
          opacity(0.),
          transitionProperty("all"),
          transitionDuration(200),
          transitionTimingFunction(`easeInOut),
          unsafe("content", ""),
          ...tipPositions,
        ],
      ),
      hover([
        selector("&:before", [opacity(1.)]),
        selector("&:after", [opacity(1.)]),
      ]),
    ])
  );
};

module Examples = {
  module Styles = {
    open Css;
    let exampleContainer =
      style([
        padding2(~h=2.->rem, ~v=1.->rem),
        selector(
          "& span",
          [
            display(`inlineBlock),
            padding(1.->rem),
            margin(1.->rem),
            backgroundColor(`rgba((128, 128, 128, `num(0.5)))),
          ],
        ),
      ]);
  };

  [@react.component]
  let make = (~theme) => {
    let themedTip = tip(~theme);
    <>
      <div className=Styles.exampleContainer>
        <span className={themedTip(~tipPosition=Top(Left), "T-L")}>
          "Top Left"->React.string
        </span>
        <span className={themedTip(~tipPosition=Top(Center), "T-C")}>
          "Top Center"->React.string
        </span>
        <span className={themedTip(~tipPosition=Top(Right), "T-R")}>
          "Top Right"->React.string
        </span>
      </div>
      <div className=Styles.exampleContainer>
        <span className={themedTip(~tipPosition=Bottom(Left), "B-L")}>
          "Bottom Left"->React.string
        </span>
        <span className={themedTip(~tipPosition=Bottom(Center), "B-C")}>
          "Bottom Center"->React.string
        </span>
        <span className={themedTip(~tipPosition=Bottom(Right), "B-R")}>
          "Bottom Right"->React.string
        </span>
      </div>
      <div className=Styles.exampleContainer>
        <span className={themedTip(~tipPosition=Left(Top), "L-T")}>
          "Left Top"->React.string
        </span>
        <span className={themedTip(~tipPosition=Left(Middle), "L-M")}>
          "Left Middle"->React.string
        </span>
        <span className={themedTip(~tipPosition=Left(Bottom), "L-B")}>
          "Left Bottom"->React.string
        </span>
      </div>
      <div className=Styles.exampleContainer>
        <span className={themedTip(~tipPosition=Right(Top), "R-T")}>
          "Right Top"->React.string
        </span>
        <span className={themedTip(~tipPosition=Right(Middle), "R-M")}>
          "Right Middle"->React.string
        </span>
        <span className={themedTip(~tipPosition=Right(Bottom), "R-B")}>
          "Right Bottom"->React.string
        </span>
      </div>
    </>;
  };
};
