#include "Mathf.h"

float Mathf::getRandom(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

float Mathf::getRadians(float degree)
{
	return degree * (3.14f / 180.0f);
}
