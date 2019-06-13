import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Dialog {
	id: dialog
	title: qsTr("New Task")
	
	property alias taskTitle: titleTxt.text
	property alias taskDescription: descriptionTxt.text
	property alias taskClient: clientTxt.text
	property alias taskActivity: activityTxt.text
	property alias taskTarget: targetTxt.text
	
	implicitWidth: 300
	implicitHeight: 400
	
	standardButtons: Dialog.Save | Dialog.Cancel
	closePolicy: Dialog.CloseOnEscape | Dialog.CloseOnPressOutside

	Kirigami.FormLayout {
		anchors.fill: parent

		TextField {
			id: titleTxt
			Kirigami.FormData.label: qsTr("Title")
		}
		TextArea {
			id: descriptionTxt
			Kirigami.FormData.label: qsTr("Description")
			width: titleTxt.width
			height: titleTxt.height * 4
		}
		Kirigami.Separator {
			Kirigami.FormData.isSection: true
		}
		TextField {
			id: clientTxt
			Kirigami.FormData.label: qsTr("Client")
		}
		TextField {
			id: activityTxt
			Kirigami.FormData.label: qsTr("Activity")
		}
		TextField {
			id: targetTxt
			Kirigami.FormData.label: qsTr("Target")
		}
	}
	
	function reset() {
		titleTxt.text = "";
		descriptionTxt.text = "";
		clientTxt.text = "";
		activityTxt.text = "";
		targetTxt.text = "";
		titleTxt.focus = true;
	}
}
