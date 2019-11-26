#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include<stdlib.h>
#include"macros.h"
#define HEAD 0
  /*
  final file : track;
  dsize;
  offset_h;
  offset_elem;
  offset_1x;
  offset_1y;
  offset_1r;
  offset_1g;
  offset_1b;
  */
 typedef struct tagTRACKH {
   BYTE offset_h;
   BYTE offset_elem;
 } TRACKH;
  /*
  final file : track elem;
  valuable_x,
  valuable_y,
  */
  typedef struct tagTRACKE
  {
    BYTE x;
    BYTE y;
    BYTE state;
    struct tagTRACKE*next;
    struct tagTRACKE*prior;
  }TRACKE;
  
//functions statement
  void InitTRACKH(TRACKH*header,TRACKE*head);
	char CreateH		(TRACKE**head);
	void CreateTRACKE	(TRACKE**head,int length);				//Create a specified length TRACKE; C
	int  TRACKELength 	(TRACKE*head);							//Get the input-TRACKE's length; C
	void InitTRACKE		(TRACKE*head);							//Create an empty TRACKE; C
	char TRACKEEmpty	 	(TRACKE*head);							//Judge that the input-TRACKE is empty or not; C
	int  ClearTRACKE		(TRACKE*head);							//Clear the input-TRACKE; C
	int  LocateLElemR	(TRACKE*head,int elem);					//Locating elem in input-TRACKE(relative address); C
	int  LocateLElemA	(TRACKE*head,int sernum,TRACKE**target);	//Locating elem in input-TRACKE(absolute address); C
	void GetLelem	 	(TRACKE*head,int sernum,int*value);	//Return sernumth element's value by 'value'; C	
  void PTRACKE(TRACKE*head,int length);//Print all emelents in the stack
  char TRACKEInsert 	(TRACKE*head,int sernum,int value);	//Insert 'value' in input-TRACKE as it's sernumth element; C
	char TRACKEDelete 	(TRACKE*head,int sernum,int*value);	//Delete sernumth element in input-TRACKE; C
#endif
