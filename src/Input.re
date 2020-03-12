open UiTypes;
open InputStyles;

[@react.component]
let make =
    (
      ~_type="text",
      ~defaultValue="",
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
    <input
      onBlur={GenericHelpers.optionFn(onBlur)}
      onChange={GenericHelpers.optionFn(onChange)}
      id=identifier
      type_=_type
      defaultValue
      placeholder
      className={inputStyles(~variant, ~validity, ~theme?, ())}
    />
  </div>;
};
