import React from "react";
import { make as Checkbox } from "../src/Checkbox.bs.js";
import { make as Card } from "../src/Card.bs.js";
import { light, dark, normal, mono, invalid } from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";

export default {
  title: "Checkbox"
};

const margin = {
  margin: "1rem"
};

export const checkbox = () => {
  return (
    <>
      <div style={margin}>
        <h3>Full Width</h3>
        <div style={margin}>
          <Card theme={dark}>
            <Checkbox
              theme={dark}
              label="Some Label"
              variant={normal}
              defaultValue={false}
            />
            <Checkbox
              theme={dark}
              validity={invalid}
              label="Some Label"
              variant={normal}
              defaultValue={false}
            />
          </Card>
        </div>
        <div style={margin}>
          <Card theme={light}>
            <Checkbox
              theme={light}
              label="Some Label"
              variant={normal}
              defaultValue={true}
            />
          </Card>
        </div>
      </div>
    </>
  );
};
