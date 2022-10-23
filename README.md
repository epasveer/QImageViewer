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

To build the test program "leah",  run these steps:
```
% cd QImageViewer/src/build
% cmake ..
% make
[ 20%] Automatic MOC and UIC for target leah
[ 20%] Built target leah_autogen
[ 40%] Building CXX object CMakeFiles/leah.dir/leah_autogen/mocs_compilation.cpp.o
[ 60%] Building CXX object CMakeFiles/leah.dir/leah.cpp.o
[ 80%] Building CXX object CMakeFiles/leah.dir/QImageViewer.cpp.o
[100%] Linking CXX executable leah
[100%] Built target leah

```
That will leave a program called "leah".
```
$ ls -l leah
-rwxr-xr-x 1 erniep users 1159560 Oct 23 16:38 leah
```
Give it one argument. The path to some image. It should auto-detech the image format.
```
$ ./leah
usage: ./leah /path/to/image

$ ./leah ../../images/lena.png
```

![image](https://user-images.githubusercontent.com/44415985/197419762-cf2986d6-6e30-460a-b73a-4712312ffda0.png)
