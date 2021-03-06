// Copyright (c) Arni Mar Jonsson.
// See LICENSE for details.

#include "leveldb_ext.h"

PyObject* leveldb_exception = 0;

static PyMethodDef leveldb_methods[] =
{
	{ (char*)"RepairDB", (PyCFunction)leveldb_repair_db, METH_VARARGS, (char*)leveldb_repair_db_doc },
	{ (char*)"DestroyDB", (PyCFunction)leveldb_destroy_db, METH_VARARGS, (char*)leveldb_destroy_db_doc },
	{NULL, NULL},
};

extern "C" PyMODINIT_FUNC
initleveldb(void)
{
	PyObject* leveldb_module = Py_InitModule3((char*)"leveldb", leveldb_methods, 0);

	if (leveldb_module == 0)
		return;

	if (PyType_Ready(&PyLevelDB_Type) < 0)
		return;

	if (PyType_Ready(&PyLevelDBSnapshot_Type) < 0)
		return;

	if (PyType_Ready(&PyWriteBatch_Type) < 0)
		return;

	// add custom types to the different modules
	Py_INCREF(&PyLevelDB_Type);

	if (PyModule_AddObject(leveldb_module, (char*)"LevelDB", (PyObject*)&PyLevelDB_Type) != 0)
		return;

	Py_INCREF(&PyLevelDBSnapshot_Type);

	if (PyModule_AddObject(leveldb_module, (char*)"Snapshot", (PyObject*)&PyLevelDBSnapshot_Type) != 0)
		return;

	Py_INCREF(&PyWriteBatch_Type);

	if (PyModule_AddObject(leveldb_module, (char*)"WriteBatch", (PyObject*)&PyWriteBatch_Type) != 0)
		return;

	// add custom exceptions
	leveldb_exception = PyErr_NewException((char*)"leveldb.LevelDBError", 0, 0);

	if (leveldb_exception == 0)
		return;

	Py_INCREF(leveldb_exception);

	if (PyModule_AddObject(leveldb_module, (char*)"LevelDBError", leveldb_exception) != 0)
		return;
}
