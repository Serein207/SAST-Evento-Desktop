import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtCore
import FluentUI

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_theming

    Settings {
        id: settings
        property var darkMode
        property string nativeTextSet
        property string enableAnimationSet
        property int colorIndex
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 270
        paddings: 10
        ColumnLayout {
            spacing: 0
            anchors {
                left: parent.left
            }
            RowLayout {
                Layout.topMargin: 10
                Repeater {
                    id: rep
                    model: [FluColors.Yellow, FluColors.Orange, FluColors.Red, FluColors.Magenta, FluColors.Purple, FluColors.Blue, FluColors.Teal, FluColors.Green]
                    delegate: FluRectangle {
                        width: 42
                        height: 42
                        radius: [4, 4, 4, 4]
                        color: mouse_item.containsMouse ? Qt.lighter(
                                                              modelData.normal,
                                                              1.1) : modelData.normal
                        FluIcon {
                            anchors.centerIn: parent
                            iconSource: FluentIcons.AcceptMedium
                            iconSize: 15
                            visible: modelData === FluTheme.primaryColor
                            color: FluTheme.dark ? Qt.rgba(0, 0, 0,
                                                           1) : Qt.rgba(1, 1,
                                                                        1, 1)
                        }
                        MouseArea {
                            id: mouse_item
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                FluTheme.primaryColor = modelData
                                settings.colorIndex = model.index
                            }
                        }
                    }
                }
            }
            FluText {
                text: "夜间模式"
                Layout.topMargin: 20
            }
            FluToggleSwitch {
                Layout.topMargin: 5
                checked: FluTheme.dark
                onClicked: {
                    if (FluTheme.dark) {
                        FluTheme.darkMode = FluThemeType.Light
                    } else {
                        FluTheme.darkMode = FluThemeType.Dark
                    }
                }
            }
            FluText {
                text: "native文本渲染"
                Layout.topMargin: 20
            }
            FluToggleSwitch {
                Layout.topMargin: 5

                //checked: FluTheme.nativeText
                onClicked: {
                    FluTheme.nativeText = !FluTheme.nativeText
                    settings.nativeTextSet = checked
                    //console.log("nativeText ", FluTheme.nativeText)
                }

                Component.onCompleted: {
                    //console.log("nativeText ", FluTheme.nativeText)
                    checked = settings.value("nativeTextSet", false)
                }
            }
            FluText {
                text: "开启动画效果"
                Layout.topMargin: 20
            }
            FluToggleSwitch {
                Layout.topMargin: 5

                //checked: FluTheme.enableAnimation
                onClicked: {
                    FluTheme.enableAnimation = !FluTheme.enableAnimation
                    settings.enableAnimationSet = checked
                    //console.log("animation ", FluTheme.enableAnimation)
                }

                Component.onCompleted: {
                    //console.log("animation ", FluTheme.enableAnimation)
                    checked = settings.value("enableAnimationSet", true)
                }
            }
        }
    }
}