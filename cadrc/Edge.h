#pragma once
#include<assert.h>

class HalfEdge;
class Edge
{
public:
	Edge() {
		static int ide = 0;
		eid = ide++;
		m_preve = m_nexte = NULL;
		m_halfedge[0] = m_halfedge[1] = NULL;
	}
	~Edge() {};
	HalfEdge*& halfedge(int id)
	{
		assert(0 <= id && id < 2);
		return m_halfedge[id];
	}
	Edge*& prev() { return m_preve; }
	Edge*& next() { return m_nexte; }
	void setPreve(Edge* e) { m_preve = e; }
	void setNexte(Edge* e) { m_nexte = e; }
	void setHalfEdge(int id, HalfEdge* he) {
		m_halfedge[id] = he;
	}
	int eid;
protected:
	HalfEdge* m_halfedge[2];
	Edge* m_preve;
	Edge* m_nexte;
};
