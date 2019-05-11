#include "Application.h"
#include "phantomstyle.h"

enum ThemeType : int {
  Carbon = 0,
  Polar = 1,
  Stealth = 2,
  Sakura = 3,
};
QPalette namedColorSchemePalette(ThemeType x);

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
    #if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
        Application::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
    Application::setOrganizationName("Columbia Secondary School");
    Application::setApplicationName("CCMS");
    Application::setApplicationVersion("0.1");
    Application::setStyle(new PhantomStyle);
    Application::setPalette(namedColorSchemePalette(Stealth));

    Application app(argc, argv);
    return app.exec();
}

Application::~Application() {
    delete mainWindow;
    delete mySession;
    delete cModel;
}

QPalette namedColorSchemePalette(ThemeType x) {
  struct ThemeColors {
    QColor window;
    QColor text;
    QColor disabledText;
    QColor brightText;
    QColor highlight;
    QColor highlightedText;
    QColor base;
    QColor alternateBase;
    QColor shadow;
    QColor button;
    QColor disabledButton;
    QColor unreadBadge;
    QColor unreadBadgeText;
    QColor icon;
    QColor disabledIcon;
    QColor chatTimestampText;
  };
  auto themeColorsToPalette = [](const ThemeColors& x) -> QPalette {
    QPalette pal;
    pal.setColor(QPalette::Window, x.window);
    pal.setColor(QPalette::WindowText, x.text);
    pal.setColor(QPalette::Text, x.text);
    pal.setColor(QPalette::ButtonText, x.text);
    if (x.brightText.isValid())
      pal.setColor(QPalette::BrightText, x.brightText);
    pal.setColor(QPalette::Disabled, QPalette::WindowText, x.disabledText);
    pal.setColor(QPalette::Disabled, QPalette::Text, x.disabledText);
    pal.setColor(QPalette::Disabled, QPalette::ButtonText, x.disabledText);
    pal.setColor(QPalette::Base, x.base);
    pal.setColor(QPalette::AlternateBase, x.alternateBase);
    if (x.shadow.isValid())
      pal.setColor(QPalette::Shadow, x.shadow);
    pal.setColor(QPalette::Button, x.button);
    pal.setColor(QPalette::Highlight, x.highlight);
    pal.setColor(QPalette::HighlightedText, x.highlightedText);
    if (x.disabledButton.isValid())
      pal.setColor(QPalette::Disabled, QPalette::Button, x.disabledButton);
    // Used as the shadow text color on disabled menu items
    pal.setColor(QPalette::Disabled, QPalette::Light, Qt::transparent);
    return pal;
  };
  ThemeColors c;
  switch (x) {
  case Carbon: {
    QColor window(60, 61, 64);
    QColor button(74, 75, 80);
    QColor base(46, 47, 49);
    QColor alternateBase(41, 41, 43);
    QColor text(208, 209, 212);
    QColor highlight(0xbfc7d5);
    QColor highlightedText(0x2d2c27);
    QColor disabledText(0x60a4a6a8);
    disabledText = disabledText.darker(120); // old
    c.window = window;
    c.text = text;
    c.disabledText = disabledText;
    c.base = base;
    c.alternateBase = alternateBase;
    c.shadow = base;
    c.button = button;
    c.disabledButton = button.darker(107);
    c.brightText = Qt::white;
    c.highlight = highlight;
    c.highlightedText = highlightedText;
    c.icon = text;
    c.disabledIcon = c.disabledText;
    c.unreadBadge = c.text;
    c.unreadBadgeText = c.highlightedText;
    c.chatTimestampText = c.base.lighter(160);
    break;
  }
  case Polar: {
    QColor snow(251, 252, 254);
    QColor callout(90, 97, 111);
    QColor bright(237, 236, 241);
    QColor lessBright(234, 234, 238);
    QColor dimmer(221, 221, 226);
    QColor text(18, 18, 24);
    QColor disabledText(140, 140, 145);
    c.window = bright;
    c.highlight = callout;
    c.highlightedText = QColor(255, 255, 255);
    c.base = snow;
    c.alternateBase = lessBright;
    c.button = bright;
    c.text = text;
    c.disabledText = disabledText;
    c.icon = QColor(105, 107, 113);
    c.disabledIcon = c.disabledText.lighter(125);
    c.unreadBadge = c.highlight;
    c.unreadBadgeText = c.highlightedText;
    c.chatTimestampText = c.base.darker(130);
    break;
  }
  case Stealth: {
    QColor window(30, 31, 32);
    QColor button(41, 42, 44);
    QColor base(23, 24, 25);
    QColor alternateBase(19, 19, 22);
    QColor text(212, 209, 208);
    QColor highlight(211, 210, 208);
    QColor highlightedText(0x2d2c27);
    QColor disabledText(0x60a4a6a8);
    c.window = window;
    c.text = text;
    c.disabledText = disabledText.darker(150);
    c.base = base;
    c.alternateBase = alternateBase;
    c.shadow = base;
    c.button = button;
    c.disabledButton = button.darker(107);
    c.brightText = Qt::white;
    c.highlight = highlight;
    c.highlightedText = highlightedText;
    c.icon = text;
    c.disabledIcon = c.disabledText;
    c.unreadBadge = c.text;
    c.unreadBadgeText = c.highlightedText;
    c.chatTimestampText = c.base.lighter(160);
    break;
  }
  case Sakura: {
    QColor callout(156, 112, 160);
    QColor bright(252, 234, 243);
    QColor lessBright(242, 234, 237);
    QColor dimmer(255, 219, 250);
    QColor text(24, 18, 18);
    QColor disabledText(145, 140, 140);
    c.window = bright;
    c.highlight = callout;
    c.highlightedText = QColor(255, 255, 255);
    c.base = QColor(255, 247, 252);
    c.alternateBase = lessBright;
    c.button = dimmer;
    c.text = text;
    c.disabledText = disabledText;
    c.icon = QColor(120, 100, 112);
    c.disabledIcon = c.disabledText.lighter(125);
    c.unreadBadge = c.highlight;
    c.unreadBadgeText = c.highlightedText;
    c.chatTimestampText = c.base.darker(130);
    break;
  }
  }
  return themeColorsToPalette(c);
}

