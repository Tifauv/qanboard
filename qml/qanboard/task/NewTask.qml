import QtQuick 1.1
import "../tools"

Rectangle {
	id: task
	width: 240
	height: 150
	color: "#ffffff"
	clip: true

	property alias taskId: header.taskId
	property string description: "Description"
	property int margin: 5
	property int spacing: 6

	signal addTask(int taskId, string description)
	signal cancel()

	TaskHeader {
		id: header
		height: 14
		anchors.top: parent.top
		anchors.topMargin: margin
		anchors.left: parent.left
		anchors.leftMargin: margin
		anchors.right: parent.right
		anchors.rightMargin: margin
		assignee: ""
	}

	TextEdit {
		id: descriptionTxt
		text: qsTr(description)
		wrapMode: Text.WordWrap
		font.pointSize: 9
		anchors.top: header.bottom
		anchors.topMargin: spacing
		anchors.left: parent.left
		anchors.leftMargin: margin
		anchors.right: parent.right
		anchors.rightMargin: margin
		anchors.bottom: actionLayout.top
		color: Qt.rgba(0, 0, 0, 0.87)
	}

	Row {
		id: actionLayout
		height: 32
		layoutDirection: Qt.RightToLeft
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		spacing: 5

		TextButton {
			id: createBtn
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			label: qsTr("Create")

			onClicked: addTask(header.taskId, descriptionTxt.text)
		}

		TextButton {
			id: cancelBtn
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			label: qsTr("Cancel")

			onClicked: cancel()
		}
	}
}
