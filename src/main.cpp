#include <QApplication>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <SingleApplication>

#include "Logger.hpp"
#include "MainWindow.h"
#include "Path.h"
#include "version.h"

void loadQssStyle()
{
    // TODO:检测设置或系统颜色主题，应用对应样式表
    QFile qssFile(":/qss/resources/style/style_white.qss");
    if (qssFile.open(QIODevice::ReadOnly)) {
        qApp->setStyleSheet(qssFile.readAll());
    }
    qssFile.close();
}

void initLogger()
{
    std::string filepath = utils::Path::logPath().append("/flowd.log").toStdString();
    Log::instance("FlowD", filepath);
    Log::setLevel(1);
}

int main(int argc, char* argv[])
{
    SingleApplication a(argc, argv);

    initLogger();
    loadQssStyle();

#if defined(Q_OS_WIN)
    a.setWindowIcon(QIcon(":/resources/win/logo.ico"));
#elif defined(Q_OS_MAC)
    a.setWindowIcon(QIcon(":/resources/mac/logo.icns"));
#else
    a.setWindowIcon(QIcon(":/resources/logo.png"));
#endif

    MainWindow w;
    w.setWindowTitle("FlowD " + QString(VERSION_STR));
    w.show();

    QObject::connect(&a, &SingleApplication::instanceStarted, &w, &MainWindow::show);

    return QApplication::exec();
}
