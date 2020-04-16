import React from "react";
import { make as Input } from "../src/Input.bs.js";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { okaidia } from "react-syntax-highlighter/dist/esm/styles/prism";
import { useDarkMode } from "storybook-dark-mode";
import { make as Card } from "../src/Card.bs.js";
import {
  labeled,
  light,
  dark,
  normal,
  mono,
  valid,
  invalid,
} from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";

export default {
  title: "Input",
};

const margin = {
  margin: "1rem",
};

export const input = () => {
  const theme = useDarkMode() ? dark : light;

  return (
    <div style={margin}>
      <Card theme={theme}>
        <h1>Input</h1>

        <h3>Interface</h3>
        <p>
          As there is the option to have a label, we need to have an id so that
          we can make that clickable and link the label and the input. We can
          infer the id from the label, but this may clash. When in doubt, add an
          id.
        </p>
        <SyntaxHighlighter language="reason" style={okaidia} showLineNumbers>
          {`type Input: (
  ~_type: option(string), /* maps to "type", defaults to "text" */
  ~defaultValue: option(string), /* defaults to empty string */
  ~label: option(UiStyles.labels), /* defaults to "UiStyles.Unlabeled" */
  ~id: option(string), /* the id is used to make labels clickable. This falls back to the label */
  ~validity: option(UiStyles.validation), /* defaults to "UiStyles.Valid" */
  ~width: option(float), /* as a percentage. Defaults to "100.0" */
  ~theme: option(UiTypes.theme)
  ~placeholder: option(string) /* defaults to empty string */
  ~onChange=option(React.SyntheticEvent.t->unit),
  ~onBlur=option(React.SyntheticEvent.t->unit),
) => React.element;
`}
        </SyntaxHighlighter>

        <h3>Preview</h3>
        <h4>Custom Width</h4>
        <Input
          label={labeled("I'm a tiny input")}
          placeholder="Like for a zipcode"
          width={10.0}
          theme={theme}
          variant={normal}
        />
        <Input
          label={labeled("I'm a bit bigger")}
          placeholder="Like for a name"
          width={60.0}
          theme={theme}
          variant={normal}
        />
        <Input
          label={labeled("If the total width stays under 100%")}
          placeholder="We stay inline"
          width={30.0}
          theme={theme}
          variant={normal}
        />

        <h4>Labeled vs Unlabeled</h4>
        <Input
          label={labeled("I have a label")}
          placeholder="Check my cool label above"
          width={50.0}
          theme={theme}
          variant={normal}
        />
        <Input
          placeholder="I don't"
          width={50.0}
          theme={theme}
          variant={normal}
        />

        <h4>Normal / Mono fonts</h4>
        <Input
          label={labeled("Normal Font")}
          placeholder="Font setting will also have effect in the placeholder"
          width={50.0}
          theme={theme}
          variant={normal}
        />
        <Input
          label={labeled("Mono Font")}
          placeholder="And in the label"
          width={50.0}
          theme={theme}
          variant={mono}
        />
      </Card>
    </div>
  );
};
