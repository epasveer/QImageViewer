#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtGui/QImage>
#include <QtGui/QKeyEvent>
#include <QtGui/QWheelEvent>
#include <QtPrintSupport/QPrinter>
#include "ui_QImageViewer.h"

class QImageViewer : public QWidget, protected Ui::QImageViewer {

    Q_OBJECT

    public:
        explicit QImageViewer (QWidget* parent = 0);
       ~QImageViewer ();

        bool                    loadFile                (const QString& file);
        void                    setImage                (const QImage& image);
        const QImage&           image                   () const;

        double                  zoomFactor              () const;

    public slots:
        void                    zoom                    (double factor);
        void                    zoomIn                  ();
        void                    zoomOut                 ();
        void                    zoomReset               ();
        void                    print                   ();

    protected slots:
        void                    keyPressEvent           (QKeyEvent* event);
        void                    enterEvent              (QEvent*    event);
        void                    leaveEvent              (QEvent*    event);

    private:
        void                    adjustScrollBar         (QScrollBar* scrollBar, double factor);

        QImage                  _image;
        QLabel*                 _imageLabel;
        double                  _zoomFactor;
        QPrinter                _printer;
};

