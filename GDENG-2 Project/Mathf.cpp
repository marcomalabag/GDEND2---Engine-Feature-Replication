#include "Mathf.h"

#include "Random.h"
#include "DirectXMath.h"

float Mathf::getRandom(float min, float max)
{
	return Engine::Random::Range<float>(min, max);
}

float Mathf::getRadians(float degree)
{
	return DirectX::XMConvertToRadians(degree);
}
