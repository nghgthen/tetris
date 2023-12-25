#include "pch.h"
#include "CBanco.h"
#include "CQuancoFactory.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

CBanco::CBanco()
{
	x = 50;
	y = 80;
	pc = nullptr;
	CQuancoFactory factory = CQuancoFactory();
	pnext = factory.create_quanco(x + (WIDTH * RONG) + 100, y + 50);
	control = 0;
	level = 1;
	diem = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			oco[i][j] = OCoMau(x + j * RONG, y + i * RONG, x + (j + 1) * RONG, y + (i + 1) * RONG, 255, 225, 225, 0);
		}
	}

}
void CBanco::draw(CClientDC* pdc) {

	//CPen pen();
	pdc->Rectangle(0, 0, x + 3000, y + 3000);
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* pOldPen = pdc->SelectObject(&pen);
	CBrush myBrush(RGB(169, 169, 169));
	CBrush* pOldBrush = pdc->SelectObject(&myBrush);
	pdc->Rectangle(x, y, x+ RONG * WIDTH, y + RONG * HEIGHT);

	for (int i = 1; i < HEIGHT; ++i) {
		pdc->MoveTo(x, y + RONG * i);
		pdc->LineTo(x + RONG * WIDTH, y + RONG * i);
	}
	for (int j = 1; j < WIDTH; ++j) {
		pdc->MoveTo(x + RONG * j, y);
		pdc->LineTo(x + RONG * j, y + RONG * HEIGHT);
	}


	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			//pdc->Rectangle(x + j * RONG, y + i * RONG, x + (j + 1) * RONG, y + (i + 1) * RONG);
			oco[i][j].draw(pdc);
		}
	}
	pdc->Rectangle(x + (RONG * WIDTH) + 30 , y  , x + (RONG * WIDTH) + 250 , y + RONG + 200);
	int startX = x + (RONG * WIDTH) + 30;
	int startY = y;
	int endX = x + (RONG * WIDTH) + 250;
	int endY = y + RONG + 200;

	pdc->Rectangle(startX, startY, endX, endY);

	for (int i = 1; i < 5; ++i) {
		pdc->MoveTo(startX, startY + RONG * i);
		pdc->LineTo(endX, startY + RONG * i);
	}
	for (int j = 1; j < 5; ++j) {
		pdc->MoveTo(startX + RONG * j, startY);
		pdc->LineTo(startX + RONG * j, endY);
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			oco[i][j].draw(pdc);
		}
}
	pdc->SelectObject(pOldPen);
	pdc->SelectObject(pOldBrush);

	

	CString strLevel;

	// xuat Level: level=1
	strLevel.Format(_T("Level: % d"), level);
	CRect rect1(50, 0, WIDTH * RONG, 40);
	pdc->DrawText(strLevel, rect1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	// Xuat Point: diem=0
	strLevel.Format(_T("Point: % d"), diem);
	CRect rect2(50, 40, WIDTH * RONG, 80);
	pdc->DrawText(strLevel, rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	strLevel.Format(_T("Next"));
	CRect rect3(x + (RONG * WIDTH) + 30, y, x + (RONG * WIDTH) + 250, y + RONG - 20);
	pdc->DrawText(strLevel, rect3, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	//draw quanco
	if (pc != nullptr) {
		pc->draw(pdc, y);
	}
	if (pnext != nullptr) {
		pnext->draw(pdc, y);
	}
}


void CBanco::start()
{
	CQuancoFactory factory = CQuancoFactory();
	control = 1;
	diem = 0;
	level = 1;
	pc = factory.create_quanco(x + int(WIDTH / 2) * RONG - RONG, y - 4 * RONG);
	PlaySound(TEXT("nhacnen.mp3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	
}


int CBanco::kiemtra_dixuong() {
	int kq = 1;

	CQuanco originalPiece = *pc;
	pc->goDown();

	for (int i = 0; i < 4; i++) {
		if (pc->oco[i].y2 > y) {
			toado vitri = timIJ(pc->oco[i]);
			if (vitri.i >= HEIGHT || oco[vitri.i][vitri.j].gt == 1) { 
				kq = 0;
				break; 
			}
		}
	}

	*pc = originalPiece;

	return kq;
}


int CBanco::kiemtra_quatrai()
{
	pc->goLeft();
	int kq = 1; // di chuyen dc
	int i = 0;
	toado vitri;
	while (i < 4 && kq == 1)
	{
		if (pc->oco[i].x1 < x)
			kq = 0;
		//kiemtraocotren ban co bi chiem hay chua
		vitri = timIJ(pc->oco[i]);
		if (vitri.i > 0 && oco[vitri.i][vitri.j].gt == 1)
			kq = 0;

		i++;
		if (kq == 0) {
			i++;
		}
	}
	pc->goRight();
	return kq;
}

int CBanco::kiemtra_quaphai() {
	int x2 = x + WIDTH * RONG;

	pc->goRight();

	int kq = 1; 
	int i = 0;

	while (i < 4 && pc->oco[i].x2 <= x2 && kq == 1) {
		toado vitri = timIJ(pc->oco[i]);

		if (vitri.j >= WIDTH || (vitri.i >= 0 && oco[vitri.i][vitri.j].gt == 1)) {
			kq = 0; 
		}

		i++;
	}

	if (i < 4) {
		kq = 0;
	}

	pc->goLeft();

	return kq;
}

int CBanco::kiemtra_xoay()
{
	pc->doiTrangThai();

	int kq = 1;
	int x2 = x + WIDTH * RONG;
	int y2 = y + HEIGHT * RONG;
	int i = 0;

	while (i < 4 && kq == 1) {
		if (pc->oco[i].x1 < x || pc->oco[i].x2 > x2 || pc->oco[i].y2 > y2) {
			kq = 0;
		}
		else {
			toado vitri = timIJ(pc->oco[i]);
			if (vitri.i >= 0 && vitri.i < HEIGHT && vitri.j >= 0 && vitri.j < WIDTH && oco[vitri.i][vitri.j].gt == 1) {
				kq = 0; 
			}
		}
		i++;
	}

	pc->veTrangThaicu();
	return kq;
}
void CBanco::play(CClientDC* pdc)
{
	int tam = 0;
	int initialSpeed = 1000;
	int speed = initialSpeed;
	do {
		while (kiemtra_dixuong()) {
			pc->goDown();
			draw(pdc);
			Sleep(speed);
		}
			transfer_banco(pdc);
			spawn_quanco();
			tam++;
			if (level == 1) {
				speed = initialSpeed;
			}
			else if (level == 2) {
				//diem += 10;
				speed = 800;
			}
			else if (level == 3) {
				//diem += 20;
				speed = 600;
			}
			else if (level == 4) {
				speed = 400;
			}
			else if (level == 5) {
				speed = 200;
			}
			if (diem >= 30 * level) {
				level++;
			}
	} while (kiemtra_dixuong());
	
}

toado CBanco::timIJ(CHcnmau oco)
{
	toado kq = toado();
	kq.j = (oco.x1 - x) / RONG;
	kq.i = (oco.y1 - y) / RONG;

	return kq;
}

void CBanco::clear_banco(int mi) {
	int i = mi;
	int j = 0;
	while (i > 0) {
		for (int j = 0; j < WIDTH; j++) {
			oco[i][j].gt = oco[i - 1][j].gt;
			oco[i][j].r = oco[i - 1][j].r;
			oco[i][j].g = oco[i - 1][j].g;
			oco[i][j].b = oco[i - 1][j].b;
		}
		i--;
	}
	for (int j = 0; j < WIDTH; j++) {
		oco[0][j].gt = 0;
		
	}
}

void CBanco::transfer_banco(CClientDC* pdc)
{
	for (int i = 0; i < 4; i++) {
		toado vitri = timIJ(pc->oco[i]);
		oco[vitri.i][vitri.j].gt = 1;
		oco[vitri.i][vitri.j].r = pc->oco[i].r;
		oco[vitri.i][vitri.j].g = pc->oco[i].g;
		oco[vitri.i][vitri.j].b = pc->oco[i].b;
	}
	int i = HEIGHT - 1;
	int j = 0;
	int tong = 0;
	int dem = 0;
	while (i > 0) {
		tong = 0;
		for (int j = 0; j < WIDTH; j++) {
			tong += oco[i][j].gt;
		}
		if (tong == WIDTH) {
			diem += 10;
			clear_banco(i);
			draw(pdc);
			Sleep(300);
			dem++;
		}else
			i--;
	}
	if (dem == 4) {
		diem += 60;
	}
}

void CBanco::spawn_quanco()
{
	CQuancoFactory factory = CQuancoFactory();
	delete pc;
	pc = pnext;
	pc->thietlap(x + int(WIDTH / 2)* RONG - RONG, y - 2 * RONG);
	pnext = factory.create_quanco(x + (WIDTH * RONG) + 100, y + 50);

}

void CBanco::goDown(CClientDC* pdc)
{
	int tam = 0;
		if (kiemtra_dixuong()) {
			pc->goDown();
			draw(pdc);
		}
}

void CBanco::goLeft(CClientDC* pdc)
{
	if (kiemtra_quatrai()) {
		pc->goLeft();
		draw(pdc);
	}
}

void CBanco::goRight(CClientDC* pdc)
{
	if(kiemtra_quaphai()) {
		pc->goRight();
		draw(pdc);
	}
}

void CBanco::rotate(CClientDC* pdc)
{
	if (kiemtra_xoay()) {
		pc->rotate();
		draw(pdc);
	}
}

bool CBanco::kiemtrathua(CClientDC* pdc)
{
	if (!kiemtra_dixuong()) {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (oco[i][j].gt == 1 && oco[i][j].y1 == y) {
					CString strFail = _T("Game Over - You Lose!");
					CRect rectFail(50, 650, WIDTH * RONG + 50 , 120);
					pdc->DrawText(strFail, rectFail, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					CString strInfo;
					strInfo.Format(_T("Point: %d - Level: %d"), diem, level);
					CRect rectInfo(50, 700, WIDTH * RONG + 50, 170);
					pdc->DrawText(strInfo, rectInfo, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					PlaySound(TEXT("path_to_your_sound_file.wav"), NULL, SND_FILENAME | SND_ASYNC);

					return true;
				}
			}
		}
	}
	return false;
	
}

