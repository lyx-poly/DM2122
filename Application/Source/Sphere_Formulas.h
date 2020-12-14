#pragma once

class Sphere_Formulas
{
private:
	float final_sum;
public:
	Sphere_Formulas();
	~Sphere_Formulas();

	float spherex(float radius, float phi, float theta);
	float spherey(float radius, float phi, float theta);
	float spherez(float radius, float phi, float theta);
};