//姓名：胡光辉
//学号：120L052208

//作业1.3
//题目：在有n个选手P1,P2......Pn 参加的单循环赛中，每对选手之间非胜即负。现要求求出一个选手序列:P1',P2'......Pn'其满足Pi'胜Pi+1'(i=1,... ,n-1)
//输入：先键入n代表选手数目，然后键入n*(n-1)/2个有序数对（x,y），代表着在该场比赛中Px胜Py
//      例: 4
//        1 2
//        1 3
//        2 3
//        3 4
//        4 1
//        4 2
//输出：1、输入待搜索的100个数，五个为一行，且都保留两位小数
//      2、输出最大值，小数保留两位小数
//编程思路：将各个选手抽象为图的各个顶点，若Pi和Pj两个选手之间的比赛结果满足Pi胜Pj负，则<Pi,Pj>属于A，这样的图是一个有向图D=(V,A)
//          且该有向图满足条件“对任意的i，j均有Pi可达Pj或Pj可达Pi”,这个有向图是一个比赛图。因此要求选手序列则是有向图的一条哈密顿路
//          改编拓扑排序算法，将原算法中的“度为0的顶点”改为“当前可选顶点中度最小的顶点”，这样就可以求出一条哈密顿路
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int mindegree(int n,int p,int id1[50],bool check1[50],int s1[50][50])//实现功能：选择当前可选顶点中度最小的顶点
{
    int i;
    int minp=0;
    for (i=1;i<=n;i++)
    {
        if ((check1[i])||(s1[p][i]==0)) continue;//跳过当前不可选顶点
        if (id1[minp]>id1[i]) minp=i;//在可选顶点中选择度最小的顶点
    }
    return minp;
}
int main()
{
    bool check[50];//判断该顶点是否被选择
    int s[50][50];//邻接矩阵
    int id[50];
    int i,j,n,num,a,b,p;
    scanf("%d",&n);
//以下部分为邻接矩阵和入度出度的初始化
    for (i=0;i<=n*n;i++)
    {
        if (i==0)
            for (j=1;j<=n;j++)
            s[i][j]=1;
        else for (j=1;j<=n;j++)
            s[i][j]=0;
        id[i]=0;
        check[i]=false;
    }
    id[0]=n;//假设一个P0顶点与所有顶点邻接
//以下部分为比赛结果的输入
    for (i=1;i<=(n*(n-1))/2;i++)
    {

        scanf("%d %d",&a,&b);
        s[a][b]=1;
        id[b]=id[b]+1;
    }
//以下为寻找哈密顿路
    num=0;//记录选择的定点数
    p=0;//记录选择的当前顶点
    do
    {
        p=mindegree(n,p,id,check,s);
        check[p]=true;
        num=num+1;
        for (i=1;i<=n;i++)
        {
            if (s[p][i]==1)
                {
                   id[i]=id[i]-1;
                }
        }
        if (num==n) printf("%d",p);
        else printf("%d->",p);
    }while(num<n);
    return 0;
}
