/******************************************************************************
 *
 * @file postman.h
 *
 * @brief PostMan - Main Handler for network/http related functions.
 *
 * @author              Hai Pham
 *
 */

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

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the Cartographer.
   */
  explicit PostMan(QObject *parent = nullptr);


  /**
   * @brief Used to make network request to server.
   * @param Url QUrl containing endpoint to make request to.
   * @param postData QUrlQuery containing post body data.
   */
  void makeNetworkRequest(QUrl Url, QUrlQuery postData);

public slots:

  /**
   * @brief Slot to handle finished signal of QNetworkAccessManager.
   * @param reply The QNetworkReply from the network request.
   */
  void networkManagerGotResponse(QNetworkReply *reply);

signals:

  /**
   * @brief Signal with network request response.
   * @param response QString containing response body from network request.
   */
  void newResponseFromServer(const QString& response);

private:
  QNetworkAccessManager *m_networkManager;
};

#endif // POSTMAN_H
