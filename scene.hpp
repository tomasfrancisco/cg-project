//
//  scene.hpp
//  cg-project
//
//  Created by Tomás Francisco and Madalena Fernandinho.
//  Copyright © 2016 Tomás Francisco and Madalena Fernandinho. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

void start(int argc, char** argv);

#endif /* scene_hpp */
