#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <Python.h>
#include "boxbranding.h"

#define MAKE_STRING_FUNCTION(name) \
static PyObject* name(PyObject* self, PyObject* args) \
{ \
	PyObject* res; \
	char *s = _##name(); \
	res = Py_BuildValue("s", s); \
	free(s); \
	return res; \
} \

/* Available functions */
MAKE_STRING_FUNCTION(getVisionVersion)
MAKE_STRING_FUNCTION(getVisionRevision)
MAKE_STRING_FUNCTION(getBoxBrand)
MAKE_STRING_FUNCTION(getOEVersion)
MAKE_STRING_FUNCTION(getImageDistro)
MAKE_STRING_FUNCTION(getBoxType)
MAKE_STRING_FUNCTION(getBrandOEM)
MAKE_STRING_FUNCTION(getMachineBrand)
MAKE_STRING_FUNCTION(getMachineName)
MAKE_STRING_FUNCTION(getMachineBuild)
MAKE_STRING_FUNCTION(getMachineMake)
MAKE_STRING_FUNCTION(getImageVersion)
MAKE_STRING_FUNCTION(getImageBuild)
MAKE_STRING_FUNCTION(getImageDevBuild)
MAKE_STRING_FUNCTION(getImageType)
MAKE_STRING_FUNCTION(getFeedsUrl)
MAKE_STRING_FUNCTION(getImageFolder)
MAKE_STRING_FUNCTION(getImageFileSystem)
MAKE_STRING_FUNCTION(getMachineMtdBoot)
MAKE_STRING_FUNCTION(getMachineMtdRoot)
MAKE_STRING_FUNCTION(getMachineMtdKernel)
MAKE_STRING_FUNCTION(getMachineRootFile)
MAKE_STRING_FUNCTION(getMachineKernelFile)
MAKE_STRING_FUNCTION(getMachineMKUBIFS)
MAKE_STRING_FUNCTION(getMachineUBINIZE)
MAKE_STRING_FUNCTION(getImageArch)
MAKE_STRING_FUNCTION(getDisplayType)
MAKE_STRING_FUNCTION(getHaveSmallFlash)
MAKE_STRING_FUNCTION(getHaveMiddleFlash)
MAKE_STRING_FUNCTION(getHaveTranscoding)
MAKE_STRING_FUNCTION(getHaveMultiTranscoding)
MAKE_STRING_FUNCTION(getHaveMultiLib)
MAKE_STRING_FUNCTION(getMachineProcModel)

/* Module specification */
static PyMethodDef boxbrandingMethods[] = {
	{ "getVisionVersion", getVisionVersion, METH_NOARGS, NULL },
	{ "getVisionRevision", getVisionRevision, METH_NOARGS, NULL },
	{ "getBoxBrand", getBoxBrand, METH_NOARGS, NULL },
	{ "getOEVersion", getOEVersion, METH_NOARGS, NULL },
	{ "getImageDistro", getImageDistro, METH_NOARGS, NULL },
	{ "getBoxType", getBoxType, METH_NOARGS, NULL },
	{ "getBrandOEM", getBrandOEM, METH_NOARGS, NULL },
	{ "getMachineBrand", getMachineBrand, METH_NOARGS, NULL },
	{ "getMachineName", getMachineName, METH_NOARGS, NULL },
	{ "getMachineBuild", getMachineBuild, METH_NOARGS, NULL },
	{ "getMachineMake", getMachineMake, METH_NOARGS, NULL },
	{ "getImageVersion", getImageVersion, METH_NOARGS, NULL },
	{ "getImageBuild", getImageBuild, METH_NOARGS, NULL },
	{ "getImageDevBuild", getImageDevBuild, METH_NOARGS, NULL },
	{ "getImageType", getImageType, METH_NOARGS, NULL },
	{ "getFeedsUrl", getFeedsUrl, METH_NOARGS, NULL },
	{ "getImageFolder", getImageFolder, METH_NOARGS, NULL },
	{ "getImageFileSystem", getImageFileSystem, METH_NOARGS, NULL },
	{ "getMachineMtdBoot", getMachineMtdBoot, METH_NOARGS, NULL },
	{ "getMachineMtdRoot", getMachineMtdRoot, METH_NOARGS, NULL },
	{ "getMachineMtdKernel", getMachineMtdKernel, METH_NOARGS, NULL },
	{ "getMachineRootFile", getMachineRootFile, METH_NOARGS, NULL },
	{ "getMachineKernelFile", getMachineKernelFile, METH_NOARGS, NULL },
	{ "getMachineMKUBIFS", getMachineMKUBIFS, METH_NOARGS, NULL },
	{ "getMachineUBINIZE", getMachineUBINIZE, METH_NOARGS, NULL },
	{ "getImageArch", getImageArch, METH_NOARGS, NULL },
	{ "getDisplayType", getDisplayType, METH_NOARGS, NULL },
	{ "getHaveSmallFlash", getHaveSmallFlash, METH_NOARGS, NULL },
	{ "getHaveMiddleFlash", getHaveMiddleFlash, METH_NOARGS, NULL },
	{ "getHaveTranscoding", getHaveTranscoding, METH_NOARGS, NULL },
	{ "getHaveMultiTranscoding", getHaveMultiTranscoding, METH_NOARGS, NULL },
	{ "getHaveMultiLib", getHaveMultiLib, METH_NOARGS, NULL },
	{ "getMachineProcModel", getMachineProcModel, METH_NOARGS, NULL },
	{ NULL, NULL, 0, NULL }
};

/* Initialize the module */
void initboxbranding() {
	Py_InitModule("boxbranding", boxbrandingMethods);
}
