/*
Ruben Wihler
11.02.2022
A fake virus very visual to make a joke.
*/

#include <windows.h>
#include <iostream>
#include <thread>
#include <shellapi.h>

int scrWidth, scrHeight;
int Interval = 125;
int runtime = 0;

struct beepParams
{
	int freq;
	int mil;
};

void beepTone(beepParams params)
{
	Beep(params.freq, params.mil);
}

LRESULT CALLBACK Main(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
	{
		HDC Desktop = GetDC(HWND_DESKTOP);
		HDC Window = GetDC(hWnd);

		BitBlt(Window, 0, 0, scrWidth, scrHeight, Desktop, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, Window);
		ReleaseDC(HWND_DESKTOP, Desktop);

		SetTimer(hWnd, 0, Interval, 0);
		ShowWindow(hWnd, SW_SHOW);
		break;
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);
		break;
	}
	case WM_TIMER:
	{
		HDC Window = GetDC(hWnd);
		int X = (rand() % scrWidth) - (150 / 2),
			Y = (rand() % 15),
			Width = (rand() % 150);
		BitBlt(Window, X, Y, Width, scrHeight, Window, X, 0, SRCCOPY);
		BitBlt(Window, X, Y, Width, scrHeight, Window, X, 0, SRCINVERT);
		BitBlt(Window, X, Y, Width, scrHeight, Window, X, 0, SRCPAINT);
		ReleaseDC(hWnd, Window);
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}
	return 0;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE Prev, LPSTR Cmd, int showcmd)
{
	Sleep(2000);
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);

	ShellExecute(0, 0, "https://chrome.google.com/webstore/detail/clickclean/ghgabhipcejejjmhhchfonmamedcbeod?hl=en", 0, 0, SW_SHOW);
	ShellExecute(0, 0, "https://chrome.google.com/webstore/detail/clickclean/ghgabhipcejejjmhhchfonmamedcbeod?hl=en", 0, 0, SW_NORMAL);
	Sleep(2000);
	MessageBox(0, "Trust installer blocked the threat!", "A threat was detected.", MB_DEFBUTTON1);
	Sleep(100);
	MessageBox(0, "Trust installer blocked the threat!", "A threat was detected.", MB_DEFBUTTON1);
	Sleep(1000);
	MessageBox(0, "Trust installer blocked the threat!", "A threat was detected.", MB_DEFBUTTON1);
	Sleep(2000);

	WNDCLASS wndClass = { 0, Main, 0,0, Inst, 0, LoadCursor(0, IDC_ARROW), 0, 0, "screenMelter" };

	if (RegisterClass(&wndClass))
	{
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "screenMelter", 0, WS_POPUP,
			0, 0, scrWidth, scrHeight, HWND_DESKTOP, 0, Inst, 0);
		if (hWnd)
		{
			srand(GetTickCount());
			MSG Msg = { 0 };
			beepParams params;
			params.freq = 600;
			params.mil = 500;
			std::thread t(beepTone, params);
			t.detach();

			for (int i = 0; i < 3; i++)
			{
				MessageBox(0, "Trust installer blocked the threat!", "A threat was detected.", MB_ICONEXCLAMATION);	
			}
			while (Msg.message != WM_QUIT)
			{
				if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
			}
		}
	}
	return 0;
}
