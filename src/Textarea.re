open UiTypes;
open TextareaStyles;

[@react.component]
let make =
    (
      ~defaultValue="",
      ~value=?,
      ~label=Unlabeled,
      ~disabled=false,
      ~id=?,
      ~variant=Normal,
      ~validity=Valid,
      ~width=[@reason.preserve_braces] 100.0,
      ~resize=NoResize,
      ~theme=Config.defaultTheme,
      ~placeholder="",
      ~onChange=?,
      ~onBlur=?,
      ~styles=[],
      ~rows=4,
      ~cols=50,
    ) => {
  let identifier = GenericHelpers.genIdentifier(id, label);

  <div className={textareaContainerStyles(~pctWidth=width, ~label, ())}>
    <Label label identifier variant theme />
    {switch (value) {
     | Some(value) =>
       <textarea
         ?onBlur
         ?onChange
         id=identifier
         rows
         disabled
         cols
         value
         placeholder
         className={textareaStyles(
           ~variant,
           ~theme,
           ~resize,
           ~validity,
           ~styles,
           (),
         )}
       />
     | None =>
       <textarea
         ?onBlur
         ?onChange
         id=identifier
         disabled
         rows
         cols
         defaultValue
         placeholder
         className={textareaStyles(
           ~variant,
           ~theme,
           ~resize,
           ~validity,
           ~styles,
           (),
         )}
       />
     }}
  </div>;
};
