#include<cstdio>
//dp[i]=(1,2,...,i番目の列の塗り方の個数)
//     =sum_{j<i|j番目の色 \neq j+1番目の色 = i番目の色}(1,2,...,j番目の塗り方の個数)
//     =sum_{j<i|j番目の色 \neq j+1番目の色 = i番目の色} dp[j]
//     （このときj番目までの色がj+1番目とつながらないのでダブりがなく、
//       任意の塗り方はもとの列のどこかの端点を端点とするのでもれもない）
//col[c]=sum_{j<i|j番目の色 \neq j+1番目の色 = i番目の色 = c} dp[j]とおき、同時に更新する
long long dp[200001],col[200001];
long long const mod=1e9+7;
int c[200001];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]);
    dp[0]=1;
    c[0]=0;
    for(int i=1;i<=n;i++){
        if(c[i-1]!=c[i])col[c[i]]=(col[c[i]]+dp[i-1])%mod; //col[c[i]]に新たに増えるのは直前（j=i-1のとき）だけ
        dp[i]=col[c[i]]%mod;
    }
    printf("%lld\n",dp[n]);
    return 0;
}