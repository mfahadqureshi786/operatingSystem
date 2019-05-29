
#include<iostream>
#include<cmath>
using namespace std;
struct processNode
{
	float arrivalTime=0,burstTime=0;
	int pNo,priority;
	float completionTime,turnAroundTime,waitingTime,responseTime;
	processNode *left=0,*right=0;
	
};
int max(int a,int b)
{
if(a>=b)return a;return b;
}
class processAvl
{
public:
	processNode *root;
processAvl():root(0){}
void delNode(processNode *root)
{  
if(root==0)
return;

		delNode(root->left);
		delNode(root->right);
		delete root;
		root=0;
	
}
void delTree()
{
	delNode(this->root);
	
	this->root=0;
	
}
void copyPreOrder (processNode *root)
{
	if(root!=0)
	{this->root=insertProcess(this->root,root->pNo,root->arrivalTime,root->burstTime,root->priority);
		copyPreOrder(root->left);
		copyPreOrder(root->right);
	}

}
void mkcopy(processAvl &obj)
{

copyPreOrder(obj.root);
}
processNode* rightRotate(processNode *root)
{
processNode *newRoot=root->left;
root->left=newRoot->right;
newRoot->right=root;
return newRoot;
}
processNode* leftRotate(processNode *root)
{
processNode *newRoot=root->right;
root->right=newRoot->left;
newRoot->left=root;
return newRoot;
}

int findHeight(processNode *root)
{
	if(root==0)
	return -1;
	else	
	{
	int left=findHeight(root->left);
	int right=findHeight(root->right);
	return max(left,right)+1;
	}
}
processNode* search(processNode *root,int pid)
{
	if(root!=0 && pid==root->pNo)
	{
		return root;
	}
	else if(root!=0 && pid<root->pNo)
	{
		search(root->left,pid);
	}
	else if(root!=0 &&pid>root->pNo)
	{
		search(root->right,pid);
	}
	else return 0;
}
processNode* insertProcess(processNode *root,int pNo,float arrivalTime,float burstTime,int priority)
{
	if(root==0){root=new processNode;root->pNo=pNo;root->arrivalTime=arrivalTime;
	root->burstTime=burstTime;root->priority=priority;
	}
	else if(pNo<=root->pNo )
	{
		root->left=insertProcess(root->left,pNo,arrivalTime,burstTime,priority);
	}
	else if(pNo>root->pNo)
	{
		root->right=insertProcess(root->right,pNo,arrivalTime,burstTime,priority);
	}
	
	int bFact=findHeight(root->left)-findHeight(root->right);
	if(bFact>1) //left case
	{   //left left
		if(findHeight(root->left->left)>=findHeight(root->left->right))
		{
			root=rightRotate(root);
		}//left right
		else
		{
			root->left=leftRotate(root->left);
			root=rightRotate(root);
			
		}
	}
	//right case
	else if (bFact<-1)
	{   //right right
		if(findHeight(root->right->right)>=findHeight(root->right->left))
		{
			root=leftRotate(root);
		}//right left
		else
		{
				root->right=rightRotate(root->right);
			root=leftRotate(root);
		}
	}
	return root;
}
void inOrder(processNode *root)
{
	if(root!=0)
	{
		inOrder(root->left);
		cout<<"Pno:"<<root->pNo<<",ArrivalTime:"<<root->arrivalTime<<",Priority:"<<root->priority<<endl;
		inOrder(root->right);
	}
}

};
struct pidNode
{
int pid=0;
struct pidNode *next=0;
};

class LL
{
	public:
		pidNode *head;
        int elements;
	LL():head(0),elements(0){}
	void insert(int pid)
	{
		if(head==0)
		{
			head=new pidNode;
			head->pid=pid;
		}
		else
		{
			pidNode *curr=head;
			while(curr->next!=0)
			{
				curr=curr->next;
			}
			curr->next=new pidNode;
			curr->next->pid=pid;
		}
		elements++;
	}
	pidNode* operator[](int index)
	{  
		if(index>=0 && index<elements)
		{
			pidNode *curr=head;
			while(curr->next!=0 && index!=0)
			{
				curr=curr->next;
				index--;
			}
			return curr;
		}
		return 0;
	}
};
int n=1;
LL *arrayArrival=new LL[n];
void FCFS(processAvl *obj)
{   float time=0;
    float avgTAT=0;
    float avgWait=0;
    int totalps=0;
    cout<<"\nFirst come first Serve:\n";
    cout<<"PNO"<<"--AT"<<"--BT"<<"--CT"<<"--TAT"<<"--WT"<<"--RT"<<endl;
	for(int i=0;i<n;i++)
	{   
	     if((arrayArrival[i]).elements>0)
	     {
		 totalps+=(arrayArrival[i]).elements;
         if(time<i)
		 {
		 	while(time<i)
		 	time++;
		 }	     
		for(int k=0;k<(arrayArrival[i]).elements;k++)
		{   
			processNode *temp=obj->search(obj->root,arrayArrival[i][k]->pid);
			
			if(temp!=0)
			{   temp->responseTime=time-temp->arrivalTime;
			    //time+=abs(temp->arrivalTime-time)+time;
			    time+=temp->burstTime;
				temp->completionTime=time;
				temp->turnAroundTime=temp->completionTime-temp->arrivalTime;
				temp->waitingTime=temp->turnAroundTime-temp->burstTime;
				
				
				
				temp->burstTime=0;//executed
				
				cout<<temp->pNo<<"    "<<temp->arrivalTime<<"   "<<temp->burstTime<<"   "
				<<temp->completionTime<<"   "<<temp->turnAroundTime<<"   "<<temp->waitingTime<<"  "
				<<temp->responseTime<<endl;
				
				avgWait+=temp->waitingTime;
				avgTAT+=temp->turnAroundTime;
			}
		
		}
		
		}
		
		
		
	}
	avgTAT/=totalps;
		avgWait/=totalps;
	cout<<"\nAverageTurnAroundTime:"<<avgTAT;
	cout<<"\nAverageWaitingTime:"<<avgWait;
}
void SJF(processAvl *obj)
{  
 cout<<"\nShortest Job First:\n";
    cout<<"PNO"<<"--AT"<<"--BT"<<"--CT"<<"--TAT"<<"--WT"<<"--RT"<<endl;

float avgTAT=0;
    float avgWait=0;
    int totalps=6;
	float time;
	processNode *temp=obj->search(obj->root,1);
	for(int i=1;i<=5 ;i++)
	{  
		processNode *temp=obj->search(obj->root,i);
			if(i==3){
		int as=3434;
		//cout<<"BURSTTIME:"<<t->burstTime<<"PNO"<<t->pNo<<endl;
	}
		while(temp->burstTime==0)
		{   if(i<5)
			temp=obj->search(obj->root,i+1);
			else break;
		}
for(int id=1;id<6;id++)	
{
	processNode *t=obj->search(obj->root,id);

	if((temp->burstTime>=t->burstTime&& t->burstTime!=0)||temp->burstTime==0)
	{ 
		temp=t;
	}
}
time+=temp->burstTime;
				temp->completionTime=time;
				temp->turnAroundTime=temp->completionTime-temp->arrivalTime;
				temp->waitingTime=temp->turnAroundTime-temp->burstTime;
				
				cout<<temp->pNo<<"    "<<temp->arrivalTime<<"   "<<temp->burstTime<<"   "
				<<temp->completionTime<<"   "<<temp->turnAroundTime<<"   "<<temp->waitingTime<<"  "
				<<temp->responseTime<<endl;
				temp->burstTime=0;//executed
				avgWait+=temp->waitingTime;
				avgTAT+=temp->turnAroundTime;
	}			
		avgTAT/=totalps;
		avgWait/=totalps;
	cout<<"\nAverageTurnAroundTime:"<<avgTAT;
	cout<<"\nAverageWaitingTime:"<<avgWait;
}
int main()
{
	processAvl obj,obj2;
	
	obj.root=obj.insertProcess(obj.root,1,0,2,2);
	(arrayArrival[0]).insert(1);
    obj.root=obj.insertProcess(obj.root,2,0,1,1);
    (arrayArrival[0]).insert(2);
    obj.root=obj.insertProcess(obj.root,3,0,8,4);
    (arrayArrival[0]).insert(3);
    obj.root=obj.insertProcess(obj.root,4,0,4,2);
    (arrayArrival[0]).insert(4);
    obj.root=obj.insertProcess(obj.root,5,0,5,3);
    (arrayArrival[0]).insert(5);
	obj2.mkcopy(obj);
	
	FCFS(&obj2);
	obj2.delTree();
	obj2.mkcopy(obj);
	//obj2.inOrder(obj2.root);
	
	SJF(&obj2);
	
}
