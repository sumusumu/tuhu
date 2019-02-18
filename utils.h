#pragma once
#include <cmath>

#define DEG_TO_RAD 0.017453f //1���� ���� ��
#define PI 3.141592654f
#define PI2 (PI * 2)

//������ �̹��� ȸ�� ��ų��
//�� �������� ���� ������ ��ŭ�� �ʿ���
#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

#define FLOAT_EPSILON 0.001f //�Ǽ��� ���� ���� ������ �׸������ ���Ƿ� �ԽǷ��̶�� ��

namespace SIERRA_UTIL	//���ϴ´��
{
	//�Ÿ� �������� ����
	float getDistance(float startX, float startY, float endX, float endY);

	//���� �������� ����
	float getAngle(float x1, float y1, float x2, float y2);
}