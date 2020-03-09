open UiTypes;
open InputStyles;

[@react.component]
let make =
    (
      ~_type="text",
      ~defaultValue="",
      ~label=?,
      ~id=?,
      ~validity=Valid,
      ~variant=Normal,
      ~width=[@reason.preserve_braces] 100.0,
      ~theme=?,
      ~placeholder="",
      ~onChange=?,
      ~onBlur=?,
    ) => {
  let identifier =
    switch (id, label) {
    | (Some(idString), _) => idString
    | (None, Some(labelString)) => labelString
    | (None, None) => ""
    };

  let labeled =
    switch (label) {
    | Some(_) => true
    | None => false
    };

  <div className={inputContainerStyles(~pctWidth=width, ~labeled, ())}>
    {switch (label) {
     | Some(labelString) =>
       <label
         className={labelStyles(~variant, ~theme?, ())} htmlFor=identifier>
         {React.string(labelString)}
       </label>
     | None => React.string("")
     }}
    <input
      onBlur={
        switch (onBlur) {
        | Some(fn) => fn
        | None => ignore
        }
      }
      onChange={
        switch (onChange) {
        | Some(fn) => fn
        | None => ignore
        }
      }
      id=identifier
      type_=_type
      defaultValue
      placeholder
      className={inputStyles(~variant, ~validity, ~theme?, ())}
    />
  </div>;
};
