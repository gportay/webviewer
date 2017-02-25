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

#include "StandardInput.hpp"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <QTextStream>

StandardInput::StandardInput(QObject *parent) :
	QObject(parent),
	notifier(STDIN_FILENO, QSocketNotifier::Read)
{
	int ret = fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
	if (ret) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	connect(&notifier, SIGNAL(activated(int)), this, SLOT(activated(int)));
}

void StandardInput::activated(int socket)
{
	Q_UNUSED(socket);
	QTextStream qin(stdin);
	QString line = qin.readLine();

	if (line.isNull())
		emit closed();
	else
		emit lineRead(line);
}
