class UnionFind{
private:
    int length;
    //parent[x]=xの親の番号 ............. xに親が存在する場合,
    //parent[x]=-(xを含む集合の要素数) ... xが親である場合
    int *parent;
    int *rank;
public:
    UnionFind(int l);
    ~UnionFind();
    int root(int x);
    void unite(int x,int y);
    bool isSameTree(int x,int y);
    int sizeOf(int x);
    int count();
};
UnionFind::UnionFind(int l){
    length=l;
    parent=new int[l];
    for(int i=0;i<l;i++)parent[i]=-1;
    rank=new int[l];
    for(int i=0;i<l;i++)rank[i]=0;
}
UnionFind::~UnionFind(){
    delete[] parent;
    delete[] rank;
}
int UnionFind::root(int x){
    if(parent[x]<0)return x;
    return parent[x]=root(parent[x]);
}
void UnionFind::unite(int x,int y){
    int rx=root(x),ry=root(y);
    if(rank[rx]>rank[ry]){
        parent[rx]+=parent[ry];
        parent[ry]=rx;
    }
    else if(rank[rx]<rank[ry]){
        parent[ry]+=parent[rx];
        parent[rx]=ry;
    }
    else if(rx!=ry){
        parent[rx]+=parent[ry];
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
int UnionFind::sizeOf(int x){
    return -parent[root(x)];
}