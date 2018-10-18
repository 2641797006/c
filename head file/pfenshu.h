#ifndef _PFENSHU_H_
#define _PFENSHU_H_

#ifndef _INC_STDIO
#include <stdio.h>
#ifndef _INC_STDIO
#define _INC_STDIO
#endif
#endif

typedef struct fenshu{
	int fz;
	int fm;
}fenshu;

int gcd(int x, int y)
{
	int t;
	x= x<0 ? -x : x;
	y= y<0 ? -y : y;
	x>=y ?: (t=x, x=y, y=t);
	y= y==0 ? 1 : y;
	while(t=x%y, x=y, y=t);
	return x;
}

int lcm(int x, int y)
{
	int z=gcd(x, y);
	z= z==0 ? 1 : z;
	return x/z*y;
}

void fs_yuefen(fenshu* fs)
{
	int yuefen=gcd(fs->fz, fs->fm);
	yuefen= yuefen==0 ? 1 : yuefen;
	fs->fz/=yuefen;
	fs->fm/=yuefen;
}

double fs_value(fenshu fs)
{
	return fs.fm==0 ? 0 : ( ((double) fs.fz) / fs.fm );
}

int fs_input(fenshu* fs)
{
	ungetc('\n', stdin);
	return scanf("%*[^-0-9]%d%*c%d", &fs->fz, &fs->fm);
}

char* fs_string(fenshu fs, char* str)
{
	int fz, fm;
	fs_yuefen(&fs);
	fm= fs.fm<0 ? -fs.fm : fs.fm;
	fz= fs.fz<0 ? (fs.fm<0 ? -fs.fz : fs.fz) : (fs.fm<0 ? -fs.fz : fs.fz);
	sprintf(str,"%d/%d", fz, fm);
	if(fm==1 || fz==0&&fm!=0)
		sprintf(str, "%d", fz/fm);
	return str;
}

int fs_output(fenshu fs)
{
	char str[32];
	return printf("%s", fs_string(fs, str));
}

fenshu fs_add(fenshu f1, fenshu f2)
{
	fenshu f;
	fs_yuefen(&f1);
	fs_yuefen(&f2);
	f.fm=lcm(f1.fm, f2.fm);
	f.fz= f1.fz*(f.fm/f1.fm) + f2.fz*(f.fm/f2.fm);
	fs_yuefen(&f);
	return f;
}

fenshu fs_sub(fenshu f1, fenshu f2)
{
	fenshu f;
	fs_yuefen(&f1);
	fs_yuefen(&f2);
	f.fm=lcm(f1.fm, f2.fm);
	f.fz= f1.fz*(f.fm/f1.fm) - f2.fz*(f.fm/f2.fm);
	fs_yuefen(&f);
	return f;
}

fenshu fs_mul(fenshu f1, fenshu f2)
{
	fs_yuefen(&f1);
	fs_yuefen(&f2);
	f1.fz= f1.fz*f2.fz;
	f1.fm= f1.fm*f2.fm;
	fs_yuefen(&f1);
	return f1;
}

fenshu fs_daoshu(fenshu fs)
{
	fenshu f;
	f.fz=fs.fm;
	f.fm=fs.fz;
	return f;
}

fenshu fs_div(fenshu f1, fenshu f2)
{
	return fs_mul(f1, fs_daoshu(f2));
}

fenshu fs_pow(fenshu fs, int pow)
{
	fenshu fpow={1, 1};
	fs_yuefen(&fs);
	fs= pow>0 ? fs : ( pow=-pow, fs_daoshu(fs) );
	int i=0;
	while(i++<pow){
		fpow.fz*=fs.fz;
		fpow.fm*=fs.fm;
	}
	return fpow;
}

fenshu fs_intfs(int a)
{
	fenshu f;
	f.fz=a;
	f.fm=1;
	return f;
}

fenshu fs_xsfs(double xs)
{
	int i=0, bs=1, cs=1, t;
	fenshu f;
	t=(int)xs;
	xs-=t;
//	while((int)xs!=0&&i++<9){
//		xs/=10;
//		cs*=10;
//	}
	i=0;
	while( (xs-(int)xs!=0) && (i++<9) ){
		xs*=10;
		bs*=10;
	}
	xs= xs-(int)xs!=0 ? (xs>0 ? xs+1 : xs-1) : xs;
	f.fz=(int)xs;
	f.fm=bs/cs;
	f.fz+=t*f.fm;
	fs_yuefen(&f);
	return f;
}

/*
fenshu fs_xsfs(double xs)
{
	int i=0, bs=1, cs=1, t;
	fenshu f;
	t=(int)xs;
	while((int)xs!=0&&i++<9){
		xs/=10;
		cs*=10;
	}
	i=0;
	while( (xs-(int)xs!=0) && (i++<9) ){
		xs*=10;
		bs*=10;
	}
	xs= xs-(int)xs!=0 ? (xs>0 ? xs+1 : xs-1) : xs;
	f.fz=(int)xs;
	f.fm=bs/cs;
	fs_yuefen(&f);
	return f;
}*/


#endif