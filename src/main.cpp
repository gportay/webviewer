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

#ifndef QT_NO_WIDGETS
#include <QtWidgets/QApplication>
typedef QApplication Application;
#else
#include <QtGui/QGuiApplication>
typedef QGuiApplication Application;
#endif

#include "Qurlew.hpp"
#include "StandardInput.hpp"

int main(int argc, char **argv)
{
	Application app(argc, argv);

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	StandardInput input;
	QObject::connect(&input, &StandardInput::closed, &app,
			 &Application::quit);

	Qurlew qurlew;
	QObject::connect(&input, &StandardInput::lineRead, &qurlew,
			 &Qurlew::lineRead);

	return app.exec();
}
