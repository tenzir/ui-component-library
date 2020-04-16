import React from "react";
import { make as Button, Group } from "../src/Button.bs.js";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { okaidia } from "react-syntax-highlighter/dist/esm/styles/prism";
import { useDarkMode } from "storybook-dark-mode";
import { make as Card } from "../src/Card.bs.js";
import { make as Input } from "../src/Input.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";
import icons from "./icons.js";

export default {
  title: "Icons",
};

const margin = {
  margin: "1rem",
};

const inputContainer = {
  marginBottom: "2rem",
};

const icon = {
  container: {
    textAlign: "center",
    width: "20%",
    display: "inline-block",
    marginBottom: "2rem",
  },
  title: {
    display: "block",
    margin: "0.5rem",
  },
  icon: {
    display: "inline-block",
  },
};

const cardContainer = {
  width: "calc(100% - 2rem)",
  margin: "1rem",
  display: "block",
};

const lCase = (str) => str.toLowerCase();

export const feather = () => {
  const [filteredIcons, setFilteredIcons] = React.useState(icons);
  const [filter, setFilter] = React.useState("");
  const theme = useDarkMode() ? dark : light;
  React.useEffect(() => {
    const newSet = icons.filter(({ name }) =>
      lCase(name).includes(lCase(filter))
    );
    setFilteredIcons(newSet);
  }, [filter]);

  return (
    <div style={margin}>
      <Card theme={theme}>
        <h1>Icons</h1>
        <h3>Interface</h3>
        <SyntaxHighlighter language="reason" style={okaidia} showLineNumbers>
          {`type Icon: (
  ~className:option(string),
  ~color: option(string),
  ~size: option(int),
  ~style: option(ReactDomRe.Style.t),
)=> React.element;`}
        </SyntaxHighlighter>
        <h3>Preview</h3>
        <p>
          We built a script that takes some (or all) icons from the
          'react-icons', and generates ReasonML type bindings for them. We are
          currently using all 'feather-icons' from the 'react-icons' library.
          The cool part is that even though the file with the bindings is huge,
          it will be removed at compile time since they're simply type bindings.
          Check out the icons below.
        </p>

        <div style={inputContainer}>
          <Input
            theme={theme}
            defaultValue={filter}
            onChange={(e) => setFilter(e.target.value)}
            placeholder="Search"
          />
        </div>

        {filteredIcons.map(({ name, component }) => (
          <div style={icon.container}>
            <span style={icon.icon}>{component}</span>
            <h5 style={icon.title}>{name}</h5>
          </div>
        ))}
      </Card>
    </div>
  );
};
