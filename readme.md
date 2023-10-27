Integrantes: Javier Caamaño 21.377.764-5 // Diego Espinosa 21.064.138-6 // Darikson Yang Li 	21.178.716-3

Esta aplicacion permite al usuario indexar archivos .txt ademas de permitir distintos tipos de  busquedad usaremos una struct Palabra que contiene la palabra y su frecuencia y el struct Libro que contiene id, titulo, numCaracteres, numPalabras y palabrasXLibro

Funcionalidades:
- Cargar documentos
- Mostrar documentos ordenados
- Buscar un libro pot titulo
- Palabras con mayor frecuencia
- Palabras mas relevantes
- Buscar por palabra
- Mostrar palabra en su contexto dentro del libro
(en funcionamiento hasta la opcion 4)

Errores conocidos:
1. El programa es capaz de ingresar al documento, sin embargo nos da un error que no logramos descubrir y se cierra el programa, hemos colocado un  printf y nos aseguramos que se guarde el titulo sin embargo algo falla y se cierra de forma prematura. Este error fue consultado con el profesor y no econtro solución.
2. Problema con la funcion palabraRelevante, debido a incongruencias con el treemap por lo tanto la comentaremos para evitar problemas de compilacion 
3. Un funcionamiento lento en la funcion para mostrar palabra en su contexto
4. Falta de funcion buscarPorPalabra
5. 

A mejorar:
- La organizacion a la hora de trabajar en equipo
- Comprobar con mayor frecuencia y comentar a todos los errores que se encuentren para ver soluciones
- Preguntar de manera mas frecuencia a los profesores o ayudantes en cuanto nos surja una duda en el codigo que no seamos capaz de solucionar

gestor de tareas:
cd <path al lugar donde se desea clonar>

compilar el codigo:
gcc main.c treemap.c list.c -o tarea3

ejecutar aplicacion:
./tarea1

Contribuciones

Javier Caamaño 21.377.764-5
Creacion de la base de las funciones cargarDocumentos, busquedaDeLibro, palabrasConMayorFrecuencia,
palabraRelevante que posteriormente fueron revisadas y corregidas por los demas 
integrantes del grupo debido a sus multiples errores.
Auto-evaluacion: 3(Aporte excelente)

Diego Espinosa 21.064.138-6
manejo de TDAs y choques de variables
Intento de arreglo respecto a TDAs
Auto-evaluacion: 3(Aporte excelente)

Darikson Yang Li 	21.178.716-3
Alta participación en cuanto a creación y modificación de funciones
Manejo de TDAs
Auto-evaluacion: 3(Aporte excelente)

