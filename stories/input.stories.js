import React from "react";
import { make as Input } from "../src/Input.bs.js";
import { make as Card } from "../src/Card.bs.js";
import {
  labeled,
  light,
  dark,
  normal,
  mono,
  valid,
  invalid
} from "../src/UiTypes.bs";
import { tiny, huge } from "../src/CardStyles.bs";

export default {
  title: "Input"
};

const margin = {
  margin: "1rem"
};

export const input = () => {
  return (
    <>
      <div style={margin}>
        <h3>Full Width</h3>
        <div style={margin}>
          <Card theme={dark}>
            <Input theme={dark} variant={normal} placeholder="test" />
          </Card>
          <Card theme={dark}>
            <Input
              validity={invalid}
              theme={dark}
              variant={normal}
              placeholder="test"
            />
          </Card>
        </div>
        <div style={margin}>
          <Card theme={light}>
            <Input theme={light} variant={normal} placeholder="test" />
          </Card>
        </div>
      </div>

      <div style={margin}>
        <h3>Inline Width</h3>
        <div style={margin}>
          <Card theme={dark}>
            <div>
              <h5>50%</h5>
              <Input
                width={50.0}
                theme={dark}
                variant={normal}
                placeholder="test"
              />
              <Input
                width={50.0}
                theme={dark}
                variant={normal}
                placeholder="test"
              />
            </div>

            <div>
              <h5>33.3%</h5>
              <Input
                width={33.3}
                theme={dark}
                variant={normal}
                placeholder="test"
              />
              <Input
                width={33.3}
                theme={dark}
                variant={normal}
                placeholder="test"
              />
              <Input
                width={33.3}
                theme={dark}
                variant={normal}
                placeholder="test"
              />
            </div>
          </Card>
        </div>
        <div style={margin}>
          <Card theme={light}>
            <div>
              <h5>50%</h5>
              <Input
                width={50.0}
                theme={light}
                variant={normal}
                placeholder="test"
              />
              <Input
                width={50.0}
                theme={light}
                variant={normal}
                placeholder="test"
              />
            </div>

            <div>
              <h5>33.3%</h5>
              <Input
                width={33.3}
                theme={light}
                variant={normal}
                placeholder="test"
              />
              <Input
                width={33.3}
                theme={light}
                variant={normal}
                placeholder="test"
              />
              <Input
                width={33.3}
                theme={light}
                variant={normal}
                placeholder="test"
              />
            </div>
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
            <Input
              label={labeled("Label Dark 01")}
              width={50.0}
              theme={dark}
              variant={normal}
            />
            <Input
              label={labeled("Label Dark 02")}
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
            <Input
              label={labeled("Label Light 01")}
              width={50.0}
              theme={light}
              variant={normal}
            />
            <Input
              label={labeled("Label Light 02")}
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
            <Input
              label={labeled("Normal Label Dark 01")}
              width={50.0}
              theme={dark}
              variant={normal}
            />
            <Input
              label={labeled("Normal Label Dark 02")}
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
            <Input
              label={labeled("Normal Label Light 01")}
              width={50.0}
              theme={light}
              variant={normal}
            />
            <Input
              label={labeled("Normal Label Light 02")}
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
            <Input
              label={labeled("Mono Label Dark 01")}
              width={50.0}
              theme={dark}
              variant={mono}
            />
            <Input
              label={labeled("Mono Label Dark 02")}
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
            <Input
              label={labeled("Mono Label Light 01")}
              width={50.0}
              theme={light}
              variant={mono}
            />
            <Input
              label={labeled("Mono Label Light 02")}
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
