#ifndef SCENE_1_H
#define SCENE_1_H

#include "Scene.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

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

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_vertexBuffer2[NUM_GEOMETRY2];
	unsigned m_colorBuffer2[NUM_GEOMETRY2];
	unsigned m_programID;
};

#endif