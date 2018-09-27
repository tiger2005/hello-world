//Testing in Bigint
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
namespace bint{
	struct Bint{
		char num[1012];
		int len;
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
		int now=11-l+aa;
		if(aa==-1)	now=11;
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
		if(i<12){
			printf(".");
			for(int j=11;j>=i;j--)	printf("%d",a.num[j]);
		}
		return;
	}
	int big(Bint a,Bint b){
		if(a.bz^b.bz)	return !a.bz;
		if(a.len!=b.len)	return ((a.len>b.len) ^ !a.bz)+1;
		int bi=0;
		for(int i=a.len;i>=0;i--){
			if(a.num[i]>b.num[i]){
				bi=1;
				goto P;
			}
			if(a.num[i]<b.num[i]){
				bi=2;
				goto P;
			}
		}
		P:if(bi && a.bz)	bi=3-bi;
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
		if(ans.num[lo+1])	++lo;
		ans.len=lo;
		ans.bz=a.bz;
		bool wh=false;
		for(int i=0;i<=ans.len;i++){
			if(ans.num[i])	wh=true;
		}
		if(ans.bz)	ans.bz=wh;
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
		ans.bz=a.bz;
		if((big(a,b)==2) ^ a.bz){
			ans.bz=!ans.bz;
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
		bool wh=false;
		for(int i=0;i<=ans.len;i++){
			if(ans.num[i])	wh=true;
		}
		if(ans.bz)	ans.bz=wh;
		return ans;
	}
	Bint multiply(Bint a,Bint b){
		Bint ans;
		memset(ans.num,0,sizeof(ans.num));
		int bl=0;
		for(int i=0;i<=a.len;i++){
			for(int j=0;j<=b.len;j++){
				if(i+j<12)	continue;
				ans.num[i+j-12]+=a.num[i]*b.num[j];
				if(ans.num[i+j-12])	bl=max(bl,i+j-12);
				while(ans.num[i+j-12]>=10){
					++ans.num[i+j+1-12];
					ans.num[i+j-12]-=10;
					bl=max(bl,i+j+1-12);
				}
			}
		} 
		for(int i=0;i<1012;i++){
			while(ans.num[i]>=10){
				ans.num[i]-=10;
				bl=max(bl,i+1);
				++ans.num[i+1];
			}
		}
		ans.len=bl;
		ans.bz=a.bz^b.bz;
		bool wh=false;
		for(int i=0;i<=ans.len;i++){
			if(ans.num[i])	wh=true;
		}
		if(ans.bz)	ans.bz=wh;
		return ans;
	} 
	Bint divide(Bint a,Bint b){
		Bint pl,ans;
		memset(pl.num,0,sizeof(pl.num));
		bool aaa=a.bz^b.bz; 
		ans.bz=pl.bz=a.bz=b.bz=false;
		memset(ans.num,0,sizeof(ans.num));
		for(int i=a.len+11-b.len;i>=0;i--){
			pl.num[i+1]=0;
			pl.num[i]=1;
			pl.len=i;
			while(big(a,multiply(pl,b)) != 2){
				ans=plus(ans,pl);
				a=minus(a,multiply(pl,b));
			}
		}
		ans.len=1011;
		while(!ans.num[ans.len])	--ans.len;
		ans.bz=aaa;
		if(ans.num[0]<0)	ans.num[0]=0;
		bool wh=false;
		for(int i=0;i<=ans.len;i++){
			if(ans.num[i])	wh=true;
		}
		if(ans.bz)	ans.bz=wh;
		return ans;
	}
	Bint modulus(Bint a,Bint b){
		Bint ans=divide(a,b);
		for(int i=0;i<12;i++)	ans.num[i]=0;
		if(ans.len<12)	ans.len=0;
		bool aaa=a.bz;
		a.bz=ans.bz=b.bz=false;
		ans=minus(a,multiply(ans,b));
		ans.bz=aaa;
		bool wh=false;
		for(int i=0;i<=ans.len;i++){
			if(ans.num[i])	wh=true;
		}
		if(ans.bz)	ans.bz=wh;
		return ans;
	}
	
}
using namespace bint;
int main(){
	char aa[1000],bb[1000];
	scanf("%s %s",aa,bb);
	Bint b=equal(aa,0,strlen(aa)-1);
	Bint c=equal(bb,0,strlen(bb)-1);
	printf("%d\n",big(b,c));
	Bint a=plus(b,c);
	print(a);
	printf("\n");
	a=minus(b,c);
	print(a);
	printf("\n");
	a=multiply(b,c);
	print(a);
	printf("\n");
	a=divide(b,c);
	print(a);
	printf("\n");
	a=modulus(b,c);
	print(a);
	printf("\n");
}
