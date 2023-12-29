/***********************************************************
* 版权所有 (C)2023, HsichingChang
* 
* 文件名称： Graph.h
* 文件标识：无
* 内容摘要：定义了图的结构和相关操作的声明
* 其它说明：无
* 当前版本： V1.0
* 作   者：张喜庆
* 完成日期： 20231228
* 
* 修改记录1：
* 修改日期： 20231228
* 版本号： V1.0
* 修改人： 张喜庆
* 修改内容：创建图的头文件
**********************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include <vector>
#include <queue>

class Graph {
public:
    std::vector<Vertex> vertices;
    Graph();
    void addVertex(const std::string& name, const std::string& description);
    void addEdge(int from, int to, int distance);
    void detectCycle();
    void printCycle(std::vector<int>& parent, int start);
    void findShortestPath(int start, int end);
    void displayAdjacencyMatrix();
    void displayTourRoute();
    void findMinimumSpanningTree();
    void displayVerticesInfo();

private:
    bool detectCycleUtil(int v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cyclePath);
    void printPath(std::vector<int>& parent, int start, int end);
    void DFSUtil(int v, std::vector<bool>& visited);
};

#endif // GRAPH_H
