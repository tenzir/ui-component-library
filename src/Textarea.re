open UiTypes;
open TextareaStyles;

[@react.component]
let make =
    (
      ~defaultValue="",
      ~label=Unlabeled,
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
  let identifier = GenericHelpers.genIdentifier(id, label);

  <div className={textareaContainerStyles(~pctWidth=width, ~label, ())}>
    <Label label identifier variant theme />
    <textarea
      onBlur={GenericHelpers.optionFn(onBlur)}
      onChange={GenericHelpers.optionFn(onChange)}
      id=identifier
      rows
      cols
      defaultValue
      placeholder
      className={textareaStyles(
        ~variant,
        ~theme?,
        ~resize,
        ~validity,
        ~styles,
        (),
      )}
    />
  </div>;
};
