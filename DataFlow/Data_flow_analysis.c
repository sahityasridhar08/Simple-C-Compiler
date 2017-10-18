#include<stdio.h>
struct statement{
  char variable;
  int dno;};
struct block{
  int no_statements;
  struct statement s[20];
  int gensize;
  int gen[20];
  int killsize;
  int kill[20];
  int IN[20];
  int isOUTempty;
  int OUT[20];};
struct defblockmap{
  int dno;
  int bno;};
struct definitionmap{
  char variable;
  int dbmapsize;
struct defblockmap dbmap[20];};
int no_blocks = 0;
struct block b[20];
int globalno = 0;
int blockflow[20][20];
struct definitionmap dm[20];
int dmno = 0;
int findIndex(char variable){
int i;
for(i=0;i<dmno;i++){
if(dm[i].variable==variable)
return i;}
return -1;}
int isAvailableIndex(int bno, struct definitionmap dm){
int i;
for(i=0;i<dm.dbmapsize;i++){
if(dm.dbmap[i].bno == bno)
return i;}
return -1;}
void copy(int src[20],int dest[20]){
int i;
for(i=0;i<globalno;i++)
dest[i] = src[i];}
int isEqual(int p[20],int q[20]){
int i;
for(i=0;i<globalno;i++){
if(p[i]!=q[i])
return 0;}
return 1;}
void initEmpty(int p[20]){
int i;
for(i=0;i<globalno;i++)
p[i] = 0;}
void subtract(int c[20],int a[20],int b[20]){
int i;
for(i=0;i<globalno;i++){

if(a[i]==1 && b[i]==1)
c[i] = 0;
else
c[i] = a[i];}}

void unionset(int c[20],int a[20],int b[20]){
int i;
for(i=0;i<globalno;i++){
if(a[i]==1 || b[i]==1)
c[i] = 1;
else
c[i] = 0;}}
void display(char step){
int i,j;
if(step=='1')
for(i=0;i<no_blocks;i++){
printf("\nBlock %d\nNo of Statements : %d",i+1,b[i].no_statements);
for(j=0;j<b[i].no_statements;j++)
printf("\nStatement %d : Variable - %c , Dno - %d",j+1,b[i].s[j].variable,b[i].s[j].dno);}
else if(step=='2'){
for(i=0;i<dmno;i++){
printf("\n\nVariable : %c",dm[i].variable);
for(j=0;j<dm[i].dbmapsize;j++)
printf("\nd%d in B%d",dm[i].dbmap[j].dno + 1,dm[i].dbmap[j].bno + 1);}}

else if(step=='3'){
printf("\nGEN : ");
for(i=0;i<no_blocks;i++){
printf("\nBlock %d : ",i+1);
for(j=0;j<globalno;j++)
printf("%d ",b[i].gen[j]);}
printf("\nKILL : ");
for(i=0;i<no_blocks;i++){
printf("\nBlock %d : ",i+1);
for(j=0;j<globalno;j++)
printf("%d ",b[i].kill[j]);}}

else if(step=='4'){
printf("\nIN : ");
for(i=0;i<no_blocks;i++){
printf("\nBlock %d : ",i+1);
for(j=0;j<globalno;j++)
printf("%d ",b[i].IN[j]);}
printf("\nOUT : ");
for(i=0;i<no_blocks;i++){
printf("\nBlock %d : ",i+1);
for(j=0;j<globalno;j++)
printf("%d ",b[i].OUT[j]);}}}

int main(){
int i,j,k,index,flag;
char tempstatement[50];
int NEWIN[20], NEWOUT[20], temp[20];
printf("No of Blocks : ");
scanf("%d",&no_blocks);
for(i=0;i<no_blocks;i++){
for(j=0;j<globalno;j++){
b[i].kill[j] = 0;
b[i].gen[j] = 0;
b[i].isOUTempty = 1;}

initEmpty(b[i].IN);
initEmpty(b[i].OUT);
printf("Block %d\nNo of Statements : ",i+1);
scanf("%d",&b[i].no_statements);
for(j=0;j<b[i].no_statements;j++){
printf("Statement %d",j+1);
b[i].s[j].dno = globalno;
globalno++;
printf("\nType a statement : ");
scanf("%s",tempstatement);
b[i].s[j].variable = tempstatement[0];}}

for(i=0;i<no_blocks;i++)
for(j=0;j<no_blocks;j++)
if(i!=j) {
printf("Any flow from B%d to B%d? [0/1] ",i+1,j+1);
scanf("%d",&blockflow[i][j]);}
for(i=0;i<no_blocks;i++)
for(j=0;j<b[i].no_statements;j++){
index = findIndex(b[i].s[j].variable);
if(index==-1){
dm[dmno].variable = b[i].s[j].variable;
dm[dmno].dbmap[0].dno = b[i].s[j].dno;
dm[dmno].dbmap[0].bno = i;
dm[dmno].dbmapsize = 1;
dmno++;}
else{
dm[index].dbmap[dm[index].dbmapsize].dno = b[i].s[j].dno;
dm[index].dbmap[dm[index].dbmapsize].bno = i;
dm[index].dbmapsize++;}}

for(i=0;i<no_blocks;i++){
for(j=0;j<dmno;j++){
index = isAvailableIndex(i,dm[j]);
if(index!=-1){
for(k=0;k<dm[j].dbmapsize;k++){
if(k!=index)
b[i].kill[dm[j].dbmap[k].dno] = 1;
else
b[i].gen[dm[j].dbmap[k].dno] = 1;}}}}

do{
flag = 0;
for(i=0;i<no_blocks;i++){
initEmpty(NEWIN);
// IN = U ( OUT(pred) )
for(k=0;k<no_blocks;k++)
if(blockflow[k][i]==1){
if(b[k].isOUTempty==1)
unionset(NEWIN,NEWIN,b[k].gen);
else
unionset(NEWIN,NEWIN,b[k].OUT);}
if(isEqual(b[i].IN,NEWIN)==0)
copy(NEWIN,b[i].IN);
// OUT = gen U ( IN - kill )
initEmpty(temp);
initEmpty(NEWOUT);
subtract(temp,b[i].IN,b[i].kill);
unionset(NEWOUT,b[i].gen,temp);

if(isEqual(b[i].OUT,NEWOUT)==0){
flag = 1;
copy(NEWOUT,b[i].OUT);
if(b[i].isOUTempty==1)
b[i].isOUTempty = 0;}}

}while(flag==1);
//display('2');
display('3');
display('4');
return 0;}
