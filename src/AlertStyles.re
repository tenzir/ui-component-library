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

let messagePill = (~theme, ~variant, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  let bgColor = defineBackgroundColor(colors, variant);
  let pillFontColor = pillFontColor(colors, variant);
  let pillShadow = pillShadow(colors, variant);
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
    paddingLeft(2.2->rem),
    paddingRight(1.2->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.65->rem),
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

let icon =
  style([
    position(`absolute),
    left(0.8->rem),
    top(11->px),
    selector("& svg", [height(16->px)]),
  ]);
