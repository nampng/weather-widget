#include "weather.h"

#include <iostream>
#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

QString API_KEY = "none";

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
    QFile apiFile("backend/api_key.txt");
    if (!apiFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      std::cerr << "Could not open api_key.txt" << std::endl;
    }
    else
    {
      API_KEY = QString::fromStdString(apiFile.readAll().toStdString());
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
    if (API_KEY == "none")
    {
      std::cerr << "No key..." << std::endl;
      return;
    }
    std::cout << "Querying weather" << std::endl;
    QString url = "http://api.weatherapi.com/v1/current.json?key="+API_KEY+"&q="+mCities[mCurrCity]+"&aqi=no";
    mManager->get(QNetworkRequest(QUrl(url)));
}

void Weather::replyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    qDebug() << doc;

    if (doc["error"].isObject())
    {
        std::cerr << "Error!" << std::endl;
        mCurrentWeather = "Error! Check your API key!";
        mBackgroundColor = "white";
        return;
    }

    int code = doc["current"]["condition"]["code"].toInt();

    // Retrieve condition
    Condition cond = mWeatherConditions[code];

    // Determine if it's day or night
    mIsDay = doc["current"]["is_day"].toInt() == 1;

    mCurrentTempF = doc["current"]["temp_f"].toDouble();

    // Set weather
    mCurrentWeather = (mIsDay ? cond.dayWeather : cond.nightWeather);

    // Set icon
    mCurrentIcon = QString::fromStdString("icons/") + (mIsDay ? "day" : "night") + '/' + QString::number(cond.icon) + ".png";

    // Set background color
    mBackgroundColor = (mIsDay ? mBackgrounds[code].first : mBackgrounds[code].second);

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

QString Weather::backgroundColor()
{
    return mBackgroundColor;
}

bool Weather::isDay()
{
    return mIsDay;
}

float Weather::fahr()
{
    return mCurrentTempF;
}
