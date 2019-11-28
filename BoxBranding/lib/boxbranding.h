#ifndef __BRANDING_H__
#define __BRANDING_H__

bool startsWith (char* base, char* str);
bool endsWith (char* base, char* str);
int fileExist(const char* filename);

/* The caller is always responsible for calling free() on the returned
 * string from all the functions that follow. */

char *ReadProcEntry(char *filename);

char *_getVisionVersion();
char *_getVisionRevision();
char *_getBoxBrand();
char *_getOEVersion();
char *_getImageDistro();
char *_getBoxType();
char *_getBrandOEM();
char *_getMachineBrand();
char *_getMachineName();
char *_getMachineBuild();
char *_getMachineMake();
char *_getImageVersion();
char *_getImageBuild();
char *_getImageDevBuild();
char *_getImageType();
char *_getFeedsUrl();
char *_getImageFolder();
char *_getImageFileSystem();
char *_getMachineMtdBoot();
char *_getMachineMtdRoot();
char *_getMachineMtdKernel();
char *_getMachineRootFile();
char *_getMachineKernelFile();
char *_getMachineMKUBIFS();
char *_getMachineUBINIZE();
char *_getImageArch();
char *_getDisplayType();
char *_getHaveSmallFlash();
char *_getHaveMiddleFlash();
char *_getHaveTranscoding();
char *_getHaveMultiTranscoding();
char *_getHaveMultiLib();
char *_getMachineProcModel();

#endif
