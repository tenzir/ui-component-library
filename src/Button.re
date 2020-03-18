[@react.component]
let make =
    (
      ~disabled=false,
      ~type_="button",
      ~variant=ButtonStyles.Primary,
      ~theme=?,
      ~icon=?,
      ~onClick=?,
      ~children,
    ) =>
  <button
    onClick={GenericHelpers.optionFn(onClick)}
    type_
    disabled
    className={ButtonStyles.button(~variant, ~theme?, icon, ())}>
    {switch (icon) {
     | Some(icon) => <span className=ButtonStyles.icon> icon </span>
     | None => <Empty />
     }}
    children
  </button>;

module Group = {
  [@react.component]
  let make = (~children) =>
    <div className=ButtonStyles.buttonGroup> children </div>;
};
