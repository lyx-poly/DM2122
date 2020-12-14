#ifndef SCENE_5c_H
#define SCENE_5c_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "Vertex.h"
#include "MatrixStack.h"

class Scene5c : public Scene
{
public:
	Scene5c();
	~Scene5c();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

private:
	Camera2 camera;

	unsigned m_vertexArrayID;
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		NUM_GEOMETRY,
		GEO_TORUS,
	};
	//unsigned m_vertexBuffer[NUM_GEOMETRY]; //comment or remove
	//unsigned m_colorBuffer[NUM_GEOMETRY]; //comment or remove
	//unsigned m_indexBuffer[NUM_GEOMETRY]; //comment or remove
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;

	MS modelStack, viewStack, projectionStack;

	float rotateAngle;
	float translateX;
	float scaleAll;

	float rotate_value;
	float rotate_value2;
	float rotate_value3;
	float rotate_value4;

};

#endif