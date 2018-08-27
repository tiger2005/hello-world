#include<iostream>
#include<cstring>
#include<cstdio>
#include<fstream>
#include<ctime>
#include<conio.h>
#include<windows.h>
int ti;
void colset(int a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
clock_t t1,t2;
using namespace std;
char lo[10000000]={0},lo2[10000000]={0};
int s,now=5000000,q=0,by[10000000];
int xx,yy;
bool aaa;
bool pr;
bool co(int be,int en){
    if(be>en){
        printf("%d|%d\n\tRuntime Error: There's no anything in it\n",xx,yy);
        aaa=false;
    }
    int nn=be;
    while(nn<=en){
        if(lo[nn]=='<'){
            --now;
            if(now==0){
                printf("%d|%d\n\tMemory Limit Exceed: No variable position there\n",xx,yy);
                aaa=false;
            }
        }
        else if(lo[nn]=='>'){
            ++now;
            if(now>10000000){
                printf("%d|%d\n\tMemory Limit Exceed: I don\'t know why you want so big memories or... more than 1000,0000 bytes!\n",xx,yy);
                aaa=false;
            }
        }
        else if(lo[nn]=='+'){
            ;
        }
        else if(lo[nn]=='-'){
            ;
        }
        else if(lo[nn]=='.'){
            ;
        }
        else if(lo[nn]==','){
            ;
        }
        else if(lo[nn]=='['){
            int nnn=nn+1,no=1;
            while(no!=0 && nnn<=en){
                if(lo[nnn]=='[')    ++no;
                if(lo[nnn]==']')    --no;
                ++nnn;
            }
            if(nnn!=en+1||no==0){
                aaa=co(nn+1,nnn-2);
        	}
            else{
            	printf("%d|%d\n\tCompile Error: I can\'t find the last part there\n",xx,yy);
            	aaa=false;
			}
            nn=nnn-1;
        }
        else if(lo[nn]==' '){;}
        else if(lo[nn]==']'){
        	printf("%d|%d\n\tComlple Error: I can\'t the first part there\n",xx,yy);
        	aaa=false;
		}
        else if(lo[nn]=='#'){
        	++xx;yy=0;
		}
		++yy;
        ++nn;
    }
    return aaa;
}
void sou1(int be,int en){
    int nn=be;
    while(nn<=en){
        if(lo[nn]=='<') --now;
        else if(lo[nn]=='>')    ++now;
        else if(lo[nn]=='+'){
            ++by[now];
            while(by[now]>255)  by[now]-=256;
        }
        else if(lo[nn]=='-'){
            --by[now];
            while(by[now]<0)    by[now]+=256;
        }
        else if(lo[nn]=='.'){
            while(by[now]<0)    by[now]+=256;
            while(by[now]>255)  by[now]-=256;
            if(by[now]!=10)	printf("%c",by[now]);
            else	printf("\\n");
            pr=true;
        }
        else if(lo[nn]==','){
        	if(pr){
        		pr=false;
        		printf("\n");
			}
            t2=clock();
            ti=ti+t2-t1;
            char haha;
            printf("Read in: ");
            haha=getch();
            by[now]=(int)haha;
            if(by[now]==13)	by[now]=10;
            if(by[now]==10)	printf("\\n");
            else	printf("%c",by[now]);
            t1=clock();
            printf("\n");
        }
        else if(lo[nn]=='['){
            int nnn=nn+1,no=1;
            while(no!=0){
                if(lo[nnn]=='[')    ++no;
                if(lo[nnn]==']')    --no;
                ++nnn;
//                printf("%d\n",nnn);
            }
            while(by[now]!=0){
            	sou1(nn+1,nnn-2);
//            	printf("%d %c\n",now,by[now]);
			}
            nn=nnn-1;
        }
        ++nn;
    }
}
int K=0;
bool com(){
	xx=1;yy=1;
    now=5000000;
    s=-1;
    aaa=true;
    return co(1,q);
}
void run(){
	printf("Compile succeed!\n");
    memset(by,0,sizeof(by));
    s=-1;
    now=5000000;
    pr=false;
    t1=clock();
    sou1(1,q);
    t2=clock();
    ti=ti+t2-t1;
    printf("----------------------\nUse %d ms to run...\n",ti);
}
int main(int argc , char *argv[])
{
	if(argc<2){
		printf("+-----------------------------------------------------------+\n");
		printf("|How to use ?                                               |\n");
		printf("|Use \"Brainfuck [input file]\" to compile your Brainfuck code|\n");
		printf("|Use \"Brainfuck ?\" for help                                 |\n");
		printf("+-----------------------------------------------------------+\n");
		system("pause");
		return 0;
	}
	for(int t=1;t<argc;t++){
		colset(11);
		printf(">>> Running the %d th test\n",t);
		colset(15);
		ifstream file1;
		file1.open(argv[1]);
		if(!strcmp(argv[1],"?")){
			printf("+-----------------------------------------------------------+\n");
			printf("|This is a Brainfuck compile system                         |\n");
			printf("|You can compile your Brainfuck code easyly                 |\n");
			printf("|Use \"test.exe [input file] \" to compile your Brainfuck code|\n");
			printf("|Use \"test.exe ? \" for help                                 |\n");
			printf("+-----------------------------------------------------------+\n");
			system("pause");
			return 0;
		}
		if(!file1){
			printf("+------------------------------+\n");
			printf("|Can not find the input file ! |\n");
			printf("+------------------------------+\n");
			system("pause");
			return 0;
		}
		q=1; 
		while(!file1.eof()){
			file1>>lo2;
			for(int i=0;lo2[i]!='\0';i++){
				if(lo2[i]=='<'||lo2[i]=='>'||lo2[i]=='+'||lo2[i]=='-'||lo2[i]=='['||lo2[i]==']'||lo2[i]==','||lo2[i]=='.')	lo[q++]=lo2[i];
			}
			lo[q++]='#';
			memset(lo2,0,sizeof(lo2));
		}
		file1.close();
		--q;
		if(com())	run();
		system("pause");
	} 
	return 0;
}
