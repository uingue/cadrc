#pragma once
#include "Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Vertex.h"
#include "Edge.h"
Solid* mvfs(Vertex* v);//输入一个点，构造一个新的物体
HalfEdge* mev(Vertex* v1, Vertex* v2, Loop* lp);//构造一个连接到v1的新点,加入loop lp中，并构造新的边
Loop* mef(Vertex* v1, Vertex* v2, Loop* lp);//构造在同一个外环上的两个点v1v2之间的新边，同时构造一个新的面
Loop* kemr(Vertex* v1, Vertex* v2, Loop* lp1);//删除v1v2之间的边，并构造一个新的内环
Loop* kfmrh(Loop* inlp, Loop* outlp);//删除一个面，将其变为一个内环，并生成物体的一个通孔
void semv(Edge* e, Vertex* v, Solid* s);//在edge e上构造一个新的点，分裂一条边为两条边
void sweep(Face* f, double dx, double dy, double dz);//扫成，从一个面的轨迹生成物体
