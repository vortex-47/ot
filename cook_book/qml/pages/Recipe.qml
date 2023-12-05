import QtQuick 2.6
import Sailfish.Silica 1.0
import ru.exlearn.cook_book 1.0

Page {
    id: recipePage
    property string nameRecipe
    property int idRecipe
    property string nameCategory
    property var jsonObject
    property int mar: 0

    PageHeader {
        id: pageRecipe
        title: nameRecipe
    }


    SilicaFlickable {
        anchors {
            top: pageRecipe.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        contentHeight: column.height
        clip: true
        VerticalScrollDecorator {}


        Column {
            id: column
            width: parent.width
            Row {
                width: parent.width
                Label {
                    id: lab

                    leftPadding: Theme.paddingLarge
                    text: qsTr("Number of persons: ")
                    color: Theme.highlightColor
                }
                Label {
                    id: lab2
                    leftPadding: Theme.paddingMedium
                    text: DataBase.persons(idRecipe)
                }
            }

            Label {
                width: parent.width
                leftPadding: Theme.paddingLarge
                topPadding: Theme.paddingLarge
                bottomPadding: Theme.paddingLarge
                text: qsTr("Ingredients:")
                color: Theme.highlightColor
            }

            SilicaListView {
                id:slView
                width: parent.width
                height: lab.height * mar
                model: ListModel {
                    id: slModel
                }
                delegate: Label {
                    id: ll
                    width: parent.width
                    leftPadding: Theme.paddingLarge
                    height: 50
                    text: title
                }
            }
            Label {
                width: parent.width
                leftPadding: Theme.paddingLarge
                topPadding: Theme.paddingLarge
                text: qsTr("Cooking process:")
                color: Theme.highlightColor
            }
            TextArea {
                width: parent.width
                readOnly: true                //leftPadding: Theme.paddingLarge
                text: DataBase.description(idRecipe)
            }
        }
    }
    Component.onCompleted: {
        if (DataBase.ingredients(idRecipe).length > 1) {
        jsonObject = JSON.parse(DataBase.ingredients(idRecipe));
        mar = jsonObject.length;
        for (var i = 0; i < mar; i++) {
            slModel.append({title: jsonObject[i].name + " -  " + jsonObject[i].kol + " " + jsonObject[i].units});
        }
        } else {
            slModel.append({title: "No iIngredients"})
            mar = 1
        }
    }
}

