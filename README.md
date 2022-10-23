# QImageViewer
A simple Qt widget to view all images that QImage supports.

There are two files you can copy to your project:

* QImageViewer.h
* QImageviewer.cpp

The widget supports:

* Loading the image from a file
* Loading the image from memory
* Scrollbars if the image is larger than the widget
* A slot to scale
* A slot to zoom in
* A slot to zoom out
* A slot to reset zoom and scale.
* A slot to invoke print dialog.

To build the test program "lena",  run these steps:
```
% cd QImageViewer/src/build
% cmake ..
% make
[ 20%] Automatic MOC and UIC for target lena
[ 20%] Built target lena_autogen
[ 40%] Building CXX object CMakeFiles/lena.dir/lena_autogen/mocs_compilation.cpp.o
[ 60%] Building CXX object CMakeFiles/lena.dir/lena.cpp.o
[ 80%] Building CXX object CMakeFiles/lena.dir/QImageViewer.cpp.o
[100%] Linking CXX executable lena
[100%] Built target lena

```
That will leave a program called "lena".
```
$ ls -l lena
-rwxr-xr-x 1 erniep users 1159560 Oct 23 16:38 lena
```
Give it one argument, the path to some image. It should auto-detect the image format and will display it.
```
$ ./lena
usage: ./lena /path/to/image

$ ./lena ../../images/lena.png
```
![image](https://user-images.githubusercontent.com/44415985/197419762-cf2986d6-6e30-460a-b73a-4712312ffda0.png)

