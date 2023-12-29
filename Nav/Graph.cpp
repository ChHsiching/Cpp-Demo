/***********************************************************
* 版权所有 (C)2023, HsichingChang
* 
* 文件名称： Graph.cpp
* 文件标识：无
* 内容摘要：实现了图的相关操作
* 其它说明：无
* 当前版本： V1.0
* 作   者：张喜庆
* 完成日期： 20231228
* 
* 修改记录1：
* 修改日期： 20231228
* 版本号： V1.0
* 修改人： 张喜庆
* 修改内容：创建图的实现文件
**********************************************************/
#include "Graph.h"
#include <iostream>
#include <climits>
#include <algorithm>

std::vector<Vertex> vertices;             // 存储图中的所有顶点
// 默认构造函数，初始化图中的顶点和边
Graph::Graph() {
    // 预定义景点分布图
    // 初始化15个景点
    // for (int i = 0; i < 15; ++i) {
    //     addVertex("景点" + to_string(i + 1), "预定义-第"  + to_string(i + 1) + "个景点");
    // }
    // 添加顶点间的边和权重，创建图结构
    // addEdge(0, 1, 5);
    // addEdge(1, 2, 3);
    // addEdge(2, 3, 4);
    // addEdge(3, 4, 2);
    // addEdge(4, 0, 7);
    // addEdge(5, 6, 6);
    // addEdge(6, 7, 5);
    // addEdge(7, 8, 4);
    // addEdge(8, 9, 3);
    // addEdge(9, 5, 2);
    // addEdge(10, 11, 4);
    // addEdge(11, 12, 3);
    // addEdge(12, 13, 5);=-
    // addEdge(13, 14, 6);
    // addEdge(14, 10, 7);
    // addEdge(2, 5, 1);
    // addEdge(6, 10, 2);
    // addEdge(9, 12, 3);
    // addEdge(13, 3, 4);
    // addEdge(8, 14, 5);
}

/********************************************************* 
* 功能描述：添加一个新的顶点到图中 
* 输入参数： name-顶点名称 
             description-顶点描述 
* 输出参数： 无
* 返回值： 无
* 其它说明：无
************************************************************/
void Graph::addVertex(const std::string& name, const std::string& description) {
    vertices.push_back({name, description, {}});
}

/********************************************************* 
* 功能描述：添加一条从一个顶点到另一个顶点的边，并指定权重 
* 输入参数： from-起始顶点索引 
             to-目标顶点索引 
             distance-边的权重
* 输出参数： 无
* 返回值： 无
* 其它说明：无
************************************************************/
void Graph::addEdge(int from, int to, int distance) {
    vertices[from].edges.push_back({to, distance});  // 从from到to的权重设置为distance
    vertices[to].edges.push_back({from, distance});  // 从to到from的权重设置为distance，因为这是一个无向图
}

/********************************************************* 
* 功能描述：检测图中是否存在环 
* 输入参数： 无
* 输出参数： 无
* 返回值： 无
* 其它说明：无
************************************************************/
void Graph::detectCycle() {
    // 初始化访问标记和父节点列表
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> parent(vertices.size(), -1);
    
    for (int i = 0; i < vertices.size(); ++i) {
        if (!visited[i]) {
            std::vector<int> cyclePath;
            if (detectCycleUtil(i, visited, parent, cyclePath)) {
                std::cout << "图中存在回路，路径为: ";
                for (int j = cyclePath.size() - 1; j >= 0; --j) {
                    std::cout << vertices[cyclePath[j]].name;
                    if (j > 0) {
                        std::cout << " -> ";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    std::cout << "图中已无其他回路";
}

/********************************************************* 
* 功能描述：打印从某个顶点开始的回路
* 输入参数： parent-父节点列表 
             start-起始顶点索引
* 输出参数： 无
* 返回值： 无
* 其它说明：无
************************************************************/
void Graph::printCycle(std::vector<int>& parent, int start) {
    int curr = start;
    do {
        std::cout << vertices[curr].name << " -> ";
        curr = parent[curr];
    } while (curr != start);
    
    std::cout << vertices[start].name;
}

/********************************************************* 
* 功能描述：查找从一个顶点到另一个顶点的最短路径和距离 
* 输入参数： start-起始顶点索引 
             end-目标顶点索引
* 输出参数： 无
* 返回值： 无
* 其它说明：无
************************************************************/
void Graph::findShortestPath(int start, int end) {
    // 初始化距离和父节点列表
    std::vector<int> dist(vertices.size(), INT_MAX);
    std::vector<int> parent(vertices.size(), -1);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& [v, w] : vertices[u].edges) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[end] == INT_MAX) {
        std::cout << "从 " << vertices[start].name << " 到 " << vertices[end].name << " 之间没有路径" << std::endl;
        return;
    }

    std::cout << "从 " << vertices[start].name << " 到 " << vertices[end].name << " 的最短路径距离是: " << dist[end] << std::endl;

    // 输出路径时使用景点名称而不是索引
    std::cout << "路径为: " << vertices[start].name;
    printPath(parent, start, end);
    std::cout << std::endl;
}

/*********************************************************
* 功能描述：显示图的邻接矩阵
* 输入参数：无
* 输出参数：无
* 返回值：无
* 其它说明：使用1表示连接，INF表示不连接
************************************************************/
void Graph::displayAdjacencyMatrix() {
    std::cout << "邻接矩阵:" << std::endl;
    for (int i = 0; i < vertices.size(); ++i) {
        std::cout << vertices[i].name << ": ";
        for (int j = 0; j < vertices.size(); ++j) {
            bool connected = false;
            for (const auto& [v, _] : vertices[i].edges) {
                if (v == j) {
                    connected = true;
                    break;
                }
            }
            if (connected) {
                 std::cout << " 1   ";
            } else {
                std::cout << " INF ";
            }
        }
        std::cout << std::endl;
    }
}

/*********************************************************
* 功能描述：深度优先搜索遍历图并输出导游线路
* 输入参数：v-当前顶点，visited-标记访问过的顶点的数组
* 输出参数：无
* 返回值：无
* 其它说明：无
************************************************************/
void Graph::DFSUtil(int v, std::vector<bool>& visited) {
    visited[v] = true;
    std::cout << vertices[v].name << " -> ";  // 输出访问的景点名称
    for (const auto& [adj, _] : vertices[v].edges) {
        if (!visited[adj]) {
            DFSUtil(adj, visited);
        }
    }
}

/*********************************************************
* 功能描述：显示导游线路图
* 输入参数：无
* 输出参数：无
* 返回值：无
* 其它说明：使用DFS进行遍历
************************************************************/
void Graph::displayTourRoute() {
    std::cout << "导游线路图 (DFS遍历):" << std::endl;
    std::vector<bool> visited(vertices.size(), false);

    // 从第一个顶点开始进行DFS遍历
    for (int i = 0; i < vertices.size(); ++i) {
        if (!visited[i]) {
            DFSUtil(i, visited);
        }
    }
    std::cout << "结束" << std::endl;
}
    
/*********************************************************
* 功能描述：使用Prim算法查找最小生成树并输出道路修建规划图
* 输入参数：无
* 输出参数：无
* 返回值：无
* 其它说明：使用优先队列和最小堆进行操作
************************************************************/
void Graph::findMinimumSpanningTree() {
    // 使用优先队列选择具有最小权重的边
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq;

    // 从第一个顶点（或任何顶点）开始
    std::vector<bool> visited(vertices.size(), false);
    int startVertex = 0; // Start with vertex 0
    visited[startVertex] = true;

    // 将起始顶点的所有边添加到优先队列
    for (const auto& [to, weight] : vertices[startVertex].edges) {
        pq.push({weight, {startVertex, to}});
    }

    std::cout << "道路修建规划图 (最小生成树):" << std::endl;
    std::cout << "边   : 权重" << std::endl;

    while (!pq.empty()) {
        int weight = pq.top().first;
        int from = pq.top().second.first;
        int to = pq.top().second.second;
        pq.pop();

        if (visited[to]) {
            continue;
        }

        // 将顶点标记为已访问
        visited[to] = true;

        // 输出边(from, to)及其权重
        std::cout << vertices[from].name << " - " << vertices[to].name << " : " << weight << std::endl;

        // 将“to”中连接未访问顶点的所有边添加到优先队列
        for (const auto& [nextTo, nextWeight] : vertices[to].edges) {
            if (!visited[nextTo]) {
                pq.push({nextWeight, {to, nextTo}});
            }
        }
    }
}

/*********************************************************
* 功能描述：检测是否存在环的递归辅助函数
* 输入参数：v-当前顶点，visited-标记访问过的顶点的数组，
*           parent-父节点数组，cyclePath-当前路径数组
* 输出参数：无
* 返回值：存在环返回true，否则返回false
* 其它说明：使用深度优先搜索进行检测
************************************************************/
bool Graph::detectCycleUtil(int v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cyclePath) {
    visited[v] = true;
    cyclePath.push_back(v);
    
    for (const auto& [adj, _] : vertices[v].edges) {
        if (!visited[adj]) {
            parent[adj] = v;
            if (detectCycleUtil(adj, visited, parent, cyclePath)) {
                return true;
            }
        } else if (adj != parent[v] && find(cyclePath.begin(), cyclePath.end(), adj) != cyclePath.end()) {
            // Found a back edge which indicates a cycle
            cyclePath.push_back(adj);
            return true;
        }
    } 
    cyclePath.pop_back();
    return false;
}

/*********************************************************
* 功能描述：从起点到终点打印路径
* 输入参数：parent-父节点数组，start-起点，end-终点
* 输出参数：无
* 返回值：无
* 其它说明：输出路径上的景点名称
************************************************************/
void Graph::printPath(std::vector<int>& parent, int start, int end) {
    if (end == start) {
        return;
    }
    printPath(parent, start, parent[end]);
    std::cout << " -> " << vertices[end].name;  // 输出景点名称
}

/*********************************************************
* 功能描述：显示所有景点的信息
* 输入参数：无
* 输出参数：无
* 返回值：无
* 其它说明：输出景点的名称、简介等信息
************************************************************/
void Graph::displayVerticesInfo() {
    std::cout << "景点信息如下:" << std::endl;
    for (int i = 0; i < vertices.size(); ++i) {
        std::cout << "景点代码: " << i + 1 << std::endl;
        std::cout << "景点名称: " << vertices[i].name << std::endl;
        std::cout << "景点简介: " << vertices[i].description << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}
