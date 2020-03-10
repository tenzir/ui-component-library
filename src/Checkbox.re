open CheckboxStyles;
open UiTypes;

[@react.component]
let make =
    (
      ~defaultValue=false,
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

  <div className={inputContainerStyles(~pctWidth=width, ())}>
    <label className={labelStyles(~theme?, ~validity, ())} htmlFor=identifier>
      <input
        onChange={
          switch (onChange) {
          | Some(fn) => fn
          | None => ignore
          }
        }
        id=identifier
        type_="checkbox"
        checked=defaultValue
        placeholder
        className={inputStyles(~theme?, ())}
      />
      label->React.string
    </label>
  </div>;
};
