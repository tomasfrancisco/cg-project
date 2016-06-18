//
// Created by Tomás Francisco on 18/06/16.
//

#ifndef CG_PROJECT_OBJECT_HPP
#define CG_PROJECT_OBJECT_HPP

#define LINE_LEN 100

#include "OpenGL.hpp"
#include "Structs.hpp"

class Object {
public:
    Object(const char * filePath);
    bool LoadFile();
    void Draw();

protected:
    vector <Point> V;    // List of geometric vertices, with (x,y,z[,w]) coordinates, w is optional and defaults to 1.0.
    vector <Point> VT;   // List of texture coordinates, in (u, v [,w]) coordinates, these will vary between 0 and 1, w is optional and defaults to 0.
    vector <Point> VN;   // List of vertex normals in (x,y,z) form; normals might not be unit vectors.
    vector <Face>  F;    // Polygonal face element

private:
    const char * filePath;

};


#endif //CG_PROJECT_OBJECT_HPP