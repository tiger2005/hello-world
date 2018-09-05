#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<algorithm>
#include<cmath>
#include<conio.h>
using namespace std;
void Goto(int X,int Y){
    COORD C; C.X=X; C.Y=Y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),C);   
}
struct Node{
	int zz[128],fa;
}tr[1000000];

void begin(){
	Goto(0,0);
	printf("");
}

int main(){
	begin();
	return 0;
}
