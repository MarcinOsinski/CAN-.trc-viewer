#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QHBoxLayout>

#include "pliktrc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    plikTRC trc;

    QString getFilePath();

    void showValues(int indexFrame185, int indexFrame285, int indexFrame385, int indexFrame485, int indexFrame205);

    //////////////////////////  CHECKBOX    //////////////////////////

    QWidget *pWidget[89];
    QHBoxLayout *pLayout[89];

    QCheckBox *checkboxFZED1;
    QCheckBox *checkboxFZED2;
    QCheckBox *A_MH;
    QCheckBox *ZAL_HAMULCA;
    QCheckBox *WH_A;
    QCheckBox *WH_B;
    QCheckBox *WH_S;
    QCheckBox *OJ;
    QCheckBox *MC_A;
    QCheckBox *MC_B;
    QCheckBox *MC_S;
    QCheckBox *MZ;
    QCheckBox *MG;
    QCheckBox *StHEP;
    QCheckBox *MASA_A;
    QCheckBox *MASA_B;
    QCheckBox *MASA_S;
    QCheckBox *AWMC_B;
    QCheckBox *AWMCp_B;
    QCheckBox *AWMZR_B;
    QCheckBox *AWMW_B;
    QCheckBox *AWMC_A;
    QCheckBox *AWMCp_A;
    QCheckBox *AWMZR_A;
    QCheckBox *AWMW_A;
    QCheckBox *AWCANRS_S;
    QCheckBox *AWCANRS_B;
    QCheckBox *AWCANRS_A;
    QCheckBox *OGRV;
    QCheckBox *AWMC_S;
    QCheckBox *AWMCp_S;
    QCheckBox *AWMZR_S;
    QCheckBox *AWMW_S;
    QCheckBox *AWCAN_KA;
    QCheckBox *AWCAN_KB;
    QCheckBox *ERRSTKA;
    QCheckBox *ERRSTKB;
    QCheckBox *ERRSTNS;
    QCheckBox *RA_KA;
    QCheckBox *RB_KA;
    QCheckBox *RA_KB;
    QCheckBox *RB_KB;
    QCheckBox *RAB_A;
    QCheckBox *RAB_B;
    QCheckBox *brWYBORU_TK;
    QCheckBox *brWYBORU_TT;
    QCheckBox *MED;
    QCheckBox *EP;
    QCheckBox *PN;
    QCheckBox *PS;
    QCheckBox *TW;
    QCheckBox *AK2;
    QCheckBox *zeroJ_TK;
    QCheckBox *Gm;
    QCheckBox *Cd;
    QCheckBox *zeroSHP;
    QCheckBox *zeroRS;
    QCheckBox *SG;
    QCheckBox *zeroJ_1;
    QCheckBox *zeroJ_2;
    QCheckBox *zeroJ_3;
    QCheckBox *zeroJ_4;
    QCheckBox *zeroJ_5;
    QCheckBox *zeroJ_6;
    QCheckBox *zeroJ_7;
    QCheckBox *AWMZ_KA;
    QCheckBox *AWMGp_KA;
    QCheckBox *AWMG_KA;
    QCheckBox *AWMHS_KA;
    QCheckBox *AWMC_KA;
    QCheckBox *AWMZ_KB;
    QCheckBox *AWMGp_KB;
    QCheckBox *AWMG_KB;
    QCheckBox *AWMHS_KB;
    QCheckBox *AWMC_KB;
    QCheckBox *FRED1;
    QCheckBox *FRED2;
    QCheckBox *V_POJAZDU;
    QCheckBox *ED1_ZAL;
    QCheckBox *ED2_ZAL;
    QCheckBox *MED_SNP;
    QCheckBox *POSL_N;
    QCheckBox *StHEP_SL;
    QCheckBox *AWYp_A1;
    QCheckBox *AWYp_A2;
    QCheckBox *AWYp_B1;
    QCheckBox *AWYp_B2;
    QCheckBox *AWYp_S1;
    QCheckBox *AWYp_S2;


private:
    Ui::MainWindow *ui;

    QString filePath;
    QTableWidgetItem *checkbox[89];
    QTimer* timer;

    int time;

    void putCheckboxes();

private slots:
    void timerTimeout();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_radiobutton_toggled(bool checked);
    void on_radiobutton_2_toggled(bool checked);

    void on_spinBox_2_valueChanged();

    void on_checkBoxTimerON_checked(bool checked);

    void on_checkboxFZED1_checked(bool checked);
    void on_checkboxFZED2_checked(bool checked);
    void on_checkboxA_MH_checked(bool checked);
    void on_checkboxZAL_HAMULCA_checked(bool checked);
    void on_checkboxWH_A_checked(bool checked);
    void on_checkboxWH_B_checked(bool checked);
    void on_checkboxWH_S_checked(bool checked);
    void on_checkboxOJ_checked(bool checked);
    void on_checkboxMC_A_checked(bool checked);
    void on_checkboxMC_B_checked(bool checked);
    void on_checkboxMC_S_checked(bool checked);
    void on_checkboxMZ_checked(bool checked);
    void on_checkboxMG_checked(bool checked);
    void on_checkboxStHEP_checked(bool checked);
    void on_checkboxMASA_A_checked(bool checked);
    void on_checkboxMASA_B_checked(bool checked);
    void on_checkboxMASA_S_checked(bool checked);
    void on_checkboxAWMC_B_checked(bool checked);
    void on_checkboxAWMCp_B_checked(bool checked);
    void on_checkboxAWMZR_B_checked(bool checked);
    void on_checkboxAWMW_B_checked(bool checked);
    void on_checkboxAWMC_A_checked(bool checked);
    void on_checkboxAWMCp_A_checked(bool checked);
    void on_checkboxAWMZR_A_checked(bool checked);
    void on_checkboxAWMW_A_checked(bool checked);
    void on_checkboxAWCANRS_S_checked(bool checked);
    void on_checkboxAWCANRS_B_checked(bool checked);
    void on_checkboxAWCANRS_A_checked(bool checked);
    void on_checkboxOGRV_checked(bool checked);
    void on_checkboxAWMC_S_checked(bool checked);
    void on_checkboxAWMCp_S_checked(bool checked);
    void on_checkboxAWMZR_S_checked(bool checked);
    void on_checkboxAWMW_S_checked(bool checked);
    void on_checkboxAWCAN_KA_checked(bool checked);
    void on_checkboxAWCAN_KB_checked(bool checked);
    void on_checkboxERRSTKA_checked(bool checked);
    void on_checkboxERRSTKB_checked(bool checked);
    void on_checkboxERRSTNS_checked(bool checked);
    void on_checkboxRA_KA_checked(bool checked);
    void on_checkboxRB_KA_checked(bool checked);
    void on_checkboxRA_KB_checked(bool checked);
    void on_checkboxRB_KB_checked(bool checked);
    void on_checkboxRAB_A_checked(bool checked);
    void on_checkboxRAB_B_checked(bool checked);
    void on_checkboxbrWYBORU_TK_checked(bool checked);
    void on_checkboxbrWYBORU_TT_checked(bool checked);
    void on_checkboxMED_checked(bool checked);
    void on_checkboxEP_checked(bool checked);
    void on_checkboxPN_checked(bool checked);
    void on_checkboxPS_checked(bool checked);
    void on_checkboxTW_checked(bool checked);
    void on_checkboxAK2_checked(bool checked);
    void on_checkboxzeroJ_TK_checked(bool checked);
    void on_checkboxGm_checked(bool checked);
    void on_checkboxCd_checked(bool checked);
    void on_checkboxzeroSHP_checked(bool checked);
    void on_checkboxzeroRS_checked(bool checked);
    void on_checkboxSG_checked(bool checked);
    void on_checkboxzeroJ_1_checked(bool checked);
    void on_checkboxzeroJ_2_checked(bool checked);
    void on_checkboxzeroJ_3_checked(bool checked);
    void on_checkboxzeroJ_4_checked(bool checked);
    void on_checkboxzeroJ_5_checked(bool checked);
    void on_checkboxzeroJ_6_checked(bool checked);
    void on_checkboxzeroJ_7_checked(bool checked);
    void on_checkboxAWMZ_KA_checked(bool checked);
    void on_checkboxAWMGp_KA_checked(bool checked);
    void on_checkboxAWMG_KA_checked(bool checked);
    void on_checkboxAWMHS_KA_checked(bool checked);
    void on_checkboxAWMC_KA_checked(bool checked);
    void on_checkboxAWMZ_KB_checked(bool checked);
    void on_checkboxAWMGp_KB_checked(bool checked);
    void on_checkboxAWMG_KB_checked(bool checked);
    void on_checkboxAWMHS_KB_checked(bool checked);
    void on_checkboxAWMC_KB_checked(bool checked);
    void on_checkboxFRED1_checked(bool checked);
    void on_checkboxFRED2_checked(bool checked);
    void on_checkboxV_POJAZDU_checked(bool checked);
    void on_checkboxED1_ZAL_checked(bool checked);
    void on_checkboxED2_ZAL_checked(bool checked);
    void on_checkboxMED_SNP_checked(bool checked);
    void on_checkboxPOSL_N_checked(bool checked);
    void on_checkboxStHEP_SL_checked(bool checked);
    void on_checkboxAWYp_A1_checked(bool checked);
    void on_checkboxAWYp_A2_checked(bool checked);
    void on_checkboxAWYp_B1_checked(bool checked);
    void on_checkboxAWYp_B2_checked(bool checked);
    void on_checkboxAWYp_S1_checked(bool checked);
    void on_checkboxAWYp_S2_checked(bool checked);
};

#endif // MAINWINDOW_H
