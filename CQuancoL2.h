#pragma once
#include "CQuanco.h"
class CQuancoL2 :
    public CQuanco
{
public:
    CQuancoL2(int mx, int my);
    void thietlap(int x, int y);
    void doiTrangThai();
    void veTrangThaicu();
    void rotate();
};

