import QtQuick 2.9
import "../tools"

Item {
	id: taskFooter

	property alias dueDateLbl: dueDateLbl
	property alias targetLbl: targetLbl

	implicitHeight: Math.max(targetLbl.implicitHeight,
							 dueDateLbl.implicitHeight)

	Label {
		id: targetLbl
		state: "secondary"
		text: "Target"
		elide: Text.ElideRight

		anchors {
			left: parent.left
			right: dueDateLbl.left
			rightMargin: 4
			bottom: parent.bottom
		}
	}

	Label {
		id: dueDateLbl
		state: "secondary"
		text: "12/05/2015"
		horizontalAlignment: Text.AlignRight
		clip: true

		anchors {
			right: parent.right
			bottom: parent.bottom
		}
	}
}




/*##^## Designer {
	D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
