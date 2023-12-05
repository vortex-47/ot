/*******************************************************************************
**
** Copyright (C) 2022 ru.exlearn
**
** This file is part of the Книга для ваших кулинарных заметок и рецептов project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.6
import Sailfish.Silica 1.0
import ru.exlearn.cook_book 1.0

Page {
    id: mainPage
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: qsTr("Add category")
                onClicked: {
                    var addCategoryDialog = pageStack.push(Qt.resolvedUrl("../dialogs/category/AddCategory.qml"))
                    addCategoryDialog.accepted.connect(function() {
                        sqlModel.insertQuery(addCategoryDialog.nameCategory);
                    })
                }
            }
        }
        PageHeader {
            id: pageHeader
            title: qsTr("Categories")
            extraContent.children: [
                IconButton {
                    objectName: "aboutButton"
                    icon.source: "image://theme/icon-m-about"
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                }
            ]
        }

        SilicaListView {
            anchors.top: pageHeader.bottom
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
            width: parent.width - Theme.horizontalPageMargin
            height: parent.height - pageHeader.height
            clip: true
            model: sqlModel
            delegate: ListItem {
                width: ListView.view.width
                Label {
                    text: nameCat
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.verticalCenter: parent.verticalCenter
                }
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Change")
                        onClicked: {
                            var changeCategoryDialog = pageStack.push(Qt.resolvedUrl("../dialogs/category/ChangeCategory.qml"), {"nameCategory": nameCat})
                            changeCategoryDialog.accepted.connect(function() {
                                sqlModel.updateQuery(changeCategoryDialog.nameCategory, idCat);
                            })
                        }
                    }
                    MenuItem {
                        text: qsTr("Delete")
                        onClicked: {
                            var delCategoryDialog = pageStack.push(Qt.resolvedUrl("../dialogs/category/DelCategory.qml"), {"nameCategory": nameCat})
                            delCategoryDialog.accepted.connect(function() {
                                sqlModel.deleteQuery(idCat);
                            })
                        }
                    }
                }
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("./Category.qml"), {"nameCategory": nameCat})
                }
            }
            VerticalScrollDecorator { }
        }
        Label {
            id: noCategory
            visible: DataBase.isEmpty("category")
            anchors.centerIn: parent
            text: qsTr("No categories")
            font.pixelSize: Theme.fontSizeHuge
            color: "darkred"
        }
    }
    Connections {
        target: sqlModel
        onQueryStrChanged: {
            noCategory.visible = DataBase.isEmpty("category")
        }
    }
}
