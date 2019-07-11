import QtQuick 2.9
import QtQuick.Controls 2.4 as Controls
import org.kde.kirigami 2.4 as Kirigami

Item {
    implicitWidth: 300
    implicitHeight: 400

    property alias clientTxt: clientTxt
    property alias activityTxt: activityTxt
    property alias descriptionTxt: descriptionTxt
    property alias dueDateTxt: dueDateTxt
    property alias targetTxt: targetTxt

    Kirigami.FormLayout {
        clip: true
        anchors.fill: parent

        Controls.TextField {
            id: clientTxt
            placeholderText: qsTr("Client name")
            Kirigami.FormData.label: qsTr("Client")
			selectByMouse: true
            maximumLength: 24
            focus: true
        }
        Controls.TextField {
            id: activityTxt
            placeholderText: qsTr("Run or Project name")
            Kirigami.FormData.label: qsTr("Activity")
			selectByMouse: true
            maximumLength: 32
        }
        Controls.TextField {
            id: descriptionTxt
            placeholderText: qsTr("What is it about?")
            Kirigami.FormData.label: qsTr("* Description")
			selectByMouse: true
            maximumLength: 250
        }
        Kirigami.Separator {
            Kirigami.FormData.isSection: true
        }
        Controls.TextField {
            id: dueDateTxt
            placeholderText: qsTr("dd/mm/yyyy")
            // TODO find a way to accept the input mask or an empty string
            //inputMask: qsTr("00/00/0000;_")
            Kirigami.FormData.label: qsTr("Due date")
			selectByMouse: true
            maximumLength: 32
        }
        Controls.TextField {
            id: targetTxt
            placeholderText: qsTr("CI, Server names...")
            Kirigami.FormData.label: qsTr("Target")
			selectByMouse: true
            maximumLength: 32
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
