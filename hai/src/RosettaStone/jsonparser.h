#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>

class JSONParser : public QObject
{
  Q_OBJECT
public:
  struct GameData
  {
    QString m_gameID;
    QString m_playUrl;
    QString m_viewUrl;
    int     m_mapSize;
    QString m_gameMap;
  };
  explicit JSONParser(QObject *parent = nullptr);

  GameData parseJSONString(const QString& jsonString);

signals:
};

#endif // JSONPARSER_H
