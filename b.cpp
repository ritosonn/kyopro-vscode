#include<cstdio>
int main(){
    long long n;
    scanf("%lld",&n);
    for(long long k=34000;k>=0;k--){
        if(k*k<=n){
            printf("%lld\n",k);
            return 0;
        }
    }
}