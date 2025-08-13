#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "features/language/LanguageController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Set application properties for translation context
    app.setApplicationName("LanguageSystem");
    app.setOrganizationName("QtExample");
    app.setApplicationVersion("1.0");

    // Create the language controller singleton
    LanguageController languageController;

    QQmlApplicationEngine engine;

    // Register the LanguageController instance as a context property
    engine.rootContext()->setContextProperty("LanguageController", &languageController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LanguageSystem", "Main");

    return app.exec();
}
