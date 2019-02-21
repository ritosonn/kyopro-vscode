#include<cstdio>
#include<vector>
#include<queue>
#include<functional>
typedef long long weight;
weight const infty = 0x3fffffffffffff;
typedef std::pair<weight,int> edge;
class Graph{
private:
    int numVertex;
    std::vector<edge> *adj;
public:
    Graph(int v);
    ~Graph();
    void addEdge(int u,int v,weight w=1LL,bool isDirected=false);
    int getNumVertex();
    void dijkstra(weight l[],int s,int prev[]=NULL);
    void debugPrint();
};

//Graph g(v) ... make a new 0-indexed graph with v vertex.
Graph::Graph(int v){
    this->numVertex=v;
    this->adj=new std::vector<edge>[v];
}

//destructor
Graph::~Graph(){
    delete[] adj;
}

// add u->v (or u-v) edge with weight w
void Graph::addEdge(int u,int v,weight w,bool isDirected){
    adj[u].push_back({w,v});
    if(!isDirected)adj[v].push_back({w,u});
}

// shortest path length, O(E+VlogV)
void Graph::dijkstra(weight l[],int s,int prev[]){
    for(int i=0;i<numVertex;i++)l[i]=infty;
    if(prev!=NULL)for(int i=0;i<numVertex;i++)prev[i]=-1;
    l[s]=0;
    std::priority_queue<edge,std::vector<edge>,std::greater<edge>> pq;
    pq.push({0,s});
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        for(auto i=adj[u].begin();i!=adj[u].end();i++){
            int v=(*i).second;
            weight w=(*i).first;
            if(l[v]>l[u]+w){
                l[v]=l[u]+w;
                if(prev!=NULL)prev[v]=u;
                pq.push({l[v],v});
            }
        }
    }
}

void Graph::debugPrint(){
    printf("numVertex: %d\n",numVertex);
    for(int i=0;i<numVertex;i++){
        printf("%4d: ",i);
        for(auto itr=adj[i].begin();itr!=adj[i].end();itr++){
            printf("(%d->%d:%lld)",i,(*itr).second,(*itr).first);
        }
        printf("\n");
    }
}