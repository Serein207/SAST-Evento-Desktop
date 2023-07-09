import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import FluentUI
import "qrc:///SAST_Evento/qml/component"

FluPage{
    launchMode: FluPage.SingleTop
    FluRemoteLoader{
        anchors.fill: parent
        source: "https://zhu-zichu.gitee.io/T_RemoteLoader.qml"
    }
}