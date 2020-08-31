open UiTypes;
open InputStyles;

[@react.component]
let make =
    (
      ~_type="text",
      ~defaultValue="",
      ~className="",
      ~value=?,
      ~disabled=false,
      ~label=Unlabeled,
      ~id=?,
      ~validity=Valid,
      ~variant=Normal,
      ~width=[@reason.preserve_braces] 100.0,
      ~theme=Config.defaultTheme,
      ~placeholder="",
      ~onChange=?,
      ~onKeyDown=?,
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
         ?onKeyDown
         id=identifier
         disabled
         type_=_type
         value
         placeholder
         className={
           inputStyles(~variant, ~validity, ~theme, ()) ++ " " ++ className
         }
       />
     | None =>
       <input
         ?onBlur
         ?onChange
         ?onKeyDown
         id=identifier
         disabled
         type_=_type
         defaultValue
         placeholder
         className={
           inputStyles(~variant, ~validity, ~theme, ()) ++ " " ++ className
         }
       />
     }}
  </div>;
};
