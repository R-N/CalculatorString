#ifndef DOUBLELINKEDLISTVOID_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"General.h"

typedef struct List_Struct_Node* List_Node;
typedef struct List_Struct* List;

struct List_Struct_Node{
	Object data;
	List_Node prev;
	List_Node next;
};


struct List_Struct{
	int sort;
	int count;
	List_Node first;
	List_Node last;
};

List List_Create();
List_Node List_CreateNode(Object);
int List_CountBackwards(List);

int List_Count(List);

int List_Add(List, Object);



List_Node List_GetNode(List, int);

Object List_Get(List, int);

bool List_RemoveNode(List, List_Node, bool);

bool List_RemoveAt(List , int , bool );

int List_AddFirst(List , Object );

int List_Insert(List , Object , int );

int List_InsertAnyway(List , Object , int );

int List_RemoveFirst(List , bool (Object, Object), Object , int , bool );


int List_RemoveLast(List , bool (Object, Object), Object , int , bool );

int List_RemoveAll(List , bool (Object, Object), Object , bool );

void Clear(List , bool );

int List_RemoveRange(List , int , int , bool );

int List_CountWhere(List , bool (Object, Object), Object );

int List_IndexOfFirst(List , bool (Object, Object), Object );

int List_IndexOfLast(List , bool (Object, Object), Object );


void PrintList(List list);

Object List_Pop(List list);

bool List_TryPop(List list, Object* out);

Object List_PopFirst(List list);

bool List_TryPopFirst(List list, Object* out);


int List_SwitchNodes(List list, List_Node a1, List_Node b1);

void List_Sort(List list, Comparison f(Object, Object), bool ascending);

void List_Reverse(List list);

void List_ReverseNodes(List list);

List List_JoinFirst(List List_Add, List to, int freeIt);

List List_JoinLast(List List_Add, List to, int freeIt);

List List_JoinAt(List List_Add, List to, int index, int freeIt);

List List_JoinAtAnyway(List List_Add, List to, int index, int freeIt);

void List_Destroy(List list, bool freeData);

Object IntToVoid(int x);

int VoidToInt(Object x, bool freeIt);

bool IntEquality(Object x, Object y);

Comparison CompareInt(Object x, Object y);

bool MatchPointer(Object, Object);

#define DOUBLELINKEDLISTVOID_H
#endif // DOUBLELINKEDLISTVOID_H
