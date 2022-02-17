//
//  Defines.h
//  YAGE Kit
//
//  Created by Simon Jordan on 17/07/2013.
//  Copyright (c) 2013 Yage Tech. All rights reserved.
//

#ifndef YAGE_Kit_Defines_h
#define YAGE_Kit_Defines_h

//Typdefs to mask libraries used, so they can be swapped out without ceasing functionality of the engine

#include "glm.hpp"
#include "quaternion.hpp"
#include "matrix_transform.hpp"
#include <BulletDynamics/btBulletDynamicsCommon.h>


typedef glm::vec2 YKVec2;
typedef glm::vec3 YKVec3;
typedef glm::vec4 YKVec4;
typedef glm::mat4 YKMat4;
typedef glm::mat3 YKMat3;
typedef glm::mat2 YKMat2;
typedef glm::mat2x2 YKMat2x2;
typedef glm::mat2x3 YKMat2x3;
typedef glm::mat2x4 YKMat2x4;
typedef glm::mat3x2 YKMat3x2;
typedef glm::mat3x3 YKMat3x3;
typedef glm::mat3x4 YKMat3x4;
typedef glm::mat4x2 YKMat4x2;
typedef glm::mat4x3 YKMat4x3;
typedef glm::mat4x4 YKMat4x4;

typedef btRigidBody YKRigidBody;
typedef btTransform YKTransform;
typedef btQuaternion YKQuaternion;
typedef btCollisionShape YKCollisionShape;
typedef btDefaultMotionState YKMotionState;
typedef btRigidBody YKRigidBody;




#endif
