#include "filesocialista.h"

int main()
{
    lista *inicio, *aux, *auxscript; 
    pila *comanEjecutados;
    cola *comandoscript;
    arbol *Directorios;
    char escribir[TAM_CADENA], *token;
    char comando[TAM_CADENA], accion1[TAM_CADENA], accion2[TAM_CADENA];//, camino[TAM_CADENA];
    int tam, palabra=1, i;

    #ifdef ESUNIX
    {
        system("clear");
    }
    #else
    {
        system("cls");
    }
    #endif

    inicio = NULL;
    comanEjecutados = NULL;
    comandoscript = NULL;
    getcwd(camino, TAM_CADENA);
    strcat(camino, "/scripts.obj");
    inicio = leerArchivo(inicio);
    for (i=0; i <= 15; ++i)
    {
        scriptsGlobal[i] = NULL;
    }

    printf("$ ");
    memset(escribir, 0, TAM_CADENA);
    for(tam=0; (escribir[tam] = getchar()) != FDL; tam++);
    fflush(stdin);

    #ifdef ESUNIX
        escribir[strlen(escribir) - 1] = '\0';
    #endif

    while(strcmp(escribir, "exit") != 0)
    {
        aux = inicio;   
        token = strtok(escribir," ");
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
        aux = buscarcomando(aux, comando);
        if (aux==NULL)
        {
            if (strcmp(comando,"createscript") == 0)
            {
                crearscripts(camino);
            }
            else if (strcmp(comando,"newdir") == 0)
            {
                Directorios = insertarDirectorioAVL(comando, Directorios);
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
            else if (strcmp(comando,"executescript") == 0)
            {
                i=0;
                strcat(accion1, "\n");
                cargadescripts(camino);
                while (scriptsGlobal[i] != NULL)
                {
                    if (strcmp(scriptsGlobal[i]->script,accion1) == 0)
                    {
                        comandoscript = scriptsGlobal[i]->sig;
                    }
                    i++;
                }

                auxscript = inicio;
                ejecutarscript(comandoscript, auxscript);
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
                printf("por favor introduzca el comando correcto\n");
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
        printf("$ ");
        memset(escribir, 0, TAM_CADENA);
        for(tam=0; (escribir[tam] = getchar()) != FDL; tam++);
        fflush(stdin);
        escribir[strlen(escribir) - 1] = '\0';
        comanEjecutados = comandoejecutado(comanEjecutados, comando);
        for (i=0; i <= 15; ++i)
        {
            scriptsGlobal[i] = NULL;
        }
    }

    return EXIT_SUCCESS;
}