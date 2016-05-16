// Matrix.cpp : Defines the entry point for the application.
//

#include "MatrixCalculator.h"
#include "stdafx.h"
#include "Matrix.h"
#include <string>
#define MAX_LOADSTRING 100
#define OUTPUT_EDIT_WIDTH 25

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int currentOperation = 0;
HWND hw;
HWND a[101];
HWND b[101];
HWND f[101];
MATRIX firstMatrix;
MATRIX secondMatrix;
MATRIX finalMatrix;

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
      CW_USEDEFAULT, 0, 830, 250, NULL, NULL, hInstance, NULL);
   hw = hWnd;
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
		currentOperation = wmId;
		
		if (currentOperation == IDD_SUMMTRX)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			if (firstMatrix.size() == 0 || secondMatrix.size() == 0)
			{
				MessageBox(hWnd, "Mатрицы должны быть заполнены!", "Ошибка", MB_OK | MB_ICONWARNING);
			}
			else
			{
				if (firstMatrix.size() == secondMatrix.size() && firstMatrix[0].size() == secondMatrix[0].size())
				{
					finalMatrix = MatrixCalculator::AddMatrix(firstMatrix, secondMatrix);
					char currentElement[255];
					int ind = 0;
					for (int j = 0; j < finalMatrix.size(); j++)
					{
						for (int i = 0; i < finalMatrix[j].size(); i++)
						{
							_gcvt_s(currentElement, finalMatrix[j][i], 10);
							f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) + 
								(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
							ind++;
						}
					}
					f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);

				}
				else
				{
					MessageBox(hWnd, "Mатрицы должны иметь одинаковые размерности! Cложение невозможно!", "Ошибка", MB_OK | MB_ICONWARNING);
				}
			}
		}

		if (currentOperation == IDD_GETREVERSEA)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			if (firstMatrix.size() == firstMatrix[0].size() && firstMatrix.size() != 0)
			{
				finalMatrix = MatrixCalculator::GetReverceMatrix(firstMatrix);
				char currentElement[255];
				int ind = 0;
				for (int j = 0; j < finalMatrix.size(); j++)
				{
					for (int i = 0; i < finalMatrix[j].size(); i++)
					{
						_gcvt_s(currentElement, finalMatrix[j][i], 10);
						f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) +
							(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
						ind++;
					}
				}
				f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);

			}
			else
			{
				MessageBox(hWnd, "Mатрицa должнa быть заполненa!", "Ошибка", MB_OK | MB_ICONWARNING);
			}
		}

		if (currentOperation == IDD_GETREVERSEB)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			if (secondMatrix.size() == secondMatrix[0].size() && secondMatrix.size() != 0)
			{
				finalMatrix = MatrixCalculator::GetReverceMatrix(secondMatrix);
				char currentElement[255];
				int ind = 0;
				for (int j = 0; j < finalMatrix.size(); j++)
				{
					for (int i = 0; i < finalMatrix[j].size(); i++)
					{
						_gcvt_s(currentElement, finalMatrix[j][i], 10);
						f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) +
							(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
						ind++;
					}
				}
				f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);

			}
			else
			{
				MessageBox(hWnd, "Mатрицa должнa быть заполненa!", "Ошибка", MB_OK | MB_ICONWARNING);
			}
		}

		if (currentOperation == IDD_TPNMTRXA)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			finalMatrix = MatrixCalculator::TransposeMatrix(firstMatrix);
			char currentElement[255];
			int ind = 0;
			for (int j = 0; j < finalMatrix.size(); j++)
			{
				for (int i = 0; i < finalMatrix[j].size(); i++)
				{
					_gcvt_s(currentElement, finalMatrix[j][i], 10);
					f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) +
						(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
					ind++;
				}
			}
			f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);

		}

		if (currentOperation == IDD_TPNMTRXB)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			finalMatrix = MatrixCalculator::TransposeMatrix(secondMatrix);
			char currentElement[255];
			int ind = 0;
			for (int j = 0; j < finalMatrix.size(); j++)
			{
				for (int i = 0; i < finalMatrix[j].size(); i++)
				{
					_gcvt_s(currentElement, finalMatrix[j][i], 10);
					f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) +
						(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
					ind++;
				}
			}
			f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);
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
		if (currentOperation == IDD_MN4)
		{
			SendDlgItemMessage(hDlg, ID_CMBBX, CB_ADDSTRING, NULL, (LPARAM)"A");
			SendDlgItemMessage(hDlg, ID_CMBBX, CB_ADDSTRING, NULL, (LPARAM)"B");
		}

		//if (currentOperation == IDD_TPNMTRX)
		//{
		//	SendDlgItemMessage(hDlg, ID_CMBBX, CB_ADDSTRING, NULL, (LPARAM)"A");
		//	SendDlgItemMessage(hDlg, ID_CMBBX, CB_ADDSTRING, NULL, (LPARAM)"B");
		//}
		if (currentOperation == IDD_MNM)
		{
			SendDlgItemMessage(hDlg, ID_CMBBX1, CB_ADDSTRING, NULL, (LPARAM)"A");
			SendDlgItemMessage(hDlg, ID_CMBBX1, CB_ADDSTRING, NULL, (LPARAM)"B");
			SendDlgItemMessage(hDlg, ID_CMBBX2, CB_ADDSTRING, NULL, (LPARAM)"A");
			SendDlgItemMessage(hDlg, ID_CMBBX2, CB_ADDSTRING, NULL, (LPARAM)"B");
		}
		//if (currentOperation == IDD_GETREVERSE)
		//{
		//	SendDlgItemMessage(hDlg, ID_CMBBX, CB_ADDSTRING, NULL, (LPARAM)"A");
		//	SendDlgItemMessage(hDlg, ID_CMBBX, CB_ADDSTRING, NULL, (LPARAM)"B");
		//}
		return TRUE;
	case WM_COMMAND:    /* сообщение от управляющих элементов */
		if (LOWORD(wp) == IDOK || LOWORD(wp) == IDCANCEL) EndDialog(hDlg, 0);
		
		//Ввод матриц
		if (LOWORD(wp) == BTN_SETSIZE)
		{
			char bufI[3];
			char bufJ[3];
			GetDlgItemTextA(hDlg, N_SIZE, bufI, 3);
			GetDlgItemTextA(hDlg, M_SIZE, bufJ, 3);
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
					SetDlgItemTextA(hDlg, N_SIZE, "10");
					imax = 10;
				}
				if (jmax > 10)
				{
					SetDlgItemTextA(hDlg, M_SIZE, "10");
					jmax = 10;
				}
				MessageBox(hDlg, "Количество строк/столбцов не должно превышать 10! Размер матрицы был изменен", "Ошибка", MB_OK | MB_ICONINFORMATION);
			}
			int ind = 0;
			for (int j = 0; j < jmax; j++)
			{
				for (int i = 0; i < imax; i++)
				{
					ind += i + j;
					CreateWindow("edit", "0", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT, 125 + (int)(OUTPUT_EDIT_WIDTH * (10 - imax) / 2) + 
						(OUTPUT_EDIT_WIDTH * i), 105 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hDlg, (HMENU)(600 + ind), NULL, NULL);
				}
				int x = 0;
				x++;
			}
		}
		if (LOWORD(wp) == BTN_FILLMTRX)
		{
			char bufI[3];
			char bufJ[3];
			char currentElement[255];
			GetDlgItemTextA(hDlg, N_SIZE, bufI, 3);
			GetDlgItemTextA(hDlg, M_SIZE, bufJ, 3);
			int imax = atoi(bufJ);									//	Размерности 
			int jmax = atoi(bufI);									//				матрицы
			if (currentOperation == IDD_INPUTA)
			{
				firstMatrix.assign(imax, vector<double>(jmax)); // ТАК ЗАДАЕТСЯ РАЗМЕР
				int ind = 0;
				//заполняем матрицу A
				for (int i = 0; i < firstMatrix.size(); i++)
				{
					for (int j = 0; j < firstMatrix[i].size(); j++)
					{
						ind += i + j;
						GetDlgItemTextA(hDlg, (600 + ind), currentElement, 255);
						firstMatrix[i][j] = strtod(currentElement, '\0'); // ТУТ ПРИСВАИВАЕМ ЭЛЕМЕНТЫ
					}
				}
				for (int i = 0; i < 100; i++)
				{
					DestroyWindow(a[i]);
				}
				ind = 0;
				for (int j = 0; j < firstMatrix.size(); j++)
				{
					for (int i = 0; i < firstMatrix[j].size(); i++)
					{
						_gcvt_s(currentElement,firstMatrix[j][i], 3);
						a[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 5 + (int)(OUTPUT_EDIT_WIDTH * (10 - imax) / 2) +
							(OUTPUT_EDIT_WIDTH * i), 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(800 + ind), NULL, NULL);
						ind++;
					}
				}
				a[100] = CreateWindow("static", "Матрица A", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 30, 5, 100, 20, hw, (HMENU)999, NULL, NULL); //Сделать нормальную заливку и для остальных матриц
			}
			if (currentOperation == IDD_INPUTB)
			{
				secondMatrix.assign(imax, vector<double>(jmax)); // ТАК ЗАДАЕТСЯ РАЗМЕР
				int ind = 0;
				//заполняем матрицу В
				for (int i = 0; i < secondMatrix.size(); i++)
				{
					for (int j = 0; j < secondMatrix[i].size(); j++)
					{
						ind += i + j;
						GetDlgItemTextA(hDlg, (600 + ind), currentElement, 255);
						secondMatrix[i][j] = atol(currentElement); // ТУТ ПРИСВАИВАЕМ ЭЛЕМЕНТЫ
					}
				}
				for (int i = 0; i < 101; i++)
				{
					DestroyWindow(b[i]);
				}
				ind = 0;
				for (int j = 0; j < secondMatrix.size(); j++)
				{
					for (int i = 0; i < secondMatrix[j].size(); i++)
					{
						_gcvt_s(currentElement, secondMatrix[j][i],  10);
						b[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 540 + (int)(OUTPUT_EDIT_WIDTH * (10 - imax) / 2) +
							(OUTPUT_EDIT_WIDTH * i), 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1000 + ind), NULL, NULL);
						ind++;
					}
				}
				b[100] = CreateWindow("static", "Матрица B", WS_CHILD | WS_VISIBLE |SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 600, 5, 100, 20, hw, (HMENU)999, NULL, NULL); //Сделать нормальную заливку и для остальных матриц
			}

			EndDialog(hDlg, 0);
		}

		//Умножение матрицы на число
		if (LOWORD(wp) == BTN_MN4)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			bool isOK = true;
			char buf[255];
			long number = 0;
			GetDlgItemTextA(hDlg, 21, buf, 10);
			number = atol(buf);
			char bufM[2];
			GetDlgItemTextA(hDlg, ID_CMBBX, bufM, 2);
			if (bufM[0] == 'A' && firstMatrix.size() != 0)
			{
				finalMatrix = MatrixCalculator::MultiplyOnNumber(number, firstMatrix);
			}
			else
			{
				if (bufM[0] == 'B' && secondMatrix.size() != 0)
				{
					finalMatrix = MatrixCalculator::MultiplyOnNumber(number, secondMatrix);
				}
				else
				{
					isOK = false;
					MessageBox(hDlg, "Выбранная матрица не заполнена!", "Ошибка!", MB_OK | MB_ICONWARNING);
				}
			}
			if (isOK)
			{
				char currentElement[255];
				int ind = 0;
				for (int j = 0; j < finalMatrix.size(); j++)
				{
					for (int i = 0; i < finalMatrix[j].size(); i++)
					{
						_gcvt_s( currentElement, finalMatrix[j][i], 10);
						f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) +
							(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
						ind++;
					}
				}
				f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);

				EndDialog(hDlg, 0);
			}
		}
		
		////Транспонирование матрицы
		//if (LOWORD(wp) == BTN_TRNSP)
		//{
		//	//транспонируем
		//	EndDialog(hDlg, 0);
		//}

		//Умножение матриц
		if (LOWORD(wp) == BTN_MNM)
		{
			for (int i = 0; i < 101; i++)
			{
				DestroyWindow(f[i]);
			}
			bool isOk = true;
			char buf1[255];
			GetDlgItemTextA(hDlg, ID_CMBBX1, buf1, 10);
			char buf2[255];
			GetDlgItemTextA(hDlg, ID_CMBBX2, buf2, 10);
			int n1,m2;
			if (buf1[0] == 'A')
			{
				n1 = firstMatrix[0].size();
			}
			else
			{
				n1 = secondMatrix[0].size();
			}
			if (buf2[0] == 'B')
			{
				m2 = secondMatrix.size();
			}
			else
			{
				m2 = firstMatrix.size();
			}
			if (buf1[0] == '\0' || buf2[0] == '\0')
			{
				MessageBox(hDlg, "Не выбрана матрица(-ы) для умножения!", "Ошибка!", MB_OK | MB_ICONWARNING);
				isOk = false;
			}
			if (n1 == m2 && n1 != 0)
			{
				if (buf1[0] == 'A')
				{
					if (buf1[0] == 'A')
					{
						finalMatrix = MatrixCalculator::MultiplyMatrix(firstMatrix, firstMatrix);
					}
					else
					{
						finalMatrix = MatrixCalculator::MultiplyMatrix(firstMatrix, secondMatrix);
					}
				}
				else
				{
					if (buf2[0] == 'B')
					{
						finalMatrix = MatrixCalculator::MultiplyMatrix(secondMatrix, secondMatrix);
					}
					else
					{
						finalMatrix = MatrixCalculator::MultiplyMatrix(secondMatrix, firstMatrix);
					}
				}
			}
			else
			{
				isOk = false;
				MessageBox(hDlg, "Число стобцов первой матрицы не равно числу строк второй, или матрица не заполнена! Умножение невозможно!", "Ошибка", MB_OK | MB_ICONINFORMATION);
			}
			if (isOk)
			{
				char currentElement[255];
				int ind = 0;
				for (int j = 0; j < finalMatrix.size(); j++)
				{
					for (int i = 0; i < finalMatrix[j].size(); i++)
					{
						_gcvt_s( currentElement, finalMatrix[j][i], 10);
						f[ind] = CreateWindow("edit", currentElement, WS_CHILD | WS_VISIBLE, 270 + (int)(OUTPUT_EDIT_WIDTH * (10 - finalMatrix.size()) / 2) +
							(OUTPUT_EDIT_WIDTH * i) + 5, 30 + (15 * j), OUTPUT_EDIT_WIDTH, 15, hw, (HMENU)(1200 + ind), NULL, NULL);
						ind++;
					}
				}
				f[100] = CreateWindow("static", "Результат операции", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_SUNKEN | SS_LEFT, 300, 5, 150, 20, hw, (HMENU)999, NULL, NULL);

				EndDialog(hDlg, 0);
			}
		}

		//Получение обратной матрицы
		//if (LOWORD(wp) == BTN_REVERSE)
		//{
		//	//Выполнить
		//}
	}
	return FALSE;
}