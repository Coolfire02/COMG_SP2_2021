#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>
#include "Vertex.h"
#include "Vector3.h"
#include "Material.h"

/******************************************************************************/
/*!
\file	LoadOBJ.h
\brief
Handles loading of OBJs and MTLs
*/
/******************************************************************************/

bool LoadOBJ(
	const char *file_path, 
	std::vector<Position> & out_vertices, 
	std::vector<TexCoord> & out_uvs, 
	std::vector<Vector3> & out_normals
);

void IndexVBO(
	std::vector<Position> & in_vertices,
	std::vector<TexCoord> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
);

bool LoadOBJMTL(
	const char* file_path, 
	const char* mtl_path,
	std::vector<Position>& out_vertices,
	std::vector<TexCoord>& out_uvs,
	std::vector<Vector3>& out_normals,
	std::vector<Material>& out_materials
);

#endif