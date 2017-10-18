#include <stdio.h>
#include<string.h>
char tac[10][5];
int label[10];
char var[30][5];
int r=0,l=0;
void assignment(char tac[10][5]){
strcpy(var[r],tac[0]);
printf("MOV R%d,#%s\n",r,tac[2]);
r++;}
int search(char a[5]){
int i;
for(i=0;i<r;++i){
if(strcmp(var[i],a)==0)
return i;}
return -1;}
void cmp(char tac[10][5]){
int index=-1,index2;
char labelval;
index=search(tac[3]);
if(isdigit(tac[5][0])){
strcpy(var[r],tac[5]);
index2=r;
printf("MOV R%d,#%s\n",index2,tac[5]);
r++;}
else{
index2=search(tac[5]);}
labelval=tac[0][1];
printf("L%c: CMP R%d,R%d\n",labelval,index,index2);
label[l++]=labelval-48;
if(strcmp(tac[4],"<=")==0){
printf("JLE %s",tac[7]);
label[l++]=tac[7][1]-48;}
else if(strcmp(tac[4],">=")==0){
printf("JGE %s",tac[7]);
label[l++]=tac[7][1]-48;}}
void unconditionalJump(char tac[10][5]){
printf("JMP %s\n",tac[1]);
label[l++]=tac[1][1]-48;}
int addition(char tac[10][5],int n){
int i,index,index2,index0;
if(tac[0][0]=='L')
printf("%s: ",tac[0]);
for(i=0;i<n;i++){
if(tac[i][0]=='+'){
index0=search(tac[i-3]);//temp variable or resultant variable
index=search(tac[i-1]); // first operand
index2=search(tac[i+1]);// second operand
if(index0==-1 && index!=-1 && index2!=-1){
printf("ADD R%d,R%d\n",index,index2);
return 100;}
else if(index2==-1 && index0==-1){
printf("MOV R%d,#%s\n",r,tac[i+1]);
printf("ADD R%d,R%d\n",index,r);
r++;
return 100;}}}}

int main(){
int i,j,res;
char str[70],*token,tempstr[70];
FILE *fm=fopen("tac.txt","r+");
while(fgets(str,70,fm)!=NULL) {
strcpy(tempstr,str);
for(i=0,token = strtok(str," ");token!=NULL;token = strtok(NULL, " ")){
//printf("%s ",token);
strcpy(tac[i++],token); }
if(strcmp(tac[1],"=")==0 && strcmp(tac[3],"+")!=0)
{ assignment(tac); } //just assignment statements
else if(strcmp(tac[2],"if")==0)
{ cmp(tac); } //if condition
else if(strcmp(tac[0],"goto")==0)
{ unconditionalJump(tac); } // unconditional Jump
else if(strstr(tempstr,"+")!=NULL){
res=addition(tac,i);
if(res==100){ fgets(str,70,fm); res=0;}}
else if(tac[0][0]=='L' && i==2){
printf("%s: \n”,tac[0]);}}return 0;}
