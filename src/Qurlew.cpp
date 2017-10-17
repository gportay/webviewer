/*
 * Copyright (C) 2017  Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *	Gaël Portay <gael.portay@savoirfairelinux.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "Qurlew.hpp"

#include <QDebug>

Qurlew::Qurlew(QObject *parent) :
	QObject(parent)
{
	connect(&view, &QWebEngineView::urlChanged, this, &Qurlew::urlChanged);
	view.showFullScreen();
	view.setUrl(QUrl("https://www.savoirfairelinux.com"));
}

void Qurlew::urlChanged(const QUrl &url)
{
	qDebug() << "URL changed: " << url;
}

void Qurlew::lineRead(const QString &line)
{
	qDebug() << "Changing URL: " << line;
	view.setUrl(QUrl(line));
}
