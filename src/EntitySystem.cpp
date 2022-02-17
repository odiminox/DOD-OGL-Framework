#include "EntitySystem.h"

entitySystem::gameObject::gameObject()
{
	this->gameObjectID = 0;
	this->gameObjectForeignKey =rand()%100000;
    this->worldPosition = 0;
    parentGameObjectID = -1;
}


entitySystem::transformComponent::transformComponent()
{
	this->ID = 0x80;//10000000
    gameObjectID = 0;
    gameObjectForeignKey = 0;
    
    isDirty = true;
    isLocal = true;

	model = glm::mat4(1.0f);
	worldTranslate = glm::mat4(1.0f);
    positon = glm::vec3(0,0,0);
    scale = glm::vec3(0,0,0);
    trans.setIdentity();
    trans = btTransform(btQuaternion(btVector3(0,0,1),3.14159265359/2));
    orientation =  glm::normalize(glm::quat(glm::vec3(0,0,0)));
    qOrientation = btQuaternion(btVector3(0,0,1),3.14159265359/2);
    rotX = 0.0f;
    rotY = 0.0f;
    rotZ = 0.0f;
    
    localTranslate = glm::mat4(1.0f);
    localRotate = glm::mat4(1.0f);
    localScale = glm::mat4(1.0f);
    
    worldTranslate = glm::mat4(1.0f);
    worldRotate = glm::mat4(1.0f);
    worldScale = glm::mat4(1.0f);

    mv = glm::mat4(1.0f);
}

entitySystem::meshComponent::meshComponent()
{
	this->ID =  0x40;//010000000
    gameObjectID = 0;
    gameObjectForeignKey = 0;
	float side = 1.0f;
	float side2 = side / 2.0f;
    

	RED	  = 1.f;
	GREEN = 1.f;
	BLUE  = 1.f;
	ALPHA = 1.f;
    
    diffuseName = "";
    specularName = "";
    normalName = "";
    meshName = "";
    
    _texture = 0;
    _texCoordSlot = 0;
    _positionSlot = 0;
    _colorSlot = 0;
    _NormalSlot = 0;
    _vaoHandle = 0;
    _vertexBufferID = 0;
    _indexBufferID = 0;
    _textureBufferID = 0;

    //Garbage test data that will need to be removed when real geom data is loaded in.
	static const entityData::Vertex testVerts[] =
	{
		// Front
		{{-side2, -side2, side2}, {0.0f, 0.0f, 1.0f}, {1, 0, 0, 1}, {0, 0}},
		{{side2, -side2, side2}, {0.0f, 0.0f, 1.0f}, {0, 1, 0, 1}, {1, 0}},
		{{side2, side2, side2}, {0.0f, 0.0f, 1.0f},{0, 0, 1, 1}, {1, 1}},
		{{-side2, side2, side2},{0.0f, 0.0f, 1.0f}, {0, 0, 0, 1}, {0, 1}},
		// Back
		{{side2, -side2, side2}, {1.0f, 0.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{side2, -side2, -side2},{1.0f, 0.0f, 0.0f}, {0, 1, 0, 1}, {1, 0}},
		{{side2, side2, -side2},{1.0f, 0.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{side2, side2, side2},{1.0f, 0.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}},
		// Left
		{{-side2, -side2, -side2}, {0.0f, 0.0f, -1.0f},{1, 0, 0, 1}, {0, 0}},
		{{-side2, side2, -side2},{0.0f, 0.0f, -1.0f}, {0, 1, 0, 1}, {1, 0}},
		{{side2, side2, -side2}, {0.0f, 0.0f, -1.0f},{0, 0, 1, 1}, {1, 1}},
		{{side2, -side2, -side2},{0.0f, 0.0f, -1.0f}, {0, 0, 0, 1}, {0, 1}},
		// Right
		{{-side2, -side2, side2},{-1.0f, 0.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{-side2, side2, side2}, {-1.0f, 0.0f, 0.0f},{0, 1, 0, 1}, {1, 0}},
		{{-side2, side2, -side2},{-1.0f, 0.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{-side2, -side2, -side2},{-1.0f, 0.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}},
		// Top
		{{-side2, -side2, side2},{0.0f, -1.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{-side2, -side2, -side2},{0.0f, -1.0f, 0.0f}, {0, 1, 0, 1}, {1, 0}},
		{{side2, -side2, -side2},{0.0f, -1.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{side2, -side2, side2},{0.0f, -1.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}},
		// Bottom
		{{-side2, side2, side2},{0.0f, 1.0f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{side2, side2, side2}, {0.0f, 1.0f, 0.0f},{0, 1, 0, 1}, {1, 0}},
		{{side2, side2, -side2},{0.0f, 1.0f, 0.0f}, {0, 0, 1, 1}, {1, 1}},
		{{-side2, side2, -side2},{0.0f, 1.0f, 0.0f}, {0, 0, 0, 1}, {0, 1}}
	};

	 static const entityData::Index testIndices[] =
	{
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};

	std::vector<entityData::Vertex> vec(testVerts, testVerts + sizeof(testVerts) / sizeof(testVerts[0]));
	std::vector<entityData::Index> in(testIndices, testIndices + sizeof(testIndices) / sizeof(testIndices[0]));

	Vertices = vec;
	Indices = in;
}


entitySystem::cameraComponent::cameraComponent()
{
	this->ID = 0x20;//00100000
    gameObjectID = 0;
    gameObjectForeignKey = 0;

	position  = glm::vec3(0.0f,0.0f,0.0f);
	target    = glm::vec3(0.0f, 0.0f, 0.0f);
	up        = glm::vec3(0.0f, 1.0f, 0.0f);
	pitch           = 0.0f;
	roll            = 0.0f;
	yaw             = 0.0f;
	fieldOfView     = 45.0f;
	nearPlane       = 0.1f;
	farPlane        = 1000.0f;
	aspectRatio     = 90.0f;
}

entitySystem::physicsComponent::physicsComponent()
{
	this->ID = 0x10;//00010000
    gameObjectID = 0;
    gameObjectForeignKey = 0;
    boxCollisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
    //trans = btTransform(btQuaternion(btVector3(0,0,1),3.14159265359/2));
    mass = 0.0f;
    localInteria = btVector3(0,0,0);
}

entitySystem::lightComponent::lightComponent()
{
    this->ID = 0x8;//00001000
    gameObjectID = 0;
    gameObjectForeignKey = 0;
    
    colour = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    Kd = glm::vec3(1.0f,1.0f,1.0f);
    Ld = glm::vec3(1.0f,1.0f,1.0f);
    radius = 5.0f;
}
