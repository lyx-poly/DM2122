#include "Light.h"

Light::Light()
{
	power = 0.5f;
	kC = kL = kQ = 0.f;
	position.Set(0, 5, 0);
	color.Set(1, 1, 1);
}
