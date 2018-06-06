#include <Windows.h>
#include <iostream>
#include <random>

//해상도 설정부분
#define width 1280
#define height 720
#define blk 10

using namespace std;
HPEN MyPen, OldPen;
#define MAX 9
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Windows Programing KWB";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, "window progra1-2", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 100, 50, width, height, NULL, (HMENU)NULL, hInstance, NULL);
	int x = 800;
	int y = 600;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	static char command;
	switch (iMessage) {
	case WM_CHAR:
		hDC = GetDC(hWnd);
		command = wParam;
		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 40; ++i)
			for (int j = 0; j < 40; ++j) {
				rect.left = (width - (2 * blk)) / 40 * i + blk;
				rect.right = (width - (2 * blk)) / 40 * i + blk + 10;
				rect.top = (height - (2 * blk)) / 40 * j + blk;
				rect.bottom = (height - (2 * blk)) / 40 * j + blk + 10;
				char text[5] = "";
				switch (command) {
				case 'a':
					if (i == j || i == 39 - j)
						sprintf(text, "*");
					break;
				case 'b':
					if (((i < 20 && 2 * i >= j)) || (i >= 20 && (2 * i - 20 <= 58 - j)))
						sprintf(text, "*");
					break;
				case 'c':
					if ((i < 20 && j >= 20 && i >= j - 20) || (i < 20 && j < 20 && 19 - i <= j) || (i >= 20 && j < 20 && i - 20 <= j) || (i >= 20 && j >= 20 && i - 20 <= 39 - j))
						sprintf(text, "*");
					break;
				case 'd':
					if ((i < 20 && j < 20 && i <= j) || (i < 20 && j >= 20 && 39 - i >= j) || (i >= 20 && j < 20 && i >= 39 - j) || (i >= 20 && j >= 20 && i - 20 >= j - 20))
						sprintf(text, "*");
					break;
				case 'e':
					if ((i < 20 && j < 20 && i >= j) || (i < 20 && j >= 20 && 39 - i <= j) || (i >= 20 && j < 20 && i <= 39 - j) || (i >= 20 && j >= 20 && i - 20 <= j - 20))
						sprintf(text, "*");
					break;
				case 'q':
					PostQuitMessage(0);
					break;
				}

				SetBkColor(hDC, RGB(0, 0, 0));
				SetTextColor(hDC, RGB(255, 255, 255));
				DrawText(hDC, text, strlen(text), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}