#include "Vertex.h"

bool Vertex::setPoint(double* point_coordinates)
{
	for (int i = 0; i < 3; i++)
	{
		m_point[i] = point_coordinates[i];
	}
	return true;
}

bool Vertex::setPoint(double x, double y, double z)
{
	m_point[0] = x;
	m_point[1] = y;
	m_point[2] = z;
	return true;
}
