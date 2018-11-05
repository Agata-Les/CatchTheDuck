#pragma once

#define FVF_VERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )

struct Vertex
{
	Vertex(float x_,
		   float y_,
		   float z_,
		   float u_,
		   float v_)
	: x(x_),
	  y(y_),
	  z(z_),
	  u(u_),
	  v(v_)
	{}

	float x, y, z;
	float u, v;
};
