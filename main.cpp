#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQuickVTKRenderItem.h>
#include <QQuickVTKRenderWindow.h>
#include <QTranslator>
#include <vtkActor.h>
#include <vtkAutoInit.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
static QQuickVTKRenderItem *gViewRender = NULL;

int main(int argc, char *argv[]) {
  QQuickVTKRenderWindow::setupGraphicsBackend();
  QGuiApplication app(argc, argv);

  qmlRegisterType<QQuickVTKRenderWindow>("VTKPLUS", 9, 1, "VTKRenderWindow");
  qmlRegisterType<QQuickVTKRenderItem>("VTKPLUS", 9, 1, "VTKRenderItem");

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/MReader/main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                   [url](QObject *obj, const QUrl &objUrl) {
                     if (!obj && url == objUrl)
                       QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);
  engine.load(url);

  QObject *topLevel = engine.rootObjects().value(0);

  // Fetch the QQuick window using the standard object name set up in the
  // constructor
  auto *viewObj = topLevel->findChild<QObject *>("view");
  auto *qquickObject = viewObj->findChild<QObject *>("ConeView");
  gViewRender = dynamic_cast<QQuickVTKRenderItem *>(qquickObject);

  // set background
  gViewRender->renderer()->SetBackground(0.9, 0.7, 0.7);
  gViewRender->renderer()->SetBackground2(0.3, 0.2, 0.1);
  gViewRender->renderer()->SetGradientBackground(true);
  gViewRender->update();

  return app.exec();
}
