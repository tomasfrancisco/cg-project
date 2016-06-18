//
// Created by Tomás Francisco on 18/06/16.
//

#include "Object.hpp"


Object::Object(const char *filePath) {
    this->filePath = filePath;
}

bool Object::LoadFile() {
    Point p;

    FILE * file = fopen(this->filePath, "r");
    if (!file) {
        cout << "Cannot read file [" << this->filePath << "]\n";
        return false;
    }

    char line[LINE_LEN];
    double x = 0, y = 0, z = 0;
    int conn[6];
    //int uv[3];
    //this->uvEnabled = false;

    while(fgets(line, LINE_LEN, file)) {
        switch (line[0]) {
            case 'v':
                sscanf(line+2, "%lf %lf %lf", &x, &y, &z);
                //p = {x, y, z};
                p.x = x;
                p.y = y;
                p.z = z;
                if (line[1] == ' ') {
                    this->V.push_back(p);
                }
                else if (line[1] == 'n') {
                    this->VN.push_back(p);
                }
                else if (line[1] == 't') {
                    //this->uvEnabled = true;
                    //this->uvs.push_back(p);
                }
                break;
            case 'f':
//                if (this->uvEnabled) {
//                    sscanf(line+2, "%d/%d/%d %d/%d/%d %d/%d/%d", &conn[0], &uv[0], &conn[1], &conn[2], &uv[1], &conn[3], &conn[4], &uv[2], &conn[5]);
//                }
//                else {
                    sscanf(line+2, "%d//%d %d//%d %d//%d", &conn[0], &conn[1], &conn[2], &conn[3], &conn[4], &conn[5]);
//                }
                Face cf;
                cf.V.push_back(this->V[conn[0]-1]);
                cf.V.push_back(this->V[conn[2]-1]);
                cf.V.push_back(this->V[conn[4]-1]);
                cf.VN.push_back(this->VN[conn[1]-1]);
                cf.VN.push_back(this->VN[conn[3]-1]);
                cf.VN.push_back(this->VN[conn[5]-1]);
//                if (this->uvEnabled) {
//                    cf.uvs.push_back(this->uvs[uv[0]-1]);
//                    cf.uvs.push_back(this->uvs[uv[1]-1]);
//                    cf.uvs.push_back(this->uvs[uv[2]-1]);
//                }
                this->F.push_back(cf);
                break;
        }
    }
    return true;
}

void Object::Draw() {
    int i;
//    if (this->texture) {
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, this->texture);
//    }
//    if (this->opacity < 1.0) {
//        GLfloat color[4] = {1.0, 1.0, 1.0, this->opacity};
//        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
//    }
    glBegin(GL_TRIANGLES);
    for (i=0;i<(signed)this->F.size();i++) {
        glNormal3f(this->F[i].VN[0].x, this->F[i].VN[0].y, this->F[i].VN[0].z);
        //if ((this->texture) && (this->uvEnabled)) glTexCoord2f(this->faces[i].uvs[0].x, this->faces[i].uvs[0].y);
        glVertex3f(this->F[i].V[0].x, this->F[i].V[0].y, this->F[i].V[0].z);
        glNormal3f(this->F[i].VN[1].x, this->F[i].VN[1].y, this->F[i].VN[1].z);
        //if ((this->texture) && (this->uvEnabled)) glTexCoord2f(this->faces[i].uvs[1].x, this->faces[i].uvs[1].y);
        glVertex3f(this->F[i].V[1].x, this->F[i].V[1].y, this->F[i].V[1].z);
        glNormal3f(this->F[i].VN[2].x, this->F[i].VN[2].y, this->F[i].VN[2].z);
        //if ((this->texture) && (this->uvEnabled)) glTexCoord2f(this->faces[i].uvs[2].x, this->faces[i].uvs[2].y);
        glVertex3f(this->F[i].V[2].x, this->F[i].V[2].y, this->F[i].V[2].z);

    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//class Object {
//public:
//    Object();
//    Object(char * filePath);
//
//    void LoadFile();
//    void LoadFile(char * filePath);
//
//    void Draw();
//
//protected:
//    float V;    // List of geometric vertices, with (x,y,z[,w]) coordinates, w is optional and defaults to 1.0.
//    float VT;   // List of texture coordinates, in (u, v [,w]) coordinates, these will vary between 0 and 1, w is optional and defaults to 0.
//    float VN;   // List of vertex normals in (x,y,z) form; normals might not be unit vectors.
//    float F;    // Polygonal face element
//
//private:
//    char * filePath;
//
//};
