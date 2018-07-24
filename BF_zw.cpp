//For Bainfuck
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
void colset(int a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void Goto(int Y,int X){
    COORD C; C.X=X; C.Y=Y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),C);   
}
void Hide(){ 
    CONSOLE_CURSOR_INFO cursor_info={1,0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
using namespace std;
int by[10000002];
char lo[10000002],sc[10000002];
bool bp[10000002];
int now=1,ma,s=-1,nnnn=0,cs,mn;
bool ok=false;
int q=0;
bool aaa=true;
bool co(int be,int en){
	if(be>en){
		printf("运行时错误：这个循环里没东西，会死循环的···\n");
		for(int i=1;i<en;i++)	printf("%c",lo[i]);
		colset(12);
		for(int i=en;i<=be;i++)	printf("%c",lo[i]);
		colset(15);
		for(int i=be+1;i<=q;i++)	printf("%c",lo[i]);
		printf("\n");
		aaa=false;
	}
	int nn=be;
	while(nn<=en){
		if(lo[nn]=='<'){
			--now;
			if(now==0){
				printf("超内存：你成功的在指向第一个位置时往左移\n");
				for(int i=1;i<nn;i++)	printf("%c",lo[i]);
				colset(12);
				printf("%c",lo[nn]);
				colset(15);
				for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
				printf("\n");
				aaa=false;
			}
		}
		else if(lo[nn]=='>'){
			++now;
			if(now>10000000){
				printf("超内存：我不知道你为何要这么大的内存，或说，1000,0000 字节！\n");
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
				if(lo[nnn]=='[')	++no;
				if(lo[nnn]==']')	--no;
				++nnn;
			}
			if(nnn!=en+1||no==0){
				aaa=co(nn+1,nnn-2);
			}
			else{
				printf("编译错误：你的右括号呢？\n");
				for(int i=1;i<nn;i++)	printf("%c",lo[i]);
				colset(12);
				printf("%c",lo[nn]);
				colset(15);
				for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
				printf("\n");
				aaa=false;
			}
			nn=nnn-1;
		}
		else if(lo[nn]==' '||lo[nn]==']'){;}
		else{
			printf("编译错误：什么是 \'%c\' ？\n",lo[nn]);
			for(int i=1;i<nn;i++)	printf("%c",lo[i]);
			colset(12);
			printf("%c",lo[nn]);
			colset(15);
			for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
			printf("\n");
			aaa=false;
		}
		++nn;
	}
	return aaa;
}
void sou(int be,int en){
	int nn=be;
	while(nn<=en){
		if(bp[nn]){
			printf("这有个断点！\n");
			for(int i=1;i<nn;i++)	printf("%c",lo[i]);
			colset(12);
			printf("%c",lo[nn]);
			colset(15);
			for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
			printf("\n");
			printf("你可以在现在看看储存情况\n");
			printf("输入L查看\n");
			printf("输入Q退出\n");
			char hhh;
			do{
				hhh=getch();
			}while(hhh!='L'&&hhh!='l'&&
				   hhh!='Q'&&hhh!='q');
			if(hhh=='L'||hhh=='l'){
				int h=(mn+9)/10;
				for(int i=0;i<h;i++){
					for(int j=0;j<10;j++){
						if(i*10+j+1==now)	colset(12);
						printf(" %3d |",by[i*10+j+1]);
						colset(15);
					}
					printf("\n");
					if((now+9)/10==i+1){
						for(int j=1;j<(now%10);j++)	printf("      ");
						printf(" ^^^\n");
					}
				}
			}
			printf("继续运行中\n");
		}
		if(lo[nn]=='<')	--now;
		else if(lo[nn]=='>'){
			++now;
			if(mn<now)	mn=now;
		}
		else if(lo[nn]=='+'){
			++by[now];
			while(by[now]<0)	by[now]+=128;
			while(by[now]>127)	by[now]-=128;
		}
		else if(lo[nn]=='-'){
			--by[now];
			while(by[now]<0)	by[now]+=128;
			while(by[now]>127)	by[now]-=128;
		}
		else if(lo[nn]=='.'){
			while(by[now]<0)	by[now]+=128;
			while(by[now]>127)	by[now]-=128;
			sc[++s]=by[now];
		}
		else if(lo[nn]==','){
			printf("在第 %d 个符号遇到读入要求，请输入\n",nn);
			for(int i=1;i<nn;i++)	printf("%c",lo[i]);
			colset(12);
			printf("%c",lo[nn]);
			colset(15);
			for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
			printf("\n");
			char haha;
			haha=getch();
			by[now]=(int)haha;
			printf("已成功读入 ");
			if(by[now]!=13)	printf("\'%c\'\n",by[now]);
			else	{
				printf("回车\n");
				by[now]=10;
			}
			for(int i=1;i<nn;i++)	printf("%c",lo[i]);
			colset(12);
			printf("%c",lo[nn]);
			colset(15);
			for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
			printf("\n");
		}
		else if(lo[nn]=='['){
			int nnn=nn+1,no=1;
			while(no!=0){
				if(lo[nnn]=='[')	++no;
				if(lo[nnn]==']')	--no;
				++nnn;
			}
			while(by[now]!=0){
				sou(nn+1,nnn-2);
				++cs;
				if(cs>1000000){
					printf("\n运行时错误:太多循环次数了，或说，多于100,0000次！\n");
					return;
				}
			}
			nn=nnn-1;
		}
		++nn;
	}
}
int K=0;
bool com(){
	now=1;
	s=-1;
	nnnn=0;
	aaa=true;
	return co(1,q);
}
void run(){
	memset(by,0,sizeof(by));
	mn=1;
	s=-1;
	sou(1,q);
	if(s==-1)	printf("    没有输出...\n");
	else{
		printf("    输出:\n");
		for(int i=0;i<=s;i++)	printf("%c",sc[i]);
	}
	nnnn=0;
	ok=false;
}
void bpt(){
	int qw=1;
	system("cls");
	printf("\n---------------------\n");
	Goto(4,0);
	printf("^");
	int qwe=(q-1)/175+1;
	Goto(3,0);
	for(int i=0;i<qwe;i++){
		for(int j=1;j<=(i==qwe-1?(q-1)%175+1:175);j++){
			if(bp[i*175+j])	colset(12);
			printf("%c",lo[i*175+j]);
			colset(15);
		}
		printf("\n\n");
	}
	printf("输入:\n");
	printf("A左移\n");
	printf("D右移\n");
	printf("S确认或取消\n");
	printf("Q放弃此次设置\n");
	printf("\n---------------------\n");
	while(1){
		char hhhh;
		do{
			hhhh=getch();
		}while(hhhh!='A'&&hhhh!='a'&&
			   hhhh!='D'&&hhhh!='d'&&
			   hhhh!='S'&&hhhh!='s'&&
			   hhhh!='Q'&&hhhh!='q');
		if(hhhh=='A'||hhhh=='a'||hhhh=='D'||hhhh=='d'){
			Goto((qw-1)/175*2+4,(qw-1)%175);
			printf(" ");
		}
		if(hhhh=='A'||hhhh=='a'){
			--qw;
			if(qw<0)	qw+=q;
			while(lo[qw]=='['||lo[qw]==']'){
				--qw;
				if(qw<0)	qw+=q;
			}
			Goto((qw-1)/175*2+4,(qw-1)%175);
			printf("^");
		}
		else if(hhhh=='D'||hhhh=='d'){
			++qw;
			if(qw>q)	qw-=q;
			while(lo[qw]=='['||lo[qw]==']'){
				++qw;
				if(qw>q)	qw-=q;
			}
			Goto((qw-1)/175*2+4,(qw-1)%175);
			printf("^");
		}
		else if(hhhh=='S'||hhhh=='s'){
			Goto(0,0);
			bp[qw]=!bp[qw];
			if(bp[qw])	printf("现在这里有一个断点。");
			else	printf("现在这里没有断点。");
			printf("按任意键继续...");
			getch();
			break;
		}
		else	break;
	}
	system("cls");
}
bool r;
char haha;
void mdf(){
	printf("打入BF代码，保持");
	colset(12);
	printf("一");
	colset(15);
	printf("行（无回车）\n");
	q=0;
	while(scanf("%c",&haha)&&(q==0||haha!=10)){
		if(q==0&&haha==10){
			;
		}
		else	lo[++q]=haha;
	}
}
int mnn,zz,zz2,uu;
void im(int be,int en){
	int nn=be;
	int su=(q-1)/175+1;
	while(nn<=en){
		if(zz!=now){
			Goto(4*(zz/34)+5+su,5*(zz%34)+1);
			printf("   ");
			zz=now;
			Goto(4*(now/34)+5+su,5*(now%34)+1);
			printf("^^^");
		}
		Goto((nn-1)/175+2,(nn-1)%175);
		colset(12);
		printf("%c",lo[nn]);
		colset(15);
		if(zz2!=nn){
			Goto((zz2-1)/175+2,(zz2-1)%175);
			colset(15);
			printf("%c",lo[zz2]);
		}
		zz2=nn;
		if(lo[nn]=='<'){
			Goto(4*(now/34)+5+su,5*(now%34)+1);
			printf("   ");
			--now;
			Goto(4*(now/34)+5+su,5*(now%34)+1);
			printf("^^^");
			zz=now;
		}
		else if(lo[nn]=='>'){
			Goto(4*(now/34)+5+su,5*(now%34)+1);
			printf("   ");
			++now;
			Goto(4*(now/34)+5+su,5*(now%34)+1);
			printf("^^^");
			if(mnn<now){
				mnn=now;
				Goto(4*(now/34)+2+su,5*(now%34));
				printf("+---+");
				Goto(4*(now/34)+3+su,5*(now%34));
				printf("|  0|");
				Goto(4*(now/34)+4+su,5*(now%34));
				printf("+---+");
			}
			zz=now;
		}
		else if(lo[nn]=='+'){
			++by[now];
			while(by[now]<0)	by[now]+=128;
			while(by[now]>127)	by[now]-=128;
			Goto(4*(now/35)+3+su,5*(now%35)+1);
			printf("%3d",by[now]);
		}
		else if(lo[nn]=='-'){
			--by[now];
			while(by[now]<0)	by[now]+=128;
			while(by[now]>127)	by[now]-=128;
			Goto(4*(now/35)+3+su,5*(now%35)+1);
			printf("%3d",by[now]);
		}
		else if(lo[nn]=='.'){
			while(by[now]<0)	by[now]+=128;
			while(by[now]>127)	by[now]-=128;
			Goto(1,++s);
			if(by[now]!=10)	printf("%c",by[now]);
			else{
				printf("\\n");
				++s;
			}
		}
		else if(lo[nn]==','){
			Goto(0,0);
			printf("准备读入");
			char haha;
			haha=getch();
			by[now]=(int)haha;
			if(by[now]==13)	by[now]=10;
			Goto(0,0);
			printf("        ");
			Goto(4*(now/35)+3+su,5*(now%35)+1);
			printf("%3d",by[now]);
		}
		else if(lo[nn]=='['){
			int nnn=nn+1,no=1;
			while(no!=0){
				if(lo[nnn]=='[')	++no;
				if(lo[nnn]==']')	--no;
				++nnn;
			}
			while(by[now]!=0)	im(nn+1,nnn-2);
			nn=nnn-1;
		}
		++nn;
		Sleep(100);
	}
}
void imt(){
	memset(by,0,sizeof(by));
	system("cls");
	printf("在运行时，你需要较少的内存，输出，代码和时间。\n");
	printf("你");
	colset(12);
	printf("确定");
	colset(15);
	printf("吗？(Y确定,N退出)\n");
	char qwer;
	do{
		qwer=getch();
	}while(qwer!='Y'&&qwer!='y'&&qwer!='N'&&qwer!='n');
	if(qwer=='N'||qwer=='n')	return;
	system("cls");
	do{
		system("cls");
		printf("选择速度。\n");
		printf("输入一个数确认两次操作间的时间（单位为毫秒）\n");
		printf(">=10,<=500\n");
		scanf("%d",&uu);
	}while(uu<10||uu>500);
	system("cls");
	mnn=0;
	s=6;
	now=0;
	zz2=1;
	int sua=(q-1)/175+1;
	Goto(2+sua,0);
	printf("+---+\n|  0|\n+---+\n ^^^ ");
	zz=1;
	Goto(1,0);
	printf("输出 :)");
	Goto(2,0);
	for(int i=0;i<sua;i++){
		for(int j=0;j<(i==sua-1?(q-1)%175+1:175);j++){
			printf("%c",lo[i*175+j+1]);
		}
		if(i!=sua-1)	printf("\n");
	}
	im(1,q);
	Goto(0,0);
	printf("按任意键继续...");
	getch();
	system("cls");
}
void imf(){
	system("cls");
	printf("这是个Brainfuck编译系统\n");
	printf("制作人信息\n");
	printf("名字:\n");
	printf("++++++++++[>>>>>>++[\n<<<<<+++>>>>>-]<<++[\n<<+++++>>-]>++[<<+++\n+++>>-]<<<<<-]>+++++\n");
	printf("++.>++++++.>----.\n");
	printf("昵称:\n");
	printf(">+++++[>+++++[<<++>>\n-]<-]<[>++>>++>>++>>\n+>>+<+<<+<<++<<++<<-\n]>>>>>>>>>>++++[<<<<\n");
	printf("<<<<<++++>>>>>>>>>-]\n<<<<<<<<<.>+++++.>++\n+.>+.>>>>>>+++[<<<<<\n+++++>>>>>-]<<<<<-.>\n.>--.>--.>+++.\n");
	printf("按任意键继续...");
	getch();
	system("cls");
}
int main(){
	colset(15);
	system("mode con cols=175 lines=50");
	Hide();
	while(1){
		printf("第%d次...\n",++K);
		mdf();
		r=false;
		while(1){
			colset(15);
			printf("\n---------------------\n\n输入:\n");
			printf("C编译\n");
			printf("M重写\n");
			printf("Q退出\n");
			printf("I查看更多信息\n");
			if(!r)	colset(8);
			printf("R运行\n");
			printf("B设置断点\n");
			printf("L查看模拟运行过程\n\n");
			printf("-----------------------\n");
			colset(15);
			do{
				haha=getch();
			}while(haha!='C'&&haha!='c'&&haha!='R'&&
				   haha!='r'&&haha!='B'&&haha!='b'&&
				   haha!='M'&&haha!='m'&&haha!='Q'&&
				   haha!='q'&&haha!='I'&&haha!='i'&&
				   haha!='L'&&haha!='l');
			if(haha=='B'||haha=='b'||haha=='R'||haha=='r'||haha=='l'||haha=='L'){
				if(!r){
					colset(12);
					printf("先编译\n");
					colset(15);
				}
				else{
					if(haha=='B'||haha=='b')	bpt();
					else if(haha=='L'||haha=='l')	imt();
					else	run();
				}
			}
			else if(haha=='C'||haha=='c'){
				printf("\n----------\n编译信息:\n");
				r=com();
				if(r==true)	printf("编译成功\n");
				printf("\n----------\n");
			}
			else if(haha=='M'||haha=='m'){
				mdf();
				r=false;
			}
			else if(haha=='I'||haha=='i')	imf();
			else	break;
		}
		printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		memset(sc,0,sizeof(sc));
		memset(by,0,sizeof(by));
		memset(lo,0,sizeof(lo));
		memset(bp,0,sizeof(bp));
	}
}
//For copy
//Name:++++++++++[>>>>>>++[<<<<<+++>>>>>-]<<++[<<+++++>>-]>++[<<++++++>>-]<<<<<-]>+++++++.>++++++.>----.
//Nickname:>+++++[>+++++[<<++>>-]<-]<[>++>>++>>++>>+>>+<+<<+<<++<<++<<-]>>>>>>>>>>++++[<<<<<<<<<++++>>>>>>>>>-]<<<<<<<<<.>+++++.>+++.>+.>>>>>>+++[<<<<<+++++>>>>>-]<<<<<-.>.>--.>--.>+++.
