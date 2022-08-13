#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>
#include "Lang.h"
#include "Backend.h"

int main(int argc, char* argv[]) {
	#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	#endif
	Backend* backend = new Backend();
	Language* language = new Language();

	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	language->setContext(engine.rootContext());
	language->setLanguage(0);

	engine.rootContext()->setContextProperty("locale", language);
	engine.rootContext()->setContextProperty("backend", backend);

	const QUrl url(u"qrc:/main.qml"_qs);
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated, &app,
		[url] (QObject* obj, const QUrl& objUrl) {
		if(!obj && url == objUrl)
			QCoreApplication::exit(-1);
	},
		Qt::QueuedConnection);

	engine.load(url);
	if(engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}