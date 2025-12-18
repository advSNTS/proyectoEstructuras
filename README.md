# Proyecto de Estructuras de Datos – Procesamiento de Imágenes

Este proyecto implementa un **sistema interactivo por consola** para el procesamiento de imágenes en formato **PGM P2**, desarrollado en **C++**.

El sistema permite cargar imágenes y volúmenes, obtener información, generar proyecciones 2D, segmentar imágenes y realizar **codificación y decodificación mediante Huffman**, utilizando diferentes **Tipos Abstractos de Datos (TADs)** como vectores, grafos y árboles.

## 🧠 Estructuras de datos utilizadas

El proyecto hace uso explícito de las siguientes estructuras:

- **Vectores (`std::vector`)**
  - Almacenamiento de imágenes
  - Manejo de segmentos y semillas
- **Grafos**
  - Representación de relaciones entre píxeles para segmentación
- **Árboles**
  - Árbol de Huffman para codificación y decodificación de imágenes
- **Clases y TADs propios**
  - `Imagen`
  - `Volumen`
  - `Sistema`
  - `Grafo`, `Arista`
  - `ArbolHuffman`, `NodoHuffman`

## ⚙️ Funcionalidades principales

El sistema funciona mediante comandos ingresados por consola:

- **Carga de datos**
  - `cargar_imagen <nombre_imagen.pgm>`
  - `cargar_volumen <nombre_base> <n_im>`

- **Consulta de información**
  - `info_imagen`
  - `info_volumen`

- **Procesamiento**
  - `proyeccion2D <dirección> <criterio> <archivo_salida.pgm>`
  - `segmentar <salida_imagen.pgm> <sx1> <sy1> <sl1> ...`

- **Compresión**
  - `codificar_imagen <archivo.huf>`
  - `decodificar_archivo <archivo.huf> <imagen_salida.pgm>`

- **Ayuda**
  - `ayuda`
  - `ayuda <comando>`

- **Salida**
  - `salir`

El sistema valida errores de entrada y muestra mensajes claros para cada caso.

## 📂 Estructura del proyecto

├── main.cxx
├── sistema.h
├── sistema.cxx
├── imagen.h
├── imagen.cxx
├── volumen.h
├── volumen.cxx
├── Grafo.h
├── Grafo.cxx
├── Arista.h
├── Arista.cxx
├── ArbolHuffman.h
├── ArbolHuffman.cxx
├── NodoHuffman.h
├── NodoHuffman.cxx
└── README.md


## 🛠️ Compilación

Para compilar el proyecto, utiliza el siguiente comando en Bash:

```bash
g++ -std=c++11 -o sistema main.cxx sistema.cxx imagen.cxx volumen.cxx Grafo.cxx Arista.cxx ArbolHuffman.cxx NodoHuffman.cxx
```
Y para ejecutarlo:

```bash
./sistema
```