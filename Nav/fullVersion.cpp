/***********************************************************
* 版权所有 (C)2023, HsichingChang
* 
* 文件名称： TouristInformationSystem.cpp
* 文件标识：无
* 内容摘要：实现景区旅游信息管理系统
* 其它说明：无
* 当前版本： V1.0
* 作   者：张喜庆
* 完成日期： 20231228
* 
* 修改记录1：
* 修改日期： 20231228
* 版本号： V1.0
* 修改人： 张喜庆
* 修改内容：创建
**********************************************************/

#include <iostream>
#include <limits>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// 定义图中的顶点结构
struct Vertex {
    string name;                         // 顶点名称
    string description;                  // 顶点描述或简介
    vector<pair<int, int>> edges;        // 与其他顶点相邻的边的列表，存储格式为<目标顶点索引, 边的权重>
};

// 定义图的类
class Graph {
public:
    vector<Vertex> vertices;             // 存储图中的所有顶点
    // 默认构造函数，初始化图中的顶点和边
    Graph() {
        // 预定义景点分布图
        // 初始化15个景点
        for (int i = 0; i < 15; ++i) {
            addVertex("景点" + to_string(i + 1), "预定义-第"  + to_string(i + 1) + "个景点");
        }
        // 添加顶点间的边和权重，创建图结构
        addEdge(0, 1, 5);
        addEdge(1, 2, 3);
        addEdge(2, 3, 4);
        addEdge(3, 4, 2);
        addEdge(4, 0, 7);
        addEdge(5, 6, 6);
        addEdge(6, 7, 5);
        addEdge(7, 8, 4);
        addEdge(8, 9, 3);
        addEdge(9, 5, 2);
        addEdge(10, 11, 4);
        addEdge(11, 12, 3);
        addEdge(12, 13, 5);
        addEdge(13, 14, 6);
        addEdge(14, 10, 7);
        addEdge(2, 5, 1);
        addEdge(6, 10, 2);
        addEdge(9, 12, 3);
        addEdge(13, 3, 4);
        addEdge(8, 14, 5);
    }

    /********************************************************* 
    * 功能描述：添加一个新的顶点到图中 
    * 输入参数： name-顶点名称 
                 description-顶点描述 
    * 输出参数： 无
    * 返回值： 无
    * 其它说明：无
    ************************************************************/
    void addVertex(const string& name, const string& description) {
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
    void addEdge(int from, int to, int distance) {
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
    void detectCycle() {
        // 初始化访问标记和父节点列表
        vector<bool> visited(vertices.size(), false);
        vector<int> parent(vertices.size(), -1);
        
        for (int i = 0; i < vertices.size(); ++i) {
            if (!visited[i]) {
                vector<int> cyclePath;
                if (detectCycleUtil(i, visited, parent, cyclePath)) {
                    cout << "图中存在环，路径为: ";
                    for (int j = cyclePath.size() - 1; j >= 0; --j) {
                        cout << vertices[cyclePath[j]].name;
                        if (j > 0) {
                            cout << " -> ";
                        }
                    }
                    cout << endl;
                }
            }
        }
    }

    /********************************************************* 
    * 功能描述：打印从某个顶点开始的环 
    * 输入参数： parent-父节点列表 
                 start-起始顶点索引
    * 输出参数： 无
    * 返回值： 无
    * 其它说明：无
    ************************************************************/
    void printCycle(vector<int>& parent, int start) {
        int curr = start;
        do {
            cout << vertices[curr].name << " -> ";
            curr = parent[curr];
        } while (curr != start);
        
        cout << vertices[start].name;
    }

    /********************************************************* 
    * 功能描述：查找从一个顶点到另一个顶点的最短路径和距离 
    * 输入参数： start-起始顶点索引 
                 end-目标顶点索引
    * 输出参数： 无
    * 返回值： 无
    * 其它说明：无
    ************************************************************/
    void findShortestPath(int start, int end) {
        // 初始化距离和父节点列表
        vector<int> dist(vertices.size(), INT_MAX);
        vector<int> parent(vertices.size(), -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
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
            cout << "从 " << vertices[start].name << " 到 " << vertices[end].name << " 之间没有路径" << endl;
            return;
        }

        cout << "从 " << vertices[start].name << " 到 " << vertices[end].name << " 的最短路径距离是: " << dist[end] << endl;

        // 输出路径时使用景点名称而不是索引
        cout << "路径为: " << vertices[start].name;
        printPath(parent, start, end);
        cout << endl;
    }

    /*********************************************************
    * 功能描述：显示图的邻接矩阵
    * 输入参数：无
    * 输出参数：无
    * 返回值：无
    * 其它说明：使用1表示连接，INF表示不连接
    ************************************************************/
    void displayAdjacencyMatrix() {
        cout << "邻接矩阵:" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << vertices[i].name << ": ";
            for (int j = 0; j < vertices.size(); ++j) {
                bool connected = false;
                for (const auto& [v, _] : vertices[i].edges) {
                    if (v == j) {
                        connected = true;
                        break;
                    }
                }
                if (connected) cout << " 1   ";
                else cout << " INF ";
            }
            cout << endl;
        }
    }

    

    /*********************************************************
    * 功能描述：显示导游线路图
    * 输入参数：无
    * 输出参数：无
    * 返回值：无
    * 其它说明：使用DFS进行遍历
    ************************************************************/
    void displayTourRoute() {
        cout << "导游线路图 (DFS遍历):" << endl;
        vector<bool> visited(vertices.size(), false);

        // 从第一个顶点开始进行DFS遍历
        for (int i = 0; i < vertices.size(); ++i) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
        cout << "结束" << endl;
    }
    
    /*********************************************************
    * 功能描述：使用Prim算法查找最小生成树并输出道路修建规划图
    * 输入参数：无
    * 输出参数：无
    * 返回值：无
    * 其它说明：使用优先队列和最小堆进行操作
    ************************************************************/
    void findMinimumSpanningTree() {
        // 使用优先队列选择具有最小权重的边
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        // 从第一个顶点（或任何顶点）开始
        vector<bool> visited(vertices.size(), false);
        int startVertex = 0; // Start with vertex 0
        visited[startVertex] = true;

        // 将起始顶点的所有边添加到优先队列
        for (const auto& [to, weight] : vertices[startVertex].edges) {
            pq.push({weight, {startVertex, to}});
        }

        cout << "道路修建规划图 (最小生成树):" << endl;
        cout << "边   : 权重" << endl;

        while (!pq.empty()) {
            int weight = pq.top().first;
            int from = pq.top().second.first;
            int to = pq.top().second.second;
            pq.pop();

            if (visited[to]) continue;

            // 将顶点标记为已访问
            visited[to] = true;

            // 输出边(from, to)及其权重
            cout << vertices[from].name << " - " << vertices[to].name << " : " << weight << endl;

            // 将“to”中连接未访问顶点的所有边添加到优先队列
            for (const auto& [nextTo, nextWeight] : vertices[to].edges) {
                if (!visited[nextTo]) {
                    pq.push({nextWeight, {to, nextTo}});
                }
            }
        }
    }

    /*********************************************************
    * 功能描述：显示所有景点的信息
    * 输入参数：无
    * 输出参数：无
    * 返回值：无
    * 其它说明：输出景点的名称、简介等信息
    ************************************************************/
    void displayVerticesInfo() {
        cout << "景点信息如下:" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << "景点代码: " << i << endl;
            cout << "景点名称: " << vertices[i].name << endl;
            cout << "景点简介: " << vertices[i].description << endl;
            cout << "-----------------------------" << endl;
        }
    }

private:
    /*********************************************************
    * 功能描述：检测是否存在环的递归辅助函数
    * 输入参数：v-当前顶点，visited-标记访问过的顶点的数组，
    *           parent-父节点数组，cyclePath-当前路径数组
    * 输出参数：无
    * 返回值：存在环返回true，否则返回false
    * 其它说明：使用深度优先搜索进行检测
    ************************************************************/
    bool detectCycleUtil(int v, vector<bool>& visited, vector<int>& parent, vector<int>& cyclePath) {
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
    void printPath(vector<int>& parent, int start, int end) {
        if (end == start) return;
        printPath(parent, start, parent[end]);
        cout << " -> " << vertices[end].name;  // 输出景点名称
    }

    /*********************************************************
    * 功能描述：深度优先搜索遍历图并输出导游线路
    * 输入参数：v-当前顶点，visited-标记访问过的顶点的数组
    * 输出参数：无
    * 返回值：无
    * 其它说明：无
    ************************************************************/
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << vertices[v].name << " -> ";  // 输出访问的景点名称

        for (const auto& [adj, _] : vertices[v].edges) {
            if (!visited[adj]) {
                DFSUtil(adj, visited);
            }
        }
    }
};

/*********************************************************
* 功能描述：显示菜单选项供用户选择操作
* 输入参数：无
* 输出参数：无
* 返回值：无
* 其它说明：显示操作选项供用户选择
************************************************************/
void displayMenu() {
    cout << "\n景区旅游信息管理系统" << endl;
    cout << "1. 创建景区景点分布图" << endl;
    cout << "2. 输出景区景点分布图 (邻接矩阵)" << endl;
    cout << "3. 输出导游线路图" << endl;
    cout << "4. 判断导游线路图有无回路" << endl;
    cout << "5. 求两个景点间的最短路径和最短距离" << endl;
    cout << "6. 输出道路修建规划图" << endl;
    cout << "7. 退出" << endl;
    cout << "请选择操作: ";
}

/*********************************************************
* 功能描述：程序的入口函数，负责菜单显示和用户交互
* 输入参数：无
* 输出参数：无
* 返回值：0-正常退出
* 其它说明：通过菜单选择执行对应的功能
************************************************************/
int main() {
    Graph g;   // 创建图对象

    int choice;  // 存储用户选择的选项
    while (true) {
        displayMenu();  // 显示菜单
        cin >> choice;   // 获取用户的选择

        // 根据用户的选择执行相应的操作
        switch (choice) {
            // 使用预定义景点分布图时
            // case 1:
            //     cout << "已创建景区景点分布图！" << endl;
            //     break;
            case 1:
                int numVertices;
                cout << "请输入要创建的景点数量: ";
                cin >> numVertices;

                for (int i = 0; i < numVertices; ++i) {
                    string vertexName, vertexDescription;
                    cout << "请输入第 " << i + 1 << " 个景点的名称: ";
                    cin >> vertexName;
                    cout << "请输入第 " << i + 1 << " 个景点的简介: ";
                    cin.ignore();  // 清除缓冲区
                    getline(cin, vertexDescription);
                    
                    g.addVertex(vertexName, vertexDescription);
                }
                g.displayVerticesInfo();  // 显示所有景点的信息

                // 输入景点之间的连接边和权重
                int numEdges;
                cout << "请输入景点之间的连接边数量: ";
                cin >> numEdges;

                for (int i = 0; i < numEdges; ++i) {
                    int from, to, weight;
                    cout << "请输入连接的起始景点索引: ";
                    cin >> from;
                    cout << "请输入连接的目标景点索引: ";
                    cin >> to;
                    cout << "请输入连接的权重: ";
                    cin >> weight;

                    --from; // 因为用户输入的索引从1开始，而数组索引从0开始
                    --to;   // 所以减1来得到正确的索引

                    g.addEdge(from, to, weight);
                }

                cout << "景区景点分布图创建完成！" << endl;
                break;
            case 2:
                g.displayVerticesInfo();  // 显示所有景点的信息
                g.displayAdjacencyMatrix();
                break;
            case 3:
                g.displayTourRoute();
                break;
            case 4:
                g.detectCycle();
                break;
            case 5: {
                int start, end;

                cout << "请输入起始景点的索引：";
                // cin >> start;
                if (!(cin >> start) || start < 0 || start >= g.vertices.size() + 1) {
                    cout << "无效的输入，请重新输入有效的起始景点索引。" << endl;
                    cin.clear();  // 清除错误标志
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略缓冲区中的无效字符
                    continue;  // 返回到菜单选择
                }
                cout << "请输入目标景点的索引：";
                // cin >> end;
                if (!(cin >> end) || end < 0 || end >= g.vertices.size() + 1) {
                    cout << g.vertices.size();
                    cout << "无效的输入，请重新输入有效的目标景点索引。" << endl;
                    cin.clear();  // 清除错误标志
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略缓冲区中的无效字符
                    continue;  // 返回到菜单选择
                }
                
                --start;
                --end;

                g.findShortestPath(start, end);
                break;
            }
            case 6:
                g.findMinimumSpanningTree();
                break;
            case 7:
                cout << "感谢使用景区旅游信息管理系统！" << endl;
                return 0;
            default:
                cout << "无效的选择，请重新选择！" << endl;
                break;
        }
    }
    return 0;
}
