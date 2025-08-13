import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 600
    height: 400
    visible: true
    title: qsTr("Simple Language System Demo")

    // Automatic retranslation properties - Production Version
    property string welcomeTitle: qsTr("Welcome to Language System")
    property string greetingMessage: qsTr("Hello! This is a simple language system demonstration.")
    property string descriptionMessage: qsTr("Click any language button above to see the interface change language. This demonstrates Qt's internationalization capabilities.")
    property string currentLanguageLabel: qsTr("Current language: %1")
    property string englishButton: qsTr("English")
    property string spanishButton: qsTr("Español")
    property string frenchButton: qsTr("Français")

    // Auto-retranslate when language changes - Production Version
    function retranslateUi() {
        welcomeTitle = qsTr("Welcome to Language System")
        greetingMessage = qsTr("Hello! This is a simple language system demonstration.")
        descriptionMessage = qsTr("Click any language button above to see the interface change language. This demonstrates Qt's internationalization capabilities.")
        currentLanguageLabel = qsTr("Current language: %1")
        englishButton = qsTr("English")
        spanishButton = qsTr("Español")
        frenchButton = qsTr("Français")
    }

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 30

        // Title
        Text {
            id: titleText
            width: parent.width
            text: window.welcomeTitle
            font.pixelSize: 24
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        // Language buttons
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Button {
                id: english
                text: window.englishButton
                onClicked: {
                    console.log("Clicked English")
                    LanguageController.currentLanguage = "en"
                }
            }

            Button {
                id: spanish
                text: window.spanishButton
                onClicked: {
                    console.log("Clicked Spanish")
                    LanguageController.currentLanguage = "es"
                }
            }

            Button {
                id: french
                text: window.frenchButton
                onClicked: {
                    console.log("Clicked French")
                    LanguageController.currentLanguage = "fr"
                }
            }
        }

        // Content
        Column {
            width: parent.width
            spacing: 20

            Text {
                id: greetingText
                width: parent.width
                text: window.greetingMessage
                font.pixelSize: 16
                wrapMode: Text.WordWrap
            }

            Text {
                id: descriptionText
                width: parent.width
                text: window.descriptionMessage
                font.pixelSize: 14
                wrapMode: Text.WordWrap
            }
        }

        // Current language display
        Text {
            id: currentLanguageText
            anchors.horizontalCenter: parent.horizontalCenter
            text: window.currentLanguageLabel.arg(LanguageController.currentLanguage.toUpperCase())
            font.pixelSize: 12
        }
    }

    // Automatic retranslation on language change - Production Version
    Connections {
        target: LanguageController
        function onLanguageChanged() {
            console.log("Language changed signal received - auto-retranslating")
            window.retranslateUi()
        }

        function onLanguageLoadFailed(language, reason) {
            console.error("Language load failed:", language, "-", reason)
            // In production, you might show a popup or status message to user
        }
    }
}
