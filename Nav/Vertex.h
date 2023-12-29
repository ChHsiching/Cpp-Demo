/***********************************************************
* 版权所有 (C)2023, HsichingChang
* 
* 文件名称： TouristInformationSystem.cpp
* 文件标识：无
* 内容摘要：定义了图中顶点的结构和相关操作的声明
* 其它说明：无
* 当前版本： V1.0
* 作   者：张喜庆
* 完成日期： 20231228
* 
* 修改记录1：
* 修改日期： 20231228
* 版本号： V1.0
* 修改人： 张喜庆
* 修改内容：创建顶点的头文件
**********************************************************/
#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>

// 定义图中的顶点结构
struct Vertex {
    std::string name;                         // 顶点名称
    std::string description;                  // 顶点描述或简介
    std::vector<std::pair<int, int>> edges;     // 与其他顶点相邻的边的列表，存储格式为<目标顶点索引, 边的权重>
};

#endif // VERTEX_H
