#include "Application.h"

//TODO Add config file for font, theme, and possibly language

Application::Application(int& argc, char** argv) :
    QApplication(argc, argv),
    mainWindow(nullptr),
    mySession(nullptr),
    cModel(nullptr) {

    mySession = new Session();
    //QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE");
    //cartdb.setDatabaseName("carts.db");
    //cModel = new CartModel(0,cartdb);
    cModel = new CartModel();
    mainWindow = new MainWindow(*mySession, *cModel);

    }

int main(int argc, char* argv[]) {
    QFont sansFont("Helvetica [Cronxy]", 14);

    #if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
        Application::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
    Application::setOrganizationName("Columbia Secondary School");
    Application::setApplicationName("CCMS");
    Application::setApplicationVersion("0.1");
    Application::setFont(sansFont);

    Application app(argc, argv);
    return app.exec();
}

Application::~Application() {
    delete mainWindow;
    delete mySession;
    delete cModel;
}

