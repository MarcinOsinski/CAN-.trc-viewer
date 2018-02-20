#ifndef PLIKTRC_H
#define PLIKTRC_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>

class plikTRC
{
public:
    plikTRC();
    ~plikTRC();

    // 185h
    QVector<float> FZED1;
    QVector<float> FZED2;
    QVector<float> A_MH;
    QVector<int> ZAL_HAMULCA;
    QVector<int> WH_A;
    QVector<int> WH_B;
    QVector<int> WH_S;
    QVector<int> zeroJ;
    QVector<int> MCA;
    QVector<int> MCB;
    QVector<int> MCS;

    // 285h
    QVector<float> MASA_A;
    QVector<float> MASA_B;
    QVector<float> MASA_S;
    QVector<int> AWMC_B;
    QVector<int> AWMCp_B;
    QVector<int> AWMZR_B;
    QVector<int> AWMW_B;
    QVector<int> AWMC_A;
    QVector<int> AWMCp_A;
    QVector<int> AWMZR_A;
    QVector<int> AWMW_A;
    QVector<int> AWCANRS_S;
    QVector<int> AWCANRS_B;
    QVector<int> AWCANRS_A;
    QVector<int> OGR_V;
    QVector<int> AWMC_S;
    QVector<int> AWMCp_S;
    QVector<int> AWMZR_S;
    QVector<int> AWMW_S;

    // 385h
    QVector<int> MZ;
    QVector<int> MG;
    QVector<int> StHEP;

    // 485h
    QVector<int> zeroJ_TK;
    QVector<int> Gm;
    QVector<int> Cd;
    QVector<int> zeroSHP;
    QVector<int> zeroRS;
    QVector<int> SG;
    QVector<int> zeroJ_1;
    QVector<int> zeroJ_2;
    QVector<int> zeroJ_3;
    QVector<int> zeroJ_4;
    QVector<int> zeroJ_5;
    QVector<int> zeroJ_6;
    QVector<int> zeroJ_7;
    QVector<int> AWMZ_KA;
    QVector<int> AWMGp_KA;
    QVector<int> AWMG_KA;
    QVector<int> AWMHS_KA;
    QVector<int> AWMC_KA;
    QVector<int> AWMZ_KB;
    QVector<int> AWMGp_KB;
    QVector<int> AWMG_KB;
    QVector<int> AWMHS_KB;
    QVector<int> AWMC_KB;
    QVector<int> AWYp_A1;
    QVector<int> AWYp_A2;
    QVector<int> AWYp_B1;
    QVector<int> AWYp_B2;
    QVector<int> AWYp_S1;
    QVector<int> AWYp_S2;
    QVector<int> AWCAN_KA;
    QVector<int> AWCAN_KB;
    QVector<int> ERRSTKA;
    QVector<int> ERRSTKB;
    QVector<int> ERRSTNS;
    QVector<int> RA_KA;
    QVector<int> RB_KA;
    QVector<int> RA_KB;
    QVector<int> RB_KB;
    QVector<int> RAB_A;
    QVector<int> RAB_B;
    QVector<int> brWYBORU_TK;
    QVector<int> brWYBORU_TT;
    QVector<int> MED;
    QVector<int> EP;
    QVector<int> PN;
    QVector<int> PS;
    QVector<int> TW;
    QVector<int> AK2;

    // 205h
    QVector<float> FRED1;
    QVector<float> FRED2;
    QVector<int> V_POJAZDU;
    QVector<int> ED1_ZAL;
    QVector<int> ED2_ZAL;
    QVector<int> MED_SNP;
    QVector<int> POSL_N;
    QVector<int> StHEP_SL;

    int iterator205h = 0;
    int iterator185h = 0;
    int iterator285h = 0;
    int iterator385h = 0;
    int iterator485h = 0;

    QStringList list185h;
    QStringList list285h;
    QStringList list385h;
    QStringList list485h;
    QStringList list205h;

    QStringList bytes185h;
    QStringList bytes285h;
    QStringList bytes385h;
    QStringList bytes485h;
    QStringList bytes205h;

    QStringList debuger;

    QString line;
    QFile file;

    QString s_InitialDate;
    QString s_InitialTime;
    QTime initialTime;
    QString s_Offset;
    QVector<int> offset;
    QTime frameTime;
    QStringList frameDateTime;

    QVector<int> messageNumbers185;
    QVector<int> messageNumbers285;
    QVector<int> messageNumbers385;
    QVector<int> messageNumbers485;
    QVector<int> messageNumbers205;

    void openFile(QString path);
    int U2_8bitToInt(int number);
};

#endif // PLIKTRC_H
