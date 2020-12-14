#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Vertex.h"
#include "MatrixStack.h"

class Scene5 : public Scene
{
public:
	Scene5();
	~Scene5();

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
	Camera camera;

	unsigned m_vertexArrayID;
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_SPHERE,
		NUM_GEOMETRY,
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

};

#endif