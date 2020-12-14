#include "Material.h"

Material::Material()
{
	kShininess = 0.f;
	kAmbient.Set(0, 0, 0);
	kDiffuse.Set(0, 0, 0);
	kSpecular.Set(0, 0, 0);
}
