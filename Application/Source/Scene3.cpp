#include "Scene3.h"
#include "GL\glew.h"

#include "Mtx44.h"
#include "shader.hpp"

#include "Application.h"




Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	rotateAngle = 0;
	translateX = 2;
	scaleAll = 5;

	rotate_value = 1.0;


	// Init VBO here
	// Set background color to dark blue

	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark Blue Default


	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//** BUFFER **

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glGenBuffers(NUM_GEOMETRY2, &m_vertexBuffer2[0]);
	glGenBuffers(NUM_GEOMETRY2, &m_colorBuffer2[0]);
	glGenBuffers(NUM_GEOMETRY3, &m_vertexBuffer3[0]);
	glGenBuffers(NUM_GEOMETRY3, &m_colorBuffer3[0]);

	// Vector between -1.0f to 1.0f for vertice

	// An array of 3 vectors which represents 3 vertices
	// Right angle triangle
	static const GLfloat vertex_buffer_data[] = {
	0.0f, 0.0f, 0.0f,
	0.0f, 0.1f, 0.0f,
	0.1f, 0.0f, 0.0f,
	};

	//** BUFFER **

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data),
		vertex_buffer_data, GL_STATIC_DRAW);

	//// Repeat for second triangle
	// Square
	static const GLfloat vertex_buffer_data2[] = {
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};

	//** BUFFER **

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer2[GEO_TRIANGLE_2]);


	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2),
		vertex_buffer_data2, GL_STATIC_DRAW);

	//________
	// 1 degree slice of circle

	static const GLfloat vertex_buffer_data3[] = {
		1.0f, 0.008725f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, -0.008725f, 0.0f,
	};

	//** BUFFER **

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer3[GEO_TRIANGLE_3]);


	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3),
		vertex_buffer_data3, GL_STATIC_DRAW);

	//** BUFFER **
	
	// Vector between 0.0f to 1.0f for colour

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);

	// Repeat for second triangle
	static const GLfloat color_buffer_data2[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer2[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2),
		color_buffer_data2, GL_STATIC_DRAW);

	// Repeat for circle slice
	static const GLfloat color_buffer_data3[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer3[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3),
		color_buffer_data3, GL_STATIC_DRAW);



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

void Scene3::Update(double dt)
{

	if (Application::IsKeyPressed(VK_SPACE))
	{
		/*if (rotateAngle < -10)
		{
			rotateAngle += (float)(25 * dt);
		}

		else if (rotateAngle > 30)
		{
			rotateAngle += (float)(25 * dt);
		}*/

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
	}
}

void Scene3::Render()
{
	// Render VBO here
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Triangle 1 //
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors


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
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10); /*Our world is
	a cube defined by these boundaries*/

	// Default: (-40, 40, -30, 30, -10, 10) | exe Window's aspect ratio


	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(-2, -2, 2);
	model = translate * rotate * scale; /*scale, followed by
	rotate, then lastly translate*/
	MVP = projection * view * model; /* Remember, matrix
	multiplication is the other way around*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	//
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer2[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, /* attribute 0. Must match the layout in the
		shader.Usually 0 is for vertex */

		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer2[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);


	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(translateX, 0, 0);
	model = translate * rotate * scale; /*scale, followed by
	rotate, then lastly translate*/
	MVP = projection * view * model; /* Remember, matrix
	multiplication is the other way around*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	//
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, /* attribute 0. Must match the layout in the
		shader.Usually 0 is for vertex */

		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);


	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-1, -1, -1);
	model = translate * rotate * scale; /*scale, followed by
	rotate, then lastly translate*/
	MVP = projection * view * model; /* Remember, matrix
	multiplication is the other way around*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	//
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, /* attribute 0. Must match the layout in the
		shader.Usually 0 is for vertex */

		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	/*
	// Triangle 2 //
	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	//glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer2[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex

		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer2[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle */

	//Circle
	for (int a = 0; a < 360; a++)
	{
		scale.SetToScale(10, 10, 10);
		rotate.SetToRotation(a, 0, 0, 1);
		translate.SetToTranslation(0, 0, 0);
		model = translate * rotate * scale; /*scale, followed by
		rotate, then lastly translate*/
		MVP = projection * view * model; /* Remember, matrix
		multiplication is the other way around*/
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP
		//
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer3[GEO_TRIANGLE_3]);
		glVertexAttribPointer(
			0, /* attribute 0. Must match the layout in the
			shader.Usually 0 is for vertex */

			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			0 // array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer3[GEO_TRIANGLE_3]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
	}

	glDisableVertexAttribArray(0);

	glDisableVertexAttribArray(1);
}

void Scene3::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY2, &m_vertexBuffer2[0]);
	glDeleteBuffers(NUM_GEOMETRY2, &m_colorBuffer2[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
