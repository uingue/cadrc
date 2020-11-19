#include "HalfEdge.h"

HalfEdge::HalfEdge()
{
	static int idhe = 0;
	heid = idhe++;
	m_nexthe = m_prevhe = m_pairhe = NULL;
	m_wloop = NULL;
	m_edge = NULL;
	m_startv = NULL;

}

bool HalfEdge::setStartVertex(Vertex* v)
{
	if (!v)
	{
		return false;
	}
	m_startv = v;
	return true;
}

bool HalfEdge::setPairHalfEdge(HalfEdge* he)
{
	if (!he)
	{
		return false;
	}
	m_pairhe = he;
	return true;
}

bool HalfEdge::setPrevHalfEdge(HalfEdge* he)
{
	if (!he)
	{
		return false;
	}
	m_prevhe = he;
	return true;
}

bool HalfEdge::setNextHalfEdge(HalfEdge* he)
{
	if (!he)
	{
		return false;
	}
	m_nexthe = he;
	return true;
}

bool HalfEdge::setLoop(Loop* lp)
{
	if (!lp)
	{
		return false;
	}
	m_wloop = lp;
	return true;
}

bool HalfEdge::setEdge(Edge* e)
{
	if (!e)
	{
		return false;
	}
	m_edge = e;
	return true;
}
