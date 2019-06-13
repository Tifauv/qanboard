import QtQuick 2.6
import "../tools"

Rectangle {
	id: task
	width: fullWidth
	height: fullHeight
	color: "#ffffff"
	clip: true

	property string title: "Title"
	property string description: "Description"
	property string client: "Client"
	property string activity: "Activity"
	property string target: "Target"
	property int margin: 5
	property int spacing: 6
	property int fullWidth: 320
	property int fullHeight: 240

	signal clicked()
	signal addTask(int taskId, string title, string description, string client, string activity, string target)
	signal cancel()

	Column {
		id: formLayout

		anchors {
			top: parent.top
			topMargin: 4
			left: parent.left
			leftMargin: 8
			right: parent.right
			rightMargin: 8
			bottom: actionLayout.top
			bottomMargin: 8
		}

		Label {
			id: titleLbl
			anchors {
				left: parent.left
				right: parent.right
			}
			text: qsTr("Title")
			verticalAlignment: Text.AlignBottom
			state: "secondary"
		}

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 14
			border.color: "#eeeeee"

			TextEdit {
				id: titleTxt
				text: title
				wrapMode: Text.WordWrap
				font.pointSize: 9
				anchors.fill: parent
				color: Qt.rgba(0, 0, 0, 0.87)
			}
		}

		Label {
			id: descriptionLbl
			anchors {
				left: parent.left
				right: parent.right
			}
			text: qsTr("What do you have to do?")
			verticalAlignment: Text.AlignBottom
			state: "secondary"
		}

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 5*14
			border.color: "#eeeeee"

			TextInput {
				id: descriptionTxt
				text: description
				wrapMode: Text.WordWrap
				font.pointSize: 9
				anchors.fill: parent
				color: Qt.rgba(0, 0, 0, 0.87)
			}
		}

		Label {
			id: clientLbl
			anchors {
				left: parent.left
				right: parent.right
			}
			text: qsTr("Client")
			verticalAlignment: Text.AlignBottom
			state: "secondary"
		}

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 14
			border.color: "#eeeeee"

			TextEdit {
				id: clientTxt
				text: client
				wrapMode: Text.WordWrap
				font.pointSize: 9
				anchors.fill: parent
				color: Qt.rgba(0, 0, 0, 0.87)
			}
		}


		Label {
			id: activityLbl
			anchors {
				left: parent.left
				right: parent.right
			}
			text: qsTr("Title")
			verticalAlignment: Text.AlignBottom
			state: "secondary"
		}

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 14
			border.color: "#eeeeee"

			TextEdit {
				id: activityTxt
				text: activity
				wrapMode: Text.WordWrap
				font.pointSize: 9
				anchors.fill: parent
				color: Qt.rgba(0, 0, 0, 0.87)
			}
		}


		Label {
			id: targetLbl
			anchors {
				left: parent.left
				right: parent.right
			}
			text: qsTr("Target")
			verticalAlignment: Text.AlignBottom
			state: "secondary"
		}

		Rectangle {
			anchors {
				left: parent.left
				right: parent.right
			}
			height: 14
			border.color: "#eeeeee"

			TextEdit {
				id: targetTxt
				text: target
				wrapMode: Text.WordWrap
				font.pointSize: 9
				anchors.fill: parent
				color: Qt.rgba(0, 0, 0, 0.87)
			}
		}
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
		anchors {
			top: parent.bottom
			bottom: parent.bottom
			left: parent.left
			right: parent.left
		}

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
				color: "#fdd835"
				radius: height/2
			}
			PropertyChanges {
				target: actionLayout
				opacity: 0
			}
			PropertyChanges {
				target: formLayout
				opacity: 0
			}
			AnchorChanges {
				target: button
				anchors.top: parent.top
				anchors.bottom: parent.bottom
				anchors.left: parent.left
				anchors.right: parent.right
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
