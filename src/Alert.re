open AlertStyles;

[@react.component]
let make = (~variant=Primary, ~theme=?, ~message) =>
  switch (message) {
  | None => <Empty />
  | Some(message) =>
    <h4 className={messagePill(~variant, ~theme?, ())}>
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
        <span> message->React.string </span>
      </>
    </h4>
  };
