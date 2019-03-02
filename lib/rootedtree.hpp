//根つき木
#include<vector>
#include<cstdio>
class RootedTree{
private:
    int numVertex;
    int *parent, *depth, *height;
    std::vector<int> *child;
public:
    RootedTree(int v);
    ~RootedTree();
    void addEdge(int p,int c);
    void printData();
    void printData(int v);
    bool isRoot(int v);
    bool isLeaf(int v);
    void computeDepth(int v);
    void computeDepth();
    void computeHeight(int v);
    void computeHeight();
    std::vector<int> sibling(int v);
    void init();
    void dfs(int v);
};
RootedTree::RootedTree(int v){
    numVertex=v;
    parent=new int[v];
    for(int i=0;i<v;i++)parent[i]=-1;
    depth=new int[v];
    for(int i=0;i<v;i++)depth[i]=-1;
    height=new int[v];
    child=new std::vector<int>[v];
}
RootedTree::~RootedTree(){
    delete[] parent;
    delete[] child;
}
void RootedTree::addEdge(int p,int c){
    parent[c]=p;
    child[p].push_back(c);
}
bool RootedTree::isRoot(int v){
    return parent[v]==-1;
}
bool RootedTree::isLeaf(int v){
    return child[v].empty();
}
void RootedTree::computeDepth(){
    for(int i=0;i<numVertex;i++){
        if(isRoot(i))computeDepth(i);
    }
}
void RootedTree::computeDepth(int v){
    if(isRoot(v))depth[v]=0;
    for(auto itr=child[v].begin();itr!=child[v].end();itr++){
        depth[*itr]=depth[v]+1;
        computeDepth(*itr);
    }
}
void RootedTree::computeHeight(){
    for(int i=0;i<numVertex;i++){
        if(isRoot(i))computeHeight(i);
    }
}
void RootedTree::computeHeight(int v){
    height[v]=0;
    if(!isLeaf(v)){
        for(auto itr=child[v].begin();itr!=child[v].end();itr++){
            computeHeight(*itr);
            if(height[v]<=height[*itr])height[v]=height[*itr]+1;
        }
    }
}
std::vector<int> RootedTree::sibling(int v){
    std::vector<int> vec;
    if(isRoot(v))return vec;
    for(auto itr=child[parent[v]].begin();itr!=child[parent[v]].end();itr++){
        if(*itr!=v)vec.push_back(*itr);
    }
    return vec;
}
void RootedTree::printData(int v){
    printf("node %d: ",v);
    printf("parent = %d, ",parent[v]);
    printf("sibling = %d, ",(sibling(v).empty())?-1:sibling(v)[0]);
    printf("depth = %d, ",depth[v]);
    if(isRoot(v))printf("root");
    else if(isLeaf(v))printf("leaf");
    else printf("internal node");
    // printf(", [");
    // for(auto itr=child[v].begin(); itr!=child[v].end(); itr++){
    //     printf("%s%d",(itr==child[v].begin())?"":", ",*itr);
    // }
    printf("\n");
}
void RootedTree::printData(){
    for(int i=0;i<numVertex;i++)printData(i);
}
void RootedTree::dfs(int v){
    //preorder
    for(auto itr=child[v].begin();itr!=child[v].end();itr++)dfs(*itr);
    //postorder
}
void RootedTree::init(){
    for(int i=0;i<numVertex;i++){
        int id,left,right;
        scanf("%d%d%d",&id,&left,&right);
        if(left>=0)addEdge(id,left);
        if(right>=0)addEdge(id,right);
    }
    computeDepth();
    computeHeight();
}