import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4 as Controls
import org.kde.kirigami 2.4 as Kirigami
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
	
	signal edit(int taskId)
	
	property bool _showActions: false

	ColumnLayout {
		id: taskLayout
		
		anchors.fill: parent
		anchors.margins: Kirigami.Units.largeSpacing
		
		spacing: Kirigami.Units.smallSpacing
		
		RowLayout {
			id: headerLayout
			
			Layout.fillWidth: true
			
			TaskHeader {
				id: header
				
				taskId: task.taskId
				title: qsTr("%1 %2").arg(task.client).arg(task.activity)
				
				Layout.fillWidth: true
			}
			
			Controls.Button {
				id: menuBtn
				
				text: qsTr("Show task actions")
				icon.name: "overflow-menu"
				display: Controls.AbstractButton.IconOnly
				flat: true
				
				topPadding: 1
				bottomPadding: 1
				leftPadding: 1
				rightPadding: 1
				
				enabled: ! _showActions
				
				Layout.preferredHeight: Kirigami.Units.gridUnit
				Layout.preferredWidth: Kirigami.Units.gridUnit
				
				hoverEnabled: true
				onHoveredChanged: menuBtn.icon.color = (hovered ? Kirigami.Theme.highlightColor : Kirigami.Theme.textColor)
				onClicked: _showActions = true
			}
		}

		Label {
			id: descriptionLbl

			text: task.description
			clip: true
			elide: Text.ElideRight
			wrapMode: Text.WordWrap
			font.pointSize: 9
			
			Layout.fillWidth: true
			Layout.fillHeight: true
		}

		TaskFooter {
			id: footer
			
			target: task.target
			dueDate: task.dueDate
			
			Layout.fillWidth: true
		}
	}
	
	Item {
		id: actionsPanel
		
		visible: false
		
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
		}
		height: 0
		
		Rectangle {
			id: actionsBackground
			
			anchors.fill: actionsPanel
			color: Kirigami.Theme.highlightColor
			opacity: 0.6
		}
		
		MouseArea {
			id: mouseArea
			
			anchors.fill: parent
			hoverEnabled: true
			
			propagateComposedEvents: true
			
			onContainsMouseChanged: if (!containsMouse) _showActions = false
		}

		RowLayout {
			id: actionsLayout
			
			anchors.fill: parent
			anchors.margins: Kirigami.Units.largeSpacing
			layoutDirection: Qt.RightToLeft
			
			Controls.ToolButton {
				id: editBtn
				
				text: qsTr("Edit")
				icon.name: "document-edit"
				display: Controls.AbstractButton.IconOnly
				
				onClicked: edit(taskId)
			}
		}
	}
	
	states: [
		State {
			name: "ShowActions"
			when: _showActions
			
			PropertyChanges {
				target: actionsPanel
				height: task.height
				visible: true
			}
		}
	]
	
	transitions: Transition {
		NumberAnimation {
			target: actionsPanel
			property: "height"
			duration: Kirigami.Units.shortDuration
			easing.type: Easing.InOutQuad
		}
	}
}
