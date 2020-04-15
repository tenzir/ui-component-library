import React from "react";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { okaidia } from "react-syntax-highlighter/dist/esm/styles/prism";
import { useDarkMode } from "storybook-dark-mode";
import { make as Checkbox } from "../src/Checkbox.bs.js";
import { make as Card } from "../src/Card.bs.js";
import { light, dark, normal, mono, invalid } from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";

export default {
  title: "Checkbox",
};

const margin = {
  margin: "1rem",
};

export const checkbox = () => {
  const theme = useDarkMode() ? dark : light;
  const [val, setVal] = React.useState(false);
  return (
    <>
      <div style={margin}>
        <Card theme={theme}>
          <h1>Cards</h1>
          <h3>Interface</h3>
          <SyntaxHighlighter language="reason" style={okaidia} showLineNumbers>
            {`type Card: (
    ~defaultValue: option(bool), /* Defaults to false */
    ~disabled: option(bool), /* Defaults to false */
    ~label: string,
    ~id: option(string), /* Id's have a fallback to the label, but possible collisions may occur if no id is presented */
    ~width: option(float), /* as a percentage, defaults to 100.0 */
    ~theme: option(UiTypes.theme),
    ~placeholder: option(string), /* defaults to empty string */
    ~validity: UiTypes.validation, /* defaults to UiTypes.Valid */
    ~onChange=option(React.SyntheticEvent.t->unit),
  ) => React.element;`}
          </SyntaxHighlighter>

          <h3>Preview</h3>
          <div style={margin}>
            <Checkbox
              theme={theme}
              label="We inline by default"
              width={50.0}
              variant={normal}
              defaultValue={val}
              onChange={(e) => setVal(!val)}
            />
            <Checkbox
              theme={theme}
              validity={invalid}
              width={50.0}
              label="Being invalid turns me red"
              variant={normal}
              defaultValue={val}
              onChange={(e) => setVal(!val)}
            />
            <Checkbox
              theme={theme}
              width={100.0}
              label="By being wide enough, we can also cover the whole page"
              variant={normal}
              defaultValue={val}
              onChange={(e) => setVal(!val)}
            />
            <Checkbox
              theme={theme}
              width={100.0}
              label="You can also disable me outright"
              disabled={true}
              variant={normal}
            />
          </div>
        </Card>
      </div>
    </>
  );
};
