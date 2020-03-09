# Tenzir UI-Component Library

## Development
The following steps will start the storybook application:
```
1. yarn
2. yarn start
3. (separate tab) - yarn storybook
```

## Release
This library is only used internally. Directly sourcing the directory from within other directories of the monorepo brings along some issues with conflicting temp build files, resulting in having to clean everything. Combined with the lack of versioning, there is a tiny script to build tarballs of the `.RE` files in the repo. For now, the version number is manual (which is nice for quick small and predominantly local updates). Later on, this could be handled by CI.
```
1. node scripts/tar.js
2. enter version no.
```

### Overhead
There is an every so slight overhead for the moment as we pull in fonts from Google that are in the '.storybook/preview-head' folder. These are also pulled in the actual FE library.
