Memoria Advent of Code 2025 - Día 5

Problema: Day 5 - Cafeteria (Part 1 & Part 2)

1. Justificación

Elegí este problema porque representa un punto de inflexión respecto a los ejercicios anteriores: es un problema de optimización de rangos. Es el escenario perfecto para demostrar que la fuerza bruta es inviable cuando los datos escalan, y para aplicar estrategias avanzadas como Divide y Vencerás y algoritmos de Barrido de Línea.
Además, permite trabajar la gestión eficiente de la memoria RAM mediante técnicas de streaming en la lectura de archivos de texto.

2. Descripción Técnica

El núcleo del problema es gestionar rangos de números (IDs) que pueden solaparse. Dividí la estrategia en dos fases claras:

El Motor (Merge Intervals): Tanto para la Parte 1 como para la Parte 2, el paso crítico es la función merge_ranges.

Primero, ordenamos los rangos según su inicio (Divide y Vencerás implícito en el algoritmo de ordenación).

Luego, recorremos la lista una sola vez fusionando los intervalos superpuestos (ej: 10-14 y 12-18 se convierten en 10-18). Esto reduce drásticamente el espacio de búsqueda y elimina redundancias.

Parte 1 (Búsqueda Binaria): El objetivo era verificar si millones de IDs individuales pertenecían a algún rango válido.

En lugar de comprobar cada ID contra todos los rangos (lento), implementé una Búsqueda Binaria Manual. Al tener los rangos ya fusionados y ordenados, puedo descartar la mitad de los datos en cada comparación, logrando respuestas casi instantáneas.

Parte 2 (Cálculo de Volumen): El requerimiento cambió a calcular cuántos números totales cubren los rangos.

Aquí la búsqueda binaria deja de ser útil. Cambié a un enfoque aritmético: sumar la longitud de los rangos fusionados (fin - inicio + 1).
Gracias a la fusión previa, evito el error matemático de contar duplicados en las intersecciones de los rangos.

3. Calidad Algorítmica y Eficiencia

La prioridad absoluta fue reducir la complejidad temporal y espacial para evitar el colapso del programa con inputs masivos.

Complejidad Temporal: Una solución basica compararía cada consulta con cada rango, resultando en O. Mi solución invierte tiempo en ordenar los rangos al principio, haciendo que las operaciones posteriores sean triviales.

Gestión de Memoria (Streaming):

Parte 1: No almaceno los IDs de consulta en un vector. Los leo, los proceso y los descarto en tiempo real (O(1) en memoria para consultas).

Parte 2: Implementé un Cierre Temprano (file.close()) justo al terminar de leer los rangos. El programa ignora los millones de líneas de IDs innecesarias, ahorrando ciclos de CPU y lectura de disco.

4. Diseño y Claridad del Código

El código sigue una arquitectura procedimental académica y robusta:

Estructuras de Datos: Usé struct Range con sobrecarga del operador < para facilitar la ordenación natural con std::sort.

Separación de Fases: El main está estructurado en bloques lógicos secuenciales (Lectura -> Optimización -> Procesamiento), evitando el uso de "banderas" complejas y prefiriendo bucles de lectura especializados.

Limpieza Explícita: Uso comandos como ranges.shrink_to_fit() y clear() para demostrar control sobre los recursos del sistema, liberando memoria de datos crudos una vez procesados.

5. Alternativas Descartadas

Antes de llegar a la solución final, descarté:

Tablas Hash / Arrays Booleanos: Pensé en crear un array gigante donde arr[id] = true. Lo descarté inmediatamente porque si los IDs llegan a 1.000 millones, necesitaría gigabytes de RAM, provocando un desbordamiento de memoria.

Fuerza Bruta: Iterar todos los rangos originales para cada ID. Se descartó porque con inputs grandes el tiempo de ejecución sería de horas en lugar de milisegundos.

6. Valoración Personal

Este ejercicio ha sido fundamental para entender la diferencia entre Datos Crudos y Datos Procesados. He aprendido que "invertir tiempo" ordenando y limpiando los datos al principio (Fusión de Intervalos) ahorra una cantidad inmensa de tiempo después. También me ha servido para practicar la lectura robusta de archivos de texto con formatos mixtos y la importancia de no cargar en memoria datos que no se van a utilizar.

7. INSTRUCCIONES DE EJECUCION DE CODIGOS

Poner todos los archivos (main.cpp, datosAOC5.txt, Makefile si lo hubiera) en una misma carpeta.

Para compilar, ejecutar en la terminal:

make bin/AOC5 (Para el programa de la Parte 1)
make bin/AOC5-2 (Para el programa de la Parte 2)

Ejecutar el programa:

./bin/AOC5
./bin/AOC5-2
