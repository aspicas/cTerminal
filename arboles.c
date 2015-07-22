#include "filesocialista.h"

arbol *crearArbol(arbol *registro) 
{
	return (registro = NULL);
}

int	esNodoVacio(arbol *registro)
{
	if (registro == NULL)
		return TRUE;

	return FALSE;
}

int esRaizDelArbol(char clave[], arbol *raizArbol)
{
	if(strcmp(clave,raizArbol->valor) == 0)
		return TRUE;
	
	return FALSE;
}

int	esHoja(arbol *registro)
{
	if (esNodoVacio(registro->hijoIzq) && esNodoVacio(registro->hijoDer))
		return TRUE;

	return FALSE;
}

arbol *nodoPadre(char clave[], arbol *raizArbol)
{
	arbol *raizSubArbol;

	raizSubArbol = raizArbol;

	if (!esNodoVacio(raizArbol) && !esRaizDelArbol(clave,raizArbol))
	{
		while (!esHoja(raizSubArbol))
		{
			if (!esNodoVacio(raizSubArbol->hijoIzq) && strcmp(raizSubArbol->hijoIzq->valor, clave) == 0)
				return raizSubArbol;

			if (!esNodoVacio(raizSubArbol->hijoDer) && strcmp(raizSubArbol->hijoDer->valor, clave) == 0)
				return raizSubArbol;

			if (strcmp(clave, raizSubArbol->valor) < 0)
				raizSubArbol = raizSubArbol->hijoIzq;
			else
			{
				if (strcmp(clave, raizSubArbol->valor) > 0)
					raizSubArbol = raizSubArbol->hijoDer;
			}
		}
	}

	return NULL;
}

arbol *insertarDirectorioAVL(char Directorio[],arbol *registro) 
{
	arbol *nuevoregistro;
	arbol *aux;

	if (registro == NULL)
	{
		nuevoregistro = (arbol *)malloc(sizeof(arbol));
		strcpy(nuevoregistro->valor, Directorio);
		nuevoregistro->hijoIzq = NULL;
		nuevoregistro->hijoDer = NULL;
		registro = nuevoregistro;
	}
	else 
	{
		aux = registro;

		if (strcmp(Directorio, registro->valor) < 0)
		{
			aux = insertarDirectorioAVL(Directorio,aux->hijoIzq);
			registro->hijoIzq = aux;
		}

		if (strcmp(Directorio, registro->valor) > 0)
		{
			aux = insertarDirectorioAVL(Directorio, aux->hijoDer);
			registro->hijoDer = aux;
		}
	}

	return registro;
}


int esRDI(arbol *registro)
{
	if (registro->FE == 2 && registro->hijoDer->FE == -1)
		return TRUE;
	
	return FALSE;
}

arbol *balanceoRDI(arbol *registro, arbol *raizArbol)
{
   arbol *P, *Q;

   P = registro;
   Q = P->hijoDer;
   
   raizArbol = balanceoRSD(Q, raizArbol);
   raizArbol = balanceoRSI(P, raizArbol);

   return raizArbol;
}

int esRDD(arbol *registro)
{
	if (registro->FE == -2 && registro->hijoIzq->FE == 1)
		return TRUE;
	
	return FALSE;
}

arbol *balanceoRDD(arbol *registro, arbol *raizArbol)
{
   arbol *P, *Q;

   P = registro;
   Q = P->hijoIzq;
   
   raizArbol = balanceoRSI(Q, raizArbol);
   raizArbol = balanceoRSD(P, raizArbol);

   return raizArbol;
}

int esRSI(arbol *registro)
{
	if (registro->FE == 2 && (registro->hijoDer->FE == 1 || registro->hijoDer->FE == 0))
		return TRUE;
	
	return FALSE;
}

arbol *balanceoRSI(arbol *registro, arbol *raizArbol)
{
   arbol *padre, *P, *Q, *B;

   P = registro;
   Q = P->hijoDer;
   B = Q->hijoIzq;

   padre = nodoPadre(registro->valor,raizArbol);

   if(padre) 
   {
     if(padre->hijoIzq == P) 
		 padre->hijoIzq = Q;
     else 
		 padre->hijoDer = Q;
   }
   else 
	   raizArbol = Q;

   P->hijoDer = B;
   Q->hijoIzq = P;

   P->FE = 0;
   Q->FE = 0;

   return raizArbol;
}

int esRSD(arbol *registro)
{
	if (registro->FE == -2 && (registro->hijoIzq->FE == -1 || registro->hijoIzq->FE == 0))
		return TRUE;
	
	return FALSE;
}

arbol *balanceoRSD(arbol *registro, arbol *raizArbol)
{
   arbol *padre, *P, *Q, *B;

   P = registro;
   Q = P->hijoIzq;
   B = Q->hijoDer;

   padre = nodoPadre(registro->valor,raizArbol);

   if(padre) 
   {
     if(padre->hijoDer == P) 
		 padre->hijoDer = Q;
     else 
		 padre->hijoIzq = Q;
   }
   else 
	   raizArbol = Q;

   P->hijoIzq = B;
   Q->hijoDer = P;

   P->FE = 0;
   Q->FE = 0;

   return raizArbol;
}

