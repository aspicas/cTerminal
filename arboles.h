extern arbol *crearArbol(arbol *registro);
extern int	esNodoVacio(arbol *registro);
extern int esRaizDelArbol(char clave[], arbol *raizArbol);
extern int	esHoja(arbol *registro);
extern arbol *nodoPadre(char clave[], arbol *raizArbol);
extern arbol *insertarDirectorioAVL(char Directorio[],arbol *registro);
extern int esRDI(arbol *registro);
extern arbol *balanceoRDI(arbol *registro, arbol *raizArbol);
extern int esRDD(arbol *registro);
extern arbol *balanceoRDD(arbol *registro, arbol *raizArbol);
extern int esRSI(arbol *registro);
extern arbol *balanceoRSI(arbol *registro, arbol *raizArbol);
extern int esRSD(arbol *registro);
extern arbol *balanceoRSD(arbol *registro, arbol *raizArbol);