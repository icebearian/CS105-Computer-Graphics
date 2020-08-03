#pragma once
class CLine
{
public:
	static void LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color);
	static void LineDDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);

	static void LineBressenham(CDC* pDC, CPoint A, CPoint B, COLORREF color);
	static void LineBressenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);

	static void Midpoint(CDC* pDC, CPoint A, int R, COLORREF color);
	static void Midpoint(CDC* pDC, int x1, int y1,int R, COLORREF color);
	
private:
	//hàm dùng cho vẽ đường thẳng tăng chậm/giảm chậm
	static void _LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	//hàm dùng cho vẽ đường thẳng tăng nhanh/giảm nhanh
	static void _LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	
	static void _LineBressenham1(CDC * pDC, int x1, int y1, int x2, int y2, COLORREF color);
	
	static void _LineBressenham2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
};

