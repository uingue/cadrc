# cadrc

1. ##### 程序功能

   （1）定义半边数据结构；

   （2）基于半边数据结构，实现五个欧拉操作；

   （3）基于欧拉操作，实现扫掠操作；

   （4）将基于欧拉操作、扫掠操作构建的实体模型进行图形显示

2. ##### 运行环境

   win10+VS2019

3. ##### 依赖库

   C/C++标准库、OpenGL

4. ##### 各文件功能

   Vertex.h, Vertex.cpp: 定义顶点数据结构

   HalfEdge.h, HalfEdge.cpp: 定义半边数据结构

   Edge.h, Edge.cpp: 定义边数据结构

   Face.h, Face.cpp: 定义面片数据结构

   Loop.h, Loop.cpp: 定义环数据结构

   Solid.h, Solid.cpp: 定义实体数据结构

   Euler.h, Euler.cpp: 定义欧拉操作及扫穷操作

   MakeSolid.h, MakeSolid.cpp: 使用欧拉操作及扫穷操作构建实体

   main.cpp: 主函数

5. ##### 使用说明

   （1）命令行输入“euler_1g”，基于欧拉操作生成含有一个亏格的立方体

   （2）命令行输入“sweep_1g”，基于扫成操作生成含有一个亏格的实体

   命令行输入“sweep_1g dx dy dz”，基于(dx,dy,dz)的偏移量进行扫成操作生成含有一个亏格的实体

   （3）命令输入“sweep_2g”，基于扫成操作生成含有两个亏格的实体

   命令行输入“sweep_2g dx dy dz”，基于(dx,dy,dz)的偏移量进行扫成操作生成含有两个亏格的实体

   （4）命令行输入“euler_cb”，基于欧拉操作生成实体

   命令行输入“euler_cb num”，基于欧拉操作生成具有num个圆分辨率的拟合圆柱体形成的实体

6. ##### 结果展示

   （1）欧拉操作生成含有一个亏格的立方体

   ![image-20201119144127966](D:\code\cadrc\images\image-20201119144127966.png)

   （2）扫成操作生成的含有一个亏格的实体

   ![image-20201119144401349](D:\code\cadrc\images\image-20201119144401349.png)

   （3）扫成操作生成含有两个亏格的实体

   ![image-20201119144457629](D:\code\cadrc\images\image-20201119144457629.png)

   （4）基于欧拉操作生成具有拟合圆柱体和形成的实体

![image-20201119144646682](D:\code\cadrc\images\image-20201119144646682.png)

![image-20201119144742392](D:\code\cadrc\images\image-20201119144742392.png)