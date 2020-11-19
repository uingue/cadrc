#include "Euler.h"

//输入一个点，构造一个新的物体
Solid* mvfs(Vertex* v)
{
	Solid* s = new Solid();
	Face* f = new Face();
	Loop* l = new Loop();

	s->addVertex(v);
	s->addFace(f);
	f->addLoop(l);

	return s;
}

//构造一个连接到v1的新点,加入loop lp中，并构造新的边
HalfEdge* mev( Vertex* v1, Vertex* v2, Loop* lp)
{
	Solid* s = lp->face()->solid();
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();
	Edge* e = new Edge();

	if (!v1)
	{
		puts("v1 is not in the solid!");
		return NULL;
	}

	he1->setStartVertex(v1);
	he2->setStartVertex(v2);
	he1->setPairHalfEdge(he2);
	he2->setPairHalfEdge(he1);
	he1->setLoop(lp);
	he2->setLoop(lp);
	he1->setEdge(e);
	he2->setEdge(e);
	e->setHalfEdge(0, he1);
	e->setHalfEdge(1, he2);

	if (!lp->halfedge())
	{
		lp->setHalfEdge(he1);
		he1->setPrevHalfEdge(he2);
		he2->setNextHalfEdge(he1);
	}
	else
	{
		HalfEdge* he = lp->halfedge();
		for (; he->next()->startVertex() != v1; he = he->next());
		he1->setPrevHalfEdge(he);
		he2->setNextHalfEdge(he->next());
		he->next()->setPrevHalfEdge(he2);
		he->setNextHalfEdge(he1);
	}
	he1->setNextHalfEdge(he2);
	he2->setPrevHalfEdge(he1);

	s->addEdge(e);
	s->addVertex(v2);

	return he1;
}

//构造在同一个外环上的两个点v1v2之间的新边，同时构造一个新的面
Loop* mef(Vertex* v1, Vertex* v2, Loop* lp1)
{
	Solid* s = lp1->face()->solid();

	if (!v1)
	{
		puts("v1 is not in the solid!");
		return NULL;
	}
	if (!v2)
	{
		puts("v2 is not in the solid!");
		return NULL;
	}
	if (!lp1->isInLoop(v1) || !lp1->isInLoop(v2))
	{
		puts("v1 and v2 are not in a same loop!");
		return NULL;
	}

	Edge* e = new Edge();
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();
	Loop* lp2 = new Loop();
	Face* f = new Face();

	HalfEdge* she1 = lp1->findHalfEdge(v1);
	HalfEdge* she2 = lp1->findHalfEdge(v2);

	he1->setStartVertex(v1);
	he2->setStartVertex(v2);
	he1->setPairHalfEdge(he2);
	he2->setPairHalfEdge(he1);
	he1->setEdge(e);
	he2->setEdge(e);
	e->setHalfEdge(0, he1);
	e->setHalfEdge(1, he2);

	HalfEdge* temphe = she1;
	while (temphe)
	{
		if (temphe == she2)
			break;
		temphe->setLoop(lp2);
		temphe = temphe->next();
	}
	he1->setLoop(lp1);
	he2->setLoop(lp2);
	lp2->addHalfEdge(he2);
	lp1->setHalfEdge(he1);
	lp2->setFace(f);

	he1->setPrevHalfEdge(she1->prev());
	he1->setNextHalfEdge(she2);
	he2->setPrevHalfEdge(she2->prev());
	he2->setNextHalfEdge(she1);

	she1->setPrevHalfEdge(he2);
	he2->prev()->setNextHalfEdge(he2);
	she2->setPrevHalfEdge(he1);
	he1->prev()->setNextHalfEdge(he1);

	s->addEdge(e);
	s->addFace(f);
	f->addLoop(lp2);
	f->setSolid(s);

	return lp2;
}

//删除v1v2之间的边，并构造一个新的内环
Loop* kemr(Vertex* v1, Vertex* v2, Loop* lp1)
{
	Solid* s = lp1->face()->solid();
	if (!v1)
	{
		puts("v1 is not in the solid!");
		return NULL;
	}
	if (!v2)
	{
		puts("v2 is not in the solid!");
		return NULL;
	}
	if (!lp1->isInLoop(v1) || !lp1->isInLoop(v2))
	{
		puts("v1 and v2 are not in a same loop!");
		return NULL;
	}

	HalfEdge* he1 = lp1->findHalfEdge(v1,v2);
	HalfEdge* he2 = he1->pair();

	Loop* lp2 = new Loop();
	if (he1->next() != he2)
	{
		HalfEdge* temphe = he1->next();
		while (temphe)
		{
			if (temphe == he2)
				break;
			temphe->setLoop(lp2);
			lp2->addHalfEdge(temphe);
			temphe = temphe->next();
		}
		he1->next()->setPrevHalfEdge(he2->prev());
		he2->prev()->setNextHalfEdge(he1->next());
	}
	lp1->face()->addLoop(lp2);
	lp1->setHalfEdge(he1->prev());

	he1->prev()->setNextHalfEdge(he2->next());
	he2->next()->setPrevHalfEdge(he1->prev());

	Edge* e = he1->edge();
	if (e->next() && e->prev())
	{
		e->next()->setPreve(e->prev());
		e->prev()->setNexte(e->next());
	}
	else if (e->next() && !e->prev())
	{
		e->next()->setPreve(NULL);
		s->setEdge(e->next());
	}
	else if (!e->next() && e->prev())
	{
		e->prev()->setNexte(NULL);
	}
	else
	{
		s->setEdge(NULL);
	}

	delete e;
	delete he1;
	delete he2;
	return lp2;

}

//删除一个面，将其变为一个内环，并生成物体的一个通孔
Loop* kfmrh( Loop* inlp, Loop* outlp)
{
	Face* f = inlp->face();
	outlp->face()->addLoop(inlp);

	if (f->next() && f->prev())
	{
		f->next()->setPrevf(f->prev());
		f->prev()->setNextf(f->next());
	}
	else if (f->next() && !f->prev())
	{
		f->next()->setPrevf(NULL);
		outlp->face()->solid()->setFace(f->next());
	}
	else if (!f->next() && f->prev())
	{
		f->prev()->setNextf(NULL);
	}
	else
	{
		outlp->face()->solid()->setFace(NULL);
	}
	delete f;
	return inlp;
}

void semv(Edge* e, Vertex* v, Solid* s)
{

	HalfEdge* he1 = e->halfedge(0);
	HalfEdge* he2 = e->halfedge(1);
	Vertex* v1 = he1->startVertex();
	Vertex* v2 = he2->startVertex();

	Edge* ne = new Edge();
	HalfEdge* nhe1 = new HalfEdge();
	HalfEdge* nhe2 = new HalfEdge();

	he1->next()->setPrevHalfEdge(nhe1);
	he2->prev()->setNextHalfEdge(nhe2);
	he2->setStartVertex(v);
	nhe2->setStartVertex(v2);

	nhe1->setStartVertex(v);
	nhe1->setPrevHalfEdge(he1);
	nhe1->setNextHalfEdge(he1->next());
	nhe2->setPrevHalfEdge(he2->prev());
	nhe2->setNextHalfEdge(he2);
	nhe1->setPairHalfEdge(nhe2);
	nhe2->setPairHalfEdge(nhe1);

	he1->setNextHalfEdge(nhe1);
	he2->setPrevHalfEdge(nhe2);
	
	nhe1->setEdge(ne);
	nhe2->setEdge(ne);

	ne->setHalfEdge(0, nhe1);
	ne->setHalfEdge(1, nhe2);
	e->setNexte(ne);
	
	nhe1->setLoop(he1->loop());
	nhe2->setLoop(he2->loop());

	he1->loop()->addHalfEdge(nhe1);
	he2->loop()->addHalfEdge(nhe2);

	s->addVertex(v);
	s->addEdge(ne);

}

void sweep(Face* f, double dx, double dy, double dz)
{
	for (Loop* l = f->loop(); l != NULL; l = l->next())
	{
		HalfEdge* he = l->halfedge();
		Vertex* sv = he->startVertex();
		HalfEdge *henext = he->next(), *heprev = he->prev();

		Vertex* v1 = sv;
		Vertex* v2 = new Vertex(sv->point()[0] + dx, sv->point()[1] + dy, sv->point()[2] + dz);
		Vertex* first = v2;
		Vertex* last = first;

		mev(v1, v2, l);
		//取下一个半边并判断循环是否结束
		if (he == heprev)
		{
			he = NULL;
		}
		else
		{
			he = henext;
			henext = he->next();
		}
		while (he)
		{
			v1 = he->startVertex();
			v2 = new Vertex(v1->point()[0] + dx, v1->point()[1] + dy, v1->point()[2] + dz);

			mev(v1, v2, l);
			mef(last, v2, l);
			last = v2;

			if (he == heprev)
			{
				//最后一个面
				mef(last, first, l);
				he = NULL;
			}
			else
			{
				//否则继续取下个he
				he = henext;
				henext = he->next();
			}
		}
	}
}
