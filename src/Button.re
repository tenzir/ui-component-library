[@react.component]
let make =
    (
      ~disabled=false,
      ~type_="button",
      ~variant=ButtonStyles.Primary,
      ~size=ButtonStyles.Small,
      ~theme=?,
      ~icon=?,
      ~iconPosition=ButtonStyles.Left,
      ~onClick=?,
      ~className="",
      ~children,
    ) =>
  <button
    ?onClick
    type_
    disabled
    className={
      ButtonStyles.button(~variant, ~theme?, size, icon, iconPosition, ())
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
