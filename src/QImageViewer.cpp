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

QImageViewer::QImageViewer (QWidget* parent) : QWidget(parent) {

    _zoomFactor = 1.0;

    // Construct the UI.
    setupUi(this);

    // Setup the widgets
    _imageLabel = new QLabel;

    _imageLabel->setBackgroundRole(QPalette::Base);
    _imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  //_imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(_imageLabel);
    scrollArea->setVisible(true);

    _imageLabel->setPixmap(QPixmap::fromImage(_image));
}

QImageViewer::~QImageViewer () {
}

bool QImageViewer::loadFile (const QString& file) {

    QImageReader reader(file);

    reader.setAutoTransform(true);

    QImage image = reader.read();

    if (image.isNull()) {
        return false;
    }

    setImage(image);

    return true;
}

void QImageViewer::setImage (const QImage& image) {

    qDebug() << image;

    _image      = image;
    _zoomFactor = 1.0;

    _imageLabel->setPixmap(QPixmap::fromImage(_image));
    _imageLabel->adjustSize(); //
}

const QImage& QImageViewer::image () const {

    return _image;
}

double QImageViewer::zoomFactor () const {

    return _zoomFactor;
}

void QImageViewer::zoom (double factor) {

    qDebug() << "New scale factor " << factor;

    _zoomFactor = factor;

    _imageLabel->resize(_zoomFactor * _imageLabel->pixmap(Qt::ReturnByValue).size());

    //adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    //adjustScrollBar(scrollArea->verticalScrollBar(),   factor);
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

    Q_ASSERT(_imageLabel->pixmap(Qt::ReturnByValue).isNull() == false);

    QPrintDialog dialog(&_printer, this);

    if (dialog.exec()) {
        QPainter painter(&_printer);
        QRect rect = painter.viewport();
        QSize size = _imageLabel->pixmap(Qt::ReturnByValue).size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(_imageLabel->pixmap(Qt::ReturnByValue).rect());
        painter.drawPixmap(0, 0, _imageLabel->pixmap(Qt::ReturnByValue));
    }
}

void QImageViewer::keyPressEvent (QKeyEvent* event) {

    qDebug() << "Key =" << event->key();

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
            QWidget::keyPressEvent(event);
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

