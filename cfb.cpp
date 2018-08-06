#include"testlib.h"
#include<cstdio>
#include<cstring>
using namespace std;
char lo[1000000];
int by[100000000],now,nnn,q,xh,xx,yy;
bool aaa=true;
void co(int be,int en){
    if(be>en){
        quitf(_wa , "Fell in endless loop at No. %d...",be-1 );
        aaa=false;
        return;
    }
    int nn=be;
    while(nn<=en&&aaa){
        if(lo[nn]=='<'){
            --now;
            if(now==0){
                quitf(_wa,"Point to the undefination byte at No. %d...",nn );
                aaa=false;
                if(!aaa)	return;
            }
        }
        else if(lo[nn]=='>'){
            ++now;
            if(now>100000000){
                quitf(_wa,"Use more than 100000000 byte at No. %d...",nn );
                aaa=false;
                if(!aaa)	return;
            }
        }
        else if(lo[nn]=='+'){
            ++by[now];
            while(by[now]<0)    by[now]+=128;
            while(by[now]>127)  by[now]-=128;
        }
        else if(lo[nn]=='-'){
            --by[now];
            while(by[now]<0)    by[now]+=128;
            while(by[now]>127)  by[now]-=128;
    	}
        else if(lo[nn]=='.'){
        	char hh=ans.readChar(by[now]); 
        	if(hh!=by[now]){
        		if(hh==10)	quitf(_wa,"Wrong in line %d",xx+1);
        		else	quitf(_wa,"Wrong in line %d , column %d",xx+1,yy+1);
			}
        }
        else if(lo[nn]==','){
        	if(inf.eof())	quitf(_wa,"Cannot read at No. %d...",nn);
        	else{
        		char hh=inf.readChar();
        		by[now]=(int)hh;
			}
        }
        else if(lo[nn]=='['){
            int nnn=nn+1,no=1;
            while(no!=0 && nnn<=en){
                if(lo[nnn]=='[')    ++no;
                if(lo[nnn]==']')    --no;
                ++nnn;
            }
            if(nnn!=en+1||no==0){
                while(by[now]){
                	++xh;
                	if(xh>1000000){
                		quitf(_wa,"Fell in morethan 1000000 loops in No. %d",nn-1);
                		aaa=false;
                		return;
					}
                	co(nn+1,nnn-2);
				}
            }
            else{
                quitf(_wa,"Cannot find the last part in No. %d...",nn );
                aaa=false;
                if(!aaa)	return;
            }
            if(!aaa)	return;
            nn=nnn-1;
        }
        else if(lo[nn]==']'){
			quitf(_wa,"Cannot find the last part in No. %d...",nn );
            aaa=false;
            if(!aaa)	return;
        }
        ++nn;
    }
}
int main(int argc, char* argv[]){
	registerTestlibCmd(argc, argv);
	char h;
	while(h!=10){
		h=ouf.readChar();
		lo[++q]=h;
	}
	for(int i=q;i>=1;i--){
		lo[i]=lo[i-1];
		lo[i-1]=0;
	}
	memset(by,0,sizeof(by));
    now=1;
    aaa=true;
    co(1,q);
    if(!ans.eof())quitf(_ok,"Answer correct ! ");
    else	quitf(_pe,"You stop at (%d,%d) and yu must print less/more thing...",xx+1,yy+1);
    return 0;
}
