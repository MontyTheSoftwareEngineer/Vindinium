import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import Vindinium 1.0

Window {
    id: window
    visible: true
    width: 800
    height: 800

    property int mapSize: uiHelper.mapSize

    Column {
        id: colLayout
        anchors.fill: parent
        Repeater {
            id: colRepeater
            model: mapSize
            Row {
                id: rowLayout
                property var rowNum: modelData
                Repeater {
                    id: rowRepeater
                    model: mapSize
                    Rectangle {
                        id: cell
                        property int cellIndex: rowLayout.rowNum * mapSize + modelData
                        border.color: "black"
                        width: window.width / mapSize
                        height: window.height / mapSize
                        color: uiHelper.getCellColor(cellIndex)
                        MouseArea {
                            anchors.fill: parent
                            onClicked: uiHelper.setDest(cellIndex)
                        }
                        Text {
                            id: cellText
                            visible: true
                            clip: true
                            anchors.centerIn: parent
                            color: "black"
                            text: uiHelper.getCellText(cellIndex)
                        }

                        Connections {
                            target: uiHelper
                            function onMapUpdate() {
                                cellText.text = uiHelper.getCellText(cellIndex)
                                cell.color = uiHelper.getCellColor(cellIndex)
                            }
                        }
                    }
                }
            }
        }
    }
}
