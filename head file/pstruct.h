#ifndef _PSTRUCT_H_
#define _PSTRUCT_H_

#ifndef _PTYPE_H_
#include <__pink/ptype.h>
#endif

typedef struct{
	_1p word[64];
	_8p flag;
	_8p reserve;
	_4p version;
	_4p versionx;
	_4p update_v;
	_4p update_vx;
}_WH;

typedef struct{
	_4p flag;
	_4p reserve;
	_4p execute;
	_4p important;
	_4p id;
	_4p idx;
	_8p overmem;
}_WHEXE;

























#undef _1p
#undef _2p
#undef _4p
#undef _8p

#endif