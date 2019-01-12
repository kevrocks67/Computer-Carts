#include "Application.h"


Application::Application(int& argc, char** argv) :
    QApplication(argc, argv),
    mainWindow(nullptr),
    mySession(nullptr),
    cModel(nullptr) {

    mySession = new Session();
    cModel = new CartModel();
    mainWindow = new MainWindow(*mySession, *cModel);

    }

int main(int argc, char* argv[]) {
    #if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
        Application::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
    Application::setOrganizationName("Columbia Secondary School");
    Application::setApplicationName("CCMS");
    Application::setApplicationVersion("0.1");

    Application app(argc, argv);
    return app.exec();
}

Application::~Application() {
    delete mainWindow;
    delete mySession;
    delete cModel;
}
