/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "pubnub_qt_gui_sample.h"

extern "C" {
#include "pubnub_helper.h"
}

#include <QQuickWindow>
#include <QQuickItem>
#include <QMetaObject>
#include <QQmlProperty>
#include <QJsonDocument>
#include <QJsonObject>

void pubnub_qt_gui_sample::resetPubnub()
{
    // sign up for keys at http://pubnub.com
    d_pb_publish.reset(new pubnub_qt("<pub-key here>", "<sub-key here>"));
    connect(d_pb_publish.data(), SIGNAL(outcome(pubnub_res)), this, SLOT(onPublish(pubnub_res)));

    d_pb_subscribe.reset(new pubnub_qt("<pub-key here>", "<sub-key here>"));
    connect(d_pb_subscribe.data(), SIGNAL(outcome(pubnub_res)), this, SLOT(onSubscribe(pubnub_res)));
    d_pb_subscribe->subscribe("qt-data-simulator");
}


pubnub_qt_gui_sample::pubnub_qt_gui_sample()
{

    resetPubnub();
}


void pubnub_qt_gui_sample::onPublish(pubnub_res result)
{
    QString report =  QString("Publish result: '") + pubnub_res_2_string(result) + "', response: " + d_pb_publish->last_publish_result() + "\n";

    qDebug() << report;
}


void pubnub_qt_gui_sample::onSubscribe(pubnub_res result)
{
    if (PNR_OK != result) {
        qDebug() << "subscribe failed";
    }
    else {
        QList<QString> msg = d_pb_subscribe->get_all();
        for (int i = 0; i < msg.size(); ++i) {
            qDebug() << "subscribe message " + msg[i] + '\n';
            QJsonDocument json = QJsonDocument::fromJson(msg[i].toUtf8());
            QJsonObject object = json.object();


            if (mainWindow) {
                qDebug() << "has mainWindow";
                qDebug() << mainWindow->children();
                QQuickItem *valueSource = mainWindow->findChild<QQuickItem*>("valueSource", Qt::FindChildrenRecursively);
                if (valueSource) {
                    qDebug() << "has valueSource!";
                    if (object.contains("kph")) {
                        valueSource->setProperty("kph", object.value("kph").toInt());
                    }
                    if (object.contains("rpm")) {
                        valueSource->setProperty("rpm", object.value("rpm").toDouble());
                    }
                    if (object.contains("fuel")) {
                        valueSource->setProperty("fuel", object.value("fuel").toDouble());
                    }
                }
            }
            
        }
    }

    result = d_pb_subscribe->subscribe("qt-data-simulator");
    if (result != PNR_STARTED) {
        qDebug() << "subscribe failed";
    }
}


void pubnub_qt_gui_sample::pubkeyChanged()
{
    qDebug() << "pubkeyChanged()";
    resetPubnub();
}


void pubnub_qt_gui_sample::keysubChanged()
{
    qDebug() << "keysubChanged()";
    resetPubnub();
}


void pubnub_qt_gui_sample::channelChanged()
{
    qDebug() << "channelChanged()";
    d_pb_subscribe->cancel();
}


void pubnub_qt_gui_sample::messageChanged()
{
    qDebug() << "messageChanged()";
    pubnub_res result = d_pb_publish->publish("qt", "testing");
    if (result != PNR_STARTED) {
        qDebug() << "Publish failed";
    }
}

