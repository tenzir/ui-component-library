open CardStyles;

[@react.component]
let make = (
  ~spacing=Normal, 
  ~theme=?, 
  ~depth=0, 
  ~children=?, 
  ~styles=?) =>
  <div className={card(~spacing, ~theme?, ~depth, ~styles, ())}>
  { Belt.Option.getWithDefault(children, <Empty />) }
  </div>;
