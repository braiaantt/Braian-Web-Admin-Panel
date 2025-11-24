#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QNetworkReply>

namespace NetworkUtils{
    bool checkError(QNetworkReply *reply, QString &errorMsg);
}

#endif // NETWORKUTILS_H
