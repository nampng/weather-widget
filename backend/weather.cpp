#include "weather.h"
#include "key.h"

#include <iostream>
#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

static Weather *sInstance = nullptr;

Weather::Weather(QObject *parent): QObject{parent}
{
    mManager = new QNetworkAccessManager(this);
    connect(mManager, &QNetworkAccessManager::finished, this, &Weather::replyFinished);
    QFile file("backend/weather_conditions.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Could not open weather_conditions.json" << std::endl;
    }
    else
    {
        QByteArray json = file.readAll();
        file.close();

        QJsonDocument weatherConditions = QJsonDocument::fromJson(json);
        for (QJsonValue val : weatherConditions.array())
        {
            QJsonObject obj = val.toObject();
            Condition cond{obj["icon"].toInt(), obj["day"].toString(), obj["night"].toString()};
            mWeatherConditions.insert(obj["code"].toInt(), cond);
        }
    }
    queryWeather();
}

Weather::~Weather()
{
    delete mManager;
}

Weather* Weather::getInstance()
{
    if (sInstance == nullptr)
    {
        sInstance = new Weather();
    }

    return sInstance;
}

void Weather::switchCity()
{
    mCurrCity += 1;
    if (mCurrCity >= mCities.size())
    {
        mCurrCity = 0;
    }
    queryWeather();
}

void Weather::queryWeather()
{
    std::cout << "Querying weather" << std::endl;
    QString url = "http://api.weatherapi.com/v1/current.json?key="+QString::fromStdString(API_KEY)+"&q="+mCities[mCurrCity]+"&aqi=no";
    mManager->get(QNetworkRequest(QUrl(url)));
}

void Weather::replyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    qDebug() << doc;

    Condition cond = mWeatherConditions[doc["current"]["condition"]["code"].toInt()];
    mCurrentWeather = cond.dayWeather;
    mCurrentIcon = QString::fromStdString("icons/") + (doc["current"]["is_day"].toInt() == 1 ? "day" : "night") + '/' + QString::number(cond.icon) + ".png";
    emit conditionChanged();
}

QString Weather::city()
{
    return mCities[mCurrCity];
}

QString Weather::weather()
{
    return mCurrentWeather;
}

QString Weather::icon()
{
    return mCurrentIcon;
}
