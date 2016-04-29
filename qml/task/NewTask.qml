import QtQuick 2.4
import "../tools"

Rectangle {
	id: task
	width: fullWidth
	height: fullHeight
	color: "#ffffff"
	clip: true

	property string description: "Description"
	property int margin: 5
	property int spacing: 6
	property int fullWidth: 240
	property int fullHeight: 150

	signal clicked()
	signal addTask(int taskId, string description)
	signal cancel()

	Label {
		id: header
		height: 14
		anchors.top: parent.top
		anchors.topMargin: margin
		anchors.left: parent.left
		anchors.leftMargin: margin
		anchors.right: parent.right
		anchors.rightMargin: margin
		text: qsTr("Enter task description")
		state: "secondary"
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

	MouseArea {
		id: button
		anchors.fill: parent
		opacity: 0

		onClicked: task.clicked()

		Text {
			color: "white"
			text: "+"
			font.pointSize: parent.height * 0.75
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}

	states: [
		State {
			name: "button"
			PropertyChanges {
				target: task
				height: 32
				width: 32
				color: "#ffab00"
				radius: height/2
			}
			PropertyChanges {
				target: actionLayout
				opacity: 0
			}
			PropertyChanges {
				target: descriptionTxt
				opacity: 0
			}
			PropertyChanges {
				target: header
				opacity: 0
			}
			PropertyChanges {
				target: button
				opacity: 1
			}
		}
	]

	transitions: [
		Transition {
			PropertyAnimation {
				properties: "width,height,opacity,radius"
				duration: 150
				easing.type: Easing.OutQuad
			}
			ColorAnimation {
				duration: 150
			}
		}
	]
}
