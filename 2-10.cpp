#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hinst;
LPCTSTR lpszClass = TEXT("First");

struct Shape
{
	int info;//������ ����
	int number;
	int r, g, b;//������ ����
	int size;
	POINT p[3]; // ������ ��ǥ
};

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) //h�� �ǹ�? = �ڵ�
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hinst = hinstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //���α׷� ������ ���̴� Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������ 
	WndClass.hInstance = hinstance; //���� ����ǰ� �ִ� ��ü�� �ڵ�
	WndClass.lpfnWndProc = WndProc; //���ν����Լ��� �̸� 
	WndClass.lpszClassName = lpszClass; //������ Ŭ���� ������ �̸� 
	WndClass.lpszMenuName = NULL; // �޴��� �̸�
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //������ ��� ��Ÿ��
											  // ������� WNDCLASS����ü�� �����鿡 ���� ����

	RegisterClass(&WndClass); // ������ Ŭ������ �ü���� ���

	hWnd = CreateWindow(lpszClass, "Windows Program 1-1", WS_OVERLAPPEDWINDOW, 0, 0, 1280, 1280, NULL, (HMENU)NULL, hinstance, NULL);
	//CreateWindow(Ŭ���� �̸�,Ÿ��Ʋ �̸�,������ ��Ÿ��, ������ ��ġ��ǥx , y,������ ����ũ��, ������ ����ũ��, �θ� ������ �ڵ�, �޴� �ڵ�, �������α׷� �ν��Ͻ�, ���� ������ ����(NULL))
	ShowWindow(hWnd, nCmdShow); //�������� ȭ�� ���
	UpdateWindow(hWnd); //OS�� WM_PAINT�޽��� ����
	while (GetMessage(&Message, NULL, 0, 0))
	{
		//������ ���ν������� PostQuitMessage()�� ȣ���Ҷ� �����.
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}//�޽��������� ����.
	return (int)Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) //CALLBACK(������ �ڵ�, ó���ؾ� �� �޽����� ��,�Է���ġ�� ��1,2)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hpen, hpen2, oldpen, oldpen2;
	HBRUSH hBrush, oldBrush;
	static Shape shape[5];

	static int R, G, B;
	static int xpos1;
	static int ypos1;
	static int xpos2;
	static int ypos2;
	static int cnt = 0;
	static int select;
	static int setValue = 0;
	static int size[5] = { 0 };

	switch (iMessage) //�޽����� ��ȣ
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:

		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);

		if (wParam == 'e' || wParam == 'E')
		{
			if (cnt > 4)
			{
				cnt = 0;
			}
			xpos1 = rand() % 40;
			ypos1 = rand() % 40;
			xpos2 = xpos1 + 1;
			ypos2 = ypos2 + 1;

			shape[cnt].r = rand() % 255;
			shape[cnt].b = rand() % 255;
			shape[cnt].g = rand() % 255;

			shape[cnt].info = 1;
			shape[cnt].p[0].x = xpos1;
			shape[cnt].p[0].y = ypos1;
			shape[cnt].p[1].x = xpos2;
			shape[cnt].p[1].y = ypos2;
			shape[cnt].number = cnt;
			size[cnt] = 0;
			cnt++;
		}

		else if (wParam == 'r' || wParam == 'R')
		{
			if (cnt > 5)
			{
				cnt = 0;
			}
			xpos1 = rand() % 40;
			ypos1 = rand() % 40;
			xpos2 = xpos1 + 1;
			ypos2 = ypos2 + 1;

			shape[cnt].r = rand() % 255;
			shape[cnt].b = rand() % 255;
			shape[cnt].g = rand() % 255;

			shape[cnt].info = 2;
			shape[cnt].p[0].x = xpos1;
			shape[cnt].p[0].y = ypos1;
			shape[cnt].p[1].x = xpos2;
			shape[cnt].p[1].y = ypos2;
			shape[cnt].number = cnt;
			size[cnt] = 0;
			cnt++;

		}
		else if (wParam == 't' || wParam == 'T')
		{
			if (cnt > 5)
			{
				cnt = 0;

			}

			shape[cnt].info = 3;
			shape[cnt].p[0].x = rand() % 20 * 20;
			shape[cnt].p[0].y = rand() % 20 * 20;
			shape[cnt].p[1].x = shape[cnt].p[0].x + 20;
			shape[cnt].p[1].y = shape[cnt].p[0].y;
			shape[cnt].p[2].x = shape[cnt].p[0].x;
			shape[cnt].p[2].y = shape[cnt].p[0].y - 20;
			size[cnt] = 0;



			shape[cnt].r = rand() % 255;
			shape[cnt].b = rand() % 255;
			shape[cnt].g = rand() % 255;


			shape[cnt].number = cnt;
			cnt++;
		}

		else if (wParam - 48 <= 9 && wParam - 48 >= 0)
		{
			select = wParam - 48;
		}

		else if (wParam == 's')
		{
			setValue = 1;
		}
		else if (wParam == 'm')
		{
			setValue = 0;
		}
		else if (wParam == 'l')
		{
			setValue = 2;
		}

		else if (wParam == '+')
		{
			if (shape[select - 1].info == 3) {
				shape[select - 1].p[1].x += 20;
				shape[select - 1].p[2].y -= 20;
			}
			else
				size[select - 1] += 20;
		}
		else if (wParam == '-')
		{
			if (shape[select - 1].info == 3) {
				shape[select - 1].p[1].x -= 20;
				shape[select - 1].p[2].y += 20;
			}
			else
				size[select - 1] -= 20;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_KEYUP:
		hdc = GetDC(hWnd);
		switch (wParam)
		{
		case VK_UP:
			if (shape[select - 1].info == 3)
			{
				shape[select - 1].p[0].y -= 20;
				shape[select - 1].p[1].y -= 20;
				shape[select - 1].p[2].y -= 20;
			}
			else
				shape[select - 1].p[0].y -= 1;
			break;

		case VK_DOWN:
			if (shape[select - 1].info == 3)
			{
				shape[select - 1].p[0].y += 20;
				shape[select - 1].p[1].y += 20;
				shape[select - 1].p[2].y += 20;
			}
			else
				shape[select - 1].p[0].y += 1;
			break;

		case VK_LEFT:
			if (shape[select - 1].info == 3)
			{
				shape[select - 1].p[0].x -= 20;
				shape[select - 1].p[1].x -= 20;
				shape[select - 1].p[2].x -= 20;
			}
			else
				shape[select - 1].p[0].x -= 1;
			break;

		case VK_RIGHT:
			if (shape[select - 1].info == 3)
			{
				shape[select - 1].p[0].x += 20;
				shape[select - 1].p[1].x += 20;
				shape[select - 1].p[2].x += 20;
			}
			else
				shape[select - 1].p[0].x += 1;
			break;

		case VK_DELETE:
			for (int i = select - 1; i < 5; ++i)
			{
				shape[i] = shape[i + 1];
				shape[i].number -= 1;
			}
			cnt -= 1;
			break;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //�޽����� ó��
		hdc = BeginPaint(hWnd, &ps);
		hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		oldpen = (HPEN)SelectObject(hdc, hpen);


		if (setValue == 0) {
			Rectangle(hdc, 0, 0, 800, 800);
			for (int i = 0; i < 40; i++) {
				MoveToEx(hdc, 20 * (i + 1), 0, NULL);
				LineTo(hdc, 20 * (i + 1), 800);
			}
			for (int i = 0; i < 40; i++) {
				MoveToEx(hdc, 0, 20 * (i + 1), NULL);
				LineTo(hdc, 800, 20 * (i + 1));
			}
		}

		else if (setValue == 1) {
			Rectangle(hdc, 0, 0, 600, 600);
			for (int i = 0; i < 30; i++) {
				MoveToEx(hdc, 20 * (i + 1), 0, NULL);
				LineTo(hdc, 20 * (i + 1), 600);
			}
			for (int i = 0; i < 30; i++) {
				MoveToEx(hdc, 0, 20 * (i + 1), NULL);
				LineTo(hdc, 600, 20 * (i + 1));
			}
		}

		else if (setValue == 2) {
			Rectangle(hdc, 0, 0, 1000, 1000);
			for (int i = 0; i < 50; i++) {
				MoveToEx(hdc, 20 * (i + 1), 0, NULL);
				LineTo(hdc, 20 * (i + 1), 1000);
			}
			for (int i = 0; i < 50; i++) {
				MoveToEx(hdc, 0, 20 * (i + 1), NULL);
				LineTo(hdc, 1000, 20 * (i + 1));
			}
		}

		for (int i = 0; i < 5; ++i)
		{

			if (shape[i].info == 1) {
				hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
				oldpen = (HPEN)SelectObject(hdc, hBrush);
				if (select - 1 == shape[i].number)
				{
					hpen2 = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
					oldpen2 = (HPEN)SelectObject(hdc, hpen2);
				}
				else {
					hpen2 = CreatePen(PS_SOLID, 1, RGB(shape[i].r, shape[i].g, shape[i].b));
					oldpen2 = (HPEN)SelectObject(hdc, hpen2);
				}
				Ellipse(hdc, shape[i].p[0].x * 20, shape[i].p[0].y * 20, shape[i].p[0].x * 20 + 20 + size[i], shape[i].p[0].y * 20 + 20 + size[i]);
			}
			else if (shape[i].info == 2) {
				hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
				oldpen = (HPEN)SelectObject(hdc, hBrush);
				if (select - 1 == shape[i].number)
				{
					hpen2 = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
					oldpen2 = (HPEN)SelectObject(hdc, hpen2);
				}
				else
				{
					hpen2 = CreatePen(PS_SOLID, 1, RGB(shape[i].r, shape[i].g, shape[i].b));
					oldpen2 = (HPEN)SelectObject(hdc, hpen2);
				}
				Rectangle(hdc, shape[i].p[0].x * 20, shape[i].p[0].y * 20, shape[i].p[0].x * 20 + 20 + size[i], shape[i].p[0].y * 20 + 20 + size[i]);
			}
			else if (shape[i].info == 3) {
				hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
				oldpen = (HPEN)SelectObject(hdc, hBrush);
				if (select - 1 == shape[i].number)
				{
					hpen2 = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
					oldpen2 = (HPEN)SelectObject(hdc, hpen2);
				}
				else
				{
					hpen2 = CreatePen(PS_SOLID, 1, RGB(shape[i].r, shape[i].g, shape[i].b));
					oldpen2 = (HPEN)SelectObject(hdc, hpen2);
				}
				Polygon(hdc, shape[i].p, 3);
			}
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	//case���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}
