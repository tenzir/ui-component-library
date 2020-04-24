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

type iconPosition =
  | Left
  | Right;

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

let button = (~theme=?, ~variant, icon, iconPosition, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  let bgColor = defineBackgroundColor(colors, variant);
  let btnFontColor = buttonFontColor(colors, variant);
  let btnShadow = buttonShadow(colors, variant);
  let padding =
    switch (icon, iconPosition) {
    | (None, _) =>
      padding4(
        ~left=1.2->rem,
        ~right=1.2->rem,
        ~top=0.6->rem,
        ~bottom=0.65->rem,
      )
    | (Some(_), Left) =>
      padding4(
        ~left=2.2->rem,
        ~right=1.2->rem,
        ~top=0.6->rem,
        ~bottom=0.65->rem,
      )
    | (Some(_), Right) =>
      padding4(
        ~left=1.2->rem,
        ~right=2.2->rem,
        ~top=0.6->rem,
        ~bottom=0.65->rem,
      )
    };
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
    padding,
    position(`relative),
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

let icon = iconPosition => {
  let pos =
    switch (iconPosition) {
    | Left => left(0.8->rem)
    | Right => right(0.8->rem)
    };
  style([
    pos,
    position(`absolute),
    top(11->px),
    selector("& svg", [height(16->px)]),
  ]);
};

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
