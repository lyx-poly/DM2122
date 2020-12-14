#include "SceneA.h"
#include "GL\glew.h"

#include "Mtx44.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"

#include "Application.h"




SceneA::SceneA()
{
	standing = false;
	dance_mode = false;
	lightswitch = true;
	ball_positionZ = 8; // Default z position for push position
	ball_positionY = -0.6f; // Default y position for push position
	prince_position = 0;
	headRotation = 0;

	leg_switch = 'r';
}

SceneA::~SceneA()
{
}

void SceneA::Init()
{
	glEnable(GL_CULL_FACE);

	rotateAngle = 45;
	rotateAngle_stand = 0;
	rotateAngle_2 = -45;
	rotateAngleBall = 0;
	translateX = 0;
	translateMovementZ = 0;
	translateMovementX = 0;
	rotateDirection = 0;
	scaleAll = 5;

	dance_arm_rotate = 0;
	dance_shoulder_rotate1 = 0;
	dance_shoulder_rotate2 = 0;

	dance_hip_rotateR = 1;
	dance_leg_rotateR = 1;

	dance_hip_rotateL = 1;
	dance_leg_rotateL = 1;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	//m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	/*m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	//m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");*/

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	glUseProgram(m_programID);

	//Set up light object
	light[0].type = Light::LIGHT_POINT; //
	light[0].position.Set(0, 15, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	//Set up light2 object
	/*
	light[1].type = Light::LIGHT_POINT; //
	light[1].position.Set(0, 5, 0);
	light[1].color.Set(1, 1, 0);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);
	*/

	// Make sure you pass uniform parameters after glUseProgram()
	/*glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);*/

	//glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	/*
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	*/
	rotate_value = 0;
	rotate_value2 = 0;
	rotate_value3 = 100;
	rotate_value4 = 200;
	rotate_value5 = 100;

	dance_arm_rotate_value = 55.5;
	dance_shoulder_rotate_value1 = 18.25;
	dance_shoulder_rotate_value2 = 55.5;
	dance_hip_rotate_valueR = 200;
	dance_leg_rotate_valueR = 200;

	translate_value = 20;

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(0, 1, 1), 360, 1.0F);


	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere2("lightball", Color(1,1,1),45,45,0.2);

	meshList[GEO_CUBE_EYE] = MeshBuilder::GenerateCube2("Cube eyes", Color(0.431, 0.431, 0.514), Color(0.431, 0.431, 0.514), 2.0f);
	meshList[GEO_CUBE_EYE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CUBE_EYE]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CUBE_EYE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CUBE_EYE]->material.kShininess = 1.f;

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1, Color(0.0f, 0.5f, 0.0f));
	meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;


	//Prince geometries
	meshList[GEO_HEAD_CYLINDER] = MeshBuilder::GenerateCylinderHead("head", Color(0.5098039215686274, 0.7372549019607844, 0.21568627450980393), Color(0.9411764705882353, 0.803921568627451, 0.7137254901960784), Color(0.9098039215686274
		, 0.792156862745098
		, 0.27058823529411763), 20, 2.0f, 5);
	meshList[GEO_HEAD_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEAD_CYLINDER]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_HEAD_CYLINDER]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEAD_CYLINDER]->material.kShininess = 1.f;

	meshList[GEO_TORSO_CYLINDER] = MeshBuilder::GenerateCylinderBody("torso_body", Color(0.5098039215686274, 0.7372549019607844, 0.21568627450980393), Color(0.506, 0.102, 0.471), 20, 1.7f, 7);
	meshList[GEO_TORSO_CYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TORSO_CYLINDER]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_TORSO_CYLINDER]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TORSO_CYLINDER]->material.kShininess = 1.f;

	meshList[GEO_HEMISPHERE_SIDES] = MeshBuilder::GenerateHemisphere("head_sides", Color(0.6745098039215687
		, 0.8235294117647058
		, 0.29411764705882354), Color(0.29411764705882354
			, 0.6274509803921569
			, 0.21568627450980393), Color(0.2235294117647059
				, 0.5843137254901961
				, 0.2627450980392157), 2.0f);
	meshList[GEO_HEMISPHERE_SIDES]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE_SIDES]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_HEMISPHERE_SIDES]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEMISPHERE_SIDES]->material.kShininess = 1.f;

	meshList[GEO_CONE_ANTENNA] = MeshBuilder::GenerateCone("Cone_Antenna", Color(0.9098039215686274
		, 0.792156862745098
		, 0.27058823529411763), 0.5f, 1.5f);
	meshList[GEO_CONE_ANTENNA]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CONE_ANTENNA]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CONE_ANTENNA]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CONE_ANTENNA]->material.kShininess = 1.f;

	meshList[GEO_SPHERE_ANTENNA] = MeshBuilder::GenerateSphere2("antenna_ball", Color(0.784, 0.141, 0.196), 45, 45, 0.2);
	meshList[GEO_SPHERE_ANTENNA]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE_ANTENNA]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE_ANTENNA]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE_ANTENNA]->material.kShininess = 1.f;

	meshList[GEO_TORUS] = MeshBuilder::GenerateTorus2("Belt", Color(0.2235294117647059
		, 0.5843137254901961
		, 0.2627450980392157),50,50,1.7f,0.2f);
	meshList[GEO_TORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TORUS]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_TORUS]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TORUS]->material.kShininess = 1.f;


	meshList[GEO_ARM_JOINT] = MeshBuilder::GenerateSphere2("Arm Joint", Color(0.5098039215686274, 0.7372549019607844, 0.21568627450980393), 45, 45, 0.3f);
	meshList[GEO_ARM_JOINT]->material.kAmbient.Set(0.5f,0.5f,0.5f);
	meshList[GEO_ARM_JOINT]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_ARM_JOINT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ARM_JOINT]->material.kShininess = 1.f;

	meshList[GEO_ARM_SEG] = MeshBuilder::GenerateCylinderBody("Arm SEG", Color(0.5098039215686274, 0.7372549019607844, 0.21568627450980393), Color(0.5098039215686274, 0.7372549019607844, 0.21568627450980393), 1, 0.3f, 1.5);
	meshList[GEO_ARM_SEG]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ARM_SEG]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_ARM_SEG]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ARM_SEG]->material.kShininess = 1.f;


	meshList[GEO_LEG_JOINT] = MeshBuilder::GenerateSphere2("Leg Joint", Color(0.506, 0.102, 0.471), 45, 45, 0.3f);
	meshList[GEO_LEG_JOINT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_LEG_JOINT]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LEG_JOINT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEG_JOINT]->material.kShininess = 1.f;

	meshList[GEO_LEG_SEG] = MeshBuilder::GenerateCylinderBody("Leg SEG", Color(0.506, 0.102, 0.471), Color(0.506, 0.102, 0.471), 1, 0.3f, 1.5);
	meshList[GEO_LEG_SEG]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_LEG_SEG]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LEG_SEG]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEG_SEG]->material.kShininess = 1.f;


	meshList[GEO_PYRAMID_NOSE] = MeshBuilder::GenerateSquarePyramid("Nose", Color(0.886, 0.365, 0.145), 1, 1.5f);
	meshList[GEO_PYRAMID_NOSE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PYRAMID_NOSE]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_PYRAMID_NOSE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PYRAMID_NOSE]->material.kShininess = 1.f;

	meshList[GEO_TRAPEZOID_MOUTH] = MeshBuilder::GenerateTrapezoid("Mouth", Color(0.784, 0.141, 0.196));
	meshList[GEO_TRAPEZOID_MOUTH]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TRAPEZOID_MOUTH]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_TRAPEZOID_MOUTH]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TRAPEZOID_MOUTH]->material.kShininess = 1.f;

	//Environment
	meshList[GEO_CYLINDER_TRUNK] = MeshBuilder::GenerateCylinderBody("Tree trunk", Color(0.2f,0,0), Color(0.2f, 0, 0), 1, 1.0f, 10);
	meshList[GEO_CYLINDER_TRUNK]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CYLINDER_TRUNK]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CYLINDER_TRUNK]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CYLINDER_TRUNK]->material.kShininess = 0.1f;

	meshList[GEO_SPHERE_LEAVES] = MeshBuilder::GenerateSphere2("Sphere foilage", Color(0,0.4f,0), 45, 45, 3.0f);
	meshList[GEO_SPHERE_LEAVES]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE_LEAVES]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE_LEAVES]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE_LEAVES]->material.kShininess = 0.1f;

	meshList[GEO_CONE_LEAVES] = MeshBuilder::GenerateCone("Cone foilage", Color(0, 0.4f, 0), 3.0f, 6.0f);
	meshList[GEO_CONE_LEAVES]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CONE_LEAVES]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CONE_LEAVES]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CONE_LEAVES]->material.kShininess = 0.0f;


	meshList[GEO_SAMPLE_SPHERE] = MeshBuilder::GenerateSphere2("Test Sphere", Color(1.0, 0.0f, 0), 45, 45, 3.0f);
	meshList[GEO_SAMPLE_SPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SAMPLE_SPHERE]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SAMPLE_SPHERE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SAMPLE_SPHERE]->material.kShininess = 0.5f;


	// Katamari ball
	meshList[GEO_SPHERE_KATAMARI] = MeshBuilder::GenerateSphere2("Test Sphere", Color(1.0 ,0.247 ,0.541), 45, 45, 6.0f);
	meshList[GEO_SPHERE_KATAMARI]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE_KATAMARI]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE_KATAMARI]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE_KATAMARI]->material.kShininess = 1;

	meshList[GEO_HEMISPHERE_BUMPS] = MeshBuilder::GenerateHemisphere("Test Sphere", Color(0.9, 0.247, 0.541), Color(1.0, 1.0f, 1.0f), Color(0.698 ,0.635 ,0.251), 2.0f);
	meshList[GEO_HEMISPHERE_BUMPS]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HEMISPHERE_BUMPS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEMISPHERE_BUMPS]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEMISPHERE_BUMPS]->material.kShininess = 1;

	// Init VBO here
	// Set background color to dark blue

	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark Blue Default

	//glClearColor(0,0,0,0);

	glClearColor(0.529f,0.808f,0.992f,0.f); // Sky Blue

	//** BUFFER **

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Vector between -1.0f to 1.0f for vertice

	// An array of 3 vectors which represents 3 vertices
	// Right angle triangle

	//** BUFFER **

	// Set the current active buffer
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);



	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//glGenBuffers(NUM_GEOMETRY, &m_indexBuffer[GEO_TRIANGLE_1]);
	//generate index buffer...
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer[GEO_TRIANGLE_1]); //bind index buffer
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void SceneA::Update(double dt)
{
	// Standing bool switches prince between pushing ball and walking on ball

	if (Application::IsKeyPressed('5'))
	{
		standing = true;
		dance_mode = false;
		ball_positionZ = 0;
		ball_positionY = -11.5f;
		prince_position = 11.5f;
	}

	else if (Application::IsKeyPressed('6'))
	{
		standing = false;
		ball_positionZ = 8;
		ball_positionY = -0.6f;
		prince_position = 0;
	}

	if (standing)
	{
		if (Application::IsKeyPressed('7'))
		{
			dance_mode = true;
		}

		if (Application::IsKeyPressed('8'))
		{
			dance_mode = false;
		}
	}
	/*
	if (Application::IsKeyPressed(VK_SPACE))
	{

		if (rotateAngle <= 0)
		{
			rotate_value = 100;
		}

		else if (rotateAngle >= 180)
		{
			rotate_value = -100;
		}

		//
		rotateAngle += (float)(rotate_value * dt);
		//

		if (translateX > -1 and translateX < 5)
		{
			translateX += (float)(10 * dt);
		}

		else
		{
			translateX = 0;
		}

		if (scaleAll < 10) { scaleAll += (float)(2 * dt); }
		else { scaleAll = 5; };
	}*/

	if (Application::IsKeyPressed('9'))
	{
		lightswitch = true;
	}
	if (Application::IsKeyPressed('0'))
	{
		lightswitch = false;
	}
	
	camera.Update(dt);
	camera.Reset(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	
	//rotate_value += (float)(1.0 * dt);
	//rotate_value2 += (float)(5.0 * dt);
	//rotate_value3 += (float)(4.0 * dt);
	rotate_value4 += (float)(1.0 * dt);

	if (Application::IsKeyPressed('1')) {
		glEnable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('2')) {
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('3')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}

	if (Application::IsKeyPressed('4')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	// Move lightball
	static const float LSPEED = 4.f;

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	/*if (Application::IsKeyPressed('5'))
	{
		//to do: switch light type to POINT and pass the information to shader
		light[0].type = Light::LIGHT_POINT; //
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);

	}
	else if (Application::IsKeyPressed('7'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		light[0].type = Light::LIGHT_SPOT; // rotateAngle_stand
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}*/

	// Prince animations | Refer to IsKeyPresses('H') for update value references
		if (Application::IsKeyPressed('T'))
		{
			switch (dance_mode)
			{
			case true:
				translateMovementZ -= (float)(translate_value * dt);
				rotateDirection = 180;
				rotateAngleBall += (float)(rotate_value3 * dt);
				break;
			case false:
					if (rotateAngle <= 45)
					{
						rotate_value = 200;
					}

					else if (rotateAngle >= 135)
					{
						rotate_value = -200;
					}

					else
					{
						rotate_value = rotate_value;
					}


					if (rotateAngle_stand <= -45)
					{
						rotate_value5 = 200;
					}

					else if (rotateAngle_stand >= 45)
					{
						rotate_value5 = -200;
					}

					else
					{
						rotate_value5 = rotate_value5;
					}


					if (rotateAngle_2 <= -45)
					{
						rotate_value2 = 200;
					}

					else if (rotateAngle_2 >= 45)
					{
						rotate_value2 = -200;
					}

					else
					{
						rotate_value2 = rotate_value2;
					}


					if (headRotation <= -45)
					{
						rotate_value4 = 200;
					}

					else if (headRotation >= 45)
					{
						rotate_value4 = -200;
					}

					else
					{
						rotate_value4 = rotate_value4;
					}

					headRotation += (float)(rotate_value4 * dt);

					//
					rotateAngle += (float)(rotate_value * dt);
					rotateAngle_stand += (float)(rotate_value5 * dt);
					rotateAngle_2 += (float)(rotate_value2 * dt);
					translateMovementZ -= (float)(translate_value * dt);
					rotateDirection = 180;
					rotateAngleBall += (float)(rotate_value3 * dt);
					//
				break;
			}
		}

		if (Application::IsKeyPressed('G'))
		{
			switch (dance_mode)
			{
			case true:
				translateMovementZ += (float)(translate_value * dt);
				rotateDirection = 0;
				rotateAngleBall += (float)(rotate_value3 * dt);
				break;
			case false:
				if (rotateAngle <= 45)
				{
					rotate_value = 200;
				}

				else if (rotateAngle >= 135)
				{
					rotate_value = -200;
				}

				else
				{
					rotate_value = rotate_value;
				}

				if (rotateAngle_stand <= -45)
				{
					rotate_value5 = 200;
				}

				else if (rotateAngle_stand >= 45)
				{
					rotate_value5 = -200;
				}

				else
				{
					rotate_value5 = rotate_value5;
				}


				if (rotateAngle_2 <= -45)
				{
					rotate_value2 = 200;
				}

				else if (rotateAngle_2 >= 45)
				{
					rotate_value2 = -200;
				}

				else
				{
					rotate_value2 = rotate_value;
				}

				if (headRotation <= -45)
				{
					rotate_value4 = 200;
				}

				else if (headRotation >= 45)
				{
					rotate_value4 = -200;
				}

				else
				{
					rotate_value4 = rotate_value4;
				}

				headRotation += (float)(rotate_value4 * dt);

				//
				rotateAngle += (float)(rotate_value * dt);
				rotateAngle_stand += (float)(rotate_value5 * dt);
				rotateAngle_2 += (float)(rotate_value2 * dt);
				translateMovementZ += (float)(translate_value * dt);
				rotateDirection = 0;
				rotateAngleBall += (float)(rotate_value3 * dt);
				//
				break;
			}
		}

		if (Application::IsKeyPressed('F'))
		{
			switch (dance_mode)
			{
			case true:
				translateMovementX -= (float)(translate_value * dt);
				rotateDirection = 270;
				rotateAngleBall += (float)(rotate_value3 * dt);
				break;
			case false:
				if (rotateAngle <= 45)
				{
					rotate_value = 200;
				}

				else if (rotateAngle >= 135)
				{
					rotate_value = -200;
				}

				else
				{
					rotate_value = rotate_value;
				}

				if (rotateAngle_stand <= -45)
				{
					rotate_value5 = 200;
				}

				else if (rotateAngle_stand >= 45)
				{
					rotate_value5 = -200;
				}

				else
				{
					rotate_value5 = rotate_value5;
				}


				if (rotateAngle_2 <= -45)
				{
					rotate_value2 = 200;
				}

				else if (rotateAngle_2 >= 45)
				{
					rotate_value2 = -200;
				}

				else
				{
					rotate_value2 = rotate_value;
				}

				if (headRotation <= -45)
				{
					rotate_value4 = 200;
				}

				else if (headRotation >= 45)
				{
					rotate_value4 = -200;
				}

				else
				{
					rotate_value4 = rotate_value4;
				}

				headRotation += (float)(rotate_value4 * dt);

				//
				rotateAngle += (float)(rotate_value * dt);
				rotateAngle_stand += (float)(rotate_value5 * dt);
				rotateAngle_2 += (float)(rotate_value2 * dt);
				translateMovementX -= (float)(translate_value * dt);
				rotateDirection = 270;
				rotateAngleBall += (float)(rotate_value3 * dt);
				//
				break;
			}
		}

		if (Application::IsKeyPressed('H'))
		{
			switch (dance_mode)
			{
			case true:
				translateMovementX += (float)(translate_value * dt); // Translation movement
				rotateDirection = 90; // Translation Direction
				rotateAngleBall += (float)(rotate_value3 * dt); // Rotate katamari ball
				break;
			case false:
				if (rotateAngle <= 45)
				{
					rotate_value = 200;
				}

				else if (rotateAngle >= 135)
				{
					rotate_value = -200;
				}

				else
				{
					rotate_value = rotate_value;
				}


				if (rotateAngle_stand <= -45)
				{
					rotate_value5 = 200;
				}

				else if (rotateAngle_stand >= 45)
				{
					rotate_value5 = -200;
				}

				else
				{
					rotate_value5 = rotate_value5;
				}


				if (rotateAngle_2 <= -45)
				{
					rotate_value2 = 200;
				}

				else if (rotateAngle_2 >= 45)
				{
					rotate_value2 = -200;
				}

				else
				{
					rotate_value2 = rotate_value;
				}

				if (headRotation <= -45)
				{
					rotate_value4 = 200;
				}

				else if (headRotation >= 45)
				{
					rotate_value4 = -200;
				}

				else
				{
					rotate_value4 = rotate_value4;
				}

				headRotation += (float)(rotate_value4 * dt);

				//
				rotateAngle += (float)(rotate_value * dt);
				rotateAngle_stand += (float)(rotate_value5 * dt);
				rotateAngle_2 += (float)(rotate_value2 * dt);

				translateMovementX += (float)(translate_value * dt); // Translation movement
				rotateDirection = 90; // Translation Direction
				rotateAngleBall += (float)(rotate_value3 * dt); // Rotate katamari ball
				//
				break;
			}
		}



		// Dance mode
		if (dance_mode)
		{
			float doubler = 1; // IGNORE
			// Legs
			if (leg_switch == 'r')
			{
				dance_hip_rotate_valueL = 0;
				dance_leg_rotate_valueL = 0;
				if (dance_hip_rotateR <= 0)
				{
					dance_hip_rotate_valueL = doubler *  200;
					dance_leg_rotate_valueL = doubler *  200;
					dance_hip_rotateR++;
					dance_hip_rotate_valueR = doubler * 200;
					leg_switch = 'l';
					//std::cout << leg_switch << std::endl;
				}

				else if (dance_hip_rotateR >= 90)
				{
					dance_hip_rotate_valueR = doubler * -200;
				}

				else
				{
					dance_hip_rotate_valueR = dance_hip_rotate_valueR;
				}

				//

				if (dance_leg_rotateR <= 0)
				{
					dance_leg_rotate_valueR = doubler * 200;
				}

				else if (dance_leg_rotateR >= 90)
				{
					dance_leg_rotate_valueR = doubler * -200;
				}

				else
				{
					dance_leg_rotate_valueR = dance_leg_rotate_valueR;
				}

			}
			else if (leg_switch == 'l')
			{
				//std::cout << "O" << std::endl;
				dance_hip_rotate_valueR = 0;
				dance_leg_rotate_valueR = 0;
				if (dance_hip_rotateL <= 0)
				{
					dance_hip_rotate_valueR = doubler * 200;
					dance_leg_rotate_valueR = doubler * 200;
					dance_hip_rotateL++;
					dance_hip_rotate_valueL = doubler * 200;
					leg_switch = 'r';
					//std::cout << leg_switch << std::endl;
				}

				else if (dance_hip_rotateL >= 90)
				{
					dance_hip_rotate_valueL = doubler * -200;
				}

				else
				{
					dance_hip_rotate_valueL = dance_hip_rotate_valueL;
				}

				//

				if (dance_leg_rotateL <= 0)
				{
					dance_leg_rotate_valueL = doubler * 200;
				}

				else if (dance_leg_rotateL >= 90)
				{
					dance_leg_rotate_valueL = doubler * -200;
				}

				else
				{
					dance_leg_rotate_valueL = dance_leg_rotate_valueL;
				}
			}

			dance_hip_rotateR += (float)(dance_hip_rotate_valueR * dt);
			dance_leg_rotateR += (float)(dance_leg_rotate_valueR * dt);

			dance_hip_rotateL += (float)(dance_hip_rotate_valueL * dt);
			dance_leg_rotateL += (float)(dance_leg_rotate_valueL * dt);


			//Arms
			if (dance_shoulder_rotate1 <= -10)
			{
				dance_shoulder_rotate_value1 = doubler * 18.25;
			}

			else if (dance_shoulder_rotate1 >= 10)
			{
				dance_shoulder_rotate_value1 = doubler * -18.25;
			}

			else
			{
				dance_shoulder_rotate_value1 = dance_shoulder_rotate_value1;
			}

			dance_shoulder_rotate1 += (float)(dance_shoulder_rotate_value1 * dt);

			////

			if (dance_shoulder_rotate2 <= 0)
			{
				dance_shoulder_rotate_value2 = doubler * 55.5;
			}

			else if (dance_shoulder_rotate2 >= 30)
			{
				dance_shoulder_rotate_value2 = doubler * -55.5;
			}

			else
			{
				dance_shoulder_rotate_value2 = dance_shoulder_rotate_value2;
			}
			dance_shoulder_rotate2 += (float)(dance_shoulder_rotate_value2 * dt);


			////

			if (dance_arm_rotate <= 0)
			{
				dance_arm_rotate_value = doubler * 55.5;
			}

			else if (dance_arm_rotate >= 30)
			{
				dance_arm_rotate_value = doubler * -55.5;
			}

			else
			{
				dance_arm_rotate_value = dance_arm_rotate_value;
			}
			dance_arm_rotate += (float)(dance_arm_rotate_value * dt);
		}




		if (Application::IsKeyPressed('E')) // Reset character & animations
		{
			rotateAngle = 45;
			rotateAngle_2 = -45;
			translateMovementZ = 0;
			translateMovementX = 0;
			rotateDirection = 0;
			rotateAngleBall = 0;
			headRotation = 0;

			dance_mode = false;
			standing = false;
			ball_positionZ = 8;
			ball_positionY = -0.6f;
			prince_position = 0;

			dance_arm_rotate_value = 55.5;
			dance_shoulder_rotate_value1 = 18.25;
			dance_shoulder_rotate_value2 = 55.5;

			dance_arm_rotate = 0;
			dance_shoulder_rotate2 = 0;
			dance_shoulder_rotate1 = 0;

			dance_hip_rotate_valueR = 200;
			dance_leg_rotate_valueR = 200;
			dance_hip_rotate_valueL = 200;
			dance_leg_rotate_valueL = 200;

			dance_hip_rotateR = 0;
			dance_leg_rotateR = 0;
			dance_hip_rotateL = 0;
			dance_leg_rotateL = 0;
		}
}

void SceneA::Render()
{
	// Render VBO here
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Triangle 1 //
	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	//glEnableVertexAttribArray(1); // 2nd attribute buffer : colors


	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); /*no need camera for now, set it at
	World's origin*/
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10); /*Our world is
	a cube defined by these boundaries*/

	// Default: (-40, 40, -30, 30, -10, 10) | exe Window's aspect ratio

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
		camera.position.z, camera.target.x, camera.target.y,
		camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();


	/*scale.SetToScale(10, 10, 10); ////
	rotate.SetToRotation(rotateAngle, 0, 0, 1);*/
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_AXES]->Render();

	Position lightPosition_cameraspace = viewStack.Top() *
		light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1,
		&lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y,
		light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -6.5);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();


	//START OF ENVIROMENT MESH GENERATION//
	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(0, 2.5f, -10);
	RenderMesh(meshList[GEO_CYLINDER_TRUNK], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_CONE_LEAVES], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(-25, 2.5f, 25);
	RenderMesh(meshList[GEO_CYLINDER_TRUNK], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_CONE_LEAVES], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(13, 2.5f, -20);
	RenderMesh(meshList[GEO_CYLINDER_TRUNK], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_SPHERE_LEAVES], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(-19, 2.5f, 43);
	RenderMesh(meshList[GEO_CYLINDER_TRUNK], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_CONE_LEAVES], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(-10, 2.5f, -12);
	RenderMesh(meshList[GEO_CYLINDER_TRUNK], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_SPHERE_LEAVES], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();


	//END OF ENVIROMENT MESH GENERATION//

	modelStack.PushMatrix();
	//modelStack.Rotate(rotateAngle_2, 0, 1, 0);
	modelStack.Translate(0, prince_position, 0);

	modelStack.Translate(translateMovementX, 0, translateMovementZ);
	modelStack.Rotate(rotateDirection, 0, 1, 0);
	RenderMesh(meshList[GEO_TORSO_CYLINDER], true); //Torso (Body) | *MAIN PARENT* | M1_MAIN
	

	modelStack.PushMatrix(); // Katamari ball M2
	//modelStack.Scale(2, 2, 2);
	modelStack.Translate(0, ball_positionY, ball_positionZ);
	//modelStack.Translate(translateMovementX / 2, 0, translateMovementZ / 2);
	modelStack.Rotate(rotateAngleBall, 1, 0, 0);
	RenderMesh(meshList[GEO_SPHERE_KATAMARI], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 5.5f, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true); //1 TOP // Tweleve hemisphere bumps M3
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5.5f, 0);
	modelStack.Rotate(180, 1,0,0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//2 BOTTOM
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.0f, 0);
	modelStack.Rotate(72 * 0, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(70, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//3  | UPPER FIVE 3 - 7 |
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.0f, 0);
	modelStack.Rotate(72 * 1, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(70, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//4
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.0f, 0);
	modelStack.Rotate(72 * 2, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(70, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//5
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.0f, 0);
	modelStack.Rotate(72 * 3, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(70, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//6
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.0f, 0);
	modelStack.Rotate(72 * 4, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(70, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//7
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, -2.0f, 0);
	modelStack.Rotate(72 * 0, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(115, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//3  | LOWER FIVE 3 - 7 |
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, -2.0f, 0);
	modelStack.Rotate(72 * 1, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(115, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//4
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, -2.0f, 0);
	modelStack.Rotate(72 * 2, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(115, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//5
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, -2.0f, 0);
	modelStack.Rotate(72 * 3, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(115, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//6
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, -2.0f, 0);
	modelStack.Rotate(72 * 4, 0, 1, 0);
	modelStack.Translate(0, 0, 5);
	modelStack.Rotate(115, 1, 0, 0);
	RenderMesh(meshList[GEO_HEMISPHERE_BUMPS], true);//7
	modelStack.PopMatrix();

	// End of katamari ball generation

	modelStack.PopMatrix();



	modelStack.PushMatrix(); // M2_HEAD | All meshes from head cylinder to antenna are part of M2_Head.
	modelStack.Translate(0, 3, 0);
	modelStack.Rotate(90, 0, 0, 1);
	if (standing && !dance_mode) { modelStack.Rotate(headRotation, 1, 0, 0); }
	else if (dance_mode) { modelStack.Rotate(0, 1, 0, 0); }

	//modelStack.Rotate(rotateAngle, 1, 0, 0); //TEST

	RenderMesh(meshList[GEO_HEAD_CYLINDER], true); //Head M2


	modelStack.PushMatrix(); //Head Sides M3
	modelStack.Translate(0, 2.5, 0);
	//modelStack.Rotate(-90, 0, 0, 1);

	RenderMesh(meshList[GEO_HEMISPHERE_SIDES], true); // Head sides R M3
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Translate(0, 2.5, 0);

	RenderMesh(meshList[GEO_HEMISPHERE_SIDES], true); // Head sides L M3
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(1.3f, 0, 1.5f);
	modelStack.Translate(0, 0.6, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_CUBE_EYE], true); // R eye
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(1.3f, 0, 1.5f);
	modelStack.Translate(0, -0.6, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_CUBE_EYE], true); // L eye
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.5f,0,1.85f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(-10, 1, 0, 0);
	modelStack.Scale(0.2, 0.4, 0.2);
	RenderMesh(meshList[GEO_PYRAMID_NOSE], true); // Nose
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,0,2);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(0.5, 0.2, 0.2);
	RenderMesh(meshList[GEO_TRAPEZOID_MOUTH], true); // Mouth
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Translate(0, 1.5f, 0);

	RenderMesh(meshList[GEO_CONE_ANTENNA], true); //Antenna M3


	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5f, 0);

	RenderMesh(meshList[GEO_SPHERE_ANTENNA], true); //Antenna ball M5
	
	for (int a = 0; a < 3; a++)
	{
		modelStack.PopMatrix(); // Pop three times back to M1_MAIN
	}


	modelStack.PushMatrix();
	modelStack.Translate(0,-3, 0);

	RenderMesh(meshList[GEO_TORUS], true); // Belt | Solo member of M2_TORUS
	modelStack.PopMatrix();

	//ARMS
	// Start of a Limb Branch//

	modelStack.PushMatrix(); // M2_R_Shoulder

	modelStack.Translate(0, 0.5f, 0);
	modelStack.Translate(-1.7f, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);

	switch (standing)
	{
	case true:
		switch (dance_mode)
		{
		case true:
			modelStack.Rotate(70, 1, 0, 0);
			modelStack.Rotate(dance_shoulder_rotate1, 0,0,1);
			modelStack.Rotate(dance_shoulder_rotate2, 1, 0, 0);
			break;
		case false:
			modelStack.Rotate(-rotateAngle_stand, 1, 0, 0);
			break;
		}
		break;
	case false:
		modelStack.Rotate(rotateAngle, 0, 1, 0);
		modelStack.Rotate(60, 0, 0, 1);
		break;
	}

	RenderMesh(meshList[GEO_ARM_JOINT], true); //R Shoulder Joint


	modelStack.PushMatrix(); // M3_R_Upper_Arm

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_ARM_SEG], true); //R Upper Arm


	modelStack.PushMatrix(); // M4_R_Arm_Joint

	modelStack.Translate(0, 0.75, 0);
	if (dance_mode) 
	{
		modelStack.Rotate(110, 1, 0, 0);
		modelStack.Rotate(-dance_arm_rotate, 1,0,0);
	}
	RenderMesh(meshList[GEO_ARM_JOINT], true); //R Arm Joint

	modelStack.PushMatrix(); // M5_R_Lower_Arm

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_ARM_SEG], true); //R Lower Arm


	modelStack.PushMatrix(); // M6_R_Hand

	modelStack.Scale(1.1, 1.1, 1.1);
	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_ARM_JOINT], true); //R Hand

	for (int a = 0; a < 5; a++)
	{
		modelStack.PopMatrix(); // Pop five times back to M1_MAIN
	}

	// End of a Limb Branch//

	// Start of a Limb Branch//

	modelStack.PushMatrix(); // M2_L_Shoulder

	modelStack.Translate(0, 0.5f, 0);
	modelStack.Translate(1.7f, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);

	switch (standing)
	{
	case true:
		switch (dance_mode)
		{
		case true:
			modelStack.Rotate(70, 1, 0, 0);
			modelStack.Rotate(dance_shoulder_rotate1, 0, 0, 1);
			modelStack.Rotate(dance_shoulder_rotate2, 1, 0, 0);
			break;
		case false:
			modelStack.Rotate(rotateAngle_stand, 1, 0, 0);
			break;
		}
		break;
	case false:
		modelStack.Rotate(rotateAngle, 0, 1, 0);
		modelStack.Rotate(60, 0, 0, 1);
		break;
	}

	RenderMesh(meshList[GEO_ARM_JOINT], true); //L Shoulder Joint


	modelStack.PushMatrix(); // M3_L_Upper_Arm

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_ARM_SEG], true); //L Upper Arm


	modelStack.PushMatrix(); // M4_L_Arm_Joint

	modelStack.Translate(0, 0.75, 0);
	if (dance_mode)
	{
		modelStack.Rotate(110, 1, 0, 0);
		modelStack.Rotate(-dance_arm_rotate, 1, 0, 0);
	}
	RenderMesh(meshList[GEO_ARM_JOINT], true); //L Arm Joint

	modelStack.PushMatrix(); // M5_L_Lower_Arm

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_ARM_SEG], true); //L Lower Arm


	modelStack.PushMatrix(); // M6_L_Hand

	modelStack.Scale(1.1, 1.1, 1.1);
	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_ARM_JOINT], true); //L Hand

	for (int a = 0; a < 5; a++)
	{
		modelStack.PopMatrix(); // Pop five times back to M1_MAIN
	}

	// End of a Limb Branch//

	// LEGS
	// Start of a Limb Branch//

	modelStack.PushMatrix(); // M2_R_Hip

	modelStack.Translate(0, -3.5, 0);
	modelStack.Translate(-1.2f, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	switch (dance_mode)
	{
	case true:
		modelStack.Rotate(10, 0, 1, 0);
		modelStack.Rotate(dance_hip_rotateR, 1, 0, 0);
		break;
	case false:
		modelStack.Rotate(-rotateAngle_2, 1, 0, 0);
		break;
	}
	//modelStack.Rotate(-45, 1, 0, 0);

	RenderMesh(meshList[GEO_LEG_JOINT], true); //R Hip Joint


	modelStack.PushMatrix(); // M3_R_Upper_Leg

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_LEG_SEG], true); //R Upper Leg


	modelStack.PushMatrix(); // M4_R_Leg_Joint

	modelStack.Translate(0, 0.75, 0);
	if (dance_mode){ modelStack.Rotate(-dance_leg_rotateR, 1, 0, 0); } 
	RenderMesh(meshList[GEO_LEG_JOINT], true); //R Leg Joint

	modelStack.PushMatrix(); // M5_R_Lower_Leg

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_LEG_SEG], true); //R Lower Leg

	for (int a = 0; a < 4; a++)
	{
		modelStack.PopMatrix(); // Pop four times back to M1_MAIN
	}

	// End of a Limb Branch//

	// Start of a Limb Branch//

	modelStack.PushMatrix(); // M2_L_Hip

	modelStack.Translate(0, -3.5, 0);
	modelStack.Translate(1.2f, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);

	switch (dance_mode)
	{
	case true:
		modelStack.Rotate(-10, 0, 1, 0);
		modelStack.Rotate(dance_hip_rotateL, 1, 0, 0);
		//std::cout << dance_hip_rotate_valueL << std::endl;
		break;
	case false:
		modelStack.Rotate(rotateAngle_2, 1, 0, 0);
		break;
	}
	//modelStack.Rotate(-45, 1, 0, 0);

	RenderMesh(meshList[GEO_LEG_JOINT], true); //L Hip Joint


	modelStack.PushMatrix(); // M3_L_Upper_Leg

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_LEG_SEG], true); //L Upper Leg


	modelStack.PushMatrix(); // M4_L_Leg_Joint

	modelStack.Translate(0, 0.75, 0);
	if (dance_mode) {modelStack.Rotate(-dance_leg_rotateL, 1, 0, 0); }
	RenderMesh(meshList[GEO_LEG_JOINT], true); //L Leg Joint

	modelStack.PushMatrix(); // M5_L_Lower_Leg

	modelStack.Translate(0, 0.75, 0);
	RenderMesh(meshList[GEO_LEG_SEG], true); //L Lower Leg

	for (int a = 0; a < 4; a++)
	{
		modelStack.PopMatrix(); // Pop four times back to M1_MAIN
	}

	// End of a Limb Branch//

	modelStack.Clear();
	/*glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex

		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);*/

	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 36); //comment this line
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer[GEO_TRIANGLE_1]);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//glDisableVertexAttribArray(0);

	//glDisableVertexAttribArray(1);
}

void SceneA::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && lightswitch == true)
	{
		if (light[0].type == Light::LIGHT_DIRECTIONAL) //
		{
			Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if (light[0].type == Light::LIGHT_SPOT) //
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else if (light[0].type == Light::LIGHT_POINT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//---------

		/*if (light[1].type == Light::LIGHT_DIRECTIONAL) //
		{
			Vector3 lightDir2(light[1].position.x, light[1].position.y, light[1].position.z);
			Vector3 lightDirection_cameraspace2 = viewStack.Top() * lightDir2;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace2.x);
		}
		else if (light[1].type == Light::LIGHT_SPOT) //
		{
			Position lightPosition_cameraspace2 = viewStack.Top() * light[1].position;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace2.x);
			Vector3 spotDirection_cameraspace2 = viewStack.Top() * light[1].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace2.x);
		}
		else if (light[1].type == Light::LIGHT_POINT)
		{
			Position lightPosition_cameraspace2 = viewStack.Top() * light[1].position;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace2.x);
		}*/

		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void SceneA::Exit()
{
	// Cleanup VBO here

	//glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	//glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
