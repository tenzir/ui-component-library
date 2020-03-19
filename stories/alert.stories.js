import React from "react";
import { make as Alert } from "../src/Alert.bs.js";
import { FiActivity as Activity } from "react-icons/fi";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import {
  primary,
  secondary,
  success,
  warning,
  danger
} from "../src/AlertStyles.bs";

export default {
  title: "Alert"
};

const margin = {
  margin: "1rem"
};
export const Alerts = () => {
  return (
    <>
      <div style={margin}>
        <h3>Light Background</h3>
        <div style={margin}>
          <Card theme={light}>
            <span style={margin}>
              <Alert message="This is an info alert" variant={primary} />
            </span>
            <span style={margin}>
              <Alert
                message="This is a toned down info alert"
                variant={secondary}
              />
            </span>
            <span style={margin}>
              <Alert message="This is a success alert" variant={success} />
            </span>
            <span style={margin}>
              <Alert message="This is a warning alert" variant={warning} />
            </span>
            <span style={margin}>
              <Alert message="This is a danger alert" variant={danger} />
            </span>
          </Card>
        </div>
      </div>
      <div style={margin}>
        <h3>Dark Background</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <Alert message="This is an info alert" variant={primary} />
            </span>
            <span style={margin}>
              <Alert
                message="This is a toned down info alert"
                variant={secondary}
              />
            </span>
            <span style={margin}>
              <Alert message="This is a success alert" variant={success} />
            </span>
            <span style={margin}>
              <Alert message="This is a warning alert" variant={warning} />
            </span>
            <span style={margin}>
              <Alert message="This is a danger alert" variant={danger} />
            </span>
          </Card>
        </div>
      </div>
    </>
  );
};
