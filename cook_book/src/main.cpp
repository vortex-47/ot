/*******************************************************************************
**
** Copyright (C) 2022 ru.exlearn
**
** This file is part of the Книга для ваших кулинарных заметок и рецептов
*project.
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

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtQuick>
#include <auroraapp.h>

#include "categorysqlmodel.h"
#include "database.h"
#include "recipesqlmodel.h"

int main(int argc, char *argv[]) {

  qmlRegisterSingletonType<DataBase>("ru.exlearn.cook_book", 1, 0, "DataBase",
                                     &DataBase::dbInstance);
  qmlRegisterType<CategorySqlModel>("ru.exlearn.cook_book", 1, 0,
                                    "CategorySqlModel");
  qmlRegisterType<RecipeSqlModel>("ru.exlearn.cook_book", 1, 0,
                                  "RecipeSqlModel");

  QScopedPointer<QGuiApplication> application(
      Aurora::Application::application(argc, argv));
  application->setOrganizationName(QStringLiteral("ru.exlearn"));
  application->setApplicationName(QStringLiteral("cook_book"));

  QScopedPointer<QQuickView> view(Aurora::Application::createView());
  view->setSource(
      Aurora::Application::pathTo(QStringLiteral("qml/cook_book.qml")));
  view->show();

  return application->exec();
}
