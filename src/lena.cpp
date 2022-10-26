#include "QImageViewer.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main (int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " /path/to/image" << std::endl;
        return 0;
    }

    qSetMessagePattern("[%{time hh:mm:ss}][%{function}:%{line}][%{category}] %{message}");

    //
    // Create the app.
    //
    QApplication app(argc, argv);

    //
    // Start Leah
    //
    QImageViewer leah;

    leah.loadFile(argv[1]);
    leah.show();

    return app.exec();
}

