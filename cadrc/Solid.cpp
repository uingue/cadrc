#include "Solid.h"
#include"Face.h"

bool Solid::addVertex(Vertex* v)
{
	if (!v)
		return false;
	Vertex* tempv = m_v;
	if (!tempv)
		m_v = v;
	else
	{
		while (tempv->next())
		{
			tempv = tempv->next();
		}
		tempv->setNextv(v);
		v->setPrevv(tempv);
	}

	return true;
}

bool Solid::addFace(Face* f)
{
	if (!f)
		return false;
	Face* tempf = m_f;
	if (!tempf)
		m_f = f;
	else
	{
		while (tempf->next())
		{
			tempf= tempf->next();
		}
		tempf->setNextf(f);
		f->setPrevf(tempf);
	}
	f->setSolid(this);
	return true;
}

bool Solid::addEdge(Edge* e)
{
	if (!e)
		return false;
	Edge* tempe = m_e;
	if (!tempe)
		m_e = e;
	else
	{
		while (tempe->next())
		{
			tempe = tempe->next();
		}
		tempe->setNexte(e);
		e->setPreve(tempe);
	}
	return true;
}
