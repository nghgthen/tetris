#include "pch.h"
#include "CQuancoL2.h"

CQuancoL2::CQuancoL2(int mx, int my)
{
    x = mx;
    y = my;
    oco[0] = CHcnmau(x, y, x + RONG, y + RONG, 138, 43, 226);
    oco[1] = CHcnmau(x, y + RONG, x + RONG, y + 2 * RONG, 138, 43, 226);
    oco[2] = CHcnmau(x, y + 2 * RONG, x + RONG, y + 3 * RONG, 138, 43, 226);
    oco[3] = CHcnmau(x - RONG, y + 2 * RONG, x, y + 3 * RONG, 138, 43, 226);
    trangthai = 0;
}

void CQuancoL2::thietlap(int x, int y)
{
    this->x = x;
    this->y = y;
    if (trangthai == 0) {
        oco[0].thietlap(x, y, x + RONG, y + RONG);
        oco[1].thietlap(x, y + RONG, x + RONG, y + 2 * RONG);
        oco[2].thietlap(x, y + 2 * RONG, x + RONG, y + 3 * RONG);
        oco[3].thietlap(x - RONG, y + 2 * RONG, x, y + 3 * RONG);
    }
    if (trangthai == 1) {
        oco[0].thietlap(x, y + RONG, x + RONG, y + 2 * RONG);
        oco[1].thietlap(x - RONG, y + RONG, x, y + 2 * RONG);
        oco[2].thietlap(x - RONG, y, x, y + RONG);
        oco[3].thietlap(x + RONG, y + RONG, x + 2 * RONG, y + 2 * RONG);
    }
    if (trangthai == 2) {
        oco[0].thietlap(x, y + RONG, x + RONG, y + 2 * RONG);
        oco[1].thietlap(x, y, x + RONG, y +  RONG);
        oco[2].thietlap(x + RONG, y, x + 2 * RONG, y + RONG);
        oco[3].thietlap(x, y + 2 * RONG, x + RONG, y + 3 * RONG);
    }
    if (trangthai == 3) {
        oco[0].thietlap(x, y + RONG, x + RONG, y + 2 * RONG);
        oco[1].thietlap(x - RONG, y + RONG, x, y + 2 * RONG);
        oco[2].thietlap(x + RONG, y + RONG, x + 2 * RONG, y + 2 * RONG);
        oco[3].thietlap(x + RONG, y + 2 * RONG, x + 2 * RONG, y + 3 * RONG);
    }
}

void CQuancoL2::doiTrangThai()
{
    trangthai += 1;
    trangthai = trangthai % 4;
    thietlap(x, y);
}

void CQuancoL2::veTrangThaicu()
{
    trangthai += 3;
    trangthai = trangthai % 4;
    thietlap(x, y);
}

void CQuancoL2::rotate()
{
    doiTrangThai();
    thietlap(x, y);
}
