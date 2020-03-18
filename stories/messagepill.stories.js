import React from "react";
import { make as MessagePill } from "../src/MessagePill.bs.js";
import { FiActivity as Activity } from "react-icons/fi";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import {
  primary,
  secondary,
  success,
  warning,
  danger
} from "../src/MessagePillStyles.bs";

export default {
  title: "Message Pill"
};

const margin = {
  margin: "1rem"
};
export const MessagePills = () => {
  return (
    <>
      <div style={margin}>
        <h3>Light Background</h3>
        <div style={margin}>
          <Card theme={light}>
            <span style={margin}>
              <MessagePill
                message="This is an info message"
                variant={primary}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a toned down info message"
                variant={secondary}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a success message"
                variant={success}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a warning message"
                variant={warning}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a danger message"
                variant={danger}
              />
            </span>
          </Card>
        </div>
      </div>
      <div style={margin}>
        <h3>Dark Background</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <MessagePill
                message="This is an info message"
                variant={primary}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a toned down info message"
                variant={secondary}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a success message"
                variant={success}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a warning message"
                variant={warning}
              />
            </span>
            <span style={margin}>
              <MessagePill
                message="This is a danger message"
                variant={danger}
              />
            </span>
          </Card>
        </div>
      </div>
    </>
  );
};
