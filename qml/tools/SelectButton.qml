import QtQuick 1.1

Rectangle {
	id: button
	height: 20
	width: height
	color: "#e3f2fd"
	radius: height/2

	property bool selected: false

	Label {
		id: label
		text: "+"
		font.pointSize: button.height * 0.75
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
	}

	MouseArea {
		id: mouseArea
		anchors.fill: parent

		onClicked:  {
			selected = !selected;
			console.log("(i) [SelectButton]  selection is now " + selected);
		}
	}

	states: [
		State {
			name: "hover"
			when: mouseArea.containsMouse && ! selected
			PropertyChanges {
				target: label
				font.pointSize: button.height * 0.9
			}
		},
		State {
			name: "selected"
			when: !mouseArea.containsMouse && selected
			PropertyChanges {
				target: button
				color: "#ffab00"
			}
			PropertyChanges {
				target: label
				color: "white"
				font.pointSize: button.height * 0.9
			}
		},
		State {
			name: "hoverSelected"
			when: mouseArea.containsMouse && selected
			PropertyChanges {
				target: button
				color: "#ffab00"
			}
			PropertyChanges {
				target: label
				color: "white"
				font.pointSize: button.height * 0.9
			}
		}

	]
}
