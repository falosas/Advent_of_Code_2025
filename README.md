Memoria Advent of Code 2025 - Día 8

Problema: Day 8 - Playground 

1. Justificación

Elegí este problema porque marca la transición de estructuras de datos lineales a Teoría de Grafos. 
Es el escenario ideal para introducir el algoritmo Disjoint Set Union (DSU) o Union-Find. 
El problema plantea un reto de agrupamiento y conectividad que, resuelto con herramientas básicas (arrays o listas), sería lento y propenso a errores. 
Este ejercicio justifica el uso de algoritmos avanzados de grafos para resolver problemas de Componentes Conexas y Árboles de Expansión Mínima (MST).

2. Descripción Técnica

El problema se modeló matemáticamente como un Grafo No Dirigido y Ponderado, donde cada caja de conexiones es un vértice (V) y la distancia entre ellas es el peso de la arista (E).

    El Motor (DSU - Union Find):

    Para gestionar los grupos de cables, implementé un sistema DSU con dos optimizaciones críticas:

       Compresión de Caminos: Al buscar la raíz de un nodo, conectamos recursivamente todos los nodos del camino directamente a la raíz. Esto aplana el árbol haciendo que futuras busquedas sean de coste minimo.

       Unión por Tamaño: Al fusionar dos grupos, siempre adjuntamos el grupo más pequeño al más grande para mantener el árbol balanceado.

    Parte 1 (Agrupamiento Parcial):

       Generé todas las aristas posibles y las ordené por distancia (Algoritmo de Kruskal).

       Procesé estrictamente las primeras 1000 conexiones más cortas.

       Utilicé el DSU para rastrear el tamaño de los circuitos resultantes y calcular el producto de los mayores.

    Parte 2 (Conectividad Total - MST):

       El objetivo cambió a conectar todos los nodos en un solo circuito.

       Introduje una variable de estado componentes_activos, inicializada en N. Cada vez que el DSU unía dos conjuntos previamente desconectados, decrementaba este contador.

       La condición de parada fue componentes_activos == 1. La arista que provocó esta transición es la que completa el Árbol de Expansión Mínima.

3. Calidad Algorítmica y Eficiencia

Se priorizó la eficiencia matemática sobre la fuerza bruta.

    Complejidad temporal:

       El paso dominante es ordenar las aristas (std::sort). Las operaciones de DSU son inversamente proporcionales a la función de Ackermann, lo que en la práctica es constante.

       Comparado con un enfoque de búsqueda en anchura (BFS) tras cada conexión, esta solución es órdenes de magnitud más rápida.

    Optimización Aritmética:

       Distancia al Cuadrado: Evité el uso de sqrt() para calcular distancias. Comparar distancias al cuadrado mantiene la relación de orden pero evita operaciones de punto flotante costosas y problemas de precisión decimal.

    Lectura Eficiente:

       Utilicé sscanf para el parsing de las coordenadas. Es una función de C extremadamente rápida para patrones fijo, superando a los flujos de C++ en velocidad bruta de lectura.

4. Diseño y Claridad del Código

El código sigue un paradigma procedimental estricto, eliminando la sobrecarga de la Programación Orientada a Objetos en favor de estructuras de datos planas (POD).

    Estructuras de Datos:

       struct Punto y struct Arista: Contenedores de datos puros sin lógica interna.

       Vectores paralelos: padre y tamano gestionan el estado del DSU de forma local en el main, facilitando el paso de argumentos por referencia.

    Modularidad:

       Las funciones encontrar_raiz y unir son puras y desacopladas. No dependen de variables globales, lo que las hace portables y fáciles de testear.

       La lógica de "Unión devuelve Bool" en la Parte 2 permite que el bucle principal controle el flujo del programa de manera semántica.

5. Alternativas Descartadas

    BFS/DFS para conectividad: Se descartó usar algoritmos de recorrido (como BFS) para verificar si dos nodos ya estaban conectados antes de añadir un cable.
    Esto habría elevado la complejidad por cada arista, haciendo el programa inviable para grandes inputs.

    Algoritmo de Prim: Aunque Prim también encuentra el MST, Kruskal (ordenar aristas) se ajustaba más naturalmente a la narrativa del problema.

    Matrices de Adyacencia: Representar el grafo en una matriz N×N habría desperdiciado memoria y complicado la gestión de componentes dispersos. La lista de aristas es más compacta.

6. Valoración Personal

Este ejercicio consolida la importancia de reconocer patrones abstractos en problemas narrativos. Lo que el enunciado describe como "cables y cajas" es, en realidad, un problema de Bosques de Conjuntos Disjuntos. 
He aprendido que "aplanar" la estructura de clases (pasar de class DSU a funciones sueltas) no reduce la sofisticación del algoritmo, sino que a veces mejora la legibilidad. 
La combinación de Kruskal + DSU ha demostrado ser una herramienta indispensable en mi arsenal.

7. INSTRUCCIONES DE EJECUCION DE CODIGOS

    Poner todos los archivos (main.cpp, datosAOC8.txt, Makefile) en una misma carpeta.

    Para compilar, ejecutar en la terminal:

        make bin/AOC8 
        make bin/AOC8-2

    Ejecutar el programa:

        ./bin/AOC8
        ./bin/AOC8-2
