[@react.component]
let make =
    (
      ~disabled=false,
      ~type_="button",
      ~variant=ButtonStyles.Primary,
      ~theme=?,
      ~icon=?,
      ~iconPosition=ButtonStyles.Left,
      ~onClick=?,
      ~className="",
      ~children,
    ) =>
  <button
    onClick={GenericHelpers.optionFn(onClick)}
    type_
    disabled
    className={
      ButtonStyles.button(~variant, ~theme?, icon, iconPosition, ())
      ++ " "
      ++ className
    }>
    {switch (icon) {
     | Some(icon) =>
       <span className={ButtonStyles.icon(iconPosition)}> icon </span>
     | None => <Empty />
     }}
    <span> children </span>
  </button>;

module Group = {
  [@react.component]
  let make = (~children, ~className="") =>
    <div className={ButtonStyles.buttonGroup ++ "  " ++ className}>
      children
    </div>;
};
