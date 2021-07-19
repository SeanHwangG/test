# Tool

## Mac

* disable accented key for long press
  * defaults write -g ApplePressAndHoldEnabled -bool false

> Shortcut

* ⌘ ⇧ 3 / 4: captures a screenshot of your entire screen / drag to select a portion of your screen
* ⌘ ⇧ 6: captures number pad
* (⌃) ⌘ shift 4 / 5: Screen shot (saved to clipboard)

* ⌘ ⇧ /: Help
* ⌘ space: Search files
* ⌥ ⌘ v: Ctrl x for files
* ⇧ ⌘ .: See Hidden files
* ⌃ ⌘ space: See special characters
* ⌘ ⇧ G: Go to specific file path
* ⌘ ⌃ f: Full screen
* System Preferences -> Sharing -> Computer Name:

## Google

* search
  * &tbs=qdr:X: n h d w m y
  * past 6 month: `http://www.google.com/search?q=local+seo&tbs=qdr:m6`

* Drive: Free storage
  * Version Control
  * Shareable link with different permission
  * drive API for automation (fetching, writing)
  * [Backup and sync for computer](https://www.google.com/intl/en/drive/download/)
  * Shortcut
    * ⌃ ⌥ f: File
    * ⌃ ⌥ e: Edit
    * ⌥ /: Search menu
    * ⌘ /: Search shortcut

* Docs
  * [Equation](http://www.notuom.com/google-docs-equation-shortcuts.html)
  * Shortcut
    * ⌥ ⌘ x: Spell check
    * ⇧ ⌘ c: page info
    * ⌘ ⌥ 1~6: Heading
    * ⌘ ⌥ c / v: style copy / paste

* Form: make quiz -> put answer

* Sheet
  * Shortcut
    * option ↑ ↓: Change sheet

## Chrome

* Shortcut
  * ⌘  d: bookmark
  * ⌘  l: search tab
  * ⌘  `: change window
  * ⌘  ⇧  t: reopen closed tab
  * ⌘  ⇧  c: page inspection

> stylish

* Customize css for any website

```css
/* Increase Center */
.reset-3c756112--pageContainer-544d6e9c {
  max-width: 1800px;
}

/* Hide left navigation */
.reset-3c756112--body-324a5898 {
  margin: 0;
}

.reset-3c756112--contentNavigation-dd3370a4 {
  min-width: 0px;
}

/* Hide except edit on github */
.reset-3c756112--menuItem-aa02f6ec--menuItemLight-757d5235--menuItemInline-173bdf97--pageSideMenuItem-22949732:
not(:first-child) {
  display: none;
}

/* reduce right navigation */
.reset-3c756112--contentNavigation-dd3370a4 {
  padding-left: 0;
  width: calc((100% - 1448px) / 5);
}

.reset-3c756112--pageSide-ad9fed26 {
  width: 180px;
}

/* Hide admin option */
.reset-3c756112--sidebarNav-1270f224 {
  display: none;
}

.reset-3c756112--body-324a5898 {
  width: 100%;
}
```

## editorconfig

* charset = (ex: utf-8)
* end_of_line = lf
* indent_style = (space, tab)
* indent_size = 2
* line_length = 88

> python

* multi_line_output = 3

{% include '.editorconfig' %}
