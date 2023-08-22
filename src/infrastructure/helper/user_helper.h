#ifndef USERHELPER_H
#define USERHELPER_H

#include <QtQml>
#include <QStringList>
#include <QString>

struct User;

class UserHelper : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(UserHelper)
    QML_SINGLETON

    Q_PROPERTY(QString id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString avatar MEMBER m_avatar NOTIFY avatarChanged)
    Q_PROPERTY(QStringList department MEMBER m_department NOTIFY departmentChanged)
    Q_PROPERTY(QString description MEMBER m_description NOTIFY descriptionChanged)
    Q_PROPERTY(QString email MEMBER m_email NOTIFY emailChanged)
    Q_PROPERTY(QStringList link MEMBER m_link NOTIFY linkChanged)

public:
    static UserHelper *getInstance();

    static UserHelper *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    void updateUser(const User &user);

    /*--------------------------------------/
    /                                       /
    /                                       /
    /    Waiting for the completed part     /
    /  (Perhaps a get function is missing)  /
    /                                       /
    /                                       /
    /--------------------------------------*/
private:
    UserHelper() = default;

    QString m_id;
    QString m_name;
    QString m_avatar;
    QStringList m_department;
    QString m_description;
    QString m_email;
    QStringList m_link;

signals:
    void idChanged();
    void nameChanged();
    void avatarChanged();
    void departmentChanged();
    void descriptionChanged();
    void emailChanged();
    void linkChanged();
};

#endif // USERHELPER_H