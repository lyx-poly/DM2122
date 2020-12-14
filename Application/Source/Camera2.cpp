#include "Camera2.h"
#include "Application.h"
#include "Vertex.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera2::Camera2()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera2::~Camera2()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera2::Reset(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	if (Application::IsKeyPressed('R'))
	{
		this->position = pos;
		this->target = target;
		this->up = up;
	}
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera2::Update(double dt)
{

	/*
	if (Application::IsKeyPressed('A'))
		this->position.x -= CAMERA_SPEED * dt; //move camera left
	if (Application::IsKeyPressed('D'))
		this->position.x += CAMERA_SPEED * dt; //move camera right
	if (Application::IsKeyPressed('W'))
		this->position.y += CAMERA_SPEED * dt; //move camera up
	if (Application::IsKeyPressed('S'))
		this->position.y -= CAMERA_SPEED * dt; //move camera down
	if (Application::IsKeyPressed('M'))
		this->position.z += CAMERA_SPEED * dt; //move camera forward
	if (Application::IsKeyPressed('N'))
		this->position.z -= CAMERA_SPEED * dt; //move camera backwards
		*/

	/*float zx_hyp; // Hypothenuse
	float yx_hyp;
	float zx_tan; // Angle
	float yx_tan;
	float x;
	float y;
	float z;*/

	/*x = this->position.x;
	y = this->position.y;
	z = this->position.z;

	zx_hyp = sqrt((x * x) + (z * z));
	yx_hyp = sqrt((x * x) + (y * y));

	//zx_tan = this->position.z / this->position.x;// zx plane | zx_tan = opp/adj ; opp = position.z, adj = position.x*/
	static const float CAMERA_SPEED = 50.f;

	Vector3 view = (target - position).Normalized();
	if (Application::IsKeyPressed('W'))
	{
		// Rotation matrix
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z);
		// Apply Rotation
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('A'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
		// Apply Rotation
		position = rotation * position;
		up = rotation * up;
	}

	if (Application::IsKeyPressed('N'))
	{
		position += view * (CAMERA_SPEED / 5) * dt;
		if (position.Length() < 5) //Prevent the camera from touching the origin
		{
			view.Normalize();
			position -= view * CAMERA_SPEED * dt;
		}
	}

	if (Application::IsKeyPressed('S'))
	{
		// Rotation matrix
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
		// Apply Rotation
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}

	if (Application::IsKeyPressed('D'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
		// Apply Rotation
		position = rotation * position;
		up = rotation * up;
	}

	if (Application::IsKeyPressed('M'))
	{
		position -= view * (CAMERA_SPEED / 5) * dt;
	}
}