/***************************************************************************
 *   Copyright (C) 2005/06 by the Quassel Project                          *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "verticaldock.h"

#include <QPainter>

#include <QDebug>

VerticalDockTitle::VerticalDockTitle(QDockWidget *parent)
  : QWidget(parent)
{
}

QSize VerticalDockTitle::sizeHint() const {
  return QSize(10, 15);
}

QSize VerticalDockTitle::minimumSizeHint() const {
  return QSize(10, 15);
}

void VerticalDockTitle::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  
  if(rect().isValid() && rect().height() > minimumSizeHint().height()) {
    for(int i = 0; i < 2; i++) {
      QPoint topLeft = rect().topLeft() + QPoint(3 + i*2, 5);
      QPoint bottomRight = rect().topLeft() + QPoint(3 + i*2, rect().height() - 5);
      qDrawShadeLine(&painter, topLeft, bottomRight, palette());
    }
  }

}



// ==============================
//  Vertical Dock
// ==============================
VerticalDock::VerticalDock(const QString &title, QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
  setDefaultTitleWidget();
}

VerticalDock::VerticalDock(QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(parent, flags)
{
  setDefaultTitleWidget();
}

void VerticalDock::setDefaultTitleWidget() {
  QWidget *oldDockTitle = titleBarWidget();
  QWidget *newDockTitle = new VerticalDockTitle(this);

  setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
  setFeatures(features() | QDockWidget::DockWidgetVerticalTitleBar);
  setTitleBarWidget(newDockTitle);
  
  if(oldDockTitle)
    oldDockTitle->deleteLater();
}

void VerticalDock::showTitle(bool show) {
  QWidget *oldDockTitle = titleBarWidget();
  QWidget *newDockTitle = 0;
  
  if(show)
    newDockTitle = new VerticalDockTitle(this);
  else
    newDockTitle = new EmptyDockTitle(this);

  setTitleBarWidget(newDockTitle);
  if(oldDockTitle)
    oldDockTitle->deleteLater();
}
