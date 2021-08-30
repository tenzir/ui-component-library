open UiTypes;
open Config;
open GenericHelpers;

/* Converts `rgb to `rgba */
let rgbWithAlpha = (rgb, alpha) =>
  switch (rgb) {
  | `rgb(r, g, b) => `rgba((r, g, b, `num(alpha)))
  | x => x
  };

/* Map over r,g,b, return tuple instead of List */
let mapRGB = (fn, r, g, b) =>
  switch ([r, g, b]->Belt.List.map(fn)) {
  | [nR, nG, nB] => (nR, nG, nB)
  | _ => (r, g, b)
  };

/* Add or subtract percentage of 255 from color */
let applyPercentageToColor =
    (changeType, percentage, color: Css_AtomicTypes.Color.t) => {
  let operation =
    switch (changeType) {
    | Lighten => operatePercent(percentage, Add)
    | Darken => operatePercent(percentage, Subtract)
    };

  let change = value => operation(value) |> bound(0, 255);

  switch (color) {
  | `rgb(r, g, b) => `rgb(mapRGB(change, r, g, b))
  | `rgba(r, g, b, a) =>
    let (nR, nG, nB) = mapRGB(change, r, g, b);
    `rgba((nR, nG, nB, a));
  | _ => color
  };
};

/* Partially applied to specifically lighten or darken a color */
let lighten = applyPercentageToColor(Lighten);
let darken = applyPercentageToColor(Darken);

let offsetBgColorFlt = (theme, depth: float, color) => {
  (
    switch (theme) {
    | UiTypes.Dark
    | UiTypes.TenzirBlue =>
      float_of_int(Misc.cardDarkeningPct) *. (depth *. (-1.) -. 1.)
    | _ => float_of_int(Misc.cardDarkeningPct) *. depth
    }
  )
  ->int_of_float
  ->darken(color);
};

let offsetBgColor = (theme, depth, color) => {
  (
    switch (theme) {
    | UiTypes.Dark
    | UiTypes.TenzirBlue => Misc.cardDarkeningPct * (depth * (-1) - 1)
    | _ => Misc.cardDarkeningPct * depth
    }
  )
  ->darken(color);
};

let hoverColorChange =
  switch (Colors.hoverChangeType) {
  | Lighten => lighten(Colors.hoverChangePercent)
  | Darken => darken(Colors.hoverChangePercent)
  };

let activeColorChange =
  switch (Colors.activeChangeType) {
  | Lighten => lighten(Colors.activeChangePercent)
  | Darken => darken(Colors.activeChangePercent)
  };

let colorsFromThemeVariant = (themeVariant: UiTypes.theme) =>
  switch (themeVariant) {
  | Light => Colors.light
  | Dark => Colors.dark
  | TenzirBlue => Colors.tenzirBlue
  };

let adjustForSize = (size, value) =>
  switch (size) {
  | Small => 0.6 *. value
  | Medium => 1.0 *. value
  | Large => 1.2 *. value
  };

let adjustForSizeP4 =
  Css.(
    (~size, ~left, ~right, ~top, ~bottom) => {
      padding4(
        ~left=adjustForSize(size, left)->rem,
        ~right=adjustForSize(size, right)->rem,
        ~top=adjustForSize(size, top)->rem,
        ~bottom=adjustForSize(size, bottom)->rem,
      );
    }
  );
