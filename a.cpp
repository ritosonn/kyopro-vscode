#include<cstdio>
char s[100001];
int main(){
    scanf("%s",s);
    for(int i=0;s[i]!='\0';i++){
        printf("%d\n",i+1);
    }
    return 0;
}