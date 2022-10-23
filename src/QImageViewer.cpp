#include "QImageViewer.h"
#include <QtWidgets/QScrollBar>
#include <QtGui/QImageReader>

QImageViewer::QImageViewer (QWidget* parent) : QLabel(parent) {

    _scaleFactor = 1.0;

    _scrollArea = new QScrollArea;
    _scrollArea->setBackgroundRole(QPalette::Dark);
    _scrollArea->setWidget(this);

    setPixmap(QPixmap::fromImage(_image));
}

QImageViewer::~QImageViewer () {
}

bool QImageViewer::loadFile (const QString& file) {

    QImageReader reader(file);

    reader.setAutoTransform(true);

    const QImage newImage = reader.read();

    if (newImage.isNull()) {
        return false;
    }

    setImage(newImage);

    return true;
}

void QImageViewer::setImage (const QImage&  newImage) {

    _image = newImage;

    setPixmap(QPixmap::fromImage(_image));

    _scaleFactor = 1.0;

    _scrollArea->setVisible(true);

    adjustSize(); //
}

void QImageViewer::scaleImage (double factor) {

    _scaleFactor *= factor;

    resize(_scaleFactor * pixmap(Qt::ReturnByValueConstant()).size());

    adjustScrollBar(_scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(_scrollArea->verticalScrollBar(),   factor);
}

void QImageViewer::adjustScrollBar (QScrollBar* scrollBar, double factor) {

    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

