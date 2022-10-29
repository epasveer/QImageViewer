#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <QtGui/QImage>
#include <QtGui/QKeyEvent>
#include <QtGui/QWheelEvent>
#include <QtPrintSupport/QPrinter>

class QImageViewer : public QLabel {

    Q_OBJECT

    public:
        QImageViewer (QWidget* parent = 0);
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
        QScrollArea*            _scrollArea;
        double                  _zoomFactor;
        QPrinter                _printer;
};

