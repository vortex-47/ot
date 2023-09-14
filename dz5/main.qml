import QtQuick 2.0
import QtQuick.Controls 2.0

ListView {
    id: listView
    width: 480
    height: 854
    required model
    delegate: test

    property int smallMargin: 10

    Component {
        id: test
        Rectangle {
            required property string name
            required property int price
            required property bool inFavorite
            required property int discontPrice
            required property int quantity
            required property string image
            id: rec
            width: listView.width - smallMargin * 2
            height: 430
            x: smallMargin
            Text {
                id: pName
                text: name
                y: 20
                font.pixelSize: 26
                font.bold: true
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Image {
                id: pImage
                anchors.top: pName.bottom
                anchors.topMargin: 5
                source: image
                height: 150
                width: parent.width
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
            }
            Text {
                id: pPrice
                anchors.top: pImage.bottom
                text: "Цена: " + price
                font.pixelSize: 16
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                id: pDPrice
                anchors.top: pPrice.bottom
                text: "Цена со скидкой: " + discontPrice
                font.pixelSize: 26
                color: "red"
                font.bold: true
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                id: pQuantity
                anchors.top: pDPrice.bottom
                text: "В наличии: " + quantity + " шт."
                font.pixelSize: 20
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                id: pInFavorite
                anchors.top: pQuantity.bottom
                text: "В избранном: " + (inFavorite ? "ДА" : "НЕТ")
                font.pixelSize: 16
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Button {
                id: but
                anchors.top: pInFavorite.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                text: "В корзину"
                onClicked: console.log("Added in cart")
            }
            Rectangle {
                anchors.top: but.bottom
                anchors.topMargin: 50
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 50
                height: 3
                color: "steelblue"
            }
        }
    }
}
