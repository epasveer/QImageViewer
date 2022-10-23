#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <QtGui/QImage>

class QImageViewer : public QLabel {

    Q_OBJECT

    public:
        QImageViewer (QWidget* parent = 0);
       ~QImageViewer ();

        bool                    loadFile                (const QString& file);

    public  slots:
    private slots:

    private:

        void                    setImage                (const QImage&  newImage);
        void                    scaleImage              (double factor);
        void                    adjustScrollBar         (QScrollBar* scrollBar, double factor);

        QImage                  _image;
        QScrollArea*            _scrollArea;
        double                  _scaleFactor;

};

