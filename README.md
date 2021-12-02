# Integral-B -> Sistema de navegación y consulta de una biblioteca
Actividad integradora B para la materia TC1031 - Programación de estructuras de datos y algoritmos fundamentales.  
Erick Alfredo García Huerta - A01708119
## Contexto.
Una nueva biblioteca ha abierto en la ciudad y quieres ir a revisar su colección de libros. Al entrar en el edificio te encuentras con una máquina que te permite consultar un mapa del edificio y crear un camino hacia el pasillo que contiene los libros del tema que buscas, esto debido a que algunas puertas está trabadas y sólo pueden abrirse en una dirección. Además, otra opción del sistema te permite consultar de ante mano qué libros son los que están en la colección de dicho género y otra función te deja ver su orden en función de su número de páginas.
## Solución.
### SICT0301B Evalúa los componentes.
* Presenta Casos de Prueba correctos y completos para todas las funciones y procedimientos del programa.
   * Se incluyeron casos de prueba como la opción 4 en main.cpp, además de que se puede ver su construcción en la función pruebasAutomaticas() de la clase Menu en menu.h
* Hace un análisis de complejidad correcto y completo para todo el programa y sus componetes [NOTA DEL ALUMNO: para un análisis más a detalle, revisar los comentarios en cada clase].
   * Grafo -> O(n*m) debido a que de esa forma se es capaz de calcular la totalidad de los nodos del grafo y al haber implementado un Depth-first search, en el peor de los casos, se puede llegar a recorrer la totalidad del grafo en la búsqueda de un path.
   * Hash table -> O(n) debido a que en la búsqueda el recorrido de datos como de insersión, se puede llegar a recorrer la totalidad del arreglo en el peor de los casos.
   * AVL Tree -> O(log n) debido a que con cada búsqueda se desecha una mitad de los datos disponibles hasta en contrar en el dato requerido, esta es la complejidad que se encuentran en los métodos tanto de búsqueda como de inserción, los cuales son básicos en su funcionamiento. Mientras, las funciones de impresión tienen una complejidad de O(n) debido a que deben imprimir toda la estructura y en el proceso, recorrer todo el arreglo; así mismo, las funciones de apoyo como las rotaciones también tendrían una complejidad de O(n) en el peor de los casos durante el rebalanceo del árbol.
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
