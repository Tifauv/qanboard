import QtQuick 1.1

ListModel {
	//nextId: 26

	ListElement {
		name: "Backlog"
		tasks: [
			ListElement {
				taskId: 3
				assignee: ""
				description: "Write documentation for the new API"
				category: "Documentation"
			},

			ListElement {
				taskId: 4
				assignee: ""
				description: "Install Redis on the server"
				category: "Sysadmins"
			},

			ListElement {
				taskId: 24
				assignee: ""
				description: "Write documentation about the new feature"
				category: "Documentation"
			},

			ListElement {
				taskId: 25
				assignee: ""
				description: "Implement a new algorithm"
				category: "Improvement"
			}
		]
	}

	ListElement {
		name: "Ready"
		tasks: [
			ListElement {
				taskId: 2
				assignee: "demo"
				description: "Fix that bug [TB: 4h]"
				category: "Bug"
			}
		]
	}

	ListElement {
		name: "Work in progress"
		tasks: [
			ListElement {
				taskId: 1
				assignee: "demo1"
				description: "Add this awesome feature"
				category: "Feature request"
			},

			ListElement {
				taskId: 22
				assignee: "demo2"
				description: "Fix bug in prod"
				category: "Bug"
			}
		]
	}

	ListElement {
		name: "Done"
		tasks: [
			ListElement {
				taskId: 23
				assignee: ""
				description: "Code refactoring"
				category: "Improvement"
			}
		]
	}
}
