#include <Windows.h>
#include <iostream>
#include <random>
#include <time.h>
#define Height 1280
#define Weight 720

using namespace std;
HPEN MyPen, OldPen;
#define MAX 9
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Windows Programing KWB";
struct printT {
	char temp[100];
};
struct Size {
	char inputCommand[100];
	int x[100];
	int y[100];
	char PrintTemp[100];
	printT t[100];
};

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
	hWnd = CreateWindow(lpszClass, "window progra1-2", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 100, 50, Height, Weight, NULL, (HMENU)NULL, hInstance, NULL);
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
static char str;
int p = 0;
int position[100];
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	Size pos;
	//srand(time(NULL));
	char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	char beta[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static char str;
	int k = 0;
	static int color = 0;
	default_random_engine dre;
	uniform_int_distribution <> uid(0, Height);

	int cnt = 0;
	int x, y;

	char temp[100] = {};
	switch (iMessage) {
	case WM_CHAR:
		x = rand() % (Height - 70);
		y = rand() % Weight - 2;
		hDC = GetDC(hWnd);
		str = wParam - 97;
		for (int i = str; i <= 26; ++i) {
			temp[k] = alpha[i];
			k++;
		}
		temp[k] = '\0';
		k = 0;
		SetBkColor(hDC, RGB(color += 10, 0, 140));
		TextOut(hDC, x, y, temp, strlen(temp));
		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}