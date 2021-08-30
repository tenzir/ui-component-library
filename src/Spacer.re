module Vertical = {
  [@react.component]
  let make = (~amount: Css.Types.Length.t) => {
    <div className={Css.style([Css.height(amount)])} />;
  };
};
module Horizontal = {
  [@react.component]
  let make = (~amount: Css.Types.Length.t) => {
    <div className={Css.style([Css.width(amount)])} />;
  };
};
