import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import Vindinium 1.0

Window {
    property int mapSize: uiHelper.mapSize
    property bool loadedGrid: false

    id: window
    visible: true
    width: 1200
    height: 800

    Rectangle {
        id: leftPanelBG
        color: "#e8e8e8"
        anchors {
            top: parent.top
            left: parent.left
            right: mainLoader.left
            bottom: parent.bottom
        }
    }

    Text {
        id: gameStatText
        anchors.horizontalCenter: leftPanelBG.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        anchors.top: leftPanelBG.top
        anchors.topMargin: 20
        text: uiHelper.gameStats
    }

    Connections {
        target: uiHelper
        function onMapUpdate() {
            if (!loadedGrid) {
                loadedGrid = true
                mainLoader.source = "qrc:/ui/UIGrid.qml"
            }
        }
    }

    Loader {
        anchors {
            top: parent.top
            right: parent.right
        }

        id: mainLoader
        width: 800
        height: 800
    }
}
