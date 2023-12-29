/*********************************************************** 
* 版权所有 (C)2019, LiuTingting 
* 
* 文件名称： graph.c
* 文件标识：无 
* 内容摘要：定义了图的相关操作函数的具体实现
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

#include "graph.h"
#include <stdio.h>
#include <string.h>

/********************************************************* 
* 功能描述：初始化图结构
* 输入参数： graph - 指向图的指针
* 输出参数： 无
* 返回值： 无
* 其它说明：初始化图的顶点数和边的权重
************************************************************/ 
void initGraph(Graph* graph) {
    graph->vertexCount = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            graph->edges[i][j] = INT_MAX; // 初始化为无穷大，表示不相连
        }
    }
}

/********************************************************* 
* 功能描述：向图中添加一个景点
* 输入参数： graph - 指向图的指针
            code - 景点代码
            name - 景点名称
            description - 景点描述
* 输出参数： 无
* 返回值： 无
* 其它说明：将新的景点信息添加到图的顶点数组中
************************************************************/ 
void addVertex(Graph* graph, int code, const char* name, const char* description) {
    Vertex v = {code};
    strcpy(v.name, name);
    strcpy(v.description, description);
    graph->vertices[graph->vertexCount++] = v;
}

/********************************************************* 
* 功能描述：向图中添加两个景点之间的路径
* 输入参数： graph - 指向图的指针
            from - 起始景点代码
            to - 终点景点代码
            distance - 两景点之间的距离
* 输出参数： 无
* 返回值： 无
* 其它说明：在图的边缘矩阵中设置两个景点之间的权重
************************************************************/ 
void addEdge(Graph* graph, int from, int to, int distance) {
    graph->edges[from][to] = distance;
    graph->edges[to][from] = distance; // 无向图
}

/********************************************************* 
* 功能描述：使用Dijkstra算法找到两个景点之间的最短路径
* 输入参数： graph - 指向图的指针
            src - 起始景点代码
            dest - 终点景点代码
* 输出参数： 无
* 返回值： 无
* 其它说明：计算最短路径并打印出路径和长度
************************************************************/ 
void dijkstra(Graph* graph, int src, int dest) {
    int dist[10];
    int parent[10];  // 用于存储路径上的前驱顶点
    bool visited[10] = {false};

    for (int i = 0; i < 10; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;  // 初始化前驱顶点为-1
    }

    dist[src] = 0;

    for (int count = 0; count < 10 - 1; count++) {
        int u = -1;
        for (int v = 0; v < 10; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = true;

        for (int v = 0; v < 10; v++) {
            if (!visited[v] && graph->edges[u][v] != INT_MAX && dist[u] + graph->edges[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->edges[u][v];
                parent[v] = u;  // 更新v的前驱顶点为u
            }
        }
    }

    // 输出最短路径长度
    printf("最短路径长度为: %d\n", dist[dest]);

    // 输出最短路径
    printf("最短路径为: ");
    int path[10];
    int pathLength = 0;
    int current = dest;
    while (current != -1) {
        path[pathLength++] = current;
        current = parent[current];
    }

    // 从后向前打印路径
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%s", graph->vertices[path[i]].name);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}

/********************************************************* 
* 功能描述：显示图中所有景点的信息
* 输入参数： graph - 指向图的指针
* 输出参数： 无
* 返回值： 无
* 其它说明：遍历并打印图中所有景点的详细信息
************************************************************/ 
void displayVertexInfo(Graph* graph) {
    printf("\n景点信息如下:\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("景点代码: %d\n", graph->vertices[i].code);
        printf("景点名称: %s\n", graph->vertices[i].name);
        printf("景点简介: %s\n", graph->vertices[i].description);
        printf("-----------------------------\n");
    }
}
