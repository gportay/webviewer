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

#include <QCommandLineParser>

#include "Qurlew.hpp"
#include "StandardInput.hpp"

int main(int argc, char **argv)
{
	Application app(argc, argv);

	QCommandLineParser parser;
	parser.setApplicationDescription(
			"A stdin controlled WebBrowser based on Qt WebEngine.");
	QCommandLineOption urlOption(QStringList() << "u" << "url",
			QCoreApplication::translate("main", "Set default URL."),
			QCoreApplication::translate("main", "url"));
	parser.addOption(urlOption);
	parser.addVersionOption();
	parser.addHelpOption();
	parser.process(app);

	QCoreApplication::setApplicationName("Qurlew");
	QCoreApplication::setApplicationVersion("0.1");
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	StandardInput input;
	QObject::connect(&input, &StandardInput::closed, &app,
			 &Application::quit);

	QString url = parser.value(urlOption);
	Qurlew qurlew(url);
	QObject::connect(&input, &StandardInput::lineRead, &qurlew,
			 &Qurlew::urlRequested);

	return app.exec();
}
