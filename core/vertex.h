#ifndef VERTEX_H
#define VERTEX_H

#include "vec3.h"
class Vertex {
public:
	Vec3 position;
	Vec3 normal;
	
	Vertex(Vec3 position, Vec3 normal);
};

#endif
