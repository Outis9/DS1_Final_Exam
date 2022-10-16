#include <iostream>
#include <string>
using namespace std;

const int MaxN = 10000;
int parent[MaxN];
bool Diff[MaxN][MaxN];

// 初始化
void Init(int n){
    for (int x = 1; x <= n; x++){
        parent[x] = x;      // 自己是自己的父亲结点
    }
}

//找根节点
int find(int x){
    if (x == parent[x]) return x;
    parent[x] = find(parent[x]);    //路径压缩
    return parent[x];               //返回父节点
}

//合并
void union_merge(int x,int y){
    int fx = find(x);   //x所在集合的根节点
    int fy = find(y);
    if (fx != fy)   parent[fx] = fy ;   //fx的父亲指向fy的父亲
}



int main() {
    std::freopen(R"(D:\GitHubFiles\DS1FinalProject\virus0.in)","r",stdin);
    int N,M;
    cin>>N>>M;
    Init(N);        //初始化
    for (int i = 1; i <= M; i++) {
        char c ;
        int p,q;
        cin>>c>>p>>q;
        if (c == 'S') union_merge(p,q);     //如果是同类直接合并
        else{                               //否则是不同类
            Diff[p][q] = Diff[q][p] = true; //标记不同类
            for (int j = 1; j <= N; j++) {
                if (Diff[p][j]) union_merge(q,j);
                else if (Diff[q][j]) union_merge(p,j);
            }
        }
    }
    int count = 0;
    for(int i = 1;i <= N;i++)   if(parent[i] == i)  count++;
    std::freopen(R"(D:\GitHubFiles\DS1FinalProject\virus0.out)","w",stdout);
    cout<<count;
    return 0;
}

