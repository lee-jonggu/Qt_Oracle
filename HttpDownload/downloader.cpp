#include "downloader.h"

Downloader::Downloader(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("http://www.google.com")));
}

void Downloader::replyFinished(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    } else {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        QFile *file = new QFile("./downloaded.html");
        if(file->open(QFile::Append)) {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }
    reply->deleteLater();
}
