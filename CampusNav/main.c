/*********************************************************** 
* 版权所有 (C)2019, LiuTingting 
* 
* 文件名称： main.c
* 文件标识：无 
* 内容摘要：主程序入口，用于展示校园导航系统功能
* 其它说明：包含图结构的相关操作和用户交互功能
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

#include <stdio.h>
#include "graph.h"

/********************************************************* 
* 功能描述：主程序入口，用于展示校园导航系统功能
* 输入参数： graph - 指向图的指针
* 输出参数： 无
* 返回值： 0 - 成功退出
* 其它说明：主要调用图结构中的函数来展示不同的功能
************************************************************/ 
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
                printf("\n感谢使用，再见!\n");
                return 0;
            default:
                printf("\n无效选择，请重新输入。\n");
                break;
        }
    }
    return 0;
}
