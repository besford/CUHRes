/*
 * Class:       MainWindow
 * Purpose:     The purpose of this class is to provide the GUI
 *              for the CuNICS system.
 */

#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userorm.h"
#include "roleorm.h"
#include "employeecontrol.h"
#include "applyraisescontrol.h"
#include "cuhresparser.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), db(CunicsDb::db())
{
    QSqlError error;
    if ((error = db.initDb()).isValid()) {
        qWarning() << "test" << error.text();
    }
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //set the first page to the login window
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString userID = ui->lineEdit_ID->text(); //get the text entered by the user & assign it to the userID var

    QList<User*> userList = UserOrm::find(userID.toInt());
    if (userList.isEmpty()) {
        QMessageBox::warning(this, "login", "The user ID does not exist");
        return;
    }

    User* user = userList[0];
    if (user->getType() == "payroll_specialist") {
        QMessageBox::information(this, "login", "Login successful!"); //display this info
        ui->stackedWidget->setCurrentIndex(1);
    } else { //if employee
        QMessageBox::information(this, "login", "Login successful!"); //display this info
        ui->stackedWidget->setCurrentIndex(3);
    }

    delete user;
}

void MainWindow::on_pushButton_filter_clicked()
{
    QString filterParams = ui->lineEdit_filter->text();
    filterParams = "lname LIKE '%" + filterParams + "%'";
    QList<Employee*> filteredList = EmployeeOrm::filter(filterParams);
    QStandardItemModel* model = employeesToModel(filteredList);
    ui->employeesList->setModel(model);
    for (int i = 0; i < filteredList.size(); i++)
        delete filteredList[i];
}

void MainWindow::on_pushButton_loadTable_clicked()
{
    QList<Employee*> list = EmployeeOrm::all();
    QStandardItemModel* model = employeesToModel(list);
    QItemSelectionModel *oldModel = ui->employeesList->selectionModel();
    ui->employeesList->setModel(model);
    if (oldModel)
        delete oldModel;
    for (int i = 0; i < list.size(); i++)
        delete list[i];
}

void MainWindow::on_pushButton_logoutPS_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_addEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::on_pushButton_logoutEmployee_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_returnFromAddEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_logoutFromAddEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_employeesList_clicked(const QModelIndex &index)
{
    QString id = model->index(index.row(),0).data().toString(); //get content of cell
    QString role = model->index(index.row(), 2).data().toString();

    ui->stackedWidget->setCurrentIndex(5);

    selectedEmployeeId = id.toInt();

    updateDisplay(selectedEmployeeId, role);
}

void MainWindow::assignEmployeeParams(QHash<QString, QVariant> &params)
{
    params["fname"] = ui->lineEdit_firstNameEdit->text();
    params["lname"] = ui->lineEdit_lastNameEdit->text();
    params["role"] = getCurrentRole();

    if (!ui->lineEdit_hoursEdit->text().isEmpty()) {
        params["hours"] = ui->lineEdit_hoursEdit->text().toInt();
    }
    if (!ui->dateEdit_termFrom->text().isEmpty() && !ui->dateEdit_termTo->text().isEmpty()) {
        params["start_term"] = ui->dateEdit_termFrom->text();
        params["end_term"] = ui->dateEdit_termTo->text();
    }
    if (!ui->dateEdit_leaveFrom->text().isEmpty()) {
        params["start_leave"] = ui->dateEdit_leaveFrom->text();
    }
    if (!ui->dateEdit_leaveTo->text().isEmpty()) {
        params["end_leave"] = ui->dateEdit_leaveTo->text();
    }
    params["leave_percentage"] = ui->double_leavePerc->value();

    QString type;
    if (ui->radioButton_fullTime->isChecked()) {
        type = "full-time";
    } else if (ui->radioButton_partTime->isChecked()) {
        type = "part-time";
    } else if (ui->radioButton_term->isChecked()) {
        type = "term";
    } else if(ui->radioButton_continuing->isChecked()) {
        type = "continuing";
    }
    params["type"] = type;
}

void MainWindow::updateDisplayToRole(int employeeId, QString role)
{
    Employee *e = EmployeeOrm::find(employeeId).first();
    EmployeePosition* position = e->getPositionForRole(role);
    if (position) {
        ui->lineEdit_hoursEdit->setText(QString::number(position->getHours()));
        ui->label_wageAmount->setText("$" + QString::number(position->getWage()));
        ui->dateEdit_termFrom->setDate(QDate::fromString(position->getTerm().getSDate(), "yyyy-MM-dd"));
        ui->dateEdit_termTo->setDate(QDate::fromString(position->getTerm().getEDate(), "yyyy-MM-dd"));

        if(position->getRole() == "TA") {
            ui->radioButton_TA->setChecked(true);
        } else if(position->getRole() =="RA") {
            ui->radioButton_RA->setChecked(true);
        } else if(position->getRole() == "Staff") {
            ui->radioButton_staff->setChecked(true);
        } else if(position->getRole() == "Faculty") {
            ui->radioButton_faculty->setChecked(true);
        }

        if (position->getType() == "full-time") {
            ui->radioButton_fullTime->setChecked(true);
        } else if (position->getType() == "part-time") {
            ui->radioButton_partTime->setChecked(true);
        } else if (position->getType() == "term") {
            ui->radioButton_term->setChecked(true);
        } else if(position->getType() =="continuing") {
            ui->radioButton_continuing->setChecked(true);
        }
    } else {
        ui->lineEdit_hoursEdit->clear();
        ui->label_wageAmount->clear();
        ui->dateEdit_termFrom->setDate(QDate::currentDate());
        ui->dateEdit_termTo->setDate(QDate::currentDate());

        if(role == "TA") {
            ui->radioButton_TA->setChecked(true);
        } else if(role =="RA") {
            ui->radioButton_RA->setChecked(true);
        } else if(role == "Staff") {
            ui->radioButton_staff->setChecked(true);
        } else if(role == "Faculty") {
            ui->radioButton_faculty->setChecked(true);
        }

        ui->radioButton_fullTime->setChecked(false);
        ui->radioButton_partTime->setChecked(false);
        ui->radioButton_term->setChecked(false);
        ui->radioButton_continuing->setChecked(false);
    }
    updateEmployeeEditRestrictions(e, role);
    delete e;
}

QString MainWindow::getCurrentRole()
{
    QString role;
    if (ui->radioButton_TA->isChecked()) {
        role = "TA";
    } else if (ui->radioButton_RA->isChecked()) {
        role = "RA";
    } else if (ui->radioButton_faculty->isChecked()) {
        role = "Faculty";
    } else if(ui->radioButton_staff->isChecked()) {
        role = "Staff";
    }
    return role;
}

void MainWindow::updateDisplay(int employeeId, QString roleString)
{
    if (roleString.isEmpty()) {
        roleString = getCurrentRole();
    }
    Employee *e = EmployeeOrm::find(employeeId).first();
    ui->lineEdit_firstNameEdit->setText(e->getName().getFName());
    ui->lineEdit_lastNameEdit->setText(e->getName().getLName());
    ui->dateEdit_leaveFrom->setDate(QDate::fromString(e->getStartLeave(), "yyyy-MM-dd"));
    ui->dateEdit_leaveTo->setDate(QDate::fromString(e->getEndLeave(), "yyyy-MM-dd"));
    ui->double_leavePerc->setValue(e->getLeavePerc());
    updateDisplayToRole(employeeId, roleString);
    delete e;
}

void MainWindow::updateEmployeeEditRestrictions(Employee* e, QString role)
{
    EmployeePosition *position = e->getPositionForRole(role);
    QString type = "";
    if (position)
        type = position->getType();

    ui->radioButton_fullTime->setDisabled(false);
    ui->radioButton_partTime->setDisabled(false);
    ui->radioButton_term->setDisabled(false);
    ui->radioButton_continuing->setDisabled(false);
    ui->radioButton_TA->setDisabled(false);
    ui->radioButton_RA->setDisabled(false);
    ui->radioButton_staff->setDisabled(false);
    ui->radioButton_faculty->setDisabled(false);


    // type
    if (role == "Faculty") {
        ui->radioButton_partTime->setDisabled(true);
    } else if (role == "RA" || role == "TA") {
        ui->radioButton_fullTime->setDisabled(true);
        ui->radioButton_continuing->setDisabled(true);
    }

    // leave
    if (role != "Staff" && role != "Faculty" && type == "continuing") {
        ui->dateEdit_leaveFrom->setDisabled(true);
        ui->dateEdit_leaveTo->setDisabled(true);
    }

    // role
    if (role == "Staff" || role == "RA" || role == "TA") {
        ui->radioButton_faculty->setDisabled(true);
    } else if (role == "Faculty") {
        ui->radioButton_staff->setDisabled(true);
        ui->radioButton_RA->setDisabled(true);
        ui->radioButton_TA->setDisabled(true);
    }
}

QStandardItemModel* MainWindow::employeesToModel(QList<Employee*> &list)
{
    model = new QStandardItemModel(list.size(),9,this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Role")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Type")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Hours")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Wage")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Salary")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Start Date")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("End Date")));

    int entryRow = 0;
    for (int i=0; i<list.size(); i++)
    {
        Employee* employee = list[i];
        QList<EmployeePosition*> &positions = employee->getPositions();
        if (positions.size() == 0)
        {
            QStandardItem *id = new QStandardItem(QString::number(employee->getUID()));
            model->setItem(entryRow,0,id);
            const UserName &userName = employee->getName();
            QStandardItem *name = new QStandardItem(QString(userName.getFName() + " " + userName.getLName()));
            model->setItem(entryRow,1,name);
            entryRow++;
        }
        for (int j=0; j < positions.size(); j++) {
            EmployeePosition *position = positions[j];
            QStandardItem *id = new QStandardItem(QString::number(employee->getUID()));
            model->setItem(entryRow,0,id);
            const UserName &userName = employee->getName();
            QStandardItem *name = new QStandardItem(QString(userName.getFName() + " " + userName.getLName()));
            model->setItem(entryRow,1,name);
            QStandardItem *role = new QStandardItem(QString(position->getRole()));
            model->setItem(entryRow,2,role);
            QStandardItem *type = new QStandardItem(QString(position->getType()));
            model->setItem(entryRow,3,type);
            QStandardItem *hours = new QStandardItem(QString::number(position->getHours()));
            model->setItem(entryRow,4,hours);
            QStandardItem *wage = new QStandardItem(QString::number(position->getWage()));
            model->setItem(entryRow,5,wage);
            QStandardItem *salary = new QStandardItem(QString::number(position->calcSalary()));
            model->setItem(entryRow,6,salary);
            WorkTerm workTerm = position->getTerm();
            QStandardItem *startDate = new QStandardItem(QString(workTerm.getSDate()));
            model->setItem(entryRow,7,startDate);
            QStandardItem *endDate = new QStandardItem(QString(workTerm.getEDate()));
            model->setItem(entryRow,8,endDate);
            entryRow++;
        }
    }
    return model;
}

void MainWindow::on_pushButton_applyRaises_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_logoutFromEditEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_cancelEdit_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_cancelAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_cancelRaise_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->doubleSpinBox_raisePercentage->setEnabled(true);
    ui->doubleSpinBox_raiseAmount->setEnabled(true);
}


void MainWindow::on_pushButton_logoutFromApplyRaises_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_psHelp_clicked()
{
    QMessageBox::information(this, "help", "\nTo update the list of employees: click on 'Update Table'\n"
                                           "\nTo edit an employee: select the employee name from the table\n"
                                           "\nTo filter employees based on their last name:\n"
                                           "\nType the last name in the search box then hit 'Filter'\n"
                                           "\nTo apply a raise to an employee: click on 'Apply Raises'\n"); //display this info
}

void MainWindow::on_pushButton_psHelp_applyRaises_clicked()
{
    QMessageBox::information(this, "help", "\n1- Select the category of employees that you would like to apply a raise to\n"
                                           "\n2- Enter the raise amount in percentage OR fixed amount\n"
                                           "\n3- Click Apply\n"
                                           );
}

void MainWindow::on_pushButton_helpEditForm_clicked()
{
    QMessageBox::information(this, "help", "\nEnter your changes then click on 'save changes'\n"
                                           "\nTo return back to the Home Page: click on 'back'");
}

void MainWindow::on_stackedWidget_currentChanged(int index)
{
    if (index == 1) {
        QList<Employee*> list = EmployeeOrm::all();
        QStandardItemModel* model = employeesToModel(list);
        ui->employeesList->setModel(model);
        for (int i = 0; i < list.size(); i++)
            delete list[i];
    } else if (index == 2) {
        updateRaiseDisplay();
    }
}

void MainWindow::on_pushButton_saveEdit_clicked()
{
    QHash<QString, QVariant> params;
    assignEmployeeParams(params);

    EmployeeControl::updateEmployee(selectedEmployeeId, params);
    updateDisplay(selectedEmployeeId);
    QMessageBox::information(this, "Update", "Update successful!");
}

void MainWindow::on_pushButton_applyRaise_clicked()
{
    double raiseAmount = ui->doubleSpinBox_raiseAmount->value();
    double raisePercentage = ui->doubleSpinBox_raisePercentage->value();
    if (raiseAmount > 0 && raisePercentage > 100) {
        ui->doubleSpinBox_raiseAmount->setValue(0);
        ui->doubleSpinBox_raisePercentage->setValue(0);
        QMessageBox::warning(this, "Invalid Amount", "Select either amount or percentage, but not both.");
        return;
    }

    QString roleId;
    if (ui->radioButton_facultyRaise->isChecked()) {
        roleId = "Faculty";
    } else if (ui->radioButton_staffRaise->isChecked()) {
        roleId = "Staff";
    } else {
        QMessageBox::warning(this, "Invalid Role", "Select a role before performing a raise.");
        return;
    }

    double resultWage;
    if (raiseAmount > 0)
        resultWage = ApplyRaisesControl::applyRaise(roleId, raiseAmount, false);
    else
        resultWage = ApplyRaisesControl::applyRaise(roleId, raisePercentage, true);

    updateRaiseDisplay();
    QMessageBox::information(this, "Raise Success", "Raise of " + QString::number(resultWage) + " applied successfully.");
}

void MainWindow::updateRaiseDisplay()
{
    Role* facultyRole = RoleOrm::find("Faculty").first();
    Role* staffRole = RoleOrm::find("Staff").first();
    ui->label_facultyWage->setText("$" + QString::number(facultyRole->getWage()));
    ui->label_staffWage->setText("$" + QString::number(staffRole->getWage()));
    delete facultyRole;
    delete staffRole;
}

void MainWindow::on_radioButton_TA_clicked()
{
    updateDisplayToRole(selectedEmployeeId, "TA");
}

void MainWindow::on_radioButton_RA_clicked()
{
    updateDisplayToRole(selectedEmployeeId, "RA");
}

void MainWindow::on_radioButton_faculty_clicked()
{
    updateDisplayToRole(selectedEmployeeId, "Faculty");
}

void MainWindow::on_radioButton_staff_clicked()
{
    updateDisplayToRole(selectedEmployeeId, "Staff");
}

void MainWindow::on_pushButton_import_clicked()
{
    QString filter = "Cunics Files (*.cunics);; Text Files(*.txt);; All Files (*.*)";
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Import File"),
                QDir::homePath(),
                filter
            );
    if (!filename.isEmpty()) {
        ui->label_fileName->setText("File selected: " + filename);
        transactionFileName = filename;
    }
}

void MainWindow::on_pushButton_DataIntegrationTool_clicked()
{
   ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_cancel_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_backFromEdit_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_backFromRaises_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_backFromDit_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_createEmployee_clicked()
{

}

void MainWindow::on_pushButton_update_clicked()
{
    CuHRESParser parser;
    bool fileParsed = parser.parseTransactionFile(transactionFileName);
    if(fileParsed) {
        QMessageBox::information(this,tr("Transaction"),"Changes have been updated successfully!");

        /* clear transaction file selection on successful parse */
        ui->label_fileName->clear();
        transactionFileName = "";
    } else if (transactionFileName.isEmpty()) {
        QMessageBox::warning(this,tr("Transaction"),"No Transaction file selected. Please import one");
    } else {
        QMessageBox::warning(this,tr("Transaction"),"Errors found in the transaction file!");
    }
}
