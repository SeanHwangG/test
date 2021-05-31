# README

* works even if the original code didn't violate the style guide (similar to clang-format, gofmt)

* python -m pip install yapf
* python -m site --user-base

* Specified on the command line
* In the `style` section of a .style.yapf file in either the current directory or one of its parent directories
* In the `yapf` section of a setup.cfg file in either the current directory or one of its parent directories
* In the `tool.yapf` section of a pyproject.toml file in either the current directory or one of its parent directories
* In the `style` section of a ~/.config/yapf/style file in your home directory
* If none of those files are found, the default style is used (PEP8)

## CLI

* -d: print the diff for the fixed source
* -e `pat`: exclude `pat` while formatting
* -i `glob`: change in-place
* -r: run recursively over directories
* --vv: print out file names while processsing
* --no-local-style: don't search for local style definition
