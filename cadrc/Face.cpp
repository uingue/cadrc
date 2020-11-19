#include "Face.h"
#include"Loop.h"

bool Face::addLoop(Loop* l)
{
	if (!l)
		return false;
	Loop* templ = m_l;
	if (!templ)
		m_l = l;
	else
	{
		while (templ->next())
		{
			if (templ == l)
			{
				puts("l already in loop!");
				return false;
			}
			templ = templ->next();
		}
		templ->setNextl(l);
		l->setPrevl(templ);
	}
	l->setFace(this);
	return true;
}
