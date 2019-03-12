//aのk乗(aはモノイドの元で、単位元はT(1))
template<typename T>
T power(T a,long long k){
    if(k==0)return T(1);
    if(k>0){
        T sqrta=power(a,k/2);
        return sqrta*sqrta*((k%2==0)?T(1):a);
    }
}

//拡張ユークリッド互除法（ax+by=gcd(a,b) 返り値はgcd）
long long ext_gcd(long long a,long long b,long long &x,long long &y){
    //b==0ならa*1+b*0=a
    if(b==0){x=1;y=0;return a;}
    //a=qb+rとして、bx+qy=gなるx,y,gが得られたとすると、
    //aX+bY=g \iff (qb+r)X+bY=g \iff b(qX+Y)+rX=g
    //より、x=qX+Y, y=X \iff X=y, Y=x-qy
    long long q=a/b, g=ext_gcd(b,a-q*b,x,y), z=x-q*y;
    x=y; y=z;
    return g;
}

//標数pの素体
template<long long p>
struct Fp{
    //0<=value<p
    long long value;
    Fp(){ value=0; }
    //x+a*p>=0なる最小のaは、a*p>=-x, a>=(-x)/p より a=ceil((-x)/p)=(-x+p-1)/p
    Fp(long long x){ value=(x>=0)?x%p:(x+((-x+p-1)/p)*p); }
    ~Fp(){}
    Fp inv(){
        long long x,y;
        ext_gcd(value,p,x,y);
        return Fp(x);
    }
    const Fp operator+(const Fp& a) const{ return Fp(value+a.value); }
    const Fp operator-(const Fp& a) const{ return Fp(value-a.value); }
    const Fp operator*(const Fp& a) const{ return Fp(value*a.value); }
    const Fp operator/(const Fp& a) const{ return Fp(value*a.inv().value); }
    void operator=(const Fp& a) { value=a.value; }
    bool operator==(const Fp& a) { return value==a.value; }
    bool operator!=(const Fp& a) { return !(this==a); }
    static Fp nCr(long long n,long long r){
        if(n>0&&0<r&&r<n){ return Fp(n)*Fp(r).inv()*nCr(n-1,r-1); }
        else if(n==0||r==0||n==r) return Fp(1);
        else return Fp(0);
    }
};

//nCr mod pの前計算
template<long long p>
struct nCr{
private:
    int maxN,maxR;
    Fp<p>** array;
public:
    nCr(int n,int r){
        maxN=n;
        maxR=r;
        array=new Fp<p>* [maxN+1];
        for(int i=0;i<=maxN;i++){
            array[i]=new Fp<p>[maxR];
            for(int j=0;j<=maxR;j++){
                if(0==i||i==j||j==0)array[i][j]=Fp<p>(1);
                else array[i][j]=array[i-1][j-1]+array[i-1][j];
            }
        }
    }
    ~nCr(){
        for(int i=0;i<=maxN;i++)delete[] array[i];
        delete[] array;
    }
    long long val(int n,int r){
        return array[n][r].value;
    }
};