#ifndef MODELREADER_H
#define MODELREADER_H

#include <QObject>
#include <QQuickVTKRenderItem.h>
#include <vtkSTLReader.h>

class ModelReader : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
public:
  explicit ModelReader(QObject *parent = nullptr);

  void setFilePath(QString name);
  QString filePath();

  void setRenderItem(QQuickVTKRenderItem *item);

private:
  QString m_filePath;
  QQuickVTKRenderItem *m_renderItem;
  QList<vtkSmartPointer<vtkActor>> m_actorList;

protected:
  void readSTL();

signals:
  void filePathChanged();
};

#endif // MODELREADER_H
