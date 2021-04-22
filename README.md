# My first Geant4 application
Este archivo contiene la práctica de Geant-4 de la asignatura Física de Partículas en la Frontera de la Energía. 

En este repositorio nos encontramos con el 'main.cc' que recibe el nombre de 'ourmain.cc' y las carpetas:
i) src: donde se encuentran los documentos '.cc'
ii) include: donde se encuentran los documentos '.hh'
iii)build: donde se ejecuta el código
iv) experiment: donde está el '.mac' que se ha de usar para el análisis y el '.dat' con el que se han de comparar los resultado
###############################################################################################################################

Para ejecutarlo:
i) Cada vez que se haga un cambio, se ha de ejecutar el comando 'make' en la carpeta build.
ii) Para ejecutar el programa se escribe en la carpeta build:
   ./ourmain ../experiment/g4Macro_Meroli_100MeV_electron_5p6um_Si.mac
