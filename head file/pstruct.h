#ifndef _PSTRUCT_H_
#define _PSTRUCT_H_

#define _1p unsigned char
#define _2p unsigned short
#define _4p unsigned long
#define _8p unsigned long long



typedef struct{
	_1p word[64];
	_8p flag;
	_8p reserve;
	_8p version;
	_8p versionx;
}_WH;





























#undef _1p
#undef _2p
#undef _4p
#undef _8p

#endif