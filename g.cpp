#include<cstdio>
char s[100001];
int main(){
    int alphabet[26]={};
    scanf("%s",s);
    for(int i=0;s[i]!='\0';i++){
        alphabet[s[i]-'a']++;
    }
    long long sum=0,remain=0;
    for(int i=0;i<26;i++){
        sum+=alphabet[i]-alphabet[i]%2;
        remain+=alphabet[i]%2;
    }
    if(remain>0){
        sum++;
        remain--;
    }
    printf("%lld\n",sum*sum+remain);
}