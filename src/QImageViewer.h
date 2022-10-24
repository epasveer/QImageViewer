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
        void                    setImage                (const QImage&  newImage);
        const QImage&           image                   () const;

    public slots:
        void                    scaleImage              (double factor);

    private slots:

    private:
        void                    adjustScrollBar         (QScrollBar* scrollBar, double factor);

        QImage                  _image;
        QScrollArea*            _scrollArea;
        double                  _scaleFactor;

};

