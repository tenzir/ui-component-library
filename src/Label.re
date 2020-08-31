open UiTypes;
open InputStyles;

[@react.component]
let make =
    (
      ~label=Unlabeled,
      ~identifier,
      ~variant=Normal,
      ~theme=Config.defaultTheme,
    ) =>
  switch (label) {
  | Labeled(labelString) =>
    <label className={labelStyles(~variant, ~theme, ())} htmlFor=identifier>
      {React.string(labelString)}
    </label>
  | Unlabeled => <Empty />
  };
