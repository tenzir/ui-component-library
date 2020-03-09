open ButtonStyles;

[@react.component]
let make =
    (
      ~disabled=false,
      ~type_="button",
      ~variant=Primary,
      ~theme=?,
      ~onClick=?,
      ~children,
    ) =>
  <button
    onClick={
      switch (onClick) {
      | Some(fn) => fn
      | None => ignore
      }
    }
    type_
    disabled
    className={button(~variant, ~theme?, ())}>
    children
  </button>;

module Group = {
  [@react.component]
  let make = (~children) => <div className=buttonGroup> children </div>;
};
