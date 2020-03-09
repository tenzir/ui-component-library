import React from "react";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";

export default {
  title: "Typography"
};

const margin = {
  margin: "1rem"
};

export const typograph = () => {
  return (
    <>
      <div style={margin}>
        <h3>Light Background</h3>
        <div style={margin}>
          <Card theme={light}>
            <h1>This is an h1 title</h1>
            <h2>This is an h2 title</h2>
            <h3>This is an h3 title</h3>
            <h4>This is an h4 title</h4>
            <h5>This is an h5 title</h5>
            <h6>This is an h6 title</h6>
            <p>Here is the paragraph text</p>
          </Card>
        </div>

        <h3>Dark Background</h3>
        <div style={margin}>
          <Card theme={dark}>
            <h1>This is an h1 title</h1>
            <h2>This is an h2 title</h2>
            <h3>This is an h3 title</h3>
            <h4>This is an h4 title</h4>
            <h5>This is an h5 title</h5>
            <h6>This is an h6 title</h6>
            <p>Here is the paragraph text</p>
          </Card>
        </div>
      </div>
    </>
  );
};
