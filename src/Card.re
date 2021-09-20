open CardStyles;

[@react.component]
let make =
    (
      ~onMouseOver=?,
      ~onMouseOut=?,
      ~spacing=Normal,
      ~theme=Config.defaultTheme,
      ~depth=1,
      ~className="",
      ~header=?,
      ~footer=?,
      ~children=<Empty />,
    ) => {
  <div
    ?onMouseOver
    ?onMouseOut
    className={className ++ " " ++ card(~spacing, ~theme, ~depth, ()) ++ "  "}>
    {header->Belt.Option.mapWithDefault(<Empty />, header =>
       <div className={cardHeader(~theme, ~depth, ())}> header </div>
     )}
    <div
      className={cardContent(
        ~hasHeader=header->Belt.Option.isSome,
        ~hasFooter=footer->Belt.Option.isSome,
      )}>
      children
    </div>
    {footer->Belt.Option.mapWithDefault(<Empty />, footer =>
       <div className={cardFooter(~theme, ~depth, ())}> footer </div>
     )}
  </div>;
};

module Tabbed = {
  [@react.component]
  let make =
      (
        ~onMouseOver=?,
        ~onMouseOut=?,
        ~spacing=Normal,
        ~theme=Config.defaultTheme,
        ~depth=1,
        ~className="",
        ~footer=?,
        ~children=<Empty />,
        ~activeTabId: string,
        ~tabs: array(Tabs.t),
        ~addButtonText,
        ~onAdd=?,
        ~onMove=?,
        ~onOpen=?,
        ~onClose=?,
        ~onDuplicate=?,
        ~onRename=?,
      ) => {
    <div
      ?onMouseOver
      ?onMouseOut
      className={
        className ++ " " ++ card(~spacing, ~theme, ~depth, ()) ++ "  "
      }>
      <Tabs
        standalone=false
        tabs
        activeTabId
        theme
        depth
        ?addButtonText
        ?onAdd
        ?onMove
        ?onOpen
        ?onClose
        ?onDuplicate
        ?onRename
      />
      <div
        className={cardContent(
          ~hasHeader=true,
          ~hasFooter=footer->Belt.Option.isSome,
        )}>
        children
      </div>
      {footer->Belt.Option.mapWithDefault(<Empty />, footer =>
         <div className={cardFooter(~theme, ~depth, ())}> footer </div>
       )}
    </div>;
  };
};
