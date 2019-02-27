//一点更新と区間和（あるいは差分をとって区間更新と一点の値）をO(log N)で計算する
class Fenwick{
private:
    int length;
    long long *vec;
public:
    Fenwick(int l);
    ~Fenwick();
    void add(int a,long long x);
    long long sum(int a);
    long long sum(int a,int b);
    long long operator[](int i);
    void init();
    void set(int a,long long x);
    void debug();
};
Fenwick::Fenwick(int l){
    length=l;
    vec=new long long[l+1];
    init();
}
Fenwick::~Fenwick(){
    delete[] vec;
}
// v[1]+...+v[a], O(log N)
long long Fenwick::sum(int a){
    if(a<0)return 0;
    if(a>length)a=length;
    long long sum=0;
    while(a>0){
        sum+=vec[a];
        a-=a&(-a);
    }
    return sum;
}
// v[a+1]+v[a+2]+...+v[b], O(log N)
long long Fenwick::sum(int a,int b){
    return sum(b)-sum(a);
}
// v[a]+=x, O(log N)
void Fenwick::add(int a,long long x){
    if(a<=0||a>length)return;
    while(a<=length){
        vec[a]+=x;
        a+=a&(-a);
    }
}
// v[a]=x, O(log N)
void Fenwick::set(int a,long long x){
    add(a,x-operator[](a));
}
long long Fenwick::operator[](int i){
    return sum(i)-sum(i-1);
}
void Fenwick::init(){
    for(int i=0;i<=length;i++){
        vec[i]=0;
    }
}
void Fenwick::debug(){
    for(int i=0;i<=length;i++)printf("%lld ",vec[i]);
    printf("\n");
}