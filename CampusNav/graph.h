/*********************************************************** 
* 版权所有 (C)2019, LiuTingting 
* 
* 文件名称： graph.h
* 文件标识：无 
* 内容摘要：定义了图的数据结构及相关操作函数的声明
* 其它说明：无 
* 当前版本： V1.0 
* 作   者：刘婷婷 
* 完成日期： 20231229 
* 
* 修改记录1： 
* 修改日期： 20231229 
* 版本号： V1.0 
* 修改人： 刘婷婷 
* 修改内容：创建 
**********************************************************/ 

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <limits.h>

// 定义景点结构体
typedef struct {
int code; // 景点代码
char name[50]; // 景点名称
char description[200]; // 景点简介
} Vertex;

// 定义图的结构体
typedef struct {
Vertex vertices[10]; // 顶点数组，最多10个景点
int vertexCount; // 当前图中的顶点数量
int edges[10][10]; // 邻接矩阵，表示景点之间的关系
} Graph;

// 初始化图结构
void initGraph(Graph* graph);

// 向图中添加一个景点
void addVertex(Graph* graph, int code, const char* name, const char* description);

// 向图中添加两个景点之间的路径
void addEdge(Graph* graph, int from, int to, int distance);

// 使用Dijkstra算法找到两个景点之间的最短路径
void dijkstra(Graph* graph, int src, int dest);

// 显示图中所有景点的信息
void displayVertexInfo(Graph* graph);

#endif // GRAPH_H
