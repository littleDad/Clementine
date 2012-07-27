#ifndef OAUTHENTICATOR_H
#define OAUTHENTICATOR_H

#include <QObject>
#include <QTcpServer>

#include "core/network.h"

class QTcpSocket;

class OAuthenticator : public QObject {
  Q_OBJECT
 public:
  explicit OAuthenticator(QObject* parent = 0);
  void StartAuthorisation();
  void RefreshAuthorisation(const QString& refresh_token);

 signals:
  // Token to use now.
  void AccessTokenAvailable(const QString& token);
  // Token to use to get a new access token when it expires.
  void RefreshTokenAvailable(const QString& token);

 private slots:
  void NewConnection();
  void RedirectArrived(QTcpSocket* socket, QByteArray buffer);
  void FetchAccessTokenFinished(QNetworkReply* reply);
  void RefreshAccessTokenFinished(QNetworkReply* reply);

 private:
  QByteArray ParseHttpRequest(const QByteArray& request) const;
  void RequestAccessToken(const QByteArray& code, quint16 port);

  QTcpServer server_;
  NetworkAccessManager network_;

  QString access_token_;
  QString refresh_token_;
};

#endif
