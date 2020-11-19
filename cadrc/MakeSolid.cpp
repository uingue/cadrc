#include"MakeSolid.h"
#include<vector>
using namespace std;
#define PI 3.1415926


Solid* makeSolid_1genus()
{
	vector<Vertex*> vs;

	vs.push_back(new Vertex(-1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, 1.0, -1.0));
	vs.push_back(new Vertex(-1.0, 1.0, -1.0));
	vs.push_back(new Vertex(-1.0, -1.0, 1.0));
	vs.push_back(new Vertex(1.0, -1.0, 1.0));
	vs.push_back(new Vertex(1.0, 1.0, 1.0));
	vs.push_back(new Vertex(-1.0, 1.0, 1.0));

	vs.push_back(new Vertex(-0.3, -0.3, -1.0));
	vs.push_back(new Vertex(0.3, -0.3, -1.0));
	vs.push_back(new Vertex(0.3, 0.3, -1.0));
	vs.push_back(new Vertex(-0.3, 0.3, -1.0));
	vs.push_back(new Vertex(-0.3, -0.3, 1.0));
	vs.push_back(new Vertex(0.3, -0.3, 1.0));
	vs.push_back(new Vertex(0.3, 0.3, 1.0));
	vs.push_back(new Vertex(-0.3, 0.3, 1.0));


	Solid* s = mvfs(vs[0]);
	Loop* l = s->face()->loop();

	////构造底面
	mev(vs[0], vs[1], l);
	mev(vs[1], vs[2], l);
	mev(vs[2], vs[3], l);
	mef(vs[3], vs[0], l);

	//在这个面基础上构造一个立方体
	mev(vs[0], vs[4], l);
	mev(vs[1], vs[5], l);
	mef(vs[4], vs[5], l);
	mev(vs[2], vs[6], l);
	mef(vs[5], vs[6], l);
	mev(vs[3], vs[7], l);
	mef(vs[6], vs[7], l);
	mef(vs[7], vs[4], l);


	/* 孔 */
	Loop* bl = s->face()->next()->loop();//底面的环
	Loop* tl = s->face()->loop();//顶面的环
	//在底面上构造桥边
	mev(vs[0], vs[8], bl);
	//删桥边，生成一个新的（空）环
	Loop* nl1 = kemr(vs[0], vs[8], bl);
	////在空环上构造要挖空的面
	mev(vs[8], vs[9], nl1);
	mev(vs[9], vs[10], nl1);
	mev(vs[10], vs[11], nl1);
	Loop* nl2 = mef(vs[11], vs[8], nl1);
	//挖空内部，贯穿立方体
	mev(vs[8], vs[12], nl2);
	mev(vs[9], vs[13], nl2);
	mef(vs[13], vs[12], nl2);
	mev(vs[10], vs[14], nl2);
	mef(vs[14], vs[13], nl2);
	mev(vs[11], vs[15], nl2);
	mef(vs[15], vs[14], nl2);
	mef(vs[12], vs[15], nl2);
	//nl2现在是顶面的内环，删掉nl2所代表的面，并将nl2并入顶面tl，形成通孔
	kfmrh(nl2, tl);

	return s;
}


Solid* makeSolid_cylinderbox(double num)
{
	vector<Vertex*> vs;

	vs.push_back(new Vertex(-1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, 1.0, -1.0));
	vs.push_back(new Vertex(-1.0, 1.0, -1.0));
	vs.push_back(new Vertex(-1.0, -1.0, 1.0));
	vs.push_back(new Vertex(1.0, -1.0, 1.0));
	vs.push_back(new Vertex(1.0, 1.0, 1.0));
	vs.push_back(new Vertex(-1.0, 1.0, 1.0));

	double r = 0.5;
	for (double i = 0.0; i < num; i++)
	{
		vs.push_back(new Vertex(r * cos(PI * i * 2 / num), r * sin(PI * i * 2 / num), 1.0));

	}
	for (double i = 0.0; i < num; i++)
	{
		vs.push_back(new Vertex(r * cos(PI * i * 2 / num), r * sin(PI * i * 2 / num), 2.0));
	}

	Solid* s = mvfs(vs[0]);
	Loop* l = s->face()->loop();

	////构造底面
	mev(vs[0], vs[1], l);
	mev(vs[1], vs[2], l);
	mev(vs[2], vs[3], l);
	mef(vs[3], vs[0], l);

	//在底面基础上构造一个立方体
	mev(vs[0], vs[4], l);
	mev(vs[1], vs[5], l);
	mef(vs[4], vs[5], l);
	mev(vs[2], vs[6], l);
	mef(vs[5], vs[6], l);
	mev(vs[3], vs[7], l);
	mef(vs[6], vs[7], l);
	mef(vs[7], vs[4], l);

	/*圆柱*/
	Loop* bl = s->face()->next()->loop();//底面的环
	Loop* tl = s->face()->loop();//顶面的环
	//在顶面上构造桥边
	mev(vs[4], vs[8], tl);
	////删桥边，生成一个新的（空）环
	Loop* nl1 = kemr(vs[4], vs[8], tl);
	////在空环上构造面
	for (int i = 8; i < num + 7; i++)
		mev(vs[i], vs[i + 1], nl1);
	Loop* nl2 = mef(vs[num + 7], vs[8], nl1);
	//生成圆柱
	mev(vs[8], vs[8 + num], nl2);
	for (int i = 9; i <= num + 7; i++)
	{
		mev(vs[i], vs[i + num], nl2);
		mef(vs[i + num], vs[i + num - 1], nl2);
	}
	mef(vs[8 + num], vs[2 * num + 7], nl2);


	return s;
}

Solid* makeSolid_1genus_sweep(double dx, double dy, double dz)
{
	vector<Vertex*> vs;
	vs.push_back(new Vertex(-1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, 1.0, -1.0));
	vs.push_back(new Vertex(-1.0, 1.0, -1.0));

	vs.push_back(new Vertex(-0.3, -0.3, -1.0));
	vs.push_back(new Vertex(0.3, -0.3, -1.0));
	vs.push_back(new Vertex(0.3, 0.3, -1.0));
	vs.push_back(new Vertex(-0.3, 0.3, -1.0));

	Solid* s = mvfs(vs[0]);
	Loop* l0 = s->face()->loop();
	mev(vs[0], vs[1], l0);
	mev(vs[1], vs[2], l0);
	mev(vs[2], vs[3], l0);
	Loop* l1 = mef(vs[3], vs[0], l0);

	mev(vs[0], vs[4], l1);
	Loop* l2 = kemr(vs[0], vs[4], l1);
	mev(vs[4], vs[5], l2);
	mev(vs[5], vs[6], l2);
	mev(vs[6], vs[7], l2);
	Loop* l3 = mef(vs[7], vs[4], l2);
	kfmrh(l3, l0);

	sweep(s->face(), dx, dy, dz);
	return s;

}

Solid* makeSolid_2genus_sweep(double dx, double dy, double dz)
{
	vector<Vertex*> vs;
	vs.push_back(new Vertex(-1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, -1.0, -1.0));
	vs.push_back(new Vertex(1.0, 1.0, -1.0));
	vs.push_back(new Vertex(-1.0, 1.0, -1.0));

	vs.push_back(new Vertex(-0.75, -0.75, -1.0));
	vs.push_back(new Vertex(-0.25, -0.75, -1.0));
	vs.push_back(new Vertex(-0.25, -0.25, -1.0));
	vs.push_back(new Vertex(-0.75, -0.25, -1.0));

	vs.push_back(new Vertex(0.75, 0.75, -1.0));
	vs.push_back(new Vertex(0.25, 0.75, -1.0));
	vs.push_back(new Vertex(0.25, 0.25, -1.0));
	vs.push_back(new Vertex(0.75, 0.25, -1.0));

	Solid* s = mvfs(vs[0]);
	Loop* l0 = s->face()->loop();
	mev(vs[0], vs[1], l0);
	mev(vs[1], vs[2], l0);
	mev(vs[2], vs[3], l0);
	Loop* l1 = mef(vs[3], vs[0], l0);


	//第一个环
	mev(vs[0], vs[4], l1);
	Loop* l2 = kemr(vs[0], vs[4], l1);
	mev(vs[4], vs[5], l2);
	mev(vs[5], vs[6], l2);
	mev(vs[6], vs[7], l2);
	Loop* l3 = mef(vs[7], vs[4], l2);
	kfmrh(l3, l0);


	//第二个环
	mev(vs[0], vs[8], l1);
	Loop* l4 = kemr(vs[0], vs[8], l1);
	mev(vs[8], vs[9], l4);
	mev(vs[9], vs[10], l4);
	mev(vs[10], vs[11], l4);
	Loop* l5 = mef(vs[11], vs[8], l4);
	kfmrh(l5, l0);


	sweep(s->face(), 0, 0, 2);
	return s;

}
