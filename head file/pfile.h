#ifndef _PFILE_H_
#define _PFILE_H_


void pfname(char** ppc)
{
		ungetc('\1',stdin);
		ungetc('\n',stdin);
		scanf("%*[^\n]%*c%[^\n]", *ppc);
		if(**ppc==0x22){
			*(*ppc+strlen(*ppc)-1)=0;
			(*ppc)++;
		}
}








#endif