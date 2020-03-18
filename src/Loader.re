open Css;
let pulse =
  keyframes([
    (0, [opacity(0.1)]),
    (60, [opacity(0.5)]),
    (100, [opacity(0.1)]),
  ]);

let loaderStyles =
  style([
    display(`flex),
    alignSelf(`center),
    justifyContent(`center),
    height(100.0->pct),
    width(100.0->pct),
    selector(
      "& circle",
      [
        opacity(0.1),
        animationName(pulse),
        animationDuration(1200),
        animationTimingFunction(`easeInOut),
        animationIterationCount(`infinite),
      ],
    ),
    selector("& circle:nth-of-type(1)", [animationDelay(100)]),
    selector("& circle:nth-of-type(2)", [animationDelay(200)]),
  ]);

type background =
  | Dark
  | Light;

[@react.component]
let make = (~theme, ~className="") => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);

  <div className={loaderStyles ++ "  " ++ className}>
    <Icons.MoreHorizontal
      color={colors.font->Css_AtomicTypes.Color.toString}
      size=40
    />
  </div>;
};

let default = make;
