#include "pch.h"
#include "OCoMau.h"

OCoMau::OCoMau()
{
	gt = 0;
}

void OCoMau::draw(CClientDC* pDC)
{
	if (gt == 1) {
		CPen pen(PS_SOLID, 3, RGB(150, 150, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush myBrush(RGB(r, g, b));
		CBrush* pOldBrush = pDC->SelectObject(&myBrush);
		pDC->Rectangle(x1, y1, x2, y2);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
}
