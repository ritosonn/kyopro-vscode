#include<cstdio>
int numofbits(int bits){
    bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
    bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
    return (bits & 0x0000ffff) + (bits >>16 & 0x0000ffff);
}
int msb(int bits){
    bits |= (bits >> 1);
    bits |= (bits >> 2);
    bits |= (bits >> 4);
    bits |= (bits >> 8);
    bits |= (bits >> 16);
    return (bits + 1) >> 1;
}
int lsb(int bits){
    return bits & (-bits);
}
//nビットの数字の列{x=a_0,a_1,...,a_{2^n-1}=y} を出力する
//（ただしnumofbits(a_i xor a_{i+1})=1, n=numofbits(mask), a_iで変化するビットはmaskだけ）
void print_gray(int x,int y,int mask){
    if(numofbits(mask)==1){
        printf("%d %d",x,y);
    }else{
        //aはxとyが異なる最小ビット、bはmaskのどれかでaと異なるもの
        //中間地点として、xから1bitずらしたものを使う
        int a=lsb(x^y),b=msb(mask);
        if(a==b)b=lsb(mask);//maskが2bit以上あれば別のbitが出てくる
        int z=x^b;
        //前半はaをxと同じ状態にfixしてxからzまで
        print_gray(x,z,mask^a);
        printf(" ");
        //後半はaをyと同じ状態にfixしてzからyまで
        print_gray(z^a,y,mask^a);
    }
}
int main(){
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    if(numofbits(a^b)%2==0)printf("NO\n");
    else{
        printf("YES\n");
        print_gray(a,b,(1<<n)-1);
        printf("\n");
    }
    return 0;
}