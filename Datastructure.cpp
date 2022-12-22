#include "Datastructure.h"
#include "stdafx.h"

/// @brief ���ŵ�������ӵ���״
/// @param o �����
/// @param box Ҫ��ӡ��Box����
/// @return ����o��ΪʲôҪ��o��������Ϊ�������ã���������cout << box1 << box2 << endl;
std::ostream& operator<<(std::ostream& o, const Box& box)
{
    o << "(" << box.Length() << ", " << box.Width() << ", " << box.Height() << ")";
    return o;
}

/// @brief ���ŵ��������
/// @param o �����
/// @param point Ҫ��ӡ��point����
/// @return ����o��ΪʲôҪ��o��������Ϊ�������ã���������cout << box1 << box2 << endl;
std::ostream& operator<<(std::ostream& o, const Point& point)
{
    o << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    return o;
}