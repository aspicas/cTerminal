#include "filesocialista.h"

lista *insertarlista(char comando[], char comandoWin[], char comandoUnix[], lista *inicio)      
{
	lista *newnodo, *posact;

	newnodo = (lista *) malloc(sizeof(lista));
	strcpy(newnodo->Terminal,comando);
	strcpy(newnodo->Win,comandoWin);
	strcpy(newnodo->Unix,comandoUnix);
	newnodo->sig = NULL;

	posact = inicio;

	if (inicio == NULL)
	{
		inicio = newnodo;
	}
	else
	{
		while (posact->sig != NULL)
		{
			posact = posact->sig;
		}
		posact->sig = newnodo;
	}
		
	return inicio;
}

void imprimirlista(lista *inicio)
{
	lista *aux;

	aux = inicio;
	printf("inicio -> ");

	while (aux != NULL)
	{
		printf("%s ->", aux->Terminal);
		aux = aux->sig;
	}

	printf("NULL\n");
}

void imprimircola(cola *inicio)
{
	cola *aux;

	aux = inicio;
	printf("inicio -> ");

	while (aux != NULL)
	{
		printf("%s ->", aux->script);
		aux = aux->sig;
	}

	printf("NULL\n");
}