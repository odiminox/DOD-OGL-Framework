//
//  Shader.fsh
//  Kepler Framework
//
//  Created by Simon Jordan on 05/10/2013.
//  Copyright (c) 2013 Black Ice Interactive. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
