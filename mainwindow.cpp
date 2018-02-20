#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMainWindow::showMaximized();

    ui->textEdit->setAlignment(Qt::AlignHCenter);
    ui->textEdit_2->setAlignment(Qt::AlignHCenter);

    ui->tableWidget->setColumnWidth(1, 22);
    ui->tableWidget->setColumnWidth(4, 22);
    ui->tableWidget->setColumnWidth(7, 22);
    ui->tableWidget->setColumnWidth(10, 22);\
    ui->tableWidget->setColumnWidth(13, 22);


/*  ui->spinBox_3->setPrefix(QString::fromUtf8("\u00b1"));
    ui->spinBox_4->setPrefix(QString::fromUtf8("\u00b1"));
    ui->spinBox_5->setPrefix(QString::fromUtf8("\u00b1"));
    ui->spinBox_6->setPrefix(QString::fromUtf8("\u00b1"));
    ui->spinBox_7->setPrefix(QString::fromUtf8("\u00b1"));*/


    time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

    connect(ui->checkBoxTimerON, SIGNAL(clicked(bool)), this, SLOT(on_checkBoxTimerON_checked(bool)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_2_valueChanged()));
    connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(on_radiobutton_toggled(bool)));
    connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(on_radiobutton_2_toggled(bool)));


    //////////////////  CHECKBOX    ///////////////////////

    for(int i=0; i < 89; i++)
    {
        pLayout[i] = new QHBoxLayout;
        pWidget[i] = new QWidget;

        pLayout[i]->setAlignment(Qt::AlignCenter);
        pLayout[i]->setContentsMargins(0,0,0,0);
        pWidget[i]->setLayout(pLayout[i]);
    }

    checkboxFZED1 = new QCheckBox();
    pLayout[0]->addWidget(checkboxFZED1);
    ui->tableWidget->setCellWidget(0, 1, pWidget[0]);

    connect(checkboxFZED1, SIGNAL(clicked(bool)), this, SLOT(on_checkboxFZED1_checked(bool)));

    checkboxFZED2 = new QCheckBox();
    pLayout[1]->addWidget(checkboxFZED2);
    ui->tableWidget->setCellWidget(1, 1, pWidget[1]);

    connect(checkboxFZED2, SIGNAL(clicked(bool)), this, SLOT(on_checkboxFZED2_checked(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
    if(trc.iterator205h > 0)
        trc.iterator205h--;
    else
        QMessageBox::information(this, "", "Nie ma już poprzednich ramek 205h");

    if(trc.iterator185h > 0)
        trc.iterator185h--;
    else
        QMessageBox::information(this, "", "Nie ma już poprzednich ramek 185h");

    if(trc.iterator285h > 0)
        trc.iterator285h--;
    else
        QMessageBox::information(this, "", "Nie ma już poprzednich ramek 285h");

    if(trc.iterator385h > 0)
        trc.iterator385h--;
    else
        QMessageBox::information(this, "", "Nie ma już poprzednich ramek 385h");

    if(trc.iterator485h > 0)
        trc.iterator485h--;
    else
        QMessageBox::information(this, "", "Nie ma już poprzednich ramek 485h");

    showValues(trc.iterator185h, trc.iterator285h, trc.iterator385h, trc.iterator485h, trc.iterator205h);

    ui->spinBox_2->setValue(trc.iterator185h);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(trc.iterator205h < trc.list205h.size())
        trc.iterator205h++;
    else
        QMessageBox::information(this, "", "Nie ma już więcej ramek 205h");

    if(trc.iterator185h < trc.list185h.size())
        trc.iterator185h++;
    else
        QMessageBox::information(this, "", "Nie ma już więcej ramek 185h");

    if(trc.iterator285h < trc.list285h.size())
        trc.iterator285h++;
    else
        QMessageBox::information(this, "", "Nie ma już więcej ramek 285h");

    if(trc.iterator385h < trc.list385h.size())
        trc.iterator385h++;
    else
        QMessageBox::information(this, "", "Nie ma już więcej ramek 385h");

    if(trc.iterator485h < trc.list485h.size())
        trc.iterator485h++;
    else
        QMessageBox::information(this, "", "Nie ma już więcej ramek 485h");

    showValues(trc.iterator185h, trc.iterator285h, trc.iterator385h, trc.iterator485h, trc.iterator205h);

    ui->spinBox_2->setValue(trc.iterator185h);
}

void MainWindow::on_pushButton_3_clicked()
{
    trc.iterator185h = 0;
    trc.iterator285h = 0;
    trc.iterator385h = 0;
    trc.iterator485h = 0;
    trc.iterator205h = 0;

    showValues(trc.iterator185h, trc.iterator285h, trc.iterator385h, trc.iterator485h, trc.iterator205h);
}

void MainWindow::on_pushButton_4_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Open the file");
    trc.openFile(filePath);

    ui->textEdit_3->setText(filePath);
    ui->spinBox->setEnabled(true);
    ui->checkBoxTimerON->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->lineEdit->setText(QString::number(trc.list185h.size()));
    ui->lineEdit_2->setText(QString::number(trc.list285h.size()));
    ui->lineEdit_3->setText(QString::number(trc.list385h.size()));
    ui->lineEdit_4->setText(QString::number(trc.list485h.size()));
    ui->lineEdit_5->setText(QString::number(trc.list205h.size()));

    showValues(trc.iterator185h, trc.iterator285h, trc.iterator385h, trc.iterator485h, trc.iterator205h);
}

void MainWindow::on_radiobutton_toggled(bool checked)
{
    if(checked)
    {
        ui->progressBar->reset();

        ui->progressBar->setMaximum(trc.list185h.size());
        ui->progressBar->setValue(trc.iterator185h);
    }
}

void MainWindow::on_radiobutton_2_toggled(bool checked)
{
    if(checked)
    {
        ui->progressBar->reset();
        ui->progressBar->setMaximum(ui->spinBox->value());
    }
}

void MainWindow::timerTimeout()
{
    if(time == ui->spinBox->value())
    {
        if(trc.iterator205h < trc.list205h.size())
            trc.iterator205h++;
        else
            QMessageBox::information(this, "", "Nie ma już więcej ramek 205h");

        if(trc.iterator185h < trc.list185h.size())
            trc.iterator185h++;
        else
            QMessageBox::information(this, "", "Nie ma już więcej ramek 185h");

        if(trc.iterator285h < trc.list285h.size())
            trc.iterator285h++;
        else
            QMessageBox::information(this, "", "Nie ma już więcej ramek 285h");

        if(trc.iterator385h < trc.list385h.size())
            trc.iterator385h++;
        else
            QMessageBox::information(this, "", "Nie ma już więcej ramek 385h");

        if(trc.iterator485h < trc.list485h.size())
            trc.iterator485h++;
        else
            QMessageBox::information(this, "", "Nie ma już więcej ramek 485h");

        showValues(trc.iterator185h, trc.iterator285h, trc.iterator385h, trc.iterator485h, trc.iterator205h);

        ui->spinBox_2->setValue(trc.iterator185h);

        if(ui->radioButton_2->isChecked())
            ui->progressBar->reset();

        time = 0;
    }

    else
    {
        time++;

        if(ui->radioButton_2->isChecked())
            ui->progressBar->setValue(time);
    }

}

void MainWindow::on_checkBoxTimerON_checked(bool checked)
{
    if(checked)
    {
        if(ui->radioButton_2->isChecked())
            ui->progressBar->setMaximum(ui->spinBox->value());

        timer->start(1);
    }

    else
    {
        time = 0;
        timer->start();  // starts resets timer if it's already running
        timer->stop();

        if(ui->radioButton_2->isChecked())
            ui->progressBar->reset();
    }
}


void MainWindow::on_spinBox_2_valueChanged()
{
    if(ui->spinBox_2->hasFocus())
    {
        if(trc.list185h.size() >= ui->spinBox_2->value())
            trc.iterator185h = ui->spinBox_2->value();

        if(trc.list285h.size() >= ui->spinBox_2->value())
            trc.iterator285h = ui->spinBox_2->value();

        if(trc.list385h.size() >= ui->spinBox_2->value())
            trc.iterator385h = ui->spinBox_2->value();

        if(trc.list485h.size() >= ui->spinBox_2->value())
            trc.iterator485h = ui->spinBox_2->value();

        if(trc.list205h.size() >= ui->spinBox_2->value())
            trc.iterator205h = ui->spinBox_2->value();

        showValues(trc.iterator185h, trc.iterator285h, trc.iterator385h, trc.iterator485h, trc.iterator205h);
    }
}

void MainWindow::on_checkboxFZED1_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxFZED2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxA_MH_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxZAL_HAMULCA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxWH_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxWH_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxWH_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
        QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxOJ_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxMC_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxMC_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxMC_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxMZ_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxMG_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxStHEP_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxMASA_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxMASA_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxMASA_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMC_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMCp_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMZR_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMW_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMC_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMCp_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMZR_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMW_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWCANRS_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWCANRS_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWCANRS_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxOGRV_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMC_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMCp_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMZR_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMW_S_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWCAN_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWCAN_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxERRSTKA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxERRSTKB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxERRSTNS_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxRA_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxRB_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxRA_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxRB_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxRAB_A_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxRAB_B_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxbrWYBORU_TK_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxbrWYBORU_TT_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxMED_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxEP_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxPN_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxPS_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxTW_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAK2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxzeroJ_TK_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxGm_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxCd_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxzeroSHP_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxzeroRS_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxSG_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxzeroJ_1_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxzeroJ_2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxzeroJ_3_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxzeroJ_4_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxzeroJ_5_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxzeroJ_6_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}




void MainWindow::on_checkboxzeroJ_7_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWMZ_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWMGp_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWMG_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWMHS_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMC_KA_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMZ_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMGp_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMG_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}

void MainWindow::on_checkboxAWMHS_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWMC_KB_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxFRED1_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxFRED2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxV_POJAZDU_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxED1_ZAL_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxED2_ZAL_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxMED_SNP_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxPOSL_N_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxStHEP_SL_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWYp_A1_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWYp_A2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWYp_B1_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWYp_B2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



void MainWindow::on_checkboxAWYp_S1_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}


void MainWindow::on_checkboxAWYp_S2_checked(bool checked)
{
    if(checked)
        QMessageBox::information(this, "", "zaznaczono");
    else
         QMessageBox::information(this, "", "odznaczono");
}



QString MainWindow::getFilePath()
{
    return filePath;
}

void MainWindow::showValues(int indexFrame185, int indexFrame285, int indexFrame385, int indexFrame485, int indexFrame205)
{
    ui->textEdit->setText(trc.frameDateTime[indexFrame185]);
//    ui->textEdit->setText(trc.debuger[indexFrame185]);
    ui->textEdit_2->setText(QString(QString::number(trc.messageNumbers185[indexFrame185]) + ", "
                                              + QString::number(trc.messageNumbers285[indexFrame285]) + ", "
                                              + QString::number(trc.messageNumbers385[indexFrame385]) + ", "
                                              + QString::number(trc.messageNumbers485[indexFrame485]) + ", "
                                              + QString::number(trc.messageNumbers205[indexFrame205])));


    QTableWidgetItem *protoItem = new QTableWidgetItem();
    protoItem->setTextAlignment(Qt::AlignCenter);


    ////////////////////////    185h    /////////////////////////////

    QTableWidgetItem *FZED1_Item = protoItem->clone();
    FZED1_Item->setText(QString::number(trc.FZED1[indexFrame185]));
    ui->tableWidget->setItem(0, 2, FZED1_Item);

    QTableWidgetItem *FZED2_Item = protoItem->clone();
    FZED2_Item->setText(QString::number(trc.FZED2[indexFrame185]));
    ui->tableWidget->setItem(1, 2, FZED2_Item);

    QTableWidgetItem *A_MH_Item = protoItem->clone();
    A_MH_Item->setText(QString::number(trc.A_MH[indexFrame185]));
    ui->tableWidget->setItem(2, 2, A_MH_Item);

    QTableWidgetItem *ZAL_HAMULCA_Item = protoItem->clone();
    ZAL_HAMULCA_Item->setText(QString::number(trc.ZAL_HAMULCA[indexFrame185]));
    ui->tableWidget->setItem(3, 2, ZAL_HAMULCA_Item);

    QTableWidgetItem *WH_A_Item = protoItem->clone();
    WH_A_Item->setText(QString::number(trc.WH_A[indexFrame185]));
    ui->tableWidget->setItem(4, 2, WH_A_Item);

    QTableWidgetItem *WH_B_Item = protoItem->clone();
    WH_B_Item->setText(QString::number(trc.WH_B[indexFrame185]));
    ui->tableWidget->setItem(5, 2, WH_B_Item);

    QTableWidgetItem *WH_S_Item = protoItem->clone();
    WH_S_Item->setText(QString::number(trc.WH_S[indexFrame185]));
    ui->tableWidget->setItem(6, 2, WH_S_Item);

    QTableWidgetItem *zeroJ_Item = protoItem->clone();
    zeroJ_Item->setText(QString::number(trc.zeroJ[indexFrame185]));
    ui->tableWidget->setItem(7, 2, zeroJ_Item);

    QTableWidgetItem *MCA_Item = protoItem->clone();
    MCA_Item->setText(QString::number(trc.MCA[indexFrame185]));
    ui->tableWidget->setItem(8, 2, MCA_Item);

    QTableWidgetItem *MCB_Item = protoItem->clone();
    MCB_Item->setText(QString::number(trc.MCB[indexFrame185]));
    ui->tableWidget->setItem(9, 2, MCB_Item);

    QTableWidgetItem *MCS_Item = protoItem->clone();
    MCS_Item->setText(QString::number(trc.MCS[indexFrame185]));
    ui->tableWidget->setItem(10, 2, MCS_Item);


    ////////////////////////    285h    /////////////////////////////

    QTableWidgetItem *MASA_A_Item = protoItem->clone();
    MASA_A_Item->setText(QString::number(trc.MASA_A[indexFrame285]));
    ui->tableWidget->setItem(0, 5, MASA_A_Item);

    QTableWidgetItem *MASA_B_Item = protoItem->clone();
    MASA_B_Item->setText(QString::number(trc.MASA_B[indexFrame285]));
    ui->tableWidget->setItem(1, 5, MASA_B_Item);


    QTableWidgetItem *MASA_S_Item = protoItem->clone();
    MASA_S_Item->setText(QString::number(trc.MASA_S[indexFrame285]));
    ui->tableWidget->setItem(2, 5, MASA_S_Item);


    QTableWidgetItem *AWMC_B_Item = protoItem->clone();
    AWMC_B_Item->setText(QString::number(trc.AWMC_B[indexFrame285]));
    ui->tableWidget->setItem(3, 5, AWMC_B_Item);


    QTableWidgetItem *AWMCp_B_Item = protoItem->clone();
    AWMCp_B_Item->setText(QString::number(trc.AWMCp_B[indexFrame285]));
    ui->tableWidget->setItem(4, 5, AWMCp_B_Item);


    QTableWidgetItem *AWMZR_B_Item = protoItem->clone();
    AWMZR_B_Item->setText(QString::number(trc.AWMZR_B[indexFrame285]));
    ui->tableWidget->setItem(5, 5, AWMZR_B_Item);


    QTableWidgetItem *AWMW_B_Item = protoItem->clone();
    AWMW_B_Item->setText(QString::number(trc.AWMW_B[indexFrame285]));
    ui->tableWidget->setItem(6, 5, AWMW_B_Item);


    QTableWidgetItem *AWMC_A_Item = protoItem->clone();
    AWMC_A_Item->setText(QString::number(trc.AWMC_A[indexFrame285]));
    ui->tableWidget->setItem(7, 5, AWMC_A_Item);


    QTableWidgetItem *AWMCp_A_Item = protoItem->clone();
   AWMCp_A_Item->setText(QString::number(trc.AWMCp_A[indexFrame285]));
    ui->tableWidget->setItem(8, 5, AWMCp_A_Item);


    QTableWidgetItem *AWMZR_A_Item = protoItem->clone();
    AWMZR_A_Item->setText(QString::number(trc.AWMZR_A[indexFrame285]));
    ui->tableWidget->setItem(9, 5, AWMZR_A_Item);


    QTableWidgetItem *AWMW_A_Item = protoItem->clone();
    AWMW_A_Item->setText(QString::number(trc.AWMW_A[indexFrame285]));
    ui->tableWidget->setItem(10, 5, AWMW_A_Item);


    QTableWidgetItem *AWCANRS_S_Item = protoItem->clone();
    AWCANRS_S_Item->setText(QString::number(trc.AWCANRS_S[indexFrame285]));
    ui->tableWidget->setItem(11, 5, AWCANRS_S_Item);


    QTableWidgetItem *AWCANRS_B_Item = protoItem->clone();
    AWCANRS_B_Item->setText(QString::number(trc.AWCANRS_B[indexFrame285]));
    ui->tableWidget->setItem(12, 5, AWCANRS_B_Item);

    QTableWidgetItem *AWCANRS_A_Item = protoItem->clone();
    AWCANRS_A_Item->setText(QString::number(trc.AWCANRS_A[indexFrame285]));
    ui->tableWidget->setItem(13, 5, AWCANRS_A_Item);



    QTableWidgetItem *OGR_V_Item = protoItem->clone();
    OGR_V_Item->setText(QString::number(trc.OGR_V[indexFrame285]));
    ui->tableWidget->setItem(14, 5, OGR_V_Item);


    QTableWidgetItem *AWMC_S_Item = protoItem->clone();
    AWMC_S_Item->setText(QString::number(trc.AWMC_S[indexFrame285]));
    ui->tableWidget->setItem(15, 5, AWMC_S_Item);


    QTableWidgetItem *AWMCp_S_Item = protoItem->clone();
    AWMCp_S_Item->setText(QString::number(trc.AWMCp_S[indexFrame285]));
    ui->tableWidget->setItem(16, 5, AWMCp_S_Item);


    QTableWidgetItem *AWMZR_S_Item = protoItem->clone();
    AWMZR_S_Item->setText(QString::number(trc.AWMZR_S[indexFrame285]));
    ui->tableWidget->setItem(17, 5, AWMZR_S_Item);


    QTableWidgetItem *AWMW_S_Item = protoItem->clone();
    AWMW_S_Item->setText(QString::number(trc.AWMW_S[indexFrame285]));
    ui->tableWidget->setItem(18, 5, AWMW_S_Item);




    ////////////////////////    385h    /////////////////////////////

    QTableWidgetItem *MZ_Item = protoItem->clone();
    MZ_Item->setText(QString::number(trc.MZ[indexFrame385]));
    ui->tableWidget->setItem(12, 2, MZ_Item);

    QTableWidgetItem *MG_Item = protoItem->clone();
    MG_Item->setText(QString::number(trc.MG[indexFrame385]));
    ui->tableWidget->setItem(13, 2, MG_Item);

    QTableWidgetItem *StHEP_Item = protoItem->clone();
    StHEP_Item->setText(QString::number(trc.StHEP[indexFrame385]));
    ui->tableWidget->setItem(14, 2, StHEP_Item);



    ////////////////////////    485h    /////////////////////////////

    QTableWidgetItem *zeroJ_TK_Item = protoItem->clone();
    zeroJ_TK_Item->setText(QString::number(trc.zeroJ_TK[indexFrame485]));
    ui->tableWidget->setItem(0, 11, zeroJ_TK_Item);


    QTableWidgetItem *Gm_Item = protoItem->clone();
    Gm_Item->setText(QString::number(trc.Gm[indexFrame485]));
    ui->tableWidget->setItem(1, 11, Gm_Item);


    QTableWidgetItem *Cd_Item = protoItem->clone();
    Cd_Item->setText(QString::number(trc.Cd[indexFrame485]));
    ui->tableWidget->setItem(2, 11, Cd_Item);


    QTableWidgetItem *zeroSHP_Item = protoItem->clone();
    zeroSHP_Item->setText(QString::number(trc.zeroSHP[indexFrame485]));
    ui->tableWidget->setItem(3, 11, zeroSHP_Item);


    QTableWidgetItem *zeroRS_Item = protoItem->clone();
    zeroRS_Item->setText(QString::number(trc.zeroRS[indexFrame485]));
    ui->tableWidget->setItem(4, 11, zeroRS_Item);


    QTableWidgetItem *SG_Item = protoItem->clone();
    SG_Item->setText(QString::number(trc.SG[indexFrame485]));
    ui->tableWidget->setItem(5, 11, SG_Item);


    QTableWidgetItem *zeroJ_1_Item = protoItem->clone();
    zeroJ_1_Item->setText(QString::number(trc.zeroJ_1[indexFrame485]));
    ui->tableWidget->setItem(6, 11, zeroJ_1_Item);


    QTableWidgetItem *zeroJ_2_Item = protoItem->clone();
    zeroJ_2_Item->setText(QString::number(trc.zeroJ_2[indexFrame485]));
    ui->tableWidget->setItem(7, 11, zeroJ_2_Item);


    QTableWidgetItem *zeroJ_3_Item = protoItem->clone();
    zeroJ_3_Item->setText(QString::number(trc.zeroJ_3[indexFrame485]));
    ui->tableWidget->setItem(8, 11, zeroJ_3_Item);


    QTableWidgetItem *zeroJ_4_Item = protoItem->clone();
    zeroJ_4_Item->setText(QString::number(trc.zeroJ_4[indexFrame485]));
    ui->tableWidget->setItem(9, 11, zeroJ_4_Item);


    QTableWidgetItem *zeroJ_5_Item = protoItem->clone();
    zeroJ_5_Item->setText(QString::number(trc.zeroJ_5[indexFrame485]));
    ui->tableWidget->setItem(10, 11, zeroJ_5_Item);


    QTableWidgetItem *zeroJ_6_Item = protoItem->clone();
    zeroJ_6_Item->setText(QString::number(trc.zeroJ_6[indexFrame485]));
    ui->tableWidget->setItem(11, 11, zeroJ_6_Item);


    QTableWidgetItem *zeroJ_7_Item = protoItem->clone();
    zeroJ_7_Item->setText(QString::number(trc.zeroJ_7[indexFrame485]));
    ui->tableWidget->setItem(12, 11, zeroJ_7_Item);


    QTableWidgetItem *AWMZ_KA_Item = protoItem->clone();
    AWMZ_KA_Item->setText(QString::number(trc.AWMZ_KA[indexFrame485]));
    ui->tableWidget->setItem(13, 11, AWMZ_KA_Item);


    QTableWidgetItem *AWMGp_KA_Item = protoItem->clone();
    AWMGp_KA_Item->setText(QString::number(trc.AWMGp_KA[indexFrame485]));
    ui->tableWidget->setItem(14, 11, AWMGp_KA_Item);


    QTableWidgetItem *AWMG_KA_Item = protoItem->clone();
    AWMG_KA_Item->setText(QString::number(trc.AWMG_KA[indexFrame485]));
    ui->tableWidget->setItem(15, 11, AWMG_KA_Item);


    QTableWidgetItem *AWMHS_KA_Item = protoItem->clone();
    AWMHS_KA_Item->setText(QString::number(trc.AWMHS_KA[indexFrame485]));
    ui->tableWidget->setItem(16, 11, AWMHS_KA_Item);


    QTableWidgetItem *AWMC_KA_Item = protoItem->clone();
    AWMC_KA_Item->setText(QString::number(trc.AWMC_KA[indexFrame485]));
    ui->tableWidget->setItem(17, 11, AWMC_KA_Item);


    QTableWidgetItem *AWMZ_KB_Item = protoItem->clone();
    AWMZ_KB_Item->setText(QString::number(trc.AWMZ_KB[indexFrame485]));
    ui->tableWidget->setItem(18, 11, AWMZ_KB_Item);


    QTableWidgetItem *AWMGp_KB_Item = protoItem->clone();
    AWMGp_KB_Item->setText(QString::number(trc.AWMGp_KB[indexFrame485]));
    ui->tableWidget->setItem(19, 11, AWMGp_KB_Item);


    QTableWidgetItem *AWMG_KB_Item = protoItem->clone();
    AWMG_KB_Item->setText(QString::number(trc.AWMG_KB[indexFrame485]));
    ui->tableWidget->setItem(20, 11, AWMG_KB_Item);


    QTableWidgetItem *AWMHS_KB_Item = protoItem->clone();
    AWMHS_KB_Item->setText(QString::number(trc.AWMHS_KB[indexFrame485]));
    ui->tableWidget->setItem(21, 11, AWMHS_KB_Item);



    QTableWidgetItem *AWMC_KB_Item = protoItem->clone();
    AWMC_KB_Item->setText(QString::number(trc.AWMC_KB[indexFrame485]));
    ui->tableWidget->setItem(22, 11, AWMC_KB_Item);


    QTableWidgetItem *AWYp_A1_Item = protoItem->clone();
    AWYp_A1_Item->setText(QString::number(trc.AWYp_A1[indexFrame485]));
    ui->tableWidget->setItem(9, 14, AWYp_A1_Item);


    QTableWidgetItem *AWYp_A2_Item = protoItem->clone();
    AWYp_A2_Item->setText(QString::number(trc.AWYp_A2[indexFrame485]));
    ui->tableWidget->setItem(10, 14, AWYp_A2_Item);


    QTableWidgetItem *AWYp_B1_Item = protoItem->clone();
    AWYp_B1_Item->setText(QString::number(trc.AWYp_B1[indexFrame485]));
    ui->tableWidget->setItem(11, 14, AWYp_B1_Item);


    QTableWidgetItem *AWYp_B2_Item = protoItem->clone();
    AWYp_B2_Item->setText(QString::number(trc.AWYp_B2[indexFrame485]));
    ui->tableWidget->setItem(12, 14, AWYp_B2_Item);


    QTableWidgetItem *AWYp_S1_Item = protoItem->clone();
    AWYp_S1_Item->setText(QString::number(trc.AWYp_S1[indexFrame485]));
    ui->tableWidget->setItem(13, 14, AWYp_S1_Item);


    QTableWidgetItem *AWYp_S2_Item = protoItem->clone();
    AWYp_S2_Item->setText(QString::number(trc.AWYp_S2[indexFrame485]));
    ui->tableWidget->setItem(14, 14, AWYp_S2_Item);


    QTableWidgetItem *AWCAN_KA_Item = protoItem->clone();
    AWCAN_KA_Item->setText(QString::number(trc.AWCAN_KA[indexFrame485]));
    ui->tableWidget->setItem(0, 8, AWCAN_KA_Item);


    QTableWidgetItem *AWCAN_KB_Item = protoItem->clone();
    AWCAN_KB_Item->setText(QString::number(trc.AWCAN_KB[indexFrame485]));
    ui->tableWidget->setItem(1, 8, AWCAN_KB_Item);


    QTableWidgetItem *ERRSTKA_Item = protoItem->clone();
    ERRSTKA_Item->setText(QString::number(trc.ERRSTKA[indexFrame485]));
    ui->tableWidget->setItem(2, 8, ERRSTKA_Item);


    QTableWidgetItem *ERRSTKB_Item = protoItem->clone();
    ERRSTKB_Item->setText(QString::number(trc.ERRSTKB[indexFrame485]));
    ui->tableWidget->setItem(3, 8, ERRSTKB_Item);



    QTableWidgetItem *ERRSTNS_Item = protoItem->clone();
    ERRSTNS_Item->setText(QString::number(trc.ERRSTNS[indexFrame485]));
    ui->tableWidget->setItem(4, 8, ERRSTNS_Item);


    QTableWidgetItem *RA_KA_Item = protoItem->clone();
    RA_KA_Item->setText(QString::number(trc.RA_KA[indexFrame485]));
    ui->tableWidget->setItem(5, 8, RA_KA_Item);


    QTableWidgetItem *RB_KA_Item = protoItem->clone();
    RB_KA_Item->setText(QString::number(trc.RB_KA[indexFrame485]));
    ui->tableWidget->setItem(6, 8, RB_KA_Item);


    QTableWidgetItem *RA_KB_Item = protoItem->clone();
    RA_KB_Item->setText(QString::number(trc.RA_KB[indexFrame485]));
    ui->tableWidget->setItem(7, 8, RA_KB_Item);


    QTableWidgetItem *RB_KB_Item = protoItem->clone();
    RB_KB_Item->setText(QString::number(trc.RB_KB[indexFrame485]));
    ui->tableWidget->setItem(8, 8, RB_KB_Item);


    QTableWidgetItem *RAB_A_Item = protoItem->clone();
    RAB_A_Item->setText(QString::number(trc.RAB_A[indexFrame485]));
    ui->tableWidget->setItem(9, 8, RAB_A_Item);


    QTableWidgetItem *RAB_B_Item = protoItem->clone();
    RAB_B_Item->setText(QString::number(trc.RAB_B[indexFrame485]));
    ui->tableWidget->setItem(10, 8, RAB_B_Item);


    QTableWidgetItem *brWYBORU_TK_Item = protoItem->clone();
    brWYBORU_TK_Item->setText(QString::number(trc.brWYBORU_TK[indexFrame485]));
    ui->tableWidget->setItem(11, 8, brWYBORU_TK_Item);


    QTableWidgetItem *brWYBORU_TT_Item = protoItem->clone();
    brWYBORU_TT_Item->setText(QString::number(trc.brWYBORU_TT[indexFrame485]));
    ui->tableWidget->setItem(12, 8, brWYBORU_TT_Item);


    QTableWidgetItem *MED_Item = protoItem->clone();
    MED_Item->setText(QString::number(trc.MED[indexFrame485]));
    ui->tableWidget->setItem(13, 8, MED_Item);


    QTableWidgetItem *EP_Item = protoItem->clone();
    EP_Item->setText(QString::number(trc.EP[indexFrame485]));
    ui->tableWidget->setItem(14, 8, EP_Item);


    QTableWidgetItem *PN_Item = protoItem->clone();
    PN_Item->setText(QString::number(trc.PN[indexFrame485]));
    ui->tableWidget->setItem(15, 8, PN_Item);


    QTableWidgetItem *PS_Item = protoItem->clone();
    PS_Item->setText(QString::number(trc.PS[indexFrame485]));
    ui->tableWidget->setItem(16, 8, PS_Item);


    QTableWidgetItem *TW_Item = protoItem->clone();
    TW_Item->setText(QString::number(trc.TW[indexFrame485]));
    ui->tableWidget->setItem(17, 8, TW_Item);


    QTableWidgetItem *AK2_Item = protoItem->clone();
    AK2_Item->setText(QString::number(trc.AK2[indexFrame485]));
    ui->tableWidget->setItem(18, 8, AK2_Item);



    ////////////////////////    205h    /////////////////////////////

    QTableWidgetItem *FRED1_Item = protoItem->clone();
    FRED1_Item->setText(QString::number(trc.FRED1[indexFrame205]));
    ui->tableWidget->setItem(0, 14, FRED1_Item);

    QTableWidgetItem *FRED2_Item = protoItem->clone();
    FRED2_Item->setText(QString::number(trc.FRED2[indexFrame205]));
    ui->tableWidget->setItem(1, 14, FRED2_Item);

    QTableWidgetItem *V_POJAZDU_Item = protoItem->clone();
    V_POJAZDU_Item->setText(QString::number(trc.V_POJAZDU[indexFrame205]));
    ui->tableWidget->setItem(2, 14, V_POJAZDU_Item);

    QTableWidgetItem *ED1_ZAL_Item = protoItem->clone();
    ED1_ZAL_Item->setText(QString::number(trc.ED1_ZAL[indexFrame205]));
    ui->tableWidget->setItem(3, 14, ED1_ZAL_Item);

    QTableWidgetItem *ED2_ZAL_Item = protoItem->clone();
    ED2_ZAL_Item->setText(QString::number(trc.ED2_ZAL[indexFrame205]));
    ui->tableWidget->setItem(4, 14, ED2_ZAL_Item);

    QTableWidgetItem *MED_SNP_Item = protoItem->clone();
    MED_SNP_Item->setText(QString::number(trc.MED_SNP[indexFrame205]));
    ui->tableWidget->setItem(5, 14, MED_SNP_Item);

    QTableWidgetItem *POSL_N_Item = protoItem->clone();
    POSL_N_Item->setText(QString::number(trc.POSL_N[indexFrame205]));
    ui->tableWidget->setItem(6, 14, POSL_N_Item);

    QTableWidgetItem *StHEP_SL_Item = protoItem->clone();
    StHEP_SL_Item->setText(QString::number(trc.StHEP_SL[indexFrame205]));
    ui->tableWidget->setItem(7, 14, StHEP_SL_Item);

    if(ui->radioButton->isChecked())
        ui->progressBar->setValue(trc.iterator185h);

}
