import QtQuick 2.6

Text {
	id: label
	font.pointSize: 8
	color: Qt.rgba(0, 0, 0, 0.87)

	states: [
		State {
			name: "secondary"
			PropertyChanges {
				target: label
				color: Qt.rgba(0, 0, 0, 0.54)
			}
		},

		State {
			name: "disabled"
			PropertyChanges {
				target: label
				color: Qt.rgba(0, 0, 0, 0.26)
			}
		}
	]
}
