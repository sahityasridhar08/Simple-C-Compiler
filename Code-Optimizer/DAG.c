#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//DAG node
struct node
{
	char val[20];
	struct node *left;
	struct node *right;
	char labels[100];
};

struct node *tree[50];
int ctr=0;

void makeNew(char label[],char opd1[],char op[],char opd2[]){
	tree[ctr] = malloc(sizeof(struct node));
	strcpy(tree[ctr]->val,op);
	strcpy(tree[ctr]->labels, label);
	
	tree[ctr]->left=malloc(sizeof( struct node));
	strcpy(tree[ctr]->left->val, opd1);
	tree[ctr]->left->left=NULL;
	tree[ctr]->left->right=NULL;
	
	tree[ctr]->right=malloc( sizeof(struct node));
	strcpy(tree[ctr]->right->val, opd2);
	tree[ctr]->right->left=NULL;
	tree[ctr]->right->right=NULL;
	ctr++;
}

void create(char label[],char opd1[],char op[],char opd2[])
{
    int i;
	struct node *tmp;
	int leftflag= 0, rightflag = 0;
	if(ctr==0)
	{
		makeNew(label,opd1,op,opd2);
		return;
	} 
	tree[ctr] = malloc(sizeof(struct node));
	if(strcmp(op,"-1")==0 && strcmp(opd2,"-1")==0){
		for(i=0;i<ctr;i++){
			tmp = tree[i];
			if(strstr(tmp->labels,opd1)!=NULL){
				strcat(tmp->labels,",");
                strcat(tmp->labels,label);
				return;
			}	
			else if(strcmp(tmp->left->val,opd1)==0){
				strcpy(tree[ctr]->labels,label);
				tree[ctr]->left = tmp->left;
				tree[ctr]->right = NULL;
				ctr++;
				return;
			}
			else if(strcmp(tmp->right->val,opd1)==0){
				strcpy(tree[ctr]->labels,label);
				tree[ctr]->left = tmp->right;
				tree[ctr]->right = NULL;
				ctr++;
				return;
			}
		}
	}
	else{
		strcpy(tree[ctr]->val,op);
		for(i=0;i<ctr;i++){
			tmp = tree[i];
			if(strcmp(opd1,tmp->left->val)==0 && strcmp(opd2,tmp->right->val)==0 && strcmp(op,tmp->val)==0)
			{
                strcat(tmp->labels,",");
                strcat(tmp->labels,label);
				free(tree[ctr]);
                return;
			}
			else{
				//match left operand
				if(strstr(opd1,tmp->labels) != NULL) {tree[ctr]->left = tmp; leftflag=1;}//with label
				else if(strcmp(opd1,tmp->left->val)==0)	{tree[ctr]->left = tmp->left; leftflag=1;}//with left child
				else if(strcmp(opd1,tmp->right->val)==0){tree[ctr]->left = tmp->right; leftflag=1;}//with right child
				//match right operand
				if(strstr(opd2,tmp->labels) != NULL) {tree[ctr]->right = tmp; rightflag=1;}//with label
				else if(strcmp(opd2,tmp->left->val)==0) {tree[ctr]->right = tmp->left; rightflag=1;} //with left child
				else if(strcmp(opd2,tmp->right->val)==0) {tree[ctr]->right = tmp->right; rightflag=1;} //with right child
			}
			if(leftflag && rightflag){strcpy(tree[ctr]->labels, label);ctr++; return;}
		}
		if(leftflag == 0 && rightflag==1){
			tree[ctr]->left=malloc(sizeof( struct node));
			strcpy(tree[ctr]->left->val, opd1);
			strcpy(tree[ctr]->labels,label);
			tree[ctr]->left->left=NULL;
			tree[ctr]->left->right=NULL;
			leftflag =1;
			ctr++;
		}
		else if(leftflag==1 && rightflag==0){
			tree[ctr]->right=malloc( sizeof(struct node));
			strcpy(tree[ctr]->right->val, opd2);
			strcpy(tree[ctr]->labels,label);
			tree[ctr]->right->left=NULL;
			tree[ctr]->right->right=NULL;
			rightflag=1;
			ctr++;
		}
		else {
			
			makeNew(label,opd1,op,opd2);
		}
	}
}

void printDAG()
{
	
    int i;
    for(i=0;i<ctr;i++)
    {
		printf("\nLabels: %s",tree[i]->labels);
		printf("\nValue: %s",tree[i]->val);
		printf("\nLeft child: %s",tree[i]->left->val);
		printf("\nRight child: %s\n",tree[i]->right->val);
    }
}


int main()
{
	char input[50];
	char op[20],opd1[10],opd2[10], label[10];
	int flag,i,j,space,at;
	FILE * f = fopen("/Users/cseb65/Desktop/dag/code.txt","r");
	while(fgets(input,50,f))
	{
		for(i=0,flag=0,j=0,space=0; input[i]!='\0';i++)
		{
			if(input[i]!=' ' && !flag)
				label[j++]=input[i];
			else if(input[i]==' ' && input[i+1]=='=')
			{
				flag=1;
				label[j]='\0';
			}
			else if(flag && input[i]!=' ' && space==1)
			{
				opd1[j++]=input[i];
			}
			else if(flag && input[i]!=' ' && space==2)
			{
				op[j++]=input[i];
			}
			else if(flag && input[i]!=' ' && space==3)
			{
				opd2[j++]=input[i];
			}
			else if(input[i]==' ' || input[i]=='\n')
			{ 
				if(space==1)opd1[j]='\0';
				else if(space==2)op[j]='\0';
				else if(space==3)opd2[j]='\0';
				space++;j=0;
			}
		}
		//printf("space is : %d\n",space);
		if(space>=3)
		{    
			printf("label = operand1 operator operand2 : %s = %s %s %s.\n",label,opd1,op,opd2);
			//create node.
			
			create(label,opd1,op,opd2);
		}
		else if(space==2)
		{ 
			
			for(i=0,flag=0;opd1[i]!='\0'; i++)
			{
				if(opd1[i]=='[')
				{    
					at=i;
					flag=1;
					op[0]='[',op[1]=']',op[2]='\0' ;
					j=0;
					while(opd1[++i]!=']')opd2[j++] =opd1[i];
					opd2[j]='\0';
					opd1[at]='\0';
					break;
				}
			}
			if(!flag)
			{
				printf("label = operand1 : %s=%s.\n",label,opd1);
				//create nodes
				create(label,opd1,"-1","-1");
			}
			else 
			{ 
				printf("label = operand1 operator operand2 : %s=%s%s%s.\n",label,opd1,op, opd2);    
				//create nodes
				create(label,opd1,op,opd2);
			}
		} 
	}
	
	printDAG();
	return 0;
}
