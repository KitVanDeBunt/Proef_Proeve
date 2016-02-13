#include "Proef_Proeve.h"
#include "MathUtil.h"

FVector MathUtil::Lerp(FVector a, FVector b, float t)
{
	return a + t*(b - a);
}