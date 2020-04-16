open CheckboxStyles;
open UiTypes;

[@react.component]
let make =
    (
      ~defaultValue=false,
      ~disabled=false,
      ~label,
      ~id=?,
      ~width=[@reason.preserve_braces] 100.0,
      ~theme=?,
      ~placeholder="",
      ~validity=Valid,
      ~onChange=?,
    ) => {
  let identifier =
    switch (id) {
    | Some(idString) => idString
    | None => label
    };

  <div className={inputContainerStyles(~pctWidth=width, ~disabled, ())}>
    <label className={labelStyles(~theme?, ~validity, ())} htmlFor=identifier>
      <input
        disabled
        onChange={GenericHelpers.optionFn(onChange)}
        id=identifier
        type_="checkbox"
        checked=defaultValue
        placeholder
        className={checkboxStyles(~theme?, ())}
      />
      label->React.string
    </label>
  </div>;
};
