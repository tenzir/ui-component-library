open Css;
open Config;
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

let buttonShadow = (colors, variant, componentState) => {
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

let buttonFontColor = (colors: colors, variant, componentState) => {
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

let button = (~theme=?, ~variant, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  let bgColor = defineBackgroundColor(colors, variant);
  let btnFontColor = buttonFontColor(colors, variant);
  let btnShadow = buttonShadow(colors, variant);
  style([
    backgroundColor(bgColor(Base)),
    borderStyle(`none),
    outlineStyle(`none),
    cursor(`pointer),
    boxShadow(btnShadow(Base)),
    color(btnFontColor(Base)),
    fontFamily(Typography.family_default),
    fontWeight(Typography.weight_button),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    letterSpacing(0.01->rem),
    paddingLeft(1.2->rem),
    paddingRight(1.2->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.65->rem),
    hover([
      boxShadow(btnShadow(Hovering)),
      color(btnFontColor(Hovering)),
      backgroundColor(bgColor(Hovering)),
    ]),
    active([
      boxShadow(btnShadow(Active)),
      color(btnFontColor(Active)),
      backgroundColor(bgColor(Active)),
    ]),
    selector("&[disabled]", [opacity(0.8), cursor(`notAllowed)]),
    ...Misc.baseTransitions,
  ]);
};

let icon = () => style([backgroundColor(`rgb((0, 0, 0)))]);

let buttonGroup =
  style([
    position(`relative),
    selector(
      "& > button",
      [
        borderRadius(`zero),
        position(`relative),
        selector(
          "&:after",
          [
            contentRule(""),
            position(absolute),
            width(1->px),
            height(50.0->pct),
            right(`zero),
            top(25.0->pct),
            backgroundColor(`rgba((0, 0, 0, 0.1))),
          ],
        ),
      ],
    ),
    selector(
      "& > button:first-child",
      [
        borderTopLeftRadius(Misc.borderRadius),
        borderBottomLeftRadius(Misc.borderRadius),
      ],
    ),
    selector(
      "& > button:last-child",
      [
        borderTopRightRadius(Misc.borderRadius),
        borderBottomRightRadius(Misc.borderRadius),
      ],
    ),
  ]);
