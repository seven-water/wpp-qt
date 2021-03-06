#include "Application.h"

#include <QTranslator>

//#if defined(Q_OS_MAC) || defined(Q_OS_WIN) || defined(Q_OS_LINUX)
#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
#include <QtWebEngine>
#endif

#include <wpp/qt/IOS.h>

#include <wpp/qt/System.h>
//#include <wpp/qt/LocalStorage.h>
#include <wpp/qt/HttpAgent.h>
#include <wpp/qt/Resolution.h>

#include <wpp/qt/NativeCamera.h>
#include <wpp/qt/ImagePicker.h>
#include <wpp/qt/NativeMap.h>
#include <wpp/qt/NativeDateTimePicker.h>
#include <wpp/qt/IOSTimeZonePicker.h>


namespace wpp {
namespace qt {

#ifdef Q_QDOC
Application::Application(int &argc, char **argv)
	: QGuiApplication(argc, argv)
{
	init();
}
#else
Application::Application(int &argc, char **argv, int flags)
	: QGuiApplication(argc, argv, flags)
{
	init();
}
#endif

void Application::init()
{
#ifdef Q_OS_IOS
	wpp::qt::IOS::documentsDirectoryExcludeICloudBackup();
#endif

	//register singletons
	//wpp::qt::LocalStorage::getInstance();
	wpp::qt::System::getInstance();
	//wpp::qt::HttpAgent& httpAgent = wpp::qt::HttpAgent::getInstance();
	//httpAgent.setDefaultParam("_locale", QLocale::system().name());

	//register QML types
	qmlRegisterType<wpp::qt::NativeCamera>("wpp.qt.NativeCamera", 1, 0, "NativeCamera");
	qmlRegisterType<wpp::qt::ImagePicker>("wpp.qt.ImagePicker", 1, 0, "ImagePicker");
	qmlRegisterType<wpp::qt::NativeMap>("wpp.qt.NativeMap", 1, 0, "NativeMap");
	qmlRegisterType<wpp::qt::NativeDateTimePicker>("wpp.qt.NativeDateTimePicker", 1, 0, "NativeDateTimePicker");
	qmlRegisterType<wpp::qt::IOSTimeZonePicker>("wpp.qt.IOSTimeZonePicker", 1, 0, "IOSTimeZonePicker");

	enableAutoScreenOrientation(true);
}

void Application::loadTranslations(const QString& qmFilenameNoExtension)
{
	QTranslator *translator = new QTranslator(this);
	QString transFilename( QString(":/%1.").arg(qmFilenameNoExtension) + QLocale::system().name() );
	//QString transFilename( QString(":/i18n.en_US") );
	if ( !translator->load( transFilename ) )
	{
		qDebug() << "[ERR] " << __FUNCTION__ << ": Load translation error! filename:" << transFilename;
	}
	else
	{
		qDebug() << "[OK] " << __FUNCTION__ << ": Translations loaded successfully: " << transFilename;
	}
	this->installTranslator(translator);
}

void Application::enableQtWebEngineIfPossible()
{
//#ifdef Q_OS_MAC | Q_OS_WIN | Q_OS_LINUX
#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
	QtWebEngine::initialize();
#endif
}

void Application::registerApplePushNotificationService()
{
	wpp::qt::System::getInstance().registerApplePushNotificationService();
}

}
}

