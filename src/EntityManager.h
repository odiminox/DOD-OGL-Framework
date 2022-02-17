#pragma once

#include "worldData.h"
#include <iostream>

//There is exists only one instance of each function to manipulate gameObject data
//as gameObjects only contain the pure data themselves, they do not have to be
//weighed down by multiple instances of the same function



namespace entityManager
{
    //Also need to create an object that is not automatically added to the world object list.
    
	void createGameObjectByTag(int tag);
	void createGameObjectByName(std::string name);
    

	entitySystem::gameObject* getGameObjectByTag(int tag);
	//entitySystem::gameObject* getGameObjectByName(std::string name);

	void addTransformComponent(entitySystem::gameObject* GO);
	void addMeshComponent(entitySystem::gameObject* GO);
	void addPhysicsComponent(entitySystem::gameObject* GO);
	void addCameraComponent(entitySystem::gameObject* GO);
    void addLightComponent(entitySystem::gameObject* GO);

	void removeTransformComponent(entitySystem::gameObject* GO);
	void removePhysicsComponent(entitySystem::gameObject* GO);
	void removeCameraComponent(entitySystem::gameObject* GO);
	void removeMeshComponent(entitySystem::gameObject* GO);
    void removeLightComponent(entitySystem::gameObject* GO);

	void addChildToGameObject(int parent, int child);
	void removeChildFromGameObject(entitySystem::gameObject* parent, entitySystem::gameObject* child);
    
    int getGameObjectWorldPosition(entitySystem::gameObject* GO);
    void setGameObjectParentWorldPosition(int childWorldPos, int parentWorldPos);
    
    namespace editorObjects
    {
        namespace buttonComponent
        {
            
        }
    }

	namespace gameObjects
	{
		namespace transformComponent
		{
			void GOOffsetVec(entitySystem::gameObject* GO, glm::vec3 &offset);
			void GOOffsetXYZ(entitySystem::gameObject* GO,float x, float y, float z);
			void GOOffsetX(entitySystem::gameObject* GO,float x);
			void GOOffsetY(entitySystem::gameObject* GO,float y);
			void GOOffsetZ(entitySystem::gameObject* GO,float z);

			void GOTranslateVec(entitySystem::gameObject* GO, glm::vec3 &pos);
			void GOTranslateXYZ(entitySystem::gameObject* GO, float x, float y, float z);
			void GOTranslateX(entitySystem::gameObject* GO,float x);
			void GOTranslateY(entitySystem::gameObject* GO,float y);
			void GOTranslateZ(entitySystem::gameObject* GO,float z);

			glm::vec3 GOGetPosVec(entitySystem::gameObject* GO);
			float GOGetPosX(entitySystem::gameObject* GO);
			float GOGetPosY(entitySystem::gameObject* GO);
			float GOGetPosZ(entitySystem::gameObject* GO);

			void GORotateX(entitySystem::gameObject* GO,float amount);
			void GORotateY(entitySystem::gameObject* GO,float amount);
			void GORotateZ(entitySystem::gameObject* GO,float amount);
            
			float GOGetRotX(entitySystem::gameObject* GO);
			float GOGetRotY(entitySystem::gameObject* GO);
			float GOGetRotZ(entitySystem::gameObject* GO);

			void GOScaleVec(entitySystem::gameObject* GO, glm::vec3 &scale);
			void GOScaleXYZ(entitySystem::gameObject* GO, float x, float y, float z);
			void GOScaleX(entitySystem::gameObject* GO,float x);
			void GOScaleY(entitySystem::gameObject* GO,float y);
			void GOScaleZ(entitySystem::gameObject* GO,float z);

			glm::vec3 GOGetScaleVec(entitySystem::gameObject* GO);
			float GOGetScaleX(entitySystem::gameObject* GO);
			float GOGetScaleY(entitySystem::gameObject* GO);
			float GoGetScaleZ(entitySystem::gameObject* GO);

			void GOSetMV();
		}
		
		namespace meshComponent
		{
			void GOSetDiffuseName(entitySystem::gameObject* GO, std::string fileName);
			std::string GOGetTextureName(entitySystem::gameObject* GO);

			void GOSetBlue(entitySystem::gameObject* GO, float blue);
			void GOSetRed(entitySystem::gameObject* GO, float red);
			void GOSetGreen(entitySystem::gameObject* GO, float green);
			void GOSetAlpha(entitySystem::gameObject* GO, float alpha);
    
			void GOVisible(entitySystem::gameObject* GO, bool isVisible);
			void GOInvisible(entitySystem::gameObject* GO, bool isInvisible);

			float GOGetRed(entitySystem::gameObject* GO);
			float GOGetGreen(entitySystem::gameObject* GO);
			float GOGetBlue(entitySystem::gameObject* GO);
			float GOGetAlpha(entitySystem::gameObject* GO);
            
            bool GOLoadMesh(entitySystem::gameObject* GO, std::string meshName);

			void GOLoadDiffiuse(entitySystem::gameObject* GO, std::string diffuseName);
		}

		namespace cameraComponent
		{
			void GOPitchCamera(entitySystem::gameObject* GO, float angle);
			void GORollCamera(entitySystem::gameObject* GO, float angle);
			void GOYawCamera(entitySystem::gameObject* GO, float angle);
			void GOSetCamPitchYawRoll(entitySystem::gameObject* GO, float pitch,float yaw,float roll);
			void GOOffSetCamPitchRoll(entitySystem::gameObject* GO, float pitch, float yaw, float roll);

			float GOGetCameraPitch(entitySystem::gameObject* GO);
			float GOGetCameraRoll(entitySystem::gameObject* GO);
			float GOGetCameraYaw(entitySystem::gameObject* GO);
    
			float GOGetCamNearPlane(entitySystem::gameObject* GO);
			float GOGetCamFarPlane(entitySystem::gameObject* GO);
    
			glm::mat4 GOCamOrientation(entitySystem::gameObject* GO);
			glm::vec3 GOGetForward(entitySystem::gameObject* GO);
			glm::vec3 GOGetUp(entitySystem::gameObject* GO);
			glm::vec3 GOGetRight(entitySystem::gameObject* GO);
    
			void GOSetAspectRatio(entitySystem::gameObject* GO, float amount);
			float GOGetAspectRatio(entitySystem::gameObject* GO);

			glm::mat4 GOUpdateProjection(entitySystem::gameObject* GO);
			glm::mat4 GOUpdateView(entitySystem::gameObject* GO);
            
            glm::mat4 GOMatrix(entitySystem::gameObject* GO);
        
		}

		namespace physicsComponent
		{
            void GOSetObjectMass(entitySystem::gameObject* GO, float mass);
            float GOGetObjectMass(entitySystem::gameObject* GO);
            void GOSetCollisionShapeScale(entitySystem::gameObject* GO, float x, float y, float z);
		}
        
        namespace lightComponent
        {
            void GOSetLightColourVec(entitySystem::gameObject* GO, glm::vec4 &col);
            void GOSetLightColourRGBA(entitySystem::gameObject* GO, float r, float g, float b, float a);
            void GOSetLightColourR(entitySystem::gameObject* GO, float r);
            void GOSetLightColourG(entitySystem::gameObject* GO, float g);
            void GOSetLightColourB(entitySystem::gameObject* GO, float b);
            void GOSetLightColourA(entitySystem::gameObject* GO, float a);
            
            void GOSetLightKa(entitySystem::gameObject* GO, float a, float b, float c);
            void GOSetLightKd(entitySystem::gameObject* GO, float a, float b, float c);
            void GOSetLightKs(entitySystem::gameObject* GO, float a, float b, float c);
            
            void GOSetLightLa(entitySystem::gameObject* GO, float a, float b, float c);
            void GOSetLightLd(entitySystem::gameObject* GO, float a , float b, float c);
            void GOSetLightLs(entitySystem::gameObject* GO, float a, float b, float c);
            
            void GOSetLightShininess(entitySystem::gameObject* GO, float shininess);
            
            glm::vec3 GOGetLightKa(entitySystem::gameObject* GO);
            glm::vec3 GOGetLightKd(entitySystem::gameObject* GO);
            glm::vec3 GOGetLightKs(entitySystem::gameObject* GO);
            
            glm::vec3 GOGetLightLa(entitySystem::gameObject* GO);
            glm::vec3 GOGetLightLd(entitySystem::gameObject* GO);
            glm::vec3 GOGetLightLs(entitySystem::gameObject* GO);
            
            float GoGetLightShininess(entitySystem::gameObject* GO);
            
            glm::vec3 GOGetLightPosition(entitySystem::gameObject* GO);
            
            float GOGetLightKaA(entitySystem::gameObject* GO);
            float GOGetLightKaB(entitySystem::gameObject* GO);
            float GOGetLightKaC(entitySystem::gameObject* GO);
            float GOGetLightKdA(entitySystem::gameObject* GO);
            float GOGetLightKdB(entitySystem::gameObject* GO);
            float GOGetLightKdC(entitySystem::gameObject* GO);
            float GOGetLightKsA(entitySystem::gameObject* GO);
            float GOGetLightKsB(entitySystem::gameObject* GO);
            float GOGetLightKsC(entitySystem::gameObject* GO);
            
            float GOGetLightLaA(entitySystem::gameObject* GO);
            float GOGetLightLaB(entitySystem::gameObject* GO);
            float GOGetLightLaC(entitySystem::gameObject* GO);
            float GOGetLightLdA(entitySystem::gameObject* GO);
            float GOGetLightLdB(entitySystem::gameObject* GO);
            float GOGetLightLdC(entitySystem::gameObject* GO);
            float GOGetLightLsA(entitySystem::gameObject* GO);
            float GOGetLightLsB(entitySystem::gameObject* GO);
            float GOGetLightLsC(entitySystem::gameObject* GO);
            
            
            float GOGetLightColourR(entitySystem::gameObject* GO);
            float GOGetLightColourG(entitySystem::gameObject* GO);
            float GOGetLightColourB(entitySystem::gameObject* GO);
            float GOGetLightColourA(entitySystem::gameObject* GO);

            void GOSetLightRadius(entitySystem::gameObject* GO, float rad);
            float GOGetLightRadius(entitySystem::gameObject* GO);
        }
		
	}
}