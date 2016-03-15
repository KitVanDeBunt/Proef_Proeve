#include "Proef_Proeve.h"
#include "MathUtil.h"

FVector MathUtil::Lerp(FVector a, FVector b, float t)
{
	return a + t*(b - a);
}

SmoothInterpolate::SmoothInterpolate(FVector startPosition, float sloopDist, float dist, float speed, float sloopPower, float speedMult, float interpolation){
	this->dist = dist;
	this->speed = speed;
	this->sloopPower = sloopPower;
	this->speedMult = speedMult;
	this->startPosition = startPosition;
	this->interpolation = interpolation;

	sloopTop = 1.0f;
	currentSloopLength = sloopDist;
	if ((sloopDist * 2.0f) > dist) {
		float distHalf = dist / 2.0f;
		float sloopOverlapHalf = sloopDist - distHalf;
		currentSloopLength = sloopDist - sloopOverlapHalf;
		sloopTop = currentSloopLength / sloopDist;
	}
}

float SmoothInterpolate::UpdatePosition(FVector currentPos, float deltaTime) {
	float distTravled = FVector::Dist(currentPos,startPosition);

	bool startSloop = (distTravled < currentSloopLength);
	bool startEnd = (distTravled >(dist - currentSloopLength));
	float sloopProgress;
	float sloopSpeedMult = 1.0f;

	if (startSloop) {
		sloopProgress = (distTravled / currentSloopLength);
		sloopSpeedMult = FMath::Lerp(0.001f, sloopTop, sloopProgress);
	}
	else if (startEnd) {
		sloopProgress = ((distTravled - (dist - currentSloopLength)) / currentSloopLength);
		sloopSpeedMult = FMath::Lerp(sloopTop, 0.001f, sloopProgress);
	}
	oldInterpolation = interpolation;
	interpolation += ((deltaTime / speedMult) * speed * (sloopSpeedMult * sloopPower));
	return interpolation;
}

void SmoothInterpolate::SetOldInterpolation(){
	interpolation = oldInterpolation;
}

SmoothInterpolate::~SmoothInterpolate(){
}