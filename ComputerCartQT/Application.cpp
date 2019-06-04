#include "Application.h"

Application::Application(int& argc, char** argv) :
    QApplication(argc, argv),
    mainWindow(nullptr),
    cModel(nullptr) {
        cModel = new CartModel();
        mainWindow = new MainWindow(*cModel);
    }

int main(int argc, char* argv[]) {
    //Default font
    QFont sansFont("Helvetica [Cronxy]", 12);

    #if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
        Application::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
    Application::setOrganizationName("Columbia Secondary School");
    Application::setApplicationName("CCMS");
    Application::setApplicationVersion("0.2");
    Application::setFont(sansFont);

    Application app(argc, argv);
    return app.exec();
}

Application::~Application() {
    delete mainWindow;
    delete cModel;
}

