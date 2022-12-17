#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>
#include <qqmlcomponent.h>
#include "Backend.h"
#include "logger.h"

int main(int argc, char* argv[]) {
	setupLogger();

	#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	#endif
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	Backend* backend = new Backend(nullptr, engine.rootContext());

	engine.rootContext()->setContextProperty("backend", backend);

	const QUrl url(u"qrc:/main.qml"_qs);
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated, &app,
		[url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);

	engine.load(url);
	backend->setObj(engine.rootObjects().at(0));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}