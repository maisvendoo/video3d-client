//------------------------------------------------------------------------------
//
//
//
//
//------------------------------------------------------------------------------
/*!
 *
 *
 *
 *
 *
 */

#include    "tcp-client.h"
#include    "server-data-struct.h"
#include    "settings.h"

#include    <QTimer>
#include    <osgViewer/Viewer>

#ifndef     NETWORK_H
#define     NETWORK_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class NetworkClient : public QObject
{
    Q_OBJECT

public:

    explicit NetworkClient(QObject *parent = Q_NULLPTR);
    virtual ~NetworkClient();

    void init(const settings_t &settings, osgViewer::Viewer *viewer);

private:

    TcpClient   *tcp_cilent;

    osgViewer::Viewer *viewer;

    QTimer      timerRequester;

    server_data_t   server_data;

private slots:

    void onClientAuthorized();

    void onClientDissconnected();

    void onTimerRequester();
};

#endif // NETWORK_H
