import QtQuick 2.6
import Sailfish.Silica 1.0

Dialog {
    property string nameCategory

    showNavigationIndicator: false

    canAccept: nameField.acceptableInput

    Column {
        width: parent.width

        DialogHeader {
            acceptText: qsTr("Change")
            cancelText: qsTr("Cancel")
        }

        TextField {
            id: nameField
            width: parent.width
            text: nameCategory
            placeholderText: qsTr("Enter name category")
            label: qsTr("(rus eng 0-9 _-space)(from 3 to 40 symb.)")
            validator: RegExpValidator {
            regExp: /^[a-zA-Zа-яА-Я0-9_ -]{3,20}$/ }
            inputMethodHints: Qt.ImhNoAutoUppercase
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            nameCategory = nameField.text
        }
    }
}
