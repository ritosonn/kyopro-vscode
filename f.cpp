#include<cstdio>
int main(){
    int n;
    scanf("%d",&n);
    char s[]="aaabcde";
    for(int i=1;i<=n;i++){
        bool flag=true;
        for(int j=2;j<=6;j++){
            if(i%j==0){
                printf("%c",s[j]);
                flag=false;
            }
        }
        if(flag)printf("%d",i);
        printf("\n");
    }
    return 0;
}