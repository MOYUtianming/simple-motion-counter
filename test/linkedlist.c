#include"linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

void InitTRACKH(TRACKH *header,TRACKE*head)
{
	header->offset_h=sizeof(TRACKH);
	header->offset_elem=sizeof(TRACKE);
}
//based instruction set;
char CreateH(TRACKE**head)
{
	//Create the head state;
		*head=(TRACKE*)malloc(sizeof(TRACKE));//create a new storage for the head point;
	if(*head!=NULL)
	{
		(*head)->next=*head;	
		(*head)->prior=*head;
	//Initialize head state;
		InitTRACKE(*head);
		return 1;
	}
	else
	{
		return 0;
	}
}

void CreateTRACKE(TRACKE**head,int length)//Create a specified length TRACKE;
{
	//Use 'head' as the first state,create a spicified-length linked list;
	TRACKE *p=*head,*n=NULL;
	int i=0;
	static int cont=1;
		while(length>0 && i!=length)
		{
			i++;
			n=(TRACKE*)malloc(sizeof(TRACKE));
				n->state=cont++;
				n->x=0;
				n->y=0;
				n->prior=p;
				n->next=NULL;
			//Link prior state with '*n';	
				p->next=n;
			//Recursion;
				p=n;
		}
	//In this step,'n' corresponds to final state;
		//Link final with head;
		if(length>0)
		{
			n->next=*head;	
			(*head)->prior=n;
		}
		else
		{
			(*head)->prior=*head;
			(*head)->next =*head;
		}
	//Initialize head state;
		InitTRACKE(*head);
}

int  TRACKELength(TRACKE*head)//Get the input-TRACKE's length;
{
	int cont=0;
	TRACKE*p=head;
	while((p->next)!=head)
	{
		cont++;
		p=p->next;
	}
	return cont;
}

void InitTRACKE(TRACKE *head)	//Create an empty TRACKE;
{
		head->state=TRACKELength(head);
}

char TRACKEEmpty	 (TRACKE*head)//Judge that the input-TRACKE is empty or not;
{
	InitTRACKE(head);
	if (head->prior==head->next)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int ClearTRACKE(TRACKE *head)							//Clear the input-TRACKE;
{
	int cont=0,length=0;
	TRACKE*p=head,*n=NULL;
	length=TRACKELength(head); 
	for(cont=0;cont<length+1;cont++)
	{
		n=p->next;
		free(p);
		p=n;
	}
	return cont;
}

int LocateLElemR(TRACKE*head,int elem)//locating elem in input-TRACKE,return relative address;
{
	int cont=1;
	TRACKE*p=head->next;
	while(p->state!=elem && p->next!=head)
	{
		p=p->next;
		cont++;
	}
	if(p->state!=elem)
	{
		return 0;
	}
	else
	{
		return cont;
	}
}

int LocateLElemA(TRACKE*head,int sernum,TRACKE**target)//locating elem in input-TRACKE,return absolute address;
{
	int cont=0;
	int length=TRACKELength(head);
	TRACKE*p=head;
		if(sernum>length || sernum==0)
		{
			*target=p;
			return 0;
		}
		else
		{
			p=head->next;
			for(cont=0;cont<sernum-1;cont++)
			{
				p=p->next;
			}
			*target=p;
			return 1;
		}
}

void GetLelem(TRACKE*head,int sernum,int*value)//Return sernumth state's value by 'value';
{
	TRACKE*p=head->next;
	int length=0,cont=0;
		length=TRACKELength(head);
		if(sernum>length || sernum==0)
		{
			*value=0;
		}
		else
		{
			for(cont=0;cont<sernum-1;cont++)
			{
				p=p->next;
				//p=p->prior;//only can be used when input TRACKE is a double linked list;<replace prior set>
			}
			*value=p->state;
		}
}

char TRACKEInsert(TRACKE*head,int sernum,int value)	//Insert 'value' in input-TRACKE as it's sernumth state;
{
	TRACKE*p=NULL,*n=NULL,*N=NULL;
	int length=0,getnum=0;
	length=TRACKELength(head);
		if(sernum>length+1 || sernum==0)
		{
			return 0;
		}
		else
		{
			LocateLElemA(head,sernum-1,&p);
			N=p->next;
			
			getnum=CreateH(&n);
				if(getnum!=0)
				{
					n->state=value;
					n->prior=p;
					n->next=p->next;
								
					p->next=n;
					N->prior=n;
				}
				else
				{
					return 0;
				}
		}
		return 1;
	InitTRACKE(head);
} 

char TRACKEDelete(TRACKE*head,int sernum,int*value)	//Delete sernumth state in input-TRACKE;
													  		//use '*value' return it's value;
{
	TRACKE*p=head->next,*n=NULL,*N=NULL;
	int length=TRACKELength(head);
		if(sernum>length+1 || sernum==0)
		{
			*value=0;
			InitTRACKE(head);
			return 0;
		}
		else
		{
			LocateLElemA(head,sernum-1,&p);
			LocateLElemA(head,sernum,&n);
			N=n->next;
			
			p->next=N;
			N->prior=p;
			*value=n->state;
			free(n);
			InitTRACKE(head);
			return 1;
		}
}

void PTRACKE(TRACKE*head,int length)//Print all emelents in the stack
{
	int cont=0;
	TRACKE*p=head;
	for(cont=0;cont<length;cont++)
	{
		printf("the %dst num is %d\n",cont,p->state);
		p=p->next;
	}
}