#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <direct.h>

#define TRUE 1
#define FALSE 0
#define FDL '\n'
//#define WIN
#define ESUNIX
#define TAM_CADENA 1024

struct nodo
{
	char Terminal[TAM_CADENA];
	char Win[TAM_CADENA];
	char Unix[TAM_CADENA];
	struct nodo *sig;
};

typedef struct nodo lista;

struct nodopila
{
	char ultimo[TAM_CADENA];
	struct nodopila *sig;
};

typedef struct nodopila pila;

struct nodocola
{
	char script[TAM_CADENA];
	struct nodocola *sig;
};

typedef struct nodocola cola;

cola *scriptsGlobal[15];
char camino[TAM_CADENA];

struct nodoarbol
{
	char valor[TAM_CADENA];
	int FE;
	struct nodoarbol *hijoIzq;
	struct nodoarbol *hijoDer;
};

typedef struct nodoarbol arbol;

#include "strtok.h"
#include "manejodelista.h"
#include "aplicarcomando.h"
#include "scripts.h"
#include "arboles.h"