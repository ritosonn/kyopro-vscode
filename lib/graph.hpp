#include<cstdio>
#include<vector>
#include<queue>
#include<functional>
typedef long long weight;
weight const infty = 0x3fffffffffffff;
typedef std::pair<weight,int> edge;
class Graph{
private:
    int numVertex,numEdge;
    std::vector<edge> *adj;
public:
    Graph(int v);
    ~Graph();
    void addEdge(int u,int v,weight w=1LL,bool isDirected=false);
    int getNumVertex();
    int getNumEdge();
    void dijkstra(weight l[],int s,int prev[]=NULL);
    void debugPrint();
    void connectedComponent(bool flag[],int s);
    std::pair<weight,int> farthestPoint(int s);
    weight diameter();
    bool isConnected();
    bool isTree();
};

//Graph g(v) ... make a new 0-indexed graph with v vertex.
Graph::Graph(int v){
    numVertex=v;
    numEdge=0;
    adj=new std::vector<edge>[v];
}

//destructor
Graph::~Graph(){
    delete[] adj;
}

int Graph::getNumEdge(){
    return numEdge;
}

int Graph::getNumVertex(){
    return numVertex;
}

// add u->v (or u-v) edge with weight w
void Graph::addEdge(int u,int v,weight w,bool isDirected){
    adj[u].push_back({w,v});
    numEdge++;
    if(!isDirected){
        adj[v].push_back({w,u});
        numEdge++;
    }
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

void Graph::connectedComponent(bool flag[],int s){
    for(int i=0;i<numVertex;i++)flag[i]=false;
    std::queue<int> q;
    q.push(s);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        flag[v]=true;
        for(auto i=adj[v].begin();i!=adj[v].end();i++){
            if(!flag[(*i).second]){
                flag[(*i).second]=true;
                q.push((*i).second);
            }
        }
    }
}

bool Graph::isConnected(){
    bool *flag=new bool[numVertex];
    connectedComponent(flag,0);
    for(int i=0;i<numVertex;i++){
        if(!flag[i])return false;
    }
    return true;
}

// farthest point of tree
std::pair<weight,int> Graph::farthestPoint(int s){
    std::queue<int> q;
    weight *ws=new weight[numVertex];
    for(int i=0;i<numVertex;i++)ws[i]=0;
    q.push(s);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto i=adj[v].begin();i!=adj[v].end();i++){
            if(ws[(*i).second]==0){
                ws[(*i).second]=ws[v]+(*i).first;
                q.push((*i).second);
            }
        }
    };
    int v=0;
    weight w=ws[0]; 
    for(int i=1;i<=numVertex;i++){
        if(w<ws[i]){
            v=i;
            w=ws[i];
        }
    }
    delete[] ws;
    return {w,v};
}

weight Graph::diameter(){
    std::pair<weight,int> p=farthestPoint(0),q=farthestPoint(p.second);
    return q.first;
}

//------------ for debug ------------
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