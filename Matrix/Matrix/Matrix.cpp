// Matrix.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <string>
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
bool isAMatrix = true;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MATRIX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MATRIX));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MATRIX));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MATRIX);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmId == IDD_INPUTB)
		{
			isAMatrix = false;
		}
		if (wmId == IDD_INPUTA)
		{
			isAMatrix = true;
		}
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			DialogBox(hInst, MAKEINTRESOURCE(wmId), hWnd, DlgProc);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:  /* сообщение о создании диалога */
	case WM_CREATE:
		if (LOWORD(wp) == IDD_MN4)
		{
			SendDlgItemMessage(hDlg, 20, CB_ADDSTRING, NULL, (LPARAM)"A");
			SendDlgItemMessage(hDlg, 20, CB_ADDSTRING, NULL, (LPARAM)"B");
		}
		
		return TRUE;
	case WM_COMMAND:    /* сообщение от управляющих элементов */
		if (LOWORD(wp) == IDOK) EndDialog(hDlg, 0);
		
		if (LOWORD(wp) == BTN_SETSIZE)
		{
			char bufI[3];
			char bufJ[3];
			GetDlgItemTextA(hDlg, I_SIZE, bufI, 3);
			GetDlgItemTextA(hDlg, J_SIZE, bufJ, 3);
			int imax = atoi(bufI);
			int jmax = atoi(bufJ);
			if (imax == 0 || jmax == 0)
			{
				MessageBox(hDlg, "Невозможно задать матрицу указанной размерности! Введите корректные данные!", "Ошибка!", MB_OK | MB_ICONWARNING);
			}
			if ((imax > 10) || (jmax > 10))
			{
				if (imax > 10)
				{
					SetDlgItemTextA(hDlg, I_SIZE, "10");
					imax = 10;
				}
				if (jmax > 10)
				{
					SetDlgItemTextA(hDlg, J_SIZE, "10");
					jmax = 10;
				}
				MessageBox(hDlg, "Количество строк/столбцов не должно превышать 10! Размер матрицы был изменен", "Ошибка", MB_OK | MB_ICONINFORMATION);
			}
			for (int i = 0; i < imax; i++)
			{
				for (int j = 0; j < jmax; j++)
				{
					CreateWindow("edit", "0", WS_CHILD | WS_VISIBLE , 235+(15*i), 130+(15*j), 15, 15, hDlg, (HMENU)(310+i+j), NULL, NULL);
				}
				int x = 0;
				x++;
			}
			if (isAMatrix)
			{
				//заполняем матрицу А
			}
			else
			{
				//заполняем матрицу В
			}
		}

		if (LOWORD(wp) == BTN_MN4)
		{
			char buf[255];
			long x = 0;
			GetDlgItemTextA(hDlg, 21, buf, 10);
			x = atol(buf);
			//уможить
		}
	}
	return FALSE;
}