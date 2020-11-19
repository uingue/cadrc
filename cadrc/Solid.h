#pragma once
#include<stdio.h>
#include"Vertex.h"

class Face;
class Vertex;
class Edge;
class Solid
{
public:
	Solid() {
		static int ids = 0;
		sid = ids++;
		m_f = NULL;
		m_e = NULL;
		m_v = NULL;
		m_prevs = m_nexts = NULL;
	}
	~Solid() {};
	int sid;
	bool addVertex(Vertex* v);
	bool addFace(Face* f);
	bool addEdge(Edge* e);
	void setFace(Face* f) { m_f = f; }
	void setEdge(Edge* e) { m_e = e; }
	Edge*& edge() { return m_e; }
	Face*& face() { return m_f; }
	Vertex*& vertex() { return m_v; }
protected:
	Solid* m_prevs;
	Solid* m_nexts;
	Face* m_f;
	Edge* m_e;
	Vertex* m_v;
};
