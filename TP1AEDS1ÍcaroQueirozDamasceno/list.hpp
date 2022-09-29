#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

#define MAXTAM 5
#define INICIO 1

using namespace std;

typedef struct ProjType //Itens do projeto.
{
    int projid;
    char projname[30];
    int projhours;
} ProjType;

typedef struct projList //Struct da lista sequencial.
{
    ProjType projItem[MAXTAM];
    int projFirst = 0;
    int projLast = 0;
    int projSize = 0;
    
} projList;

typedef struct address //Struct do endereço do funcionário.
{
    char state[30];
    char city[30];
    char borough[30]; 
    char street[30];
    int housenum;
} address;

typedef struct ItemType //Itens do funcionário.
{
    int id;
    char name[30];
    address adrss;
    int dependents;
    projList projects;

} ItemType;



typedef struct ElementType *Pointer; //Tipo do ponteiro.

typedef struct ElementType //Representação dos itens do funcionário, e o ponteiro que aponta para o próximo item da lista encadeada.
{ 
    ItemType item;
    struct ElementType *next;

} ElementType;

typedef struct EmpList //Struct da lista encadeada.
{
    Pointer First;
    Pointer Last;
    int size = 0;
    

} EmpList;




bool listCreated = false; //Variável booleana que confirma se a lista foi criada ou não.

void CreateEmptyList(EmpList *list);
bool VerifyEmptyList(EmpList *list);
void InsertLast(EmpList *list, ItemType *item);
Pointer FindItem(EmpList *list, int id);
void PrintItem(EmpList *list, int id);
void RemoveItemById(EmpList *list, int id);
void RemoveFirst(EmpList *list);
void projCreateEmptyList(projList *list);
bool projVerifyEmptyList(projList *list);
bool projVerifyFullList(projList *list);
bool projInsertItem(projList *list, ItemType item);
int projRemoveItem(projList *list, int id);
void projPrintList(projList list);


#endif