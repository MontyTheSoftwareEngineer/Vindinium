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
    property bool loadedGrid: false

    //    Connections {
    //        target: uiHelper
    //        function onMapUpdate() {
    //            if (!loadedGrid) {
    //                mainLoader.source = "qrc:/ui/UIGrid.qml"
    //                loadedGrid = true
    //            }
    //        }
    //    }
    Loader {
        id: mainLoader
        width: 800
        height: 800
        source: "qrc:/ui/UIGrid.qml"
    }
}
