//Program to demonstrate insertion and search operation in a B+ tree
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key[2],count;
	struct node *pptr,*ptr[3];
};

typedef struct node *node;
node R;
int order=3,tarr[3];

//Create new node in the tree
node getnode(node N)
{
	N=(node)malloc(sizeof(struct node));
	int i;
	N->pptr=NULL;
	for(i=0;i<2;i++)
		N->key[i]=0;
	for(i=0;i<3;i++)
		N->ptr[i]=NULL;
	N->count=0;
	return N;
}

//Find the appropriate leaf node to insert
node find(node root,int k)
{
	node t=root;
	int i,count;
	while(t->ptr[0] != NULL) 
	{
		count=t->count;
		for(i=0;i<(t->count);i++) 
		{
			if(t->key[i]>k) 
			{
				t=t->ptr[i];
				break;
			}
		}
		if(i != count)
			continue;
		else
			t=t->ptr[i];
	}
	return t;
}

//Add value into a node
node addinto(node N,int v,node pr) 
{
	int count;	
	count=N->count;
	N->key[count]=v;
	count++;
	N->count++;
	if(N->ptr[0] != NULL)
		N->ptr[count]=pr;
	return N;
}

//Search a key node in the tree
void search(int k,node root) 
{
	int i;
	while(root->ptr[0] != NULL)
		root=root->ptr[0];
	while(root != NULL) 
	{
		i=0;
		while(i < root->count) 
		{
			if(root->key[i] == k)
			{
				printf("Key found\n");
				return;
			}
			i++;
		}
		root=root->ptr[2];
	}
	printf("Key not found\n");
	return;
}

//Insert into the tree with reconstruction of tree
node insertentry(node L,int value,node p) 
{
	node T;
	int i,j,count,m,X,temp;
	if(L->count != 2) 
	{
		if(L->count==0)	
		{
			L=addinto(L,value,p);
			return L;
		}
		if(L->key[0]<value)
			L=addinto(L,value,p);
		else 
		{
			L->key[1]=L->key[0];
			L->key[0]=value;
			if(L->ptr[0] != NULL)
				L->ptr[2]=L->ptr[1];
			L->ptr[1]=p;
			if(p != NULL)
				p->pptr=L;
			L->count++;
		}
		return R;
	}
	m=1;
	for(i=0;i<2;i++)
		tarr[i]=L->key[i];
	tarr[2]=value;
	for(i=0;i<3;i++) 
	{
		for(j=i;j<3;j++) 
		{
			if(tarr[i]>tarr[j]) 
			{
				temp=tarr[i];
				tarr[i]=tarr[j];
				tarr[j]=temp;
			}
		}
	}
	X=tarr[1];
	T=getnode(T);
	if(L->ptr[0]==NULL) 
	{
		for(i=m;i<2;i++) 
		{
			T=addinto(T,X,p);
			L->key[i]=0;
			L->ptr[i]=NULL;
			(L->count)--;
		}
		T=addinto(T,tarr[2],p);
		L->key[0]=tarr[0];
	}
	else 
	{
		for(i=m;i<2;i++) 
		{
			L->key[i]=0;
			(L->count)--;
		}
		L->key[0]=tarr[0];
		T=addinto(T,tarr[2],p);
		T->ptr[0]=L->ptr[2];
		(L->ptr[2])->pptr=T;
		L->ptr[2]=NULL;
		p->pptr=T;
	}
	if(L->pptr != NULL)
		R=insertentry(L->pptr,X,T);
	else 
	{
		R=getnode(R);
		R->key[0]=X;
		R->count=1;
		R->ptr[0]=L;
		R->ptr[1]=T;
		L->pptr=R;
		T->pptr=R;
	}
	if(L->ptr[0] == NULL) 
	{
		T->ptr[2]=L->ptr[2];
		L->ptr[2]=T;
	}	
	return R;
}

//Check if new value already exists, else insert into the tree
node insert(int value,node p,node R) 
{
	node L;
	L=find(R,value);
	R=insertentry(L,value,p);
	return R;
}

//Display all leaf elements in order, starting from the left most leaf
void traverse(node R) 
{
	int i;	
	while(R != NULL) 
	{
		i=0;
		while(i < R->count) 
		{
			printf("%d\t",R->key[i]);
			i++;
		}
		R=R->ptr[2];
	}
}

//Traverse to the left most leaf
void display(node R) 
{
	while(R->ptr[0] != NULL)
		R=R->ptr[0];
	traverse(R);
	return;
}

void main() 
{
	int ch,val,choice,op,key;
	R=getnode(R);
	do 
	{
		printf("Enter your choice\n 0.Insert\n 1.Search\n 2.Display\n");
		scanf("%d",&op);
		switch(op) 
		{
			case 0: 
				//Insertion and display
				do 
				{
					printf("Enter the value you want to insert\n");
					scanf("%d",&val);
					R=insert(val,NULL,R);
					//Display tree elements upon each element insertion
					display(R);
					printf("\n");
					printf("Do you want to insert more elements? (1 for continue)\n");
					scanf("%d",&ch);
				}while(ch==1);
				break;
				
			case 1: 
				//Search for a key in tree
				printf("Enter the key you want to search\n");
				scanf("%d",&key);
				search(key,R);
				break;
			
			case 2:
				//Just display the tree elements
				display(R);
				printf("\n");
				break;
				
			default:
				printf("Invalid choice\n");
				break;
		}
		printf("Do you want to continue? (1 for continue)\n");
		scanf("%d",&choice);
	}while(choice==1);
}
