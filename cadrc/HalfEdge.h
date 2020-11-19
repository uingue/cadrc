#pragma once
#include "Vertex.h"
#include "Loop.h"
#include"Edge.h"

class HalfEdge
{
public:
	HalfEdge();
	~HalfEdge() {};
	bool setStartVertex(Vertex* v);
	bool setPairHalfEdge(HalfEdge* he);
	bool setPrevHalfEdge(HalfEdge* he);
	bool setNextHalfEdge(HalfEdge* he);
	bool setLoop(Loop* lp);
	bool setEdge(Edge* e);
	Vertex* &startVertex() { return m_startv; }
	HalfEdge* next() { return m_nexthe; }
	HalfEdge* prev() { return m_prevhe; }
	HalfEdge* pair() { return m_pairhe; }
	Loop* &loop() { return m_wloop; }
	Edge* &edge() { return m_edge; }
	int heid;

protected:
	Edge* m_edge;
	HalfEdge* m_prevhe;
	HalfEdge* m_nexthe;
	HalfEdge* m_pairhe;
	Loop* m_wloop;
	Vertex* m_startv;//start vertex
};

