#pragma once
#include"Face.h"

class HalfEdge;
class Loop
{
public:
	Loop() {
		static int idl = 0;
		lid = idl++;
		m_nextl = m_prevl = NULL;
		m_f = NULL;
		m_he = NULL;
	};
	~Loop() {};
	int lid;
	Face* &face();
	HalfEdge* &halfedge();
	Loop*& prev() { return m_prevl; }
	Loop*& next() { return m_nextl; }
	bool addHalfEdge(HalfEdge* he);
	void setHalfEdge(HalfEdge* he) { m_he = he; };
	void setFace(Face* f) { m_f = f; }
	void setPrevl(Loop* l) { m_prevl = l; }
	void setNextl(Loop* l) { m_nextl = l; }
	bool isInLoop(Vertex* v);
	HalfEdge* findHalfEdge(Vertex* v1, Vertex* v2);
	HalfEdge* findHalfEdge(Vertex* v1);

protected:
	Loop* m_prevl;
	Loop* m_nextl;
	HalfEdge* m_he;
	Face* m_f;

};
