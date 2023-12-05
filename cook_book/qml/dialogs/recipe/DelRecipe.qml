import QtQuick 2.6
import Sailfish.Silica 1.0

Dialog {
    property string nameRecipe

    showNavigationIndicator: false

    Column {
        width: parent.width

        DialogHeader {
            acceptText: qsTr("Delete")
            cancelText: qsTr("Cancel")
        }

        Label {
            anchors.left: parent.left
            anchors.leftMargin: Theme.paddingMedium
            text: qsTr("Delete recipe:")
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: nameRecipe
            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeExtraLarge
        }
    }
}
