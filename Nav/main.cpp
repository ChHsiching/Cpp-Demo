/***********************************************************
* 版权所有 (C)2023, HsichingChang
* 
* 文件名称： main.cpp
* 文件标识：无
* 内容摘要：程序的主入口，用户交互逻辑
* 其它说明：无
* 当前版本： V1.0
* 作   者：张喜庆
* 完成日期： 20231228
* 
* 修改记录1：
* 修改日期： 20231228
* 版本号： V1.0
* 修改人： 张喜庆
* 修改内容：创建程序的主入口文件
**********************************************************/
#include <iostream>
#include <limits>
#include "Graph.h"

using namespace std;

void displayMenu();

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
                if (!(cin >> start) || start < 0 || start >= g.vertices.size()) {
                    cout << "无效的输入，请重新输入有效的起始景点索引。" << endl;
                    cin.clear();  // 清除错误标志
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略缓冲区中的无效字符
                    continue;  // 返回到菜单选择
                }
                cout << "请输入目标景点的索引：";
                // cin >> end;
                if (!(cin >> end) || end < 0 || end >= g.vertices.size() + 1) {
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