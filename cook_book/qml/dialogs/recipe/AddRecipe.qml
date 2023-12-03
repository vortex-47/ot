import QtQuick 2.6
import Sailfish.Silica 1.0

Dialog {
    property string nameRecipe
    property int numberPersons
    property var cookProcess
    property int mar: 1
    property string jsonString: ""
    property var jsonObject

    showNavigationIndicator: false

    canAccept: nameField.acceptableInput && kpField.acceptableInput

    DialogHeader {
        id: dHeader
        anchors.top:parent.top
        acceptText: qsTr("Add")
        cancelText: qsTr("Cancel")
    }

    SilicaFlickable {
        anchors {
            top: dHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        contentHeight: column.height
        clip: true

        Column {
            id: column
            width: parent.width

            Label {
                id: nRecipe
                width: parent.width
                leftPadding: Theme.paddingLarge
                text: qsTr("Name recipe:")
                color: Theme.highlightColor
            }
            TextField {
                id: nameField
                width: parent.width
                placeholderText: qsTr("Enter name recipe")
                label: qsTr("(rus eng 0-9 _-space)(from 3 to 40 symb.)")
                validator: RegExpValidator {
                    regExp: /^[a-zA-Zа-яА-Я0-9_ -]{3,40}$/
                }
                inputMethodHints: Qt.ImhNoAutoUppercase
                EnterKey.onClicked: focus = false
            }
            Label {
                id: nPersons
                width: parent.width
                leftPadding: Theme.paddingLarge
                text: qsTr("Number of persons:")
                color: Theme.highlightColor
            }
            TextField {
                id: kpField
                width: parent.width
                placeholderText: qsTr("Enter the number of persons")
                label: qsTr("1-8")
                validator: RegExpValidator {
                    regExp: /^[1-8]$/
                }
                inputMethodHints: Qt.ImhDigitsOnly
                EnterKey.onClicked: focus = false
            }
            Row {
                id: ingItem
                width: parent.width
                Label {
                    id: lIng
                    width: parent.width - icAddButton.width
                    leftPadding: Theme.paddingLarge
                    text: qsTr("Ingredients:")
                    color: Theme.highlightColor
                }
                IconButton {
                    id: icAddButton
                    icon.source: "image://theme/icon-m-add"
                    onClicked: {
                        slModel.append({name:"", kol:"", units:"gr"})
                        mar = mar + 1
                        console.log("Add")
                    }
                }
            }
            SilicaListView {
                id:slView
                width: parent.width
                height: nameField.height * 2 * mar - Theme.paddingLarge * 7
                model: ListModel {
                    id: slModel
                }
                delegate: Item {
                    id: item
                    height: ingColumn.height
                    width: parent.width
                    Column {
                        id: ingColumn
                        width: parent.width
                        Row {
                            width: parent.width
                            TextField {
                                id: tf
                                width: parent.width - icRemoveButton.width
                                placeholderText: qsTr("Enter ingredient name")
                                label: qsTr("(rus eng 0-9 _-space)(from 3 to 30 symb.)")
                                validator: RegExpValidator {
                                    regExp: /^[a-zA-Zа-яА-Я0-9_ -]{3,30}$/
                                }
                                inputMethodHints: Qt.ImhNoAutoUppercase
                                EnterKey.onClicked: focus = false
                                onTextChanged: {
                                    name = text
                                }
                            }
                            IconButton {
                                id: icRemoveButton
                                icon.source: "image://theme/icon-m-clear"
                                onClicked: {
                                    slModel.remove(index)
                                    mar = mar - 1
                                }
                            }
                        }
                        Row {
                            width: parent.width
                            Label {
                                id: lKol
                                leftPadding: Theme.paddingLarge
                                text: qsTr("Qty.:")
                            }
                            TextField {
                                id: tfKol
                                textLeftMargin: Theme.paddingSmall
                                //width: parent.width
                                width: Theme.fontSizeLarge * 5
                                validator: RegExpValidator {
                                    regExp: /^[0-9.,]{1,5}$/
                                }
                                inputMethodHints: Qt.ImhDigitsOnly
                                EnterKey.onClicked: focus = false
                                onTextChanged: {
                                    kol = text
                                }
                            }
                            ComboBox {
                                label: qsTr("Units:")

                                menu: ContextMenu {
                                    MenuItem { text: qsTr("gr") }
                                    MenuItem { text: qsTr("ml") }
                                    MenuItem { text: qsTr("tsp.") }
                                    MenuItem { text: qsTr("tbsp.") }
                                    MenuItem { text: qsTr("kg") }
                                }
                                onCurrentIndexChanged: {
                                    units = value
                                }
                            }
                        }
                    }
                }
            }
            Label {
                width: parent.width
                leftPadding: Theme.paddingLarge
                text: qsTr("Cooking process:")
                color: Theme.highlightColor
            }
            TextArea {
                id: ta
                width: parent.width
                placeholderText: qsTr("Description of the cooking process")
            }
        }
        VerticalScrollDecorator { }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            nameRecipe = nameField.text
            numberPersons = kpField.text
            cookProcess = ta.text
            if (slModel.count > 0) {
                jsonString = jsonString + "[";
            }
            for (var i = 0; i < slModel.count; i++) {
                jsonString = jsonString + '{"name":"' + slModel.get(i).name + '", ';
                jsonString = jsonString + '"kol":"' + slModel.get(i).kol + '", ';
                jsonString = jsonString + '"units":"' + slModel.get(i).units + '"}';
                if (i != slModel.count - 1) {
                    jsonString = jsonString + ", ";
                }
            }
            jsonString = jsonString + "]";
            //console.log(jsonString)
            //jsonObject = JSON.parse(jsonString);
        }
    }
}
