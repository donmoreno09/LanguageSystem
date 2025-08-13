#include "LanguageEnum.h"

namespace Language {

QString toString(Code language)
{
    switch (language) {
    case Code::English:
        return "en";
    case Code::Spanish:
        return "es";
    case Code::French:
        return "fr";
    }
    return "en"; // Default fallback
}

Code fromString(const QString &languageCode)
{
    if (languageCode == "en") return Code::English;
    if (languageCode == "es") return Code::Spanish;
    if (languageCode == "fr") return Code::French;
    
    return Code::English; // Default fallback
}

QStringList getAllCodes()
{
    return QStringList() << "en" << "es" << "fr";
}

bool isSupported(const QString &languageCode)
{
    return languageCode == "en" || languageCode == "es" || languageCode == "fr";
}

}