#pragma once
#include "Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Vertex.h"
#include "Edge.h"
Solid* mvfs(Vertex* v);//����һ���㣬����һ���µ�����
HalfEdge* mev(Vertex* v1, Vertex* v2, Loop* lp);//����һ�����ӵ�v1���µ�,����loop lp�У��������µı�
Loop* mef(Vertex* v1, Vertex* v2, Loop* lp);//������ͬһ���⻷�ϵ�������v1v2֮����±ߣ�ͬʱ����һ���µ���
Loop* kemr(Vertex* v1, Vertex* v2, Loop* lp1);//ɾ��v1v2֮��ıߣ�������һ���µ��ڻ�
Loop* kfmrh(Loop* inlp, Loop* outlp);//ɾ��һ���棬�����Ϊһ���ڻ��������������һ��ͨ��
void semv(Edge* e, Vertex* v, Solid* s);//��edge e�Ϲ���һ���µĵ㣬����һ����Ϊ������
void sweep(Face* f, double dx, double dy, double dz);//ɨ�ɣ���һ����Ĺ켣��������
