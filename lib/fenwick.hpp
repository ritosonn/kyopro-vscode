class Fenwick{
private:
    int length, vecsize;
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
};
Fenwick::Fenwick(int l){
    this->length=l;
    vecsize=1;
    while(l>0){
        vecsize<<=1;
        l>>=1;
    }
    vecsize++;
    this->vec=new long long[vecsize];
    init();
}
Fenwick::~Fenwick(){
    delete[] vec;
}
// v[0]+v[1]+...+v[a-1]
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
// v[a]+v[a+1]+...+v[b-1]
long long Fenwick::sum(int a,int b){
    return sum(b)-sum(a);
}
// v[a]+=x
void Fenwick::add(int a,long long x){
    while(a<length){
        vec[a]+=x;
        a+=a&(-a);
    }
}
// v[a]=x
void Fenwick::set(int a,long long x){
    add(a,x-operator[](a));
}
long long Fenwick::operator[](int i){
    return sum(i)-sum(i-1);
}
void Fenwick::init(){
    for(int i=0;i<vecsize;i++){
        vec[i]=0;
    }
}