open Css;
open Config;
open UiTypes;

[@bs.deriving accessors]
type resize =
  | NoResize
  | Both
  | Horizontal
  | Vertical
  | Initial
  | Inherit;

let textareaFontWeight = variant =>
  switch (variant) {
  | Normal => Typography.weight_default
  | Mono => Typography.weight_mono
  };

let textareaFontFamily = variant =>
  switch (variant) {
  | Normal => Typography.family_default
  | Mono => Typography.family_mono
  };

let labelFontColor = (colors: colors, componentState) =>
  switch (componentState) {
  | Hovering => StyleHelpers.lighten(20, colors.font)
  | _ => colors.font
  };

let textareaFontColor = (colors: colors, componentState) =>
  switch (componentState) {
  | Hovering => StyleHelpers.lighten(20, colors.input)
  | _ => colors.input
  };

let textareaBordercolor = (colors: colors, componentState, ~validity=Valid, ()) =>
  switch ((componentState, validity)) {
  | ( Base, Invalid ) => colors.danger
  | ( Hovering, Invalid ) => StyleHelpers.lighten(25, colors.danger)
  | ( Active, Invalid )
  | ( Focus, Invalid ) => StyleHelpers.lighten(8, colors.danger)
  | ( Base, Valid ) => StyleHelpers.lighten(80, colors.input)
  | ( Hovering, Valid ) => StyleHelpers.lighten(50, colors.input)
  | ( Active, Valid )
  | ( Focus, Valid ) => StyleHelpers.lighten(40, colors.input)
  };

let textareaResize = resize =>
  switch (resize) {
  | NoResize => `none
  | Both => `both
  | Horizontal => `horizontal
  | Vertical => `vertical
  | Initial => `initial
  | Inherit => `inherit_
  };

let textareaContainerStyles = (~pctWidth=100.0, ~labeled=false, ()) =>
  style([
    width(pctWidth->pct),
    paddingTop(labeled ? 0.7->rem : 0.0->rem),
    display(`inlineBlock),
    position(`relative),
  ]);

let textareaStyles =
    (~theme=?, ~variant=Normal, ~resize as resizeType, ~validity, ~styles=[], ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    resize(textareaResize(resizeType)),
    display(`inlineBlock),
    width(100.0->pct),
    borderStyle(`solid),
    borderWidth(2->px),
    borderColor(textareaBordercolor(colors, Base, ~validity, ())),
    outlineStyle(`none),
    color(textareaFontColor(colors, Base)),
    fontFamily(variant->textareaFontFamily),
    fontWeight(variant->textareaFontWeight),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    paddingLeft(1.1->rem),
    paddingRight(1.1->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.6->rem),
    hover([
      color(textareaFontColor(colors, Hovering)),
      borderColor(textareaBordercolor(colors, Hovering, ~validity, ())),
    ]),
    focus([
      color(textareaFontColor(colors, Focus)),
      borderColor(textareaBordercolor(colors, Focus, ~validity, ())),
    ]),
    transitionProperty("border-color"),
    transitionDuration(200),
    transitionTimingFunction(`cubicBezier((0.72, 0.37, 0.51, 1.23))),
    ...styles,
  ]);
};

let labelStyles = (~theme=?, ~variant=Normal, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    display(`inlineBlock),
    color(labelFontColor(colors, Base)),
    fontFamily(variant->textareaFontFamily),
    fontWeight(variant->textareaFontWeight),
    fontSize(Typography.size_label),
    paddingLeft(0.6->rem),
    paddingRight(0.6->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.6->rem),
    hover([
      color(labelFontColor(colors, Hovering)),
      borderColor(textareaBordercolor(colors, Hovering, ())),
    ]),
    ...Misc.baseTransitions,
  ]);
};
