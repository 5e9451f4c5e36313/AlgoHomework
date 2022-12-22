#pragma once
#include "stdafx.h"

class Box
{
private:
    int L;
    int W;
    int H;
    int rotateState;
public:
    Box(int l, int w, int h) : L(l), W(w), H(h), rotateState(0)
    {

    }
    int Volume() const
    {
        return H * W * L;
    }
    int Length() const
    {
        return this->L;
    }
    int Width() const
    {
        return this->W;
    }
    int Height() const
    {
        return this->H;
    }
    /// @brief ���ڵض����ӽ�����ת
    void Rotate()
    {
        //LWH->WLH->WHL->HWL->HLW->LHW->LWH���ɼ�����������ת����ǰ����Ԫ�أ�ż������ת����������Ԫ��
        //��������ת�ͻ�ָ�ԭ��
        if (rotateState == 0)
        {
            std::swap(L, W);
            rotateState = 1;
        }
        else
        {
            std::swap(W, H);
            rotateState = 0;
        }
    }
};

struct Point
{
    int x;
    int y;
    int z;
    Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
    {

    }
};

std::ostream& operator<<(std::ostream&, const Box&);
std::ostream& operator<<(std::ostream&, const Point&);