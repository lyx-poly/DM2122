#ifndef SCENE_A_H
#define SCENE_A_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "Vertex.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneA : public Scene
{
public:
	SceneA();
	~SceneA();

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
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS,
		U_TOTAL,
	};

private:
	Camera2 camera;

	Light light[2];

	virtual void RenderMesh(Mesh* mesh, bool enableLight);

	unsigned m_vertexArrayID;
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE_EYE, // This one used to generate prince's eyes
		GEO_CIRCLE,
		GEO_LIGHTBALL,
		GEO_LIGHTBALL2,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE_5,
		GEO_SPHERE6,
		GEO_SPHERE7,
		GEO_SPHERE8,
		GEO_SPHERE9,

		GEO_TORUS,

		// Prince geometries
		GEO_HEAD_CYLINDER,
		GEO_TORSO_CYLINDER,
		GEO_HEMISPHERE_SIDES,

		GEO_CONE_ANTENNA,
		GEO_SPHERE_ANTENNA,

		GEO_ARM_JOINT,
		GEO_ARM_SEG,

		GEO_LEG_JOINT,
		GEO_LEG_SEG,

		GEO_PYRAMID_NOSE,
		GEO_TRAPEZOID_MOUTH,

		// Background props

		GEO_CYLINDER_TRUNK,
		GEO_CONE_LEAVES,
		GEO_SPHERE_LEAVES,

		// Katamari ball

		GEO_SPHERE_KATAMARI,
		GEO_HEMISPHERE_BUMPS,

		// Sample Props
		GEO_SAMPLE_SPHERE,

		NUM_GEOMETRY, //DO NOT MOVE FROM BOTTOM
	};

	//unsigned m_vertexBuffer[NUM_GEOMETRY]; //comment or remove
	//unsigned m_colorBuffer[NUM_GEOMETRY]; //comment or remove
	//unsigned m_indexBuffer[NUM_GEOMETRY]; //comment or remove
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_parameters[U_TOTAL];
	unsigned m_programID;

	bool lightswitch;

	MS modelStack, viewStack, projectionStack;

	// Update values
	float rotateAngle;
	float rotateAngle_stand;
	float rotateAngle_2;
	float rotateAngleBall;
	float translateX;
	float translateMovementZ;
	float translateMovementX;
	float scaleAll;

	float rotate_value;
	float rotate_value2;
	float rotate_value3;
	float rotate_value4;
	float rotate_value5;

	float translate_value;
	float rotateDirection;
	float headRotation;

	bool standing;
	bool dance_mode;

	//dance mode
	//float dance_headRotation;
	float dance_arm_rotate;
	float dance_shoulder_rotate2;
	float dance_shoulder_rotate1;
	float dance_hip_rotateR;
	float dance_leg_rotateR;
	float dance_hip_rotateL;
	float dance_leg_rotateL;

	float dance_arm_rotate_value;
	float dance_shoulder_rotate_value2;
	float dance_shoulder_rotate_value1;

	float dance_hip_rotate_valueR;
	float dance_leg_rotate_valueR;

	float dance_hip_rotate_valueL;
	float dance_leg_rotate_valueL;

	char leg_switch;

	float ball_positionZ;
	float ball_positionY;
	float prince_position;
};

#endif