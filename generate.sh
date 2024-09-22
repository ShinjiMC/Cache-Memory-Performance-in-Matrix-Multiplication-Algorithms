#!/bin/bash
set -x  # Habilitar el modo de depuración

# 1. Compilar el archivo exe4.cpp
g++ -g exe4.cpp -o exe4
if [ $? -ne 0 ]; then
  echo "Error en la compilación."
  exit 1
fi

# 2. Ejecutar valgrind con cachegrind y capturar el PID
valgrind --tool=cachegrind ./exe4 &> valgrind_output.txt
if [ $? -ne 0 ]; then
  echo "Error al ejecutar Valgrind."
  exit 1
fi

# Verificar el archivo de salida de Valgrind
ls -lh cachegrind.out.* # Lista los archivos de salida

# Capturar el PID del archivo de salida
pid=$(ls cachegrind.out.* | grep -oP "\d+")
if [ -z "$pid" ]; then
  echo "No se pudo obtener el PID de Valgrind."
  cat valgrind_output.txt  # Mostrar el contenido de la salida para depuración
  exit 1
fi

# 3. Ejecutar cg_annotate con el archivo de salida de cachegrind
cg_annotate cachegrind.out.$pid > cache_analysis_4.txt
if [ $? -eq 0 ]; then
  echo "Análisis de caché generado en cache_analysis_4.txt."
else
  echo "Error al ejecutar cg_annotate."
fi

set +x  # Deshabilitar el modo de depuración
