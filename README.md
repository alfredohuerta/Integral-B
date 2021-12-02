# Integral-B -> Sistema de navegación y consulta de una biblioteca
Actividad integradora B para la materia TC1031 - Programación de estructuras de datos y algoritmos fundamentales.  
Erick Alfredo García Huerta - A01708119
## Correcciones.
* Se implementó el primer avance en el archivo grafo.h
* Se implementó el segundo avance en el archivo hash.h
## Contexto.
Una nueva biblioteca ha abierto en la ciudad y quieres ir a revisar su colección de libros. Al entrar en el edificio te encuentras con una máquina que te permite consultar un mapa del edificio y crear un camino hacia el pasillo que contiene los libros del tema que buscas, esto debido a que algunas puertas está trabadas y sólo pueden abrirse en una dirección. Además, otra opción del sistema te permite consultar de ante mano qué libros son los que están en la colección de dicho género y otra función te deja ver su orden en función de su número de páginas.
## Solución.
### SICT0301B Evalúa los componentes.
* Presenta Casos de Prueba correctos y completos para todas las funciones y procedimientos del programa.
   * Se incluyeron casos de prueba como la opción 4 en main.cpp, además de que se puede ver su construcción en la función pruebasAutomaticas() de la clase Menu en menu.h
* Hace un análisis de complejidad correcto y completo para todo el programa y sus componetes [NOTA DEL ALUMNO: para un análisis más a detalle, revisar los comentarios en cada clase].
   * Grafo -> O(n*m) debido a que de esa forma se es capaz de calcular la totalidad de los nodos del grafo y al haber implementado un Depth-first search, en el peor de los casos, se puede llegar a recorrer la totalidad del grafo en la búsqueda de un path.
     * loadGraphList(const string &file_name, int a, int b) -> brief Método que lee el archivo de texto que contiene todas las conecciones entre los nodos y carga estas relaciones en la lista adjunta. / complejidad: O(n) -> debido a que la función debe recorrer en el peor de los casos la totalidad de la longitud del  archivo de texto
     * DFS(int start, int goal, vector< string> &pasillos) brief función que llama al dfs y carga los demás datos necesarios en otras funciones auxiliares. / complejidad: O(n*m) -> debido a que recorre todos los nodos que pueda hasta encontrar el camino hasta el goal y estos se calculan en base a los nodos y arcos que tiene el grafo
   * Hash table -> O(n) debido a que en la búsqueda el recorrido de datos como de insersión, se puede llegar a recorrer la totalidad del arreglo en el peor de los casos.
     * toString() const -> brief Función que convierte en estring las llaves del hash y las regresa en un string / complejidad: O(n) debido a la presencia de un ciclo for dependiente del tamaño del arreglo.
     * put(Key k, Value v) -> brief Función que inserta un valor en la tabla y le asigna una llave para su posterior consulta. / complejidad: O(n) debido a la presencia de un ciclo for dependiente del tamaño del arreglo.
     * get(const Key k) -> brief: función que regresa el valor asociado a una llave / complejidad: Podría clasificarse como un O(1) debido a que en sí no presenta ningún ciclo, pero como manda a llamar a la función indexOf que presenta una complejidad de O(n) y siendo que se debe tomar en cuenta la complejidad más grande, se catalogaría como O(n)
   * AVL Tree -> O(n) debido a que con cada búsqueda se debe comprobar el balance de los datos, haciendo que en pero de los casos, durante esta revisión se recorra la totalidad de los datos. Mientras, las funciones de impresión tienen una complejidad de O(n) debido a que deben imprimir toda la estructura y en el proceso, recorrer todo el arreglo; así mismo, las funciones de apoyo como las rotaciones también tendrían una complejidad de O(n) en el peor de los casos durante el rebalanceo del árbol.
     * add(const Libros &lirbo) -> brief: Función que agrega un nodo al árbol / complejidad: complejidad: O(n) -> porque en el peor de los casos debe revisar todos los datos el arbol para que esté bien balanceado
     * inorder() const -> brief Función que imprime en forma inorder los nodos del árbol / complejidad: O(n) porque imprime todos los datos del AVL, así que debe recorrerlo todo
     * preorder() const -> brief FUnción que imprime en forma preorder los nodos del árbol / complejidad: O(n) porque imprime todos los datos del AVL, así que debe recorrerlo todo
### SICT0302B Toma decisiones.
* Usa grafos para hacer analisis de información.
   * Se aplicó un grafo donde algunos nodos son accesibles en ambos sentidos.
* Usa un algoritmo de búsqueda en grafos adecuado para resolver un problema
   * Se utilizó un algoritmo de recorrido de Depth-first search, esto es debido a que los valores de los nodos son arbitrarios y no todos los nodos son accesibles directamente entre sí como el nodo 2 y 3, por lo que se requiere explorar todas los posibles caminos. Esto se puede apreciar en el método DFS del archivo grafo.h
* Usa un algoritmo de hashing adecauado para resolver un problema
   * Con el motivo de evitar colisiones entre los datos, se usó un algoritmo de validación cuadrática
### SICT0303B Implementa acciones científicas.
* Implementa mecanismos para consultar información de las estructras correctos.
  * Todas las estructuras cuentan con métodos de búsqueda y/o obtención de datos. En el caso del AVL se decidió dejar la función de búsqueda como un apoyo para la función add() y la única forma de extraer información con la que cuenta son los métodos de impresión preorder() e inorder()
* Implementa mecanismos de lectura de archivos correctos.
  * Esto puede apreciarse en el archivo grafo.h donde se leen las uniones entre los nodos del archivo Pasillos.txt
### SEG0702A Tecnologías de Vanguardia.
* Investiga e implementa un algoritmo o una estructura de datos que no se vió durante el curso.
  * Como algoritmo nuevo se implementó un AVL Tree que ordena los libros de acuerdo a su número de páginas y gracias a que los números de páginas entre libros difieren en hasta cientos, se deció implementar este tipo de árbol para tener las estructuras mejor ordenadas y que no hubiera posibilidad de un árbol mal balanceado.
* Describe cada algoritmo de la estructura (inserción, consulta, etc...) de forma clara y con ejemplos
  * Encima de cada método se encuentra una pequeña descripción de su funcionamiento y componentes, además de que los ejemplos se encuentran en la función pruebasAutomaticas() del archivo menu.h
