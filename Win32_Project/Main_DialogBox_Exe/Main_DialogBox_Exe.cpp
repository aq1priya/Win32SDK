#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<wchar.h>
#include "Mathematics.h"
#include "Chemistry.h"
#include "Physics.h"
#include "Biology.h"
#include "Background.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HMODULE hMathLib = NULL;
HMODULE hChemLib = NULL;
HMODULE hPhyLib = NULL;
int i = 0;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//initialization of wndclassex
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));

	//Register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInst;
	switch (iMsg)
	{
	case WM_CREATE:
		hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
		hMathLib = LoadLibrary(TEXT("Mathematics_Explicit_Dll.dll"));
		if (hMathLib == NULL)
		{
			MessageBox(hwnd, TEXT("Mathematics dll can not be loaded"), TEXT("LoadLibrary() Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hChemLib = LoadLibrary(TEXT("Chemistry_Client_Dll.dll"));
		if (hChemLib == NULL)
		{
			MessageBox(hwnd, TEXT("Chemistry dll can not be loaded"), TEXT("LoadLibrary() Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hPhyLib = LoadLibrary(TEXT("Physics_Client_Dll.dll"));
		if (hPhyLib == NULL)
		{
			MessageBox(hwnd, TEXT("Physics dll can not be loaded"), TEXT("LoadLibrary() Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		break;

	case WM_PAINT:
	{
		HBITMAP hSplashScreenImage;
		BITMAP bmp;
		PAINTSTRUCT ps;
		RECT rc;
		HDC hdc, memdc;
		HFONT hNewFont;
		TCHAR MyFont[10];
		TCHAR batch[] = TEXT("BATCH: WinRT 2018");
		TCHAR name[] = TEXT("NAME: PRIYA SABOO");
		TCHAR GroupName[] = TEXT("GROUP NAME: WM_CLOSE");
		TCHAR message1[] = TEXT("Press Space Bar to Continue...");
		TCHAR message2[] = TEXT("Press ESC to Exit...");
		TCHAR AstroMediComp[] = TEXT("ASTROMEDICOMP");
		TCHAR ApplicationName[] = TEXT("P C B M");

		GetClientRect(hwnd, &rc);
		hSplashScreenImage = LoadBitmap(hInst, MAKEINTRESOURCE(BITMAP_SPLASHSCREEN));
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hSplashScreenImage);
		GetObject(hSplashScreenImage, sizeof(BITMAP), &bmp);
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		hNewFont = CreateFont(30, 20, 0, 0, FW_DONTCARE, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, MyFont);
		SelectObject(hdc, hNewFont);
		TextOut(hdc, 850, 50, AstroMediComp, sizeof(AstroMediComp));
		TextOut(hdc, 850, 80, GroupName, sizeof(GroupName));
		TextOut(hdc, 50, 50, name, sizeof(name));
		TextOut(hdc, 50, 80, batch, sizeof(batch));

		hNewFont = CreateFont(30, 20, 0, 0, FW_DONTCARE, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, MyFont);
		SelectObject(hdc, hNewFont);
		TextOut(hdc, 390, 615, message1, sizeof(message1));
		TextOut(hdc, 480, 645, message2, sizeof(message2));

		hNewFont = CreateFont(70, 45, 0, 0, FW_SEMIBOLD, 0, 0, 0, EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, MyFont);
		SelectObject(hdc, hNewFont);
		TextOut(hdc, 500, 350, ApplicationName, sizeof(ApplicationName));
		EndPaint(hwnd, &ps);
	}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			DialogBox(hInst, TEXT("MATHEMATICS"), hwnd, DlgProc);
			break;
		case 27:													//close window on pressing escape
			DestroyWindow(hwnd);
			break;
		}
		break;

	case WM_DESTROY:
		FreeLibrary(hPhyLib);
		FreeLibrary(hChemLib);
		FreeLibrary(hMathLib);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memhdc;
	HINSTANCE DlgInst;
	PAINTSTRUCT ps;
	RECT rc;
	static BOOL LoadDiagramFlower, LoadDiagramAmoeba, CorrectAns, Check, SwitchColorToDefault;
	static HBITMAP hBmp;
	static HBRUSH hDlgBrush,hDlgBrush1, hDlgBrushBackground, hDlgBrushEdit;
	//HGDIOBJ h;
	
	DlgInst = (HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE);
	switch (iMsg)
	{
	case WM_INITDIALOG:
		i = 1;
		//SetFocus(GetDlgItem(hDlg, ID_etFIRSTTERMAP));
		SendDlgItemMessage(hDlg, ID_RBMATHEMATICS, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(hDlg, IDR_CHEMISTRY, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(hDlg, IDR_PHYSICS, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(hDlg, IDR_BIOLOGY, BM_SETCHECK, BST_UNCHECKED, 0);
		EnableWindow(GetDlgItem(hDlg, IDR_AMOEBA), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDR_FLOWER), FALSE);
		//enable mathematics box
		EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMAP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etDIFFERENCE), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etNAP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMGP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etRATIO), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etNGP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etNTERMAP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etSUMAP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etNTERMGP), WM_ENABLE);
		EnableWindow(GetDlgItem(hDlg, ID_etSUMGP), WM_ENABLE);
		//disable physics box
		EnableWindow(GetDlgItem(hDlg, IDE_HEIGHT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_HORIZONTAL), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_STATE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_CRITICAL), FALSE);
		//disable chemistry box
		EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLUTE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLVENT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLUTE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLVENT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLUTE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLVENT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_CMASS), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_CVOLUME), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MFSOLUTE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MFSOLVENT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MOLARITY), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_MOLALITY), FALSE);
		//disable biology block
		EnableWindow(GetDlgItem(hDlg, IDE_1), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_2), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_3), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_4), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_5), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_6), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_7), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDE_8), FALSE);
		break;

	case WM_CTLCOLORSTATIC:
		//hDlgBrush1 =(HBRUSH)GetStockObject(HOLLOW_BRUSH);
		//SetBkColor((HDC)wParam, RGB(255, 255, 247));
		//SetBkMode((HDC)wParam, OPAQUE);
		//return((BOOL)h);
		hDlgBrush1 = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (i == 1)
			SetTextColor((HDC)wParam, RGB(136, 0, 27));
		else if (i == 2)
			SetTextColor((HDC)wParam, RGB(253, 236, 166));
		else if (i == 3)
			SetTextColor((HDC)wParam, RGB(255, 155, 79));
		else if (i == 4)
			SetTextColor((HDC)wParam, RGB(3, 36, 93));
		return((INT_PTR)hDlgBrush1);
		break;

	case WM_PAINT:
	{
		GetClientRect(hDlg, &rc);
		hdc = BeginPaint(hDlg, &ps);
		memhdc = CreateCompatibleDC(hdc);
		if (i==1)
		{
			hBmp = LoadBitmap(DlgInst, MAKEINTRESOURCE(BITMAP_MATHEMATICS));
			SelectObject(memhdc, hBmp); 
			BitBlt(hdc, 0, 0, rc.right, rc.bottom, memhdc, 0, 0, SRCCOPY);
			//SelectObject(hdc, hDlgBrushBackground);
			//Rectangle(hdc, 0, 0, rc.right, rc.bottom);
		}
		else if(i==2)
		{
			hBmp = LoadBitmap(DlgInst, MAKEINTRESOURCE(BITMAP_CHEMISTRY));
			SelectObject(memhdc, hBmp);
			BitBlt(hdc, 0, 0, rc.right, rc.bottom, memhdc, 0, 0, SRCCOPY);
			/*SelectObject(hdc, hDlgBrushBackground);
			Rectangle(hdc, 0, 0, rc.right, rc.bottom);*/
		}
		else if (i == 3)
		{
			hBmp = LoadBitmap(DlgInst, MAKEINTRESOURCE(BITMAP_PHYSICS));
			SelectObject(memhdc, hBmp);
			BitBlt(hdc, 0, 0, rc.right, rc.bottom, memhdc, 0, 0, SRCCOPY);
			/*SelectObject(hdc, hDlgBrushBackground);
			Rectangle(hdc, 0, 0, rc.right, rc.bottom);*/
		}
		else if (i == 4)
		{
			hBmp = LoadBitmap(DlgInst, MAKEINTRESOURCE(BITMAP_BIOLOGY));
			SelectObject(memhdc, hBmp);
			BitBlt(hdc, 0, 0, rc.right, rc.bottom, memhdc, 0, 0, SRCCOPY);
			if (LoadDiagramAmoeba)
			{
				SetTextColor(hdc, RGB(0, 0, 0));
				SetBkMode(hdc, TRANSPARENT);
				TextOut(hdc, 35, 390, TEXT("1. Cell Membrane"), 16);
				TextOut(hdc, 165, 390, TEXT("2. Nucleus"), 10);
				TextOut(hdc, 250, 390, TEXT("3. Food Vacuole"), 15);
				TextOut(hdc, 370, 390, TEXT("4. Cytoplasm"), 12);
				TextOut(hdc, 475, 390, TEXT("5. Pseudopod"), 12);
				TextOut(hdc, 250, 410, TEXT("6. Contractile Vacuole"), 22);

				HBITMAP hbmpAmoeba;
				BITMAP bmp;
				hbmpAmoeba = LoadBitmap(DlgInst, MAKEINTRESOURCE(BITMAP_AMOEBA));
				memhdc = CreateCompatibleDC(hdc);
				SelectObject(memhdc, hbmpAmoeba);
				GetObject(hbmpAmoeba, sizeof(BITMAP), &bmp);
				BitBlt(hdc, 176, 450, bmp.bmWidth, bmp.bmHeight, memhdc, 0, 0, SRCCOPY);
			}
			if (LoadDiagramFlower)
			{
				HBITMAP hbmpFlower;
				BITMAP bmp;

				//load bitmap image of parts of flower
				hbmpFlower = LoadBitmap(DlgInst, MAKEINTRESOURCE(BITMAP_FLOWER));

				//lists the names of parts of flower
				SetTextColor(hdc, RGB(0, 0, 0));
				SetBkMode(hdc, TRANSPARENT);
				TextOut(hdc, 35, 390, TEXT("1. Stigma"), 10);
				TextOut(hdc, 105, 390, TEXT("2. Anther"), 10);
				TextOut(hdc, 175, 390, TEXT("3. Petals"), 10);
				TextOut(hdc, 245, 390, TEXT("4. Sepal"), 10);
				TextOut(hdc, 315, 390, TEXT("5. Stem"), 7);
				TextOut(hdc, 380, 390, TEXT("6. Filament"), 12);
				TextOut(hdc, 460, 390, TEXT("7. Ovary"), 8);
				TextOut(hdc, 530, 390, TEXT("8. Style"), 9);

				//show diagram of flower
				memhdc = CreateCompatibleDC(hdc);
				SelectObject(memhdc, hbmpFlower);
				GetObject(hbmpFlower, sizeof(BITMAP), &bmp);
				BitBlt(hdc, 176, 430, bmp.bmWidth, bmp.bmHeight, memhdc, 0, 0, SRCCOPY);
				ReleaseDC(hDlg, hdc);
			}
			/*SelectObject(hdc, hDlgBrushBackground);
			Rectangle(hdc, 0, 0, rc.right, rc.bottom);*/
		}
		
		EndPaint(hDlg, &ps);
	}
		break;

	case WM_CTLCOLOREDIT:
		if (i == 1)
		{
			SetBkColor((HDC)wParam, RGB(255, 250, 196));
			hDlgBrushEdit = CreateSolidBrush(RGB(255, 250, 196));
		}
		else if (i == 2)
		{
			SetBkColor((HDC)wParam, RGB(252, 209, 255));
			hDlgBrushEdit = CreateSolidBrush(RGB(252, 209, 255));
		}
		else if (i == 3)
		{
			SetBkColor((HDC)wParam, RGB(184, 243, 255));
			hDlgBrushEdit = CreateSolidBrush(RGB(184, 243, 255));
		}
		else if (i == 4)
		{
			SetBkColor((HDC)wParam, RGB(226, 182, 238));
			hDlgBrushEdit = CreateSolidBrush(RGB(226, 182, 238));
			if ((CorrectAns==TRUE) && (Check==TRUE))
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
				hDlgBrushEdit = CreateSolidBrush(RGB(0, 255, 0));
			}
			else if ((CorrectAns == FALSE) && (Check == TRUE))
			{
				SetBkColor((HDC)wParam, RGB(255, 0, 0));
				hDlgBrushEdit = CreateSolidBrush(RGB(255, 0, 0));
			}
			else if (SwitchColorToDefault == TRUE) 
			{
				SetBkColor((HDC)wParam, RGB(226, 182, 238));
				hDlgBrushEdit = CreateSolidBrush(RGB(226, 182, 238));
			}
		}
		return((INT_PTR)hDlgBrushEdit);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_RBMATHEMATICS:
		{
			i = 1;
			hDlgBrushBackground = CreateSolidBrush(RGB(255, 203, 71));
			InvalidateRect(hDlg, NULL, TRUE);
			SendDlgItemMessage(hDlg, IDR_CHEMISTRY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_PHYSICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_BIOLOGY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_FLOWER, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_AMOEBA, BM_SETCHECK, BST_UNCHECKED, 0);
			EnableWindow(GetDlgItem(hDlg, IDR_FLOWER), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDR_AMOEBA), FALSE);
			//enable mathematics box
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMAP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etDIFFERENCE), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etNAP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMGP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etRATIO), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etNGP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMAP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMAP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMGP), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMGP), WM_ENABLE);
			//disable physics box
			EnableWindow(GetDlgItem(hDlg, IDE_HEIGHT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_HORIZONTAL), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_STATE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CRITICAL), FALSE);
			//disable chemistry box
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CMASS), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CVOLUME), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLARITY), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLALITY), FALSE);
			//disable biology block
			EnableWindow(GetDlgItem(hDlg, IDE_1), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_2), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_3), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_4), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_5), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_6), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_7), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_8), FALSE);
		}
		break;

		case IDR_CHEMISTRY:
			i = 2;
			//hDlgBrushBackground = CreateSolidBrush(RGB(233, 143, 255));
			InvalidateRect(hDlg, NULL, TRUE);
			SendDlgItemMessage(hDlg, ID_RBMATHEMATICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_PHYSICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_BIOLOGY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_FLOWER, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_AMOEBA, BM_SETCHECK, BST_UNCHECKED, 0);
			EnableWindow(GetDlgItem(hDlg, IDR_FLOWER), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDR_AMOEBA), FALSE);
			//enable chemistry box
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLUTE), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLVENT), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLUTE), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLVENT), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLUTE), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLVENT), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_CMASS), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_CVOLUME), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLUTE), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLVENT), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLARITY), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLALITY), WM_ENABLE);
			//disable physics box
			EnableWindow(GetDlgItem(hDlg, IDE_HEIGHT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_HORIZONTAL), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_STATE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CRITICAL), FALSE);
			//disable mathematics box
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etDIFFERENCE), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etRATIO), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMGP), FALSE);
			//disable biology block
			EnableWindow(GetDlgItem(hDlg, IDE_1), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_2), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_3), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_4), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_5), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_6), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_7), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_8), FALSE);
			break;

		case IDR_PHYSICS:
			i = 3;
			hDlgBrushBackground = CreateSolidBrush(RGB(255, 143, 143));
			InvalidateRect(hDlg, NULL, TRUE);
			SendDlgItemMessage(hDlg, ID_RBMATHEMATICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_CHEMISTRY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_BIOLOGY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_FLOWER, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_AMOEBA, BM_SETCHECK, BST_UNCHECKED, 0);
			//enable physics box
			EnableWindow(GetDlgItem(hDlg, IDE_HEIGHT), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_HORIZONTAL), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_STATE), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_CRITICAL), WM_ENABLE);
			//disable mathematics box
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etDIFFERENCE), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etRATIO), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMGP), FALSE);
			//disable chemistry box
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CMASS), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CVOLUME), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLARITY), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLALITY), FALSE);
			//disable biology block
			EnableWindow(GetDlgItem(hDlg, IDE_1), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_2), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_3), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_4), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_5), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_6), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_7), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_8), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDR_FLOWER), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDR_AMOEBA), FALSE);
			break;

		case IDR_BIOLOGY:
			i = 4;
			hDlgBrushBackground = CreateSolidBrush(RGB(153, 255, 190));
			InvalidateRect(hDlg, NULL, TRUE);
			SendDlgItemMessage(hDlg, ID_RBMATHEMATICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_CHEMISTRY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_PHYSICS, BM_SETCHECK, BST_UNCHECKED, 0);
			EnableWindow(GetDlgItem(hDlg, IDR_FLOWER), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDR_AMOEBA), WM_ENABLE);
			SendDlgItemMessage(hDlg, IDR_FLOWER, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_AMOEBA, BM_SETCHECK, BST_UNCHECKED, 0);
			//enable biology block
			EnableWindow(GetDlgItem(hDlg, IDE_1), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_2), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_3), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_4), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_5), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_6), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_7), WM_ENABLE);
			EnableWindow(GetDlgItem(hDlg, IDE_8), WM_ENABLE);
			//disable physics box
			EnableWindow(GetDlgItem(hDlg, IDE_HEIGHT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_HORIZONTAL), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_STATE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CRITICAL), FALSE);
			//disable mathematics box
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etDIFFERENCE), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etFIRSTTERMGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etRATIO), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMAP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etNTERMGP), FALSE);
			EnableWindow(GetDlgItem(hDlg, ID_etSUMGP), FALSE);
			//disable chemistry box
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MASSSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_VOLUMESOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLESSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CMASS), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_CVOLUME), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLUTE), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MFSOLVENT), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLARITY), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDE_MOLALITY), FALSE);
			break;

		case IDP_MATHS:
		{
			//locally declared variables
			float fAPFirstTerm, fCommonDifference, fGPFirstTerm, fRatio, iN;
			float APnthTerm, APSum, GPnthTerm;
			double GPSum;
			char a[20], d[10], n[10], ga[20], r[20], gn[20], buff[40], buffgp[40];
			WCHAR buffer[40];
			size_t num;
			typedef float(*pfnMathFunction)(float, float, float);
			typedef double(*pfnMathFunction2)(float, float, float);
			pfnMathFunction pfnAP_nthTerm, pfnAP_SumOfSeries, pfnGP_nthTerm;
			pfnMathFunction2 pfnGP_SumOfSeries;
			pfnAP_nthTerm = NULL;
			pfnAP_SumOfSeries = NULL;
			pfnGP_nthTerm = NULL;
			pfnGP_SumOfSeries = NULL;
			pfnAP_nthTerm = (pfnMathFunction)GetProcAddress(hMathLib, "AP_nthTerm");
			pfnAP_SumOfSeries = (pfnMathFunction)GetProcAddress(hMathLib, "AP_SumOfSeries");
			pfnGP_nthTerm = (pfnMathFunction)GetProcAddress(hMathLib, "GP_nthTerm");
			pfnGP_SumOfSeries = (pfnMathFunction2)GetProcAddress(hMathLib, "GP_SumOfSeries");

			//get the user entered first term of AP
			GetDlgItemText(hDlg, ID_etFIRSTTERMAP, a, 20);
			fAPFirstTerm = (float)(atof(a));

			//get the user entered common difference of AP
			GetDlgItemText(hDlg, ID_etDIFFERENCE, d, 10);
			fCommonDifference = (float)(atof(d));

			//get the user entered value of n of AP
			GetDlgItemText(hDlg, ID_etNAP, n, 20);
			iN = (float)(atof(n));

			APnthTerm = pfnAP_nthTerm(fAPFirstTerm, fCommonDifference, iN);
			swprintf(buffer, 40, L"%.2f ", APnthTerm);
			wcstombs_s(&num, buff, buffer, 40);
			SetDlgItemText(hDlg, ID_etNTERMAP, buff);

			APSum = pfnAP_SumOfSeries(fAPFirstTerm, fCommonDifference, iN);
			swprintf(buffer, 40, L"%.2f", APSum);
			wcstombs_s(&num, buff, buffer, 40);
			SetDlgItemText(hDlg, ID_etSUMAP, buff);

			//get the user entered first term of GP
			GetDlgItemText(hDlg, ID_etFIRSTTERMGP, ga, 20);
			fGPFirstTerm = (float)(atof(ga));

			//get the user entered common difference of GP
			GetDlgItemText(hDlg, ID_etRATIO, r, 10);
			fRatio = (float)(atof(r));

			//get the user entered value of n of GP
			GetDlgItemText(hDlg, ID_etNGP, gn, 20);
			iN = (float)(atof(gn));

			GPnthTerm = pfnGP_nthTerm(fGPFirstTerm, fRatio, iN);
			swprintf(buffer, 40, L"%.2f ", GPnthTerm);
			wcstombs_s(&num, buffgp, buffer, 40);
			SetDlgItemText(hDlg, ID_etNTERMGP, buffgp);

			GPSum = pfnGP_SumOfSeries(fGPFirstTerm, fRatio, iN);
			swprintf(buffer, 40, L"%.2f", GPSum);
			wcstombs_s(&num, buffgp, buffer, 40);
			SetDlgItemText(hDlg, ID_etSUMGP, buffgp);
		}
			break;

		case IDP_CHEMISTRY:
		{
			typedef void(*pfnCOMFunction)(void);
			typedef float(*pfnChemistryFunction3)(float, float, float);
			typedef float(*pfnChemistryFunction2)(float, float);
			pfnCOMFunction pfn_InitializeCOM, pfn_UninitializeCOM;
			pfnChemistryFunction3 pfn_Molarity, pfn_Molality;
			pfnChemistryFunction2 pfn_ConcentrationByMassOfSolute, pfn_ConcentrationByVolumeOfSolute;
			pfnChemistryFunction2 pfn_MoleFractionOfSolute, pfn_MoleFractionOfSolvent;

			pfn_InitializeCOM = NULL;
			pfn_UninitializeCOM = NULL;
			pfn_Molarity = NULL;
			pfn_Molality = NULL;
			pfn_ConcentrationByMassOfSolute = NULL;
			pfn_ConcentrationByVolumeOfSolute = NULL;
			pfn_MoleFractionOfSolute = NULL;
			pfn_MoleFractionOfSolvent = NULL;
			pfn_InitializeCOM = (pfnCOMFunction)GetProcAddress(hChemLib, "InitializeCOM");
			pfn_UninitializeCOM = (pfnCOMFunction)GetProcAddress(hChemLib, "UnInitializeCOM");
			pfn_ConcentrationByMassOfSolute = (pfnChemistryFunction2)GetProcAddress(hChemLib,
				"CalculateConcentrationByMass");
			pfn_ConcentrationByVolumeOfSolute = (pfnChemistryFunction2)GetProcAddress(hChemLib,
				"CalculateConcentrationByVolume");
			pfn_MoleFractionOfSolute = (pfnChemistryFunction2)GetProcAddress(hChemLib, "CalculateMoleFractionOfSolute");
			pfn_MoleFractionOfSolvent = (pfnChemistryFunction2)GetProcAddress(hChemLib, "CalculateMoleFractionOfSolvent");
			pfn_Molarity = (pfnChemistryFunction3)GetProcAddress(hChemLib, "CalculateMolarity");
			pfn_Molality = (pfnChemistryFunction3)GetProcAddress(hChemLib, "CalculateMolality");

			//Local variable to get user entered values
			char localbuffer[25];
			WCHAR ChemBuffer[25];
			size_t chem;

			//get user entered Mass of solute
			char cSoluteMass[25];
			float fSoluteMass;
			GetDlgItemText(hDlg, IDE_MASSSOLUTE, cSoluteMass, 25);
			fSoluteMass = (float)(atof(cSoluteMass));

			//get the user entered volume of Solute
			char cSoluteVolume[25];
			float fSoluteVolume;
			GetDlgItemText(hDlg, IDE_VOLUMESOLUTE, cSoluteVolume, 25);
			fSoluteVolume = (float)(atof(cSoluteVolume));

			//get the user entered moles of solute
			char cSoluteMoles[25];
			float fSoluteMoles;
			GetDlgItemText(hDlg, IDE_MOLESSOLUTE, cSoluteMoles, 25);
			fSoluteMoles = (float)(atof(cSoluteMoles));

			//get the user entered mass of solvent
			char cSolventMass[25];
			float fSolventMass;
			GetDlgItemText(hDlg, IDE_MASSSOLVENT, cSolventMass, 25);
			fSolventMass = (float)(atof(cSolventMass));

			//get the user entered volume of solvent
			char cSolventVolume[25];
			float fSolventVolume;
			GetDlgItemText(hDlg, IDE_VOLUMESOLVENT, cSolventVolume, 25);
			fSolventVolume = (float)(atof(cSolventVolume));

			//get the user entered Moles of Solvent
			char cSolventMoles[25];
			float fSolventMoles;
			GetDlgItemText(hDlg, IDE_MOLESSOLVENT, cSolventMoles, 25);
			fSolventMoles = (float)(atof(cSolventMoles));

			//Initialize Com
			pfn_InitializeCOM();

			/*Find solution Concentration in terms of percentage of mass of solute
			by calling pfn_ConcentrationByMassOfSolute()*/
			float fPercentageByMassOfSolute;
			fPercentageByMassOfSolute = pfn_ConcentrationByMassOfSolute(fSoluteMass, fSolventMass);
			swprintf(ChemBuffer, 25, L"%.2f", fPercentageByMassOfSolute);
			wcstombs_s(&chem, localbuffer, ChemBuffer, 25);
			SetDlgItemText(hDlg, IDE_CMASS, localbuffer);


			/*Find solution Concentration in terms of percentage of volume of solute
			by calling pfn_ConcentrationByVolumeOfSolute()*/
			float fPercentageByVolumeOfSolute;
			fPercentageByVolumeOfSolute = pfn_ConcentrationByVolumeOfSolute(fSoluteVolume, fSolventVolume);
			swprintf(ChemBuffer, 25, L"%.2f", fPercentageByVolumeOfSolute);
			wcstombs_s(&chem, localbuffer, ChemBuffer, 25);
			SetDlgItemText(hDlg, IDE_CVOLUME, localbuffer);

			/*Find MoleFraction of solute by calling pfn_MoleFractionOfSolute()*/
			float fMoleFractionOfSolute;
			fMoleFractionOfSolute = pfn_MoleFractionOfSolute(fSoluteMoles, fSolventMoles);
			swprintf(ChemBuffer, 25, L"%.2f", fMoleFractionOfSolute);
			wcstombs_s(&chem, localbuffer, ChemBuffer, 25);
			SetDlgItemText(hDlg, IDE_MFSOLUTE, localbuffer);

			/*Find MoleFraction of solvent by calling pfn_MoleFractionOfSolvent()*/
			float fMoleFractionOfSolvent;
			fMoleFractionOfSolvent = pfn_MoleFractionOfSolvent(fSoluteMoles, fSolventMoles);
			swprintf(ChemBuffer, 25, L"%.2f", fMoleFractionOfSolvent);
			wcstombs_s(&chem, localbuffer, ChemBuffer, 25);
			SetDlgItemText(hDlg, IDE_MFSOLVENT, localbuffer);

			/*Find Molarity by calling pfn_Molarity()*/
			float fMolarityOfSolution;
			fMolarityOfSolution = pfn_Molarity(fSoluteMoles, fSoluteVolume, fSolventVolume);
			swprintf(ChemBuffer, 25, L"%.2f", fMolarityOfSolution);
			wcstombs_s(&chem, localbuffer, ChemBuffer, 25);
			SetDlgItemText(hDlg, IDE_MOLARITY, localbuffer);

			/*Find Molality by calling pfn_Molality()*/
			float fMolalityOfSolution;
			fMolalityOfSolution = pfn_Molality(fSoluteMoles, fSoluteMass, fSolventMass);
			swprintf(ChemBuffer, 25, L"%.2f", fMolalityOfSolution);
			wcstombs_s(&chem, localbuffer, ChemBuffer, 25);
			SetDlgItemText(hDlg, IDE_MOLALITY, localbuffer);

			//Uninitialize com
			pfn_UninitializeCOM();
		}
			break;

		case IDP_PHYSICS:
		{
			float HorizontalVelocity, Height;
			typedef void(*PhyCOMFunction)(void);
			typedef float(*PhysicsFunction)(float);
			PhyCOMFunction pfn_PhyInitializeCOM, pfn_PhyUninitializeCOM;
			PhysicsFunction pfn_CriticalVelocity;

			pfn_PhyInitializeCOM = NULL;
			pfn_PhyUninitializeCOM = NULL;
			pfn_CriticalVelocity = NULL;
			pfn_PhyInitializeCOM = (PhyCOMFunction)GetProcAddress(hPhyLib, "InitializeCOM");
			pfn_PhyUninitializeCOM = (PhyCOMFunction)GetProcAddress(hPhyLib, "UninitializeCOM");
			pfn_CriticalVelocity = (PhysicsFunction)GetProcAddress(hPhyLib, "CallCriticalVelocity");

			//get user entered height of projection
			char h[25];
			//WCHAR HVelocity[25];
			GetDlgItemText(hDlg, IDE_HEIGHT, h, 25);
			Height = (float)atof(h);
			//size_t hori;

			//get user entered velocity
			char Vh[25], Vc[25];
			GetDlgItemText(hDlg, IDE_HORIZONTAL, Vh, 25);
			HorizontalVelocity = (float)atof(Vh);
			

			//Innitialize COM
			pfn_PhyInitializeCOM();

			//call function to calculate critical velocity
			float CriticalVelocity;
			float EscapeVelocity = 11.2f;//km/s
			WCHAR velocity[25];
			size_t phy;

			CriticalVelocity = pfn_CriticalVelocity(Height);
			CriticalVelocity = CriticalVelocity / 1000;
			//set result
			swprintf(velocity, sizeof(velocity), L"%.2f", CriticalVelocity);
			wcstombs_s(&phy, Vc, velocity, 25);
			SetDlgItemText(hDlg, IDE_CRITICAL, Vc);
			CriticalVelocity = (float)atof(Vc);

			TCHAR str[255];
			if (HorizontalVelocity < CriticalVelocity)
			{
				wsprintf(str, TEXT("Satellite will fall back on earth describing a spiral path."));
				SetDlgItemText(hDlg, IDE_STATE, str);
			}
			else if (HorizontalVelocity == CriticalVelocity)
			{
				wsprintf(str, TEXT("Satellite will revolve in a stable circular orbit arround the earth."));
				SetDlgItemText(hDlg, IDE_STATE, str);
			}
			else if ((HorizontalVelocity > CriticalVelocity) && (HorizontalVelocity < EscapeVelocity))
			{
				wsprintf(str, TEXT("Satellite will revolve in elliptical orbit with point of projection at perigee."));
				SetDlgItemText(hDlg, IDE_STATE, str);
			}
			else if (HorizontalVelocity == EscapeVelocity)
			{
				wsprintf(str, TEXT("Satellite will escape from earth's gravitational force describing a parabola."));
				SetDlgItemText(hDlg, IDE_STATE, str);
			}
			else if (HorizontalVelocity > EscapeVelocity)
			{
				wsprintf(str, TEXT("Satellite will escape from earth's gravitational force describing a hyperbola."));
				SetDlgItemText(hDlg, IDE_STATE, str);
			}
			//Uninitialize COM
			pfn_PhyUninitializeCOM();
		}
			break;

		case IDR_AMOEBA:
		{
			for (int ide_1 = 157; ide_1 <= 162; ide_1++)
			{
				Check = FALSE;
				SwitchColorToDefault = TRUE;
				SetFocus(GetDlgItem(hDlg, ide_1));
			}
			SetWindowText(GetDlgItem(hDlg, IDE_1), "");
			SetWindowText(GetDlgItem(hDlg, IDE_2), "");
			SetWindowText(GetDlgItem(hDlg, IDE_3), "");
			SetWindowText(GetDlgItem(hDlg, IDE_4), "");
			SetWindowText(GetDlgItem(hDlg, IDE_5), "");
			SetWindowText(GetDlgItem(hDlg, IDE_6), "");
			SetWindowText(GetDlgItem(hDlg, IDE_7), "");
			SetWindowText(GetDlgItem(hDlg, IDE_8), "");
			SendDlgItemMessage(hDlg, ID_RBMATHEMATICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_CHEMISTRY, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_BIOLOGY, BM_SETCHECK, BST_CHECKED, 0);
			LoadDiagramAmoeba = TRUE;
			LoadDiagramFlower = FALSE;
			MessageBox(hDlg,
				TEXT("Write the correct answers in text boxes, according to serial number from given figure"),
				TEXT("README"), MB_OK);
			ShowWindow(GetDlgItem(hDlg, IDS_SEVEN), SW_HIDE);
			ShowWindow(GetDlgItem(hDlg, IDS_EIGHT), SW_HIDE);
			ShowWindow(GetDlgItem(hDlg, IDE_7), SW_HIDE);
			ShowWindow(GetDlgItem(hDlg, IDE_8), SW_HIDE);
			InvalidateRect(hDlg, NULL, TRUE);
		}
			break;

		case IDR_FLOWER:
		{
			for (int ide_1 = 157; ide_1 <= 162; ide_1++)
			{
				Check = FALSE;
				SwitchColorToDefault = TRUE;
				SetFocus(GetDlgItem(hDlg, ide_1));
			}
			SetWindowText(GetDlgItem(hDlg, IDE_1), "");
			SetWindowText(GetDlgItem(hDlg, IDE_2), "");
			SetWindowText(GetDlgItem(hDlg, IDE_3), "");
			SetWindowText(GetDlgItem(hDlg, IDE_4), "");
			SetWindowText(GetDlgItem(hDlg, IDE_5), "");
			SetWindowText(GetDlgItem(hDlg, IDE_6), "");
			SetWindowText(GetDlgItem(hDlg, IDE_7), "");
			SetWindowText(GetDlgItem(hDlg, IDE_8), "");
			SendDlgItemMessage(hDlg, IDR_BIOLOGY, BM_SETCHECK, BST_CHECKED, 0);
			SendDlgItemMessage(hDlg, ID_RBMATHEMATICS, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDR_CHEMISTRY, BM_SETCHECK, BST_UNCHECKED, 0);
			LoadDiagramFlower = TRUE;
			LoadDiagramAmoeba = FALSE;
			MessageBox(hDlg,
				TEXT("Write the correct answers in text boxes, according to serial number from given figure"),
				TEXT("README"), MB_OK);
			ShowWindow(GetDlgItem(hDlg, IDS_SEVEN), SW_SHOW);
			ShowWindow(GetDlgItem(hDlg, IDS_EIGHT), SW_SHOW);
			ShowWindow(GetDlgItem(hDlg, IDE_7), SW_SHOW);
			ShowWindow(GetDlgItem(hDlg, IDE_8), SW_SHOW);
			InvalidateRect(hDlg, NULL, TRUE);
		}
			break;

		case IDP_CHECK:
		{
			//TCHAR str[255];
			TCHAR UserAnswer[50];

			//Actual answers of Amoeba diagram
			const char *ActualAnswerOfAmoeba[] = { "Cell Membrane","Contractile Vacuole","Pseudopod","Food Vacuole","Cytoplasm","Nucleus" };
			//Actual answers of Flower diagram
			const char *ActualAnswerOfFlower[] = { "Petals","Stigma","Anther","Style","Filament", "Ovary","Sepal", "Stem" };

			//Check answers of Parts of Amoeba
			if (IsDlgButtonChecked(hDlg, IDR_AMOEBA))
			{
				Check = TRUE;
				int i = 0, check=0;
				for (int ide_1 = 157; ide_1 <= 162; ide_1++)
				{
					GetDlgItemText(hDlg, ide_1, UserAnswer, 50);
					if (_strcmpi(UserAnswer, ActualAnswerOfAmoeba[i]) != 0)
					{
						SwitchColorToDefault = FALSE;
						CorrectAns = FALSE;
						check++;
						SetFocus(GetDlgItem(hDlg, ide_1));
					}
					else
					{
						SwitchColorToDefault = FALSE;
						CorrectAns = TRUE;
						SetFocus(GetDlgItem(hDlg, ide_1));
					}
					i++;
				}
				CorrectAns = TRUE;
				if (check == 0)
				{
					MessageBox(hDlg, TEXT("All answers are correct"), TEXT("Good Job!!!"), MB_OK);
				}
			}

			//Check answers of parts of flower
			if (IsDlgButtonChecked(hDlg, IDR_FLOWER))
			{
				Check = TRUE;
				int i = 0, check = 0;
				for (int ide_1 = 157; ide_1 <= 164; ide_1++)
				{
					GetDlgItemText(hDlg, ide_1, UserAnswer, 50);
					if (_strcmpi(UserAnswer, ActualAnswerOfFlower[i]) != 0)
					{
						SwitchColorToDefault = FALSE;
						CorrectAns = FALSE;
						check++;
						SetFocus(GetDlgItem(hDlg, ide_1));
					}
					else
					{
						SwitchColorToDefault = FALSE;
						CorrectAns = TRUE;
						SetFocus(GetDlgItem(hDlg, ide_1));
					}
					i++;
				}
				if (check == 0)
				{
					MessageBox(hDlg, TEXT("All answers are correct"), TEXT("Good Job!!!"), MB_OK);
				}
				CorrectAns = TRUE;
			}
		}
			break;

		case IDP_CLEARMATH:
			//clear input output edit boxes of maths groupbox
			SetWindowText(GetDlgItem(hDlg, ID_etFIRSTTERMAP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etDIFFERENCE), "");
			SetWindowText(GetDlgItem(hDlg, ID_etNAP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etFIRSTTERMGP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etRATIO), "");
			SetWindowText(GetDlgItem(hDlg, ID_etNGP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etNTERMAP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etSUMAP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etNTERMGP), "");
			SetWindowText(GetDlgItem(hDlg, ID_etSUMGP), "");
			break;

		case IDP_CLEARCHEM:
			//clear input output edit boxes of chemistry groupbox
			SetWindowText(GetDlgItem(hDlg, IDE_MASSSOLUTE), "");
			SetWindowText(GetDlgItem(hDlg, IDE_VOLUMESOLUTE), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MOLESSOLUTE), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MASSSOLVENT), "");
			SetWindowText(GetDlgItem(hDlg, IDE_VOLUMESOLVENT), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MOLESSOLVENT), "");
			SetWindowText(GetDlgItem(hDlg, IDE_CMASS), "");
			SetWindowText(GetDlgItem(hDlg, IDE_CVOLUME), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MFSOLUTE), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MFSOLVENT), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MOLARITY), "");
			SetWindowText(GetDlgItem(hDlg, IDE_MOLALITY), "");
			break;

		case IDP_CLEARPHY:
			//clear input output edit boxes of physics groupbox
			SetWindowText(GetDlgItem(hDlg, IDE_HEIGHT), "");
			SetWindowText(GetDlgItem(hDlg, IDE_HORIZONTAL), "");
			SetWindowText(GetDlgItem(hDlg, IDE_CRITICAL), "");
			SetWindowText(GetDlgItem(hDlg, IDE_STATE), "");
			break;

		case IDP_CLEARBIO:
			for (int ide_1 = 157; ide_1 <= 162; ide_1++)
			{
				Check = FALSE;
				SwitchColorToDefault = TRUE;
				SetFocus(GetDlgItem(hDlg, ide_1));
			}
			SetWindowText(GetDlgItem(hDlg, IDE_1), "");
			SetWindowText(GetDlgItem(hDlg, IDE_2), "");
			SetWindowText(GetDlgItem(hDlg, IDE_3), "");
			SetWindowText(GetDlgItem(hDlg, IDE_4), "");
			SetWindowText(GetDlgItem(hDlg, IDE_5), "");
			SetWindowText(GetDlgItem(hDlg, IDE_6), "");
			SetWindowText(GetDlgItem(hDlg, IDE_7), "");
			SetWindowText(GetDlgItem(hDlg, IDE_8), "");
			break;

		case IDCANCEL:
			DeleteObject(hDlgBrush);
			DeleteObject(hDlgBrush1);
			EndDialog(hDlg, 0);
			break;
		}
		return(TRUE);
		break;
	}
	return(FALSE);
}
