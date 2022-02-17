//
//  YKDebugDraw.h
//  YAGE Kit
//
//  Created by Simon Jordan on 20/06/2013.
//  Copyright (c) 2013 Yage Tech. All rights reserved.
//

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "glm.hpp"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#ifndef YAGE_Kit_YKDebugDraw_h
#define YAGE_Kit_YKDebugDraw_h

class YKDebugDraw : public btIDebugDraw{
    
public:
    void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix);
    virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
    
    virtual void drawContactPoint(const btVector3 &,const btVector3 &,btScalar,int,const btVector3 &){}
    virtual void reportErrorWarning(const char *){}
    virtual void draw3dText(const btVector3 &,const char *){}
    virtual void setDebugMode(int p){m = p;}
    int getDebugMode(void) const {return 3;}
    int m;
    

};

#endif
