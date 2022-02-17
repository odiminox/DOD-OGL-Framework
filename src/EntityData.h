#pragma once

#include "EntitySystem.h"

namespace entityData
{
	struct Vertex{
    
		float position[3];
		float normal[3];
		float colour[4];
		float texCoord[2];
    
	};
	struct Index{
		GLuint a,b,c;
	};
    
    


}