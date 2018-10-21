#ifndef _PFILE_H_
#define _PFILE_H_

#ifndef _INC_STRING
#include <string.h>
#ifndef _INC_STRING
#define _INC_STRING
#endif
#endif


void pfilename(char** ppc)
{
		if(**ppc==0x22){
			*(*ppc+strlen(*ppc)-1)=0;
			(*ppc)++;
		}
}

#define pFILE_SHARE_ALL	0x00000007
#define pFILE_SHARE_RW	0x00000003
#define pCreateFile(filename, openmode) CreateFile(filename, GENERIC_READ|GENERIC_WRITE, pFILE_SHARE_RW, NULL, openmode, FILE_ATTRIBUTE_NORMAL, NULL)

int pfile_wb(char* filename, void* buffer, int size)
{
	FILE* fp;
	fp=fopen(filename, "wb");
	if(!fp)
		return -1;
	if( fwrite(buffer, size, 1, fp)!=1 ){
		fclose(fp);
		return -2;
	}
	fclose(fp);
	return 0;
}

int pmkdir(void* buffer, char* fileindex, char** dir, int num)
{
	int i;
	strcpy(buffer, fileindex);
	for(i=0;i<num;i++){
		strcat(buffer, *(dir+i));
		if(access(buffer, F_OK))
			if(mkdir(buffer))
				return -1;
	}
	return 0;
}






#endif