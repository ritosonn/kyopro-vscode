class UnionFind{
private:
    int length;
    int *parent;
    int *rank;
public:
    UnionFind(int l);
    ~UnionFind();
    int root(int x);
    void unite(int x,int y);
    bool isSameTree(int x,int y);
    int count();
};
UnionFind::UnionFind(int l){
    length=l;
    parent=new int[l];
    for(int i=0;i<l;i++)parent[i]=i;
    rank=new int[l];
    for(int i=0;i<l;i++)rank[i]=0;
}
UnionFind::~UnionFind(){
    delete[] parent;
}
int UnionFind::root(int x){
    if(parent[x]==x)return x;
    return parent[x]=root(parent[x]);
}
void UnionFind::unite(int x,int y){
    int rx=root(x),ry=root(y);
    if(rank[rx]>rank[ry])parent[ry]=rx;
    else if(rank[rx]<rank[ry])parent[rx]=ry;
    else if(rx!=ry){
        parent[ry]=rx;
        rank[rx]+=1;
    }
}
bool UnionFind::isSameTree(int x,int y){
    return root(x)==root(y);
}
int UnionFind::count(){
    int *tmp=new int[length];
    for(int i=0;i<length;i++)tmp[i]=0;
    for(int i=0;i<length;i++)tmp[root(i)]=1;
    int ans=0;
    for(int i=0;i<length;i++)ans+=tmp[i];
    return ans;
}