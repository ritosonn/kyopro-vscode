#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_set>
long long const infty = 0x3fffffffffffff;
struct edge{
    long long weight;
    int to,rev;
};
//隣接リスト表現
class Graph{
protected:
    int numVertex,numEdge;
    std::vector<edge> *adj;
public:
    //---基本---

    //v頂点のグラフを作成する（頂点の番号は0-indexed）
    Graph(int v){
        numVertex=v;
        numEdge=0;
        adj=new std::vector<edge>[v];
    }
    ~Graph(){ delete[] adj; }
    int getNumVertex(){ return numVertex; }
    int getNumEdge(){ return numEdge; }
    void addEdge(int u,int v,long long w=1LL){
        adj[u].push_back({w,v,-1});
        numEdge++;
    }
    //フロー計算用の有向辺+逆辺の追加
    void addNetwork(int u,int v,long long w=1LL){
        adj[u].push_back({w,v,(int)adj[v].size()});
        adj[v].push_back({0,u,(int)adj[u].size()-1});
        numEdge++;
    }

    //---一般のグラフに使えるアルゴリズム---

    //ダイクストラ法（単一頂点を始点とする最短経路）O(E+VlogV)
    //制約 : weight>=0
    void shortestPath_Dijkstra(long long l[],int s,int prev[]=NULL){
        for(int i=0;i<numVertex;i++)l[i]=infty;
        if(prev!=NULL)for(int i=0;i<numVertex;i++)prev[i]=-1;
        l[s]=0;
        auto cmp=[](const edge &a,const edge &b)->bool { return a.weight>b.weight; };
        std::priority_queue<edge,std::vector<edge>,decltype(cmp)> pq(cmp);
        pq.push({0,s,-1});
        while(!pq.empty()){
            int u=pq.top().to;
            pq.pop();
            for(auto i=adj[u].begin();i!=adj[u].end();i++){
                int v=(*i).to;
                long long w=(*i).weight;
                if(l[v]>l[u]+w){
                    l[v]=l[u]+w;
                    if(prev!=NULL)prev[v]=u;
                    pq.push({l[v],v,-1});
                }
            }
        }
    }

    //sと同じ連結成分にある頂点集合を返す
    std::unordered_set<int> isSameComponent(int s){
        std::queue<int> q;
        std::unordered_set<int> ans;
        q.push(s);
        while(!q.empty()){
            int v=q.front();
            ans.emplace(v);
            q.pop();
            for(auto i=adj[v].begin();i!=adj[v].end();i++){
                int w=(*i).to;
                q.push(w);
            }
        }
        return ans;
    }
    bool isConnected(){
        return isSameComponent(0).size()==numVertex;
    }
    bool isTree(){
        return isConnected()&&(numEdge+1==numVertex);
    }
    
private:
    //vからtへの増加パスをdfsで探す
    //fは流量の上界のうち現時点で判明している最小のもの
    long long dfs_Ford_fulkerson(int v,int t,long long f,bool* used){
        //始点と終点が一致していれば無限に流せる
        if(v==t)return f;
        used[v]=true;
        //vから出る各辺eに対して、
        for(auto itr=adj[v].begin();itr!=adj[v].end();itr++){
            edge e=*itr;
            //e.toにまだ訪問したことがなく、さらに流せるとき
            if(!used[e.to]&&e.weight>0){
                //e.toから終点tまで流せる量を取得する
                //流量の上界は、eで流せる量でも上から抑えられる
                long long d = dfs_Ford_fulkerson(e.to, t, std::min(f,e.weight), used);
                //もし流せるなら
                if(d>0){
                    //dだけ逆流させればvからtにもd流せる
                    itr->weight-=d;
                    adj[e.to][e.rev].weight+=d;
                    return d;
                }
            }
        }
        //どこも訪問済みか流せる量がないときは0
        return 0;
    }
public:
    //最大流 O(E*(最大流の流量))
    long long maxFlow_Ford_Fulkerson(int s,int t){
        bool *used=new bool[numVertex];
        long long flow=0;
        while(true){
            for(int i=0;i<numVertex;i++)used[i]=false;
            long long f=dfs_Ford_fulkerson(s,t,infty,used);
            if(f==0)return flow;
            flow+=f;
        }
    }

    //----debug----

    void debugPrint(){
        printf("numEdge: %d\n",numEdge);
        printf("numVertex: %d\n",numVertex);
        printf("isConnected: %s\n",isConnected()?"True":"False");
        printf("isTree: %s\n",isTree()?"True":"False");
        printf("EdgeList:\n");
        for(int i=0;i<numVertex;i++){
            printf("%6d: ",i);
            for(auto itr=adj[i].begin();itr!=adj[i].end();itr++){
                printf("(%d->%d:%lld)",i,(*itr).to,(*itr).weight);
            }
            printf("\n");
        }
    }
};