#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, float lengthX, float lengthY, Color color);
	static Mesh* GenerateCube(const std::string& meshName, Color color, Color color2, float length);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius = 1.f);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.f);
	static Mesh* GenerateSphere2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.f);

	// Prince geometries
	static Mesh* GenerateCylinderHead(const std::string& meshName, Color color, Color color2, Color color3, unsigned numStack, float radius, float height);
	static Mesh* GenerateHemisphere(const std::string& meshName, Color color, Color color2, Color color3, float radius);
	static Mesh* GenerateSquarePyramid(const std::string& meshName, Color color, float length_width, float height); // For nose
	static Mesh* GenerateCylinderBody(const std::string& meshName, Color color, Color color2, unsigned numStack, float radius, float height);
	static Mesh* GenerateCone(const std::string& meshName, Color color, float radius, float height);

	static Mesh* GeneratePrism(const std::string& meshName, Color color, float length);
	static Mesh* GenerateCube2(const std::string& meshName, Color color, Color color2, float length);
	static Mesh* GenerateTrapezoid(const std::string& meshName, Color color);


	static Mesh* GenerateTorus2(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerR, float innerR);
};

#endif