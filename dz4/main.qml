import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

//import ru.ot.MySqlModel 1.0
Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Домашнее задание №4")

    property int margin: 5
    property int row

    TableView {
        id: tableView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: root.height - btn.height - margin * 2

        model: mySqlModel

        rowDelegate: Item {
            height: 64
        }

        TableViewColumn {
            role: "id"
            title: "ID"
            delegate: delegateId
            width: 64
        }
        TableViewColumn {
            role: "name"
            title: "Имя"
            delegate: delegateName
            width: 64
        }
        TableViewColumn {
            role: "standart"
            title: "Стандарт"
            delegate: delegateStandart
            width: 130
        }
        TableViewColumn {
            role: "header"
            title: "Заголовок"
            delegate: delegateHeader
            width: 64
        }
        TableViewColumn {
            role: "description"
            title: "Описание"
            delegate: delegateDescription
            width: 130
        }
        Component.onCompleted: {
            mySqlModel.updateModel()
            //tableView.resizeColumnsToContents()
        }
    }

    Component {
        id: delegateId
        Label {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: styleData.value
        }
    }

    Component {
        id: delegateName
        TextEdit {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: styleData.value
            onEditingFinished: model.name = text
        }
    }
    Component {
        id: delegateStandart
        Image {
            anchors.fill: parent
            width: 130
            height: 64
            source: "qrc:/img/11.png"
        }
    }
    Component {
        id: delegateHeader

        TextEdit {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: styleData.value
            onEditingFinished: model.header = text
        }
    }

    Component {
        id: delegateDescription
        Rectangle {
            id: tt
            anchors.margins: 5
            anchors.fill: parent
            color: "#91a189"
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "Описание"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    descript.visible = true
                    tEd.text = model.description
                    row = model.index
                }
            }
            //            Component.onCompleted: {
            //                if (cnt == 0) {
            //                    console.log("Connect")
            //                    cnt = 1
            //                    root.bxc.connect(setValue)
            //                }
            //            }
            //            function setValue(value) {
            //                console.log("XCV")
            //                model.description = "XCV"
            //            }
        }
    }

    Button {
        anchors.horizontalCenter: tableView.horizontalCenter
        anchors.top: tableView.bottom
        anchors.topMargin: margin

        id: btn
        text: qsTr("Обновить")
        onClicked: {
            mySqlModel.updateModel()
            //tableView.resizeColumnsToContents()
        }
    }

    Item {
        id: descript
        width: 640
        height: 480
        visible: false
        Rectangle {
            id: unikl
            anchors.fill: parent
            color: "#dee6da"
            Rectangle {
                id: des2
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.height - btn.height - margin * 2
                TextEdit {
                    id: tEd
                    anchors.fill: parent
                }
            }
            Button {
                anchors.horizontalCenter: des2.horizontalCenter
                anchors.top: des2.bottom
                anchors.topMargin: margin

                id: btnClose
                text: qsTr("Закрыть")
                onClicked: {
                    tableView.model.updateDescription(row, tEd.text)
                    descript.visible = false
                    mySqlModel.updateModel()
                }
            }
        }
    }
}
