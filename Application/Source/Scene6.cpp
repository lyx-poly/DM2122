#include "Scene6.h"
#include "GL\glew.h"

#include "Mtx44.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"

#include "Application.h"




Scene6::Scene6()
{
}

Scene6::~Scene6()
{
}

void Scene6::Init()
{
	glEnable(GL_CULL_FACE);

	rotateAngle = 0;
	translateX = 2;
	scaleAll = 5;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
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
	glUseProgram(m_programID);

	//Set up light object
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	rotate_value = 1.0;
	rotate_value2 = 5.0;
	rotate_value3 = 2.0;
	rotate_value4 = 6.0;

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), Color(0, 1, 0), 1.0f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(0, 1, 1), 360, 1.0F);


	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere2("lightball", Color(1,1,1),45,45,0.2);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere2("sphere", Color(1, 0, 0), 45, 45, 2.0F);
	meshList[GEO_SPHERE]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere2("sphere2", Color(0, 1, 0), 45, 45, 2.0F);
	meshList[GEO_SPHERE2]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_SPHERE2]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE2]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE2]->material.kShininess = 1.f;

	meshList[GEO_SPHERE3] = MeshBuilder::GenerateSphere2("sphere3", Color(0, 0, 1), 45, 45, 2.0F);
	meshList[GEO_SPHERE3]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE3]->material.kDiffuse.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_SPHERE3]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE3]->material.kShininess = 1.f;

	meshList[GEO_SPHERE4] = MeshBuilder::GenerateSphere2("sphere4", Color(1, 1, 0), 45, 45, 2.0F);
	meshList[GEO_SPHERE4]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE4]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE4]->material.kSpecular.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_SPHERE4]->material.kShininess = 1.f;

	meshList[GEO_SPHERE_5] = MeshBuilder::GenerateSphere2("sphere5", Color(1, 0, 1), 45, 45, 2.0F);
	meshList[GEO_SPHERE_5]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE_5]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE_5]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE_5]->material.kShininess = 1.f;

	meshList[GEO_SPHERE6] = MeshBuilder::GenerateSphere2("sphere6", Color(0, 1, 1), 45, 45, 2.0F);
	meshList[GEO_SPHERE6]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE6]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE6]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE6]->material.kShininess = 1.f;

	meshList[GEO_SPHERE7] = MeshBuilder::GenerateSphere2("sphere7", Color(1, 1, 1), 45, 45, 2.0F);
	meshList[GEO_SPHERE7]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE7]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE7]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE7]->material.kShininess = 0.f;

	meshList[GEO_SPHERE8] = MeshBuilder::GenerateSphere2("sphere8", Color(0, 0, 0), 45, 45, 2.0F);
	meshList[GEO_SPHERE8]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE8]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE8]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SPHERE8]->material.kShininess = 0.5f;

	meshList[GEO_SPHERE9] = MeshBuilder::GenerateSphere2("sphere9", Color(0.5f, 0.f, 0.f), 45, 45, 2.0F);
	meshList[GEO_SPHERE9]->material.kAmbient.Set(0.5f, 1.0f, 0.5f);
	meshList[GEO_SPHERE9]->material.kDiffuse.Set(1.0f, 0.5f, 1.0f);
	meshList[GEO_SPHERE9]->material.kSpecular.Set(0.5f, 1.0f, 0.5f);
	meshList[GEO_SPHERE9]->material.kShininess = 1.f;

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1, Color(0.0f, 0.f, 0.0f));
	meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;


	//meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("sphere2", Color(1, 0, 0), 45, 45, 0.5F);
	//meshList[GEO_SPHERE3] = MeshBuilder::GenerateSphere("sphere3", Color(0, 1, 0), 45, 45, 1.0F);
	//meshList[GEO_SPHERE4] = MeshBuilder::GenerateSphere("sphere4", Color(0, 0, 1), 45, 45, 1.0F);
	//meshList[GEO_SPHERE_5] = MeshBuilder::GenerateSphere("sphere5", Color(1, 0, 0), 18, 19, 1.0F);

	//meshList[GEO_TORUS] = MeshBuilder::GenerateTorus2("Torus Space Ring",180,360,4,3,Color(0.5,0.5,0.5));

	// Init VBO here
	// Set background color to dark blue

	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark Blue Default


	glClearColor(0.f,0.f,0.4f,0.f);

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

void Scene6::Update(double dt)
{
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
	camera.Update(dt);
	camera.Reset(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	rotate_value += (float)(1.0 * dt);
	rotate_value2 += (float)(5.0 * dt);
	rotate_value3 += (float)(4.0 * dt);
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
}

void Scene6::Render()
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
	meshList[GEO_AXES]->Render();

	Position lightPosition_cameraspace = viewStack.Top() *
		light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1,
		&lightPosition_cameraspace.x);

	modelStack.PushMatrix();
	modelStack.Translate(0, 2, 0);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2, 0);
	modelStack.Translate(4, 0, 0);
	modelStack.Translate(0, 0, 4);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2, 4);
	RenderMesh(meshList[GEO_SPHERE3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, 2, 4);
	RenderMesh(meshList[GEO_SPHERE4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(4, 2, 0);
	RenderMesh(meshList[GEO_SPHERE_5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, 2, 0);
	RenderMesh(meshList[GEO_SPHERE6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(4, 2, -4);
	RenderMesh(meshList[GEO_SPHERE7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2, -4);
	RenderMesh(meshList[GEO_SPHERE8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, 2, -4);
	RenderMesh(meshList[GEO_SPHERE9], true);
	modelStack.PopMatrix();

	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y,
		light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

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

void Scene6::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
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

void Scene6::Exit()
{
	// Cleanup VBO here

	//glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	//glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
