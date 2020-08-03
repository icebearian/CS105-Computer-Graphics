#include "pch.h"
#include "CLine.h"
#include "math.h"
#define Round(x) (int) (x + 0.5)

void CLine::LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color)
{
	LineDDA(pDC, A.x, A.y, B.x, B.y, color);
}

void CLine::LineDDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	//Nếu 2 điểm A - B trùng nhau
	if (x1 == x2 && y1 == y2)
	{
		//Chỉ vẽ 1 điểm
		pDC->SetPixel(x1, y1, color);
		return;
	}
	if (abs(x2 - x1) >= abs(y2 - y1))
	{
		if (x1 <= x2)
		{
			_LineDDA1(pDC, x1, y1, x2, y2, color);
		}
		else
			_LineDDA1(pDC, x2, y2, x1, y1, color);
	}
	else
		if (y1 <= y2)
			_LineDDA2(pDC, x1, y1, x2, y2, color);
		else
			_LineDDA2(pDC, x2, y2, x1, y1, color);
}
//tăng chậm/giảm chậm lặp theo x
void CLine::_LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	//xác định điểm đầu tiên
	pDC->SetPixel(x1, y1, color);
	float m = (float)(y2 - y1) / (x2 - x1);
	float y = float(y1);
	while (x1 < x2)
	{
		x1 = x1 + 1;
		y = y + m;
		pDC->SetPixel(x1, Round(y), color);
	}
}
//tăng nhanh / giảm nhanh lặp theo y
void CLine::_LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	//xác định điểm đầu tiên
	pDC->SetPixel(x1, y1, color);
	float m = (float)(x2 - x1) / (y2 - y1);
	float x = float(x1);
	while (y1 < y2)
	{
		y1 = y1 + 1;
		x = x + m;
		pDC->SetPixel(Round(x), y1, color);
	}
}

void CLine::LineBressenham(CDC* pDC, CPoint A, CPoint B, COLORREF color)
{
	LineBressenham(pDC, A.x, A.y, B.x, B.y, color);
}
void CLine::LineBressenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	if (x1 == x2 && y2 == y1)
		pDC->SetPixel(x1, y1, color);
	else  
	{
		if (abs(x2 - x1) > abs(y2 - y1))
		{
			if (x1 < x2)
				_LineBressenham1(pDC, x1, y1, x2, y2, color);
			else
				_LineBressenham1(pDC, x2, y2, x1, y1, color);
		}
		else
		{
			if (x1 < x2)
				_LineBressenham2(pDC, x1, y1, x2, y2, color);
			else
				_LineBressenham2(pDC, x2, y2, x1, y1, color);
		}
	}
}


void CLine:: _LineBressenham2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	int Dx = x2 - x1;
	int Dy = y2 - y1;
	int x = x1, y = y1;
	int dx = (Dx < 0) ? -1 : 1;
	int dy = (Dy < 0) ? -1 : 1;
	pDC->SetPixel(x, y, color);
	Dx = abs(Dx);
	Dy = abs(Dy);
	if (Dy > Dx)
	{
		int p = (Dx << 1) - Dy;
		int Const1 = Dx << 1, Const2 = (Dx - Dy) << 1;
		while (y != y2)
		{
			if (p < 0)
			{
				p += Const1;
			}
			else
			{
				p += Const2;
				x += dx;
			}
			y += dy;
			pDC->SetPixel(x, y, color);
		}
	}
}


void CLine::_LineBressenham1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	int Dx = x2 - x1;
	int Dy = y2 - y1;
	int x = x1, y = y1;
	int dx = (Dx < 0) ? -1 : 1;
	int dy = (Dy < 0) ? -1 : 1;
	pDC->SetPixel(x, y, color);
	Dx = abs(Dx);
	Dy = abs(Dy);
	if (Dx > Dy)
	{
		int p = (Dy << 1) - Dx;
		int Const1 = Dy << 1, Const2 = (Dy - Dx) << 1;
		while (x != x2)
		{
			if (p < 0)
			{
				p += Const1;
			}
			else
			{
				p += Const2;
				y += dy;
			}
			x += dx;
			pDC->SetPixel(x, y, color);
		}
	}
}

void CLine::Midpoint(CDC* pDC, CPoint A, int R, COLORREF color)
{
	Midpoint(pDC, A.x, A.y, R, color);
}

void CLine::Midpoint(CDC* pDC, int x1, int y1, int R, COLORREF color)
{
	int x, y, d;
	x = 0;
	y = R;
	d = 1 - R;
	while (x <= y)
	{
		pDC->SetPixel(x1 + x, y1 + y, color);
		pDC->SetPixel(x1 - x, y1 + y, color);
		pDC->SetPixel(x1 + x, y1 - y, color);
		pDC->SetPixel(x1 - x, y1 - y, color);
		pDC->SetPixel(x1 + y, y1 + x, color);
		pDC->SetPixel(x1 - y, y1 + x, color);
		pDC->SetPixel(x1 + y, y1 - x, color);
		pDC->SetPixel(x1 - y, y1 - x, color);

		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
