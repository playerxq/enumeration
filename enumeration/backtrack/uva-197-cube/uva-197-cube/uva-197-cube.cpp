// uva-197-cube.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
�߿���Ƭ��ģʽ����ͼ�и����ģ����ܹ��ı�������״��Ҫ��Ľ���������߿���Ƭ��ĳ����Ϸ�ʽ����ͬ�Ŀռ�λ�ã�����ϳ�Ϊһ�������������塣��Ŀ������ʱ����30��֮�࣬������������Ҫ���������ˡ�������������27С�鹹�ɣ�������Ŀ�и��������Ի�Ҫ��ÿ��С���Ӧ�Ŀռ�����������̶���ŵġ����ǰ���ֱ������ϵ��ÿ��С��궨�������꣺

 1: (0, 2, 2),  2: (1, 2, 2),  3: (2, 2, 2),
 4: (0, 1, 2),  5: (1, 1, 2),  6: (2, 1, 2),
 7: (0, 0, 2),  8: (1, 0, 2),  9: (2, 0, 2),
10: (0, 2, 1), 11: (1, 2, 1), 12: (2, 2, 1),
13: (0, 1, 1), 14: (1, 1, 1), 15: (2, 1, 1),
16: (0, 0, 1), 17: (1, 0, 1), 18: (2, 0, 1),
19: (0, 2, 0), 20: (1, 2, 0), 21: (2, 2, 0),
22: (0, 1, 0), 23: (1, 1, 0), 24: (2, 1, 0),
25: (0, 0, 0), 26: (1, 0, 0), 27: (2, 0, 0),

��ʵ�ϣ���ЩС��������ǿ����ó���ѭ������ģ��������ȫ��ȡֵֻ��Ϊ�˷��������㷨������
�۲�7����Ƭ����bΪ3С�鹹��֮�⣬��������4С�鹹�ɡ�
��Щ��Ƭ���������ʱ�����е�ÿ��С��һ����λ��(0, 0, 0)��(2, 2, 2)�������ڵġ�
����Ҫ����һ��������Ρ�������ָһ����Ƭ����������ͨ����ת��ƽ�ƴﵽ��һ����̬��
������ÿһ��С�鶼û�г��������������߽硣
�����27��2�������ֱ�����������е�27�������Ƿ����С���飨1��ʾ��Ӧλ����һ��С���飬0��ʾû�У���
��ô��27����һ�����Ա�ʾ��7����Ƭ���κ�һ�ֹ��Ρ�һ��unsigned long������32λ���㹻��ʾ��һ����Ƭ����һ����̬��
����ֱ����7����Ƭ�ĸ���һ����̬��7��2��������(b1 | b2 | b3 | b4 | b5 | b6 | b7) = 0x07ffffff��
��˵��7����Ƭ����Щ��̬����������������塣
��������c��û�з��κ���Ƭʱc=0������һ����Ƭb����c:=c|b�����b�����λ����c���Ѿ�����С���飬
���У�~b & c != c������������Щ���ʽ��������㷨��˼·�ͺ������ˡ�
����ֻҪ����ÿһ����Ƭ�����й��Σ�Ȼ����DFS�ķ�ʽ�����Ϊ��ͬ��Ƭ�����ɱ������������п��ܵ���Ϸ�ʽ��

�������������������ÿһ����Ƭ�����й��Ρ���ʽ�кܶ��֣����������ά����任�е���ת����ʽ��
һ����Ƭ����ת�������24�ֲ�ͬ�ķ�ʽ����ʵ��ֻ����Ƭa����24�֣�
��������Ƭ��24����ת��һ����һЩת��Ľ������ͬ�ģ�������Ҫһ��ռ�����������
����Ҫ������24����ת����3x3���󣩣�����һ����x��ת��y��ת��z��ת����ϣ�
ÿһ����ת�ĽǶȿ�ѡ��0����/2���к�-��/2��
����������64�־���ȥ�غ�ͻ�ʣ�²�ͬ��24�֡����������������ʽ�ֶ�����ÿһ����Ƭ��
Ȼ�����ÿһ����Ƭ��24�ֲ�ͬ��ת������˷���������Ҫע���ʱ������������ֶ��������Ƭ������ת�����������Ƭ��
��Ҫͨ��ƽ��ʹ֮��ס�������x=0��y=0��z=0����ƽ�棬Ҳ�����������ڲ�Խ������߽��ǰ���¾����ܵĿ��������������ԭ�㡣
����ÿһ����Ƭ��������ת֮�󣬾Ϳ��Զ���ÿһ����ת����ƽ�ƣ��Ӷ��õ�ÿһ����Ƭ�����й��Ρ�
*/

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <vector>
//#include <vector.h>
#include <string>
#include <memory.h>
 
struct POINT3       // ����ÿ�����������Ľṹ��
{
    int x;
    int y;
    int z;
};
typedef std::vector<POINT3> COORDS;       // ���Ͷ��壬��ʾͼ��7��piece������
typedef unsigned long FORMMASK;         // ���Ͷ��壬��ʾÿһ��piece������ת��ƫ��֮�������һ�ֹ��͵�����
typedef std::vector<FORMMASK> VECFORMMASK;    // ���Ͷ��壬һ��piece�����뼯��
typedef std::vector<VECFORMMASK> ALLPIECEFORMS;   // ���Ͷ��壬����piece�����뼯��
typedef std::vector<int> MATRIX;      // ���Ͷ��壬��ʾ����
typedef std::vector<MATRIX> ROTMATS;  // ���Ͷ��壬��ʾ����ļ���
ALLPIECEFORMS allPieceForms;            // ȫ�ֱ������洢����piece������ת��ƫ�ƺ������
ALLPIECEFORMS result;                   // ȫ�ֱ������洢���յĽ��
ROTMATS rotMats;                        // ȫ�ֱ������洢��ת����
 
// ��λ����ֱ���X��Y��Z����ת0�㡢90�㡢180�㡢270����Ӧ�ľ���
/*
[1    0        0       0]

[0   cons(a)��sin(a)   0]

[0   -sin(a)  cos(a)   0]

[0    0        0       1] 
//////////////////////////////////////
[cos(a)  0    -sin(a)  0]

[0   1 ��0    0]

[sin(a)  0    cos(a)   0]

[0       0        0    1]
/////////////////////////////////////
[cos(a)  sin(a)   0    0]

[-sin(a) cos(a)   0 �� 0]

[0       0        1    0]    

[0       0        0    1]

��
1 0 0
0 1 0
0 0 1��� ����ͬ�Ƕȴ��뼴��
*/
int rotateMatX[][9] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, -1, 0, 1, 0},
    {1, 0, 0, 0, -1, 0, 0, 0, -1},
    {1, 0, 0, 0, 0, 1, 0, -1, 0}
};
int rotateMatY[][9] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0, -1, 0, 0},
    {-1, 0, 0, 0, 1, 0, 0, 0, -1},
    {0, 0, -1, 0, 1, 0, 1, 0, 0}
};
int rotateMatZ[][9] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, -1, 0, 1, 0, 0, 0, 0, 1},
    {-1, 0, 0, 0, -1, 0, 0, 0, 1},
    {0, 1, 0, -1, 0, 0, 0, 0, 1}
};
// ��Ŀͼ��7��piece��Ӧ�Ŀռ����꣬˳��Ϊa��f��g��e��c��d��b�������½�Ϊԭ��(0,0,0)
POINT3 pieces[][4] = {
    {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 2, 0}},
    {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {1, 1, 1}},
    {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}},
    {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {0, 1, 1}},
    {{0, 1, 0}, {1, 0, 0}, {1, 1, 0}, {1, 2, 0}},
    {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {1, 0, 2}},
    {{0, 0, 0}, {1, 0, 0}, {0, 0, 1},}
};
char nameMap[] = {'a', 'f', 'g', 'e', 'c', 'd', 'b'};
// ֱ������ϵ����Ŀ����ϵ��λ�ñ�Ŷ�Ӧ��
//��Ŀ���ĵ�k���ַ���Ӧ����ϵ��posMap[k]
char posMap[] = {24, 25, 26, 21, 22, 23, 18, 19, 20, 15, 16, 17, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};

bool operator < (const POINT3 &p1, const POINT3 &p2)
{
    return (p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y) ||
        (p1.x == p2.x && p1.y == p2.y && p1.z < p2.z));
}
 
bool operator == (const POINT3 &p1, const POINT3 &p2)
{
    return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}
// �������˷���������������pM1��pM2���������һ��������������ڶ�������������Լ�����Ĵ�С�����������˵Ľ��pR��
void MatMul(int *pM1, int *pM2, int r1, int c2, int n, int *pR)
{
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            pR[i * c2 + j] = 0;
            for (int k = 0; k < n; ++k)
                pR[i * c2 + j] += pM1[i * n + k] * pM2[k * c2 + j];
        }
    }
}
// ��������෴��
POINT3 Inverse(POINT3 &coord)
{
    coord.x = -coord.x;
    coord.y = -coord.y;
    coord.z = -coord.z;
    return coord;
}
// �ҳ�һ��piece���������ĵ��������С�ĵ�
void Bound(const COORDS &coords, POINT3 &min, POINT3 &max)
{
    min = max = coords[0];
    for (size_t i = 1; i < coords.size(); ++i) {
        if (coords[i].x < min.x) min.x = coords[i].x;
        if (coords[i].x > max.x) max.x = coords[i].x;
        if (coords[i].y < min.y) min.y = coords[i].y;
        if (coords[i].y > max.y) max.y = coords[i].y;
        if (coords[i].z < min.z) min.z = coords[i].z;
        if (coords[i].z > max.z) max.z = coords[i].z;
    }
}
// ����piece���������Сֵ�����һ��piece����ƫ��ת��ʱ��ƫ�Ƶ����λ��
void PieceSize(const COORDS &coords, POINT3 &size)
{
    POINT3 minCoord;
    Bound(coords, minCoord, size);//sizeΪ����ӿ�  mincoordΪ��С 
    size.x -= minCoord.x;
    size.y -= minCoord.y;
    size.z -= minCoord.z;
}
// piece��ƫ��ת��
void Translate(COORDS &coords, const POINT3 &dist)
{
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i].x += dist.x;
        coords[i].y += dist.y;
        coords[i].z += dist.z;
    }
}
// ����һ��piece�����룬����piece�и��������λ����������������յĽ�������г��ֵ�λ�á�
FORMMASK Coords2Mask(COORDS &coords)
{
    FORMMASK ulMask = 0;
    for (COORDS::iterator j = coords.begin(); j != coords.end(); ++j) {//����ÿ����״��ÿ���ӿ������
        ulMask |= (1 << (j->x + j->y * 3 + j->z * 9));//������123456.����������� xΪ���� yΪ3��һ�� zΪһ�㼴9��һ��
    }
    return ulMask;
}
// ��ת��ƫ��ת��3��3��3���飬forms��¼����piece�����й�������
//pieceΪ��ʼ����  nΪ�ӿ���Ŀ
void ExpandForms(const POINT3 *pPiece, int n, VECFORMMASK &forms)
{
    COORDS coords(pPiece, pPiece + n), rotCoords(n);//��Piece��ʼ��coords,�����ʼ����  rotCoords����������м�ֵ
    POINT3 minCoord, size;
    std::sort(coords.begin(), coords.end());
 
    // rots��¼����piece��������ת
    std::vector<COORDS> rots;
 
    // ������е���ת���ͣ���������ת��ԭ���ͣ���λ�󣩣�ÿһ����ת���������24����ͬ����
    for (ROTMATS::iterator i = rotMats.begin(); i != rotMats.end(); ++i) {//ȡ��һ����ת����
        for (int j = 0; j < n; ++j) {//��ÿ���ӿ�������б任
            MatMul(i->data(), (int*)&coords[j], 3, 1, 3, (int*)&rotCoords[j]);
        }
        // ���ÿһ����ת���ͣ�ʹ��ת��ķ����������½ǵ�С����Ϊԭ��
        Bound(rotCoords, minCoord, size);
        Translate(rotCoords, Inverse(minCoord));//����С���ƶ���ԭ��
        std::sort(rotCoords.begin(), rotCoords.end());//�����ص����������
        rots.push_back(rotCoords);
    }
    // ȥ���ظ�����ת����
    std::sort(rots.begin(), rots.end());
    rots.erase(std::unique(rots.begin(), rots.end()), rots.end());
    size_t nRotCnt = rots.size();
    // ��ÿһ����ת����ƫ�ƣ������µ�ƫ�ƹ��ͣ�ÿһ��piece����6��ƫ�ƹ���
    for (size_t i = 0; i != nRotCnt; ++i) {
        PieceSize(rots[i], size);//size������x y z�������ӿ�λ�ò�  3��ȥ�˲Ϊ�������ɴ˷����ϵ����λ��
        for (minCoord.x = 0; minCoord.x < 3 - size.x; ++minCoord.x) {
            for (minCoord.y = 0; minCoord.y < 3 - size.y; ++minCoord.y) {
                for (minCoord.z = 0; minCoord.z < 3 - size.z; ++minCoord.z) {
                    if (minCoord.x != 0 || minCoord.y != 0 || minCoord.z != 0) {
                        rots.push_back(rots[i]);
                        Translate(rots.back(), minCoord);
                    }
                }
            }
        }
    }
    // ������Ӧ���͵�����
    for (std::vector<COORDS>::iterator i = rots.begin(); i != rots.end(); ++i) {
        forms.push_back(Coords2Mask(*i));
    }
}
// �ݹ�Ĳ������е�7��piece����Ͻ����path�м�¼ÿһ����ϵ�����piece������
void FillCube(ALLPIECEFORMS::const_iterator curForm, FORMMASK nCube, VECFORMMASK &path)
{
    // �ݹ����������ÿһ����ϵ�������ȫ���
    if (nCube == 0x07ffffff) {
        result.push_back(path);
        return;
    }
    const FORMMASK *pForms = curForm->data();//ȡ��һ�����뼯  ��Ϊĳ��piece���ֱ任���������
    size_t nFormCnt = curForm->size();
    for (size_t i = 0; i < nFormCnt; ++i) {
        // �жϵ�ǰ���������Ƿ���ĳһpiece�����룬��û�У����޸ĵ�ǰ���룬����path�м�¼piece
        if (((~pForms[i]) & nCube) == nCube) {
            unsigned long nTmpCube = nCube | pForms[i];
            path.push_back(pForms[i]);
            FillCube(curForm + 1, nTmpCube, path);//����һ��piece
            path.pop_back();
        }
    }
}
 
int main(void)
{
    // ������ת���󣬹���24����ת������磺��XY����ת90�㣬��XZ����ת180���
    for (int i = 0; i < 4; ++i) {//����rotateMatX rotateMatY rotateMatZ���������
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                int tmp1[9];
                rotMats.push_back(std::vector<int>(9));
                MatMul(rotateMatY[j], rotateMatZ[k], 3, 3, 3, tmp1);
                MatMul(rotateMatX[i], tmp1, 3, 3, 3, rotMats.back().data());
            }
        }
    }
    std::sort(rotMats.begin(), rotMats.end());
    rotMats.erase(std::unique(rotMats.begin(), rotMats.end()), rotMats.end());//ȥ���ظ�
 
    // ��ʼ��piece��������ת��ƫ�ƵĹ���
    allPieceForms.resize(7);
    for (int i = 0; i < 7; ++i) {//�Ե�i��piece  piece[i]Ϊ��ʼ�����ӿ����� ���㾭��������ת�����γɵ��ӿ���������� piece��nameMap�е�˳��
        ExpandForms(pieces[i], 4 - (i / 6), allPieceForms[i]);//ֻ�����һ����3���ӿ� 4-i/6 = 3
    }
 
    for (std::string strLine; getline(std::cin, strLine) && !strLine.empty(); )
    {
        // ��������������a��λ��
        COORDS inputA;
        result.clear();
        for (std::string::iterator i = strLine.begin(); i != strLine.end(); ++i) {
            if (*i == 'a') {
                int nIdx = i - strLine.begin();
                POINT3 tmp = {nIdx % 3, 2 - (nIdx % 9) / 3, 2 - nIdx / 9};//��1234.����˳��ת��
                inputA.push_back(tmp);//4 points
            }
        }
        // �������pieceA��������Ϊ�ռ�ֱ������ϵ��������Ӧ������
        POINT3 minCoord, tmp;
        Bound(inputA, minCoord, tmp);
        Translate(inputA, Inverse(minCoord));//��С��ƽ�Ƶ�ԭ��
        std::sort(inputA.begin(), inputA.end());
        Coords2Mask(inputA);
        // ���Ҷ����pieceAת�����ռ�ֱ������ϵ����Ӧ�Ĺ���
        int nRot = std::find(allPieceForms[0].begin(), allPieceForms[0].end(),
            Coords2Mask(inputA)) - allPieceForms[0].begin();//allPieceForms[0]Ϊa��������תģ�� �ҵ�����������ͬ���Ǹ�����
        // ����pieceA��Ӧ���������
        FORMMASK fixedA = allPieceForms[0][nRot];//��ǰpiece a��״̬����
        VECFORMMASK vfm(1, fixedA);//path��һ������piece a
        FillCube(allPieceForms.begin() + 1, fixedA, vfm);//�ӵڶ���piece��ʼ �������ܵ����
        // ����pieceA����ƫ�ƴ������������
		//pieceA��24����ת���ͣ���һ����ת��5��ƫ�ƹ��Ϳ�ʼ��24��������ÿ��5�� ��ȡ��nRot��ļ���
        for (int i = nRot * 5 + 24; i < (nRot + 1) * 5 + 24; ++i) {
            fixedA = allPieceForms[0][i];
            vfm = VECFORMMASK(1, fixedA);
            FillCube(allPieceForms.begin() + 1, fixedA, vfm);
        }
        // ��������������ת��Ϊ�����ʽ���ַ���
        std::vector<std::string> outStrs;
        for (ALLPIECEFORMS::iterator i = result.begin(); i != result.end(); ++i) {//ȡ��һ��path
            std::string str;
            str.resize(27);
            for (size_t j = 0; j < i->size(); ++j) {
                FORMMASK mask = i->at(j);//path�е�j������  Ҳ��nameMap�е�j����ĸ��Ӧ��piece��ĳ����״
                for (size_t k = 0; k < 27; ++k) {//��������������е���Ӧλ�����
                    if (mask & (1 << posMap[k])) {//ԭ����k�����������봮��posMap[k]��
                        //�ж�������posMap[k]Ϊ���ռ�ֱ������ϵ��Ӧ����������ϵ��λ�ã���������ַ�����˳�����������Ҫ�����
                        str[k] = nameMap[j];
                    }
                }
            }
            outStrs.push_back(str);
        }
        std::sort(outStrs.begin(), outStrs.end());
        for (std::vector<std::string>::iterator i = outStrs.begin(); i != outStrs.end(); ++i) {
            std::cout << *i << std::endl;
        }
        std::cout << std::endl;
    }
 
    return 0;
}

