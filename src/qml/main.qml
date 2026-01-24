import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.plasma.plasmoid
import org.kde.plasma.core as Core
import org.kde.plasma.components as PC
import org.kde.kirigami as Kirigami


PlasmoidItem {
    id: root

    Layout.preferredHeight: 500
    Layout.preferredWidth: 400
    Layout.minimumHeight: 400
    Layout.minimumWidth: 300

    width: 400
    height: 500

    fullRepresentation: Rectangle {
        color: Kirigami.Theme.backgroundColor
        // border.color: Kirigami.Theme.textColor
        border.width: 0

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 8

            PC.TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "Search..."

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
                clip: true

                ListView {
                    id: appList
                    model: SimpleMenu.model

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
                                    Layout.fillWidth: true
                                    text: model.name
                                    font.weight: Font.Medium
                                    elide: Text.ElideRight
                                }

                                PC.Label {
                                    Layout.fillWidth: true
                                    text: model.description
                                    font.pointSize: Kirigami.Theme.smallFont.pointSize
                                    color: Kirigami.Theme.disabledTextColor
                                    elide: Text.ElideRight
                                    visible: text !== ""
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
        }
    }

    compactRepresentation: Item {
        Layout.preferredWidth: Kirigami.Units.iconSizes.medium
        Layout.preferredHeight: Kirigami.Units.iconSizes.medium

        Kirigami.Icon {
            anchors.fill: parent
            source: "applications-all"

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

