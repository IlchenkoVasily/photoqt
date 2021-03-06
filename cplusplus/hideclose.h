/**************************************************************************
 **                                                                      **
 ** Copyright (C) 2018 Lukas Spies                                       **
 ** Contact: http://photoqt.org                                          **
 **                                                                      **
 ** This file is part of PhotoQt.                                        **
 **                                                                      **
 ** PhotoQt is free software: you can redistribute it and/or modify      **
 ** it under the terms of the GNU General Public License as published by **
 ** the Free Software Foundation, either version 2 of the License, or    **
 ** (at your option) any later version.                                  **
 **                                                                      **
 ** PhotoQt is distributed in the hope that it will be useful,           **
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of       **
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        **
 ** GNU General Public License for more details.                         **
 **                                                                      **
 ** You should have received a copy of the GNU General Public License    **
 ** along with PhotoQt. If not, see <http://www.gnu.org/licenses/>.      **
 **                                                                      **
 **************************************************************************/

#ifndef HIDECLOSE_H
#define HIDECLOSE_H

#include <QObject>
#include <QQuickView>

#include "settings/settings.h"
#include "scripts/getanddostuff.h"

class HideClose : QObject {

public:
    static void handleCloseEvent(QEvent *e, Settings *settings, QQuickView *view) {

        if(settings->getTrayIcon() != 1) {

            qunsetenv("PHOTOQT_DEBUG");

            GetAndDoStuff gads;
            gads.storeGeometry(QRect(view->x(), view->y(), view->width(), view->height()));

            e->accept();
            qApp->quit();

        } else
            view->hide();

    }

};

#endif // HIDECLOSE_H
