#include "Datastructure.h"
#include "stdafx.h"
#include "Solution.h"
#include "Dataset.h"

/// @brief ��������������������
/// @param argc �����в����ĸ�����ûʲô��
/// @param argv �����в�����ûʲô��
/// @return ���ظ�����ϵͳ��Ҫ����0�Ϳ�����������crash��
int main(int argc, char** argv)
{
    for (auto& x : datasets)
    {
        std::cout << x.first << ":" << std::endl;
        auto boxes = transform(x.second);
        firstFit(boxes, 587, 233, 220, false);
    }
    return 0;
}