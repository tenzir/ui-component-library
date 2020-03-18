import React from "react";
import { make as Loader } from "../src/Loader.bs.js";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
export default {
  title: "Loader"
};

const margin = {
  margin: "1rem"
};
export const Loaders = () => {
  return (
    <>
      <div style={margin}>
        <h3>Light Background</h3>
        <div style={margin}>
          <Card theme={light}>
            <Loader theme={light} />
          </Card>
        </div>
      </div>
      <div style={margin}>
        <h3>Dark Background</h3>
        <div style={margin}>
          <Card theme={dark}>
            <Loader theme={dark} />
          </Card>
        </div>
      </div>
    </>
  );
};
