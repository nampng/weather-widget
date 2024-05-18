import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Backend.Weather 1.0

Window {
    width: 480
    height: 800
    visible: true
    title: qsTr("Weather")

    ColumnLayout
    {
        anchors.fill: parent

        Label {
            text: Weather.weather
        }

        Image {
            height: 64
            width: 64
            source: Weather.icon
        }

        Label {
            text: Weather.city
        }

        Button {
            id: switchButton
            height: 100
            width: 200
            text: "Switch"
            onClicked: {
                Weather.switchCity()
            }
        }
    }
}
