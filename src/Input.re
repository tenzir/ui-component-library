open UiTypes;
open InputStyles;

[@react.component]
let make =
    (
      ~_type="text",
      ~defaultValue="",
      ~value=?,
      ~disabled=false,
      ~label=Unlabeled,
      ~id=?,
      ~validity=Valid,
      ~variant=Normal,
      ~width=[@reason.preserve_braces] 100.0,
      ~theme=?,
      ~placeholder="",
      ~onChange=?,
      ~onBlur=?,
    ) => {
  let identifier = GenericHelpers.genIdentifier(id, label);

  <div className={inputContainerStyles(~pctWidth=width, ~label, ())}>
    <Label label identifier variant theme />
    {switch (value) {
     | Some(value) =>
       <input
         ?onBlur
         ?onChange
         id=identifier
         disabled
         type_=_type
         value
         placeholder
         className={inputStyles(~variant, ~validity, ~theme?, ())}
       />
     | None =>
       <input
         ?onBlur
         ?onChange
         id=identifier
         disabled
         type_=_type
         defaultValue
         placeholder
         className={inputStyles(~variant, ~validity, ~theme?, ())}
       />
     }}
  </div>;
};
