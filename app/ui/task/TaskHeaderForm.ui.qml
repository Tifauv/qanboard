import QtQuick 2.6
import "../tools"

Item {
	id: taskHeader
	clip: true

	property alias taskIdLbl: taskIdLbl
	property alias titleLbl: titleLbl

	implicitWidth: taskIdLbl.implicitWidth + titleLbl.anchors.leftMargin + titleLbl.implicitWidth
	implicitHeight: Math.max(taskIdLbl.implicitHeight, titleLbl.implicitHeight)

	Label {
		id: taskIdLbl
		text: "#1"
		anchors {
			verticalCenter: parent.verticalCenter
			left: parent.left
		}
		state: "secondary"
	}

	Label {
		id: titleLbl
		text: "Title"
		elide: Text.ElideRight
		anchors {
			verticalCenter: parent.verticalCenter
			left: taskIdLbl.right
			leftMargin: 4
			right: parent.right
		}
		state: "secondary"
		font.bold: true
	}
}




/*##^## Designer {
	D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
