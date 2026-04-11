# P1-CE2103-PagedArrays
Este repositorio contiene la implementación de un programa en C++ fundamentado en una clase `PagedArray` que permite manejar arreglos de gran tamaño sin mantener todo su contenido en la memoria principal. La aplicación incluye un generador de archivos de prueba `generator`, que genera archivos de tamaños predeterminados con números aleatorios en formato binario; un programa `sorter` que realiza el ordenamiento utilizando la clase `PagedArray` que encapsula completamente el funcionamiento de un arreglo paginado, en el que solo ciertas partes del arreglo están cargadas en la memoria principal, mientras que el resto se encuentra en disco. Adicionalmente, la solución incluye un programa anexo `baseline`, que consiste en la misma lógica del `sorter`, pero en lugar de la clase `PagedArray` utiliza un arreglo ordinario.

## Instrucciones de uso
## Compilación
Primero compile el programa:
```bash
mkdir build
cd build
cmake ..
make
```

Esto genera dos ejecutables: `generator` y `sorter`.

## Generador de archivos `generator`

Luego, ejecute `generator`:

```bash
./generator -size <SIZE> -output <OUTPUT FILE PATH>
```

**Parámetros:**

- `-size`: tamaño del archivo a generar. Valores aceptados:
  - `SMALL`: 512 MB
  - `MEDIUM`: 1 GB
  - `LARGE`: 2 GB
- `-output`: ruta donde se guarda el archivo binario generado.

**Ejemplo:**

```bash
./generator -size SMALL -output archivo.bin
```

## Ordenador de archivos `sorter`

Ahora, con el archivo creado, ejecute el `sorter` para ordenar el archivo:

```bash
./sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO> -pageSize <PAGE-SIZE> -pageCount <PAGE-COUNT>
```

**Parámetros:**

- `-input`: ruta del archivo binario desordenado.
- `-output`: ruta donde se guarda el archivo ordenado. Se generan dos archivos: uno binario y uno legible en texto (`.txt`).
- `-alg`: algoritmo de ordenamiento. Valores aceptados:
  - `QUICK`: QuickSort
  - `MERGE`: MergeSort
  - `HEAP`: HeapSort
  - `INSERTION`: InsertionSort
  - `SELECTION`: SelectionSort
- `-pageSize`: cantidad máxima de enteros por página.
- `-pageCount`: cantidad de páginas que se mantienen en memoria.

**Ejemplo:**

```bash
./sorter -input archivo.bin -output salida.bin -alg MERGE -pageSize 4096 -pageCount 128
```

**Salida:** al finalizar, el programa imprime el tiempo de ejecución, el algoritmo utilizado y la cantidad de page faults vs page hits.

## Programa para análisis `baseline`

Si desea comparar el comportamiento de los algoritmos al ordenar el PagedArray vs. un arreglo normal, ejecute `baseline`:

```bash
./sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO> 
```

**Parámetros:**

- `-input`: ruta del archivo binario desordenado.
- `-output`: ruta donde se guarda el archivo ordenado. Se generan dos archivos: uno binario y uno legible en texto (`.txt`).
- `-alg`: algoritmo de ordenamiento. Valores aceptados:
  - `QUICK`: QuickSort
  - `MERGE`: MergeSort
  - `HEAP`: HeapSort
  - `INSERTION`: InsertionSort
  - `SELECTION`: SelectionSort
Como es un arreglo normal, no hay tamaño ni cantidad de páginas.

**Ejemplo:**

```bash
./sorter -input archivo.bin -output salida.bin -alg MERGE 
```

**Salida:** al finalizar, el programa imprime el tiempo de ejecución y el algoritmo utilizado.
