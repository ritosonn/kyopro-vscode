#include<cstdio>
char iswin_memo[1024];
bool iswin(int x){
    if(x<0)return true;
    if(x==0)return false;
    if(x==1||x==8||x==64||x==512)return true;
    if(iswin_memo[x]=='w')return true;
    if(iswin_memo[x]=='l')return false;
    bool ans= !iswin(x-1)||!iswin(x-8)||!iswin(x-64)||!iswin(x-512);
    iswin_memo[x]=(ans)?'w':'l';
    return ans;
}
bool iswin_try(int x){
    return x%2==((x+10)/9)%2;
}
int main(){
    //long long n;
    //scanf("%lld",&n);
    for(int i=1;i<1024;i++)iswin_memo[i]='u';
    for(int i=1;i<1024;i++){
        printf("%4d,%s\n",i,(iswin(i)==iswin_try(i))?"":"x");
    }
    return 0;
}