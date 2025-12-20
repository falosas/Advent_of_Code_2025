Memoria Advent of Code 2025 - Día 1

1. Justificación
Elegí este problema porque, aunque parece sencillo, esconde una trampa técnica importante: cómo maneja C++ los números negativos. Es ideal para demostrar dos habilidades clave:

Corregir errores matemáticos básicos (el problema del módulo negativo).

Cambiar totalmente de estrategia cuando las reglas se complican en la Parte 2 (pasar de simular paso a paso a usar matemáticas directas).

2. Descripción Técnica
Para resolverlo, dividí el enfoque en dos partes según lo que pedía el enunciado:

Parte 1 (El Círculo): Usé la fórmula del "reloj" (módulo % 100). El reto fue que C++ calcula mal el residuo de números negativos.
Lo solucioné ajustando la fórmula para que el dial siempre se mantenga entre 0 y 99, sin importar cuánto reste.

Parte 2 (La Línea Recta): En lugar de girar en círculos, imaginé el dial como una cinta métrica infinita.

El Truco: Empecé en un número gigante (1 billón + 50) para trabajar siempre con positivos y evitar errores de resta.

El Cálculo: Para saber cuántas veces paso por el 0, simplemente miro en qué "centena" estoy. 
Si paso del 190 (sector 1) al 210 (sector 2), sé matemáticamente que he cruzado una vez el cero, sin tener que simular los pasos intermedios.

3. Calidad Algorítmica y Eficiencia
Me enfoqué en que el programa fuera instantáneo, sin importar el tamaño de los datos.

Sin Bucles Lentos: Una solución básica contaría paso a paso (1, 2, 3...). Si el input dice "mueve 10 millones", eso tardaría mucho.

Complejidad Constante O(1): Mi solución usa una sola resta para calcular el resultado. Moverse 1 casilla o moverse 1.000 millones tarda exactamente lo mismo: nanosegundos. Es la máxima eficiencia posible.

4. Diseño y Claridad del Código
Diseñé el código para que cualquier programador lo entienda rápido:

Variables Claras: Usé nombres como total_zeros o old_pos en lugar de a o b.

Seguridad: Usé long long (números gigantes) para asegurar que el programa nunca se rompa por falta de espacio en memoria.

Orden: Separé la lógica en funciones y añadí comentarios explicando el truco de la "cinta infinita" para que quede claro por qué empecé en un número tan alto.

5. Alternativas Descartadas
Antes de llegar a la solución final, descarté:

Fuerza Bruta (Paso a paso): Pensé en hacer un bucle que sumara +1 en cada movimiento. Lo descarté porque sería lentísimo con números grandes.

Aritmética simple: Intenté usar solo % para la parte 2, pero fallaba porque el módulo "olvida" cuántas vueltas he dado. Por eso cambié al sistema de coordenadas absolutas (la línea recta).

6. Valoración Personal
Este ejercicio me enseñó dos lecciones valiosas:

Cuidado con las herramientas: Aprendí que el operador % en C++ no funciona igual que en matemáticas puras cuando hay negativos.

Cambio de Perspectiva: Lo más importante fue aprender que, a veces, para resolver un problema circular (un dial), es más fácil tratarlo como un problema lineal (una recta). 
Cambiar la forma de ver el problema simplificó todo mi código.


7. Instrucciones de compilación y ejecución

    1. Estructura de Directorios Asegúrate de mantener la estructura del proyecto. El archivo Makefile debe estar en la raíz, y los códigos fuente junto con sus archivos de datos dentro de sus carpetas correspondientes.

    2. Compilación Desde la terminal en la carpeta raíz del proyecto, ejecuta una de las siguientes opciones:

    Compilar programas:

      make bin/AOC1
    
      make bin/AOC1-2
    
    3. Ejecución, el programa requiere que le indiques la ruta del archivo de datos como argumento. Ejecuta el comando referenciando el binario y la ruta relativa del archivo de texto:

      ./bin/AOC1 Dia-1/datosAOC1.txt
    
      ./bin/AOC1-2 Dia-1/datosAOC1.txt
