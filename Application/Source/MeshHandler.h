#pragma once
#include "Mesh.h"
#include "MeshBuilder.h"
#include "EntityDataHandler.h"

enum GEOMETRY_TYPE {
	//General
	GEO_AXES = 0,
	GEO_LIGHTBALL,
	GEO_TEXT,

	//For OBJs
	GEO_TREE,

	//Platform
	

	//Misc
	

	//Skybox
	GEO_SKY_LEFT,
	GEO_SKY_RIGHT,
	GEO_SKY_TOP,
	GEO_SKY_BOTTOM,
	GEO_SKY_FRONT,
	GEO_SKY_BACK,

	//UI
	

	//Textured Quads
	

	//For non-OBJs


	//END
	NUM_GEOMETRY
};

class MeshHandler
{
	static Mesh* meshList[NUM_GEOMETRY];
	static bool isLoaded;

public:
	static bool loadMeshes();
	static bool unloadMeshes();

	static Mesh* getMesh(GEOMETRY_TYPE);
};

