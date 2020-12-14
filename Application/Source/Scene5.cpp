#include "Scene5.h"
#include "GL\glew.h"

#include "Mtx44.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Vertex.h"

#include "Application.h"




Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
{
	glEnable(GL_CULL_FACE);

	rotateAngle = 0;
	translateX = 2;
	scaleAll = 5;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	rotate_value = 1.0;

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1, Color(1,1,1));
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), Color(0, 1, 0), 1.0f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(0, 1, 1), 360, 1.0F);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0.5, 0), 180, 360, 1.0F);

	// Init VBO here
	// Set background color to dark blue

	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark Blue Default


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

	//Load vertex and fragment shaders//
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");

	// Use our shader
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene5::Update(double dt)
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

	rotateAngle += (float)(5.0 * dt);

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
}

void Scene5::Render()
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

	modelStack.PushMatrix();

	modelStack.Translate(2, 0, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Clear();

	modelStack.Translate(-2, 0, 0);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	//scale.SetToIdentity();
	//model = translate * rotate * scale;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CUBE]->Render();

	modelStack.PopMatrix();

	modelStack.PushMatrix();

	//scale.SetToIdentity();
	//model = translate * rotate * scale;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CIRCLE]->Render();

	modelStack.PopMatrix();

	modelStack.PushMatrix();

	//scale.SetToIdentity();
	//model = translate * rotate * scale;
	modelStack.Translate(0, 2, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_QUAD]->Render();

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

void Scene5::Exit()
{
	// Cleanup VBO here

	//glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	//glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
