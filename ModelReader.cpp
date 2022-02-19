#include "ModelReader.h"
#include <QDebug>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

ModelReader::ModelReader(QObject *parent) : QObject{parent} {}

void ModelReader::setFilePath(QString name) {
  if (name != m_filePath) {
    m_filePath = name;
    emit filePathChanged();
    readSTL();
  }
}

QString ModelReader::filePath() { return m_filePath; }

void ModelReader::setRenderItem(QQuickVTKRenderItem *item) {
  m_renderItem = item;
}

void ModelReader::readSTL() {
  if (this->m_filePath.isEmpty()) {
    return;
  }

  QString formatedPath = m_filePath.replace("file:///", "");
  auto reader = vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(qUtf8Printable(formatedPath));
  reader->Update();

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(reader->GetOutput());
  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  m_renderItem->renderer()->AddActor(actor);
  m_renderItem->renderer()->ResetCamera();
  m_actorList.append(actor);
}
