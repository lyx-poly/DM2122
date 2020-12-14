#ifndef CAMERA2_H
#define CAMERA2_H

#include "Vector3.h"

class Camera2
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera2();
	~Camera2();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt);
};

#endif