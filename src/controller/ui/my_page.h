#ifndef MYPAGECONTROLLER_H
#define MYPAGECONTROLLER_H

#include <QtQml>

class MyPageController: public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MyPageController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadHistoryInfo();

signals:
    void loadHistorySuccessEvent();
    void loadHistoryErrorEvent(const QString& message);

public:
    MyPageController() = default;
    static MyPageController* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // MYPAGECONTROLLER_H