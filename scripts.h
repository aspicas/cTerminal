extern void crearscripts(char camino[]);
extern void cargadescripts(char camino[]);
extern cola *encolar(cola *inicio, char Ncomando[]);
extern void imprimirscripts(cola *inicio);
extern void ejecutarscript(cola *comandos, lista *Carchivo);