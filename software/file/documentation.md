# Documentation

* descriptive-style rather than imperative-style
  * [ex] ("""Fetches rows from a Bigtable.""") -> ("""Fetch rows from a Bigtable."""),

{% tabs %}
{% tab title='python' %}

* sphinx
  * tool for automatic generation of Sphinx sources that, using the autodoc extension
  * document a whole package in the style of other automatic API documentation tools

> Example

* spinx
  * easy_install sphinx
  * pip install sphinx
  * -o `OUTPUT_PATH`: Directory to place the output files. If it does not exist, it is created.
  * -q: Do not output anything on standard output, only write warnings and errors to standard error.
  * -f: Force overwriting of any existing generated files.

  ```py
  """
  .. module:: useful_1
    :platform: Unix, Windows
    :synopsis: A useful module indeed.

  .. moduleauthor:: Andrew Carter <andrew@invalid.com>
  """

  def public_fn_with_googley_docstring(name, state=None):
    """This function does something.

    Args:
      name (str):  The name to use.

    Kwargs:
      state (bool): Current state to be in.

    Returns:
      int.  The return code::

        0 -- Success!
        1 -- No good.
        2 -- Try again.

    Raises:
      AttributeError, KeyError

    A really great idea.  A way you might use me is

    >>> print public_fn_with_googley_docstring(name='foo', state=None)
    0

    BTW, this always returns 0.  **NEVER** use with:class:`MyPublicClass`.

    """
    return 0

  def public_fn_with_sphinxy_docstring(name, state=None):
    """This function does something.

    :param name: The name to use.
    :type name: str.
    :param state: Current state to be in.
    :type state: bool.
    :returns:  int -- the return code.
    :raises: AttributeError, KeyError

    """
    return 0

  def public_fn_without_docstring():
    return True

  def _private_fn_with_docstring(foo, bar='baz', foobarbas=None):
    """I have a docstring, but won't be imported if you just use ``:members:``.
    """
    return None


  class MyPublicClass(object):
    """We use this as a public class example class.

    You never call this class before calling :func:`public_fn_with_sphinxy_docstring`.

    .. note::

      An example of intersphinx is this: you **cannot** use:mod:`pickle` on this class.

    """

    def __init__(self, foo, bar='baz'):
      """A really simple class.

      Args:
        foo (str): We all know what foo does.

      Kwargs:
        bar (str): Really, same as foo.

      """
      self._foo = foo
      self._bar = bar

    def get_foobar(self, foo, bar=True):
      """This gets the foobar

      This really should have a full function definition, but I am too lazy.

      >>> print get_foobar(10, 20)
      30
      >>> print get_foobar('a', 'b')
      ab

      Isn't that what you want?

      """
      return foo + bar

    def _get_baz(self, baz=None):
      """A private function to get baz.

      This really should have a full function definition, but I am too lazy.

      """
      return baz
  ```

{% endtab %}
{% endtabs %}

## Doc Function

* Should have docstring unless: not externally visible, very short, obvious
* Describe function's syntax, semantics not implemenation detail
* Descriptive rather than imperative ([ex] Returns the Bigtable path. -> The Bigtable path.)

> Reference

<https://google.github.io/styleguide/pyguide.html#383-functions-and-methods>

## Manual

{% tabs %}
{% tab title='shell' %}

* man: format and display the on-line manual pages
  * 1 `printf`: printf in user commands
  * -k man `'^printf'`: search for sections in man page

* whatis `command`: search the whatis database for complete words

| Section | contents                                |
| ------- | --------------------------------------- |
| 1       | User Commands                           |
| 2       | System Calls                            |
| 3       | C Library Functions                     |
| 3n      | network functions                       |
| 4       | Devices and Special Files               |
| 5       | File Formats and Conventions            |
| 6       | Games et. al.                           |
| 7       | Miscellanea                             |
| 8       | System Administration tools and Daemons |
| 9       | Kernel routines                         |

```sh
import png:- | xclip -selection clipboard -t image/png  # screenshot goes to clipboard
```

{% endtab %}
{% tab title='vim' %}

* :help key-notation: man page

{% endtab %}
{% endtabs %}

## Reference

{% tabs %}
{% tab title='markdown' %}

```md
<!-- 1. Separate references from contents -->
[StackOverflow][1]

[1]: http://stackoverflow.com

<!-- 2. Beak long reference -->
[StackOverflow](
  http://stackoverflow.com)
```

{% endtab %}
{% endtabs %}
