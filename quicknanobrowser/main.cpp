/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT_NO_WIDGETS
#include <QtWidgets/QApplication>
typedef QApplication Application;
#else
#include <QtGui/QGuiApplication>
typedef QGuiApplication Application;
#endif
#include <QWebEngineView>

#include <QtNetwork>

#include <QTcpServer>

class Server : public QObject
{
public:
    explicit Server(QWebEngineView &view);
    bool listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 1234);

private slots:
    void onConnection();
    void onRead();

private:
    QTcpServer server;
    QWebEngineView &view;
};

Server::Server(QWebEngineView &view)
    : server(this)
    , view(view)
{
}

bool Server::listen(const QHostAddress &address, quint16 port)
{
    if (!server.listen(address, port)) {
        qCritical() << server.errorString();
        return false;
    }

    connect(&server, &QTcpServer::newConnection, this, &Server::onConnection);

    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressList.size(); ++i) {
        if (ipAddressList.at(i) != QHostAddress::LocalHost &&
            ipAddressList.at(i).toIPv4Address()) {
            ipAddress = ipAddressList.at(i).toString();
            break;
        }
    }

    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qInfo() << ipAddress<< ":" << port;

    return true;
}

void Server::onConnection()
{
    QTcpSocket *socket = server.nextPendingConnection();
    connect(socket, &QAbstractSocket::readyRead, this, &Server::onRead);
}

void Server::onRead()
{
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    char data[1024];
    qint64 size = socket->readLine(data, sizeof(data));
    if (!size)
        return;

    data[size] = 0;
    while (data[size-1] == '\n') data[--size] = 0;
    if (!size)
        return;

    socket->write(data);
    socket->disconnectFromHost();

    view.setUrl(QUrl(data));
}

int main(int argc, char **argv)
{
    Application app(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QWebEngineView view;
    view.showFullScreen();
    view.setUrl(QUrl("https://www.savoirfairelinux.com"));

    Server server(view);
    if (!server.listen())
        return 1;

    return app.exec();
}
