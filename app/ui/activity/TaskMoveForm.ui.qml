import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4 as Controls
import org.kde.kirigami 2.4 as Kirigami
import "../task"

Item {
    id: root
    width: 300
    height: 140

    property alias originQueueRect: originQueueRect
    property alias destinationQueueRect: destinationQueueRect
    property alias taskDescriptionLbl: taskDescriptionLbl
    property alias taskHeader: taskHeader
    property alias destinationQueueLbl: destinationQueueLbl
    property alias originQueueLbl: originQueueLbl
    property alias timeLbl: timeLbl

    Kirigami.Theme.colorSet: Kirigami.Theme.Window

    ColumnLayout {
        id: mainLayout

        spacing: Kirigami.Units.smallSpacing

        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing

        Controls.Label {
            id: timeLbl

            text: qsTr("11h25")
            font.pointSize: 10
            font.bold: true
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter

            Layout.fillWidth: true
        }

        Rectangle {
            id: taskRect

            Kirigami.Theme.colorSet: Kirigami.Theme.View

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                id: taskLayout

                anchors.fill: parent
                anchors.margins: Kirigami.Units.smallSpacing

                spacing: Kirigami.Units.smallSpacing

                RowLayout {
                    id: headerLayout

                    height: originQueueRect.implicitHeight
                    spacing: Kirigami.Units.smallSpacing
                    Layout.fillWidth: true

                    TaskHeader {
                        id: taskHeader

                        Layout.fillWidth: true
                    }

                    Rectangle {
                        id: originQueueRect

                        radius: height / 2
                        implicitHeight: originQueueLbl.implicitHeight + 2
                                        * Kirigami.Units.smallSpacing
                        implicitWidth: originQueueLbl.implicitWidth + 2 * radius

                        border.width: 2
                        border.color: "#4d4d4d"

                        Controls.Label {
                            id: originQueueLbl
                            text: qsTr("Backlog")
                            color: parent.border.color
                            font.pointSize: 8
                            elide: Text.ElideRight
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Controls.Label {
                        id: arrowLbl

                        text: qsTr("➡")
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Rectangle {
                        id: destinationQueueRect

                        radius: height / 2
                        implicitHeight: destinationQueueLbl.implicitHeight + 2
                                        * Kirigami.Units.smallSpacing
                        implicitWidth: destinationQueueLbl.implicitWidth + 2 * radius

                        border.width: 2
                        border.color: "#1d99f3"

                        Controls.Label {
                            id: destinationQueueLbl
                            text: qsTr("Selected")
                            color: parent.border.color
                            font.pointSize: 8
                            elide: Text.ElideRight
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Controls.Label {
                    id: taskDescriptionLbl
                    text: qsTr("Description")
                    elide: Text.ElideRight

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }

            layer.enabled: true
            layer.effect: DropShadow {
                cached: true
                verticalOffset: 1
                radius: 8.0
                samples: 16
                color: Kirigami.Theme.disabledTextColor
            }
        }
    }
}
