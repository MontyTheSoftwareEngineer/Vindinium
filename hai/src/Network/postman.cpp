/******************************************************************************
 *
 * @file postman.cpp
 *
 * @brief PostMan - Main Handler for network/http related functions.
 *
 * @author              Hai Pham
 *
 */

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
  qDebug() << "Network response";
  if (reply->error() == QNetworkReply::NoError)
  {
    QString response = reply->readAll();
    emit    newResponseFromServer(response);
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
