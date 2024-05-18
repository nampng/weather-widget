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
        }

        Image {
            Layout.alignment: Qt.AlignCenter
            height: 64
            width: 64
            fillMode: Image.Stretch
            source: Weather.icon
        }

        Label {
            Layout.alignment: Qt.AlignCenter
            text: Weather.city
            font.pixelSize: 22
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
