



//5번


//2 - 7
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <random>
#define Weight 720
#define Height 1280

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR strCmdLine, int nShowCmd) {

	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIconSm = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = "MEMO장";

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow("MEMO장", "MEMO장", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Height, Weight, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static TCHAR str[100][512] = { NULL };
	static TCHAR str2[100][512] = { NULL };
	static TCHAR str3[100][512] = { NULL };
	static TCHAR str4[100][512] = { NULL };
	static TCHAR str5[100][512] = { NULL };
	static char changeTemp[100];
	static int blank[2][100];
	static int lineCount[100] = { 0 };
	static int lineCount2[100] = { 0 };
	static int lineCount3[100] = { 0 };
	static int lineCount4[100] = { 0 };
	static int tempX = 0;
	static int tempY = 0;
	
	static size_t len = 0;
	static size_t len2 = 0;
	static size_t len3 = 1;
	static int caretLine;
	static int line = 1;
	static int x = 0;
	static int y = 0;
	static int a;
	static int b;
	static int Bcnt = 0;
	static int checkPoint = 0;
	HDC hDC;
	static int lenth;
	static int lenth2;
	static int lenth3;
	static int lenth4;

	static int aCaretSet = 0;
	static int hideCount2 = 0;
	static int hideCount = 0;
	static int checkHide = 0;
	static int saveCount = 0;
	static int testCheck = 0;
	static int ksibal = 0;
	static int checkLine = 0;
	static int check = 0;
	static int cCnt = 0;
	static int checkChange = 0;
	static int countE = 0;
	static int sibalz[100][512];
	static int sibalz2[100][512];
	static int checkE[100];
	static int save[100];
	PAINTSTRUCT ps;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 0.5, 20);
		SetCaretPos(x, y);
		ShowCaret(hWnd);
		return 0;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		switch (wParam) {
		case '3': //입력된 모든것을 *로 출력한다.
			checkPoint += 1;
			break;

		case '4': //입력된 숫자를 전부 0으로 출력한다.
			if (checkChange % 2 == 0) {
				cCnt = 0;
				for (int i = 0; i < line; ++i)
					for (int j = 0; j < len; ++j)
					{
						if (str[i][j] - 48 > 0 && str[i][j] - 48 < 10) {
							changeTemp[cCnt] = str[i][j];
							str[i][j] = '0';
							cCnt++;
						}
					}
				checkChange++;
			}

			else if (checkChange % 2 != 0)
			{
				cCnt = 0;
				for (int i = 0; i < line; ++i)
					for (int j = 0; j < len; ++j)
					{
						if (str[i][j] == '0') {
							str[i][j] = changeTemp[cCnt];
							cCnt++;
						}
					}
				checkChange++;
			}
			break;

		case '5': // 입력된 문자중 e나 E가 있으면 #으로 바꿔 출력한다.
			for (int i = 0; i < line; ++i)
				for (int j = 0; j < len; ++j)
				{
					if (str[i][j] == 'e' || str[i][j] == 'E') {
						checkE[countE++] = str[i][j];
						str[i][j] = '#';
					}
					else if (str[i][j] == '#')
						str[i][j] = checkE[countE++];
				}
			countE = 0;
			break;

		case '[': // 공백 제거해줌
			check++;
			/*Bcnt = 0;
			if (check % 2 != 0) {
				for (int i = 0; i < line; ++i)
					for (int j = 0; j < len; ++j)
					{
						if (str[i][j] == ' ')
						{
							blank[Bcnt][0] = i;
							blank[Bcnt][1] = j;
							for (int k = j; k < len; k++)
							{
								str[i][j] = str[i][j + 1];
								len--;
							}
							Bcnt++;
						}
					}
			}
			if (check % 2 == 0 && check != 0) {

			}*/
			break;
		case ']':
			checkLine++;
			break;
		case '/':
			if (checkHide % 2 == 0) {
				aCaretSet = a;
				saveCount = 0;
				for (int i = a; str[caretLine][i] != ' '; i--)
				{
					save[saveCount] = str[caretLine][i];
					str[caretLine][i] = ' ';
					saveCount++;
					hideCount++;
				}
				for (int i = a + 1; str[caretLine][i] != ' '; i++)
				{
					save[saveCount] = str[caretLine][i];
					str[caretLine][i] = ' ';
					saveCount++;
					hideCount2++;
				}
				checkHide++;
			}

			else if (checkHide % 2 != 0)
			{
				saveCount = 0;
				for (int i = a; i > a - hideCount; i--) {
					str[caretLine][i] = save[saveCount];
					saveCount++;
				}
				for (int i = a + 1; i <= a + hideCount2; ++i) {
					str[caretLine][i] = save[saveCount];
					saveCount++;
				}
			}
			break;

		case '+': // 입력된 숫자들을 1씩 더한다
			for (int i = 0; i < line; ++i)
				for (int j = 0; j < len; ++j)
				{
					if (str[i][j] - 48 < 10 && str[i][j] - 48 > 0)
						str[i][j] += 1;
				}
			break;
		case '-': // 입력된 숫자들을 1씩 뺀다
			for (int i = 0; i < line; ++i)
				for (int j = 0; j < len; ++j)
				{
					if (str[i][j]-48 >0 && str[i][j]-48 < 10)
						str[i][j] -= 1;
				}
			break;
		case VK_BACK:
			if (len == 0 && line > 1) {
				lineCount[line - 1] = 0;
				len = strlen(str[(--line - 1)]);
				x = lineCount[line - 1];
				SetCaretPos(x, y = (line - 1) * 20);
			}
			else if(len > 0) {
				ksibal = len -1;
				GetCharWidth32(hDC, (UINT)str[line - 1][len], (UINT)str[line - 1][len], &lenth);
				SetCaretPos(x -= sibalz[line - 1][len-=1], y = (line - 1) * 20);
				lineCount[line - 1] -= sibalz[line - 1][len];
			}
			break;
		case VK_ESCAPE:
			for (int i = 0; i < line; ++i)
				lineCount[i] = 0;
			line = 1;
			len = 0;
			len2 = 0;
			len3 = 0;
			SetCaretPos(x = lineCount[line - 1], y = (line - 1) * 20);
			break;
		case VK_RETURN:
			len = 0;
			line++;
			break;
		case  VK_TAB:
			str[line - 1][len++] = ' ';
			str[line - 1][len++] = ' ';
			str[line - 1][len++] = ' ';
			str[line - 1][len++] = ' ';
			GetCharWidth32(hDC, (UINT)str[line - 1][len - 1], (UINT)str[line - 1][len - 1], &lenth);
			SetCaretPos(lineCount[line - 1] += (lenth * 4), y = (line - 1) * 20);
			break;

		case  '2': //한줄만 지움
			for (int i = caretLine; i < line-1; i++) {
				for (int j = 0; j < len; ++j) {
					str[i][j] = str[i+1][j];
				}
			}
			line--;
			break;
			

		case '1': // 캐럿이 그줄 맨 앞으로 오도록 한다.
			tempX = lineCount[line - 1];
			SetCaretPos(x = 0, y = (line - 1) * 20);
			break;
		default:
			str[line - 1][len] = (TCHAR)wParam;
			str2[line - 1][len] = '*';

			if(wParam != VK_TAB)
				str3[line - 1][len2] = (TCHAR)wParam;
			if (str3[line - 1][len2] != ' ')
				len2++;

			str4[line - 1][0] = '(';
			str4[line - 1][len3] = (TCHAR)wParam;

			if (str4[line - 1][len3] == ' ')
			{
				str4[line - 1][len3] = ')';
				str4[line - 1][len3 + 1] = '(';
				len3 += 2;
			}
			else {
				len3++;
			}
			

			GetCharWidth(hDC, (UINT)wParam, (UINT)wParam, &lenth);
			lineCount[line - 1] += lenth;
			GetCharWidth(hDC, (UINT)str2[line - 1][len], (UINT)str2[line - 1][len - 1], &lenth2);
			lineCount2[line - 1] += lenth2;
			/*GetCharWidth(hDC, (UINT)str3[line - 1][len2], (UINT)str3[line - 1][len2 - 1], &lenth3);
			lineCount3[line - 1] += lenth3;
			sibalz[line - 1][len2 - 1] = lenth3;
			GetCharWidth(hDC, (UINT)str4[line - 1][len3], (UINT)str4[line - 1][len3 - 1], &lenth4);*/

			if (checkPoint % 2 == 0 && check % 2 == 0) {
				SetCaretPos(x = lineCount[line - 1], (line - 1) * 20);
				sibalz[line - 1][len++] = lenth;
			}
			else if (checkPoint % 2 == 1) {
				SetCaretPos(lineCount2[line - 1], (line - 1) * 20);
				sibalz[line - 1][len++] = lenth2;
			}
			
			if (check != 0) {
				x = lineCount[line - 1];
				SetCaretPos(lineCount[line - 1], (line - 1) * 20);
			}
			a = len;
			b = len;
			break;
		}
		str[line - 1][len] = '\0';
		str2[line - 1][len] = '\0';
		str3[line - 1][len2] = '\0';
		str4[line - 1][len3] = ')';
		caretLine = line - 1;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		if (checkPoint % 2 == 0 && check %2 == 0 && checkLine % 2 == 0) {
			for (int i = 1; i <= line; i++) {
				TextOut(hDC, 0, (i - 1) * 20, str[i - 1], strlen(str[i - 1]));
			}
		}
		else if(checkPoint % 2 == 1){
			for (int i = 1; i <= line; i++) {
				TextOut(hDC, 0, (i - 1) * 20, str2[i - 1], strlen(str2[i - 1]));
			}
		}
		if(check % 2 != 0)
			for (int i = 0; i <= line; i++) {
				TextOut(hDC, 0,(i - 1) * 20, str3[i - 1], strlen(str3[i - 1]));
			}

		if(checkLine % 2 != 0)
			for (int i = 0; i <= line; i++) {
				TextOut(hDC, 0, (i - 1) * 20, str4[i - 1], strlen(str4[i - 1]));
			}
		EndPaint(hWnd, &ps);

		break;
	}

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
			if (wParam == VK_LEFT) {
				SetCaretPos(x -= sibalz[caretLine][a--], caretLine * 20);
			}
			else if (wParam == VK_RIGHT) {
				SetCaretPos(x += sibalz[caretLine][++a], caretLine * 20);
			}
			else if (wParam == VK_UP) {
				SetCaretPos(x, (caretLine -=1) * 20);
			}
			else if (wParam == VK_DOWN) {
				SetCaretPos(x, (caretLine += 1)* 20);

			}
			else if (wParam == VK_RETURN) {
				SetCaretPos(x = 0, (caretLine += 1) * 20); 
			}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

