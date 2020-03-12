/*
 In some cases when pattern matching, we would want to show either a component, or nothing at all.
 The easiest way around this is to return an empty string as that won't render to anything. That
 isn't particularly declarative though, so we use this 'empty' component instead.
 */

[@react.component]
let make = () => React.string("");
