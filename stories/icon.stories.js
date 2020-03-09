import React from "react";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";

export default {
  title: "Icons"
};

const margin = {
  margin: "1rem"
};
const cardContainer = {
  width: "calc(100% - 2rem)",
  margin: "1rem",
  display: "block"
};

export const feather = () => {
  return (
    <div style={margin}>
      <h3>All Icons</h3>
      <Card>
        <p>
          We are currently using all 'feather-icons' from the 'react-icons'
          library. Find that set and all other possible icons{" "}
          <a target="_blank" href="https://feathericons.com/">
            here.
          </a>
        </p>
      </Card>
    </div>
  );
};
