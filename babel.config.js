module.exports = {
    plugins: [
        ['@babel/plugin-proposal-private-property-in-object', { loose: true }],
    ],
    presets: [
        [
            '@babel/preset-env',
            {
                targets: {
                    node: 'current',
                },
            },
        ],
    ],
}
