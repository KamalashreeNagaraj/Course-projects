//Compute first update of page rank for a set of pages
#include<stdio.h>
#include<stdlib.h>

struct node {
	int info;
	struct node *link[15];
	float rank;
	int count;
	int visited;
};

typedef struct node *node;
node q=NULL;
static int gName=0;
int count=0;

//Create new node in the tree
node getnode(int vis) {
	node N;
	int i=0;
	N=(node)malloc(sizeof(struct node));
	if(N==NULL) {
		printf("\n No memory ");
		exit(0);
	}
	while(i<15) {
		N->link[i]=NULL;
		i++;	
	}
	N->rank=0;
	N->count=0;
	N->visited=vis;
	return N;
}

//Search for the info in the existing tree
void Search(int info,node root,int vis) {
	int i=0;
	if(root->visited==vis)
		return;	
	if(root->info==info) {
		q=root;
	}
	root->visited=vis;
	while(i<root->count) {	
		Search(info,root->link[i],vis);
		i++;
	}
}

//Insert node into the tree
node Insert(int info1,int info2,node root) {
	node temp1,temp2;
	int visit;
	temp1=getnode(1);
	//if tree is empty
	if(root==NULL) {
		temp2=getnode(1);
		temp1->info=info1;
		temp2->info=info2;
		temp1->link[temp1->count]=temp2;
		temp1->count++;
		root=temp1;
		return root;
	}
	q=NULL;
	if(root->visited==0) 
		Search(info1,root,1);
	else
		Search(info1,root,0);
	//If first page is not requested by any other page
	if(q==NULL) {
		printf("The page inserted cannot be compared with any other page\n");
		return root;
	}
	temp1=q;
	q=NULL;
	if(root->visited==0) 
		Search(info2,root,1);
	else
		Search(info2,root,0);
	visit=root->visited;
	//If second page is requested only by first page, create new page for second page
	if(q==NULL) {
		q=getnode(visit);
		q->info=info2;
		temp1->link[temp1->count]=q;
		temp1->count++;
		return root;
	}
	//Else link second page to first page
	temp1->link[temp1->count]=q;
	temp1->count++;
	return root;
}

//Count number of pages in the tree
void countnode(node root,int vis) {
	int i=0;
	if(root->visited==vis)
		return;
	root->visited=vis;
	count++;
	while(i<root->count) {
		countnode(root->link[i],vis);
		i++;
	}
}

//Compute rank for each page
void rank(node root,int vis) {
	int i;
	if(root->visited == vis)
		return;
	i=0;
	root->visited=vis;
	while(i < root->count) {			
		root->link[i]->rank += 1.0/(count * root->count);
		rank(root->link[i],vis);
		i++;
	}
}

//Print rank of each page
void printrank(node root,int vis) {
	int i=0;
	if(root->visited==vis)
		return;
	root->visited=vis;
		printf("%d\t%f\n",root->info,root->rank);
	while(i < root->count) {
		printrank(root->link[i],vis);
		i++;
	}
}

//Display dotty output of pages
void preorderDotDump (node root, FILE* outputFile,int visit)
{
	int i=0;
	if(root->visited==visit)
		return;
	root->visited=visit;
	if (root != NULL) 
	{
		fprintf (outputFile, "%d [label=%d,color=black];\n",root->info, root->info);
        while(i<root->count) {
        	fprintf (outputFile, "%d -> %d ;\n", root->info, (root->link[i])->info);
			preorderDotDump (root->link[i], outputFile,visit);
			i++;
		}
    }
}

void dotDump(node root, FILE *outFile,int visit)
{
	gName++;
	fprintf (outFile, "digraph BST { \n",gName);
	preorderDotDump (root, outFile,visit);
    fprintf (outFile, "}\n");
}

FILE *OutputFile;
main() {
	FILE *pipe;
	int k1,k2,ch,n,i,choice,vi;
	node R;
	OutputFile = fopen ("pgrank.dot", "w");
    fclose (OutputFile);
	do {
		printf("Choose the operation to perform\n 1.Insert\n 2.Display rank\n 3.Display\n(Trying to re-insert to the tree erases the previous tree)\n");
		scanf("%d",&ch);
		switch(ch) {
			case 1: //insert, count and compute rank
				R=NULL;
				do {
					printf("\n Enter nodes in the form n1->n2 ");
					scanf("%d%d",&k1,&k2);
		            R=Insert(k1,k2,R);
					printf("Do you want to insert more nodes?(1 for continue)\n");
					scanf("%d",&n);
				}while(n==1);
				vi=R->visited;
				countnode(R,!vi);
				vi=R->visited;
				rank(R,!vi);
                break;
			case 2: //print rank of pages
				vi=R->visited;
				printrank(R,!vi);
				break;
            case 3: //dotty output
				vi=R->visited;
                OutputFile=fopen("pgrank.dot","a");
				if(OutputFile != NULL) {	
					dotDump(R,OutputFile,!vi);
				}
				fclose(OutputFile);	
				pipe=popen("dot -Tps pgrank.dot -o pgrank.ps","w");
				pclose(pipe);
				pipe=popen("evince pgrank.ps","r"); 
				pclose(pipe);
                break;
            default:
				printf("Invalid choice!\n");
				break;
        }
		printf("Do you want to continue? (1 for continue)\n");
		scanf("%d",&choice);
	}while(choice==1);
}
