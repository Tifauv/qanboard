import QtQuick 2.9
import QtQuick.Layouts 1.3
import "../tools"

Item {
    id: taskFooter

    property alias dueDateLbl: dueDateLbl
    property alias targetLbl: targetLbl

    implicitHeight: tagsLayout.implicitHeight

    Column {
        id: tagsLayout
        clip: true
        anchors.fill: parent

        Label {
            id: dueDateLbl
            state: "secondary"
            text: qsTr("Due date: 12/05/2015")
        }
        Label {
            id: targetLbl
            state: "secondary"
            text: qsTr("Servers: Target")
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
