open Css_AtomicTypes;
open UiTypes;

let defaultTheme = UiTypes.Light;

type colors = {
  background: Color.t,
  darkBlueBg: Color.t,
  primary: Color.t,
  secondary: Color.t,
  success: Color.t,
  warning: Color.t,
  danger: Color.t,
  input: Color.t,
  font: Color.t,
  black: Color.t,
  white: Color.t,
};

module Colors = {
  let hoverChangeType = Lighten;
  let hoverChangePercent = 8;
  let activeChangeType = Darken;
  let activeChangePercent = 5;
  let light = {
    background: `rgb((254, 255, 255)),
    darkBlueBg: `rgba((0, 51, 77, `num(1.0))),
    primary: `rgb((0, 164, 241)),
    secondary: `rgb((189, 207, 219)),
    success: `rgb((154, 248, 0)),
    warning: `rgb((248, 237, 0)),
    danger: `rgb((248, 65, 10)),
    input: `rgb((34, 34, 34)),
    font: `rgb((34, 34, 34)),
    black: `rgb((34, 34, 34)),
    white: `rgb((238, 238, 238)),
  };

  let dark = {
    ...light,
    background: `rgb((34, 38, 38)),
    font: `rgb((238, 238, 238)),
  };

  let tenzirBlue = {
    ...light,
    background: `rgba((0, 51, 77, `num(1.0))),
    font: `rgb((238, 238, 238)),
  };
};

module Typography = {
  open Length;
  let family_default = "'Source Sans Pro', sans-serif;";
  let family_mono = "'Source Code Pro', monospace;";
  let size = 15->px;
  let size_label = 14->px;
  let weight_default = `normal;
  let weight_button = `semiBold;
  let weight_mono = `semiBold;
};

module Misc = {
  open Css;
  let baseXPadding = 1.0->rem;
  let baseYPadding = 0.5->rem;
  let borderRadius = 0.2->rem;
  let cardDarkeningPct = 4;
  let baseTransitions = [
    transitionProperty("all"),
    transitionDuration(200),
    transitionTimingFunction(`easeInOut),
  ];
};
