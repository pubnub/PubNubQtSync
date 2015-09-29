#ifndef PUBNUBQML_H
#define PUBNUBQML_H

#include <QObject>

class PubNubQML : public QObject
{
    Q_OBJECT
public:
    explicit PubNubQML(QObject *parent = 0);

signals:
    messageReceived(const QString &subject);
public slots:
};

#endif // PUBNUBQML_H
