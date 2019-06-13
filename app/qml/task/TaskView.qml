import QtQuick 2.6
import "../tools"

Rectangle {
	id: task
	width: 180
	height: 111
	color: "#ffffff"

	property alias taskId: header.taskId
	property alias title: header.title
	property alias description: descriptionLbl.text
	property alias client: footer.client
	property alias activity: footer.activity
	property alias target: footer.target

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
		}

		Label {
			id: descriptionLbl
			text: "Description"
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
		}
	}
}
