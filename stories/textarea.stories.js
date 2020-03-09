import React from "react";
import { make as Textarea } from "../src/Textarea.bs.js";
import { make as Card } from "../src/Card.bs.js";
import { light, dark, normal, mono, valid, invalid } from "../src/UiTypes.bs";
import { horizontal, vertical, both } from "../src/TextareaStyles.bs.js";
import { tiny, huge } from "../src/CardStyles.bs";

export default {
  title: "Textarea"
};

const margin = {
  margin: "1rem"
};

export const textarea = () => {
  return (
    <>
      <div style={margin}>
        <h3>Full Width</h3>
        <div style={margin}>
          <Card theme={dark}>
            <Textarea theme={dark} variant={normal} placeholder="test" />
          </Card>
          <Card theme={dark}>
            <Textarea
              validity={invalid}
              theme={dark}
              variant={normal}
              placeholder="test"
            />
          </Card>
        </div>
        <div style={margin}>
          <Card theme={light}>
            <Textarea theme={light} variant={normal} placeholder="test" />
          </Card>
        </div>
      </div>
      <div style={margin}>
        <h3>Resizeable</h3>
        <div style={margin}>
          <Card theme={dark}>
            <Textarea
              theme={dark}
              variant={normal}
              resize={both}
              placeholder="both"
            />
          </Card>
        </div>
        <div style={margin}>
          <Card theme={light}>
            <Textarea
              theme={dark}
              variant={normal}
              resize={horizontal}
              placeholder="horizontal"
            />
          </Card>
        </div>
        <div style={margin}>
          <Card theme={light}>
            <Textarea
              theme={dark}
              variant={normal}
              resize={horizontal}
              placeholder="horizontal"
            />
          </Card>
        </div>
      </div>
    </>
  );
};

export const withLabel = () => {
  return (
    <div style={margin}>
      <h3>Labeled</h3>
      <div style={margin}>
        <Card theme={dark} spacing={tiny}>
          <div style={margin}>
            <Textarea
              label="Label Dark 01"
              width={50.0}
              theme={dark}
              variant={normal}
            />
            <Textarea
              label="Label Dark 02"
              width={50.0}
              theme={dark}
              variant={normal}
            />
          </div>
        </Card>
      </div>
      <div style={margin}>
        <Card theme={light} spacing={tiny}>
          <div style={margin}>
            <Textarea
              label="Label Light 01"
              width={50.0}
              theme={light}
              variant={normal}
            />
            <Textarea
              label="Label Light 02"
              width={50.0}
              theme={light}
              variant={normal}
            />
          </div>
        </Card>
      </div>
    </div>
  );
};

export const normalAndMono = () => {
  return (
    <div style={margin}>
      <h3>Normal Font</h3>
      <div style={margin}>
        <Card theme={dark} spacing={tiny}>
          <div style={margin}>
            <Textarea
              label="Normal Label Dark 01"
              width={50.0}
              theme={dark}
              variant={normal}
            />
            <Textarea
              label="Normal Label Dark 02"
              width={50.0}
              theme={dark}
              variant={normal}
            />
          </div>
        </Card>
      </div>

      <div style={margin}>
        <Card theme={light} spacing={tiny}>
          <div style={margin}>
            <Textarea
              label="Normal Label Light 01"
              width={50.0}
              theme={light}
              variant={normal}
            />
            <Textarea
              label="Normal Label Light 02"
              width={50.0}
              theme={light}
              variant={normal}
            />
          </div>
        </Card>
      </div>

      <h3>Monospaced Font</h3>
      <div style={margin}>
        <Card theme={dark} spacing={tiny}>
          <div style={margin}>
            <Textarea
              label="Mono Label Dark 01"
              width={50.0}
              theme={dark}
              variant={mono}
            />
            <Textarea
              label="Mono Label Dark 02"
              width={50.0}
              theme={dark}
              variant={mono}
            />
          </div>
        </Card>
      </div>

      <div style={margin}>
        <Card theme={light} spacing={tiny}>
          <div style={margin}>
            <Textarea
              label="Mono Label Light 01"
              width={50.0}
              theme={light}
              variant={mono}
            />
            <Textarea
              label="Mono Label Light 02"
              width={50.0}
              theme={light}
              variant={mono}
            />
          </div>
        </Card>
      </div>
    </div>
  );
};
