const { themes } = require('@storybook/theming')

module.exports = {
    stories: [
        '@storybook/preset-create-react-app',
        '@storybook/addon-actions/register',
        '@storybook/addon-links/register',
        'storybook-dark-mode/register',
    ],
    stories: ['../stories/*.stories.js'],
    options: {
        isFullscreen: false,
        showNav: true,
        showPanel: true,
        panelPosition: 'bottom',
        sidebarAnimations: true,
        enableShortcuts: false,
        isToolshown: true,
        storySort: undefined,
    },
    darkMode: {
        dark: { ...themes.dark, appBg: 'rgb(34, 38, 38)' },
        light: themes.light,
    },
}
