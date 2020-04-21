open Css;
open Config;
open UiTypes;

let labelFontColor = (colors: colors, componentState, ~validity=Valid, ()) =>
  switch (componentState, validity) {
  | (Hovering, Invalid) => StyleHelpers.lighten(20, colors.danger)
  | (_, Invalid) => colors.danger
  | (Hovering, Valid) => StyleHelpers.lighten(20, colors.font)
  | (_, Valid) => colors.font
  };

let inputFontColor = (colors: colors, componentState) =>
  switch (componentState) {
  | Hovering => StyleHelpers.lighten(20, colors.input)
  | _ => colors.input
  };

let inputContainerStyles = (~pctWidth=100.0, ~disabled, ()) =>
  style([
    width(pctWidth->pct),
    paddingTop(0.7->rem),
    display(`inlineBlock),
    position(`relative),
    opacity(disabled ? 0.5 : 1.0),
    selector(
      "& input, & label",
      [cursor(disabled ? `notAllowed : `default)],
    ),
    hover([cursor(disabled ? `notAllowed : `default)]),
  ]);

let checkboxStyles = (~theme=?, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    display(`inline),
    borderStyle(`solid),
    borderWidth(2->px),
    borderColor(colors.danger),
    outlineStyle(`none),
    color(inputFontColor(colors, Base)),
    fontFamily(Typography.family_default),
    fontWeight(Typography.weight_default),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    paddingLeft(1.1->rem),
    paddingRight(1.1->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.6->rem),
    marginRight(0.6->rem),
    ...Misc.baseTransitions,
  ]);
};

let labelStyles = (~theme=?, ~validity, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    color(labelFontColor(colors, Base, ~validity, ())),
    fontFamily(Typography.family_default),
    fontWeight(Typography.weight_default),
    fontSize(Typography.size_label),
    paddingLeft(0.6->rem),
    paddingRight(0.6->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.6->rem),
    ...Misc.baseTransitions,
  ]);
};
