#ifndef SCENE_H
#define SCENE_H

#include "MatrixStack.h"
#include "MeshBuilder.h"

class Scene
{

protected:
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

		//week 7
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_LIGHTENABLED,
		U_NUMLIGHTS,

		//week 9
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		//Week 14
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
	unsigned m_vertexArrayID;
	unsigned m_programID;

	std::string sceneName;

	//stores handlers for uniform parametes
	unsigned m_parameters[U_TOTAL];
	double elapsed;

	bool lightEnable;

public:
	Scene() { elapsed = 0.0; }
	~Scene() {}

	void elapser(double dt);
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	bool isLightEnabled();
	void setLightEnabled(bool);
	void toggleLights();
	std::string getName();

	double getElapsedTime();
//protected: //Change to protected if have time to add functions
	MS modelStack, viewStack, projectionStack;
	
	void ReceiveMessage(Scene* scene, std::string message);
	void RenderMesh(Mesh* mesh, bool lightEnabled);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);

};

#endif