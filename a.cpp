#include<cstdio>
char s[100001];
long long const mod=1e9+7;
int main(){
    int n,cnt[26]={};
    scanf("%d%s",&n,s);
    for(int i=0;i<n;i++)cnt[s[i]-'a']++;
    long long ans=1;
    for(int i=0;i<26;i++)ans=(ans*(cnt[i]+1))%mod;
    printf("%lld\n",ans-1);
    return 0;
}