import QtQuick 2.9

TaskFooterForm {
	id: footer

	property string dueDate: "12/05/2015"
	property string target: "Target"

	dueDateLbl.text: dueDate
	dueDateLbl.visible: footer.width >= dueDateLbl.width
	targetLbl.text: target
}

/*##^## Designer {
	D{i:0;autoSize:true;height:20;width:300}
}
 ##^##*/
