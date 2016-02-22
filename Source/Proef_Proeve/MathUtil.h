#pragma once
#include "Runtime/Core/Public/Math/Vector.h"

class MathUtil
{
public:
	static FVector Lerp(FVector a, FVector b, float t);
};


class SmoothInterpolate
{
private :
	float sloopTop = 1.0f;
	float currentSloopLength = 1.0f;
	float speed;
	float dist;
	float sloopPower;
	float speedMult;
	FVector startPosition;
	float interpolation = 0.0f;
	float oldInterpolation = 0.0f;
public :
	SmoothInterpolate(FVector startPosition, float sloopDist, float dist, float speed, float sloopPower, float speedMult);
	~SmoothInterpolate();
	float UpdatePosition(FVector currentPos, float deltaTime);
	void SetOldInterpolation();
};

