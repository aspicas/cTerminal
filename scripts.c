#include "filesocialista.h"

void crearscripts(char camino[])
{
   FILE *archivo;
   int tam;
   char nomscripts[TAM_CADENA]; 

   archivo = fopen(camino, "a");
   memset(nomscripts,0,TAM_CADENA);
   for(tam=0; (nomscripts[tam] = getchar()) != FDL; tam++);
   fflush(stdin);
   while (strcmp(nomscripts, "fin script\n") != 0)
   {
      fputs(nomscripts,archivo);
      memset(nomscripts, 0, TAM_CADENA);
      for(tam=0; (nomscripts[tam] = getchar()) != FDL; tam++);
      fflush(stdin);
   }
   fputs("\n",archivo);

   fclose(archivo);
}

void cargadescripts(char camino[])
{
   FILE *archivo;
   char comando[TAM_CADENA];
   int cont=0;

   archivo = fopen(camino,"r");
   if(archivo!=NULL)
   {
      memset(comando,0,TAM_CADENA);
      fgets(comando, TAM_CADENA, archivo);
      while(!feof(archivo))
      {
         if (strcmp(comando,"\n") != 0)
         {
            scriptsGlobal[cont] = encolar(scriptsGlobal[cont], comando);
         }
         else
         {
            cont++;
         }
         memset(comando, 0, TAM_CADENA);
         fgets(comando, TAM_CADENA, archivo);
      }
      fclose(archivo);
   }
}

cola *encolar(cola *inicio, char Ncomando[])
{
   cola *newnodo, *aux;

   newnodo = (cola *) malloc(sizeof(cola));
   strcpy(newnodo->script, Ncomando);
   newnodo->sig = NULL;

   if (inicio == NULL)
   {
      inicio = newnodo;
   }
   else
   {
      aux = inicio;

      while (aux->sig != NULL)
      {
         aux = aux->sig;
      }
      aux->sig = newnodo;
   }

   return inicio;
}

void imprimirscripts(cola *inicio)
{
   if (inicio != NULL)
   {
      printf("%s", inicio->script);
   }
}

void ejecutarscript(cola *comandoscript, lista *Carchivo)
{
  lista *aux;
  pila *comanEjecutados;
  char comando[TAM_CADENA] ,accion1[TAM_CADENA], accion2[TAM_CADENA];
  char *token;
  int palabra = 1,i=0;

  if (comandoscript != NULL)
  {
    while(comandoscript != NULL)
    {
      aux = Carchivo;
      token = strtok(comandoscript->script," ");
      palabra = 1;
      memset(comando, 0, TAM_CADENA);
      memset(accion1, 0, TAM_CADENA);
      memset(accion2, 0, TAM_CADENA);
      while(token != NULL)
      {
        switch(palabra)
        {
          case 1:
            strcpy(comando, token);
          break;

          case 2:
            strcpy(accion1, token);
          break;

          case 3:
            strcpy(accion2, token);
          break;

          default:
          break;
        }
        palabra++;
        token = strtok(NULL," ");
      }
      comanEjecutados = comandoejecutado(comanEjecutados, comando);
      if (strcmp(accion1,"") == 0)
      {
        comando[strlen(comando) - 1] = '\0';
        accion1[strlen(accion1) - 1] = '\0';
        accion2[strlen(accion2) - 1] = '\0';
      }
      printf("comando %s\n", comando);    
      printf("accion1 %s\n", accion1); 
      //printf("accion2 %s\n", accion2);
      aux = buscarcomando(aux, comando);
      if (aux == NULL)
      {
          if (strcmp(comando,"createscript") == 0)
          {
              crearscripts(camino);
          }
          else if (strcmp(comando, "exit") == 0)
          {
              exit(1);
          }
          else if (strcmp(comando,"listscripts") == 0)
          {
            cargadescripts(camino);
            i=0;
            while (scriptsGlobal[i] != NULL)
            {
              imprimirscripts(scriptsGlobal[i]);
              i++;
            }
          }
          else if (strcmp(comando,"lastcommand") == 0)
          {
              printf("%s \n", comanEjecutados->ultimo);
          }
          else if (strcmp(comando,"go") == 0)
          {
              chdir(accion1);
          }
          else
          {
              printf("Comando invalido para el cTerminal\n");
          }
      }
      if(aux!=NULL)
      {
         #ifdef ESUNIX
         {
             ejecutarcomando(aux->Unix, accion1, accion2);
         }
         #else
         {
             ejecutarcomando(aux->Win, accion1, accion2);
         }
         #endif
      }
      comandoscript = comandoscript->sig; 
    }
  }
}