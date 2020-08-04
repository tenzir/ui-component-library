open CardStyles;

[@react.component]
let make =
    (
      ~spacing=Normal,
      ~theme=?,
      ~depth=1,
      ~className="",
      ~header=?,
      ~footer=?,
      ~children=<Empty />,
      ~styles=?,
    ) => {
  switch (styles) {
  | Some(_) =>
    Js.log(
      "*Deprecated* - Adding styles this way will be removed in favour of a custom classname",
    )
  | None => ()
  };

  <div
    className={
      className ++ " " ++ card(~spacing, ~theme?, ~depth, ~styles, ()) ++ "  "
    }>
    {header->Belt.Option.mapWithDefault(<Empty />, header =>
       <div className={cardHeader(~theme?, ~depth, ())}> header </div>
     )}
    <div
      className={cardContent(
        ~hasHeader=header->Belt.Option.isSome,
        ~hasFooter=footer->Belt.Option.isSome,
      )}>
      children
    </div>
    {footer->Belt.Option.mapWithDefault(<Empty />, footer =>
       <div className={cardFooter(~theme?, ~depth, ())}> footer </div>
     )}
  </div>;
};
