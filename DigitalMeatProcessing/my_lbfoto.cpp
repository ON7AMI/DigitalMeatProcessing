#include "my_lbfoto.h"

#include <QUrl>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWidget>
#include <QMimeData>
#include <QFileInfo>
#include <QBuffer>

my_lbFoto::my_lbFoto(QWidget *parent) : QLabel(parent)
{
    this->setAcceptDrops(true);
}

void my_lbFoto::dragEnterEvent(QDragEnterEvent *event)
{
    // accept just text/uri-list mime format
    if (event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}


void my_lbFoto::dropEvent(QDropEvent *event)
{
    QList<QUrl> urlList;
    QString fName;

    QFileInfo info;
    QString bestand;

    if (event->mimeData()->hasUrls())
    {
        urlList = event->mimeData()->urls(); // returns list of QUrls

        // if just text was dropped, urlList is empty (size == 0)
        if ( urlList.size() > 0) // if at least one QUrl is present in list
        {
            fName = urlList[0].toLocalFile(); // convert first QUrl to local path
            info.setFile( fName ); // information about file
            if ( info.isFile() )
            {
                bestand = fName ; // if is file, setText
                QPixmap image(bestand);
                QByteArray bytes;
                QBuffer buffer(&bytes);
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "PNG");

                this->setPixmap(image);
            }
        }
    }

    event->acceptProposedAction();
}
