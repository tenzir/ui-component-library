open Css;
open Config; /* From UI repo */
open UiTypes;

[@bs.deriving accessors]
type variant =
  | Primary
  | Secondary
  | Success
  | Warning
  | Danger;

let baseColorDirectlyMapped = (colors, variant) =>
  switch (variant) {
  | Primary => colors.primary
  | Secondary => colors.secondary
  | Success => colors.success
  | Warning => colors.warning
  | Danger => colors.danger
  };

let pillShadow = (colors, variant, componentState) => {
  let base = Shadow.box(~y=px(0), ~x=px(0));
  let modifier =
    switch (componentState) {
    | Base => (
        color => base(~blur=px(5), StyleHelpers.rgbWithAlpha(color, 0.2))
      )
    | Active => (
        color =>
          base(
            ~blur=px(5),
            ~inset=true,
            StyleHelpers.rgbWithAlpha(StyleHelpers.darken(5, color), 0.8),
          )
      )
    | Hovering => (
        color => base(~blur=px(10), StyleHelpers.rgbWithAlpha(color, 0.5))
      )
    | _ => (
        color => base(~blur=px(5), StyleHelpers.rgbWithAlpha(color, 0.3))
      )
    };

  modifier(baseColorDirectlyMapped(colors, variant));
};

let pillFontColor = (colors: colors, variant, componentState) => {
  let baseColor =
    switch (variant) {
    | Primary
    | Danger => StyleHelpers.rgbWithAlpha(colors.white, 0.95)
    | Secondary
    | Success
    | Warning => StyleHelpers.rgbWithAlpha(colors.black, 0.7)
    };

  let modifier =
    switch (componentState) {
    | Hovering
    | Base => (x => x)
    | Focus
    | Active => StyleHelpers.lighten(10)
    };

  modifier(baseColor);
};

let defineBackgroundColor = (colors: colors, variant, componentState) => {
  let modifier =
    switch (componentState) {
    | Active => StyleHelpers.activeColorChange
    | Hovering => StyleHelpers.hoverColorChange
    | _ => (x => x)
    };

  modifier(baseColorDirectlyMapped(colors, variant));
};

let messagePill = (~theme, ~variant, ~size, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  let bgColor = defineBackgroundColor(colors, variant);
  let pillFontColor = pillFontColor(colors, variant);
  let pillShadow = pillShadow(colors, variant);
  let padding =
    StyleHelpers.adjustForSizeP4(
      ~size,
      ~left=2.2,
      ~right=1.2,
      ~top=0.6,
      ~bottom=0.65,
    );
  style([
    width(`fitContent),
    backgroundColor(bgColor(Base)),
    borderStyle(`none),
    outlineStyle(`none),
    boxShadow(pillShadow(Base)),
    color(pillFontColor(Base)),
    fontFamily(`custom(Typography.family_default)),
    fontWeight(Typography.weight_button),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    letterSpacing(0.01->rem),
    padding,
    margin(`zero),
    position(`relative),
    hover([
      boxShadow(pillShadow(Hovering)),
      color(pillFontColor(Hovering)),
      backgroundColor(bgColor(Hovering)),
    ]),
    ...Misc.baseTransitions,
  ]);
};

let iconSpace = (size, value) =>
  switch (size) {
  | Small => 0.6 *. value
  | Medium => 1.0 *. value
  | Large => 1.2 *. value
  };
let iconSize = (size, value) =>
  switch (size) {
  | Small => 0.6 *. value
  | Medium => 1.0 *. value
  | Large => 1.2 *. value
  };

let icon = (~size) => {
  let top = top(iconSpace(size, 0.6)->rem);
  let left = left(iconSpace(size, 0.6)->rem);
  let height = height(iconSize(size, 1.1)->rem);
  style([position(`absolute), top, left, selector("& svg", [height])]);
};
