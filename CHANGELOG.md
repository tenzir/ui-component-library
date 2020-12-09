# Changelog

This changelog documents all notable user-facing changes of the Tenzir 
Component Library.

Every entry has a category for which we use the following visual abbreviations:

- 🎁 Feature
- 🧬 Experimental Feature
- ⚠️  Change
- ⚡️ Breaking Change
- 🐞 Bugfix

## [0.8.1]
- 🐞 Tooltip Hover [#60](https://github.com/tenzir/ui-component-library/pull/60)
The tooltip was included in the hover's bounding box of the element. The 
`pointer-events` are now disabled for hover events until they become visible, 
meaning it can only be activated by hovering the element upon which the tooltip
is introduced, not the tooltip itself.

## [0.8.0]
- 🧬 Tooltips [#59](https://github.com/tenzir/ui-component-library/pull/59)
We've used a CSS only approach for tooltips that is reasonably flexible in terms
of positioning. We'll test this internally before releasing it publicly.
