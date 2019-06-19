import QtQuick 2.9
import QtQuick.Controls 2.2 as Controls
import org.kde.kirigami 2.4 as Kirigami

Controls.Dialog {
    id: dialog
    title: qsTr("New Task")

    property alias clientTxt: clientTxt
    property alias activityTxt: activityTxt
    property alias descriptionTxt: descriptionTxt
    property alias dueDateTxt: dueDateTxt
    property alias targetTxt: targetTxt

    implicitWidth: 300
    implicitHeight: 400

    standardButtons: Controls.Dialog.Save | Controls.Dialog.Cancel
    closePolicy: Controls.Dialog.CloseOnEscape | Controls.Dialog.CloseOnPressOutside

    Kirigami.FormLayout {
        clip: true
        anchors.fill: parent

        Controls.TextField {
            id: clientTxt
            placeholderText: qsTr("Client name")
            Kirigami.FormData.label: qsTr("Client")
            maximumLength: 24
        }
        Controls.TextField {
            id: activityTxt
            placeholderText: qsTr("Run or Project name")
            Kirigami.FormData.label: qsTr("Activity")
            maximumLength: 32
        }
        Controls.TextField {
            id: descriptionTxt
            placeholderText: qsTr("What is it about?")
            Kirigami.FormData.label: qsTr("Description")
            maximumLength: 250
        }
        Kirigami.Separator {
            Kirigami.FormData.isSection: true
        }
        Controls.TextField {
            id: dueDateTxt
            placeholderText: qsTr("dd/mm/yyyy")
            Kirigami.FormData.label: qsTr("Due date")
            focus: true
            maximumLength: 32
        }
        Controls.TextField {
            id: targetTxt
            placeholderText: qsTr("CI, Server names...")
            Kirigami.FormData.label: qsTr("Target")
            maximumLength: 32
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
