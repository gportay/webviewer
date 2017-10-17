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

#pragma once

#include <QObject>

#include <QSocketNotifier>

class StandardInput : public QObject
{
	Q_OBJECT

public:
	explicit StandardInput(QObject *parent = 0);

signals:
	void lineRead(const QString &line);
	void closed();

private:
	QSocketNotifier notifier;

private slots:
	void activated(int socket);
};
