#include<cstdio>
#include<cstring>
#include<windows.h>
#include<string>
#include<iostream>
#include<ctime>
#include<fstream>
#include<algorithm>
using namespace std;
const char* a;
string ra,so,bf,p,str1,str2;
int N,l1,l2,fk[7][6],mb,jl[1000001][2],mp;
double st,en;
void colset(double a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
bool ws(char a){
    return a=='\t' || a=='\n' || a=='\r' || a==' ' || a==EOF;
}
bool bj(){
    for(int i=0;i<=l1&&i<=l2;i++){
        if(str1[i]!=str2[i])    return true;
    }
    return false;
}
double ss(int i){
    if(i>=1000) return 12;
    else if(i<200)  return 13;
    else if(i<400)  return 9;
    else if(i<600)  return 11;
    else if(i<800)  return 10;
    return 14;
}
int sts(int i){
    if(i>=1000) return 5;
    else if(i<200)  return 0;
    else if(i<400)  return 1;
    else if(i<600)  return 2;
    else if(i<800)  return 3;
    return 4;
}
int ssts(int i,int j){
    for(int k=0;k<6;k++){
        if(i>(j*k/6) && i<=(j*(k+1)/6)) return k;
    }
    return 0;
}
long long anss=0;
int main(){
    printf("TIMESET:\n");
    for(int i=0;i<1000;i+=200){
        colset(ss(i));
        printf("%d ~ %d\n",i,i+199);
    }
    colset(ss(1000));
    printf("1000+\n");
    colset(7);
    printf("Random exe:\n");
    cin >> ra;
    printf("Correct exe(It doesn\'t matter if it is TLE):\n");
    cin >> bf;
    printf("Your exe:\n");
    cin >> so;
    printf("Text Number:\n");
    cin >> N;
    if(N>1000000){
        printf("BIGGER THAN 1000000!!!\n");
        return 0;
    }
    for(int i=1;i<=N;i++){
        p=ra+" > dat.in";
        a=p.c_str();
        system(a);
        p=bf+" < dat.in > dat.ans";
        a=p.c_str();
        system(a);
        p=so+" < dat.in > dat.out";
        a=p.c_str();
        st=clock();
        system(a);
        en=clock();
        ifstream f1;
        f1.open("dat.out");
        str1.clear();
        str2.clear();
        l1=-1;
        while(!f1.eof())    str1+=f1.get(),++l1;
        f1.close();
        f1.open("dat.ans");
        l2=-1;
        while(!f1.eof())    str2+=f1.get(),++l2;
        f1.close();
        while(l1>=0 && ws(str1[l1]))    --l1;
        while(l2>=0 && ws(str2[l2]))    --l2;
        if(bj()){
            colset(12);
            printf("### Wrong answer");
            colset(7);
            system("pause");
            return 0;
        }
        else    colset(ss(int(en-st))),printf("Accepted, TEXT:%d, TIME:%.0lfms OUPUT_BIT:%d\n",i,en-st,l2+1);
        jl[i][0]=l2+1;
        jl[i][1]=en-st;
        anss+=(en-st);
        mb=max(mb,l2+1);
    }
    mp=mb;mb/=6;++mb;
    colset(10);printf("OK!!!\n");
    for(int i=1;i<=N;i++)   ++fk[ssts(jl[i][0],mp)][sts(jl[i][1])];
    for(int i=0;i<6;i++){
        colset(ss(i*200));
        if(i!=5)    printf("%d ~ %d ms => %d\n",i*200,i*200+199,fk[0][i]+fk[1][i]+fk[2][i]+fk[3][i]+fk[4][i]+fk[5][i]);
        else    printf("%d+ ms => %d\n",i*200,fk[0][i]+fk[1][i]+fk[2][i]+fk[3][i]+fk[4][i]+fk[5][i]);
    }
    printf("AVERAGE:%lldms\n",anss/N);
    colset(7);
    system("pause");
    return 0;
}
