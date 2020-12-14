#include "MeshBuilder.h"
#include <GL\glew.h>
#include "Vertex.h"
#include <iostream>
#include "Mesh.h"
#include <vector>
#include "MyMath.h"

#include "Sphere_Formulas.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	
	v.pos.Set(lengthX, 0.0f, 0.0f); v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, 0.0f, 0.0f); v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(0.0f, lengthY, 0.f); v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, -lengthY, 0.f); v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(0.0f, 0.0f, lengthZ); v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, 0.0f, -lengthZ); v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	
	for (int i = 0; i < 6; i++)
		index_buffer_data.push_back(i);
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, float lengthX, float lengthY, Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float x, y, z; // vertex vector
	float nx, ny, nz;    // vertex normal

	x = lengthX;
	y = lengthY;
	z = 0.f;

	v.pos.Set(0.5f * x, 0.5f * y, z);	v.color = color; 
	v.normal.Set(0,0,1);	
	vertex_buffer_data.push_back(v); //v0
	v.pos.Set(-0.5f * x, 0.5f * y, z);	v.color = color; 
	v.normal.Set(0, 0, 1);	
	vertex_buffer_data.push_back(v); //v1
	v.pos.Set(-0.5f * x, -0.5f * y, z);	v.color = color; 
	v.normal.Set(0, 0, 1);	
	vertex_buffer_data.push_back(v); //v2
	v.pos.Set(0.5f * x, -0.5f * y, z);	v.color = color; 
	v.normal.Set(0, 0, 1);	
	vertex_buffer_data.push_back(v); //v3


	//v.normal.Set()

	//tri1
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	//tri2
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string& meshName, Color color, Color color2, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color2;	vertex_buffer_data.push_back(v);
	
	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.f / numSlice;

	v.pos.Set(0, 0, 0);	v.color = color;	vertex_buffer_data.push_back(v);
	for (int i = 0; i < numSlice + 1; ++i)
	{
		float theta = i * degreePerSlice;
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));	v.color = color; v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < numSlice + 1; ++i)
	{
		index_buffer_data.push_back(i + 1);
		index_buffer_data.push_back(0);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	//Notes: phil is for xz-plane angle while theta is for xy-plane angle
	Sphere_Formulas Sphere_calc;

	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;

	/*for (unsigned stack = 0; stack < numStack + 1; ++stack) //stack //replace with 180 for sphere
	{
		float phi = -90.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
		{
			float theta = slice * degreePerSlice;
			v.pos.Set(Sphere_calc.spherex(radius, phi, theta), Sphere_calc.spherey(radius, phi, theta), Sphere_calc.spherez(radius, phi, theta));
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}*/

	/*for (float phi = 0; phi < numStack; phi += 1) //stack //replace with 180 for sphere
	{
		for (float theta = 0; theta <= numSlice; theta += 1) //slice
		{
			v.pos.Set(Sphere_calc.spherex(radius, phi, theta), Sphere_calc.spherey(radius, phi, theta), Sphere_calc.spherez(radius, phi, theta)); v.color = color;
			vertex_buffer_data.push_back(v);
			v.pos.Set(Sphere_calc.spherex(radius, phi + 1, theta), Sphere_calc.spherey(radius, phi + 1, theta), Sphere_calc.spherez(radius, phi + 1, theta)); v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}*/

	/*for (float theta = 0; theta <= numSlice; theta += 10) //bottom
	{
		v.pos.Set(0, 0, 0); v.color = color;
		vertex_buffer_data.push_back(v);
		v.pos.Set(Sphere_calc.spherex(radius, 0, theta), 0, Sphere_calc.spherez(radius, 0, theta)); v.color = color;
		vertex_buffer_data.push_back(v);
	}*/

	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * Math::PI / numSlice;
	float stackStep = Math::PI / numStack;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= numStack; ++i)
	{
		stackAngle = Math::PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= numSlice; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			v.pos.Set(x, y, z); v.color = color;
			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			v.normal.Set(nx, ny, nz);
			vertex_buffer_data.push_back(v);
			

			/*// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(s);
			texCoords.push_back(t);*/
		}
	} // Code credited to: http://www.songho.ca/opengl/gl_sphere.html

	/*for (unsigned i = 0; i < numStack * numSlice * 2; ++i)
	{
		index_buffer_data.push_back(i);
		//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
	}*/

	int k1, k2;
	for (int i = 0; i < numStack; ++i)
	{
		k1 = i * (numStack + 1);     // beginning of current stack
		k2 = k1 + numSlice + 1;      // beginning of next stack

		for (int j = 0; j < numSlice; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				index_buffer_data.push_back(k1);
				index_buffer_data.push_back(k2);
				index_buffer_data.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (numStack - 1))
			{
				index_buffer_data.push_back(k1 + 1);
				index_buffer_data.push_back(k2);
				index_buffer_data.push_back(k2 + 1);
			}
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal

	for (double phi = 0; phi < 90; phi += 10) {
		for (double theta = 0; theta <= 360; theta += 10) {

			nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal reset

			v.pos.Set(radius * cos(phi * Math::PI / 180) * cos(theta * Math::PI / 180),
				radius * sin(phi * Math::PI / 180),
				radius * cos(phi * Math::PI / 180) * sin(theta * Math::PI / 180));
			v.color = color;
			nx = radius * cos(phi * Math::PI / 180) * cos(theta * Math::PI / 180) * lengthInv;
			ny = radius * sin(phi * Math::PI / 180) * lengthInv;
			nz = radius * cos(phi * Math::PI / 180) * sin(theta * Math::PI / 180) * lengthInv;
			v.normal.Set(nx, ny, nz);
			vertex_buffer_data.push_back(v);

			nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal reset

			v.pos.Set(radius * cos((phi + 10) * Math::PI / 180) * cos(theta * Math::PI / 180),
				radius * sin((phi + 10) * Math::PI / 180),
				radius * cos((phi + 10) * Math::PI / 180) * sin(theta * Math::PI / 180));
			v.color = color;
			nx = radius * cos((phi + 10) * Math::PI / 180) * cos(theta * Math::PI / 180) * lengthInv;
			ny = radius * sin((phi + 10) * Math::PI / 180) * lengthInv;
			nz = radius * cos((phi + 10) * Math::PI / 180) * sin(theta * Math::PI / 180) * lengthInv;
			v.normal.Set(nx, ny, nz);
			vertex_buffer_data.push_back(v);
		}
	}
	
	for (double phi2 = 0; phi2 >= -90; phi2 -= 10) {
		for (double theta2 = 0; theta2 <= 360; theta2 += 10) {

			nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal reset

			v.pos.Set(radius * cos(phi2 * Math::PI / 180) * cos(theta2 * Math::PI / 180),
				radius * sin(phi2 * Math::PI / 180),
				radius * cos(phi2 * Math::PI / 180) * sin(theta2 * Math::PI / 180));
			v.color = color;
			nx = radius * cos(phi2 * Math::PI / 180) * cos(theta2 * Math::PI / 180) * lengthInv;
			ny = radius * sin(phi2 * Math::PI / 180) * lengthInv;
			nz = radius * cos(phi2 * Math::PI / 180) * sin(theta2 * Math::PI / 180) * lengthInv;
			v.normal.Set(nx, ny, nz);
			vertex_buffer_data.push_back(v);

			nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal reset

			v.pos.Set(radius * cos((phi2 + 10) * Math::PI / 180) * cos(theta2 * Math::PI / 180),
				radius * sin((phi2 + 10) * Math::PI / 180),
				radius * cos((phi2 + 10) * Math::PI / 180) * sin(theta2 * Math::PI / 180));
			v.color = color;
			nx = radius * cos((phi2 + 10) * Math::PI / 180) * cos(theta2 * Math::PI / 180) * lengthInv;
			ny = radius * sin((phi2 + 10) * Math::PI / 180) * lengthInv;
			nz = radius * cos((phi2 + 10) * Math::PI / 180) * sin(theta2 * Math::PI / 180) * lengthInv;
			v.normal.Set(nx, ny, nz);
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < (10 * 36 * 2 * 2); ++i) {
		index_buffer_data.push_back(i);
	}


	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinderHead(const std::string& meshName, Color color, Color color2, Color color3, unsigned numStack, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//Code for drawing with triangle strip, with multiple stack
	float stackHeight = height / numStack;
	int indexcount = 0;
	for (float stack = 0; stack < numStack; ++stack) //stack
	{
		for (float theta = 0; theta <= 360; theta += 10) //slice
		{
			v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2 + stack * stackHeight, radius * sin(Math::DegreeToRadian(theta)));
			v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
			v.color = color;
			if (stack < numStack - 4 && stack > 3)
			{
				if (theta > 0 && theta < 110)
				{
					v.color = color2;
				}

				else if (theta == 0 || theta == 110)
				{
					v.color = color3;
				}
			}

			else if (stack == numStack - 4 || stack == 3)
			{
				if (theta >= 0 && theta <= 110)
				{
					v.color = color3;
				}
			}
			vertex_buffer_data.push_back(v);
			indexcount++;

			v.pos.Set(radius * (cos(Math::DegreeToRadian(theta))), -height / 2 + (stack + 1) * stackHeight, radius * sin(Math::DegreeToRadian(theta)));
			v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
			v.color = color;
			if (stack < numStack - 4 && stack > 3)
			{
				if (theta > 0 && theta < 110)
				{
					v.color = color2;
				}

				else if (theta == 0 || theta == 110)
				{
					v.color = color3;
				}
			}

			else if (stack == numStack - 4 || stack == 3)
			{
				if (theta >= 0 && theta <= 110)
				{
					v.color = color3;
				}
			}
			vertex_buffer_data.push_back(v);
			indexcount++;
		}
	}
	
	for (float theta = 0; theta <= 360; theta += 10) //top
	{
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;

		v.pos.Set(0, height / 2, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;
	}
	
	for (float theta = 0; theta <= 360; theta += 10) //bottom
	{
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;
	}

	for (int i = 0; i < indexcount; ++i) {
		index_buffer_data.push_back(i);
	}
	
	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string& meshName, Color color, Color color2, Color color3, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//Add normals for lighting
	int indexcount = 0;
	for (float phi = 0; phi < 90; phi += 10) //stack //replace with 180 for sphere
	{
		for (float theta = 0; theta <= 360; theta += 10) //slice
		{
			v.pos.Set(radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)), radius * sin(Math::DegreeToRadian(phi)), radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			v.normal.Set(cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)), sin(Math::DegreeToRadian(phi)), cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			if (phi < 20)
			{
				v.color = color;
			}
			else if (phi >= 20 && phi < 40)
			{
				v.color = color2;
			}
			else if (phi >= 40)
			{
				v.color = color3;
			}
			vertex_buffer_data.push_back(v);
			indexcount++;

			// phi + 10
			v.pos.Set(radius * cos(Math::DegreeToRadian(phi + 10)) * cos(Math::DegreeToRadian(theta)), radius * sin(Math::DegreeToRadian(phi + 10)), radius * cos(Math::DegreeToRadian(phi + 10)) * sin(Math::DegreeToRadian(theta)));
			v.normal.Set(cos(Math::DegreeToRadian(phi + 10)) * cos(Math::DegreeToRadian(theta)), sin(Math::DegreeToRadian(phi + 10)), cos(Math::DegreeToRadian(phi + 10)) * sin(Math::DegreeToRadian(theta)));
			if (phi < 20)
			{
				v.color = color;
			}
			else if (phi >= 20 && phi < 40)
			{
				v.color = color2;
			}
			else if (phi >= 40)
			{
				v.color = color3;
			}
			vertex_buffer_data.push_back(v);
			indexcount++;
		}
	}

	for (float theta = 0; theta <= 360; theta += 10) //bottom
	{
		v.pos.Set(0, 0, 0);
		v.normal.Set(0, -1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
		indexcount++;

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, -1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
		indexcount++;
	}
	
	for (int i = 0; i < indexcount; i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateSquarePyramid(const std::string& meshName, Color color, float length_width, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	int indexcount = 0;

	v.pos.Set(0.5f * length_width, 0 , 0.5f * length_width);	v.color = color;
	v.normal.Set(1, 0, 1);
	vertex_buffer_data.push_back(v); //v0
	indexcount++;

	v.pos.Set(0, height, 0);	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v); //(Peak)
	indexcount++;

	v.pos.Set(-0.5f * length_width, 0, 0.5f * length_width);	v.color = color;
	v.normal.Set(-1, 0, 1);
	vertex_buffer_data.push_back(v); //v1
	indexcount++;

	v.pos.Set(0, height, 0);	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v); //(Peak)
	indexcount++;

	v.pos.Set(-0.5f * length_width, 0, -0.5f * length_width);	v.color = color;
	v.normal.Set(-1, 0, -1);
	vertex_buffer_data.push_back(v); //v2
	indexcount++;

	v.pos.Set(0, height, 0);	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v); //(Peak)
	indexcount++;

	v.pos.Set(0.5f * length_width, 0, -0.5f * length_width);	v.color = color;
	v.normal.Set(1, 0, -1);
	vertex_buffer_data.push_back(v); //v3
	indexcount++;

	v.pos.Set(0, height, 0);	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v); //(Peak)
	indexcount++;

	v.pos.Set(0.5f * length_width, 0, 0.5f * length_width);	v.color = color;
	v.normal.Set(1, 0, 1);
	vertex_buffer_data.push_back(v); //v0
	indexcount++;

	v.pos.Set(0,0,0);	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v); // Base origin
	indexcount++;

	v.pos.Set(0.5f * length_width, 0, -0.5f * length_width);	v.color = color;
	v.normal.Set(1, 0, -1);
	vertex_buffer_data.push_back(v); //v3
	indexcount++;

	v.pos.Set(0, 0, 0);	v.color = color;
	v.normal.Set(0,-1,0);
	vertex_buffer_data.push_back(v); // Base origin
	indexcount++;

	v.pos.Set(-0.5f * length_width, 0, -0.5f * length_width);	v.color = color;
	v.normal.Set(-1, 0, -1);
	vertex_buffer_data.push_back(v); //v2
	indexcount++;

	v.pos.Set(0, 0, 0);	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v); // Base origin
	indexcount++;

	v.pos.Set(-0.5f * length_width, 0, 0.5f * length_width);	v.color = color;
	v.normal.Set(-1, 0, 1);
	vertex_buffer_data.push_back(v); //v1
	indexcount++;

	v.pos.Set(0, 0, 0);	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v); // Base origin
	indexcount++;

	v.pos.Set(0.5f * length_width, 0, 0.5f * length_width);	v.color = color;
	v.normal.Set(1, 0, 1);
	vertex_buffer_data.push_back(v); //v0
	indexcount++;


	for (int i = 0; i < indexcount; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinderBody(const std::string& meshName, Color color, Color color2, unsigned numStack, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//Code for drawing with triangle strip, with multiple stack
	float stackHeight = height / numStack;
	int indexcount = 0;
	for (float stack = 0; stack < numStack; ++stack) //stack
	{
		for (float theta = 0; theta <= 360; theta += 10) //slice
		{
			v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2 + stack * stackHeight, radius * sin(Math::DegreeToRadian(theta)));
			v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
			v.color = color;
			if (stack == 0)
			{
				v.color = color2;
			}
			vertex_buffer_data.push_back(v);
			indexcount++;

			v.pos.Set(radius * (cos(Math::DegreeToRadian(theta))), -height / 2 + (stack + 1) * stackHeight, radius * sin(Math::DegreeToRadian(theta)));
			v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
			v.color = color;
			if (stack == 0)
			{
				v.color = color2;
			}
			vertex_buffer_data.push_back(v);
			indexcount++;
		}
	}

	for (float theta = 0; theta <= 360; theta += 10) //top
	{
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;

		v.pos.Set(0, height / 2, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;
	}

	for (float theta = 0; theta <= 360; theta += 10) //bottom
	{
		v.pos.Set(0, -height / 2, 0);
		v.color = color2;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color2;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		indexcount++;
	}

	for (int i = 0; i < indexcount; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color color, float radius, float height)
{
	Vertex v;
	Vector3 normaliser;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	int index_count = 0;
	float nx, ny, nz;

	for (float theta = 0; theta <= 360; theta += 10) //slice
	{
		nx = height * cos(Math::DegreeToRadian(theta));
		ny = radius;
		nz = height * sin(Math::DegreeToRadian(theta));
		normaliser.Set(nx,ny,nz);
		normaliser.Normalize();


		v.normal.Set(normaliser.x, normaliser.y, normaliser.z);
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		vertex_buffer_data.push_back(v);
		index_count++;

		v.normal.Set(normaliser.x, normaliser.y, normaliser.z);
		v.pos.Set(0, height, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
		index_count++;
	}

	for (float theta = 0; theta <= 360; theta += 10) //bottom
	{
		v.normal.Set(0, -1, 0);
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
		index_count++;

		v.normal.Set(0, -1, 0);
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		vertex_buffer_data.push_back(v);
		index_count++;
	}
	
	for (int i = 0; i < index_count; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GeneratePrism(const std::string& meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	int indexcount = 0;

	float x = 0.5 * length;

	// z+
	v.pos.Set(x, 0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-x, 0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(x, -0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-x, -0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v2

	// y-
	v.pos.Set(-x, -0.5, 0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-x, -0.5, -0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(x, -0.5, 0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(x, -0.5, -0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// x+
	v.pos.Set(x, -0.5, -0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(x, 0.5, -0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(x, -0.5, 0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(x, -0.5, 0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1

	v.pos.Set(0,0,0); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0, 0, 0); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1

	// y slunt | If z+, y+. Else if z-, y-
	v.pos.Set(x, -0.5, -0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(x, -0.5, -0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-x, -0.5, -0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(x, 0.5, 0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-x, 0.5, 0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// x-
	v.pos.Set(-x, -0.5, -0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-x, 0.5, 0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-x, -0.5, 0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3

	for (int i = 0; i < indexcount; i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCube2(const std::string& meshName, Color color, Color color2, float length)
{
	// Triangle Strip Cube
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	int indexcount = 0;

	// z+
	v.pos.Set(0.5, 0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.5, 0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v2

	// y-
	v.pos.Set(-0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// x+
	v.pos.Set(0.5, -0.5, -0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(0.5, 0.5, -0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, 0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0.5, 0.5, 0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// y+
	v.pos.Set(0.5, 0.5, 0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(0.5, 0.5, -0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-0.5, 0.5, 0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, 0.5, -0.5); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// x- // Extra two vertices to fix culling bug
	v.pos.Set(-0.5, 0.5, -0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.5, 0.5, 0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-0.5, 0.5, 0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-0.5, 0.5, -0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, -0.5, 0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, -0.5, -0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// z-
	v.pos.Set(-0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.5, 0.5, -0.5); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0.5, 0.5, -0.5); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v2

	for (int i = 0; i < indexcount; i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTrapezoid(const std::string& meshName, Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	int indexcount = 0;

	// z+
	v.pos.Set(0.6, 0.5, 0.6); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.6, 0.5, 0.6); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v); indexcount++;//v2

	// y-
	v.pos.Set(-0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, 0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// x+
	v.pos.Set(0.5, -0.5, -0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(0.6, 0.5, -0.6); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, 0.5); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0.6, 0.5, 0.6); v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// y+
	v.pos.Set(0.6, 0.5, 0.6); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(0.6, 0.5, -0.6); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-0.6, 0.5, 0.6); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.6, 0.5, -0.6); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// x- // Extra two vertices to fix culling bug
	v.pos.Set(-0.6, 0.5, -0.6); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.6, 0.5, 0.6); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-0.6, 0.5, 0.6); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(-0.6, 0.5, -0.6); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, -0.5, 0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(-0.5, -0.5, -0.5); v.color = color; v.normal.Set(-1, 0, 0); vertex_buffer_data.push_back(v); indexcount++;//v2

	// z-
	v.pos.Set(-0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v0
	v.pos.Set(-0.6, 0.5, -0.6); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v3
	v.pos.Set(0.5, -0.5, -0.5); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v1
	v.pos.Set(0.6, 0.5, -0.6); v.color = color; v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v); indexcount++;//v2

	for (int i = 0; i < indexcount; i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
	Vertex v;
	Vector3 normaliser;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//int indexcount = 0;

	float degreePerStack = 360.f / numStack;
	float degreePerSlice = 360.f / numSlice;

	degreePerStack = Math::DegreeToRadian(degreePerStack);
	degreePerSlice = Math::DegreeToRadian(degreePerSlice);

	float x1, z1; //y1 is always zero
	float x2, y2, z2;

	for (unsigned stack = 0; stack < numStack + 1; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			z1 = outerR * cos(stack * degreePerStack);
			x1 = outerR * sin(stack * degreePerStack);
			z2 = (outerR + innerR * cos(slice * degreePerSlice)) * cos(stack * degreePerStack);
			y2 = innerR * sin(slice * degreePerSlice);
			x2 = (outerR + innerR * cos(slice * degreePerSlice)) * sin(stack * degreePerStack);
			v.pos.Set(x2, y2, z2);
			v.color = color;
			normaliser.Set(x2 - x1, y2, z2 - z1);
			normaliser.Normalize();
			v.normal.Set(normaliser.x, normaliser.y, normaliser.z);
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStack; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	/*for (int i = 0; i < indexcount; ++i) {
		index_buffer_data.push_back(i);
	}*/

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}