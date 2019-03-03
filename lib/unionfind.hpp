class UnionFind{
private:
    int length, numComponent;
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
    int component();
};
UnionFind::UnionFind(int l){
    length=l;
    numComponent=l;
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
    if(rx!=ry){
        numComponent--;
        if(rank[rx]>rank[ry]){
            parent[rx]+=parent[ry];
            parent[ry]=rx;
        }
        else{
            if(rank[rx]==rank[ry])rank[ry]++;
            parent[ry]+=parent[rx];
            parent[rx]=ry;
        }
    }
}
bool UnionFind::isSameTree(int x,int y){
    return root(x)==root(y);
}
int UnionFind::component(){
    return numComponent;
}
int UnionFind::sizeOf(int x){
    return -parent[root(x)];
}