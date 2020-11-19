#pragma once
#include<stdio.h>

static int idv = 0;

class Vertex
{
public:
	Vertex() {
		vid = idv++;
		m_prevv = NULL;
		m_nextv = NULL;
		m_point[0] = m_point[1] = m_point[2] = 0;
	}
	Vertex(double x,double y,double z) {
		vid = idv++;
		m_prevv = NULL;
		m_nextv = NULL;
		m_point[0] = x;
		m_point[1] = y;
		m_point[2] = z;
	}
	~Vertex() {};
	bool setPoint(double* point_coordinates);
	bool setPoint(double x, double y,double z);
	void setPrevv(Vertex* v) { m_prevv = v; }
	void setNextv(Vertex* v) { m_nextv = v; }
	Vertex*& prev() { return m_prevv; }
	Vertex*& next() { return m_nextv; }
	double* point() { return m_point; }
	int vid;
protected:
	Vertex* m_prevv;
	Vertex* m_nextv;
	double m_point[3];

};

