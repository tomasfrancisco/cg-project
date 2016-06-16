/*
 * Loader.h
 *
 * Created on: Aug 13, 2012
 *     Author: letrungkien7
 */

#ifndef LOADER_H_
#define LOADER_H_

#include<iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<string>
#include<vector>
#include "Eigen/Core"

typedef Eigen::Vector3d Point;

class Loader {
public:
	void Load(char* filename);
	void Draw();

	std::vector<Point> V;
	std::vector<std::vector<int> > F;
};

#endif /* LOADER_H_ */
