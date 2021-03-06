#pragma once
#include <cmath>

#define DEG_TO_RAD 0.017453f //1도의 라디안 값
#define PI 3.141592654f
#define PI2 (PI * 2)

//프레임 이미지 회전 시킬때
//총 프레임의 절반 프레임 만큼이 필요함
#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

#define FLOAT_EPSILON 0.001f //실수의 가장 작은 단위를 그리스어로 엡실론 입실론이라고 함

namespace SIERRA_UTIL	//원하는대로
{
	//거리 가져오는 공식
	float getDistance(float startX, float startY, float endX, float endY);

	//각도 가져오는 공식
	float getAngle(float x1, float y1, float x2, float y2);
}