#include "stdafx.h"
#include "KMain.h"
#include "resource.h"
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include <Windows.h>

void OnCreate(HWND hWnd, HINSTANCE hInst);
void OnDraw(HDC hdc);
void OnLButtonDown(HWND hWnd, LPARAM lParam);
void OnKeyDown(HWND hWnd, WPARAM wParam);
void OnTimer(WPARAM wParam);
int Check(int rotation, int sx, int sy);


#define RECT_WIDTH 15
#define RECT_HEIGHT 15

#define SIZE_WIDTH 10
#define SIZE_HEIGHT 20

#define DIR_LEFT 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_DOWN 3

#define block_O 0
#define block_I 1
#define block_Z 2
#define block_S 3
#define block_L 4
#define block_J 5
#define block_T 6

HWND mHwnd;
HINSTANCE mInst;
int rot = 1;
int block_shape = block_Z;
int block[7][4][4][4] = {
		{
			{
				0,0,0,0,
				0,1,1,0,
				0,1,1,0,
				0,0,0,0 },
				{
					0,0,0,0,
					0,1,1,0,
					0,1,1,0,
					0,0,0,0 },
					{
						0,0,0,0,
						0,1,1,0,
						0,1,1,0,
						0,0,0,0 },
						{
							0,0,0,0,
							0,1,1,0,
							0,1,1,0,
							0,0,0,0 }
		},
		{
			{
				0,0,0,0,
				1,1,1,1,
				0,0,0,0,
				0,0,0,0 },
				{
					0,0,1,0,
					0,0,1,0,
					0,0,1,0,
					0,0,1,0 },
					{
						0,0,0,0,
						1,1,1,1,
						0,0,0,0,
						0,0,0,0 },
						{
							0,0,1,0,
							0,0,1,0,
							0,0,1,0,
							0,0,1,0 }
		},
		{
			{
				0,0,0,0,
				0,1,1,0,
				0,0,1,1,
				0,0,0,0 },
				{
					0,0,0,1,
					0,0,1,1,
					0,0,1,0,
					0,0,0,0 },
					{
						0,0,0,0,
						0,1,1,0,
						0,0,1,1,
						0,0,0,0 },
						{
							0,0,0,1,
							0,0,1,1,
							0,0,1,0,
							0,0,0,0 }
		},
		{
			{
				0,0,0,0,
				0,0,1,1,
				0,1,1,0,
				0,0,0,0 },
				{
					0,0,1,0,
					0,0,1,1,
					0,0,0,1,
					0,0,0,0 },
					{
						0,0,0,0,
						0,0,1,1,
						0,1,1,0,
						0,0,0,0 },
						{
							0,0,1,0,
							0,0,1,1,
							0,0,0,1,
							0,0,0,0 }
		},
		{
			{
				0,0,0,0,
				0,1,1,1,
				0,1,0,0,
				0,0,0,0 },
				{
					0,0,1,0,
					0,0,1,0,
					0,0,1,1,
					0,0,0,0 },
					{
						0,0,0,1,
						0,1,1,1,
						0,0,0,0,
						0,0,0,0 },
						{
							0,1,1,0,
							0,0,1,0,
							0,0,1,0,
							0,0,0,0 }
		},
		{
			{
				0,0,0,0,
				0,1,1,1,
				0,0,0,1,
				0,0,0,0 },
				{
					0,0,1,1,
					0,0,1,0,
					0,0,1,0,
					0,0,0,0 },
					{
						0,1,0,0,
						0,1,1,1,
						0,0,0,0,
						0,0,0,0 },
						{
							0,0,1,0,
							0,0,1,0,
							0,1,1,0,
							0,0,0,0 }
		},
		{
			{
				0,0,0,0,
				0,1,1,1,
				0,0,1,0,
				0,0,0,0 },
				{
					0,0,1,0,
					0,0,1,1,
					0,0,1,0,
					0,0,0,0 },
					{
						0,0,1,0,
						0,1,1,1,
						0,0,0,0,
						0,0,0,0 },
						{
							0,0,1,0,
							0,1,1,0,
							0,0,1,0,
							0,0,0,0 }
		}
};

int map[SIZE_WIDTH + 2][SIZE_HEIGHT + 2] = { 0 };

HBITMAP hBitmap;
RECT crt;

int gx=(SIZE_WIDTH/2)-2, gy=1;



void OnCreate(HWND hWnd, HINSTANCE hInst)
{
	mHwnd = hWnd;
	mInst = hInst;
	srand(time(NULL));

	SetTimer(hWnd, 1, 1000, NULL);

	for (int y = 0; y < SIZE_HEIGHT + 2; y++)
	{
		for (int x = 0; x < SIZE_WIDTH+2; x++)
		{
			if ((x*y == 0) ||( x == SIZE_WIDTH + 1 ))
			{
				map[y][x] = 1;
			}
			else if (y == SIZE_HEIGHT + 1)
			{
				map[y][x] = 2;
			}
		}
	}
}



void OnDraw(HDC hdc)
{
	HDC hMemDC;
	HBITMAP OldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	/////////////////////////////////////////////////////////////////////////////////////////

	for (int y = 0; y < SIZE_HEIGHT+2; y++)
	{
		for (int x = 0; x < SIZE_WIDTH + 2; x++)
		{
			//Rectangle(hdc, RECT_WIDTH*x, RECT_HEIGHT*y, RECT_WIDTH*x + RECT_WIDTH, RECT_HEIGHT*y + RECT_HEIGHT);
			if ((map[y][x] == 1))
			{
				HBRUSH hBrush, oBrush;
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				oBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, RECT_WIDTH * x, RECT_HEIGHT *y, RECT_WIDTH*(x + 1), RECT_HEIGHT * (y + 1));


				SelectObject(hdc, oBrush);
				DeleteObject(hBrush);
			}
			else if ((map[y][x] == 2))
			{
				HBRUSH hBrush, oBrush;
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, RECT_WIDTH * x, RECT_HEIGHT *y, RECT_WIDTH*(x + 1), RECT_HEIGHT * (y + 1));


				SelectObject(hdc, oBrush);
				DeleteObject(hBrush);
			}
		}
	}

	for (int y= 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			//Rectangle(hdc, RECT_WIDTH * x, RECT_HEIGHT * y, RECT_WIDTH * x + RECT_WIDTH, RECT_HEIGHT * y + RECT_HEIGHT);
			if (block[block_shape][rot][y][x] ==1)
			{
				HBRUSH hBrush, oBrush;
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				oBrush = (HBRUSH)SelectObject(hdc, hBrush);

				Rectangle(hdc, RECT_WIDTH * (x + gx), RECT_HEIGHT *(y + gy), RECT_WIDTH*(x + gx + 1), RECT_HEIGHT * (y + gy + 1));

				SelectObject(hdc, oBrush);
				DeleteObject(hBrush);
			}
		}
	}


	//////////////////////////////////////////////////////////////////
	//BitBlt(hdc, x*RECT_WIDTH, y*RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, hMemDC, RECT_WIDTH*sx,RECT_HEIGHT * sy, SRCCOPY);
	SelectObject(hMemDC, OldBitmap); 
	DeleteDC(hMemDC); // hMemDC 제거

}



void OnLButtonDown(HWND hWnd, LPARAM lParam)
{
	
	int lx = LOWORD(lParam);
	int ly = HIWORD(lParam);
}



void OnKeyDown(HWND hWnd,WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		if (Check(rot, gx-1, gy)==0)
		{
			gx--;
		}
		break;
	case VK_RIGHT:
		if (Check(rot, gx+1, gy)==0)
		{
			gx++;
		}
		break;
	case VK_DOWN:
		if (Check(rot, gx, gy + 1) == 0)
		{
			gy += 2;
		}
		break;
	case VK_UP:
		if (Check(((rot + 1) % 4), gx, gy)==0)
		{
			rot = (rot + 1) % 4;
		}
		break;
	}
	InvalidateRect(hWnd, NULL, true);
}



void OnTimer(WPARAM wParam)
{
	switch (wParam)
	{
	case 1:
		if (Check(rot, gx, gy + 1) == 0)
		{
			gy++;
		}
		else if (Check(rot, gx, gy + 1) == -2)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (block[block_shape][rot][y][x] == 1)
					{
						map[gy + y][gx + x] = 2;
					}
				}
			}
			block_shape = rand() % 7;
			gx = (SIZE_WIDTH / 2) - 2;
			gy = 1;

			// 줄체크
			int check = 0;
			for (int y = 0; y < SIZE_HEIGHT + 2; y++)
			{
				for (int x = 0; x < SIZE_WIDTH + 2; x++)
				{
					if (map[y][x] > 0)
					{
						check++;
					}
					if (check == SIZE_WIDTH + 2)
					{
						for (int check_y = y; check_y > 0; y--)
						{
							for (int x = 1; x < SIZE_WIDTH + 1; x++)
							{
								map[y + 1][x] = map[y][x];
							}
						}
					}
					check = 0;
				}
			}
		}
		break;
	}
	InvalidateRect(mHwnd, NULL, true);

}



int Check(int rotation, int sx, int sy)
{
	/*for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[bs][rot][x][y] == 1)
			{
				if ((sx + x == 0) || (sx + x == SIZE_WIDTH))
				{
					return -1;
				}
			}
		}
	}
	return 0;*/
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[block_shape][rotation][y][x] == 1)
			{
				if (map[sy + y][sx + x] == 1)
				{
					return -1;
				}
				else if (map[sy + y][sx + x] == 2)
				{
					return -2;
				}
			}
		}
	}
	return 0;
}
