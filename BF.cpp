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
bool aaa;
bool co(int be,int en){
	if(be>en){
		printf("Runtime Error: There's no anything in it\n");
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
				printf("Memory Limit Exceed: No variable position there\n");
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
				printf("Memory Limit Exceed: I don\'t know why you want so big memories or... more than 1000,0000 bytes!\n");
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
				printf("Compile Error: I can\'t find the last part there\n");
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
			printf("Compile Error: I don\'t know what \'%c\' is\n",lo[nn]);
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
			printf("Breakpoint here!\n");
			for(int i=1;i<nn;i++)	printf("%c",lo[i]);
			colset(12);
			printf("%c",lo[nn]);
			colset(15);
			for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
			printf("\n");
			printf("You can look at the data\n");
			printf("L to look\n");
			printf("Q to quit\n");
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
			printf("Continuing...\n");
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
			printf("Waiting for read in No. %d\n",nn);
			for(int i=1;i<nn;i++)	printf("%c",lo[i]);
			colset(12);
			printf("%c",lo[nn]);
			colset(15);
			for(int i=nn+1;i<=q;i++)	printf("%c",lo[i]);
			printf("\n");
			char haha;
			haha=getch();
			by[now]=(int)haha;
			printf("Read ");
			if(by[now]!=13)	printf("\'%c\'",by[now]);
			else	{
				printf("enter ");
				by[now]=10;
			}
			printf("in No. %d\n",nn);
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
					printf("\nRuntime Error: soo many loops or... more than 100,0000 times!\n");
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
	if(s==-1)	printf("    No ouput yet...\n");
	else{
		printf("    Ouput:\n");
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
	printf("PRESS:\n");
	printf("A to move to the left\n");
	printf("D to move to the right\n");
	printf("S to select or cancel\n");
	printf("Q to quit\n");
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
			bp[qw]=!bp[qw];
			Goto(0,0);
			if(bp[qw])	printf("Now there is a breakpoint.");
			else	printf("Now there is not a breakpoint.");
			printf("Press to continue...");
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
	printf("Put the code in ");
	colset(12);
	printf("1");
	colset(15);
	printf(" line\n");
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
			printf("Waiting for read");
			char haha;
			haha=getch();
			by[now]=(int)haha;
			if(by[now]==13)	by[now]=10;
			Goto(0,0);
			printf("                ");
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
		Sleep(uu);
	}
}
void imt(){
	memset(by,0,sizeof(by));
	system("cls");
	printf("You will use this when you use less memorys , ouput , code and time.\n");
	printf("Are you ");
	colset(12);
	printf("SURE");
	colset(15);
	printf("?(Y for yes,N for no)\n");
	char qwer;
	do{
		qwer=getch();
	}while(qwer!='Y'&&qwer!='y'&&qwer!='N'&&qwer!='n');
	if(qwer=='N'||qwer=='n')	return;
	system("cls");
	do{
		system("cls");
		printf("Choose the speede.\n");
		printf("You can input a number to select there\'s ? ms between two times\n");
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
	printf("Ouput:)");
	Goto(2,0);
	for(int i=0;i<sua;i++){
		for(int j=0;j<(i==sua-1?(q-1)%175+1:175);j++){
			printf("%c",lo[i*175+j+1]);
		}
	}
	im(1,q);
	Goto(0,0);
	printf("Press to continue...");
	getch();
	system("cls");
}
void imf(){
	system("cls");
	printf("This is a Brainfuck Compile System\n");
	printf("Creater Imformatiom\n");
	printf("Name:\n");
	printf("++++++++++[>>>>>>++[\n<<<<<+++>>>>>-]<<++[\n<<+++++>>-]>++[<<+++\n+++>>-]<<<<<-]>+++++\n");
	printf("++.>++++++.>----.\n");
	printf("Nickname:\n");
	printf(">+++++[>+++++[<<++>>\n-]<-]<[>++>>++>>++>>\n+>>+<+<<+<<++<<++<<-\n]>>>>>>>>>>++++[<<<<\n");
	printf("<<<<<++++>>>>>>>>>-]\n<<<<<<<<<.>+++++.>++\n+.>+.>>>>>>+++[<<<<<\n+++++>>>>>-]<<<<<-.>\n.>--.>--.>+++.\n");
	printf("Press to continue...");
	getch();
	system("cls");
}
int main(){
	colset(15);
	system("mode con cols=175 lines=50");
	Hide(); 
	while(1){
		printf("Case %d: \n",++K);
		mdf();
		r=false;
		while(1){
			colset(15);
			printf("\n---------------------\n\nPRESS:\n");
			printf("C to compile\n");
			printf("M to modify\n");
			printf("Q to quit\n");
			printf("I for more imformation\n");
			if(!r)	colset(8);
			printf("R to run\n");
			printf("B to set breakpoint\n");
			printf("L to look the imatate\n\n");
			printf("-----------------------\n");
			colset(15);
			do{
				haha=getch();
			}while(haha!='C'&&haha!='c'&&haha!='R'&&
				   haha!='r'&&haha!='B'&&haha!='b'&&
				   haha!='M'&&haha!='m'&&haha!='Q'&&
				   haha!='q'&&haha!='I'&&haha!='i'&&
				   haha!='L'&&haha!='l');
			if(haha=='B'||haha=='b'||haha=='R'||haha=='r'||haha=='L'||haha=='l'){
				if(!r){
					colset(12);
					printf("Compile First\n");
					colset(15);
				}
				else{
					if(haha=='B'||haha=='b')	bpt();
					else if(haha=='L'||haha=='l')	imt();
					else	run();
				}
			}
			else if(haha=='C'||haha=='c'){
				printf("\n----------\nCompile information:\n");
				r=com();
				if(r==true)	printf("Compile successed\n");
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
