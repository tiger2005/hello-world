#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace bint{
	struct Bint{
		int num[1012],len;
		bool big_zero;
	};
	Bint equal(char a[],int f,int l){
		Bint c;
		c.len=0;
		memset(c.num,0,sizeof(c.num));
		int aa=-1;
		if(a[f]=='-'){
			c.big_zero=true;
			++f;
		}
		else	c.big_zero=false;
		for(int i=l;i>=f;i--){
			if(a[i]=='.')	aa=i;
			if(aa!=-1)	break;
		}
		if(aa==-1)	aa=l-13;
		int now=11-l+aa;
		for(int i=l;i>=f;i--){
			if(a[i]!='.')	++now;
			if(now>=0 && a[i]!='.')	c.num[now]=a[i]-'0';
		}
		c.len=now;
		return c;
	}
	
	Bint plus(Bint a,Bint b);
	Bint minus(Bint a,Bint b);
	Bint multiply(Bint a,Bint b);
	Bint divide(Bint a,Bint b);
	Bint modulus(Bint a,Bint b);
	Bint plus(Bint a,Bint b){
		
	}
}
using namespace bint;
int main(){
//	Bint b=equal("123.456",0,6);
}
