#include "Sphere_Formulas.h"
#include "MyMath.h"

Sphere_Formulas::Sphere_Formulas()
{
	final_sum = 0.0f;
}

Sphere_Formulas::~Sphere_Formulas()
{
}

float Sphere_Formulas::spherex(float radius, float phi, float theta)
{
	final_sum = radius * cos(phi) * cos(theta);
	return final_sum;
}

float Sphere_Formulas::spherey(float radius, float phi, float theta)
{
	final_sum = radius * sin(phi);
	return final_sum;
}

float Sphere_Formulas::spherez(float radius, float phi, float theta)
{
	final_sum = radius * cos(phi) * sin(theta);
	return final_sum;
}
