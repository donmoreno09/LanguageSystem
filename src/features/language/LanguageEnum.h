#pragma once

#include <QString>
#include <QStringList>

namespace Language {
    enum class Code {
        English,
        Spanish,
        French
    };

    QString toString(Code language);
    Code fromString(const QString &languageCode);
    QStringList getAllCodes();
    bool isSupported(const QString &languageCode);
}