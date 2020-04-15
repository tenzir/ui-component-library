import React from "react";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { make as Button, Group } from "../src/Button.bs.js";
import { okaidia } from "react-syntax-highlighter/dist/esm/styles/prism";
import { useDarkMode } from "storybook-dark-mode";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import { tiny, large, huge } from "../src/CardStyles.bs";

<Card theme={light}>Light</Card>;
export default {
  title: "Card",
};

const cardContainer = {
  width: "20%",
  height: "500px",
  margin: "1rem",
  display: "inline-block",
};

const smallCardContainer = {
  ...cardContainer,
  height: "200px",
};

const nestedCardContainer = {
  ...cardContainer,
  width: "40%",
  height: "unset",
};

const headerStyles = {
  padding: "0 1.5rem",
};

const footerStyles = {
  width: "100%",
  padding: "0 0.5rem",
  display: "flex",
  justifyContent: "flex-end",
};

const margin = {
  margin: "1rem",
};

export const card = () => {
  const theme = useDarkMode() ? dark : light;
  return (
    <div style={margin}>
      <Card theme={theme}>
        <h1>Cards</h1>
        <h3>Interface</h3>
        <SyntaxHighlighter language="reason" style={okaidia} showLineNumbers>
          {`type Card: (
  ~spacing: option(CardStyles.spacing),
  ~theme: option(UiTypes.theme),
  ~depth: option(int),
  ~header: option(React.Element),
  ~footer: option(React.Element),
  ~children: option(React.Element),
  ~className: option(string),
  ~styles: option(array(Css.rule), /* These get concatenated with the existing styles array */
) => React.element;`}
        </SyntaxHighlighter>

        <h3>Preview</h3>
        <h4>Padding</h4>
        <div style={smallCardContainer}>
          <Card spacing={tiny} depth={1} theme={theme}>
            <h2>Tiny Padding</h2>
          </Card>
        </div>
        <div style={smallCardContainer}>
          <Card depth={1} theme={theme}>
            <h2>Normal Padding</h2>
          </Card>
        </div>
        <div style={smallCardContainer}>
          <Card spacing={large} depth={1} theme={theme}>
            <h2>Large Padding</h2>
          </Card>
        </div>
        <div style={smallCardContainer}>
          <Card spacing={huge} depth={1} theme={theme}>
            <h2>Huge Padding</h2>
          </Card>
        </div>

        <h4>Nesting</h4>
        <p>
          Using the 'Depth' Parameter, one can stack multiple cards. The
          stacking here actuall starts with the background, which is one of our
          cards.
        </p>
        <div style={nestedCardContainer}>
          <Card spacing={tiny} depth={1} theme={theme}>
            <h2>No. 1</h2>
            <Card spacing={tiny} depth={2} theme={theme}>
              <h2>No. 2</h2>
              <Card spacing={tiny} depth={3} theme={theme}>
                <h2>Cards all the way down</h2>
              </Card>
            </Card>
          </Card>
        </div>

        <h4>Header / Footer</h4>
        <p>
          One can pass in a header and footer component. To be as flexible as
          possible here, we do not implement any spacing options here. The
          component passed into the header should place itself according to the
          space available
        </p>
        <div style={nestedCardContainer}>
          <Card
            header={
              <div style={headerStyles}>
                <h3>Some Header</h3>
              </div>
            }
            footer={
              <div style={headerStyles}>
                <h3>Some Header</h3>
              </div>
            }
            spacing={tiny}
            depth={1}
            theme={theme}
          >
            <h2>No. 1</h2>
            <p>Some text inside here still</p>
          </Card>
        </div>
        <div style={nestedCardContainer}>
          <Card
            header={
              <div style={headerStyles}>
                <h3>Login</h3>
              </div>
            }
            footer={
              <div style={footerStyles}>
                <Button>Login</Button>
              </div>
            }
            spacing={tiny}
            depth={1}
            theme={theme}
          >
            <p>Some forms could go here...</p>
          </Card>
        </div>
      </Card>
    </div>
  );
};
