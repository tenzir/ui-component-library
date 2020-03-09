import { addParameters, configure } from "@storybook/react";

// Option defaults:
addParameters({
  options: {
    isFullscreen: false,
    showNav: true,
    showPanel: false,
    panelPosition: "bottom",
    hierarchySeparator: /\/|\./,
    hierarchyRootSeparator: /\|/,
    sidebarAnimations: true,
    enableShortcuts: false,
    isToolshown: false,
    storySort: undefined
  }
});

// automatically import all files ending in *.stories.js
configure(require.context("../stories", true, /\.stories\.js$/), module);
