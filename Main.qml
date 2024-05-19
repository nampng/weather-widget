import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Backend.Weather 1.0

Window {
    width: 480
    height: 800
    visible: true
    title: qsTr("Weather")

    color: Weather.backgroundColor

    ColumnLayout
    {
        anchors.fill: parent

        Label {
            Layout.alignment: Qt.AlignCenter
            text: Weather.weather
            font.pixelSize: 22
            color: (Weather.isDay ? "black" : "white")
        }

        Label {
            Layout.alignment: Qt.AlignCenter
            text: Weather.fahr.toFixed(0) + "°F"
            font.pixelSize: 22
            color: (Weather.isDay ? "black" : "white")
        }

        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 128
            Layout.preferredWidth: 128
            fillMode: Image.PreserveAspectFit
            source: Weather.icon
        }

        Label {
            Layout.alignment: Qt.AlignCenter
            text: Weather.city
            font.pixelSize: 22
            color: (Weather.isDay ? "black" : "white")
        }

        Button {
            Layout.alignment: Qt.AlignCenter
            id: switchButton
            height: 100
            width: 200
            text: "Switch"
            font.pixelSize: 22
            onClicked: {
                Weather.switchCity()
            }
        }
    }
}
