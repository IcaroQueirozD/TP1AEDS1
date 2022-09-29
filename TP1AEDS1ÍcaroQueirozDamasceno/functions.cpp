#include <iostream>
#include <windows.h>
#include <fstream>
#include "list.hpp"

#define MAXTAM 5

using namespace std;

void CreateEmptyList(EmpList *list) //Criação de uma lista encadeada vazia.
{
    if (!listCreated)
    {
        list->First = new ElementType;
        list->Last = list->First;
        list->Last->next = NULL;
        listCreated = true;
    }
}

bool VerifyEmptyList(EmpList *list) //Verifica se a lista encadeada está vazia, retorna True se o primeiro item for igual ao último.
{
    if (list->First == list->Last)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InsertLast(EmpList *list, ItemType *item) //Insere um ítem na última posição da lista.
{
    list->Last->next = new ElementType;
    list->Last = list->Last->next;
    list->Last->next = NULL;
    list->Last->item = *item;
    list->size++;
}

Pointer FindItem(EmpList *list, int id) //Encontra algum ítem dentro da lista a partir de um valor inteiro.
{
    Pointer aux;
    aux = list->First->next;
    while (aux != NULL)
    {
        if (id == aux->item.id)
        {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void PrintItem(EmpList *list, int id) //Imprime algum item específico da lista a partir de um valor inteiro.
{
    Pointer aux;
    aux = list->First->next;
    while (aux != NULL)
    {
        if (aux->item.id == id)
        {
            cout << "ID: " << aux->item.id << endl;
            cout << "Name: " << aux->item.name << endl;
            cout << "ADDRESS:\nState: " << aux->item.adrss.state << "\nCidade: " << aux->item.adrss.city << "\nBorough: " << aux->item.adrss.borough << "\nStreet: " << aux->item.adrss.street << " " << aux->item.adrss.housenum
                 << endl;
            cout << "Number of dependents: " << aux->item.dependents << endl;
            break;
        }
        aux = aux->next;
    }
}

void RemoveFirst(EmpList *list) //Remove continuamente o primeiro item da lista, serve como função de desalocação de memória.
{
    
    Pointer aux, remove;
    aux = list->First->next;
    while( aux != NULL )
    {
        remove = aux;
        aux = aux->next;
        delete remove;
    }
    delete aux;
}

void RemoveItemById(EmpList *list, int id) //Remove algum item específico da lista a partir de um valor inteiro especificado pelo usuário.
{
    if (VerifyEmptyList(list) == true)
    {
        return;
    }

    Pointer aux, anterior, x;

    x = list->First;

    while (x != NULL)
    {
        if (x->next->item.id == id)
        {
            anterior = x;
            break;
        }
        x = x->next;
    }
    aux = anterior->next;
    anterior->next = aux->next;
    delete aux;
    list->size--;
}


void projCreateEmptyList(projList *list) //Cria uma lista sequencial vazia.
{
    list->projSize = 0;
}

bool projVerifyEmptyList(projList *list) //Verifica se a lista sequencial está vazia a partir do tamanho da lista.
{
    if (list->projSize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool projVerifyFullList(projList *list) //Verifica se a lista sequencial está cheia ao verificar que a lista chegou em seu tamanho máximo.
{
    if (list->projSize == MAXTAM)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool projInsertItem(projList *list, ProjType item) //Insere um novo item à lista sequencial.
{
    if (!projVerifyFullList(list))
    {
        list->projItem[list->projSize] = item;
        list->projSize++;

        return true;
    }
    else
    {
        return false;
    }
}

int projFindItem(projList *list, int id) //Encontra algum item específico na lista sequencial a partir de um valor inteiro.
{
    for (int i = 0; i < list->projSize; i++)
    {
        if (list->projItem[i].projid == id)
        {
            return i;
        }
    }
    return -1;
}

int projRemoveItem(projList *list, int id) //Remove algum item específico na lista sequencial a partir de um valor inteiro.
{
    int location = projFindItem(list, id);
    for (int i = location; i < list->projSize; i++)
    {
        list->projItem[i] = list->projItem[i + 1];
    }
    list->projSize--;
}

void projPrintList(projList list) //Imprime por completo a lista sequencial.
{
    for (int i = 0; i < list.projSize; i++)
    {
        cout << "Project ID: " << list.projItem[i].projid << endl;
        cout << "Project Name: " << list.projItem[i].projname << endl;
        cout << "Total of weekly work hours: " << list.projItem[i].projhours << endl;
    }
}


