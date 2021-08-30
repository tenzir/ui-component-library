module Function = {
  let id = x => x;
  let apply = (x, fn) => fn(x);
  let applyF = (fn, x) => fn(x);
  let const = (x, _) => x;
  let compose = (f, g, x) => f(g(x));
  let pipe = (g, f, x) => f(g(x));

  module Infix = {
    let (>>) = pipe;
    let (<<) = compose;
  };
};

module Jsx = {
  open Webapi;
  open Function.Infix;
  let focus = (ref: ReactDOM.Ref.currentDomRef) =>
    ref.current
    ->Js.Nullable.toOption
    ->Belt.Option.map(
        Dom.Element.unsafeAsHtmlElement >> Dom.HtmlElement.focus,
      )
    ->ignore;

  module Infix = {
    let (<&&>) = (a, b) => a ? b : React.null;
  };
};

module Event = {
  let getValueFromEvent = event => ReactEvent.Synthetic.target(event)##value;
  module Keyboard = {
    external toKeyboardEvent: 'a => Webapi.Dom.KeyboardEvent.t = "%identity";

    let keyWas = (inputKey, e) =>
      e
      |> toKeyboardEvent
      |> Webapi.Dom.KeyboardEvent.key
      |> (eventKey => eventKey === inputKey);
  };
};
