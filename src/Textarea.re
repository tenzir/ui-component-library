open UiTypes;
open TextareaStyles;

[@react.component]
let make =
    (
      ~defaultValue="",
      ~label=?,
      ~id=?,
      ~variant=Normal,
      ~validity=Valid,
      ~width=[@reason.preserve_braces] 100.0,
      ~resize=NoResize,
      ~theme=?,
      ~placeholder="",
      ~onChange=?,
      ~onBlur=?,
      ~styles=[],
      ~rows=4,
      ~cols=50,
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

  <div className={textareaContainerStyles(~pctWidth=width, ~labeled, ())}>
    {switch (label) {
     | Some(labelString) =>
       <label
         className={labelStyles(~variant, ~theme?, ())} htmlFor=identifier>
         {React.string(labelString)}
       </label>
     | None => React.string("")
     }}
    <textarea
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
      rows
      cols
      defaultValue
      placeholder
      className={textareaStyles(~variant, ~theme?, ~resize, ~validity,  ~styles, ())}
    />
  </div>;
};
