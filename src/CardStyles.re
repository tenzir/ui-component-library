open Css;
open Config;

[@bs.deriving accessors]
type spacing =
  | Tiny
  | Normal
  | Large
  | Huge;

let deteriminePadding = spacing => {
  let baseBadding = 1.0;
  switch (spacing) {
  | Tiny =>
    padding2(~h=(baseBadding *. 0.8)->rem, ~v=(baseBadding *. 0.6)->rem)
  | Normal =>
    padding2(~h=(baseBadding *. 1.2)->rem, ~v=(baseBadding *. 1.1)->rem)
  | Large =>
    padding2(~h=(baseBadding *. 2.2)->rem, ~v=(baseBadding *. 1.6)->rem)
  | Huge =>
    padding2(~h=(baseBadding *. 3.2)->rem, ~v=(baseBadding *. 2.6)->rem)
  };
};

let card = (~theme, ~spacing=Normal, ~depth, ~styles, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  let extraStyles = Belt.Option.getWithDefault(styles, []);
  style([
    width(100.0->pct),
    height(100.0->pct),
    overflow(`hidden),
    backgroundColor(
      StyleHelpers.offsetBgColor(theme, depth, colors.background),
    ),
    color(colors.font),
    fontFamily(`custom(Typography.family_default)),
    fontWeight(Typography.weight_default),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    deteriminePadding(spacing),
    position(`relative),
    ...extraStyles,
  ]);
};

let cardHeader = (~theme, ~depth, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    height(3.5->rem),
    position(`absolute),
    left(`zero),
    top(`zero),
    display(`flex),
    alignItems(`center),
    padding2(~h=0.0->rem, ~v=0.0->rem),
    width(100.0->pct),
    backgroundColor(
      StyleHelpers.offsetBgColor(theme, depth + 1, colors.background)
      ->StyleHelpers.rgbWithAlpha(0.5),
    ),
  ]);
};

let cardContent = (~hasHeader, ~hasFooter) => {
  style([
    paddingTop(hasHeader ? 3.5->rem : 0.0->rem),
    paddingBottom(hasFooter ? 3.5->rem : 0.0->rem),
    width(100.0->pct),
    height(100.0->pct),
  ]);
};

let cardFooter = (~theme, ~depth, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    height(3.5->rem),
    position(`absolute),
    left(`zero),
    bottom(`zero),
    display(`flex),
    alignItems(`center),
    padding2(~h=0.0->rem, ~v=0.0->rem),
    width(100.0->pct),
    backgroundColor(
      StyleHelpers.offsetBgColor(theme, depth + 1, colors.background)
      ->StyleHelpers.rgbWithAlpha(0.5),
    ),
  ]);
};
