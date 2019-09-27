#include "Application.h"

Application::Application(int& argc, char** argv) :
    QApplication(argc, argv),
    mainWindow(nullptr),
    cModel(nullptr),
    lModel(nullptr) {
        cModel = new CartModel();
        lModel = new LaptopModel("MainView");
        mainWindow = new MainWindow(*cModel, *lModel);
    }

int main(int argc, char* argv[]) {
    //Default font
    QFont sansFont("Helvetica [Cronxy]", 14);

    #if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
        Application::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
    Application::setOrganizationName("Columbia Secondary School");
    Application::setApplicationName("CCMS");
    Application::setApplicationVersion("0.3");
    Application::setFont(sansFont);

    Application app(argc, argv);
    return app.exec();
}

Application::~Application() {
    if(cModel != nullptr)
        delete cModel;
    if(lModel != nullptr)
        delete lModel;
    if(mainWindow != nullptr)
        delete mainWindow;
}

