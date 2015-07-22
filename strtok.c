#include "filesocialista.h"

lista *leerArchivo(lista *inicio)
{
   FILE *archivo;
   int linea,palabra;
   char cadena[TAM_CADENA], comando[TAM_CADENA], comandoWin[TAM_CADENA], comandoUnix[TAM_CADENA];
   char *token;

   archivo=fopen("cargainicial.obj","r");
   if(archivo!=NULL)
   {
      palabra=1;
      linea=1;
      memset(cadena,0,TAM_CADENA);
      memset(comando,0,TAM_CADENA);
      memset(comandoWin,0,TAM_CADENA);
      memset(comandoUnix,0,TAM_CADENA);

      fgets(cadena,TAM_CADENA,archivo);
      while(!feof(archivo))
      {
         token=strtok(cadena,"*");
         while(token!=NULL)
         {
            switch(palabra)
            {
               case 1:
                  strcpy(comando, token);
               break;

               case 2:
                  strcpy(comandoWin, token);
               break;

               case 3:
                  strcpy(comandoUnix, token);
               break;

               default:
               break;   
            }
            palabra++;
            token=strtok(NULL,"*");
         }
         inicio = insertarlista(comando, comandoWin, comandoUnix, inicio);
         palabra=1;
         fgets(cadena,TAM_CADENA,archivo);
         linea++;
      }
      fclose(archivo);
   }
   return inicio;
}