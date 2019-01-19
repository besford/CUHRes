#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cunicsdb.h"
#include "employeeorm.h"
#include "QStandardItemModel"
#include "employeeorm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_loadTable_clicked();

    void on_pushButton_logoutPS_clicked();

    void on_pushButton_addEmployee_clicked();

    void on_pushButton_logoutEmployee_clicked();

    void on_pushButton_returnFromAddEmployee_clicked();

    void on_pushButton_logoutFromAddEmployee_clicked();

    void on_pushButton_filter_clicked();

    void on_employeesList_clicked(const QModelIndex &index);

    void on_pushButton_applyRaises_clicked();

    void on_pushButton_logoutFromEditEmployee_clicked();

    void on_pushButton_cancelEdit_clicked();

    void on_pushButton_cancelAdd_clicked();

    void on_pushButton_cancelRaise_clicked();

    void on_pushButton_logoutFromApplyRaises_clicked();

    void on_pushButton_psHelp_clicked();

    void on_pushButton_psHelp_applyRaises_clicked();

    void on_pushButton_helpEditForm_clicked();

    void on_stackedWidget_currentChanged(int);

    void on_pushButton_saveEdit_clicked();

    void on_pushButton_applyRaise_clicked();

    void on_radioButton_TA_clicked();

    void on_radioButton_RA_clicked();

    void on_radioButton_faculty_clicked();

    void on_radioButton_staff_clicked();

    void on_pushButton_import_clicked();

    void on_pushButton_DataIntegrationTool_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_backFromEdit_clicked();

    void on_pushButton_backFromRaises_clicked();

    void on_pushButton_backFromDit_clicked();

    void on_pushButton_createEmployee_clicked();

    void on_pushButton_update_clicked();

private:
    CunicsDb& db;
    Ui::MainWindow* ui;
    QStandardItemModel* employeesToModel(QList<Employee*>&);
    QStandardItemModel* model;
    int selectedEmployeeId;
    QString transactionFileName;
    void updateDisplay(int, QString = "");
    void updateDisplayToRole(int, QString);
    void assignEmployeeParams(QHash<QString, QVariant> &params);
    void updateRaiseDisplay();
    void updateEmployeeEditRestrictions(Employee*, QString);
    QString getCurrentRole();
};

#endif // MAINWINDOW_H
