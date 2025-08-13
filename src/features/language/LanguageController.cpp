#include "LanguageController.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QEvent>
#include <QSettings>
#include <QLocale>
#include <QDebug>

LanguageController *LanguageController::s_instance = nullptr;

LanguageController::LanguageController(QObject *parent)
    : QObject(parent)
    , m_translator(new QTranslator(this))
{
    s_instance = this;

    // Initialize available languages
    m_availableLanguages << "en" << "es" << "fr";

    // Restore saved language or detect system language
    m_currentLanguage = initializeLanguage();

    // Load the determined language
    loadLanguage(m_currentLanguage);
}

LanguageController::~LanguageController()
{
    s_instance = nullptr;
}

LanguageController *LanguageController::instance()
{
    return s_instance;
}

QString LanguageController::currentLanguage() const
{
    return m_currentLanguage;
}

void LanguageController::setCurrentLanguage(const QString &language)
{
    // Validate input
    if (language.isEmpty()) {
        emit languageLoadFailed(language, "Empty language code provided");
        return;
    }

    if (!m_availableLanguages.contains(language)) {
        QString availableList = m_availableLanguages.join(", ");
        emit languageLoadFailed(language, QString("Unsupported language. Available languages: %1").arg(availableList));
        return;
    }

    if (m_currentLanguage == language) {
        qDebug() << "Language" << language << "is already current";
        return; // Already current language
    }

    // Attempt to load the language
    m_currentLanguage = language;

    // Save to persistent settings
    QSettings settings;
    settings.setValue("language", language);

    // Try to load the language
    loadLanguage(language);

    // Always emit signals since loadLanguage handles fallbacks
    emit currentLanguageChanged();
    emit languageChanged();
}

QStringList LanguageController::availableLanguages() const
{
    return m_availableLanguages;
}

QString LanguageController::initializeLanguage()
{
    // Try to restore saved language preference
    QSettings settings;
    QString savedLanguage = settings.value("language").toString();

    if (!savedLanguage.isEmpty() && m_availableLanguages.contains(savedLanguage)) {
        qDebug() << "Restored saved language:" << savedLanguage;
        return savedLanguage;
    }

    // Fallback to system locale detection
    QString systemLocale = QLocale::system().name().left(2); // "es", "fr", etc.

    if (m_availableLanguages.contains(systemLocale)) {
        qDebug() << "Using system language:" << systemLocale;
        return systemLocale;
    }

    // Final fallback to English
    qDebug() << "Using default language: en";
    return "en";
}

void LanguageController::loadLanguage(const QString &language)
{
    // Try requested language first
    if (tryLoadLanguage(language)) {
        return;
    }

    // Fallback to system language if different from requested
    QString systemLang = QLocale::system().name().left(2);
    if (language != systemLang && tryLoadLanguage(systemLang)) {
        qWarning() << "Requested language" << language << "failed, using system language" << systemLang;
        m_currentLanguage = systemLang; // Update current language to reflect reality
        emit currentLanguageChanged();
        return;
    }

    // Final fallback to English
    if (language != "en" && tryLoadLanguage("en")) {
        qWarning() << "Language" << language << "failed, falling back to English";
        m_currentLanguage = "en"; // Update current language to reflect reality
        emit currentLanguageChanged();
        return;
    }

    // Critical error - log and continue without translator
    qCritical() << "All language fallbacks failed for:" << language;
}

bool LanguageController::tryLoadLanguage(const QString &language)
{
    // Remove the old translator
    QCoreApplication::removeTranslator(m_translator);

    // Use clean resource path from Qt translation system
    QString resourcePath = QString(":/translations/app_%1.qm").arg(language);

    if (m_translator->load(resourcePath)) {
        QCoreApplication::installTranslator(m_translator);
        qDebug() << "Successfully loaded language:" << language << "from" << resourcePath;
        return true;
    }

    qDebug() << "Failed to load language file:" << resourcePath;
    return false;
}
