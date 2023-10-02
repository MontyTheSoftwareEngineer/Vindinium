#include "postman.h"

#include <QNetworkRequest>

PostMan::PostMan(QObject *parent)
  : QObject{parent}
{
  m_networkManager = new QNetworkAccessManager(this);
  connect(m_networkManager, &QNetworkAccessManager::finished, this, &PostMan::networkManagerGotResponse);
}

void PostMan::networkManagerGotResponse(QNetworkReply *reply)
{
  qDebug() << "HERE";
  if (reply->error() == QNetworkReply::NoError)
  {
    QString response = reply->readAll();
    qDebug() << response;
    emit newResponseFromServer(response);
  }
  else
  {
    qDebug() << "Error:" << reply->errorString();
  }
}

void PostMan::makeNetworkRequest(QUrl Url, QUrlQuery postData)
{
  QNetworkRequest request(Url);

  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  m_networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}
