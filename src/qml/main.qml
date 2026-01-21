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

    fullRepresentation: Rectangle {
        color: Kirigami.Theme.backgroundColor
        border.color: Kirigami.Theme.textColor
        border.width: 1

        ColumnLayout {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 8

                PC.TextField {
                    id: searchField
                    Layout.fillWidth: true
                    placeholderText: "Search..."

                    onTextChanged: {
                        // SimpleMenu.setFilter(text)
                        console.debug("New filter:", text);
                    }

                    Component.onCompleted: forceActiveFocus()
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: appList
                        model: SimpleMenu.Model

                        delegate: ItemDelegate {
                            width: appList.width
                            height: 40

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
                        }
                    }
                }
            }
    }

    // took it from kickoff from official sources
    compactRepresentation: Kirigami.Icon {
        source: "applications-all"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.debug("Expanding")
                root.expanded = !root.expanded
            }
        }
    }
}

