<h1 align="center">
  Tenzir UI Component Library
</h1>
<h4 align="center">

A ReasonML-first UI component library

[![CI][ci-badge]][ci-url]
[![NPM Version][npm-badge]][npm-url]
[![Development Status][alpha-badge]][latest-release-url]
[![License][license-badge]][license-url]

[_Introduction_](#introduction) &mdash;
[_Getting Started_](#getting-started) &mdash;
[_Contributing Guidelines_][contributing-url] &mdash;
[_License_](#license)

</h4>

## Introduction
Most UI-Libraries for use with ReasonML have bindings to existing UI-Libraries.
Wanting to be fully type-safe without outdated component bindings, leveraging 
things like pattern-matching along the way, we decided to build our own 
UI-Library, ReasonML-first. We will continually build on this and add 
components as we need them. This means components may be missing, or lack 
support of all the web API's needed in your specific use-case. We encourage 
contribution ([Contributing Guidelines][contributing-url]) in these cases.

### Components
The following components are currently built.
- Button
- Card
- Checkbox
- Icons - A script generates bindings for [React 
  Icons](https://github.com/react-icons/react-icons). We currently generate
  bindings to a subset that includes just the [Feather 
  Icons](https://feathericons.com/) (MIT licensed).
- Input
- Textarea

## Getting Started
### Installation
**Add dependency:**
```sh
yarn add bs-tenzir-ui-components
```

**Add the library to the `bs-dependencies` in your `bsconfig.json`:**
```sh
{
  ...
  "bs-dependencies": ["tenzir-ui-component-library"]
}
```

### Contributing / Development
We develop the components application agnostically with the help of 
[_Storybook_](https://storybook.js.org/). The ReasonML code is compiled first 
and is then imported as plain Javascript in the Storybook stories.

**Install dependencies:**
```sh
yarn
```

**Start ReasonML compiler with file-watcher:**
```sh
yarn start 
```

**Start Storybook server (should be ran simultaniously):**
```sh
yarn storybook
```

## License
Tenzir UI-Component Library comes with a [3-clause BSD license][license-url].

[ci-url]: https://github.com/tenzir/ui-component-library/actions?query=branch%3Amaster+workflow%3A%22UI%20Components%22
[ci-badge]: https://github.com/tenzir/ui-component-library/workflows/UI%20Components/badge.svg?branch=master
[npm-badge]: https://img.shields.io/npm/v/tenzir-ui-component-library
[npm-url]: https://www.npmjs.com/package/tenzir-ui-component-library
[contributing-url]: https://github.com/tenzir/.github/blob/master/contributing.md
[latest-release-badge]: https://img.shields.io/github/commits-since/tenzir/ui-components/latest.svg?color=green
[latest-release-url]: https://github.com/tenzir/ui-components/releases
[license-badge]: https://img.shields.io/badge/license-BSD-blue.svg
[license-url]: https://github.com/tenzir/ui-components/blob/master/COPYING
[alpha-badge]: https://img.shields.io/badge/stage-alpha-blueviolet
