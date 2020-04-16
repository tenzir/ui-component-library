import React from "react";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { okaidia } from "react-syntax-highlighter/dist/esm/styles/prism";
import { useDarkMode } from "storybook-dark-mode";
import { make as Loader } from "../src/Loader.bs.js";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
export default {
  title: "Loader",
};

const margin = {
  margin: "1rem",
};
export const Loaders = () => {
  const theme = useDarkMode() ? dark : light;
  return (
    <>
      <div style={margin}>
        <Card theme={theme}>
          <h1>Loader</h1>
          <h3>Interface</h3>
          <SyntaxHighlighter language="reason" style={okaidia} showLineNumbers>
            {`type Loader: (
  ~className: option(string), /* Defaults to empty string */
  ~theme: option(UiTypes.theme)
) => React.element;
`}
          </SyntaxHighlighter>

          <h3>Preview</h3>
          <Card depth={1} theme={theme}>
            <Loader theme={theme} />
          </Card>
        </Card>
      </div>
    </>
  );
};
