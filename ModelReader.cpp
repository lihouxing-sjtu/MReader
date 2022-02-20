#include "ModelReader.h"
#include <QDebug>
#include <QRandomGenerator>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

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

  int r = QRandomGenerator::global()->bounded(0, 255);
  int g = QRandomGenerator::global()->bounded(0, 255);
  int b = QRandomGenerator::global()->bounded(0, 255);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(r / 255.0, g / 255.0, b / 255.0);

  m_renderItem->renderer()->AddActor(actor);
  m_renderItem->renderer()->ResetCamera();
  m_actorList.append(actor);
}
