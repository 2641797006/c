#ifndef _PBITMAP_H_
#define _PBITMAP_H_

#ifndef _WINDOWS_
#include <windows.h>
#ifndef _WINDOWS_
#define _WINDOWS_
#endif
#endif

typedef struct{
	int width;
	int height;
	int x;
	int y;
	int dx;
	int dy;
}ANIMINFO;

void pPaintBMP(HWND hwnd, HBITMAP hbmBMP, int x, int y)
{
	BITMAP bm;
	PAINTSTRUCT ps;

	HDC hdc=BeginPaint(hwnd, &ps);

	HDC hdcMem=CreateCompatibleDC(hdc);
	HBITMAP hbmOld=SelectObject(hdcMem, hbmBMP);

	GetObject(hbmBMP, sizeof(BITMAP), &bm);
	BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	EndPaint(hwnd, &ps);
}

HBITMAP pMaskBMP(HBITMAP hbmBMP, int TMcolor)
{
	HDC hdcMem, hdcMem2;
	BITMAP bm;
	HBITMAP hbmMask;

	GetObject(hbmBMP, sizeof(BITMAP), &bm);
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	hdcMem = CreateCompatibleDC(0);
	hdcMem2 = CreateCompatibleDC(0);

	SelectObject(hdcMem, hbmBMP);
	SetBkColor(hdcMem, TMcolor);

	SelectObject(hdcMem2, hbmMask);
	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);

	return hbmMask;
}

void pPaintTmBMP(HWND hwnd, HBITMAP hbmBMP, HBITMAP hbmMask, int x, int y)
{
	BITMAP bm;
	PAINTSTRUCT ps;

	HDC hdc=BeginPaint(hwnd, &ps);
	HDC hdcMem=CreateCompatibleDC(hdc);

	GetObject(hbmBMP, sizeof(BITMAP), &bm);
	HBITMAP hbmOld=SelectObject(hdcMem, hbmMask);
	BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCAND);

	SelectObject(hdcMem, hbmBMP);
	BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	EndPaint(hwnd, &ps);
}

void pDrawAnim(HDC hdc, HBITMAP hbmBMP, HBITMAP hbmMask, ANIMINFO* animinfo, RECT* rect)
{
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect->right, rect->bottom);
	HBITMAP hbmOldBuffer = SelectObject(hdcBuffer, hbmBuffer);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = SelectObject(hdcMem, hbmMask);

	FillRect(hdcBuffer, rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	BitBlt(hdcBuffer, animinfo->x, animinfo->y, animinfo->width, animinfo->height, hdcMem, 0, 0, SRCAND);

	SelectObject(hdcMem, hbmBMP);
	BitBlt(hdcBuffer, animinfo->x, animinfo->y, animinfo->width, animinfo->height, hdcMem, 0, 0, SRCPAINT);

	BitBlt(hdc, 0, 0, rect->right, rect->bottom, hdcBuffer, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}

void pUpdateAnim(ANIMINFO* animinfo, RECT* rect, int MoveDelta)
{
	animinfo->x += animinfo->dx;
	animinfo->y += animinfo->dy;

	if(animinfo->x < 0)
	{
		animinfo->x = 0;
		animinfo->dx = MoveDelta;
	}
	else if(animinfo->x + animinfo->width > rect->right)
	{
		animinfo->x = rect->right - animinfo->width;
		animinfo->dx = -MoveDelta;
	}

	if(animinfo->y < 0)
	{
		animinfo->y = 0;
		animinfo->dy = MoveDelta;
	}
	else if(animinfo->y + animinfo->height > rect->bottom)
	{
		animinfo->y = rect->bottom - animinfo->height;
		animinfo->dy = -MoveDelta;
	}
}











#endif