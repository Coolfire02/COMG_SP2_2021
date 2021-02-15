#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "LoadOBJ.h"

//Load OBJ
Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string& file_path) {
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	if (!LoadOBJ(file_path.c_str(), vertices, uvs, normals))
		return NULL;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex_buffer_data);
	return mesh;
}

Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName,
	const std::string& file_path, const std::string& mtl_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(),
		vertices, uvs, normals, materials);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data,
		vertex_buffer_data);
	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials)
		mesh->materials.push_back(material);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	calcMinMaxPos(mesh, vertex_buffer_data);
	return mesh;
}


Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol)
{
	float length = 1.0f;
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	v.normal.Set(0, 0, 1);

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int indexOffset = 0;
	unsigned offset = 0;
	Color color(0, 1, 0);
	v.normal.Set(0, 0, 1);
	//v.pos.set(0.5f * length, 0.5f * length, 0.f);	v.color = color; v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v); //v0
	//v.pos.set(-0.5f * length, 0.5f * length, 0.f);	v.color = color; v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v); //v1
	//v.pos.set(-0.5f * length, -0.5f * length, 0.f);	v.color = color; v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v); //v2
	//v.pos.set(0.5f * length, -0.5f * length, 0.f);	v.color = color; v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v); //v3

	////tri1
	//index_buffer_data.push_back(0);
	//index_buffer_data.push_back(1);
	//index_buffer_data.push_back(2);
	////tri2
	//index_buffer_data.push_back(0);
	//index_buffer_data.push_back(2);
	//index_buffer_data.push_back(3);

	for (unsigned row = 0; row < numRow; ++row) {
		for (unsigned col = 0; col < numCol; ++col) {
			/*Task: Add 4 vertices into vertex_buffer_data
			Task: Add 6 indices into index_buffer_data*/
			
			v.pos.set(-0.5f, 0.5f, 0.f); //TOPL
			v.texCoord.Set(0 + width * col, 1 - height * row);
			vertex_buffer_data.push_back(v);

			v.pos.set(-0.5f, -0.5f, 0.f); //BOTL
			v.texCoord.Set(0 + width * (col), 1 - height * (row+1));
			vertex_buffer_data.push_back(v);

			v.pos.set(0.5f, 0.5f, 0.f); //TOPR
			v.texCoord.Set(0 + width * (col+1), 1 - height * row);
			vertex_buffer_data.push_back(v);

			v.pos.set(0.5f, -0.5f,0.f); //BOTR
			v.texCoord.Set(0 + width * (col+1), 1 - height * (row + 1));
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(0+indexOffset);
			index_buffer_data.push_back(1 + indexOffset);
			index_buffer_data.push_back(2 + indexOffset);

			index_buffer_data.push_back(2 + indexOffset);
			index_buffer_data.push_back(1 + indexOffset);
			index_buffer_data.push_back(3 + indexOffset);

			indexOffset += 4;
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	calcMinMaxPos(mesh, vertex_buffer_data);
	return mesh;
}

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
	std::vector<Vertex> vertex;
	Vertex v;

	v.pos.set(-100.0f, 0.0f, 0.0f); v.color.set(1.0f, 0.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(100.0f, 0.0f, 0.0f); v.color.set(1.0f, 0.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(0.0f, -100.0f, 0.0f); v.color.set(0.0f, 1.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(0.0f, 100.0f, 0.0f); v.color.set(0.0f, 1.0f, 0.0f);  vertex.push_back(v);
	v.pos.set(0.0f, 0.0f, 100.0f); v.color.set(0.0f, 0.0f, 1.0f);  vertex.push_back(v);
	v.pos.set(0.0f, 0.0f, -100.0f); v.color.set(0.0f, 0.0f, 1.0f);  vertex.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 6; i++) {
		index_buffer_data.push_back(i);
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
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

float coneX(float height, float totalHeight, int radius, int theta) {
	return height / totalHeight * radius * cos(Math::DegreeToRadian((float)theta));
}

float coneZ(float height, float totalHeight, int radius, int theta) {
	return height / totalHeight * radius * sin(Math::DegreeToRadian((float)theta));
}

Mesh* MeshBuilder::GenerateHalfCone(const std::string& meshName, Color color, int rad, int height)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;
	for (float theta = 1; theta <= 179; theta += 2) {
		if (theta > 179) theta = 179;
		float z = rad * sin(Math::DegreeToRadian(theta));
		v.pos.set(rad * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, z);
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, z);
		v.normal.Normalize();
		vertex.push_back(v);

		v.pos.set(0, (float)height / 2.0, 0);
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, z);
		v.normal.Normalize();
		vertex.push_back(v);
	}

	for (float theta = 1; theta <= 179; theta += 2) {
		if (theta > 179) theta = 179;

		float z = rad * sin(Math::DegreeToRadian(theta));
		v.pos.set(rad * cos(Math::DegreeToRadian(theta)), (float) -height / 2.0, z);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);

		v.pos.set(0, (float)-height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
	}
	v.normal.Set(0, 0, -1);
	v.pos.set(0, (float)height / 2.0, 0); vertex.push_back(v);
	v.pos.set((float)rad, (float)-height / 2.0, 0); vertex.push_back(v);
	v.pos.set((float)-rad, (float)-height / 2.0, 0); vertex.push_back(v);

	for (unsigned int i = 0; i < vertex.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateConicalFrustum(const std::string& meshName, Color color, float innerR, float outerR, int height)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.set(outerR * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, outerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set((float)height * cos(Math::DegreeToRadian(theta)), outerR, (float)height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);

		v.pos.set(innerR * cos(Math::DegreeToRadian(theta)), (float)height / 2.0, innerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set((float)height * cos(Math::DegreeToRadian(theta)), innerR, (float)height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.set(outerR * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, outerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);

		v.pos.set(0, (float)-height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.set(innerR * cos(Math::DegreeToRadian(theta)), (float)height / 2.0, innerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, 1, 0);
		//debug: v.color.set(1, 0, 0);
		vertex.push_back(v);
		
		v.pos.set(0, (float)height / 2.0, 0);
		v.normal.Set(0, 1, 0);
		vertex.push_back(v);
	}

	for (unsigned int i = 0; i < vertex.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color color, int rad, int height)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.set(rad * cos(Math::DegreeToRadian(theta)), -height / 2.0, (float)rad * sin(Math::DegreeToRadian(theta)) );
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);

		v.pos.set(0, (float)height / 2.0, 0);
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 2) {

		v.pos.set(0, -height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
		
		v.pos.set(rad * cos(Math::DegreeToRadian(theta)), -height / 2.0, rad * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
	}

	for (int i = 0; i < vertex.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}


Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, int height)
{
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	float rad = 1.0;
	int numStack = 10 * height;
	int index = 0;
	float stackHeight = ((float) height) / numStack;

	for (float theta = 0; theta <= 360; theta += 10) {
		float x = rad * cos(Math::DegreeToRadian(theta));
		float z = rad * sin(Math::DegreeToRadian(theta));

		v.pos.set(0, -height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.pos.set(x, -height / 2.0, z);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}

	for (int stack = 0; stack < numStack; ++stack) {
		for (float theta = 0; theta <= 360; theta += 10) {
			float x = rad * cos(Math::DegreeToRadian(theta));
			float z = rad * sin(Math::DegreeToRadian(theta));
			v.pos.set(x, (float)-height / 2.0 + (float)stack * stackHeight, z);
			v.normal.Set(x,0,z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			v.pos.set(x, (float)-height / 2.0 + ((float)stack + 1) * stackHeight, z);
			v.normal.Set(x, 0, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}

	for (float theta = 0; theta <= 360; theta += 10) {
		float x = rad * cos(Math::DegreeToRadian(theta));
		float z = rad * sin(Math::DegreeToRadian(theta));

		v.pos.set(x, (float)height / 2.0, z);
		v.normal.Set(0, 1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.pos.set(0, (float)height / 2.0, 0);
		v.normal.Set(0, 1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, Color color, float innerR, float outerR) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	
	unsigned int numStacks = 70;
	unsigned int numSlices = 200;
	float degreePerStack = 360.f / numStacks;
	float degreePerSlice = 360.f / numSlices;
	float x1, z1;
	float x2, y2, z2;
	for (unsigned int stack = 0; stack < numStacks + 1; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			z1 = outerR * cos(Math::DegreeToRadian(stack * degreePerStack));
			x1 = outerR * sin(Math::DegreeToRadian(stack * degreePerStack));
			z2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice))) * cos(Math::DegreeToRadian(stack * degreePerStack));
			y2 = innerR * sin(Math::DegreeToRadian(slice * degreePerSlice));
			x2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice))) * sin(Math::DegreeToRadian(stack * degreePerStack));
			v.pos.set(x2, y2, z2);
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex.push_back(v);
		}
	}

	for (unsigned int stack = 0; stack < numStacks; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
		}

	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateHalfTorus(const std::string& meshName, Color color, float innerR, float outerR) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;


	unsigned int numStacks = 70;
	unsigned int numSlices = 200;
	float degreePerStack = 180.f / numStacks;
	float degreePerSlice = 360.f / numSlices;
	float x1, z1;
	float x2, y2, z2;
	for (unsigned int stack = 0; stack < numStacks + 1; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			z1 = outerR * cos(Math::DegreeToRadian(stack * degreePerStack + 180));
			x1 = outerR * sin(Math::DegreeToRadian(stack * degreePerStack + 180));
			z2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice))) * cos(Math::DegreeToRadian(stack * degreePerStack + 180));
			y2 = innerR * sin(Math::DegreeToRadian(slice * degreePerSlice));
			x2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice))) * sin(Math::DegreeToRadian(stack * degreePerStack + 180));
			v.pos.set(x2, y2, z2);
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex.push_back(v);
		}
	}

	for (unsigned int stack = 0; stack < numStacks; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
		}

	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

float sphereX(float phi, float theta) {
	return cos(phi * Math::PI / 180) * cos(theta * Math::PI / 180);
}

float sphereY(float phi) {
	return sin(phi * Math::PI / 180);
}

float sphereZ(float phi, float theta) {
	return cos(phi * Math::PI / 180) * sin(theta * Math::PI / 180);
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;
	
	unsigned int numStack = 60;
	unsigned int numSlice = 180;
	unsigned int radius = 1;
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;

	for (unsigned stack = 0; stack < numStack + 1; ++stack) {
		float phi = -90 + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			float theta = slice * degreePerSlice;
			v.pos.set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			v.texCoord.Set(1-(slice/(float)numSlice), (stack/ (float)numStack));
			vertex.push_back(v);
		}
		
	}
	for (unsigned stack = 0; stack < numStack; ++stack) {
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	/*int index = 0;
	for (int phi = 0; phi < 180; phi += 1) {
		for (int theta = 0; theta <= 360; theta += 2) {
			
			v.normal.Set(sphereX(phi, theta), sphereY(phi) * (phi >= 90 ? -1 : 1), sphereZ(phi, theta));
			v.normal.Normalized();
			float x = 1 * sphereX(phi, theta);
			float y = 1 * sphereY(phi);
			if (phi >= 90)
				y *= -1;
			float z = 1 * sphereZ(phi, theta);
			v.pos.set(x, y, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			x = 1 * sphereX(phi+10, theta);
			y = 1 * sphereY(phi+10);
			if (phi >= 90)
				y *= -1;
			z = 1 * sphereZ(phi+10, theta);

			v.pos.set(x, y, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}*/

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateHemiSphere(const std::string& meshName, Color color) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	unsigned int index = 0;
	unsigned int numStack = 60;
	unsigned int numSlice = 90;
	unsigned int radius = 1;
	float degreePerStack = 90.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;

	for (float theta = 0; theta <= 360; theta += degreePerSlice) {
		v.normal.Set(0, -1, 0);
		v.pos.set(0, 0, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.normal.Set(0, -1, 0);
		v.pos.set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}

	for (unsigned stack = 0; stack < numStack+1; ++stack) {
		float phi = stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice+1; ++slice) {
			float theta = slice * degreePerSlice;
			v.pos.set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			v.normal.Set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			v.pos.set(radius * sphereX(phi+degreePerStack, theta), radius * sphereY(phi + degreePerStack), radius * sphereZ(phi + degreePerStack, theta));
			v.normal.Set(radius * sphereX(phi + degreePerStack, theta), radius * sphereY(phi + degreePerStack), radius * sphereZ(phi + degreePerStack, theta));
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateQuaterSphere(const std::string& meshName, Color color) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	unsigned int index = 0;
	unsigned int numStack = 60;
	unsigned int numSlice = 90;
	unsigned int radius = 1;
	float degreePerStack = 89.f / numStack;
	float degreePerSlice = 179.f / numSlice;

	for (float theta = 180; theta >= 0; theta -= degreePerSlice) {
		v.normal.Set(0, 0, -1);
		v.pos.set(0, 0, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.normal.Set(0, 0, -1);
		v.pos.set(radius * cos(Math::DegreeToRadian(theta)), radius * sin(Math::DegreeToRadian(theta)), 0);
		
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}

	for (float theta = 0; theta <= 180; theta += degreePerSlice) {
		v.normal.Set(0, -1, 0);
		v.pos.set(0, 0, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.normal.Set(0, -1, 0);
		v.pos.set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}

	for (unsigned stack = 0; stack < numStack + 1; ++stack) {
		float phi = stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			float theta = slice * degreePerSlice;
			v.pos.set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			v.normal.Set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			v.pos.set(radius * sphereX(phi + degreePerStack, theta), radius * sphereY(phi + degreePerStack), radius * sphereZ(phi + degreePerStack, theta));
			v.normal.Set(radius * sphereX(phi + degreePerStack, theta), radius * sphereY(phi + degreePerStack), radius * sphereZ(phi + degreePerStack, theta));
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}
	

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();
	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateHemiSphereFrustum(const std::string& meshName, Color color, float degreeCutOff) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	if (degreeCutOff > 180 || degreeCutOff < 2) degreeCutOff = 180;
	degreeCutOff /= 2;
	v.color = color;
	unsigned int index = 0;
	unsigned int numStack = 60;
	unsigned int numSlice = 90;
	unsigned int radius = 1;
	float degreePerStack = degreeCutOff / numStack;
	float degreePerSlice = 360.f / numSlice;

	for (float theta = 0; theta <= 360; theta += degreePerSlice) {
		v.normal.Set(0, -1, 0);
		v.pos.set(0, 0, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.normal.Set(0, -1, 0);
		v.pos.set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}

	for (unsigned stack = 0; stack < numStack+1; ++stack) {
		float phi = stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice+1; ++slice) {
			float theta = slice * degreePerSlice;
			v.pos.set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			v.normal.Set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			v.pos.set(radius * sphereX(phi + degreePerStack, theta), radius * sphereY(phi + degreePerStack), radius * sphereZ(phi + degreePerStack, theta));
			v.normal.Set(radius * sphereX(phi + degreePerStack, theta), radius * sphereY(phi + degreePerStack), radius * sphereZ(phi + degreePerStack, theta));
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}

	float innerR = sphereX(90, 360) - sphereX(degreeCutOff+degreePerStack, 360);
	float topHeight = radius * sphereY(degreeCutOff + degreePerStack);


	for (float theta = 0; theta <= 360; theta += degreePerSlice) {
		v.normal.Set(0, 1, 0);
		v.pos.set(innerR * cos(Math::DegreeToRadian(theta)), topHeight, innerR * sin(Math::DegreeToRadian(theta)));
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
		
		v.normal.Set(0, 1, 0);
		v.pos.set(0, topHeight, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateTetahedron(const std::string& meshName, Color color) {
	int index = 0;
	std::vector<Vertex> vertex;
	Vertex v;
	v.color = color;
	Vector3 normal;

	normal.Set(0.0f, 0.0f, 1.0f);
	v.pos.set(0.0f, 0.75f, 0.25f); v.normal = normal; vertex.push_back(v); //front
	v.pos.set(-0.5f, -0.25f, 0.25f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.25f, 0.25f); v.normal = normal; vertex.push_back(v);

	normal.Set(0.5f, 0.5f, 0.0f);
	v.pos.set(0.0f, 0.75f, 0.25f); v.normal = normal; vertex.push_back(v); //right
	v.pos.set(0.5f, -0.25f, 0.25f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.0f, -0.25f,- 0.75f); v.normal = normal; vertex.push_back(v);

	normal.Set(-0.5f, 0.5f, 0.0f);
	v.pos.set(0.0f, 0.75f, 0.25f); v.normal = normal; vertex.push_back(v); //left
	v.pos.set(0.0f, -0.25f, -0.75f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.25f, 0.25f); v.normal = normal; vertex.push_back(v);
	

	normal.Set(0.0f, -1.0f, 0.0f);
	v.pos.set(0.5f, -0.25f, 0.25f); v.normal = normal; vertex.push_back(v); //bottom
	v.pos.set(-0.5f, -0.25f, 0.25f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.0f, -0.25f, -0.75f); v.normal = normal; vertex.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 12; i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();


	calcMinMaxPos(mesh, vertex);
	return mesh;

}

Mesh* MeshBuilder::GenerateQuad(const std::string& meshName, Color color)
{
	float length = 1.0f;
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	v.normal.Set(0, 0, 1);
	v.pos.set(0.5f * length, 0.5f * length, 0.f);	v.color = color; v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v); //v0
	v.pos.set(-0.5f * length, 0.5f * length, 0.f);	v.color = color; v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v); //v1
	v.pos.set(-0.5f * length, -0.5f * length, 0.f);	v.color = color; v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v); //v2
	v.pos.set(0.5f * length, -0.5f * length, 0.f);	v.color = color; v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v); //v3

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

	calcMinMaxPos(mesh, vertex_buffer_data);
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
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
	// Cube
	int index = 0;
	std::vector<Vertex> vertex;
	Vertex v;
	v.color = color;
	Vector3 normal;
	normal.Set(0, 0, 1);
	v.pos.set(0.5f, 0.5f, 0.5f); v.normal = normal;  vertex.push_back(v); //front
	v.pos.set(-0.5f, 0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);

	normal.Set(-1, 0, 0);
	v.pos.set(-0.5f, 0.5f, 0.5f); v.normal = normal; vertex.push_back(v); //forward left
	v.pos.set(-0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);

	normal.Set(0, 0, -1);
	v.pos.set(-0.5f, 0.5f, -0.5f); v.normal = normal;  vertex.push_back(v); //forward back
	v.pos.set(0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);

	v.pos.set(-0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);

	normal.Set(1, 0, 0);
	v.pos.set(0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v); //forward right
	v.pos.set(0.5f, 0.5f, 0.5f);  v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);

	normal.Set(0, 1, 0);
	v.pos.set(0.5f, 0.5f, 0.5f); v.normal = normal;  vertex.push_back(v);//up
	v.pos.set(0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f); v.normal = normal; vertex.push_back(v);

	v.pos.set(0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, 0.5f, 0.5f); v.normal = normal; vertex.push_back(v);

	normal.Set(0, -1, 0);
	v.pos.set(0.5f, -0.5f, 0.5f); v.normal = normal;  vertex.push_back(v);//down
	v.pos.set(-0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);

	v.pos.set(0.5f, -0.5f, 0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(-0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);
	v.pos.set(0.5f, -0.5f, -0.5f); v.normal = normal; vertex.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 36; i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

Mesh* MeshBuilder::GenerateHitBox(const std::string& meshName, Position3D* botLeftPos, Position3D* topRightPos)
{
	// Cube
	int index = 0;
	std::vector<Vertex> vertex;
	Vertex v;
	v.color = Color(1,1,1);
	Vector3 normal;
	normal.Set(0, 0, 1);
	v.pos.set(topRightPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal;  vertex.push_back(v); //front
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);

	v.pos.set(topRightPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);

	normal.Set(-1, 0, 0);
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v); //forward left
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);

	v.pos.set(botLeftPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);

	normal.Set(0, 0, -1);
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal;  vertex.push_back(v); //forward back
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);

	v.pos.set(botLeftPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);

	normal.Set(1, 0, 0);
	v.pos.set(topRightPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v); //forward right
	v.pos.set(topRightPos->getX(), topRightPos->getY(), botLeftPos->getZ());  v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);

	v.pos.set(topRightPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);

	normal.Set(0, 1, 0);
	v.pos.set(topRightPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal;  vertex.push_back(v);//up
	v.pos.set(topRightPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);

	v.pos.set(topRightPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), topRightPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);

	normal.Set(0, -1, 0);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal;  vertex.push_back(v);//down
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);

	v.pos.set(topRightPos->getX(), botLeftPos->getY(), botLeftPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(botLeftPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);
	v.pos.set(topRightPos->getX(), botLeftPos->getY(), topRightPos->getZ()); v.normal = normal; vertex.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 36; i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh("HitBox-"+meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();

	calcMinMaxPos(mesh, vertex);
	return mesh;
}

void MeshBuilder::calcMinMaxPos(Mesh* mesh, std::vector<Vertex> vertex_buffer_data) {
	
	float lowX, lowY, highZ, //Bot Left
		highX, highY, lowZ; //Top Right
	lowX = lowY = highZ = highX = highY = lowZ = 0.f;

	for (auto& entry : vertex_buffer_data) {
		Position pos = entry.pos;
		if (pos.x < lowX) lowX = pos.x;
		else if (pos.x > highX) highX = pos.x;

		if (pos.y < lowY) lowY = pos.y;
		else if (pos.y > highY) highY = pos.y;

		if (pos.z < lowZ) lowZ = pos.z;
		else if (pos.z > highZ) highZ = pos.z;
	}

	mesh->botLeftPos = new Position3D(lowX, lowY, highZ);
	mesh->topRightPos = new Position3D(highX, highY, lowZ);

}