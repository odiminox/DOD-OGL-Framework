#pragma once

#include "Defines.h"
#include "Texture.h"
#include <vector>
#include "EntityData.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

//#include "Importer.hpp"

/*************************************************************************************************************
//gameObjects contain only the data that is to be manipulated, no functions except their constructors.
//each gameObject and component is stored contigeously in memory inside  the respective vector in EntityProcessing.h
//This gives each gameObject and component a very small memory footprint and also conforms to how
//the computer wants to consume the information. By avoiding the use of classes and the "new" keyword
//we do not need to worry about large objects spawning in (possibly)non-related areas of memory
//causing large memory footprints and many CPU cache misses
//
//Whereas before, to manipulate an object, we had to access the methods within its class and potentially
//deal messy inheritance chains that could have performance implications depending on their size
//we now have the single functions and processing functions to act upon, which we access directly.
//This implies that multi-threading is easier for data, as we can chain tasks and thread them in the appropriate
//order without the huge amount of issies trying to multi-thread normal objects
*************************************************************************************************************/

/*************************************************************************************************************
//The entity systems works similiar to a database, with relational IDs that bind each element together
//We have foreign keys in each component that link them to their respective game object
//when we process the data inside the game object, we look at the IDs, then update that corresponding data
//that we have added
*************************************************************************************************************/

//A component may only contain raw data and mutators and getters relating to that data. All methods relating to
//update are done in EntityProcesing in batch

#pragma once

namespace entitySystem {

	
	struct gameObject
	{
		gameObject();
		int tag;
        int worldPosition;
		std::string name;
		unsigned short gameObjectID;            //Instead of multiple bools for flags, we have one int 
		int gameObjectForeignKey;               //Each gameObject has a unique ID that the component can identify with it
		int componentLocations[5];              //The location of the components in their respective vectors, ordered: [TC, MC, PC, CC, LC]
		int parentGameObjectID;                 //The ID of the parent game object to be used in the scene graph.
		std::vector<int> childGameObjectIDs;    //The IDs of the children GOs linked to this GO
	};


	struct transformComponent
	{
		unsigned short ID;                      //The ID of this component that is linked to the gameObject
		unsigned short gameObjectID;			//The ID of the gameObject that is linked to this component
		int gameObjectForeignKey;               //How we bind to our GO
		transformComponent();
        
        bool isDirty;                           //So we don't inadvertently update TCs that have already been updated.
        bool isLocal;                           //Flag to specify if we want to rotate and around the local or world origin

		glm::mat4 localTranslate;
		glm::mat4 localRotate;
		glm::mat4 localScale;

		glm::mat4 worldTranslate;
		glm::mat4 worldRotate;
		glm::mat4 worldScale;

		glm::vec3 positon;
        btTransform trans;
        glm::quat orientation;
        btQuaternion qOrientation;
		glm::vec3 scale;

		glm::mat4 model;
		glm::mat4 mv;

		float rotX;
		float rotY;
		float rotZ;
	};

	struct meshComponent
	{
		unsigned short ID;
		int gameObjectID;
		int gameObjectForeignKey;
		meshComponent();

		Texture *pTexture;

		std::vector<entityData::Vertex> Vertices;
		std::vector<entityData::Index> Indices;

		std::string diffuseName;
		std::string specularName;
		std::string normalName;
		std::string meshName;

		GLuint _texture;
		GLuint _texCoordSlot;
		GLuint _positionSlot;
		GLuint _colorSlot;
		GLuint _NormalSlot;
		GLuint _vaoHandle;                      //global variable to hold the vertex array object.
		GLuint _vertexBufferID;
		GLuint _indexBufferID;
		GLuint _textureBufferID;

		float RED;
		float GREEN;
		float BLUE;
		float ALPHA;
	};

	struct cameraComponent
	{
		unsigned short ID;
		int gameObjectID;
		int gameObjectForeignKey;

		cameraComponent();

		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 up;  
		float     pitch;
		float     roll;
		float     yaw;
		float     fieldOfView;
		float     nearPlane;
		float     farPlane;
		float     aspectRatio;
	};

	struct physicsComponent
	{
		unsigned short ID;
		int gameObjectID;
		int gameObjectForeignKey;

		physicsComponent();
        
        btCollisionShape* boxCollisionShape;
        btDefaultMotionState* motionState;
        btRigidBody* rigidBody;
        
        btVector3 localInteria;
        float mass;

	};
    
    struct lightComponent
    {
        unsigned short ID;
        int gameObjectID;
        int gameObjectForeignKey;
        
        lightComponent();
        //This should be factored out into the mesh class, so each mesh can have its own material properties, keep here for easy testing.
        glm::vec3 Ka;
        glm::vec3 Kd;
        glm::vec3 Ks;
        
        glm::vec3 La;
        glm::vec3 Ld;
        glm::vec3 Ls;
        
        float shininess;
        
        glm::vec4 colour;
        float radius;
    };

}