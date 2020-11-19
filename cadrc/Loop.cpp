#include "Loop.h"
#include"HalfEdge.h"

Face* &Loop::face()
{
	return m_f;
}

HalfEdge* &Loop::halfedge()
{
	return m_he;
}

bool Loop::addHalfEdge(HalfEdge* he)
{
	if (!he)
		return false;
	HalfEdge* temphe = m_he;
	if (!temphe)
	{
		m_he = he;
	}
	else
	{
		while (temphe->next())
		{
			if (temphe == he)
			{
				puts("he already in this loop!");
				return false;
			}
			temphe = temphe->next();
		}

		temphe->setNextHalfEdge(he);
		he->setPrevHalfEdge(temphe);
	}
	he->setLoop(this);
	return true;
}

bool Loop::isInLoop(Vertex* v)
{
	if(!v)
		return false;
	HalfEdge* temphe=m_he;
	while (temphe)
	{
		if (temphe->startVertex() == v)
			return true;
		temphe = temphe->next();
		if (temphe == m_he)
			return false;
	}
	return false;
}

HalfEdge* Loop::findHalfEdge(Vertex* v1, Vertex* v2)
{
	if (!this->isInLoop(v1))
	{
		puts("v1 is not in this loop!");
		return NULL;
	}
	if (!this->isInLoop(v2))
	{
		puts("v2 is not in this loop!");
		return NULL;
	}
	HalfEdge* temphe = m_he;
	while (temphe)
	{
		if (temphe->startVertex() == v1 && temphe->pair()->startVertex() == v2)
			return temphe;
		temphe = temphe->next();
		if (temphe == m_he)
			return NULL;
	}
	return NULL;
}

HalfEdge* Loop::findHalfEdge(Vertex* v1)
{
	if (!this->isInLoop(v1))
	{
		puts("v1 is not in this loop!");
		return NULL;
	}
	HalfEdge* temphe = m_he;
	while (temphe)
	{
		if (temphe->startVertex() == v1)
			return temphe;
		temphe = temphe->next();
		if (temphe == m_he)
			return NULL;
	}
	return NULL;
}
