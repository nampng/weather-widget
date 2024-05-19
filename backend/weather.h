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
    Q_PROPERTY(bool isDay READ isDay NOTIFY conditionChanged)
    Q_PROPERTY(float fahr READ fahr NOTIFY conditionChanged)

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
    bool isDay();
    float fahr();

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

    bool mIsDay = false;
    int mCurrCity = 0;
    float mCurrentTempF = 0.0;
    QString mCurrentWeather = "None";
    QString mCurrentIcon = "";
    QString mBackgroundColor = "skyblue";

    QNetworkAccessManager *mManager;

    QVector<QString> mCities = {"Dallas", "London", "Tokyo", "Moscow", "Sydney"};
    QMap<int, Condition> mWeatherConditions;
    QMap<int, QPair<QString, QString>> mBackgrounds = {
        {1000, {"#FFD700", "#191970"}},
        {1003, {"#B0C4DE", "#2F4F4F"}},
        {1006, {"#A9A9A9", "#696969"}},
        {1009, {"#696969", "#4B4B4B"}},
        {1030, {"#E0FFFF", "#708090"}},
        {1063, {"#778899", "#2E2E2E"}},
        {1066, {"#F0FFFF", "#A9A9A9"}},
        {1069, {"#87CEFA", "#778899"}},
        {1072, {"#B0E0E6", "#6A5ACD"}},
        {1087, {"#8B0000", "#8B0000"}},
        {1114, {"#F5F5F5", "#696969"}},
        {1117, {"#DCDCDC", "#2F4F4F"}},
        {1135, {"#D3D3D3", "#778899"}},
        {1147, {"#D8BFD8", "#8A2BE2"}},
        {1150, {"#AFEEEE", "#2E8B57"}},
        {1153, {"#ADD8E6", "#4682B4"}},
        {1168, {"#B0E0E6", "#6495ED"}},
        {1171, {"#4682B4", "#4169E1"}},
        {1180, {"#87CEEB", "#00BFFF"}},
        {1183, {"#00CED1", "#1E90FF"}},
        {1186, {"#4682B4", "#4682B4"}},
        {1189, {"#1E90FF", "#0000CD"}},
        {1192, {"#4169E1", "#191970"}},
        {1195, {"#0000CD", "#000080"}},
        {1198, {"#5F9EA0", "#5F9EA0"}},
        {1201, {"#4682B4", "#4682B4"}},
        {1204, {"#87CEFA", "#87CEFA"}},
        {1207, {"#4682B4", "#4682B4"}},
        {1210, {"#F0FFFF", "#A9A9A9"}},
        {1213, {"#B0E0E6", "#B0C4DE"}},
        {1216, {"#AFEEEE", "#778899"}},
        {1219, {"#ADD8E6", "#B0E0E6"}},
        {1222, {"#E0FFFF", "#E0FFFF"}},
        {1225, {"#FFFFFF", "#D3D3D3"}},
        {1237, {"#87CEEB", "#4682B4"}},
        {1240, {"#00CED1", "#00CED1"}},
        {1243, {"#1E90FF", "#1E90FF"}},
        {1246, {"#00008B", "#00008B"}},
        {1249, {"#87CEFA", "#87CEFA"}},
        {1252, {"#4682B4", "#4682B4"}},
        {1255, {"#B0E0E6", "#B0E0E6"}},
        {1258, {"#ADD8E6", "#ADD8E6"}},
        {1261, {"#87CEEB", "#4682B4"}},
        {1264, {"#4682B4", "#4169E1"}},
        {1273, {"#8B0000", "#4B0082"}},
        {1276, {"#4B0082", "#2F4F4F"}},
        {1279, {"#8B0000", "#8B0000"}},
        {1282, {"#4B0082", "#4B0082"}},
    };
};

#endif // WEATHER_H
