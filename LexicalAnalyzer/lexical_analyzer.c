//

//  Lexical Analyzer
//
//  Created by Sahitya Sridhar on 07/01/17.
//  Copyright © 2017 Sahitya Sridhar. All rights reserved.
//

#include<stdio.h>
#include<string.h>

struct table{
    char dtype[30];
    char name[30];
    int bytes,loc,val;
};
struct table symbols[10];
int main(int argc, const char * argv[]){
    char ari_ops[5];//Arithematic Operators
    
    ari_ops[0]='+';
    ari_ops[1]='-';
    ari_ops[2]='*';
    ari_ops[3]='/';
    ari_ops[4]='%';
    
    char ari_assig_ops[5][10];//Arithmetic Assignment Operators
    
    strcpy(ari_assig_ops[0],"+= ");
    strcpy(ari_assig_ops[1],"-= ");
    strcpy(ari_assig_ops[2],"*= ");
    strcpy(ari_assig_ops[3],"/= ");
    strcpy(ari_assig_ops[4],"%= ");
    
    char log_ops[3][10];//Logical Operators
    
    strcpy(log_ops[0],"&& ");
    strcpy(log_ops[1],"|| ");
    strcpy(log_ops[2],"! ");
    
    char rel_ops[7][10];//Relational Operators
    
    strcpy(rel_ops[0],"<");
    strcpy(rel_ops[1],"> ");
    strcpy(rel_ops[2],">= ");
    strcpy(rel_ops[3],"<= ");
    strcpy(rel_ops[4],"== ");
    strcpy(rel_ops[5],"!= ");
    
    char bit_ops[6][10];//Bitwise Operatore
    
    strcpy(bit_ops[0],"ˆ ");
    strcpy(bit_ops[1],"& ");
    strcpy(bit_ops[2],"| ");
    strcpy(bit_ops[3],"<< ");
    strcpy(bit_ops[4],">> ");
    
    char un_ops[4][10];//Unary Operators
    
    strcpy(un_ops[0],"- ");
    strcpy(un_ops[1],"++ ");
    strcpy(un_ops[2],"-- ");
    
    char assig_ops[2];//Assignment Operators
    
    assig_ops[0]='=';
    
    char sp_char[10]; //Special Characters
    
    sp_char[0]='{';
    sp_char[1]='}';
    sp_char[2]='[';
    sp_char[3]=']';
    sp_char[4]='(';
    sp_char[5]=')';
    sp_char[6]=';';
    sp_char[7]=',';
    sp_char[8]='.';
    sp_char[9]='\0';
    
    char pre_proc_dir[5][30];//Preprocessor Directives
    
    strcpy(pre_proc_dir[0],"#include<stdio.h> ");
    strcpy(pre_proc_dir[1],"#include<conio.h> ");
    strcpy(pre_proc_dir[2],"#include<string.h> ");
    strcpy(pre_proc_dir[3],"#include<stdlib.h> ");
    strcpy(pre_proc_dir[4],"#include<math.h> ");
    
    char keywords[32][30];//Keywords
    
    strcpy(keywords[0],"auto ");
    strcpy(keywords[1],"break ");
    strcpy(keywords[2],"case ");
    strcpy(keywords[3],"char ");
    strcpy(keywords[4],"const ");
    strcpy(keywords[5],"continue ");
    strcpy(keywords[6],"default ");
    strcpy(keywords[7],"do ");
    
    strcpy(keywords[8],"double ");
    strcpy(keywords[9],"else\n");
    strcpy(keywords[10],"enum ");
    strcpy(keywords[11],"extern ");
    strcpy(keywords[12],"float ");
    strcpy(keywords[13],"for ");
    strcpy(keywords[14],"goto ");
    strcpy(keywords[15],"if ");
    
    strcpy(keywords[16],"int ");
    strcpy(keywords[17],"long ");
    strcpy(keywords[18],"register ");
    strcpy(keywords[19],"return");
    strcpy(keywords[20],"short ");
    strcpy(keywords[21],"signed ");
    strcpy(keywords[22],"sizeof ");
    strcpy(keywords[23],"static ");
    
    strcpy(keywords[24],"struct ");
    strcpy(keywords[25],"switch ");
    strcpy(keywords[26],"typedef ");
    strcpy(keywords[27],"union ");
    strcpy(keywords[28],"unsigned ");
    strcpy(keywords[29],"void ");
    strcpy(keywords[30],"volatile ");
    strcpy(keywords[31],"while ");
    
    char func_calls[6][10];//Function Calls
    
    strcpy(func_calls[0],"printf ");
    strcpy(func_calls[1],"scanf ");
    strcpy(func_calls[2],"getch() ");
    strcpy(func_calls[3],"clrscr() ");
    strcpy(func_calls[4],"main() ");
    
    FILE *fp;
    char ch,fname[100],str1[200];
    strcpy(fname,"programsource.txt");
    int i=0,stop1=0,j,found=0,flag=0,k=0,loca=1000;
    fp=fopen(fname,"r");
    if(fp==NULL)
        printf("Error");
    fseek(fp,0,0);
    int flagprintf=0;
    int fint=0,fdoub=0,ffloat=0,fvoid=0,fchar=0;
    while(!feof(fp)){
    	ch=getc(fp);
    	//printf("%c %d\n",ch,ch);
    	char str[101];
    	if(ch==13 || ch==10 || ch==-1){
        	//printf("Here");
            flag=0;
            //printf("%d",i);
            str1[i]='\0';
            strcpy(str,str1);
            stop1=1;
            /*if(str[0]==' ' || str[0]=='\n'){ //Remove unnecessary white spaces
                i=0;
                str1[0]='\0';
                stop1=0;
                continue;
            }*/
            printf("%s\n",str);
            i=0;
            str1[0]='\0'; //Reset the string
        }
    	//printf("%c %d\n",ch,ch);
        if(flagprintf==1){
            if(ch!=')')
                continue;
            else{
                flagprintf=0;
                continue;
            }
        }
        str1[i++]=ch;
        if(stop1==1){
            for(j=0;j<32;j++){
                if(strcmp(str,keywords[j])==0 ){
                    str[strlen(str)-1]='\0';
                    printf("%s is a keyword\n\n",str);
                    if(j==3){
                        strcpy(symbols[k].dtype,str);
                        fchar=1;
                    }
                    if(j==8){
                        strcpy(symbols[k].dtype,str);
                        fdoub=1;
                    }
                    if(j==12){
                        strcpy(symbols[k].dtype,str);
                        ffloat=1;
                    }
                    if(j==16){
                        strcpy(symbols[k].dtype,str);
                        strcpy(symbols[k+1].dtype,str);
                        fint=1;
                        symbols[k].bytes=symbols[k+1].bytes=2;
                        symbols[k].loc=1000;
                        symbols[k+1].loc=symbols[k].loc+symbols[k+1].bytes;
                    }
                    if(!strcmp(keywords[29],str)){
                        strcpy(symbols[k].dtype,str);
                        fvoid=1;
                    }
                    stop1=0;
                    flag=1;
                }
            }
            for(j=0;j<5;j++){
                if(!strcmp(str,pre_proc_dir[j])){
                    str[strlen(str)-1]='\0';
                    printf("%s is a preprocessor directive\n\n",str);
                    flag=1;
                    stop1=0;
                }
                else if(!strcmp(str,func_calls[j])){
                    flag=1;
                    stop1=0;
                    str[strlen(str)-1]='\0';
                    printf("%s is a function\n\n",str);
                    if(strstr(func_calls[0],str)){
                        flagprintf=1;
                        /*while(ch=fgetc(fp)!=')'){
                         printf("%c \t",ch);
                         continue;
                         }*/
                    }
                }
                else if(!strcmp(str,bit_ops[j])){
                    printf("%s is a bit ops\n\n",str);
                    flag=1;
                    stop1=0;
                }
                else if(!strcmp(str,ari_assig_ops[j])){
                    printf("%s is an arithmetic assignment ops\n\n",str);
                    flag=1;
                    stop1=0;
                }
            }
            for(j=0;j<5;j++){
                if(str[0]==ari_ops[j]){
                    printf("%s is an arithmetic ops\n\n",str);
                    flag=1;
                    stop1=0;
                }
            }
            if(str[0]==assig_ops[0]){
                printf("%s is an assignment op\n\n",str);
                flag=1;
                stop1=0;
            }
            for(j=0;j<3;j++){
                if(!strcmp(str,log_ops[j])){
                    printf("%s is a logical op\n\n",str);
                    flag=1;
                    stop1=0;
                }
                if(!strcmp(str,un_ops[j])){
                    printf("%s is a unary op\n\n",str);
                    flag=1;
                    stop1=0;
                }
            }
            for(j=0;j<7;j++){
                if(!strcmp(str,rel_ops[j])){
                    printf("%s is a relational op\n\n",str);
                    flag=1;
                    stop1=0;
                }
            }
            
            for(j=0;j<9;j++){
                if(str[0]==sp_char[j]){
                    str[strlen(str)-1]='\0';
                    printf("%s is a special character\n\n",str);
                    flag=1;
                    stop1=0;
                    if(str[0]==';'){
                        if(fint)
                            fint=0;
                    }
                }
            }	
            if(!flag){
                if(str[0]>='0' && str[0]<='9'){
                    printf("%s is an constant\n\n",str);
                    stop1=0;
                    flag=1;
                    symbols[k].val=(int)str;
                    
                }
                else{
                    printf("%s is an identifier \n\n",str);
                    if(fint){
                        strcpy(symbols[k].name,str);
                    }
                    flag=1;
                    stop1=0;
                    k++;
                    
                }
            }
            
        }
    }
   /* printf("\n \n\t\t-----Symbol Table------\n\n");
    printf("Name\ttype\tbytes\tlocation\tvalue\n");	
    for(i=0;i<k;i++){
        printf("%s\t%s\t%d\t%d\t\t%d\n",symbols[i].name,symbols[i].dtype,symbols[i].bytes,symbols[i].loc,symbols[i].val);
    }	*/
    fclose(fp);
    return 0;
}

