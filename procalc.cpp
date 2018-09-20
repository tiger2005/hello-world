#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
namespace bint{
	struct Bint{
		int num[1012],len;
		bool bz;
	};
	Bint equal(char a[],int f,int l){
		Bint c;
		c.len=0;
		memset(c.num,0,sizeof(c.num));
		int aa=-1;
		if(a[f]=='-'){
			c.bz=true;
			++f;
		}
		else	c.bz=false;
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
	void print(Bint a){
		int i=0;
		while(i < 12 && a.num[i] == 0)	++i;
		if(a.bz)	printf("-");
		for(int j=a.len;j>=12;j--)	printf("%d",a.num[j]);
		if(a.len < 12)	printf("0");
		if(i!=12){
			printf(".");
			for(int j=11;j>=12-i;j--)	printf("%d",a.num[j]);
		}
		return;
	}
	int big(Bint a,Bint b){
		if(a.bz^b.bz)	return !a.bz;
		if(a.len!=b.len)	return a.len>b.len;
		int bi=0;
		for(int i=a.len;i>=0;i--){
			if(a.num[i]>b.num[i]){
				bi=1;
				break;
			}
			if(a.num[i]<b.num[i]){
				bi=0;
				break;
			}
		}
		if(bi && a.bz)	bi=3-bi;
		return bi;
	}
	Bint plus(Bint a,Bint b);
	Bint minus(Bint a,Bint b);
	Bint multiply(Bint a,Bint b);
	Bint divide(Bint a,Bint b);
	Bint modulus(Bint a,Bint b);
	Bint plus(Bint a,Bint b){
		Bint ans;
		memset(ans.num,0,sizeof(ans.num));
		if(a.bz^b.bz){
			for(int i=0;i<1012;i++)	ans.num[i]=b.num[i];
			ans.bz=!b.bz;
			ans.len=b.len;
			return minus(a,ans);
		}
		int lo=max(a.len,b.len);
		for(int i=0;i<=lo;i++){
			ans.num[i]+=a.num[i]+b.num[i];
			if(ans.num[i]>9){
				++ans.num[i+1];
				ans.num[i]%=10;
			}
		}
		if(ans.num[lo])	++lo;
		ans.len=lo-1;
		ans.bz=a.bz;
		return ans;
	}
	Bint minus(Bint a,Bint b){
		Bint ans;
		memset(ans.num,0,sizeof(ans.num));
		if(a.bz^b.bz){
			for(int i=0;i<1012;i++)	ans.num[i]=b.num[i];
			ans.bz=!b.bz;
			ans.len=b.len;
			return plus(a,ans);
		}
		if((big(a,b)==2) ^ !a.bz){
			Bint t=b;
			b=a;
			a=t;
		}
		int lo=max(a.len,b.len);
		for(int i=0;i<=lo;i++){
			ans.num[i]+=a.num[i]-b.num[i];
			while(ans.num[i]<0){
				--ans.num[i+1];
				ans.num[i]+=10;
			}
		}
		while(!ans.num[lo])	--lo;
		ans.len=lo;
		ans.bz=(big(a,b)==1);
		return ans;
	}
}
using namespace bint;
int main(){
	char aa[10]={"123.456"},bb[15]={"123.456789"};
	Bint b=equal(aa,0,6);
	Bint c=equal(bb,0,9);
	Bint a=minus(b,c);
	print(a);
	printf("\n");
	print(b);
	printf(" ");
	print(c);
}
