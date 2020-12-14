#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		NUM_GEOMETRY,
	};

	enum GEOMETRY_TYPE2
	{
		GEO_TRIANGLE_2 = 0,
		NUM_GEOMETRY2,
	};

	enum GEOMETRY_TYPE3
	{
		GEO_TRIANGLE_3 = 0,
		NUM_GEOMETRY3,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_vertexBuffer2[NUM_GEOMETRY2];
	unsigned m_colorBuffer2[NUM_GEOMETRY2];
	unsigned m_vertexBuffer3[NUM_GEOMETRY3];
	unsigned m_colorBuffer3[NUM_GEOMETRY3];
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;

	float rotateAngle;
	float translateX;
	float scaleAll;

	float rotate_value;

};

#endif