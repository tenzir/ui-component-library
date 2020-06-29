open Css;
open Config;
open UiTypes;

let inputFontWeight = variant =>
  switch (variant) {
  | Normal => Typography.weight_default
  | Mono => Typography.weight_mono
  };

let inputFontFamily = variant =>
  switch (variant) {
  | Normal => Typography.family_default
  | Mono => Typography.family_mono
  };

let labelFontColor = (colors: colors, componentState) =>
  switch (componentState) {
  | Hovering => StyleHelpers.lighten(20, colors.font)
  | _ => colors.font
  };

let inputFontColor = (colors: colors, componentState) =>
  switch (componentState) {
  | Hovering => StyleHelpers.lighten(20, colors.input)
  | _ => colors.input
  };

let inputBordercolor = (colors: colors, componentState, ~validity=Valid, ()) =>
  switch (componentState, validity) {
  | (Base, Invalid) => colors.danger
  | (Hovering, Invalid) => StyleHelpers.lighten(25, colors.danger)
  | (Active, Invalid)
  | (Focus, Invalid) => StyleHelpers.lighten(8, colors.danger)
  | (Base, Valid) => StyleHelpers.lighten(80, colors.input)
  | (Hovering, Valid) => StyleHelpers.lighten(50, colors.input)
  | (Active, Valid)
  | (Focus, Valid) => StyleHelpers.lighten(40, colors.input)
  };

let inputContainerStyles = (~pctWidth=100.0, ~label=Unlabeled, ()) =>
  style([
    width(pctWidth->pct),
    paddingTop(
      switch (label) {
      | Labeled(_) => 0.7->rem
      | Unlabeled => 0.0->rem
      },
    ),
    display(`inlineBlock),
    position(`relative),
  ]);

let inputStyles = (~theme=?, ~validity, ~variant=Normal, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    display(`inlineBlock),
    width(100.0->pct),
    borderStyle(`solid),
    borderWidth(2->px),
    borderColor(inputBordercolor(colors, Base, ~validity, ())),
    outlineStyle(`none),
    color(inputFontColor(colors, Base)),
    fontFamily(variant->inputFontFamily),
    fontWeight(variant->inputFontWeight),
    fontSize(Typography.size),
    borderRadius(Misc.borderRadius),
    paddingLeft(1.1->rem),
    paddingRight(1.1->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.6->rem),
    disabled([
      cursor(`notAllowed),
      backgroundColor(StyleHelpers.rgbWithAlpha(colors.white, 0.8)),
    ]),
    hover([
      color(inputFontColor(colors, Hovering)),
      borderColor(inputBordercolor(colors, Hovering, ~validity, ())),
    ]),
    focus([
      color(inputFontColor(colors, Focus)),
      borderColor(inputBordercolor(colors, Focus, ~validity, ())),
    ]),
    ...Misc.baseTransitions,
  ]);
};

let labelStyles = (~theme=?, ~variant=Normal, ()) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  style([
    display(`block),
    color(labelFontColor(colors, Base)),
    fontFamily(variant->inputFontFamily),
    fontWeight(variant->inputFontWeight),
    fontSize(Typography.size_label),
    paddingLeft(0.6->rem),
    paddingRight(0.6->rem),
    paddingTop(0.6->rem),
    paddingBottom(0.6->rem),
    hover([
      color(labelFontColor(colors, Hovering)),
      borderColor(inputBordercolor(colors, Hovering, ())),
    ]),
    ...Misc.baseTransitions,
  ]);
};
