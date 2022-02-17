#include "EntityProcessing.h"

//GLSLShader entityProcessing::shaderLoader;
//glm::mat4 entityProcessing::view;
//glm::mat4 entityProcessing::projection;

//entityProcessing::processingData()
//{
//}


void entityProcessing::cleanupObjects()
{
	//safeDelete(textureLoader);
}


void entityProcessing::updateRotations()
{

}
void entityProcessing::updateTranslations()
{
}
void entityProcessing::updateScaling(){

}


//Create method to clean-up textures at end, as currently they create a memory leak
void entityProcessing::loadTexture(std::string fileName, GLuint *object)
{
	Texture* textureLoader;
	Bitmap bmp = Bitmap::bitmapFromFile(fileName);
	bmp.flipVertically();
	textureLoader = new Texture(bmp);
	//I don't know if this will work
	object = &textureLoader->_object;
	//delete textureLoader;
	//textureLoader = NULL;
//		safeDelete(textureLoader);
}
void entityProcessing::loadMeshdata(std::string fileName)
{
	//method for loading mesh data here
	//Also need to expand functionality to support skeletal animations
}


	static const entityData::Vertex testVerts[] =
	{
		// Front
		{{-0.5, -0.5, 0.5}, {0.0f, 0.0f, 1.0f}, {1, 0, 0, 1}, {0, 0}},
		{{0.5, -0.5, 0.5}, {0.0f, 0.0f, 1.0f}, {0, 1, 0, 1}, {1, 0}},
		{{0.5, 0.5, 0.5}, {0.0f, 0.0f, 1.0f},{0, 0, 1, 1}, {1, 1}},
		{{-0.5, 0.5, 0.5},{0.0f, 0.0f, 1.0f}, {0, 0, 0, 1}, {0, 1}},
		// Back
		{{0.5, -0.5, 0.5}, {1.0f, 0.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{0.5, -0.5, -0.5},{1.0f, 0.0f, 0.0f}, {0, 1, 0, 1}, {1, 0}},
		{{0.5, 0.5, -0.5},{1.0f, 0.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{0.5, 0.5, 0.5},{1.0f, 0.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}},
		// Left
		{{-0.5, -0.5, -0.5}, {0.0f, 0.0f, -1.0f},{1, 0, 0, 1}, {0, 0}},
		{{-0.5, 0.5, -0.5},{0.0f, 0.0f, -1.0f}, {0, 1, 0, 1}, {1, 0}},
		{{0.5, 0.5, -0.5}, {0.0f, 0.0f, -1.0f},{0, 0, 1, 1}, {1, 1}},
		{{0.5, -0.5, -0.5},{0.0f, 0.0f, -1.0f}, {0, 0, 0, 1}, {0, 1}},
		// Right
		{{-0.5, -0.5, 0.5},{-1.0f, 0.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{-0.5, 0.5, 0.5}, {-1.0f, 0.0f, 0.0f},{0, 1, 0, 1}, {1, 0}},
		{{-0.5, 0.5, -0.5},{-1.0f, 0.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{-0.5, -0.5, -0.5},{-1.0f, 0.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}},
		// Top
		{{-0.5, -0.5, 0.5},{0.0f, -1.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{-0.5, -0.5, -0.5},{0.0f, -1.0f, 0.0f}, {0, 1, 0, 1}, {1, 0}},
		{{0.5, -0.5, -0.5},{0.0f, -1.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{0.5, -0.5, 0.5},{0.0f, -1.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}},
		// Bottom
		{{-0.5, 0.5, 0.5},{0.0f, 1.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{0.5, 0.5, 0.5}, {0.0f, 1.0f, 0.0f},{0, 1, 0, 1}, {1, 0}},
		{{0.5, 0.5, -0.5},{0.0f, 1.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{-0.5, 0.5, -0.5},{0.0f, 1.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}}
	};

static const GLubyte testIndices[] =
{
	0,1,2,0,2,3,
	4,5,6,4,6,7,
	8,9,10,8,10,11,
	12,13,14,12,14,15,
	16,17,18,16,18,19,
	20,21,22,20,22,23
};

void entityProcessing::drawLights(entitySystem::gameObject *GO, GLSLShader *shader)
{
    glm::vec4 tempPos = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    glm::vec3 tempEntPos = entityManager::gameObjects::lightComponent::GOGetLightPosition(GO);
    tempPos.x = tempEntPos.x;
    tempPos.y = tempEntPos.y;
    tempPos.z = tempEntPos.z;
    tempPos.w = 1.0f;
    
    shader->setUniform("lightPosition", tempPos);
    
    shader->setUniform("Ka", entityManager::gameObjects::lightComponent::GOGetLightKa(GO));
    shader->setUniform("Kd", entityManager::gameObjects::lightComponent::GOGetLightKd(GO));
    shader->setUniform("Ks", entityManager::gameObjects::lightComponent::GOGetLightKs(GO));
    
    shader->setUniform("La", entityManager::gameObjects::lightComponent::GOGetLightLa(GO));
    shader->setUniform("Ld", entityManager::gameObjects::lightComponent::GOGetLightLd(GO));
    shader->setUniform("Ls", entityManager::gameObjects::lightComponent::GOGetLightLs(GO));
    
    shader->setUniform("shininess", entityManager::gameObjects::lightComponent::GoGetLightShininess(GO));

}

void entityProcessing::initMeshComponents(GLSLShader *shader3D, GLSLShader *shader2D)
{
	for(int i = 0; i < worldData::WOTData::worldObjects.size(); ++i){
        
        if(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].scale.z != 0.0f){
            
            initMeshes3D(&worldData::WOTData::worldObjects[i], shader3D);
            
        }else if(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].scale.z == 0.0f){
            
            initMeshed2D(&worldData::WOTData::worldObjects[i], shader2D);
        }
	}
}

void entityProcessing::loadAllTextures()
{
	for(int i = 0; i < worldData::WOTData::worldMeshComponents.size(); ++i){
		loadTexture(worldData::WOTData::worldMeshComponents[i].diffuseName, &worldData::WOTData::worldMeshComponents[i]._texture);//Init the texture data first
	}
}

void entityProcessing::drawAllObjects(GLSLShader *shader3D, GLSLShader *shader2D)
{
	for(int i = 0; i <worldData::WOTData::worldObjects.size(); ++i){
        
		if((worldData::WOTData::worldObjects[i].gameObjectID & 64) == 64)
		{
            //Check the z component of the object to see if it is 2D or 3D, 2D objects will always have a Z component of 0
            if(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].scale.z != 0.0f){
                
                //Draw 3D objects
                shader3D->bind();
                
                draw3DMVM(&worldData::WOTData::worldObjects[i], shader3D);
                draw3DMeshes(&worldData::WOTData::worldObjects[i], shader3D);

                shader3D->unbind();
                
            } else if(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].scale.z == 0.0f){
                
                //Draw 2D objects
                shader2D->bind();
                
                draw2DMVM(&worldData::WOTData::worldObjects[i], shader2D);
                draw2DMeshes(&worldData::WOTData::worldObjects[i], shader2D);
                
                shader2D->unbind();
            }
		}
        
        //Check to see if the object has a light component
        if((worldData::WOTData::worldObjects[i].gameObjectID & 8) == 8){
            shader3D->bind();
            drawLights(&worldData::WOTData::worldObjects[i], shader3D);
            shader3D->unbind();
        }
        
	}
}

void entityProcessing::initMeshes3D(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){
        
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._positionSlot,"Position");
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._colorSlot,   "SourceColor");
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._texCoordSlot,"TexCoordIn");
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._NormalSlot,  "Normal");
		
		glGenBuffers(1, &worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._vertexBufferID);
		glGenBuffers(1, &worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._indexBufferID);
        
		glBindBuffer(GL_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Vertices.size() * sizeof(entityData::Vertex), worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Vertices.data(), GL_STATIC_DRAW);
        
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._indexBufferID);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Indices.size() * sizeof(entityData::Index), worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Indices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);
        
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._positionSlot); // Vertex Position
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._colorSlot);    // Vertex Colour
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._texCoordSlot); // Vertex Texture
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._NormalSlot);   // Vertex Normal
        
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex) , 0);
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._NormalSlot,   3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._colorSlot,    4, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 6));
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._texCoordSlot, 2, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 10));
	}

}
void entityProcessing::initMeshed2D(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){
        
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._positionSlot,"Position");
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._colorSlot,   "SourceColor");
		shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._texCoordSlot,"TexCoordIn");
        shader->loadAttribute(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._NormalSlot,  "Normal");
		
		glGenBuffers(1, &worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._vertexBufferID);
		glGenBuffers(1, &worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._indexBufferID);
        
		glBindBuffer(GL_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Vertices.size() * sizeof(entityData::Vertex), worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Vertices.data(), GL_STATIC_DRAW);
        
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._indexBufferID);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Indices.size() * sizeof(entityData::Index), worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].Indices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);
        
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._positionSlot); // Vertex Position
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._colorSlot);    // Vertex Colour
		glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._texCoordSlot); // Vertex Texture
		//glEnableVertexAttribArray(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._NormalSlot);   // Vertex Normal
        
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex) , 0);
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._NormalSlot,   3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._colorSlot,    4, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 6));
		glVertexAttribPointer(worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._texCoordSlot, 2, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 10));
	}

}
void entityProcessing::draw3DMVM(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 128) == 128)
	{
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv = worldData::eData::view * worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].model;
        shader->setUniform("modelMatrix",  worldData::eData::view * worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].model);
        shader->setUniform("viewMatrix",  worldData::eData::view);
        shader->setUniform("projectionMatrix",  worldData::eData::projection);
		shader->setUniform("modelViewMatrix", worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv);
		shader->setUniform("MVP",  worldData::eData::projection * worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv);
        
        shader->setUniform("normalMatrix", glm::mat3(glm::vec3(worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv[0]),glm::vec3(worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv[1]),glm::vec3(worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv[2]) ));
	}
    
    if((GO->gameObjectID & 8) == 8)
	{
        shader->setUniform("cameraPosition",  worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon);
    }

}
void entityProcessing::draw2DMVM(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 128) == 128)
	{
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv = worldData::eData::view * worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].model;
        shader->setUniform("modelMatrix",  worldData::eData::view * worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].model);
        shader->setUniform("viewMatrix",  worldData::eData::view);
        shader->setUniform("projectionMatrix",  worldData::eData::projection);
		shader->setUniform("modelViewMatrix", worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv);
		shader->setUniform("MVP",  worldData::eData::projection * worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].mv);
	}

}
void entityProcessing::draw3DMeshes(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){
        glBindBuffer(GL_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._indexBufferID);
        
        shader->setUniform("red",   entityManager::gameObjects::meshComponent::GOGetRed(GO));
        shader->setUniform("green", entityManager::gameObjects::meshComponent::GOGetGreen(GO));
        shader->setUniform("blue",  entityManager::gameObjects::meshComponent::GOGetBlue(GO));
        shader->setUniform("alpha", entityManager::gameObjects::meshComponent::GOGetAlpha(GO));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].pTexture->_object);
        
        shader->setUniform("Texture", 0);//Apply the uniform for this instance
        
        glDrawElements(GL_TRIANGLE_STRIP, sizeof(testIndices)/sizeof(testIndices[0]), GL_UNSIGNED_BYTE, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
}
//currently is same as above, but requires different shader and enables different uniform access in the future
void entityProcessing::draw2DMeshes(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){
        glBindBuffer(GL_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]]._indexBufferID);
        
        shader->setUniform("red",   entityManager::gameObjects::meshComponent::GOGetRed(GO));
        shader->setUniform("green", entityManager::gameObjects::meshComponent::GOGetGreen(GO));
        shader->setUniform("blue",  entityManager::gameObjects::meshComponent::GOGetBlue(GO));
        shader->setUniform("alpha", entityManager::gameObjects::meshComponent::GOGetAlpha(GO));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].pTexture->_object);
        
        shader->setUniform("Texture", 0);//Apply the uniform for this instance
        
        glDrawElements(GL_TRIANGLE_STRIP, sizeof(testIndices)/sizeof(testIndices[0]), GL_UNSIGNED_BYTE, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    }

}

void entityProcessing::updateSceneGraph(int objectNum)
{
    if((worldData::WOTData::worldObjects[objectNum].gameObjectID & 128) == 128){
        
        worldData::WOTData::worldTransformComponents[objectNum].isDirty = false;
        
        //Assign the X, Y and Z inputs from the rotation the user entered to the quartonion
        worldData::WOTData::worldTransformComponents[objectNum].qOrientation.setEulerZYX(worldData::WOTData::worldTransformComponents[objectNum].rotZ,worldData::WOTData::worldTransformComponents[objectNum].rotY,worldData::WOTData::worldTransformComponents[objectNum].rotX);
        
        //We assign the values over from the bullet physics quartonion, to the glm one
        worldData::WOTData::worldTransformComponents[objectNum].orientation.x = worldData::WOTData::worldTransformComponents[objectNum].qOrientation.x();
        worldData::WOTData::worldTransformComponents[objectNum].orientation.y = worldData::WOTData::worldTransformComponents[objectNum].qOrientation.y();
        worldData::WOTData::worldTransformComponents[objectNum].orientation.z = worldData::WOTData::worldTransformComponents[objectNum].qOrientation.z();
        worldData::WOTData::worldTransformComponents[objectNum].orientation.w = worldData::WOTData::worldTransformComponents[objectNum].qOrientation.w();
                
        //Test to see if we have a physics component
        if((worldData::WOTData::worldObjects[objectNum].gameObjectID & 32) == 32){
            
            worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[objectNum].componentLocations[2]].rigidBody->clearForces();
                    
            btVector3 point;
                    
            point = worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[objectNum].componentLocations[2]].rigidBody->getCenterOfMassPosition();
            
            worldData::WOTData::worldTransformComponents[objectNum].qOrientation = worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[objectNum].componentLocations[2]].rigidBody->getOrientation();
                    
                
            worldData::WOTData::worldTransformComponents[objectNum].trans.setOrigin(point);
            worldData::WOTData::worldTransformComponents[objectNum].trans.setRotation(worldData::WOTData::worldTransformComponents[objectNum].qOrientation);
                    
            //Copy over to allow us to use with glm
            worldData::WOTData::worldTransformComponents[objectNum].positon.x = worldData::WOTData::worldTransformComponents[objectNum].trans.getOrigin().getX();
            worldData::WOTData::worldTransformComponents[objectNum].positon.y = worldData::WOTData::worldTransformComponents[objectNum].trans.getOrigin().getY();
            worldData::WOTData::worldTransformComponents[objectNum].positon.z = worldData::WOTData::worldTransformComponents[objectNum].trans.getOrigin().getZ();
                    
            worldData::WOTData::worldTransformComponents[objectNum].orientation.x = worldData::WOTData::worldTransformComponents[objectNum].trans.getRotation().getX();
            worldData::WOTData::worldTransformComponents[objectNum].orientation.y = worldData::WOTData::worldTransformComponents[objectNum].trans.getRotation().getY();
            worldData::WOTData::worldTransformComponents[objectNum].orientation.z = worldData::WOTData::worldTransformComponents[objectNum].trans.getRotation().getZ();
            worldData::WOTData::worldTransformComponents[objectNum].orientation.w = worldData::WOTData::worldTransformComponents[objectNum].trans.getRotation().getW();
            
        }
                
                
        //Cast orienation to the matrix for use and get our locals
        worldData::WOTData::worldTransformComponents[objectNum].localRotate = glm::mat4_cast(worldData::WOTData::worldTransformComponents[objectNum].orientation);
                
        worldData::WOTData::worldTransformComponents[objectNum].localScale = glm::scale(glm::mat4(1.0f), glm::vec3(worldData::WOTData::worldTransformComponents[objectNum].scale.x,
                                                                                                                   worldData::WOTData::worldTransformComponents[objectNum].scale.y,
                                                                                                                   worldData::WOTData::worldTransformComponents[objectNum].scale.z));
                
        worldData::WOTData::worldTransformComponents[objectNum].localTranslate = glm::translate(glm::mat4(1.0f),
                                                                                                glm::vec3(worldData::WOTData::worldTransformComponents[objectNum].positon.x,
                                                                                                          worldData::WOTData::worldTransformComponents[objectNum].positon.y,
                                                                                                          worldData::WOTData::worldTransformComponents[objectNum].positon.z));        
        //make sure we have a parent object
        if(worldData::WOTData::worldObjects[objectNum].parentGameObjectID != -1){
            
            //Transform the child against the parent
            worldData::WOTData::worldTransformComponents[objectNum].worldTranslate = worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[objectNum].parentGameObjectID].worldTranslate * worldData::WOTData::worldTransformComponents[objectNum].localTranslate;
            
            worldData::WOTData::worldTransformComponents[objectNum].worldRotate = worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[objectNum].parentGameObjectID].worldRotate * worldData::WOTData::worldTransformComponents[objectNum].localRotate;
            
            worldData::WOTData::worldTransformComponents[objectNum].worldScale = worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[objectNum].parentGameObjectID].worldScale * worldData::WOTData::worldTransformComponents[objectNum].localScale;
        }else {
            //We don't have a parent object, we transform them without their transforms
            worldData::WOTData::worldTransformComponents[objectNum].worldTranslate  =   worldData::WOTData::worldTransformComponents[objectNum].localTranslate;
            worldData::WOTData::worldTransformComponents[objectNum].worldRotate     =   worldData::WOTData::worldTransformComponents[objectNum].localRotate;
            worldData::WOTData::worldTransformComponents[objectNum].worldScale      =   worldData::WOTData::worldTransformComponents[objectNum].localScale;
        }
        
        //Combine the matrices together
        worldData::WOTData::worldTransformComponents[objectNum].model = worldData::WOTData::worldTransformComponents[objectNum].worldTranslate *worldData::WOTData::worldTransformComponents[objectNum].worldRotate * worldData::WOTData::worldTransformComponents[objectNum].worldScale;

        
        
        //Make sure this object has children
        if(!worldData::WOTData::worldObjects[objectNum].childGameObjectIDs.empty()){
            //Now loop through all of the children
            for(int j = 0; j < worldData::WOTData::worldObjects[objectNum].childGameObjectIDs.size(); ++j){
                //Now check for children and update
                updateSceneGraph(worldData::WOTData::worldObjects[objectNum].childGameObjectIDs[j]);
            }
        }
    }
}


void entityProcessing::updateCameraComponents(){
	for(int i = 0; i < worldData::WOTData::worldObjects.size(); ++i){
		if((worldData::WOTData::worldObjects[i].gameObjectID & 16) == 16)
		{
            worldData::eData::projection = entityManager::gameObjects::cameraComponent::GOUpdateProjection(&worldData::WOTData::worldObjects[i]);
			worldData::eData::view	   = entityManager::gameObjects::cameraComponent::GOUpdateView(&worldData::WOTData::worldObjects[i]);
		}
	}
}

void entityProcessing::runCoreUpdate()
{
    
    //worldData::WOTData::worldNotificationHandler->YKNProcessPostContracts();

    for(int i = 0; i < worldData::WOTData::worldObjects.size(); ++i){
        if(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].isDirty == true)
            updateSceneGraph(i);
        
        worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].isDirty = true;
    }
    
	updateCameraComponents();


}

void entityProcessing::runCoreDraw(GLSLShader *shader3D, GLSLShader *shader2D)
{
    worldData::pData::worldDebugDraw->SetMatrices(worldData::eData::view, worldData::eData::projection);
    worldData::pData::dynamicsWorld->debugDrawWorld();
	drawAllObjects(shader3D, shader2D);
}

void entityProcessing::initLive3DObjects()
{
    
}
void entityProcessing::initLive2DObjects()
{
    
}

void entityProcessing::initPhysicsComponents()
{
    
    //Set up world physics data

    // Set up the collision configuration and dispatcher
    worldData::pData::collisionConfiguration = new btDefaultCollisionConfiguration();
    worldData::pData::dispatcher = new btCollisionDispatcher(worldData::pData::collisionConfiguration);
    
    // Build the broadphase
    worldData::pData::broadphase = new btDbvtBroadphase();
    
    // The actual physics solver
    worldData::pData::solver = new btSequentialImpulseConstraintSolver();
    
    // The world.
    worldData::pData::dynamicsWorld = new btDiscreteDynamicsWorld(worldData::pData::dispatcher,
                                                                  worldData::pData::broadphase,
                                                                  worldData::pData::solver,
                                                                  worldData::pData::collisionConfiguration);
    worldData::pData::dynamicsWorld->setGravity(btVector3(0,-9.81f,0));
    
    worldData::pData::dynamicsWorld->setDebugDrawer(worldData::pData::worldDebugDraw);
    
    //Now set p physics data for each object
    for(int i =0; i < worldData::WOTData::worldObjects.size();++i){
        if((worldData::WOTData::worldObjects[i].gameObjectID & 32) == 32){
            
            worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].trans.setOrigin(btVector3(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].positon.x, worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].positon.y, worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].positon.z));
            
            worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].motionState = new btDefaultMotionState(worldData::WOTData::worldTransformComponents[worldData::WOTData::worldObjects[i].componentLocations[0]].trans);
            
            if(worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].mass != 0.0f){
                
                worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].boxCollisionShape->calculateLocalInertia(worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].mass, worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].localInteria);
            }
            

            
            btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].mass,//Mass in Kg 0 = static object
                                                                 worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].motionState,
                                                                 worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].boxCollisionShape,
                                                                 worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].localInteria);//Local intertia
            
            worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].rigidBody = new btRigidBody(rigidBodyCI);
            
            worldData::WOTData::worldRigidbodies.push_back(worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].rigidBody);
            
            worldData::pData::dynamicsWorld->addRigidBody(worldData::WOTData::worldPhysicsComponents[worldData::WOTData::worldObjects[i].componentLocations[2]].rigidBody);

        }
    }
}
void entityProcessing::updatePhysicsComponents(float delta){
    
    
        worldData::pData::dynamicsWorld->stepSimulation(delta);
        /*for(int j = worldData::pData::dynamicsWorld->getNumCollisionObjects()-1;j>=0;j--){
            btCollisionObject* obj = worldData::pData::dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody* body = btRigidBody::upcast(obj);
            if(body && body->getMotionState()){
                btTransform trans;
                body->getMotionState()->getWorldTransform(trans);
    
            }
        }*/
}


void entityProcessing::updateMeshComponents(){
    
}
void entityProcessing::initCameraComponents(){
    
}