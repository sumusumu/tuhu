#include "stdafx.h"
#include "utils.h"


namespace SIERRA_UTIL	//���ϴ´��
{
	//�Ÿ� �������� ����
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//���� �������� ����
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (y > 0) angle = PI2 - angle;

		return angle;
	}
}