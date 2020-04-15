import { addParameters, configure } from "@storybook/react";
import { themes } from "@storybook/theming";

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
    isToolshown: true,
    storySort: undefined,
  },
  darkMode: {
    dark: { ...themes.dark, appBg: "rgb(34, 38, 38)" },
    light: themes.light,
  },
});

// automatically import all files ending in *.stories.js
configure(require.context("../stories", true, /\.stories\.js$/), module);
