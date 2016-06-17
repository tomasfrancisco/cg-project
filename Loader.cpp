/*
 * Loader.cpp
 *
 * Created on: Aug 13, 2012
 *     Author: letrungkien7
 */

#include "Loader.hpp"

using namespace std;

Loader::Loader() { }

Loader::~Loader(){}

bool Loader::load() {
    point p;

    FILE *f = fopen(this->path, "r");
    if (!f) return false;

    char line[MAXLEN];
    double x = 0, y = 0, z = 0;
    int conn[6];
    int uv[3];
    this->uvEnabled = false;

    while(fgets(line, MAXLEN, f)) {
        switch (line[0]) {
            case 'v':
                sscanf(line+2, "%lf %lf %lf", &x, &y, &z);
                //p = {x, y, z};
                p.x = x;
                p.y = y;
                p.z = z;
                if (line[1] == ' ') {
                    this->verts.push_back(p);
                }
                else if (line[1] == 'n') {
                    this->normals.push_back(p);
                }
                else if (line[1] == 't') {
                    this->uvEnabled = true;
                    this->uvs.push_back(p);
                }
                break;
            case 'f':
                if (this->uvEnabled) {
                    sscanf(line+2, "%d/%d/%d %d/%d/%d %d/%d/%d", &conn[0], &uv[0], &conn[1], &conn[2], &uv[1], &conn[3], &conn[4], &uv[2], &conn[5]);
                }
                else {
                    sscanf(line+2, "%d//%d %d//%d %d//%d", &conn[0], &conn[1], &conn[2], &conn[3], &conn[4], &conn[5]);
                }
                face cf;
                cf.points.push_back(this->verts[conn[0]-1]);
                cf.points.push_back(this->verts[conn[2]-1]);
                cf.points.push_back(this->verts[conn[4]-1]);
                cf.normals.push_back(this->normals[conn[1]-1]);
                cf.normals.push_back(this->normals[conn[3]-1]);
                cf.normals.push_back(this->normals[conn[5]-1]);
                if (this->uvEnabled) {
                    cf.uvs.push_back(this->uvs[uv[0]-1]);
                    cf.uvs.push_back(this->uvs[uv[1]-1]);
                    cf.uvs.push_back(this->uvs[uv[2]-1]);
                }
                this->faces.push_back(cf);
                break;
        }
    }
    return true;
}

void Loader::update() {

}

void Loader::render() {
    int i;
    if (this->texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }
    if (this->opacity < 1.0) {
        GLfloat color[4] = {1.0, 1.0, 1.0, this->opacity};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    }
    glBegin(GL_TRIANGLES);
    for (i=0;i<(signed)this->faces.size();i++) {
        glNormal3f(this->faces[i].normals[0].x, this->faces[i].normals[0].y, this->faces[i].normals[0].z);
        if ((this->texture) && (this->uvEnabled)) glTexCoord2f(this->faces[i].uvs[0].x, this->faces[i].uvs[0].y);
        glVertex3f(this->faces[i].points[0].x, this->faces[i].points[0].y, this->faces[i].points[0].z);
        glNormal3f(this->faces[i].normals[1].x, this->faces[i].normals[1].y, this->faces[i].normals[1].z);
        if ((this->texture) && (this->uvEnabled)) glTexCoord2f(this->faces[i].uvs[1].x, this->faces[i].uvs[1].y);
        glVertex3f(this->faces[i].points[1].x, this->faces[i].points[1].y, this->faces[i].points[1].z);
        glNormal3f(this->faces[i].normals[2].x, this->faces[i].normals[2].y, this->faces[i].normals[2].z);
        if ((this->texture) && (this->uvEnabled)) glTexCoord2f(this->faces[i].uvs[2].x, this->faces[i].uvs[2].y);
        glVertex3f(this->faces[i].points[2].x, this->faces[i].points[2].y, this->faces[i].points[2].z);

    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}