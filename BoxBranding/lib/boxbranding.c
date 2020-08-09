#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "boxbranding.h"

/** detecting whether base is starts with str
 */
bool startsWith (char* base, char* str)
{
    return (strstr(base, str) - base) == 0;
}

/** detecting whether base is ends with str
 */
bool endsWith (char* base, char* str)
{
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

/**
* Check if a file exist using stat() function
* return 1 if the file exist otherwise return 0
*/
int fileExist(const char* filename){
	struct stat buffer;
	int exist = stat(filename,&buffer);
	if(exist == 0)
	    return 1;
	else // -1
	    return 0;
}

/** reading file and return value from it
 * This function allocates memory for the returned string.
 * The caller must call free() to prevent memory leaks.
 * */
char* ReadProcEntry(char *filename)
{
	FILE *boxtype_file = fopen(filename,"r");
	char boxtype_name[20];
	char *real_boxtype_name = NULL;
	char c;
	int i = 0;

	if(boxtype_file)
	{
		while ((c = fgetc(boxtype_file)) != EOF && i < sizeof(boxtype_name) - 2)
		{
			if (c == '\n')
			{
				i--;
				break;
			}
			boxtype_name[i] = c;
			i++;
		}
		boxtype_name[i+1] = '\0';
		real_boxtype_name = malloc(strlen(boxtype_name) + 1);
		if (real_boxtype_name)
			strcpy(real_boxtype_name, boxtype_name);

		fclose(boxtype_file);
	}
	else
		puts("[BRANDING] Can not open this proc entry!\n");

	return real_boxtype_name;
}

char *_getVisionVersion()
{
	return strdup(VISIONVERSION);
}

char *_getVisionRevision()
{
	return strdup(VISIONREVISION);
}

char *_getDeveloperName()
{
	return strdup(DEVELOPERNAME);
}

char *_getBoxBrand()
{
	return strdup(BOXBRAND);
}

char *_getOEVersion()
{
	return strdup(OE_VER);
}

char *_getImageDistro()
{
	return strdup(DISTRO);
}

char *_getBoxType()
{
	char *boxtype_name = NULL;
	if(strcmp(BOXTYPE, "xpeedlx") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/boxtype");
		if(strcmp(boxtype_name, "ini-1000lx") == 0)
		{
			free(boxtype_name);
			return strdup("xpeedlx2t");
		}
		else if(strcmp(boxtype_name, "ini-1000de") == 0)
		{
			free(boxtype_name);
			boxtype_name = ReadProcEntry("/proc/stb/fp/version");
			if(startsWith(boxtype_name, "2"))
			{
				free(boxtype_name);
				return strdup("xpeedlx2");
			}
			else
			{
				free(boxtype_name);
				return strdup("xpeedlx1");
			}
		}
	}
	else if(strcmp(BOXTYPE, "twinboxlcd") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/boxtype");
		if(strcmp(boxtype_name, "7200S") == 0)
		{
			free(boxtype_name);
			return strdup("twinboxlcdci");
		}
	}
	else if(strcmp(BOXTYPE, "ventonhdx") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/boxtype");
		if(strcmp(boxtype_name, "ini-3000") == 0)
		{
			free(boxtype_name);
			return strdup("uniboxhd1");
		}
		else if(strcmp(boxtype_name, "ini-5000") == 0)
		{
			free(boxtype_name);
			return strdup("uniboxhd2");
		}
		else if(strcmp(boxtype_name, "ini-7000") == 0)
		{
			free(boxtype_name);
			return strdup("uniboxhd3");
		}
		else if(strcmp(boxtype_name, "ini-7012") == 0)
		{
			free(boxtype_name);
			return strdup("uniboxhd3");
		}
	}
	else if(strcmp(BOXTYPE, "et7x00") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/chipset");
		if(startsWith(boxtype_name, "bcm73625"))
		{
			free(boxtype_name);
			return strdup("et7100");
		}
		else
		{
			boxtype_name = ReadProcEntry("/proc/stb/info/boxtype");
			return boxtype_name;
		}
	}
	else if(strcmp(BOXTYPE, "et6x00") == 0 || strcmp(BOXTYPE, "et9x00") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/boxtype");
		return boxtype_name;
	}
	else if(strcmp(BOXTYPE, "dm520") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/model");
		if(strcmp(boxtype_name, "dm525") == 0)
		{
			free(boxtype_name);
			return strdup("dm525");
		}
		else
		{
			free(boxtype_name);
			return strdup(BOXTYPE);
		}
	}
	else if(strcmp(BOXTYPE, "dm900") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/model");
		if(strcmp(boxtype_name, "dm920") == 0)
		{
			free(boxtype_name);
			return strdup("dm920");
		}
		else
		{
			free(boxtype_name);
			return strdup(BOXTYPE);
		}
	}
	else if(strcmp(BOXTYPE, "sf8008") == 0)
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/type");
		if(strcmp(boxtype_name, "12") == 0)
		{
			free(boxtype_name);
			return strdup("sf8008c");
		}
		else if(strcmp(boxtype_name, "11") == 0)
		{
			free(boxtype_name);
			return strdup("sf8008t");
		}
		else
		{
			free(boxtype_name);
			return strdup("sf8008s");
		}
	}
	return strdup(BOXTYPE);
}

char *_getBrandOEM()
{
	return strdup(BRAND_OEM);
}

char *_getMachineBrand()
{
	return strdup(MACHINE_BRAND);
}

/** detecting real Box Name for OSD Translations
 */
char *_getMachineName()
{
	char *boxtype_name = NULL;
	if(fileExist("/proc/stb/info/boxtype"))
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/boxtype");
		/** INI detection */
		if(strcmp(boxtype_name, "ini-3000") == 0)
		{
			free(boxtype_name);
			return strdup("HD-1");
		}
		else if(strcmp(boxtype_name, "ini-5000") == 0)
		{
			free(boxtype_name);
			return strdup("HD-2");
		}
		else if(strcmp(boxtype_name, "ini-7000") == 0)
		{
			free(boxtype_name);
			return strdup("HD-3");
		}
		else if(strcmp(boxtype_name, "ini-7012") == 0)
		{
			free(boxtype_name);
			return strdup("HD-3");
		}
		else if(strcmp(boxtype_name, "ini-1000lx") == 0)
		{
			free(boxtype_name);
			return strdup("LX-2T");
		}
		/** XTrend detection */
		else if(strcmp(boxtype_name, "et7000") == 0)
		{
			free(boxtype_name);
			boxtype_name = ReadProcEntry("/proc/stb/info/chipset");
			if(startsWith(boxtype_name, "bcm73625"))
			{
				free(boxtype_name);
				return strdup("ET7100 V2");
			}
			else
			{
				free(boxtype_name);
				return strdup("ET7000");
			}
		}
		else if(strcmp(boxtype_name, "sf8008") == 0)
		{
			free(boxtype_name);
			boxtype_name = ReadProcEntry("/proc/stb/info/type");
			if(startsWith(boxtype_name, "12"))
			{
				free(boxtype_name);
				return strdup("SF8008 4K Combo");
			}
			else if(startsWith(boxtype_name, "11"))
			{
				free(boxtype_name);
				return strdup("SF8008 4K Twin");
			}
			else
			{
				free(boxtype_name);
				return strdup("SF8008 4K Single");
			}
		}
		else if(strcmp(BOXTYPE, "twinboxlcd") == 0)
		{
			if(strcmp(boxtype_name, "7200S") == 0)
			{
				free(boxtype_name);
				return strdup("TWINBOX LCD CI");
			}
		}
		else /** if there is not matching STB name, return value from proc */
		{
			/*
			 * TODO: The comment above and the code disagree.
			 *
			 * Which should it be? Right now it's the compile time string supplied via configure.
			 */
			free(boxtype_name);
			return strdup(MACHINE_NAME);
		}
	}
	/** AZBox detection */
	else if (fileExist("/proc/stb/info/azmodel") && fileExist("/proc/stb/info/model"))
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/model");
		free(boxtype_name);
	}
	else if (fileExist("/proc/stb/info/model"))
	{
		boxtype_name = ReadProcEntry("/proc/stb/info/model");
		free(boxtype_name);
		return strdup(MACHINE_NAME);
	}
	return strdup(MACHINE_NAME);
}

char *_getMachineBuild()
{
	return strdup(MACHINE_BUILD);
}

char *_getMachineMake()
{
	return strdup(MACHINE_MAKE);
}

char *_getImageVersion()
{
	return strdup(IMAGEVERSION);
}

char *_getImageBuild()
{
	return strdup(IMAGEBUILD);
}

char *_getImageDevBuild()
{
	return strdup(IMAGEDEVBUILD);
}

char *_getImageType()
{
	return strdup(DISTRO_TYPE);
}

char *_getFeedsUrl()
{
	return strdup(FEEDSURL);
}

char *_getImageFolder()
{
	return strdup(IMAGEDIR);
}

char *_getImageFileSystem()
{
	return strdup(IMAGE_FSTYPES);
}

char *_getMachineMtdBoot()
{
	return strdup(MTD_BOOTFS);
}

char *_getMachineMtdRoot()
{
	return strdup(MTD_ROOTFS);
}

char *_getMachineMtdKernel()
{
	return strdup(MTD_KERNEL);
}

char *_getMachineRootFile()
{
	return strdup(ROOTFS_FILE);
}

char *_getMachineKernelFile()
{
	return strdup(KERNEL_FILE);
}

char *_getMachineMKUBIFS()
{
	return strdup(MKUBIFS_ARGS);
}

char *_getMachineUBINIZE()
{
	return strdup(UBINIZE_ARGS);
}

char *_getForceMode()
{
	return strdup(FORCE_MODE);
}

char *_getImageArch()
{
	return strdup(ARCH_TYPE);
}

char *_getImageFPU()
{
	return strdup(TFPU_TYPE);
}

char *_getDisplayType()
{
	return strdup(DISPLAY_TYPE);
}

char *_getHaveSmallFlash()
{
	if(strcmp(HAVE_SMALLFLASH, "False") == 0)
		return strdup("");
	return strdup(HAVE_SMALLFLASH);
}

char *_getHaveMiddleFlash()
{
	if(strcmp(HAVE_MIDDLEFLASH, "False") == 0)
		return strdup("");
	return strdup(HAVE_MIDDLEFLASH);
}

char *_getHaveTranscoding()
{
	if(strcmp(HAVE_TRANSCODING, "False") == 0)
		return strdup("");
	return strdup(HAVE_TRANSCODING);
}

char *_getHaveMultiTranscoding()
{
	if(strcmp(HAVE_MULTITRANSCODING, "False") == 0)
		return strdup("");
	return strdup(HAVE_MULTITRANSCODING);
}

char *_getHaveMultiLib()
{
	if(strcmp(HAVE_MULTILIB, "False") == 0)
		return strdup("");
	return strdup(HAVE_MULTILIB);
}

char *_getMachineProcModel() // return just value from proc entry
{
	FILE *boxtype_file;
	char boxtype_name[20];
	char *real_boxtype_name = NULL;
	int len;

	if((boxtype_file = fopen("/proc/stb/info/hwmodel", "r")) != NULL)
	{
		fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
		fclose(boxtype_file);

		real_boxtype_name = malloc(strlen(boxtype_name) + 1);
		if (real_boxtype_name)
			strcpy(real_boxtype_name, boxtype_name);
		len = strlen(real_boxtype_name);
		if (len > 0 && real_boxtype_name[len - 1 ] == '\n')
			real_boxtype_name[len - 1] = '\0';
		return real_boxtype_name;
	}
	else if((boxtype_file = fopen("/proc/stb/info/boxtype", "r")) != NULL)
	{
		fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
		fclose(boxtype_file);

		if(strcmp(boxtype_name, "gigablue\n") == 0)
		{
			if((boxtype_file = fopen("/proc/stb/info/boxtype", "r")) != NULL)
			{
				fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
				fclose(boxtype_file);

				if((boxtype_file = fopen("/proc/stb/info/gbmodel", "r")) != NULL)
				{
					fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
					fclose(boxtype_file);

				}
			}
		}
		real_boxtype_name = malloc(strlen(boxtype_name) + 1);
		if (real_boxtype_name)
			strcpy(real_boxtype_name, boxtype_name);
		len = strlen(real_boxtype_name);
		if (len > 0 && real_boxtype_name[len - 1 ] == '\n')
			real_boxtype_name[len - 1] = '\0';
		return real_boxtype_name;
	}
	/** AZBox detection */
	else if((boxtype_file = fopen("/proc/stb/info/azmodel", "r")) != NULL)
	{
		fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
		fclose(boxtype_file);

		if((boxtype_file = fopen("/proc/stb/info/model", "r")) != NULL)
		{
			fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
			fclose(boxtype_file);

			real_boxtype_name = malloc(strlen(boxtype_name) + 1);
			if (real_boxtype_name)
				strcpy(real_boxtype_name, boxtype_name);
			len = strlen(real_boxtype_name);
			if (len > 0 && real_boxtype_name[len - 1 ] == '\n')
				real_boxtype_name[len - 1] = '\0';
			return real_boxtype_name;
		}
		else
		{
			return strdup(MACHINE_NAME);
		}
	}
	/** VU+ detection */
	else if((boxtype_file = fopen("/proc/stb/info/vumodel", "r")) != NULL)
	{
		fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
		fclose(boxtype_file);

		real_boxtype_name = malloc(strlen(boxtype_name) + 3);
		if (real_boxtype_name)
			sprintf(real_boxtype_name, "vu%s", boxtype_name);
		len = strlen(real_boxtype_name);
		if (len > 0 && real_boxtype_name[len - 1 ] == '\n')
			real_boxtype_name[len - 1] = '\0';
		return real_boxtype_name;
	}
	/** DMM detection */
	else
	{
		if((boxtype_file = fopen("/proc/stb/info/model", "r")) != NULL)
		{
			fgets(boxtype_name, sizeof(boxtype_name), boxtype_file);
			fclose(boxtype_file);
			real_boxtype_name = malloc(strlen(boxtype_name) + 1);
			if (real_boxtype_name)
				strcpy(real_boxtype_name, boxtype_name);
			len = strlen(real_boxtype_name);
			if (len > 0 && real_boxtype_name[len - 1 ] == '\n')
				real_boxtype_name[len - 1] = '\0';
			return real_boxtype_name;
		}
	}
	return strdup(MACHINE_NAME);
}

char *_getHaveHDMI()
{
	if(strcmp(HAVE_HDMI, "False") == 0)
		return strdup("");
	return strdup(HAVE_HDMI);
}

char *_getHaveYUV()
{
	if(strcmp(HAVE_YUV, "False") == 0)
		return strdup("");
	return strdup(HAVE_YUV);
}

char *_getHaveRCA()
{
	if(strcmp(HAVE_RCA, "False") == 0)
		return strdup("");
	return strdup(HAVE_RCA);
}

char *_getHaveAVJACK()
{
	if(strcmp(HAVE_AV_JACK, "False") == 0)
		return strdup("");
	return strdup(HAVE_AV_JACK);
}

char *_getHaveSCART()
{
	if(strcmp(HAVE_SCART, "False") == 0)
		return strdup("");
	return strdup(HAVE_SCART);
}

char *_getHaveDVI()
{
	if(strcmp(HAVE_DVI, "False") == 0)
		return strdup("");
	return strdup(HAVE_DVI);
}

char *_getHaveSVIDEO()
{
	if(strcmp(HAVE_SVIDEO, "False") == 0)
		return strdup("");
	return strdup(HAVE_SVIDEO);
}

char *_getHaveHDMIinHD()
{
	if(strcmp(HAVE_HDMI_IN_HD, "False") == 0)
		return strdup("");
	return strdup(HAVE_HDMI_IN_HD);
}

char *_getHaveHDMIinFHD()
{
	if(strcmp(HAVE_HDMI_IN_FHD, "False") == 0)
		return strdup("");
	return strdup(HAVE_HDMI_IN_FHD);
}

char *_getHaveWOL()
{
	if(strcmp(HAVE_WOL, "False") == 0)
		return strdup("");
	return strdup(HAVE_WOL);
}

char *_getHaveCI()
{
	if(strcmp(HAVE_CI, "False") == 0)
		return strdup("");
	return strdup(HAVE_CI);
}

char *_getBlindscanBin()
{
	return strdup(BLINDSCANBINARY);
}

char *_getSoCFamily()
{
	return strdup(SOCFAMILY);
}

char *_getHaveVFDSymbol()
{
	if(strcmp(HAVE_VFDSYMBOL, "False") == 0)
		return strdup("");
	return strdup(HAVE_VFDSYMBOL);
}

char *_getKernelVersion()
{
	return strdup(KERNELVERSION);
}
