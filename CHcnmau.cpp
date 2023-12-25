#include "pch.h"
#include "CHcnmau.h"



CHcnmau::CHcnmau()
{
	r = 0;
	g = 0;
	b = 0;
}
CHcnmau::CHcnmau(int mx1, int my1, int mx2, int my2, int mr, int mg, int mb): CHcn (mx1,my1,mx2,my2)
{
	r = mr;
	g = mg;
	b = mb;
}



void CHcnmau::draw(CClientDC* pdc)
{
	CPen pen(PS_SOLID, 3, RGB(150, 150, 0));
	CPen* pOldPen = pdc->SelectObject(&pen);
	CBrush myBrush(RGB(r, g, b));
	CBrush* pOldBrush = pdc->SelectObject(&myBrush);
	pdc->Rectangle(x1, y1, x2, y2);
	pdc->SelectObject(pOldPen);
	pdc->SelectObject(pOldBrush);
}
