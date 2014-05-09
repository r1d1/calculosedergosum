# Ajustez en fonction de votre version de CMake
cmake_minimum_required (VERSION 2.8)
 
# Nom du projet
project (visualTracking_openCV)
 
find_package (OpenCV REQUIRED) 

# Exécutable "hello", compilé à partir du fichier helloworld.c
add_executable (trackingandfollowing tracking.cpp)
 
# Hello sera linké avec les bibliothèques d'OpenCV
target_link_libraries (trackingandfollowing ${OpenCV_LIBS})
