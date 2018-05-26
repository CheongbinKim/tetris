#include "stdafx.h"

#include "KMain.h"
#include "resource.h"
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include <Windows.h>

#define RECT_WIDTH 20
#define RECT_HEIGHT 20
#define MAX 3
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

int mx;
int my;
HWND mHwnd;
HINSTANCE mInst;
int r = 0;
int block[7][4][4][4]= {
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
		0,0,0,0,
		1,1,1,1,
		0,0,0,0 },
		{
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0 },
		{ 
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0 },
		{
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0 } 
	},
	{ 
		{ 
		0,0,0,0,
		1,1,0,0,
		0,1,1,0,
		0,0,0,0 },
		{
		0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,1,0,0 },
		{ 
		0,0,0,0,
		1,1,0,0,
		0,1,1,0,
		0,0,0,0 },
		{ 
		0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,1,0,0 } 
	},
	{ 
		{ 
		0,0,0,0,
		0,1,1,0,
		1,1,0,0,
		0,0,0,0 },
		{ 
		0,0,0,0,
		1,0,0,0,
		1,1,0,0,
		0,1,0,0 },
		{ 
		0,0,0,0,
		0,1,1,0,
		1,1,0,0,
		0,0,0,0 },
		{ 
		0,0,0,0,
		1,0,0,0,
		1,1,0,0,
		0,1,0,0 } 
	},
	{ 
		{ 
		0,0,0,0,
		0,0,1,0,
		1,1,1,0,
		0,0,0,0 },
		{ 
		0,0,0,0,
		1,1,0,0,
		0,1,0,0,
		0,1,0,0 },
		{ 
		0,0,0,0,
		0,0,0,0,
		1,1,1,0,
		1,0,0,0 },
		{ 
		0,0,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,1,0 } 
	},
	{ 
		{ 
		0,0,0,0,
		1,0,0,0,
		1,1,1,0,
		0,0,0,0 },
		{ 
		0,0,0,0,
		0,1,0,0,
		0,1,0,0,
		1,1,0,0 },
		{ 
		0,0,0,0,
		0,0,0,0,
		1,1,1,0,
		0,0,1,0 },
		{ 
		0,0,0,0,
		0,1,1,0,
		0,1,0,0,
		0,1,0,0 } 
	},
	{ 
		{ 
		0,0,0,0,
		0,1,0,0,
		1,1,1,0,
		0,0,0,0 },
		{ 
		0,0,0,0,
		0,1,0,0,
		1,1,0,0,
		0,1,0,0 },
		{ 
		0,0,0,0,
		0,0,0,0,
		1,1,1,0,
		0,1,0,0 },
		{ 
		0,0,0,0,
		0,1,0,0,
		0,1,1,0,
		0,1,0,0 } 
	}
};


HBITMAP hBitmap;
RECT crt;



void OnCreate(HWND hWnd, HINSTANCE hInst)
{
	mHwnd = hWnd;
	mInst = hInst;
	srand(time(NULL));
}



void OnDraw(HDC hdc)
{
	HDC hMemDC;
	HBITMAP OldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	/////////////////////////////////////////////////////////////////////////////////////////

	for (int y= 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			Rectangle(hdc, RECT_WIDTH * x, RECT_HEIGHT * y, RECT_WIDTH * x + RECT_WIDTH, RECT_HEIGHT * y + RECT_HEIGHT);
			if (block[block_L][r][y][x] ==1)
			{
				HBRUSH hBrush, oBrush;
				hBrush = CreateSolidBrush(RGB(0,0, 0));
				oBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, RECT_WIDTH * x, RECT_HEIGHT * y, RECT_WIDTH * x + RECT_WIDTH, RECT_HEIGHT * y + RECT_HEIGHT);
				SelectObject(hdc, oBrush);
				DeleteObject(hBrush);
			}
		}
	}


	//////////////////////////////////////////////////////////////////
	//BitBlt(hdc, x*RECT_WIDTH, y*RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, hMemDC, RECT_WIDTH*sx,RECT_HEIGHT * sy, SRCCOPY);
	SelectObject(hMemDC, OldBitmap); 
	DeleteDC(hMemDC); // hMemDC Á¦°Å

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
		break;
	case VK_RIGHT:
		break;
	case VK_DOWN:
		r=(r+1)%4;
		break;
	case VK_UP:
		r=(r+3)%4;
		break;
	}
	InvalidateRect(hWnd, NULL, false);
}