//Program to demonstrate construction of Decision tree, given attributes and values
//The following program demonstrated multi-way split for Nominal and Ordinal values

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

struct table 
{
	char att[20][20];
	char val[20][20];
};
struct table data[20];
struct table new[20];

struct attribute 
{
	char name[20];
	char type[20][20];
	int count;
};
struct attribute a[20];

struct node 
{
	struct node *link[20];
	char label[20];
	int count;
};
typedef struct node *node;
int flag,nn;
float min,par;

//Create a new node for decision tree
node createnode() 
{
	node N;
	int i;
	N=(node)malloc(sizeof(struct node));
	if(N==NULL) 
	{
		printf("Out of memory\n");
		return;
	}
	N->count=0;
	for(i=0;i<20;i++)
		N->link[i]=NULL;
	return N;
}

//Check the stopping criterion for decision tree
int stopcond(struct table array[],int size) 
{
	int s;
	char *c;
	c=array[0].val[nn-1];
	for(s=1;s<size;s++) 
	{
		if(strcmp(array[s].val[nn-1],c)!=0)
			return 0;
	}
	return 1;
}

//Select the best split using available attributes and corresponding values
//at a node of Decision tree, by computing Gini Index for each attribute
float gini[20];
int bestsplit(struct table array[],int size)
{
	float gtemp[20],sum1[20],count[20];
	int b,c,d,e,v;
	for(b=0;b<nn-1;b++)
	{
		gini[b]=0;
		for(c=0;c<a[b].count;c++)
		{
			par=0;
			sum1[c]=0;
			for(d=0;d<20;d++)
				count[d]=0;
			for(d=0;d<size;d++)
			{
				if(strcmp(array[d].val[b],a[b].type[c])==0)
				{
					for(e=0;e<a[nn-1].count;e++)
					{
						if(strcmp(array[d].val[nn-1],a[nn-1].type[e])==0)
						{
							count[e]++;
							sum1[c]++;
						}
					}
				}
			}
			for(e=0;e<a[nn-1].count;e++) 
			{
				if(sum1[c] != 0) {
					par += pow((count[e]/sum1[c]),2);
				}
			}
			gtemp[c]=1.0-par;
		}
		for(c=0;c<a[b].count;c++)
		{
			gini[b] += gtemp[c]*(sum1[c]/size);
		}
	}
	min=gini[0];
	v=0;
	for(b=1;b<nn-1;b++) {
		if(gini[b]<min) {
			v=b;
			min=gini[b];
		}
	}
	return v;
}

//Assign a class label to the node or select an attribute and split based on its values
node Treegrowth(struct table array[],int size) 
{
	int x,y,i,j,k,l,m;
	node temp,C,root;
	x=stopcond(array,size);
	if(x==1)
	{
		temp=createnode();
		strcpy(temp->label,array[0].val[nn-1]);
		return temp;
	}
	else 
	{
		root=createnode();
		C=createnode();
		y=bestsplit(array,size);
		strcpy(root->label,a[y].name);
		for(i=0;i<nn-1;i++)
		{
			if(strcmp(a[i].name,root->label)==0)
			{
				for(j=0;j<a[i].count;j++)
				{
					k=0;
					for(l=0;l<size;l++) 
					{
						if(strcmp(a[i].type[j],array[l].val[i])==0) 
						{
							for(m=0;m<nn;m++) {
								strcpy(new[k].val[m],array[l].val[m]);
								strcpy(new[k].att[m],array[l].att[m]);
							}
							k++;
						}
					}
					C=Treegrowth(new,k);
					root->link[root->count]=C;
					root->count++;
				}
			}
		}
	}
	return root;
}

//Compute the possible outcomes for each attribute and classes to which labels are assigned
void outcome(int size) 
{
	int j,k,l;
	for(j=0;j<nn;j++) 
	{
		for(k=0;k<size;k++) 
		{
			if(strcmp(data[k].att[j],a[j].name)==0) 
			{
				flag=0;
				if(a[j].count==0) 
				{
					strcpy(a[j].type[0],data[k].val[j]);
					a[j].count++;
				}
				else 
				{
					for(l=0;l<a[j].count;l++) 
					{
						if(strcmp(a[j].type[l],data[k].val[j])==0) 
						{
							flag=1;
							break;
						}
					}
					if(flag != 1) 
					{
						strcpy(a[j].type[a[j].count],data[k].val[j]);
						a[j].count++;
					}
				}
			}
		}
	}
}

//Display the decision tree
void display(node R) 
{
	int tmp=0;
	if(R==NULL)
		return;
	printf("%s\t",R->label);
	while(tmp < R->count) 
	{
		display(R->link[tmp]);
			printf("\n");
		tmp++;
	}
}

void main() 
{
	int i,j,number;
	node R=NULL;
	scanf("%d",&nn);
	scanf("%d",&number);
	for(i=0;i<nn;i++) 
	{
		scanf("%s",a[i].name);
		a[i].count=0;
	}
	for(i=0;i<number;i++)
	{
		for(j=0;j<nn;j++) 
		{
			scanf("%s",data[i].val[j]);
			strcpy(data[i].att[j],a[j].name);
		}
	}
	outcome(number);
	printf("Attribute set\n");
	//Print attribute set with outcomes
	for(i=0;i<nn;i++) 
	{
		for(j=0;j<a[i].count;j++) 
		{
			printf("%s\t",a[i].type[j]);
		}
		printf("\n");
	}
	for(i=0;i<number;i++)
	{
		for(j=0;j<nn;j++) 
		{
			printf("%s\t",data[i].val[j]);
		}
		printf("\n");
	}
	R=Treegrowth(data,number);
	display(R);
}
