
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>

char tokens[50][10];

struct dead{
	char label[20];
	int flag;
	int nlines;
	int line[5];
}var[20];

int varlen=0;
int lineNo=0;

int find(char *s){
	int i;
	for(i=0;i<varlen;i++){
		if(strcmp(var[i].label,s)==0)
			return i;
	}
	return -1;
}

void getLiveCode(FILE *f, FILE *g){
	int i,j,k=0,n;
	int rmlines[20];
	char tac[50];
	for(i=0;i<varlen;i++){
		if(var[i].flag==0)
			for(j=0;j<var[i].nlines;j++)
					rmlines[k++] = var[i].line[j];
	}
	n=k;
	k=1;
	while(fgets(tac,50,f)){
		for(i=0;i<n;i++) {
			if(rmlines[i]==k) break;
		}
		if(i==n){
			printf("%s",tac);
			fputs(tac,g);
		}
		k++;
	}
}

void deadCode(int l){
	lineNo++;
	int n,m,j;
	n = atoi(tokens[4]);
	m = atoi(tokens[2]);
	j =  find(tokens[0]);
	if(varlen==0 || j==-1){
		strcpy(var[varlen].label,tokens[0]);
		var[varlen].flag = 0;
		var[varlen].line[0] = lineNo;
		var[varlen].nlines = 1;
		varlen++;
	}
	else if(j > -1){
		if(var[j].flag == 0){
			var[j].line[var[j].nlines] = lineNo;
			var[j].nlines++;
		}
		else{
			var[j].flag = 0;
			var[j].line[var[j].nlines-1] = lineNo;
		}
	}
	if (m==0){
		j= find(tokens[2]);
		if(j > -1){
			if(var[j].nlines==1) var[j].flag = 1;
			else { //remove previous assignments & keep the latest one
				var[j].nlines--;
				var[j].flag = 0;
			}
		} 
	}
	if(n==0 && strcmp(tokens[4],"0") && l>3){
		j = find(tokens[4]);	
		if(j > -1){
			if(var[j].nlines==1) var[j].flag = 1;
			else {
				var[j].nlines--;
				var[j].flag = 0;
			}
		} 
	}
}

int optimize(int l){
	int n,m,i,j;
	float f;
	if(l<4) {for(i=0;i<l;i++) printf("%s",tokens[i]); return;}
	n = atoi(tokens[4]);
	m = atoi(tokens[2]);
	if(n==0 && strcmp(tokens[4],"0")){
		j = find(tokens[4]);	
		if(j > -1) var[j].flag = 1;
	}
	//constant folding
	if(m!=0 && n!=0){
		if(strcmp(tokens[3],"+")==0) printf("%s = %d\n",tokens[0],m+n);
		if(strcmp(tokens[3],"*")==0) printf("%s = %d\n",tokens[0],m*n);
		if(strcmp(tokens[3],"/")==0) printf("%s = %d\n",tokens[0],m/n);
		if(strcmp(tokens[3],"-")==0) printf("%s = %d\n",tokens[0],m-n);
	}
	//algebric identities
	else if(strcmp(tokens[3],"*")==0 && strcmp(tokens[4],"1")==0) printf("%s = %s\n",tokens[0],tokens[2]);
	else if(strcmp(tokens[3],"+")==0 && strcmp(tokens[4],"0")==0) printf("%s = %s\n",tokens[0],tokens[2]);
	//strength reduction
	else if(strcmp(tokens[3],"*")==0 && ceilf(f =log2(n))==f) printf("%s = %s << %d\n",tokens[0],tokens[2],(int)f);
	else if(strcmp(tokens[3],"/")==0 && ceilf(f =log2(n))==f) printf("%s = %s >> %d\n",tokens[0],tokens[2],(int)f);
	else if(strcmp(tokens[3],"**")==0){
		printf("%s = %s * %s\n",tokens[0],tokens[2],tokens[2]);
		for ( i=1;i<n;i++)
			printf("%s = %s * %s\n",tokens[0],tokens[0],tokens[2]);
	}
	else if(strcmp(tokens[3],"*")==0){
		printf("%s = %s + %s\n",tokens[0],tokens[2],tokens[2]);
		for ( i=1;i<n;i++)
			printf("%s = %s + %s\n",tokens[0],tokens[0],tokens[2]);
	}
	else for(i=0;i<l;i++) printf("%s ",tokens[i]);
}

int tokenize(char *str){
	int i=0;
	char *s = strtok(str," ");
	while(s != NULL){
		strcpy(tokens[i++],s);
		s = strtok(NULL," ");
	}
	return i;
}


int main(){
	char tac[50];
	int l;
	FILE *f = fopen("D:/College/SEM 6/Compiler LAB/code.txt","r");
	FILE *g = fopen("D:/College/SEM 6/Compiler LAB/optimized.txt","w");
	if(f == NULL || g == NULL){
		printf("File does not exist");
		return 1;
	}
	printf("\nORIGINAL CODE\n");
	while(fgets(tac,50,f)){
		printf("%s",tac);
		l = tokenize(tac);
		deadCode(l);
	}
	fclose(f);
	f = fopen("D:/College/SEM 6/Compiler LAB/code.txt","r");
	printf("\nNON-DEAD CODE\n");
	getLiveCode(f,g);
	fclose(f);
	fclose(g);
	g = fopen("D:/College/SEM 6/Compiler LAB/optimized.txt","r");
	printf("\nOPTIMIZED CODE\n");
	while(fgets(tac,50,f)){
		l = tokenize(tac);
		optimize(l);
	}
	fclose(g);
}
