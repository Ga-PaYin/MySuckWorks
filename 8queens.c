#include<stdio.h>
#include<string.h>
#define true 1
#define false 0
char Queen[8][8];
int count = 0;
int safe(rank,line){
	int num, check = true;
	for(num=1;num<=rank;num++){
		if(Queen[rank-num][line] == '#'){
			check = false;
		}
	}
	for(num=1;num<=rank&&line+num<8;num++){
		if(Queen[rank-num][line+num] == '#'){
			check = false;
		}
	}
	for(num=1;num<=rank&&line-num>=0;num++){
		if(Queen[rank-num][line-num] == '#'){
			check = false;
		}
	}
	return check;
}

void setQueen(int rank){
	if(rank < 8){
		int line;
		for(line = 0;line < 8; line++){
			if(safe(rank,line)){
				Queen[rank][line] = '#';
				setQueen(rank+1);
				Queen[rank][line] = '*'; 
			}
		}
	}else{
		int i,j,OKRanks=0;
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(Queen[i][j] == '#'){
					OKRanks++;
					break;
				}
			}
		}
		if(OKRanks == 8){
			for(i=0;i<8;i++){
				for(j=0;j<8;j++){
					printf("%c",Queen[i][j]);
				}
				printf("\n");
			}
			printf("-----------------------------\n");
			count++;
		}	
	}
}
int main(){
	memset(Queen,'*',8*8*sizeof(char));
	int rank = 0;
	setQueen(rank);
	printf("%d",count);
	return 0;
}
