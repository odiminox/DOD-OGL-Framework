#pragma once
#include <vector>
#include "EntitySystem.h"
#include "GLSLShader.h"
#include "YKDebugDraw.h"
//#include "YKNotificationHandler.h"

namespace worldData
{
	struct WOTData
	{
		static std::vector<entitySystem::gameObject> worldObjects;//Contains all of the objects in the world that we want to process
		static std::vector<entitySystem::transformComponent> worldTransformComponents;
		static std::vector<entitySystem::meshComponent> worldMeshComponents;
		static std::vector<entitySystem::cameraComponent> worldCameraComponents;
		static std::vector<entitySystem::physicsComponent> worldPhysicsComponents;
        static std::vector<entitySystem::lightComponent> worldLightComponents;
        static std::vector<YKRigidBody*> worldRigidbodies;
        
        //static YKNotificationHandler* worldNotificationHandler;
	};

	struct eData
	{
		eData()
		{
			tCounter = 0;
			mCounter = 0;
			pCounter = 0;
			cCounter = 0;
            lCounter = 0;
		}
		static int tCounter;
		static int mCounter;
		static int pCounter;
		static int cCounter;
        static int lCounter;
        
        static int wCounter;

		static GLSLShader *shaderLoader;
		static YKMat4 view;
		static YKMat4 projection;
        
	};
    
    struct pData
    {
        pData()
        {
            
        }
        static btBroadphaseInterface* broadphase;
        static btDefaultCollisionConfiguration* collisionConfiguration;
        static btCollisionDispatcher* dispatcher;
        static btSequentialImpulseConstraintSolver* solver;
        static btDiscreteDynamicsWorld* dynamicsWorld;
        static YKDebugDraw* worldDebugDraw;
    };

}