const { themes } = require('@storybook/theming')
const { addParameters } = require('@storybook/react')

module.exports = {
    addons: [
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
        configureJSX: true,
    },
}

addParameters({
    darkMode: {
        dark: { ...themes.dark, appBg: 'rgb(34, 38, 38)' },
        light: themes.light,
    },
})
