#include<cstdio>
int main(){
    long long n;
    scanf("%lld",&n);
    printf("%s\n",(n%2==((n+10)/9)%2)?"Win":"Lose");
    return 0;
}