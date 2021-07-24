#include <Python.h>
#include <cprint_list.hpp>

static PyObject *print_list(PyObject *self, PyObject *args)
{
  PyObject *lobj;
  /* Verify that the argument is a list. */
  if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &lobj))
    return NULL;

  /* Verify that each member of the list is of type str. */
  for (unsigned int i = 0; i < PyList_Size(lobj); ++i)
  {
    if (!PyUnicode_Check(PyList_GetItem(lobj, i)))
    {
      PyErr_SetString(PyExc_TypeError, "must pass in list of str");
      return NULL;
    }
  }
  /* Convert python object to a "natural C++ object" */
  std::vector<std::string> strings;
  for (unsigned int i = 0; i < PyList_Size(lobj); ++i)
    strings.push_back(PyUnicode_AsUTF8(PyList_GetItem(lobj, i)));

  Py_BEGIN_ALLOW_THREADS /* <-------- HERE WE RELEASE THE GIL */
      cprint_list(strings);
  Py_END_ALLOW_THREADS /* <---------- HERE WE ACQUIRE THE GIL */
      Py_RETURN_NONE;
}

static PyMethodDef SpamMethods[] = {
    {"print_list", print_list, METH_VARARGS,
     "A function that prints a list of strings."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam",        /* name of module */
    "spam module", /* module documentation */
    -1,
    SpamMethods};

PyMODINIT_FUNC
PyInit_spam(void)
{
  PyObject *m = PyModule_Create(&spammodule);
  if (m == NULL)
    return NULL;
  return m;
}
