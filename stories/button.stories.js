import React from "react";
import { make as Button, Group } from "../src/Button.bs.js";
import { FiActivity as Activity } from "react-icons/fi";
import { make as Card } from "../src/Card.bs.js";
import { light, dark } from "../src/UiTypes.bs";
import {
  primary,
  secondary,
  success,
  warning,
  danger
} from "../src/ButtonStyles.bs";

const ButtonGroup = Group.make;
export default {
  title: "Button"
};

const margin = {
  margin: "1rem"
};
export const Buttons = () => {
  return (
    <>
      <div style={margin}>
        <h3>Light Background</h3>
        <div style={margin}>
          <Card theme={light}>
            <span style={margin}>
              <Button theme={light} variant={primary}>
                Primary
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={secondary}>
                Secondary
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={success}>
                Success
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={warning}>
                Warning
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={danger}>
                Danger
              </Button>
            </span>
          </Card>
        </div>
      </div>
      <div style={margin}>
        <h3>Dark Background</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <Button theme={light} variant={primary}>
                Primary
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={secondary}>
                Secondary
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={success}>
                Success
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={warning}>
                Warning
              </Button>
            </span>
            <span style={margin}>
              <Button theme={light} variant={danger}>
                Danger
              </Button>
            </span>
          </Card>
        </div>
      </div>

      <div style={margin}>
        <h3>With Icons</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <Button icon={<Activity />} theme={light} variant={primary}>
                Primary
              </Button>
            </span>
            <span style={margin}>
              <Button icon={<Activity />} theme={light} variant={secondary}>
                Secondary
              </Button>
            </span>
            <span style={margin}>
              <Button icon={<Activity />} theme={light} variant={success}>
                Success
              </Button>
            </span>
            <span style={margin}>
              <Button icon={<Activity />} theme={light} variant={warning}>
                Warning
              </Button>
            </span>
            <span style={margin}>
              <Button icon={<Activity />} theme={light} variant={danger}>
                Danger
              </Button>
            </span>
          </Card>
        </div>
      </div>

      <div style={margin}>
        <h3>Disable</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <Button disabled={true} theme={light} variant={primary}>
                Primary
              </Button>
            </span>
            <span style={margin}>
              <Button disabled={true} theme={light} variant={secondary}>
                Secondary
              </Button>
            </span>
            <span style={margin}>
              <Button disabled={true} theme={light} variant={success}>
                Success
              </Button>
            </span>
            <span style={margin}>
              <Button disabled={true} theme={light} variant={warning}>
                Warning
              </Button>
            </span>
            <span style={margin}>
              <Button disabled={true} theme={light} variant={danger}>
                Danger
              </Button>
            </span>
          </Card>
        </div>
      </div>

      <div style={margin}>
        <h3>Buttongroup</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={primary}>
                  Left
                </Button>
                <Button theme={light} variant={primary}>
                  Middle
                </Button>
                <Button theme={light} variant={primary}>
                  Right
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={secondary}>
                  Left
                </Button>
                <Button theme={light} variant={secondary}>
                  Middle
                </Button>
                <Button theme={light} variant={secondary}>
                  Right
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={success}>
                  Left
                </Button>
                <Button theme={light} variant={success}>
                  Middle
                </Button>
                <Button theme={light} variant={success}>
                  Right
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={warning}>
                  Left
                </Button>
                <Button theme={light} variant={warning}>
                  Middle
                </Button>
                <Button theme={light} variant={warning}>
                  Right
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={danger}>
                  Left
                </Button>
                <Button theme={light} variant={danger}>
                  Middle
                </Button>
                <Button theme={light} variant={danger}>
                  Right
                </Button>
              </ButtonGroup>
            </span>
          </Card>
        </div>
      </div>
      <div style={margin}>
        <h3>Mix & Match</h3>
        <div style={margin}>
          <Card theme={dark}>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={secondary}>
                  Cancel
                </Button>
                <Button theme={light} variant={primary}>
                  Go
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={secondary}>
                  Cancel
                </Button>
                <Button theme={light} variant={success}>
                  Go!
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={secondary}>
                  Cancel
                </Button>
                <Button theme={light} variant={danger}>
                  No Go!
                </Button>
              </ButtonGroup>
            </span>
            <span style={margin}>
              <ButtonGroup>
                <Button theme={light} variant={secondary}>
                  Cancel
                </Button>
                <Button theme={light} variant={warning}>
                  Maybe Go
                </Button>
              </ButtonGroup>
            </span>
          </Card>
        </div>
      </div>
    </>
  );
};
