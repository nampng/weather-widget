#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QQuickItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMap>
#include <QImage>
#include <QVector>

class Weather : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString city READ city NOTIFY conditionChanged)
    Q_PROPERTY(QString weather READ weather NOTIFY conditionChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY conditionChanged)
    Q_PROPERTY(QString backgroundColor READ backgroundColor NOTIFY conditionChanged)

    struct Condition {
        int icon;
        QString dayWeather;
        QString nightWeather;
    };

public:
    static Weather* getInstance();
    QString city();
    QString weather();
    QString icon();
    QString backgroundColor();

signals:
    void conditionChanged();
    void cityChanged();

public slots:
    void switchCity();
    void queryWeather();
    void replyFinished(QNetworkReply *reply);

private:
    Weather(QObject *parent = nullptr);
    ~Weather();

    QVector<QString> mCities = {"Dallas", "London", "Tokyo"};

    int mCurrCity = 0;
    QString mCurrentWeather = "";
    QString mCurrentIcon = "";
    bool mIsDay = false;

    QNetworkAccessManager *mManager;

    QMap<int, Condition> mWeatherConditions;

    QMap<QString, QString> mDayBackgrounds = {
        {"Sunny", "skyblue"}
    };
    QMap<QString, QString> mNightBackgrounds= {
        {"Clear", "dimgray"}
    };
};

#endif // WEATHER_H
