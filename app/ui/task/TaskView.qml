import QtQuick 2.9
import "../tools"

Rectangle {
	id: task
	width: 180
	height: 111
	color: "#ffffff"

	property string taskId: "0"
	property string client: qsTr("Client")
	property string activity: qsTr("Activity")
	property string description: qsTr("Description")
	property string dueDate: "12/05/2015"
	property string target: qsTr("Target")

	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		TaskHeader {
			id: header
			anchors.top: parent.top
			anchors.topMargin: 4
			anchors.right: parent.right
			anchors.rightMargin: 8
			anchors.left: parent.left
			anchors.leftMargin: 8
			
			taskId: task.taskId
			title: qsTr("%1 %2").arg(task.client).arg(task.activity)
		}

		Label {
			id: descriptionLbl
			text: task.description
			clip: true
			elide: Text.ElideRight
			wrapMode: Text.WordWrap
			font.pointSize: 9
			anchors.top: header.bottom
			anchors.topMargin: 4
			anchors.right: parent.right
			anchors.rightMargin: 8
			anchors.left: parent.left
			anchors.leftMargin: 8
			anchors.bottom: footer.top
			anchors.bottomMargin: 4
		}

		TaskFooter {
			id: footer
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 4
			anchors.right: parent.right
			anchors.rightMargin: 8
			anchors.left: parent.left
			anchors.leftMargin: 8
			
			target: task.target
			dueDate: task.dueDate
		}
	}
}
