[@bs.deriving accessors]
type theme =
  | Light
  | Dark
  | TenzirBlue;

[@bs.deriving accessors]
type fontStyle =
  | Normal
  | Mono;

type componentState =
  | Base
  | Active
  | Focus
  | Hovering;

type percentOperations =
  | Add
  | Subtract;

type changeTypes =
  | Lighten
  | Darken;

[@bs.deriving accessors]
type labels =
  | Labeled(string)
  | Unlabeled;

[@bs.deriving accessors]
type validation =
  | Valid
  | Invalid;
