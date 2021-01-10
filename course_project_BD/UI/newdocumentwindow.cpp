#include "newdocumentwindow.h"
#include "ui_newdocumentwindow.h"

#include <QDebug>

#include "loggingcategories.h"

enum ERR {NAME, SURNAME, PATRONYMIC, AUTHORITY, BIRTH_PLACE, DEATH_PLACE,
          PARTNER_NAME, PARTNER_SURNAME, PARTNER_PATRONYMIC,
          WORK_PLACE, WORK_ORGANIZATION, WORK_POSITION,
          STUDY_PLACE, STUDY_ORGANIZATION, STUDY_SPECIALITY,
          RESIDENCE_REGION, RESIDENCE_STREET, RESIDENCE_LOCALITY,
          TIME_BASEDOC, TIME_BIRTH, TIME_DEATH, TIME_MARRIAGE, TIME_WORK, TIME_STUDY};

enum TYPE_DOCS {BASE, BIRTH, DEATH, MARRIAGE_START, MARRIAGE_END, WORK, STUDY, RESIDENCE};

void NewDocumentWindow::hideDocs()
{
    ui->gridLayout_birth->parentWidget()->hide();
    ui->gridLayout_death->parentWidget()->hide();
    ui->gridLayout_work->parentWidget()->hide();
    ui->gridLayout_study->parentWidget()->hide();
    ui->gridLayout_marriage->parentWidget()->hide();
    ui->gridLayout_residence->parentWidget()->hide();
}

void NewDocumentWindow::checkUI()
{
    if (!ui->lineEdit_surname->text().size())
        throw SURNAME;
    if (!ui->lineEdit_name->text().size())
        throw NAME;
    if (!ui->lineEdit_patronymic->text().size())
        throw PATRONYMIC;
    if (!ui->lineEdit_authority->text().size())
        throw AUTHORITY;
    if (ui->time_start->dateTime() > ui->time_end->dateTime() && !ui->checkBox_noendDoc->isChecked())
        throw TIME_BASEDOC;

    switch (ui->combo_typeDoc->currentIndex())
    {
    case BIRTH:
    {
        if (!ui->lineEdit_birthPlace->text().size())
            throw BIRTH_PLACE;
        if (ui->dateTimeEdit_birth->dateTime() > QDateTime::currentDateTime())
            throw TIME_BIRTH;
        break;
    }
    case DEATH:
    {
        if (!ui->lineEdit_deathPlace->text().size())
            throw BIRTH_PLACE;
        if (ui->dateTimeEdit_death->dateTime() > QDateTime::currentDateTime())
            throw TIME_DEATH;
        break;
    }
    case MARRIAGE_START:
    {
        if (!ui->lineEdit_partnerName)
            throw PARTNER_NAME;
        if (!ui->lineEdit_partnerSurname)
            throw PARTNER_SURNAME;
        if (!ui->lineEdit_partnerPatronymic)
            throw PARTNER_PATRONYMIC;
        if (ui->dateTimeEdit_marriageStart->dateTime() > QDateTime::currentDateTime())
            throw TIME_MARRIAGE;
        break;
    }
    case MARRIAGE_END:
    {
        if (!ui->lineEdit_partnerName)
            throw PARTNER_NAME;
        if (!ui->lineEdit_partnerSurname)
            throw PARTNER_SURNAME;
        if (!ui->lineEdit_partnerPatronymic)
            throw PARTNER_PATRONYMIC;
        if (ui->dateTimeEdit_marriageEnd->dateTime() > QDateTime::currentDateTime())
            throw TIME_MARRIAGE;
        break;
    }
    case WORK:
    {
        if (!ui->lineEdit_workPlace->text().size())
            throw WORK_PLACE;
        if (!ui->lineEdit_workPosition->text().size())
            throw WORK_POSITION;
        if (!ui->lineEdit_workOrganization->text().size())
            throw WORK_ORGANIZATION;
        if (ui->dateTimeEdit_workEnd->dateTime() < ui->dateTimeEdit_workStart->dateTime())
            throw TIME_WORK;
        break;
    }
    case STUDY:
    {
        if (!ui->lineEdit_studyPlace->text().size())
            throw STUDY_PLACE;
        if (!ui->lineEdit_studyOrganization->text().size())
            throw STUDY_ORGANIZATION;
        if (!ui->lineEdit_studySpeciality->text().size())
            throw STUDY_SPECIALITY;
        if (ui->dateTimeEdit_studyEnd->dateTime() < ui->dateTimeEdit_studyStart->dateTime())
            throw TIME_STUDY;
        break;
    }
    case RESIDENCE:
    {
        if (!ui->lineEdit_resRegion->text().size())
            throw RESIDENCE_REGION;
        if (!ui->lineEdit_resStreet->text().size())
            throw RESIDENCE_STREET;
        if (!ui->lineEdit_resLocality->text().size())
            throw RESIDENCE_LOCALITY;
        break;
    }
    }
}

NewDocumentWindow::NewDocumentWindow(DataFromGuiToBusiness *sender, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewDocumentWindow)
{
    ui->setupUi(this);
    this->sender = sender;

    ui->checkBox_otherDoc->hide();
    ui->lineEdit_newTypeDoc->hide();
    hideDocs();

    checkBox_personInDB = ui->checkBox_personInDB;
    lineEdit_surname = ui->lineEdit_surname;
    lineEdit_name = ui->lineEdit_name;
    lineEdit_patronymic = ui->lineEdit_patronymic;
    spinBox_numDoc= ui->spinBox_numDoc;
    spinBox_version = ui->spinBox_version;
    lineEdit_authority = ui->lineEdit_authority;
}

NewDocumentWindow::~NewDocumentWindow()
{
    delete ui;
}

void NewDocumentWindow::on_BtnReset_clicked()
{
    qDebug(logInfo()) << "Выход из окна добавления документа";
    this->close();
    emit openWindow();
}

bool NewDocumentWindow::on_BtnOk_clicked()
{
    bool res = false;
    try
    {
        checkUI();
        if (!sender->sendDataNewDoc(ui->tableWidget,
                               ui->lineEdit_patronymic,
                               ui->time_start,
                               ui->lineEdit_name,
                               ui->checkBox_personInDB,
                               ui->time_issuing,
                               ui->time_create,
                               ui->combo_sex,
                               ui->checkBox_noendDoc->isChecked() ? nullptr : ui->time_end,
                               ui->spinBox_idPerson,
                               ui->lineEdit_authority,
                               ui->combo_typeDoc,
                               ui->lineEdit_surname,
                               ui->spinBox_numDoc,
                               ui->spinBox_version,
                               ui->lineEdit_newTypeDoc,
                               ui->lineEdit_otherName,
                               ui->lineEdit_otherValue,
                               ui->combo_sexPartner,
                               ui->lineEdit_partnerSurname,
                               ui->lineEdit_partnerPatronymic,
                               ui->dateTimeEdit_marriageEnd,
                               ui->spinBox_idPartner,
                               ui->dateTimeEdit_marriageStart,
                               ui->lineEdit_partnerName,
                               ui->lineEdit_workPlace,
                               ui->dateTimeEdit_workStart,
                               ui->dateTimeEdit_workEnd,
                               ui->lineEdit_workOrganization,
                               ui->lineEdit_workPosition,
                               ui->spinBox_workSalary,
                               ui->lineEdit_studyOrganization,
                               ui->lineEdit_studySpeciality,
                               ui->dateTimeEdit_studyStart,
                               ui->lineEdit_studyPlace,
                               ui->dateTimeEdit_studyEnd,
                               ui->lineEdit_birthPlace,
                               ui->dateTimeEdit_birth,
                               ui->lineEdit_deathPlace,
                               ui->dateTimeEdit_death,
                               ui->combo_deathType,
                               ui->lineEdit_resRegion,
                               ui->lineEdit_resLocality,
                               ui->lineEdit_resStreet,
                               ui->spinBox_resHouse,
                               ui->spinBox_resBuilding,
                               ui->spinBox_resPorch,
                               ui->spinBox_resFlat,
                               ui->combo_resType,
                               ui->combo_resTypeLocality))

            throw "Error in datafromguitobusiness";

//        QMessageBox::information(this, "", "Документ успешно отправлен");
        res = true;
    }
    catch (ERR err)
    {
        QString str("Ошибка! Ошибка при вводе данных.");
        switch (err)
        {
        case NAME:
            str += " (NAME)";
            break;
        case SURNAME:
            str += " (SURNAME)";
            break;
        case PATRONYMIC:
            str += " (PATRONYMIC)";
            break;
        case AUTHORITY:
            str += " (AUTHORITY)";
            break;
        case BIRTH_PLACE:
            str += " (BIRTH_PLACE)";
            break;
        case DEATH_PLACE:
            str += " (DEATH_PLACE)";
            break;
        case PARTNER_NAME:
            str += " (PARTNER_NAME)";
            break;
        case PARTNER_SURNAME:
            str += " (PARTNER_SURNAME)";
            break;
        case PARTNER_PATRONYMIC:
            str += " (PARTNER_PATRONYMIC)";
            break;
        case WORK_PLACE:
            str += " (WORK_PLACE)";
            break;
        case WORK_ORGANIZATION:
            str += " (WORK_ORGANIZATION)";
            break;
        case WORK_POSITION:
            str += " (WORK_POSITION)";
            break;
        case STUDY_PLACE:
            str += " (STUDY_PLACE)";
            break;
        case STUDY_ORGANIZATION:
            str += " (STUDY_ORGANIZATION)";
            break;
        case STUDY_SPECIALITY:
            str += " (STUDY_SPECIALITY)";
            break;
        case RESIDENCE_REGION:
            str += " (RESIDENCE_REGION)";
            break;
        case RESIDENCE_STREET:
            str += " (RESIDENCE_STREET)";
            break;
        case RESIDENCE_LOCALITY:
            str += " (RESIDENCE_LOCALITY)";
            break;
        case TIME_BASEDOC:
            str += " (TIME_BASEDOC)";
            break;
        case TIME_BIRTH:
            str += " (TIME_BIRTH)";
            break;
        case TIME_DEATH:
            str += " (TIME_DEATH)";
            break;
        case TIME_MARRIAGE:
            str += " (TIME_MARRIAGE)";
            break;
        case TIME_WORK:
            str += " (TIME_WORK)";
            break;
        case TIME_STUDY:
            str += " (TIME_STUDY)";
            break;
        default:
            str+= " UNKNOWN UI_DATA!";
        }

        QMessageBox::critical(this, "", str);
        qDebug(logCritical()) << "Ошибка в UI";
    }
    catch (...)
    {
        QMessageBox::critical(this, "", "Ошибка! Ошибка при отправке документа.");
        qDebug(logCritical()) << "Ошибка в UI";
    }

    return res;
}

void NewDocumentWindow::on_checkBox_otherDoc_stateChanged(int checked)
{
    if (checked)
    {
        ui->combo_typeDoc->hide();
        ui->lineEdit_newTypeDoc->show();
        ui->gridLayout_baseDoc->removeWidget(ui->combo_typeDoc);
        ui->gridLayout_baseDoc->addWidget(ui->lineEdit_newTypeDoc, 1, 1);
        hideDocs();
    }
    else
    {
        on_combo_typeDoc_currentIndexChanged(ui->combo_typeDoc->currentIndex());
        ui->lineEdit_newTypeDoc->hide();
        ui->combo_typeDoc->show();
        ui->gridLayout_baseDoc->removeWidget(ui->lineEdit_newTypeDoc);
        ui->gridLayout_baseDoc->addWidget(ui->combo_typeDoc, 1, 1);
    }
}

void NewDocumentWindow::on_btn_addOtherAtribute_clicked()
{
    auto name = ui->lineEdit_otherName->text();
    auto value = ui->lineEdit_otherValue->text();

    if (!name.size() || !value.size())
    {
        QMessageBox::critical(this, "", "Error! Empty string.");
        return;
    }

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    QTableWidgetItem *pCellName = ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0);
    if(!pCellName)
    {
        pCellName = new QTableWidgetItem;
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, pCellName);
    }
    pCellName->setText(name);

    QTableWidgetItem *pCellValue = ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 1);
    if(!pCellValue)
    {
        pCellValue = new QTableWidgetItem;
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, pCellValue);
    }
    pCellValue->setText(value);
}

void NewDocumentWindow::on_tableWidget_itemSelectionChanged()
{
    QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    while (!selectedRows.empty())
    {
        ui->tableWidget->removeRow(selectedRows[0].row());
        selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    }
}

void NewDocumentWindow::on_checkBox_personInDB_stateChanged(int checked)
{
    ui->spinBox_idPerson->setEnabled(!checked);
}

void NewDocumentWindow::on_combo_typeDoc_currentIndexChanged(int index)
{
    switch(index)
    {
    case BASE:
    {
        hideDocs();
        break;
    }
    case BIRTH:
    {
        hideDocs();
        ui->gridLayout_birth->parentWidget()->show();
        break;
    }
    case DEATH:
    {
        hideDocs();
        ui->gridLayout_death->parentWidget()->show();
        break;
    }
    case MARRIAGE_START:
    {
        hideDocs();
        ui->gridLayout_marriage->parentWidget()->show();
        ui->label_dateTimeMarEnd->hide();
        ui->dateTimeEdit_marriageEnd->hide();
        ui->label_dateTimeMarStart->show();
        ui->dateTimeEdit_marriageStart->show();
        ui->combo_sexPartner->setCurrentIndex(ui->combo_sex->currentIndex() ? 0 : 1);
        break;
    }
    case MARRIAGE_END:
    {
        hideDocs();
        ui->gridLayout_marriage->parentWidget()->show();
        ui->label_dateTimeMarStart->hide();
        ui->dateTimeEdit_marriageStart->hide();
        ui->label_dateTimeMarEnd->show();
        ui->dateTimeEdit_marriageEnd->show();
        ui->combo_sexPartner->setCurrentIndex(ui->combo_sex->currentIndex() ? 0 : 1);
        break;
    }
    case WORK:
    {
        hideDocs();
        ui->gridLayout_work->parentWidget()->show();
        break;
    }
    case STUDY:
    {
        hideDocs();
        ui->gridLayout_study->parentWidget()->show();
        break;
    }
    case RESIDENCE:
    {
        hideDocs();
        ui->gridLayout_residence->parentWidget()->show();
        break;
    }
    default:
        qDebug() << "type of doc not found\n";
    }
}

void NewDocumentWindow::on_checkBox_noendDoc_stateChanged(int checked)
{
    ui->time_end->setEnabled(!checked);
}
