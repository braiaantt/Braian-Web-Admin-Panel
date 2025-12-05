#include "createproject.h"
#include "ui_createproject.h"
#include <QMessageBox>
#include "utils.h"

CreateProject::CreateProject(ServiceFactory *factory, QWidget *parent)
    : QDialog(parent), factory(factory)
    , ui(new Ui::CreateProject)
{
    ui->setupUi(this);
    init();
}

CreateProject::~CreateProject()
{
    delete ui;
}

//------ Initialization ------

void CreateProject::init()
{
    setWindowTitle("Crear Proyecto");
    projectService = factory->makeProjectService(this);
    connectSignalsAndSlots();
}

void CreateProject::connectSignalsAndSlots()
{
    connect(projectService, &ProjectService::projectCreated, this, &CreateProject::projectCreated);
    connect(projectService, &ProjectService::errorOcurred, this, &CreateProject::errorOcurred);
}

//------ Private Slots ------

void CreateProject::projectCreated(int id)
{
    project.setId(id);
    accept();
}

void CreateProject::errorOcurred(const QString &message)
{
    Utils::showWarning(this, message);
}

//------ UI Slots ------

void CreateProject::on_pushButtonSelectImage_clicked()
{
    QString coverPath = Utils::selectImageFile();

    if(coverPath.isEmpty())
        return;

    QPixmap pixmap(coverPath);
    ui->labelCover->setPixmap(pixmap);
    project.setCoverPath(coverPath);

}

void CreateProject::on_pushButtonAccept_clicked()
{
    if(!checkValues())
        return;

    setProjectValues(project);
    projectService->createProject(project);
}

//------ Helpers ------

bool CreateProject::checkValues()
{
    if(ui->lineEditName->text().isEmpty()){
        QMessageBox::warning(this, "Campo vacío", "El campo 'Nombre' no puede estar vacío!");
        return false;
    }

    if(ui->plainTextEditSmallAbout->toPlainText().isEmpty()){
        QMessageBox::warning(this, "Campo vacío", "El campo 'Descripción corta' no puede estar vacío!");
        return false;
    }

    if(ui->plainTextEditBigAbout->toPlainText().isEmpty()){
        QMessageBox::warning(this, "Campo vacío", "El campo 'Descripción larga' no puede estar vacío!");
        return false;
    }

    if(ui->plainTextEditMyComments->toPlainText().isEmpty()){
        QMessageBox::warning(this, "Campo vacío", "El campo 'Mis comentarios' no puede estar vacío!");
        return false;
    }

    return true;
}

void CreateProject::setProjectValues(Project &project)
{
    QString name = ui->lineEditName->text();
    QString smallAbout = ui->plainTextEditSmallAbout->toPlainText();
    QString bigAbout = ui->plainTextEditBigAbout->toPlainText();
    QString userComments = ui->plainTextEditMyComments->toPlainText();

    project.setName(name);
    project.setSmallAbout(smallAbout);
    project.setBigAbout(bigAbout);
    project.setUserComments(userComments);
}

//------ Getters ------

Project CreateProject::getProject() const {
    return project;
}
