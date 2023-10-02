#ifndef POSTMAN_H
#define POSTMAN_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

class PostMan : public QObject
{
  Q_OBJECT
public:
  explicit PostMan(QObject *parent = nullptr);

public slots:
  void networkManagerGotResponse(QNetworkReply *reply);
  void makeNetworkRequest(QUrl Url, QUrlQuery postData);

signals:
  void newResponseFromServer(const QString& response);

private:
  QNetworkAccessManager *m_networkManager;
};

#endif // POSTMAN_H
