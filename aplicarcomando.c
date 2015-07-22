#include "filesocialista.h"

lista *buscarcomando(lista *inicio, char comando[])
{
	lista *aux;

	aux = inicio;
	if (aux!=NULL)
	{
		while(aux!=NULL && strcmp(aux->Terminal,comando) != 0)
		{
			aux = aux->sig;
		}
	}

	return aux;
}

void ejecutarcomando(char comandoSistema[], char accion1[], char accion2[])
{
	char ejecutor[TAM_CADENA];

	strcpy(ejecutor, comandoSistema);

	#ifdef ESUNIX
        ejecutor[strlen(ejecutor) - 1] = '\0';
    #endif

	strcat(ejecutor, " ");
	strcat(ejecutor, accion1);
	strcat(ejecutor, " ");
	strcat(ejecutor, accion2);
	
	#ifdef ESUNIX
	{
		system(ejecutor);
	}
	#else
	{
		system(ejecutor);
	}
	#endif 
}

pila *comandoejecutado(pila *tope, char ejecutado[])
{
	pila *newnodo;

	newnodo = (pila *) malloc(sizeof(pila));
	strcpy(newnodo->ultimo,ejecutado);
	newnodo->sig = tope;

	tope = newnodo;

	return tope;
}