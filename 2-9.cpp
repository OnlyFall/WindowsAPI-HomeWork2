
#include <Windows.h>
#include <random>
#include<time.h>
#include<stdlib.h>
#include<tchar.h>
#define WideSize 800   
#define HighSize 600
#define Line 10
#define MAX 100

HINSTANCE g_hInst;
LPCTSTR lpszClass = "Window Class Name2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	//두 색의 합이 0으로 되겠
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, "window  1-2", WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_HSCROLL | WS_VSCROLL | WS_SYSMENU, 0, 0, WideSize, HighSize, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static SIZE size;
	HDC hdc;
	//drawtext선언을 위한 rect
	RECT rect;
	PAINTSTRUCT ps;
	//변수 설정 모음=---------
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	static TCHAR str[100];
	static TCHAR errorMessage[] = { "도형이 그려지지 않았습니다." };
	int rand_ResultR, rand_ResultG, rand_ResultB = 0;
	static int k, result = 0;
	rand_ResultR = (rand() % 255) + 0;
	rand_ResultG = (rand() % 255) + 0;
	rand_ResultB = (rand() % 255) + 0;

	static TCHAR mess[1];
	static int x, y, line, count = 0;
	//사각형 원 좌표이동을 위한 값
	static int x1, x2, y1, y2, shape, size_pen, pen_modify;
	switch (iMessage)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 3, 15);
		ShowCaret(hWnd);
		x1, y1, x2, y2 = 0;
		shape = 0;
		count = 0;
		size_pen, pen_modify = 0;
		line = 0;
		return 0;

	case WM_CHAR:
		//두께 조절
		if (wParam == '+') {
			pen_modify++;
		}
		else if (wParam == '-') {
			pen_modify--;
		}
		//화살표 이동
		//원래색으로 변경
		else if (wParam == VK_ESCAPE) {
			count = 0;
		}
		else if ((wParam == VK_BACK) && (count >0)) {
			str[count - 1] = '\0';
			count--;
		}
		else if (wParam == VK_UP) {
			y -= 20;
		}
		else if (wParam == VK_DOWN) {
			y += 20;
		}
		else if (wParam == VK_LEFT) {
			x += 20;
		}
		else if (wParam == VK_RIGHT) {
			x -= 20;
		}
		else if (wParam == VK_BACK) {
			str[count - 1] = str[count];
			count--;
		}
		else if (wParam == VK_RETURN)
		{
			sscanf(str, "%d %d %d %d %d %d", &shape, &x1, &y1, &x2, &y2, &size_pen);
		}
		else {
			str[count++] = wParam;
			str[count] = NULL;

		}
		InvalidateRect(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(255, 255, 255));
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 0, HighSize - 100, str, strlen(str));
		GetTextExtentPoint(hdc, str, strlen(str), &size);
		SetCaretPos(size.cx, 480);
		if (x1 == 0 || x2 == 0 || y1 == 0 || y2 == 0) { //에러 메세지
			TextOut(hdc, 100, 100, errorMessage, strlen(errorMessage));
		}

		//펜 해제하기
		if (shape == 1) { //선
			hPen = CreatePen(PS_DOT, size_pen + pen_modify, RGB(rand_ResultR, rand_ResultG, rand_ResultB));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, x1 + x, y1 + y, NULL);
			LineTo(hdc, x2 + x, y2 + y);

			SelectObject(hdc, oldPen);     // 이젂의 펜으로 돌아감   
			DeleteObject(hPen);    // 만듞 펜 객체 삭제하기 
			shape = 0;
			pen_modify = 0;
		}
		else if (shape == 2) { //원
			hBrush = CreateSolidBrush(RGB(255 - rand_ResultR, 255 - rand_ResultG, 255 - rand_ResultB));
			hPen = CreatePen(PS_DOT, size_pen + pen_modify, RGB(rand_ResultR, rand_ResultG, rand_ResultB));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Ellipse(hdc, x1 + x, y1 + y, x2 + x, y2 + y);

			SelectObject(hdc, oldBrush);   // 이젂의 브러시로 돌아가기  
			DeleteObject(hBrush);    // 만듞 브러시 객체 삭제하기 

			SelectObject(hdc, oldPen);     // 이젂의 펜으로 돌아감   
			DeleteObject(hPen);    // 만듞 펜 객체 삭제하기 
			pen_modify = 0;
		}
		else if (shape == 3) { //삼각형
			POINT point[3] = { { x1 + x,y1 + y },{ x2 + x,y2 + y } ,{ x + x1, y2 + y } };

			hBrush = CreateSolidBrush(RGB(255 - rand_ResultR, 255 - rand_ResultG, 255 - rand_ResultB));
			hPen = CreatePen(PS_DOT, size_pen + pen_modify, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Polygon(hdc, point, 3);

			SelectObject(hdc, oldBrush);   // 이젂의 브러시로 돌아가기  
			DeleteObject(hBrush);    // 만듞 브러시 객체 삭제하기 

			SelectObject(hdc, oldPen);     // 이젂의 펜으로 돌아감   
			DeleteObject(hPen);    // 만듞 펜 객체 삭제하기 
			pen_modify = 0;
		}

		else if (shape == 4) { //사각형
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			hPen = CreatePen(PS_DOT, size_pen + pen_modify, RGB(rand_ResultR, rand_ResultG, rand_ResultB));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, x1 + x, y1 + y, x2 + x, y2 + y);

			SelectObject(hdc, oldBrush);   // 이젂의 브러시로 돌아가기  
			DeleteObject(hBrush);    // 만듞 브러시 객체 삭제하기 

			SelectObject(hdc, oldPen);     // 이젂의 펜으로 돌아감   
			DeleteObject(hPen);    // 만듞 펜 객체 삭제하기 
			shape = 0;
			pen_modify = 0;
		}
		else {
			x = 0;
			y = 0;
		}
		SetCaretPos(size.cx, HighSize - 100);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

