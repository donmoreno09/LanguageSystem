#pragma once

#include <QObject>
#include <QString>
#include <QTranslator>
#include <QGuiApplication>

class LanguageController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentLanguage READ currentLanguage WRITE setCurrentLanguage NOTIFY currentLanguageChanged)
    Q_PROPERTY(QStringList availableLanguages READ availableLanguages CONSTANT)

public:
    explicit LanguageController(QObject *parent = nullptr);
    ~LanguageController();

    QString currentLanguage() const;
    void setCurrentLanguage(const QString &language);
    QStringList availableLanguages() const;

    static LanguageController *instance();

signals:
    void currentLanguageChanged();
    void languageChanged();
    void languageLoadFailed(const QString &language, const QString &reason);

private:
    QString initializeLanguage();
    void loadLanguage(const QString &language);
    bool tryLoadLanguage(const QString &language);

    QString m_currentLanguage;
    QTranslator *m_translator;
    QStringList m_availableLanguages;
    static LanguageController *s_instance;
};
