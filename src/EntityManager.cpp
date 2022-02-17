#include "EntityManager.h"

std::vector<entitySystem::gameObject> worldData::WOTData::worldObjects;
std::vector<entitySystem::transformComponent> worldData::WOTData::worldTransformComponents;
std::vector<entitySystem::meshComponent> worldData::WOTData::worldMeshComponents;
std::vector<entitySystem::cameraComponent> worldData::WOTData::worldCameraComponents;
std::vector<entitySystem::physicsComponent> worldData::WOTData::worldPhysicsComponents;
std::vector<entitySystem::lightComponent> worldData::WOTData::worldLightComponents;
std::vector<btRigidBody*> worldData::WOTData::worldRigidbodies;

//YKNotificationHandler* worldData::WOTData::worldNotificationHandler = new YKNotificationHandler();

int worldData::eData::tCounter;
int worldData::eData::mCounter;
int worldData::eData::pCounter;
int worldData::eData::cCounter;
int worldData::eData::lCounter;

int worldData::eData::wCounter;

GLSLShader *worldData::eData::shaderLoader = new GLSLShader();
glm::mat4 worldData::eData::view;
glm::mat4 worldData::eData::projection;

btBroadphaseInterface* worldData::pData::broadphase;
btDefaultCollisionConfiguration* worldData::pData::collisionConfiguration;
btCollisionDispatcher* worldData::pData::dispatcher;
btSequentialImpulseConstraintSolver* worldData::pData::solver;
btDiscreteDynamicsWorld* worldData::pData::dynamicsWorld;
YKDebugDraw* worldData::pData::worldDebugDraw = new YKDebugDraw();

void entityManager::createGameObjectByTag(int tag)
{
	entitySystem::gameObject GO;
	GO.tag = tag;//tag that we can identify this game object by
    GO.worldPosition = worldData::eData::wCounter;//Position of the object in the game object vector
    worldData::eData::wCounter++;
	worldData::WOTData::worldObjects.push_back(GO);
  
}

void entityManager::createGameObjectByName(std::string name)
{
	entitySystem::gameObject GO;
	GO.name = name;
    GO.worldPosition = worldData::eData::wCounter;
    worldData::eData::wCounter++;
	worldData::WOTData::worldObjects.push_back(GO);
   
}

entitySystem::gameObject* entityManager::getGameObjectByTag(int tag)
{
	for(int i = 0; i < worldData::WOTData::worldObjects.size(); ++i){
		if(worldData::WOTData::worldObjects[i].tag == tag){
			return &worldData::WOTData::worldObjects[i];
		}
	}
    
    return NULL;
}
//entitySystem::gameObject* entityManager::getGameObjectByName(std::string name)
//{
//	/*for(int i = 0; i < worldData::WOTData::worldObjects.size(); ++i){
//		if(worldData::WOTData::worldObjects[i].name == name){
//			return &worldData::WOTData::worldObjects[i];
//		}
//	}*/
//}


int entityManager::getGameObjectWorldPosition(entitySystem::gameObject* GO)
{
    return GO->worldPosition;
}

void entityManager::setGameObjectParentWorldPosition(int childWorldPos, int parentWorldPos)
{
    worldData::WOTData::worldObjects[childWorldPos].parentGameObjectID = parentWorldPos;
}

void entityManager::addTransformComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		std::cout<<"Game Object already contains transform component!"<<std::endl;
	}else {
		entitySystem::transformComponent TC;					 //Create the new component
		GO->gameObjectID = (GO->gameObjectID + 0x80);			//Set flags in GO ID so we recognise the component has been added
		TC.gameObjectForeignKey = GO->gameObjectForeignKey;		 //Associate the id of the GO with the component
		worldData::WOTData::worldTransformComponents.push_back(TC); //Add it to the appropriate world components
		GO->componentLocations[0] = worldData::eData::tCounter;				  //Access the location of the component in the world vector
		worldData::eData::tCounter++;
	}
}
void entityManager::addMeshComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 64) == 64){
		std::cout<<"Game Object already contains mesh component!"<<std::endl;
	}else {
		entitySystem::meshComponent MC;
		worldData::WOTData::worldMeshComponents.push_back(MC);
		GO->gameObjectID = (GO->gameObjectID + 0x40);
		MC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[1] = worldData::eData::mCounter;
		worldData::eData::mCounter++;
	}
}
void entityManager::addPhysicsComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 32) == 32){
		std::cout<<"Game Object already contains physics component!"<<std::endl;
	}else{
		entitySystem::physicsComponent PC;
		worldData::WOTData::worldPhysicsComponents.push_back(PC);
		GO->gameObjectID = (GO->gameObjectID + 0x20);
		PC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[2] = worldData::eData::pCounter;
		worldData::eData::pCounter++;
	}
}
void entityManager::addCameraComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		std::cout<<"Game Object already contains camera component!"<<std::endl;
	}else {
		entitySystem::cameraComponent CC;
		worldData::WOTData::worldCameraComponents.push_back(CC);
		GO->gameObjectID = (GO->gameObjectID + 0x10);
		CC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[3] = worldData::eData::cCounter;
		worldData::eData::cCounter++;
	}
}

void entityManager::addLightComponent(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
		std::cout<<"Game Object already contains light component!"<<std::endl;
	}else {
        entitySystem::lightComponent LC;
		worldData::WOTData::worldLightComponents.push_back(LC);
		GO->gameObjectID = (GO->gameObjectID + 0x8);
		LC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[4] = worldData::eData::lCounter;
		worldData::eData::lCounter++;
	}
}

void entityManager::removeTransformComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removePhysicsComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removeCameraComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removeMeshComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removeLightComponent(entitySystem::gameObject* GO)
{
}
void entityManager::addChildToGameObject(int parent, int child)
{
    worldData::WOTData::worldObjects[parent].childGameObjectIDs.push_back(child);
}
void entityManager::removeChildFromGameObject(entitySystem::gameObject* parent, entitySystem::gameObject* child)
{
}

void entityManager::gameObjects::transformComponent::GOOffsetVec(entitySystem::gameObject* GO, glm::vec3 &offset)
{
	if((GO->gameObjectID & 128) == 128){ //The gameObject has the transform component
        glm::vec3 tempTran;
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon*=offset;
	}
}
void entityManager::gameObjects::transformComponent::GOOffsetXYZ(entitySystem::gameObject* GO,float x, float y, float z)
{
	if((GO->gameObjectID & 128) == 128){
        worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.x += x;
        worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.y += y;
        worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.z += z;
        
    }
}
void entityManager::gameObjects::transformComponent::GOOffsetX(entitySystem::gameObject* GO,float x)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.x += x;
	}
}
void entityManager::gameObjects::transformComponent::GOOffsetY(entitySystem::gameObject* GO,float y)
{
	if((GO->gameObjectID & 128) == 128){ 
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.y += y;
	}
}
void entityManager::gameObjects::transformComponent::GOOffsetZ(entitySystem::gameObject* GO,float z)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.z += z;
	}
}

void entityManager::gameObjects::transformComponent::GOTranslateVec(entitySystem::gameObject* GO, glm::vec3 &pos)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon = pos;
	}
}
void entityManager::gameObjects::transformComponent::GOTranslateXYZ(entitySystem::gameObject* GO, float x, float y, float z)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.x = x;
        worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.y = y;
        worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.z = z;
	}
}
void entityManager::gameObjects::transformComponent::GOTranslateX(entitySystem::gameObject* GO,float x)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.x = x;;
	}
}
void entityManager::gameObjects::transformComponent::GOTranslateY(entitySystem::gameObject* GO,float y)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.y = y;
	}
}
void entityManager::gameObjects::transformComponent::GOTranslateZ(entitySystem::gameObject* GO,float z)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.z = z;
	}
}

glm::vec3 entityManager::gameObjects::transformComponent::GOGetPosVec(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon;
	}
    
    return glm::vec3(-101,-101,-101);
}
float entityManager::gameObjects::transformComponent::GOGetPosX(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.x;
	}
    return 0;
}
float entityManager::gameObjects::transformComponent::GOGetPosY(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.y;
	}
    return 0;
}
float entityManager::gameObjects::transformComponent::GOGetPosZ(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon.z;
	}
    return 0;
}

void entityManager::gameObjects::transformComponent::GORotateX(entitySystem::gameObject* GO,float amount)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotX = amount;
	}
}
void entityManager::gameObjects::transformComponent::GORotateY(entitySystem::gameObject* GO,float amount)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotY = amount;
	}
}
void entityManager::gameObjects::transformComponent::GORotateZ(entitySystem::gameObject* GO,float amount)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotZ = amount;
	}
}

float entityManager::gameObjects::transformComponent::GOGetRotX(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotX;
	}
    return 0;
}
float entityManager::gameObjects::transformComponent::GOGetRotY(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotY;
	}
    return 0;
}
float entityManager::gameObjects::transformComponent::GOGetRotZ(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotZ;
	}
    return 0;
}

void entityManager::gameObjects::transformComponent::GOScaleVec(entitySystem::gameObject* GO, glm::vec3 &scale)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale = scale;
	}
}
void entityManager::gameObjects::transformComponent::GOScaleXYZ(entitySystem::gameObject* GO, float x, float y, float z)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.x = x;
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.y = y;
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.z = z;
	}
}
void entityManager::gameObjects::transformComponent::GOScaleX(entitySystem::gameObject* GO,float x)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.x = x;
	}
}
void entityManager::gameObjects::transformComponent::GOScaleY(entitySystem::gameObject* GO,float y)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.y = y;
	}
}
void entityManager::gameObjects::transformComponent::GOScaleZ(entitySystem::gameObject* GO,float z)
{
	if((GO->gameObjectID & 128) == 128){
		worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.z = z;
	}
}

glm::vec3 entityManager::gameObjects::transformComponent::GOGetScaleVec(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale;
	}
    return glm::vec3(-100,-100,-100);
}
float entityManager::gameObjects::transformComponent::GOGetScaleX(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.x;
	}
    return 0;
}
float entityManager::gameObjects::transformComponent::GOGetScaleY(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.y;
	}
    return 0;
}
float entityManager::gameObjects::transformComponent::GoGetScaleZ(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 128) == 128){
		return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].scale.z;
	}
    return 0;
}

void entityManager::gameObjects::meshComponent::GOSetDiffuseName(entitySystem::gameObject* GO, std::string fileName)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].diffuseName = fileName;
	}
}
std::string entityManager::gameObjects::meshComponent::GOGetTextureName(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 64) == 64){
		return worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].diffuseName;
	}
    
    return "err";
}

void entityManager::gameObjects::meshComponent::GOSetBlue(entitySystem::gameObject* GO, float blue)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].BLUE = blue;
	}
}
void entityManager::gameObjects::meshComponent::GOSetRed(entitySystem::gameObject* GO, float red)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].RED = red;
	}
}
void entityManager::gameObjects::meshComponent::GOSetGreen(entitySystem::gameObject* GO, float green)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].GREEN = green;
	}
}
void entityManager::gameObjects::meshComponent::GOSetAlpha(entitySystem::gameObject* GO, float alpha)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].ALPHA = alpha;
	}
}
    
void entityManager::gameObjects::meshComponent::GOVisible(entitySystem::gameObject* GO, bool isVisible)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].ALPHA = 1.0f;
	}
}
void entityManager::gameObjects::meshComponent::GOInvisible(entitySystem::gameObject* GO, bool isInvisible)
{
	if((GO->gameObjectID & 64) == 64){
		worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].ALPHA = 0.0f;
	}
}

float entityManager::gameObjects::meshComponent::GOGetRed(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 64) == 64){
		return worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].RED;
	}
    return 0;
}
float entityManager::gameObjects::meshComponent::GOGetGreen(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 64) == 64){
		return worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].GREEN;
	}
    return 0;
}
float entityManager::gameObjects::meshComponent::GOGetBlue(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 64) == 64){
		return worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].BLUE;
	}
    return 0;
}
float entityManager::gameObjects::meshComponent::GOGetAlpha(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 64) == 64){
		return worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].ALPHA;
	}
    return 0;
}

void entityManager::gameObjects::meshComponent::GOLoadDiffiuse(entitySystem::gameObject* GO, std::string diffuseName)
{
	if((GO->gameObjectID & 64) == 64){
		 Bitmap bmp = Bitmap::bitmapFromFile(diffuseName);
		 bmp.flipVertically();
		 worldData::WOTData::worldMeshComponents[GO->componentLocations[1]].pTexture = new Texture(bmp);
	}
}

bool entityManager::gameObjects::meshComponent::GOLoadMesh(entitySystem::gameObject* GO, std::string meshName)
{
    bool ret = false;
    
    if((GO->gameObjectID & 64) == 64){
        
        
        return ret;
    }
    
    return ret;
}


void entityManager::gameObjects::cameraComponent::GOPitchCamera(entitySystem::gameObject* GO, float angle)
{
	if((GO->gameObjectID & 16) == 16){
        if((GO->gameObjectID & 128) == 128){
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotX = angle;
        }
	}
}
void entityManager::gameObjects::cameraComponent::GORollCamera(entitySystem::gameObject* GO, float angle)
{
	if((GO->gameObjectID & 16) == 16){
		if((GO->gameObjectID & 128) == 128){
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotZ = angle;
        }
	}
}
void entityManager::gameObjects::cameraComponent::GOYawCamera(entitySystem::gameObject* GO, float angle)
{
	if((GO->gameObjectID & 16) == 16){
        if((GO->gameObjectID & 128) == 128){
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotY = angle;
        }
	}
}
void entityManager::gameObjects::cameraComponent::GOSetCamPitchYawRoll(entitySystem::gameObject* GO, float pitch,float yaw,float roll)
{
	if((GO->gameObjectID & 16) == 16){
        if((GO->gameObjectID & 128) == 128){
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotX = pitch;
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotY = yaw;
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotZ = roll;
        }
	}
}
void entityManager::gameObjects::cameraComponent::GOOffSetCamPitchRoll(entitySystem::gameObject* GO, float pitch, float yaw, float roll)
{
	if((GO->gameObjectID & 16) == 16){
        if((GO->gameObjectID & 128) == 128){
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotX += pitch;
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotY += yaw;
            worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotZ += roll;
        }
	}
}

float entityManager::gameObjects::cameraComponent::GOGetCameraPitch(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].pitch;
	}
    return 0;
}
float entityManager::gameObjects::cameraComponent::GOGetCameraRoll(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].roll;
	}
    return 0;
}
float entityManager::gameObjects::cameraComponent::GOGetCameraYaw(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].yaw;
	}
    return 0;
}

    
float entityManager::gameObjects::cameraComponent::GOGetCamNearPlane(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].nearPlane;
	}
    return 0;
}
float entityManager::gameObjects::cameraComponent::GOGetCamFarPlane(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].farPlane;
	}
    return 0;
}

glm::mat4 entityManager::gameObjects::cameraComponent::GOMatrix(entitySystem::gameObject *GO)
{
    if((GO->gameObjectID & 16) == 16){
        glm::mat4 camera =  glm::perspective(45.0f, worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].aspectRatio,
                         worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].nearPlane,
                         worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].farPlane);
        camera *= GOCamOrientation(GO);
        camera = glm::translate(camera, -worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon);
        return camera;
    }
    glm::mat4 fail;
    return fail;
}
    
glm::mat4 entityManager::gameObjects::cameraComponent::GOCamOrientation(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
         if((GO->gameObjectID & 128) == 128){
             glm::mat4 orientation;
             
             orientation = glm::rotate(orientation, worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotX, glm::vec3(1,0,0));
             orientation = glm::rotate(orientation, worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotY,   glm::vec3(0,1,0));
             orientation = glm::rotate(orientation, worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].rotZ,  glm::vec3(0,0,1));
             return orientation;
         }
	}
    //Output an error here
    return glm::mat4(1.0f);//if we get to this control point, there was an error
}
glm::vec3 entityManager::gameObjects::cameraComponent::GOGetForward(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		glm::vec4 forward = glm::inverse(GOCamOrientation(GO))  * glm::vec4(0,0,-1,1);
		return glm::vec3(forward);
	}
    return glm::vec3(0,0,0);
}
glm::vec3 entityManager::gameObjects::cameraComponent::GOGetUp(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		glm::vec4 up = glm::inverse(GOCamOrientation(GO))  * glm::vec4(0,1,0,1);
		return glm::vec3(up);
	}
    return glm::vec3(0,0,0);
}
glm::vec3 entityManager::gameObjects::cameraComponent::GOGetRight(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		glm::vec4 right = glm::inverse(GOCamOrientation(GO)) * glm::vec4(1,0,0,1);
		return glm::vec3(right);
	}
    return glm::vec3(0,0,0);
}
    
void entityManager::gameObjects::cameraComponent::GOSetAspectRatio(entitySystem::gameObject* GO, float amount)
{
	if((GO->gameObjectID & 16) == 16){
		worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].aspectRatio = amount;
	}
}
float entityManager::gameObjects::cameraComponent::GOGetAspectRatio(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].aspectRatio;
	}
    return 0;
}

glm::mat4 entityManager::gameObjects::cameraComponent::GOUpdateProjection(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
		return glm::perspective(45.0f, worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].aspectRatio, 
							worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].nearPlane, 
							worldData::WOTData::worldCameraComponents[GO->componentLocations[3]].farPlane);
	}
    glm::mat4 fail;
    return fail;
}

glm::mat4 entityManager::gameObjects::cameraComponent::GOUpdateView(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & 16) == 16){
        if((GO->gameObjectID & 128) == 128){
            return GOCamOrientation(GO) * glm::translate(glm::mat4(), -worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon);
        }
	}
    glm::mat4 fail;
    return fail;
}

void entityManager::gameObjects::physicsComponent::GOSetObjectMass(entitySystem::gameObject* GO,float mass)
{
    if((GO->gameObjectID & 32) == 32){
        worldData::WOTData::worldPhysicsComponents[GO->componentLocations[2]].mass = mass;
    }
}
float entityManager::gameObjects::physicsComponent::GOGetObjectMass(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 32) == 32){
        return worldData::WOTData::worldPhysicsComponents[GO->componentLocations[2]].mass;
    }else{
        return 0;
    }
    
}

void entityManager::gameObjects::physicsComponent::GOSetCollisionShapeScale(entitySystem::gameObject* GO, float x, float y, float z)
{
    if((GO->gameObjectID & 32) == 32){
        worldData::WOTData::worldPhysicsComponents[GO->componentLocations[2]].boxCollisionShape->setLocalScaling(btVector3(x,y,z));
    }
}


void entityManager::gameObjects::lightComponent::GOSetLightColourVec(entitySystem::gameObject* GO, glm::vec4 &col)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour = col;
    }
}
void entityManager::gameObjects::lightComponent::GOSetLightColourRGBA(entitySystem::gameObject* GO, float r, float g, float b, float a)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.x = r;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.y = g;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.z = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.w = a;
    }
}



void entityManager::gameObjects::lightComponent::GOSetLightColourR(entitySystem::gameObject* GO, float r)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.x = r;
    }
}
void entityManager::gameObjects::lightComponent::GOSetLightColourG(entitySystem::gameObject* GO, float g)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.y = g;
    }
}
void entityManager::gameObjects::lightComponent::GOSetLightColourB(entitySystem::gameObject* GO, float b)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.z = b;
    }
}
void entityManager::gameObjects::lightComponent::GOSetLightColourA(entitySystem::gameObject* GO, float a)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.w = a;
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightShininess(entitySystem::gameObject *GO, float shininess)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].shininess = shininess;
    }
}

float entityManager::gameObjects::lightComponent::GOGetLightColourR(entitySystem::gameObject* GO)
{
    return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.x;
}
float entityManager::gameObjects::lightComponent::GOGetLightColourG(entitySystem::gameObject* GO)
{
    return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.y;
}
float entityManager::gameObjects::lightComponent::GOGetLightColourB(entitySystem::gameObject* GO)
{
    return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.z;
}

float entityManager::gameObjects::lightComponent::GOGetLightColourA(entitySystem::gameObject* GO)
{
    return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].colour.w;
}

void entityManager::gameObjects::lightComponent::GOSetLightRadius(entitySystem::gameObject* GO, float rad)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].radius = rad;
    }
}
float entityManager::gameObjects::lightComponent::GOGetLightRadius(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].radius;
    }
    return -100.0f;
}
glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightKa(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka;
    }else{
        return glm::vec3(0,0,0);
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightKd(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd;
    }else{
        return glm::vec3(0,0,0);
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightKs(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks;
    }else{
        return glm::vec3(0,0,0);
    }
}

glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightLa(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La;
    }else{
        return glm::vec3(0,0,0);
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightLd(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld;
    }else{
        return glm::vec3(0,0,0);
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightLs(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls;
    }else{
        return glm::vec3(0,0,0);
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightKa(entitySystem::gameObject* GO, float a, float b, float c)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka.x = a;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka.y = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka.z = c;
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightKd(entitySystem::gameObject* GO, float a, float b, float c)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd.x = a;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd.y = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd.z = c;
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightKs(entitySystem::gameObject* GO, float a, float b, float c)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks.x = a;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks.y = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks.z = c;
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightLa(entitySystem::gameObject* GO, float a , float b, float c)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La.x = a;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La.y = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La.z = c;
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightLd(entitySystem::gameObject* GO, float a , float b, float c)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld.x = a;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld.y = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld.z = c;
    }
}

void entityManager::gameObjects::lightComponent::GOSetLightLs(entitySystem::gameObject* GO, float a , float b, float c)
{
    if((GO->gameObjectID & 8) == 8){
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls.x = a;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls.y = b;
        worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls.z = c;
    }
}


float entityManager::gameObjects::lightComponent::GOGetLightKaA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka.x;
    } else {
        return 0;
    }
}
float entityManager::gameObjects::lightComponent::GOGetLightKdA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd.x;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightKsA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks.x;
    }else {
        return 0;
    }

}

float entityManager::gameObjects::lightComponent::GOGetLightKaB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka.y;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightKdB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd.y;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightKsB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks.y;
    }else {
        return 0;
    }

}

float entityManager::gameObjects::lightComponent::GOGetLightKaC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ka.z;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightKdC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Kd.z;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightKsC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ks.z;
    }else {
        return 0;
    }

}

float entityManager::gameObjects::lightComponent::GOGetLightLaA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La.x;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightLdA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld.x;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightLsA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls.x;
    }else {
        return 0;
    }

}

float entityManager::gameObjects::lightComponent::GOGetLightLaB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La.y;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightLdB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld.y;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightLsB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls.y;
    }else {
        return 0;
    }

}

float entityManager::gameObjects::lightComponent::GOGetLightLaC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].La.z;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightLdC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ld.z;
    }else {
        return 0;
    }

}
float entityManager::gameObjects::lightComponent::GOGetLightLsC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].Ls.z;
    }else {
        return 0;
    }

}

float entityManager::gameObjects::lightComponent::GoGetLightShininess(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        return worldData::WOTData::worldLightComponents[GO->componentLocations[4]].shininess;
    }else {
        return 0;
    }

}

glm::vec3 entityManager::gameObjects::lightComponent::GOGetLightPosition(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & 8) == 8){
        if((GO->gameObjectID & 128) == 128){
            return worldData::WOTData::worldTransformComponents[GO->componentLocations[0]].positon;
        }
    }
    return glm::vec3(0,0,0);
    
}

