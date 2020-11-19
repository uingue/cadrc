#pragma once
#include "Edge.h"
#include"Solid.h"
class Loop;
class Face
{
public:
	Face() {
		static int idf = 0;
		fid = idf++;
		m_nextf = m_prevf = NULL;
		m_s = NULL;
		m_l = NULL;
	}
	~Face(){}
	int fid;
	Loop* &loop() { return m_l; }
	Solid* &solid() { return m_s; }
	Face*& prev() { return m_prevf; }
	Face*& next() { return m_nextf; }
	void setPrevf(Face* f) { m_prevf = f; }
	void setNextf(Face* f) { m_nextf = f; }
	void setSolid(Solid* s) { m_s = s; }
	bool addLoop(Loop* l);

protected:
	Face* m_prevf;
	Face* m_nextf;
	Loop* m_l;
	Solid* m_s;
};

