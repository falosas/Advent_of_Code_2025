Informe Técnico: Advent of Code 2025 - Día 11

1. Justificación de la Elección

Elegí el problema del Día 11 porque representa el escenario perfecto para demostrar la integración de múltiples estructuras de datos en un único programa coherente.

A diferencia de problemas anteriores que se resolvían con un solo truco matemático, este problema exigía una arquitectura de software completa:

    Tablas Hash: Para traducir identificadores de texto ("aaa", "out") a índices numéricos manipulables.

    Grafos: Para modelar las conexiones de la red.

    Programación Dinámica: Para optimizar el conteo de caminos, que de otra forma sería computacionalmente inviable (exponencial).

Es un problema que no permite fuerza bruta, lo que me obligó a implementar una solución eficiente.

2. Descripción Técnica

La solución se estructura en tres capas claramente diferenciadas:

Capa 1: Gestión de Datos

Implementé mi propia clase TablaHash.

    Funcionamiento: Utiliza una función de hash para convertir strings en índices de un array estático.

    Colisiones: Implementé una resolución de colisiones mediante encadenamiento (Listas Enlazadas). Esto asegura que si dos claves generan el mismo hash, ambas se conserven.
    Esta capa traduce el problema de "Strings" a "Enteros", permitiendo que el resto del algoritmo trabaje con vectores rápidos en lugar de comparaciones de texto lentas.

Capa 2: Algoritmo de Búsqueda

El núcleo es una Búsqueda en Profundidad (DFS) sobre un grafo dirigido.

    Un grafo denso puede tener millones de caminos posibles entre dos puntos. Recorrerlos uno a uno es imposible.
    La Solución (Memoización): Utilicé un vector MemoTable. Cada vez que calculo cuántos caminos hay desde el nodo X hasta el final, guardo ese número. 
    Si el algoritmo vuelve a pasar por X desde otra ruta, devuelve el valor guardado instantáneamente en lugar de recalcular.

Capa 3: Lógica Combinatoria

La Parte 2 exigía pasar por dos puntos intermedios (dac y fft).

    En lugar de modificar el DFS para "recordar" visitas, apliqué la regla del producto.
    Dividí el viaje en etapas independientes.

        Ruta A: svr → dac → fft → out.

        Cálculo: (Caminos svr-dac) × (Caminos dac-fft) × (Caminos fft-out).

    Gestión de Memoria: Implementé un "wrapper" (tramos) que limpia y reinicia la tabla de memoización entre cada etapa, asegurando que los cálculos de un tramo no contaminen al siguiente.

3. Calidad Algorítmica y Eficiencia

El enfoque implementado reduce drásticamente la complejidad del problema.

    Complejidad Temporal:

        Sin Memoización (Exponencial). El programa se colgaría con inputs grandes.

        Con Memoización (Lineal), donde V son vértices y E aristas. Cada conexión se visita una única vez.

    Eficiencia de Memoria:

        Usé Listas de Adyacencia (vector<vector<int>>) en lugar de Matrices de Adyacencia. Esto ahorra inmensa cantidad de RAM en grafos dispersos (donde la mayoría de dispositivos no están conectados entre sí).

    Optimización de Bajo Nivel: Al convertir los strings a int al inicio, todas las búsquedas posteriores son accesos directos a memoria, eliminando la sobrecarga de comparar cadenas de texto repetidamente.

4. Diseño y Claridad del Código

Me esforcé por mantener un código legible y modular a pesar de su complejidad técnica:

    Modularidad: Separé la lógica de la estructura de datos de la lógica del algoritmo.

    Robustez: Añadí métodos de seguridad como getID (que devuelve -1 si no encuentra un nodo) y comprobaciones de rangos para evitar fallos en la segmentacion si el input contiene referencias a nodos inexistentes.

5. Alternativas Consideradas y Descartadas

Antes de llegar a la solución final, evalué y descarté estas opciones:

    Fuerza Bruta:

        Idea: Recorrer cada camino y sumar un contador al llegar al final.
        Descarte: Inviable por tiempo de ejecución. El número de caminos crece explosivamente.

    Modificar el DFS para la Parte 2:

        Idea: Pasar booleanos visited_dac y visited_fft en la recursión.
        Descarte: Esto rompe la memoización simple. Un nodo X tendría diferentes valores dependiendo de si ya visité dac o no, obligando a una tabla de memoria tridimensional compleja. 
        La estrategia de multiplicar segmentos fue mucho más limpia.

6. Valoración Personal

Este ejercicio ha sido fundamental para consolidar mi entendimiento sobre la Programación Dinámica aplicada a Grafos.

Lo más valioso que aprendí es que la estructura de datos correcta simplifica el algoritmo. Al principio, el problema de los strings parecía difícil de manejar. 
Al implementar la traducción a IDs numéricos, el problema se transformó en un ejercicio estándar de grafos mucho más sencillo de visualizar y depurar.

También aprendí en la Parte 2 que a veces la solución no es programar más lógica compleja, sino aplicar lógica matemática (dividir el problema en tramos) para reutilizar el código que ya tenía funcionando.

7. Instrucciones de ejecución de códigos

Poner todos los archivos (main.cpp, datosAOC11.txt, Makefile) en una misma carpeta.

Para compilar, ejecutar en la terminal:

 make bin/AOC11 
 make bin/AOC11-2

Ejecutar el programa:

 ./bin/AOC11
 ./bin/AOC11-2

