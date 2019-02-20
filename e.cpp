#include<cstdio>
long long collatz(long long x){
    if(x>=1e16||x<=1)return 0;
    if(x%2==0)return x/2;
    else return 3*x+1;
}
int main(){
    int p;
    scanf("%d",&p);
    long long x=1789997546303;
    for(int i=1000;i>p;i--)x=collatz(x);
    printf("%lld\n",x);
    return 0;
}