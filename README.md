Memoria Advent of Code 2025 - Día 7

Problema: Day 7 - Laboratories (Part 1 & Part 2) Lenguaje: C++
1. Justificación

Seleccioné este problema porque es el ejemplo canónico de Modelado de Grafos en Rejillas. 
Aunque visualmente parece una simulación física simple, matemáticamente expone la diferencia crítica entre problemas de "Alcanzabilidad" (¿A dónde puedo llegar?) y problemas de "Conteo de Caminos" (¿De cuántas formas puedo llegar?). 
Es el escenario ideal para contrastar dos de las herramientas más potentes de la algoritmia: BFS (Búsqueda en Anchura) para la exploración eficiente y Programación Dinámica (DFS + Memoización) para manejar la complejidad exponencial.

2. Descripción Técnica

El problema requiere simular el comportamiento de un haz de partículas en un entorno con gravedad y divisores.

Abstracción del Grafo: Traté la matriz 2D como un grafo dirigido implícito. Cada celda es un nodo y la gravedad define las aristas hacia abajo. Los divisores (^) son nodos que bifurcan el flujo.

Parte 1 (Fusión de Estados - BFS): El objetivo era contar cuántos divisores únicos se activan.

    La clave aquí es que los rayos pueden fusionarse. Si dos rayos llegan al mismo punto, se convierten en uno solo.

    Implementé un algoritmo BFS (Breadth-First Search) utilizando una cola (std::queue).

    Para evitar procesar el mismo rayo infinitas veces, utilicé una matriz de control visitados. Si un rayo intenta nacer en una coordenada ya procesada, se descarta inmediatamente. Esto colapsa el espacio de búsqueda.

Parte 2 (Interpretación de Muchos Mundos - DP): El objetivo cambió a contar el número total de líneas temporales (caminos distintos).

    Aquí los rayos NO se fusionan. Si dos caminos llegan al mismo punto, sus historias se suman.

    La fuerza bruta es inviable (O(2N)). Cambié la estrategia a Programación Dinámica Top-Down.

    Utilicé una función recursiva con una tabla de Memoización (memo[r][c]). Cada vez que calculo cuántas líneas temporales genera un divisor, guardo el resultado. Si vuelvo a pasar por ahí, devuelvo el dato en O(1).

3. Calidad Algorítmica y Eficiencia

La prioridad fue transformar un problema de crecimiento exponencial en uno de complejidad polinómica.

    Complejidad Temporal (O(R×C)):

    En la Parte 1, cada celda se encola y procesa como máximo una vez gracias a la matriz de visitados.

    En la Parte 2, gracias a la memoización, cada divisor calcula su sub-árbol recursivo una única vez. Las siguientes consultas son instantáneas.

    Esto garantiza que el tiempo de ejecución sea lineal respecto al tamaño del mapa, independientemente de cuántos millones de líneas temporales se generen.

    Gestión de Memoria:

    Utilicé matrices nativas (vector<vector<T>>) en lugar de mapas (std::map) para la caché y los visitados, garantizando un acceso a memoria más rápido y cache-friendly.

    La estructura struct Punto permite pasar coordenadas por valor de forma ligera, evitando la sobrecarga de punteros.

4. Diseño y Claridad del Código

El código se reestructuró para seguir principios sólidos de ingeniería de software:

    Modularización: Extraje la lógica de búsqueda del punto inicial a su propia función buscar_S, devolviendo un struct Punto. Esto limpia el main y separa la fase de configuración de la fase de cálculo.

    Semántica: El uso de struct Punto { int r, c; } hace que el código sea autodocumentado. Es mucho más legible inicio.r que inicio.first (como sería en un std::pair).

    Control de Flujo: En la Parte 2, la recursividad está limpia y clara: Caso Base (salir del mapa), Caso Memoizado (retorno rápido) y Caso Recursivo (cálculo real).

5. Alternativas Descartadas

    Simulación Pura (Step-by-step): Intentar mover cada partícula paso a paso en un bucle infinito. 
    Se descartó porque en la Parte 2, el número de partículas se duplica en cada divisor, lo que desbordaría la memoria RAM y el tiempo de CPU en segundos.

    DFS sin Memoización: Habría resultado en un algoritmo correcto pero extremadamente lento (O(2N)), recalculando las mismas ramas del árbol millones de veces.

    BFS para la Parte 2: Aunque posible, acumular sumas de caminos "hacia arriba" con BFS es más complejo de implementar y propenso a errores que la recursividad natural de "hacia abajo" con DP.

6. Valoración Personal

Este ejercicio ha sido una lección magistral sobre cómo un cambio sutil en las reglas (de "fusión de rayos" a "suma de historias") obliga a cambiar completamente la arquitectura del algoritmo (de BFS iterativo a DP recursivo). He reforzado la importancia de la Memoización: una simple tabla de enteros (memo) es la diferencia entre un programa que tarda 3 milisegundos y uno que tarda 3 siglos. También he mejorado mi disciplina de código al forzar la separación de responsabilidades (buscar_S) en lugar de aglomerar todo en el main.

7. INSTRUCCIONES DE EJECUCION DE CODIGOS

    Poner todos los archivos (main.cpp, datosAOC7.txt, Makefile si lo hubiera) en una misma carpeta.

    Para compilar, ejecutar en la terminal:

    make bin/AOC7 (Para el programa de la Parte 1 - BFS)
    make bin/AOC7-2 (Para el programa de la Parte 2 - DP)

    Ejecutar el programa:

    ./bin/AOC7 (Buscará datosAOC7.txt)
    ./bin/AOC7-2
