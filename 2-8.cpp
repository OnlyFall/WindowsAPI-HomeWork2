#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hinst;
LPCTSTR lpszClass = TEXT("First");

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) //h의 의미? = 핸들
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hinst = hinstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //프로그램 내에서 보이는 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘 
	WndClass.hInstance = hinstance; //현재 실행되고 있는 객체의 핸들
	WndClass.lpfnWndProc = WndProc; //프로시저함수의 이름 
	WndClass.lpszClassName = lpszClass; //윈도우 클래스 내용의 이름 
	WndClass.lpszMenuName = NULL; // 메뉴바 이름
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우 출력 스타일
											  // 여기까지 WNDCLASS구조체의 변수들에 값을 대입

	RegisterClass(&WndClass); // 윈도우 클래스를 운영체제에 등록

	hWnd = CreateWindow(lpszClass, "Windows Program 1-1", WS_OVERLAPPEDWINDOW, 0, 0, 520, 570, NULL, (HMENU)NULL, hinstance, NULL);
	//CreateWindow(클래스 이름,타이틀 이름,윈도우 스타일, 윈도우 위치좌표x , y,윈도우 가로크기, 윈도우 세로크기, 부모 윈도우 핸들, 메뉴 핸들, 응용프로그램 인스턴스, 생성 윈도우 정보(NULL))
	ShowWindow(hWnd, nCmdShow); //윈도우의 화면 출력
	UpdateWindow(hWnd); //OS에 WM_PAINT메시지 전송
	while (GetMessage(&Message, NULL, 0, 0))
	{
		//윈도우 프로시저에서 PostQuitMessage()를 호출할때 종료됨.
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}//메시지루프를 돌림.
	return (int)Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) //CALLBACK(윈도우 핸들, 처리해야 할 메시지의 값,입력장치의 값1,2)
{
	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hpen, oldpen;
	HBRUSH hBrush, hBrush2, hBrush3, hBrush4, oldBrush;
	static SIZE size;
	static int xpos1 = rand() % 9 + 1;
	static int ypos1 = rand() % 9 + 1;
	static int xpos2 = rand() % 9 + 1;
	static int ypos2 = rand() % 9 + 1;

	static int outRectangle = 0;
	static int outCircle = 0;
	static char value[100];
	static int changeCheck = 0;
	static int check = 0;
	static int R, G, B;
	static int R1 = 100, G1 = 143, B1 = 225;
	static int R2 = 255, G2 = 140, B2 = 76;
	static int cnt = 0;
	switch (iMessage) //메시지의 번호
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		if (wParam == VK_LEFT || VK_RIGHT || VK_UP || VK_DOWN) {
			oldpen = (HPEN)SelectObject(hdc, hBrush);
			if (check % 2 == 0)
				Rectangle(hdc, xpos1 * 50, ypos1 * 50, xpos1 * 50 + 50, ypos1 * 50 + 50);
			else
				Ellipse(hdc, xpos2 * 50, ypos2 * 50, xpos2 * 50 + 50, ypos2 * 50 + 50);
		}
		ReleaseDC(hWnd, hdc);
		break;
	case WM_KEYUP:
		R = R1;
		G = G1;
		B = B1;
		if (wParam == VK_LEFT)
		{
			if (check % 2 == 0) {
				if (xpos1 == 0)
				{
					xpos1 = 10;
					R2 = rand() % 225;
					G2 = rand() % 225;
					B2 = rand() % 225;
					outRectangle++;
				}
				xpos1 -= 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					xpos1 += 1;
					check -= 1;

				}
				check++;
			}
			else if (check % 2 != 0) {
				if (xpos2 == 0)
				{
					xpos2 = 10;
					R1 = rand() % 225;
					G1 = rand() % 225;
					B1 = rand() % 225;
					outCircle++;
				}
				xpos2 -= 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					xpos2 += 1;
					check -= 1;
				}
				check++;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			if (check % 2 == 0) {
				if (xpos1 == 9)
				{
					xpos1 = -1;
					R2 = rand() % 225;
					G2 = rand() % 225;
					B2 = rand() % 225;
					outRectangle++;
				}
				xpos1 += 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					xpos1 -= 1;
					check -= 1;
				}
				check++;
			}
			else if (check % 2 != 0) {
				if (xpos2 == 9)
				{
					xpos2 = -1;
					R1 = rand() % 225;
					G1 = rand() % 225;
					B1 = rand() % 225;
					outCircle++;
				}
				xpos2 += 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					xpos2 -= 1;
					check -= 1;
				}
				check++;
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (check % 2 == 0) {
				if (ypos1 == 9)
				{
					ypos1 = -1;
					outRectangle++;
					R2 = rand() % 225;
					G2 = rand() % 225;
					B2 = rand() % 225;
				}
				ypos1 += 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					ypos1 -= 1;
					check -= 1;
				}
				check++;
			}
			else if (check % 2 != 0) {
				if (ypos2 == 9)
				{
					ypos2 = -1;
					R1 = rand() % 225;
					G1 = rand() % 225;
					B1 = rand() % 225;
					outCircle++;
				}
				ypos2 += 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					ypos2 -= 1;
					check -= 1;
				}
				check++;
			}
		}
		else if (wParam == VK_UP)
		{
			if (check % 2 == 0) {
				if (ypos1 == 0)
				{
					ypos1 = 10;
					outRectangle++;
					R2 = rand() % 225;
					G2 = rand() % 225;
					B2 = rand() % 225;
				}
				ypos1 -= 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					ypos1 += 1;
					check -= 1;
				}
				check++;
			}
			else if (check % 2 != 0) {
				if (ypos2 == 0)
				{
					ypos2 = 10;
					R1 = rand() % 225;
					G1 = rand() % 225;
					B1 = rand() % 225;
					outCircle++;
				}
				ypos2 -= 1;
				if (xpos1 == xpos2 && ypos1 == ypos2) {
					ypos2 += 1;
					check -= 1;
				}
				check++;
			}
		}

		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //메시지의 처리
		hdc = BeginPaint(hWnd, &ps);
		hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		oldpen = (HPEN)SelectObject(hdc, hpen);
		Rectangle(hdc, 0, 0, 500, 500);

		if (WM_KEYDOWN) {
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
		}

		for (int i = 0; i < 9; i++) {
			MoveToEx(hdc, 50 * (i + 1), 0, NULL);
			LineTo(hdc, 50 * (i + 1), 500);
		}
		for (int i = 0; i < 9; i++) {
			MoveToEx(hdc, 0, 50 * (i + 1), NULL);
			LineTo(hdc, 500, 50 * (i + 1));
		}


		hBrush = CreateSolidBrush(RGB(R2, G2, B2));
		oldpen = (HPEN)SelectObject(hdc, hBrush);
		Rectangle(hdc, xpos1 * 50, ypos1 * 50, xpos1 * 50 + 50, ypos1 * 50 + 50);
		hBrush2 = CreateSolidBrush(RGB(R1, G1, B1));
		oldpen = (HPEN)SelectObject(hdc, hBrush2);
		Ellipse(hdc, xpos2 * 50, ypos2 * 50, xpos2 * 50 + 50, ypos2 * 50 + 50);

		wsprintf(value, TEXT("Rectangle : (%d, %d), outtime : %d  ||   Circle : (%d, %d) , outtime : %d"), xpos1, ypos1, outRectangle, xpos2, ypos2, outCircle);
		TextOut(hdc, 50, 510, value, strlen(value));
		SelectObject(hdc, hBrush);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	//case에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}