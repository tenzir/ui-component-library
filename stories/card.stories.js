import React from "react";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";

<Card theme={light}>Light</Card>;
export default {
  title: "Card"
};

const cardContainer = {
  width: "40%",
  height: "500px",
  margin: "1rem",
  display: "inline-block"
};

const smallCardContainer = {
  ...cardContainer,
  height: "200px"
};

const nestedCardContainer = {
  ...cardContainer,
  height: "unset"
};

const margin = {
  margin: "1rem"
};

export const simpleCard = () => {
  return (
    <div style={margin}>
      <h3>Theming</h3>
      <div style={cardContainer}>
        <Card theme={light}>Light</Card>
      </div>
      <div style={cardContainer}>
        <Card theme={dark}>Dark</Card>
      </div>
      <h3>Spacing</h3>
      <div style={smallCardContainer}>
        <Card theme={dark} spacing={tiny}>
          Tiny
        </Card>
      </div>
      <div style={smallCardContainer}>
        <Card theme={dark}> Normal </Card>
      </div>
      <div style={smallCardContainer}>
        <Card theme={dark} spacing={huge}>
          Huge
        </Card>
      </div>
    </div>
  );
};

export const nestedCards = () => {
  return (
    <div style={margin}>
      <h3>Nested Card</h3>
      <div style={nestedCardContainer}>
        <Card theme={dark}>
          <p>Depth = 0</p>
          <Card theme={dark} depth={1}>
            <p>Depth = 1</p>
            <Card theme={dark} depth={2}>
              <p>Depth = 2</p>
            </Card>
          </Card>
        </Card>
      </div>
      <div style={nestedCardContainer}>
        <Card theme={light}>
          <p>Depth = 0</p>
          <Card theme={light} depth={1}>
            <p>Depth = 1</p>
            <Card theme={light} depth={2}>
              <p>Depth = 2</p>
            </Card>
          </Card>
        </Card>
      </div>
    </div>
  );
};
