#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

// 定义景点结构体
typedef struct {
    int code;           // 景点代码
    char name[50];      // 景点名称
    char description[200]; // 景点简介
} Vertex;

// 定义顺序表类
typedef struct {
    Vertex vertices[10];  // 最多10个景点
    int vertexCount;
    int edges[10][10];    // 邻接矩阵
} Graph;

// 初始化图
void initGraph(Graph* graph) {
    graph->vertexCount = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            graph->edges[i][j] = INT_MAX; // 初始化为无穷大，表示不相连
        }
    }
}

// 添加景点
void addVertex(Graph* graph, int code, const char* name, const char* description) {
    Vertex v = {code};
    strcpy(v.name, name);
    strcpy(v.description, description);
    graph->vertices[graph->vertexCount++] = v;
}

// 添加路径
void addEdge(Graph* graph, int from, int to, int distance) {
    graph->edges[from][to] = distance;
    graph->edges[to][from] = distance; // 无向图
}

// Dijkstra算法找最短路径
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


// 浏览景点信息
void displayVertexInfo(Graph* graph) {
    printf("\n景点信息如下:\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("景点代码: %d\n", graph->vertices[i].code);
        printf("景点名称: %s\n", graph->vertices[i].name);
        printf("景点简介: %s\n", graph->vertices[i].description);
        printf("-----------------------------\n");
    }
}

int main() {
    Graph graph;
    initGraph(&graph);

    // 添加十个景点
    addVertex(&graph, 0, "图书馆", "这是学校的图书馆");
    addVertex(&graph, 1, "体育馆", "这是学校的体育馆");
    addVertex(&graph, 2, "实验楼", "这是学校的实验楼");
    addVertex(&graph, 3, "食堂", "这是学校的食堂");
    addVertex(&graph, 4, "教学楼A", "这是学校的教学楼A");
    addVertex(&graph, 5, "操场", "这是学校的操场");
    addVertex(&graph, 6, "艺术馆", "这是学校的艺术馆");
    addVertex(&graph, 7, "图像馆", "这是学校的图像馆");
    addVertex(&graph, 8, "行政楼", "这是学校的行政楼");
    addVertex(&graph, 9, "图书馆二楼", "这是学校的图书馆二楼");

    // 添加路径
    addEdge(&graph, 0, 1, 5);
    addEdge(&graph, 0, 2, 7);
    addEdge(&graph, 1, 3, 3);
    addEdge(&graph, 1, 4, 6);
    addEdge(&graph, 2, 5, 4);
    addEdge(&graph, 2, 6, 2);
    addEdge(&graph, 3, 7, 5);
    addEdge(&graph, 4, 8, 8);
    addEdge(&graph, 5, 9, 6);
    addEdge(&graph, 6, 9, 3);
    addEdge(&graph, 7, 8, 4);
    addEdge(&graph, 8, 9, 2);

    int choice;
    while (true) {
        printf("\n校园导航系统\n\n1. 浏览景点信息\n2. 查询最短路径\n3. 退出\n\n请选择: ");
        scanf("%d", &choice);

        int src, dest;
        switch (choice) {
            case 1:
                displayVertexInfo(&graph);
                break;
            case 2:
                printf("请输入起始景点代码: ");
                scanf("%d", &src);
                printf("请输入目标景点代码: ");
                scanf("%d", &dest);
                dijkstra(&graph, src, dest);
                break;
            case 3:
                printf("感谢使用，再见!\n");
                return 0;
            default:
                printf("无效选择，请重新输入。\n");
                break;
        }
    }
    return 0;
}
