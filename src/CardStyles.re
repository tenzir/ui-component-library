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
  | Tiny => padding2(~h=(baseBadding *. 1.2)->rem, ~v=baseBadding->rem)
  | Normal =>
    padding2(~h=(baseBadding *. 2.2)->rem, ~v=(baseBadding *. 2.0)->rem)
  | Large =>
    padding2(~h=(baseBadding *. 3.2)->rem, ~v=(baseBadding *. 3.0)->rem)
  | Huge =>
    padding2(~h=(baseBadding *. 4.2)->rem, ~v=(baseBadding *. 4.0)->rem)
  };
};

let card = (~theme=?, ~spacing=Normal, ~depth, ~styles, ()) => {
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
    fontFamily(Typography.family_default),
    fontWeight(Typography.weight_default),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    deteriminePadding(spacing),
    ...extraStyles,
  ]);
};
