import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.plasma.plasmoid
import org.kde.plasma.core as Core
import org.kde.plasma.components as PC
import org.kde.plasma.extras as PE
import org.kde.kirigami as Kirigami


PlasmoidItem {
    id: root

    width: 300
    height: 500

    Layout.minimumWidth: 300
    Layout.minimumHeight: 500

    Layout.maximumWidth: 300

    fullRepresentation: Rectangle {
        color: Kirigami.Theme.backgroundColor
        border.width: 0
        width: 300
        height: 500

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 4
            spacing: 4

            PE.ActionTextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "Search..."

                rightActions: [
                    Action {
                        icon.name: "edit-clear"
                        enabled: searchField.text.length > 0
                        onTriggered: {
                            searchField.text = ""
                            searchField.forceActiveFocus()
                        }
                    }
                ]

                onTextChanged: {
                    console.debug("New filter:", text);
                    SimpleMenu.filter = text;
                    focusTimer.restart()
                }

                Component.onCompleted: {
                    Qt.callLater(function() {
                        // console.debug("Setting focus")
                        searchField.forceActiveFocus()
                    })
                }

                Timer {
                    id: focusTimer
                    interval: 750
                    onTriggered: {
                        // console.debug("Triggering")
                        if (appList.count > 0 && searchField.text !== "") {
                            appList.currentIndex = 0
                            console.debug("Focusing current item:", appList.currentItem)
                            //appList.currentItem.forceActiveFocus()
                        }
                    }
                }

                Keys.onReturnPressed: {
                    if (appList.currentIndex >= 0) {
                        SimpleMenu.model.launchApp(appList.currentIndex)
                        root.expanded = false
                    }
                }

                Keys.onEnterPressed: {
                    if (appList.currentIndex >= 0) {
                        SimpleMenu.model.launchApp(appList.currentIndex)
                        root.expanded = false
                    }
                }

                Keys.onUpPressed: {
                    if (appList.currentIndex > 0) {
                        appList.currentIndex--;
                    }
                }

                Keys.onDownPressed: {
                    if (appList.currentIndex < appList.count-1) {
                        appList.currentIndex++;
                    }
                }
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ListView {
                    id: appList
                    model: SimpleMenu.model
                    clip: true

                    highlightMoveDuration: 0
                    highlightResizeDuration: 0

                    delegate: ItemDelegate {
                        width: appList.width
                        height: 44
                        activeFocusOnTab: true
                        focus: true
                        leftPadding: 5
                        rightPadding: 0
                        topPadding: 0
                        bottomPadding: 0

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 4
                            spacing: 8

                            Kirigami.Icon {
                                Layout.preferredWidth: 32
                                Layout.preferredHeight: 32
                                source: model.icon
                                fallback: "application-x-executable"
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 0

                                PC.Label {
                                    id: nameLabel
                                    Layout.fillWidth: true
                                    text: model.name
                                    font.weight: Font.Normal
                                    elide: Text.ElideRight
                                }

                                PC.ToolTip {
                                    text: model.description
                                }
                            }
                        }

                        onClicked: {
                            SimpleMenu.model.launchApp(index)
                            root.expanded = false
                        }

                        background: Rectangle {
                            color: {
                                if (appList.currentIndex === index) {
                                    return Kirigami.Theme.highlightColor
                                } else if (hovered) {
                                    return Kirigami.Theme.hoverColor
                                } else {
                                    return "transparent"
                                }
                            }
                            radius: 4
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 40

                PC.Button {
                    Layout.fillWidth: true
                    text: "Logout"
                    icon.name: "system-log-out"

                    onClicked: {
                        SimpleMenu.logout()
                        root.expanded = false
                    }
                }

                PC.Button {
                    Layout.fillWidth: true
                    text: "Power Off"
                    icon.name: "system-shutdown"

                    onClicked: {
                        SimpleMenu.poweroff()
                        root.expanded = false
                    }
                }
            }
        }
    }

    compactRepresentation: Item {
        Layout.preferredWidth: Kirigami.Units.iconSizes.medium
        Layout.preferredHeight: Kirigami.Units.iconSizes.medium

        Kirigami.Icon {
            anchors.fill: parent
            source: "view-grid-symbolic"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // console.debug("Expanding")
                    root.expanded = !root.expanded
                }
            }
        }
    }
}

