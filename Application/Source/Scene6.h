#ifndef SCENE_6_H
#define SCENE_6_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "Vertex.h"
#include "MatrixStack.h"
#include "Light.h"

class Scene6 : public Scene
{
public:
	Scene6();
	~Scene6();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	//virtual void RenderMesh(Mesh* mesh, bool enableLight);
	virtual void Exit();

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};

private:
	Camera2 camera;

	Light light[1];

	virtual void RenderMesh(Mesh* mesh, bool enableLight);

	unsigned m_vertexArrayID;
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE_5,
		GEO_SPHERE6,
		GEO_SPHERE7,
		GEO_SPHERE8,
		GEO_SPHERE9,
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