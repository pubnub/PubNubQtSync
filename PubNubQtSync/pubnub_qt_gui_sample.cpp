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
    d_pb_publish.reset(new pubnub_qt("demo-36", "demo-36"));
    connect(d_pb_publish.data(), SIGNAL(outcome(pubnub_res)), this, SLOT(onPublish(pubnub_res)));

    d_pb_subscribe.reset(new pubnub_qt("demo-36", "demo-36"));
    connect(d_pb_subscribe.data(), SIGNAL(outcome(pubnub_res)), this, SLOT(onSubscribe(pubnub_res)));
    d_pb_subscribe->subscribe("qt");
}


pubnub_qt_gui_sample::pubnub_qt_gui_sample()
{

    resetPubnub();
}


void pubnub_qt_gui_sample::onPublish(pubnub_res result)
{
    QString report =  QString("Publish result: '") + pubnub_res_2_string(result) + "', response: " + d_pb_publish->last_publish_result() + "\n";

    qDebug() << report;
//    d_console->insertPlainText(report);
//    QScrollBar *bar = d_console->verticalScrollBar();
//    bar->setValue(bar->maximum());
}


void pubnub_qt_gui_sample::onSubscribe(pubnub_res result)
{
    if (PNR_OK != result) {
        qDebug() << "subscribe failed";
//        d_console->insertPlainText(QString("Subscribe failed, result: ") + pubnub_res_2_string(result) + '\n');
    }
    else {
        QList<QString> msg = d_pb_subscribe->get_all();
        qDebug() << "msg";
        qDebug() << msg;
        for (int i = 0; i < msg.size(); ++i) {
            qDebug() << "subscribe message " + msg[i] + '\n';
            QJsonDocument json = QJsonDocument::fromJson(msg[i].toUtf8());
            qDebug() << json;
            QJsonObject object = json.object();
            qDebug() << "object";
            qDebug() << object;
//            qDebug() << object.value("text");
//            if (mainView) {
//                qDebug() << "has mainView";
//                qDebug() << mainView->children();
//                qDebug() << mainView->source();
//                qDebug() << mainView->rootObject();
//                QQuickItem *item = mainView->rootObject();
//                qDebug() << "item is ";
//                qDebug() << item;
//                mainView->rootObject()->setProperty("value", 160);
//                qDebug() << "property value:" << QQmlProperty::read(item, "height").toInt();
//                QObject *speedometer = item->findChild<QObject*>("speedometer", Qt::FindChildrenRecursively);
//                if (speedometer) {
//                    qDebug() << "found speedometer!";
//                    speedometer->setProperty("value", 160);
//                }
////                QQuickItem *speedometer = mainView->findChild<QQuickItem*>("speedometer", Qt::FindChildrenRecursively);
////                if (speedometer) {
////                    qDebug() << "has speedometer";
////                    speedometer->setProperty("value", 160);
////                }


//            }
            if (mainWindow) {
                qDebug() << "has mainWindow";
                qDebug() << mainWindow->children();
                QQuickItem *valueSource = mainWindow->findChild<QQuickItem*>("valueSource", Qt::FindChildrenRecursively);
                if (valueSource) {
                    qDebug() << "has valueSource!";
//                    valueSource->setProperty("kph", 160);
//                    valueSource->setProperty("rpm", 4.5);
//                    valueSource->setProperty("fuel", 0.5);
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
            
//            d_console->insertPlainText(msg[i] + '\n');
        }
    }

//    QScrollBar *bar = d_console->verticalScrollBar();
//    bar->setValue(bar->maximum());

    result = d_pb_subscribe->subscribe("qt");
    if (result != PNR_STARTED) {
        qDebug() << "subscribe failed";
//        d_console->insertPlainText(QString("Subscribe failed, result: '") + pubnub_res_2_string(result) + "'\n");
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
//        d_console->insertPlainText(QString("Publish failed, result: '") + pubnub_res_2_string(result) + "'\n");
    }
}

