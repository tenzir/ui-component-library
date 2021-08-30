open Css;

let calcBg = (theme, depth) => {
  let colors = StyleHelpers.colorsFromThemeVariant(theme);
  StyleHelpers.offsetBgColorFlt(theme, depth, colors.background);
};

let droppable =
  style([
    margin(`zero),
    padding(`zero),
    display(`flex),
    width(100.->pct),
    height(100.->pct),
    paddingTop(0.5->rem),
    paddingLeft(0.5->rem),
    paddingRight(0.5->rem),
    overflowX(`auto),
    overflowY(`visible),
  ]);

let container = (standalone, theme, depth) =>
  style([
    backgroundColor(calcBg(theme, float_of_int(depth) +. 0.5)),
    boxShadow(
      Shadow.box(
        ~y=(-10)->px,
        ~x=`zero,
        ~spread=0->px,
        ~blur=10->px,
        ~inset=true,
        `rgba((0, 0, 0, `num(0.02))),
      ),
    ),
    display(`flex),
    position(standalone ? `static : `absolute),
    alignItems(`flexEnd),
    borderRadius(Config.Misc.borderRadius),
    left(standalone ? `unset : `zero),
    right(standalone ? `unset : `zero),
    top(standalone ? `unset : `zero),
    height(standalone ? 3.5->rem : 3.0->rem),
  ]);
let input = style([maxWidth(100->px)]);
let text = (active, canUpdate) =>
  style([
    display(`block),
    maxWidth(100->px),
    overflow(`hidden),
    whiteSpace(`nowrap),
    textOverflow(`ellipsis),
    cursor(active && canUpdate ? `text : `pointer)->important,
  ]);

let roundedIconButton = (~leftMargin=false, theme, depth, active) =>
  style([
    cursor(`pointer)->important,
    margin(`zero),
    marginLeft(leftMargin ? 0.5->rem : `zero),
    width(1.5->rem),
    height(1.5->rem),
    borderRadius(1.0->rem),
    alignItems(`center),
    justifyContent(`center),
    display(`flex),
    hover([
      backgroundColor(
        active
          ? calcBg(theme, float_of_int(depth + 1))
          : calcBg(theme, float_of_int(depth + 2)),
      ),
    ]),
    ...Config.Misc.baseTransitions,
  ]);
let tab = (theme, depth, active, canOpen) =>
  style([
    cursor(canOpen ? `auto : `notAllowed),
    backgroundColor(
      active ? calcBg(theme, float_of_int(depth)) : `transparent,
    ),
    borderTopLeftRadius(Config.Misc.borderRadius),
    borderTopRightRadius(Config.Misc.borderRadius),
    display(`flex),
    justifyContent(`center),
    alignItems(`center),
    alignContent(`center),
    height(2.5->rem),
    paddingLeft(1.0->rem),
    paddingRight(0.5->rem),
    fontWeight(`semiBold),
    boxShadow(
      Shadow.box(
        ~y=`zero,
        ~x=`zero,
        ~spread=0->px,
        ~blur=10->px,
        active ? `rgba((0, 0, 0, `num(0.02))) : `transparent,
      ),
    ),
    selector(
      "& ."
      ++ roundedIconButton(~leftMargin=true, theme, depth, active)
      ++ ", & ."
      ++ roundedIconButton(~leftMargin=false, theme, depth, active),
      [opacity(0.2)],
    ),
    hover([
      backgroundColor(
        active
          ? calcBg(theme, float_of_int(depth))
          : calcBg(theme, float_of_int(depth + 1)),
      ),
      selector(
        "& ."
        ++ roundedIconButton(~leftMargin=true, theme, depth, active)
        ++ ", & ."
        ++ roundedIconButton(~leftMargin=false, theme, depth, active),
        [opacity(1.0)],
      ),
    ]),
  ]);
