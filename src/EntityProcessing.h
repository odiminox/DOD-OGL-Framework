#pragma once

//This is responsible for processing each of the gameObjects and their respective entity components contigeously in memory
//We need to ensure that the appropriate stages recieve the correct data that has been updated in the correct order.
//It is no good a physics component attempting to process data if the gameObject contains no transform component.

//At the kernal, all code is written in C-style(Data Orientated Design) programming techniques, 
//whilst the higher layers are C++(Object Orientated Design)
//The justification for this, is we want to keep away from the keyword "new" as much as possible
//as all processing and entity data needs to be as contigeous as possible, to stop arbitary jumps
//all over memory

//The gameObject only exists as a means for the user to interact with component data.
//All processing is done purely on the components and ignores the gameObjects, we do not
//have to acknowledge their exsistence, until the users submits a query to access a certain GO component data.


//#include "Source\memoryManager.h"
#include "Bitmap.h"
#include "Texture.h"
#include "GLSLShader.h"
#include "EntityManager.h"

namespace entityProcessing
{

	//struct processingData
	//{
		//processingData();

    void cleanupObjects();

    void updateRotations();
    void updateTranslations();
    void updateScaling();
    void updatePhysics(float delta);

    void loadTexture(std::string fileName, GLuint *object);
    void loadMeshdata(std::string fileName);

    void drawLights(entitySystem::gameObject *GO, GLSLShader *shader);

    
    void draw3DMVM(entitySystem::gameObject *GO,GLSLShader *shader);
    void draw2DMVM(entitySystem::gameObject *GO,GLSLShader *shader);
    
    void draw3DMeshes(entitySystem::gameObject *GO,GLSLShader *shader);
    void draw2DMeshes(entitySystem::gameObject *GO,GLSLShader *shader);

    void loadAllTextures();

    
    void initMeshes3D(entitySystem::gameObject *GO,GLSLShader *shader);
    void initMeshed2D(entitySystem::gameObject *GO,GLSLShader *shader);
    void initMeshComponents(GLSLShader *shader3D, GLSLShader *shader2D);
    void initCameraComponents();
    void initPhysicsComponents();
    
    void initLive3DObjects();
    void initLive2DObjects();
    
    
    void drawAllObjects(GLSLShader *shader3D, GLSLShader *shader2D);
    void updateCameraComponents();
    
    void updateSceneGraph(int objectNum);

    void runCoreUpdate();
    void runCoreDraw(GLSLShader *shader3D, GLSLShader *shader2D);

    void updateMeshComponents();

    void updatePhysicsComponents(float delta);

	//};	

}