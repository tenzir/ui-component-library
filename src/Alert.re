open AlertStyles;

[@react.component]
let make =
    (~children=?, ~variant=Primary, ~theme=?, ~className="", ~message=?) =>
  <h4 className={messagePill(~variant, ~theme?, ()) ++ " " ++ className}>
    <>
      <span className=icon>
        {switch (variant) {
         | Primary
         | Secondary => <Icons.Info />
         | Success => <Icons.CheckCircle />
         | Warning => <Icons.AlertCircle />
         | Danger => <Icons.XCircle />
         }}
      </span>
      {switch (message, children) {
       | (Some(message), Some(children)) =>
         <> <span> message->React.string </span> children </>
       | (Some(message), None) => <span> message->React.string </span>
       | (None, Some(children)) => children
       | (None, None) => <Empty />
       }}
    </>
  </h4>;
