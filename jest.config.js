module.exports = {
    transformIgnorePatterns: [
        'node_modules/(?!(' +
            '|bs-css' +
            '|@glennsl/bs-jest' +
            '|bs-css-emotion' +
            '|bs-platform' +
            ')/)',
    ],
}
