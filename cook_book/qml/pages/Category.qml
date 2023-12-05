import QtQuick 2.6
import Sailfish.Silica 1.0
import ru.exlearn.cook_book 1.0

Page {
    id: categoryPage
    property string nameCategory

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Add recipe")
                onClicked: {
                    var addRecipeDialog = pageStack.push(Qt.resolvedUrl("../dialogs/recipe/AddRecipe.qml"))
                    addRecipeDialog.accepted.connect(function() {
                        recipeModel.insertQuery(addRecipeDialog.nameRecipe, addRecipeDialog.numberPersons, addRecipeDialog.jsonString, addRecipeDialog.cookProcess, nameCategory);
                    })
                }
            }
        }
        PageHeader { id: pageCategory
            title: nameCategory }

        SilicaListView {
            anchors.top: pageCategory.bottom
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
            width: parent.width - Theme.horizontalPageMargin
            height: parent.height - pageCategory.height
            clip: true
            model: recipeModel
            delegate: ListItem {
                width: ListView.view.width
                Label {
                    text: nameRec
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.verticalCenter: parent.verticalCenter
                }
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Delete")
                        onClicked: {
                            var delRecipeDialog = pageStack.push(Qt.resolvedUrl("../dialogs/recipe/DelRecipe.qml"), {"nameRecipe": nameRec})
                            delRecipeDialog.accepted.connect(function() {
                                recipeModel.deleteQuery(idRec, nameCategory);
                            })
                        }
                    }
                }
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("./Recipe.qml"), {"nameRecipe": nameRec, "idRecipe": idRec, "nameCategory": nameCategory})
                }
            }
            VerticalScrollDecorator { }
        }

    }
    Label {
        id: noRecipes
        visible: DataBase.isEmptyCategory(nameCategory)
        anchors.centerIn: categoryPage
        text: qsTr("No recipes")
        font.pixelSize: Theme.fontSizeHuge
        color: "darkred"
    }

    Component.onCompleted: {
        recipeModel.refreshQuery(nameCategory);
    }
    Connections {
        target: recipeModel
        onQueryStrChanged: {
            noRecipes.visible = DataBase.isEmptyCategory(nameCategory)
        }
    }
}
