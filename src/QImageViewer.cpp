#include "QImageViewer.h"
#include <QtWidgets/QScrollBar>
#include <QtGui/QImageReader>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtPrintSupport/QPrintDialog>

//
// https://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
//
// Except mine extends QLabel, not QMainWindow.
//

QImageViewer::QImageViewer (QWidget* parent) : QLabel(parent) {

    _zoomFactor = 1.0;

    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);

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

    QImage newImage = reader.read();

    if (newImage.isNull()) {
        return false;
    }

    setImage(newImage);

    return true;
}

void QImageViewer::setImage (const QImage&  newImage) {

    _image = newImage;

    qDebug() << _image;

    setPixmap(QPixmap::fromImage(_image));

    _zoomFactor = 1.0;

    _scrollArea->setVisible(true);

    adjustSize(); //
}

const QImage& QImageViewer::image () const {

    return _image;
}

double QImageViewer::zoomFactor () const {

    return _zoomFactor;
}

void QImageViewer::zoom (double factor) {

    // qDebug() << "New scale factor " << factor;

    _zoomFactor = factor;

    resize(_zoomFactor * pixmap(Qt::ReturnByValueConstant()).size());

    adjustScrollBar(_scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(_scrollArea->verticalScrollBar(),   factor);
}

void QImageViewer::zoomIn () {

    zoom(zoomFactor() * 1.25);
}

void QImageViewer::zoomOut () {

    zoom(zoomFactor() * 0.8);
}

void QImageViewer::zoomReset () {

    zoom(1.0);
}

void QImageViewer::print () {

    Q_ASSERT(pixmap(Qt::ReturnByValueConstant()).isNull() == false);

    QPrintDialog dialog(&_printer, this);

    if (dialog.exec()) {
        QPainter painter(&_printer);
        QRect rect = painter.viewport();
        QSize size = pixmap(Qt::ReturnByValueConstant()).size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(pixmap(Qt::ReturnByValueConstant()).rect());
        painter.drawPixmap(0, 0, pixmap(Qt::ReturnByValueConstant()));
    }
}

void QImageViewer::keyPressEvent (QKeyEvent* event) {

    // qDebug() << "Key =" << event->key();

    switch (event->key()) {
        case Qt::Key_Escape:
            zoomReset();
            break;
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_P:
            if (event->modifiers() == Qt::ControlModifier) {
                print();
            }
            break;
        default:
            QLabel::keyPressEvent(event);
            break;
    }
}

void QImageViewer::enterEvent (QEvent* event) {

    Q_UNUSED(event);

    setFocus();
}

void QImageViewer::leaveEvent (QEvent* event) {
    Q_UNUSED(event);
}

void QImageViewer::adjustScrollBar (QScrollBar* scrollBar, double factor) {

    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

