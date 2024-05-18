#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "weather.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Register types here
    Weather *lWeather = Weather::getInstance();
    qmlRegisterSingletonInstance("Backend.Weather", 1, 0, "Weather", lWeather);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    const QUrl url(QStringLiteral("weather-app/Main.qml"));
    engine.load(url);

    return app.exec();
}
