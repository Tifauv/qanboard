import QtQuick 2.6
import "../tools"

Item {
	id: taskFooter

	property alias clientTag: clientLbl
	property alias activityTag: activityLbl
	property alias targetTag: targetLbl

	implicitHeight: tagsLayout.implicitHeight

	Flow {
		id: tagsLayout
		clip: true
		spacing: 4
		anchors.fill: parent

		Label {
			id: clientLbl
			state: "secondary"
			text: "Client"
		}

		Label {
			id: activityLbl
			state: "secondary"
			text: "Activity"
		}

		Label {
			id: targetLbl
			state: "secondary"
			text: "Target"
		}
	}
}

/*##^## Designer {
	D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
