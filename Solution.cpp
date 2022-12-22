#include "Datastructure.h"
#include "Solution.h"
#include "stdafx.h"

/// @brief �������������壬�ж����߿ռ����Ƿ����ص�
/// @param b1 ��һ����������״
/// @param p1 ��һ������������
/// @param b2 �ڶ�����������״
/// @param p2 �ڶ�������������
/// @return �ǣ�true����false���ص�
bool rectangleCross(const Box& b1, const Point& p1, const Box& b2, const Point& p2)
{
    return !(p2.x >= (p1.x + b1.Length()) || (p2.x + b2.Length()) <= p1.x ||
        p2.y >= (p1.y + b1.Width()) || (p2.y + b2.Width()) <= p1.y ||
        p2.z >= (p1.z + b1.Height()) || (p2.z + b2.Height()) <= p1.z
        );
}

/// @brief ��������������
/// @param box Ҫ���õ�����
/// @param target ��Ҫ���õ�����
/// @param Loaded �Ѿ���װ�������
/// @return box�ܷ����target
bool canLoad(const Box& box, const Point& target, const std::vector<std::pair<Point, Box>>& Loaded, int carriageLength, int carriageWidth, int carriageHeight)
{
    //ֻҪ�ж�(target.x + box.Length(), target.y + box.Width(), target.z + box.Height()�����������û�����Ӿ�����
    for (const auto& loaded : Loaded)
    {
        bool overLength = (target.x + box.Length()) > carriageLength;
        bool overWidth = (target.y + box.Width()) > carriageWidth;
        bool overHeight = (target.z + box.Height()) > carriageHeight;
        bool cross = rectangleCross(box, target, loaded.second, loaded.first);
        if (cross || overLength || overWidth || overHeight)
            return false;
    }
    return true;
}

void firstFit(std::vector<Box>& boxes, int carriageLength, int carriageWidth, int carriageHeight, bool shuffle = false)
{
    auto t1 = clock();
    if (!shuffle) std::sort(boxes.begin(), boxes.end(), [](const Box& l, const Box& r)->bool {return l.Volume() > r.Volume(); });
    else std::shuffle(boxes.begin(), boxes.end(), std::mt19937());
    std::vector<std::pair<Point, Box>> LoadedBoxes;
    int loadedVolume = 0;
    int loadedNum = 0;
    for (size_t i = 0; i < boxes.size(); ++i)
    {
        //���һ�����Ӷ���û�Ž�ȥ
        if (LoadedBoxes.empty())
        {
            //��������������5����ת����6����ת�ͻָ�ԭ����
            //��ת��ζ��Ų���ȥ��ֱ���ӵ�
            for (int j = 0; j < 5; ++j)
            {
                //�����ĳ��״̬�ܷŽ�ȥ���Ǿ�ֱ�ӷŽ�ȥ
                if (boxes[i].Length() <= carriageLength && boxes[i].Width() <= carriageWidth && boxes[i].Height() <= carriageHeight)
                {
                    LoadedBoxes.push_back(std::pair<Point, Box>(Point(0, 0, 0), boxes[i]));
                    loadedVolume += boxes[i].Volume();
                    ++loadedNum;
                    break;
                }
                //��������ӽ�����ת�����5��
                else
                {
                    boxes[i].Rotate();
                }
            }
        }
        //�������ӱ�����
        /*���״���Ӧ�㷨�У�����ÿ���Ѿ����õ����ӣ���Ϊp������������Ϊ(p.x, p.y, p.z)��
        ������׼�������ֱ�Ϊ(p.x, p.y, p.z + height)��(x, y + width, z)��(x + length, y, z)
        ֻ��Ҫ�ж�box�ܷ�ŵ��������㼴��
        ���ж��������������������ӣ���ȥ�ж�֮ǰÿһ����װ������ӻ᲻�ᵲ���������
        */
        else
        {
            for (const auto& loaded : LoadedBoxes)
            {
                bool flag = false;
                Point pos1 = Point(loaded.first.x, loaded.first.y, loaded.first.z + loaded.second.Height());
                Point pos2 = Point(loaded.first.x, loaded.first.y + loaded.second.Width(), loaded.first.z);
                Point pos3 = Point(loaded.first.x + loaded.second.Length(), loaded.first.y, loaded.first.z);
                for (int j = 0; j < 5; ++j)
                {
                    if (canLoad(boxes[i], pos1, LoadedBoxes, carriageLength, carriageWidth, carriageHeight))
                    {
                        LoadedBoxes.push_back(std::pair<Point, Box>(Point(pos1), boxes[i]));
                        loadedVolume += boxes[i].Volume();
                        ++loadedNum;
                        flag = true;
                        break;
                    }
                    if (canLoad(boxes[i], pos2, LoadedBoxes, carriageLength, carriageWidth, carriageHeight))
                    {
                        LoadedBoxes.push_back(std::pair<Point, Box>(Point(pos2), boxes[i]));
                        loadedVolume += boxes[i].Volume();
                        ++loadedNum;
                        flag = true;
                        break;
                    }
                    if (canLoad(boxes[i], pos3, LoadedBoxes, carriageLength, carriageWidth, carriageHeight))
                    {
                        LoadedBoxes.push_back(std::pair<Point, Box>(Point(pos3), boxes[i]));
                        loadedVolume += boxes[i].Volume();
                        ++loadedNum;
                        flag = true;
                        break;
                    }
                    //�������װ�ز���ȥ����ô����תһ��
                    boxes[i].Rotate();
                }
                //��Ȼ�Ѿ����ȥ�ˣ��Ͳ����жϺ���Ŀ�᲻�ᵲס��
                if (flag) break;
            }
        }
    }
    auto t2 = clock();
    std::cout << "�Ž�ȥ" << loadedNum << "����" <<  "�����" << loadedVolume * 100.0 / (carriageHeight * carriageLength * carriageWidth) << "%��" << "��ʱ" << (double)(t2 - t1) / CLOCKS_PER_SEC << "s��" << std::endl;
    for (const auto& i : LoadedBoxes)
    {
        std::cout << "λ�ã�" << i.first << "����״��" << i.second << std::endl;
    }
}