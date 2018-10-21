/*
 * pinkwin.h
 * <windows.h> should be include before this file
 * HINSTANCE hInst; char s[1024+]; should be add in main.c file 
 * 
 *
 */

#ifndef _PINKWIN_H_
#define _PINKWIN_H_
//-mwin32 || -mwindows

#ifndef _PINKRES_H_
#include <__pink/pinkres.h>
//windres picon.rc picon.o
#endif

#ifndef _WINDOWS_
#include <windows.h>
#ifndef _WINDOWS_
#define _WINDOWS_
#endif
#endif

 __attribute__((__cdecl__)) __attribute__((__nothrow__)) char *strcat (char *, const char *);


#define pWinMain(pint1,pint2,pc,vint) int __attribute__((__stdcall__)) WinMain (HINSTANCE pint1, HINSTANCE pint2, LPSTR pc, int vint)
#define pinkwin() pWinMain(hInstance,hPrevInstance,lpCmdLine,nCmdShow)

#define pWinClass(name,value) const char name[]=value

#define pWinFunc(WndProc,pint,uint1,uint2,vlong) LRESULT (__attribute__((__stdcall__)) WndProc) (HWND pint, UINT uint1, WPARAM uint2, LPARAM vlong)
#define pinkfunc() pWinFunc(WndProc,hwnd,Message,wParam,lParam)
#define pWinCFun(FuncType,WndProc,pint,uint1,uint2,vlong) FuncType (__attribute__((__stdcall__)) WndProc) (HWND pint, UINT uint1, WPARAM uint2, LPARAM vlong)
#define pinkcfun(FuncType,FuncName) pWinCFun(FuncType,FuncName,hwnd,Message,wParam,lParam)

#define pRGB(x) ( ((x&0xff)<<16) | (x&0xff00) | ((x&0xff0000)>>16) )

#define pinkwc(wc,ClassName,Picon,pColorRGB)\
			WNDCLASSEX wc;\
			wc.cbSize	=sizeof(WNDCLASSEX);\
			wc.style	=CS_HREDRAW | CS_VREDRAW;\
			wc.lpfnWndProc	=WndProc;\
			wc.cbClsExtra	=0;\
			wc.cbWndExtra	=0;\
			wc.hInstance	=hInstance;\
			wc.hIcon	=LoadIcon (hInstance, MAKEINTRESOURCE(Picon)) ;\
			wc.hCursor	=LoadCursor(NULL, IDC_ARROW);\
			wc.hbrBackground=CreateSolidBrush(pColorRGB);\
			wc.lpszMenuName	=MAKEINTRESOURCE(PM_STDM);\
			wc.lpszClassName=ClassName;\
			wc.hIconSm	=LoadIcon(hInstance, MAKEINTRESOURCE(Picon));

#define pRegisterClass(wc)\
		if(!RegisterClassEx(&wc)){\
			MessageBox(NULL, "Window Registration Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);\
			return 0;\
		}

#define pCreateWindow(hwnd,ClassName,WindowName)\
		hwnd=CreateWindowEx(\
			WS_EX_CLIENTEDGE,\
			ClassName,\
			WindowName,\
			WS_OVERLAPPEDWINDOW,\
			CW_USEDEFAULT, CW_USEDEFAULT, 1025, 525,\
			NULL, NULL, hInstance, NULL);\
		if(hwnd == NULL){\
			MessageBox(NULL, "Window Creation Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);\
			return 0;\
		}

#define pGetMessage(Msg)\
		while(GetMessage(&Msg, NULL, 0, 0) > 0){\
			TranslateMessage(&Msg);\
			DispatchMessage(&Msg);\
		}

#define pDrawTextEx0(hwnd,text){\
		HDC dt0_hdc;\
		PAINTSTRUCT dt0_ps;\
		RECT dt0_rect;\
		dt0_hdc=BeginPaint(hwnd,&dt0_ps);\
		GetClientRect(hwnd,&dt0_rect);\
		DrawTextEx(dt0_hdc,text,-1,&dt0_rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER,NULL);\
		EndPaint(hwnd,&dt0_ps);\
	}

#define pExeName(FileName) GetModuleFileName(GetModuleHandle(NULL), FileName, MAX_PATH);

#define pinkwinA() pWinClass(_P_win_class_,"_P_pink_value_");\
		pinkwin(){\
			pinkwc(wc,_P_win_class_,PI_WH,pRGB(0x2095f3));\
			pRegisterClass(wc);\
			HWND hwnd;\
			{\
				char exePathName[MAX_PATH+32], P_flag_str[32]=" - WhiteHat -0.99";\
				pExeName(exePathName);\
				strcat(exePathName,P_flag_str);\
				pCreateWindow(hwnd,_P_win_class_,exePathName);\
			}\
			ShowWindow(hwnd,nCmdShow);\
			UpdateWindow(hwnd);\
			MSG Msg;\
			pGetMessage(Msg);\
			return Msg.wParam;\
		}

#define pGetWindowWH(hwnd,width,height){\
		RECT rect;\
		GetWindowRect(hwnd,&rect);\
		width=rect.right-rect.left, height=rect.bottom-rect.top;\
	}

#define pGetClientWH(hwnd,width,height){\
		RECT rect;\
		GetClientRect(hwnd,&rect);\
		width=rect.right-rect.left, height=rect.bottom-rect.top;\
	}

#define pGetLastError(){\
		char pErrorCode[16];\
		sprintf(pErrorCode,"%d",GetLastError());\
		MessageBox(hwnd,pErrorCode,"P Error Code",MB_OK);\
	}

void pReportErrorFunc(HWND hwnd, int pErrorCode, int ErrorCodeID, int CodeID_x)
{
	pErrorCode+=ErrorCodeID<<16;
	char pReportStr[256];
	sprintf(pReportStr, "Error Code: 0x%04X%08X\nSend the Error-Code to the Author?", CodeID_x, pErrorCode);
	int x = MessageBox(hwnd, pReportStr, "Error!  --ReportError()", MB_OKCANCEL | MB_ICONWARNING);
	if(x==IDOK){
		sprintf(pReportStr, "mailto:yongxxone@gmail.com?subject=Report Error Code(WH6.66)&body=Error Code: 0x%04X%08X%%0d%%0a%%0d%%0a%%0d%%0a%%0d%%0a", CodeID_x, pErrorCode);
		ShellExecute(hwnd, "open", pReportStr, NULL, NULL, SW_SHOWNORMAL);
	}
}

#define __ReportError(hwnd, ErrorCodeID, CodeID_x){\
		int pErrorCode=GetLastError();\
		if(pErrorCode!=0)\
			pReportErrorFunc(hwnd,pErrorCode,ErrorCodeID,CodeID_x);\
	}

#define __ReturnError(){\
		int pErrorCode=GetLastError();\
		if(pErrorCode!=0)\
			return pErrorCode;\
	}

#define pCoutInt(value){\
		char s[32];\
		sprintf(s,"value=%d, hex=0x%X",(int)(value), (int)(value));\
		MessageBox(NULL,s,"pCoutInt(value)",MB_OK);\
	}

#define pCoutDouble(value){\
		char s[64];\
		sprintf(s,"value=%Lf",(double)(value));\
		MessageBox(NULL,s,"pCoutDouble(value)",MB_OK);\
	}

#define pCoutStr(string)		MessageBox(NULL,string,"pCoutStr(string)",MB_OK)

#define pCoutFont(hdc){\
		char s[32];\
		GetTextFace(hdc,32,s);\
		MessageBox(hwnd,s,"pCoutFont(hdc)",MB_OK);\
	}

#define pSetWinFont(hwnd,defFont)	SendMessage(hwnd, WM_SETFONT, (WPARAM)defFont, (LPARAM)TRUE)

#define pSetCwinFont(hwnd,id,defFont)	SendMessage(GetDlgItem(hwnd,id), WM_SETFONT, (WPARAM)defFont, (LPARAM)TRUE)

#define pDesktopHwnd(hwnd){\
		hwnd=FindWindow("Progman","Program Manager");\
		hwnd=FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);\
		hwnd=FindWindowEx(hwnd, NULL, "SysListView32", "FolderView");\
	}

#define pKey_Win_D(){\
		keybd_event(VK_LWIN, 0, 0, 0);\
		keybd_event('D', 0, 0, 0);\
		keybd_event('D', 0, KEYEVENTF_KEYUP, 0);\
		keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);\
	}

#define p2Key(key1,key2){\
		keybd_event(key1, 0, 0, 0);\
		keybd_event(key2, 0, 0, 0);\
		keybd_event(key2, 0, KEYEVENTF_KEYUP, 0);\
		keybd_event(key1, 0, KEYEVENTF_KEYUP, 0);\
	}

#define pSetToTop(hwnd)			SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE)

#define pSetNoTop(hwnd)			SetWindowPos(hwnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE)

#define pGetAdmin(){\
		pExeName(s);\
		ShellExecute(hwnd, "runas", s, NULL, NULL, SW_SHOWNORMAL);\
		__ReportError(hwnd,0xad00,0);\
		DestroyWindow(hwnd);\
	}

#define pGetMenu2(hwnd, x)		GetSubMenu(GetMenu(hwnd), x)

#define pGetMenu3(hwnd, x, y)		GetSubMenu(pGetMenu2(hwnd,x), y)

#define pSetChecked(hwnd, x, y)		CheckMenuItem(pGetMenu2(hwnd, x), y, MF_BYPOSITION | MF_CHECKED)

#define pSetUnchecked(hwnd, x, y)	CheckMenuItem(pGetMenu2(hwnd, x), y, MF_BYPOSITION | MF_UNCHECKED)

#define pSetRadio2(hwnd, x, s, e, z)	CheckMenuRadioItem(pGetMenu2(hwnd, x), s, e, z, MF_BYPOSITION)

#define pSetRadio3(hwnd, x, y, s, e, z)	CheckMenuRadioItem(pGetMenu3(hwnd, x, y), s, e, z, MF_BYPOSITION)

#define pSetChecked3(hwnd, x, y, z)	CheckMenuItem(pGetMenu3(hwnd, x, y), z, MF_BYPOSITION | MF_CHECKED)

#define pSetUnchecked3(hwnd, x, y, z)	CheckMenuItem(pGetMenu3(hwnd, x, y), z, MF_BYPOSITION | MF_UNCHECKED)

#define pGetScreenWH(x, y){\
		x=GetSystemMetrics(SM_CXSCREEN);\
		y=GetSystemMetrics(SM_CYSCREEN);\
	}

#define pTaskbarHwnd()			FindWindow("Shell_traywnd", NULL)

#define pRoundDouble(doubleV)			( (long long)(doubleV+0.5) )

#define pDiv(x, y)			pRoundDouble( ((double)x) / ((double)y) )

#define pHeightCM(longv){\
		HDC hdc;\
		hdc=GetDC(NULL);\
		longv=pDiv( GetDeviceCaps(hdc,LOGPIXELSY) , 2.54 );\
		ReleaseDC(NULL, hdc);\
	}

#define pWidthCM(longv){\
		HDC hdc;\
		hdc=GetDC(NULL);\
		longv=pDiv( GetDeviceCaps(hdc,LOGPIXELSX) , 2.54 );\
		ReleaseDC(NULL, hdc);\
	}

#define pCreateFont(height, fontname)	CreateFont(height, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontname)

#define pHLWORD(hiword, loword) ( (hiword<<16) | loword )

#define pLoadBMP(ID) LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(ID), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR)

#define pRectInit(rect,x1,y1,x2,y2) rect.left=x1, rect.top=y1, rect.right=x2, rect.buttom=y2;

#ifdef __cplusplus
#define pAtoW(a,w,len) swprintf(w, len, L"%s", a)
#define pWtoA(w,a,len) sprintf(a, len, "%S", w)
#else
#define pAtoW(a,w,len) swprintf(w, len, L"%S", a)
#define pWtoA(w,a,len) sprintf(a, len, "%s", w)
#endif

#define pCreateThread(FuncProc, param) CreateThread(NULL, 0, FuncProc, param, 0, NULL);

#endif