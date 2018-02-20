#include "pliktrc.h"

plikTRC::plikTRC()
{

}

plikTRC::~plikTRC()
{

}

int plikTRC::U2_8bitToInt(int number)
{
    if(number > 127)
        return number - 256;

    else
        return number;
}

void plikTRC::openFile(QString path)
{
    file.setFileName(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            QMessageBox::information(0, "error", file.errorString());

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString temp;

            line = in.readLine();

            if(line.contains(";   Start time:"))
            {
                s_InitialDate = line.mid(16, 10);
                s_InitialTime = line.mid(27, 8);
            }

            initialTime = QTime::fromString(s_InitialTime);

            if(line.contains("Rx         0205", Qt::CaseInsensitive))
            {
                bool ok;

                list205h << line.mid(41);
                bytes205h = line.mid(41).split(" ");

                messageNumbers205 << line.left(6).toInt();

                temp = bytes205h[0];
                FRED1 << U2_8bitToInt(temp.toInt(&ok, 16)) * 0.6;
                temp = bytes205h[1];
                FRED2 << U2_8bitToInt(temp.toInt(&ok, 16)) * 0.6;
                temp = bytes205h[2];
                V_POJAZDU << temp.toInt(&ok, 16);
                temp = bytes205h[3];
                ED1_ZAL << (1LL & (temp.toInt(&ok, 16) >> 0));
                ED2_ZAL << (1LL & (temp.toInt(&ok, 16) >> 1));
                MED_SNP << (1LL & (temp.toInt(&ok, 16) >> 2));
                POSL_N << (1LL & (temp.toInt(&ok, 16) >> 3));
                temp = bytes205h[5];
                StHEP_SL << temp.toInt(&ok, 16);
            }

            if(line.contains("Rx         0185", Qt::CaseInsensitive))
            {
                bool ok;

                s_Offset = line.mid(8, 11);
                offset << (int)s_Offset.toFloat();
                frameTime = initialTime.addMSecs(offset.last());
                frameDateTime << s_InitialDate + " " + frameTime.toString("hh:mm:ss");

                list185h << line.mid(41);
                bytes185h = line.mid(41).split(" ");

                          //  debuger << bytes185h[0];

                messageNumbers185 << line.left(6).toInt();

                temp = bytes185h[0];
                FZED1 << U2_8bitToInt(temp.toInt(&ok, 16)) * 0.6;
                temp = bytes185h[1];
                FZED2 << U2_8bitToInt(temp.toInt(&ok, 16)) * 0.6;
                temp = bytes185h[2];
                A_MH << temp.toInt(&ok, 16) * 0.01;
                temp = bytes185h[3];
                ZAL_HAMULCA << (1LL & (temp.toInt(&ok, 16) >> 0));
                WH_A << (1LL & (temp.toInt(&ok, 16) >> 1));
                WH_B << (1LL & (temp.toInt(&ok, 16) >> 2));
                WH_S << (1LL & (temp.toInt(&ok, 16) >> 3));
                zeroJ << (1LL & (temp.toInt(&ok, 16) >> 4));
                temp = bytes185h[5];
                MCA << temp.toInt(&ok, 16) * 2;
                temp = bytes185h[6];
                MCB << temp.toInt(&ok, 16) * 2;
                temp = bytes185h[7];
                MCS << temp.toInt(&ok, 16) * 2;
            }

            if(line.contains("Rx         0285", Qt::CaseInsensitive))
            {
                bool ok;

                list285h << line.mid(41);
                bytes285h = line.mid(41).split(" ");

                messageNumbers285 << line.left(6).toInt();

                temp = bytes285h[0];
                MASA_A << temp.toInt(&ok, 16);
                temp = bytes285h[1];
                MASA_A.last() += 256 * temp.toInt(&ok, 16);
                MASA_A.last() *= 0.1;
                temp = bytes285h[2];
                MASA_B << temp.toInt(&ok, 16);
                temp = bytes285h[3];
                MASA_B.last() += 256 * temp.toInt(&ok, 16);
                MASA_B.last() *= 0.1;
                temp = bytes285h[4];
                MASA_S << temp.toInt(&ok, 16);
                temp = bytes285h[5];
                MASA_S.last() += 256 * temp.toInt(&ok, 16);
                MASA_S.last() *= 0.1;
                temp = bytes285h[6];
                AWMC_B << (1LL & (temp.toInt(&ok, 16) >> 0));
                AWMCp_B << (1LL & (temp.toInt(&ok, 16) >> 1));
                AWMZR_B << (1LL & (temp.toInt(&ok, 16) >> 2));
                AWMW_B << (1LL & (temp.toInt(&ok, 16) >> 3));
                AWMC_A << (1LL & (temp.toInt(&ok, 16) >> 4));
                AWMCp_A << (1LL & (temp.toInt(&ok, 16) >> 5));
                AWMZR_A << (1LL & (temp.toInt(&ok, 16) >> 6));
                AWMW_A << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes285h[7];
                AWCANRS_S << (1LL & (temp.toInt(&ok, 16) >> 0));
                AWCANRS_B << (1LL & (temp.toInt(&ok, 16) >> 1));
                AWCANRS_A << (1LL & (temp.toInt(&ok, 16) >> 2));
                OGR_V << (1LL & (temp.toInt(&ok, 16) >> 3));
                AWMC_S << (1LL & (temp.toInt(&ok, 16) >> 4));
                AWMCp_S << (1LL & (temp.toInt(&ok, 16) >> 5));
                AWMZR_S << (1LL & (temp.toInt(&ok, 16) >> 6));
                AWMW_S << (1LL & (temp.toInt(&ok, 16) >> 7));
            }

            if(line.contains("Rx         0385", Qt::CaseInsensitive))
            {
                bool ok;

                list385h << line.mid(41);
                bytes385h = line.mid(41).split(" ");

                messageNumbers385 << line.left(6).toInt();

                temp = bytes385h[0];
                MZ << temp.toInt(&ok, 16);
                temp = bytes385h[1];
                MZ.last() += 256 * temp.toInt(&ok, 16);
                temp = bytes385h[2];
                MG << temp.toInt(&ok, 16);
                temp = bytes385h[3];
                MG.last() += 256 * temp.toInt(&ok, 16);
                temp = bytes385h[4];
                StHEP << temp.toInt(&ok, 16);
            }

            if(line.contains("Rx         0485", Qt::CaseInsensitive))
            {
                bool ok;

                list485h << line.right(23);
                bytes485h = line.right(23).split(" ");

                messageNumbers485 << line.left(6).toInt();

                temp = bytes485h[0];
                zeroJ_TK << (1LL & (temp.toInt(&ok, 16) >> 0));
                Gm << (1LL & (temp.toInt(&ok, 16) >> 1));
                Cd << (1LL & (temp.toInt(&ok, 16) >> 2));
                zeroSHP << (1LL & (temp.toInt(&ok, 16) >> 3));
                zeroRS << (1LL & (temp.toInt(&ok, 16) >> 4));
                SG << (1LL & (temp.toInt(&ok, 16) >> 5));
                zeroJ_1 << (1LL & (temp.toInt(&ok, 16) >> 6));
                zeroJ_2 << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes485h[1];
                zeroJ_3 << (1LL & (temp.toInt(&ok, 16) >> 0));
                zeroJ_4 << (1LL & (temp.toInt(&ok, 16) >> 1));
                zeroJ_5 << (1LL & (temp.toInt(&ok, 16) >> 2));
                zeroJ_6 << (1LL & (temp.toInt(&ok, 16) >> 3));
                zeroJ_7 <<(1LL & (temp.toInt(&ok, 16) >> 4));
                AWMZ_KA << (1LL & (temp.toInt(&ok, 16) >> 5));
                AWMGp_KA << (1LL & (temp.toInt(&ok, 16) >> 6));
                AWMG_KA << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes485h[2];
                AWMHS_KA << (1LL & (temp.toInt(&ok, 16) >> 0));
                AWMC_KA << (1LL & (temp.toInt(&ok, 16) >> 1));
                AWMZ_KB << (1LL & (temp.toInt(&ok, 16) >> 2));
                AWMGp_KB << (1LL & (temp.toInt(&ok, 16) >> 3));
                AWMG_KB << (1LL & (temp.toInt(&ok, 16) >> 4));
                AWMHS_KB << (1LL & (temp.toInt(&ok, 16) >> 5));
                AWMC_KB << (1LL & (temp.toInt(&ok, 16) >> 6));
                AWYp_A1 << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes485h[3];
                AWYp_A2 << (1LL & (temp.toInt(&ok, 16) >> 0));
                AWYp_B1 << (1LL & (temp.toInt(&ok, 16) >> 1));
                AWYp_B2 << (1LL & (temp.toInt(&ok, 16) >> 2));
                AWYp_S1 << (1LL & (temp.toInt(&ok, 16) >> 3));
                AWYp_S2 << (1LL & (temp.toInt(&ok, 16) >> 4));
                AWCAN_KA << (1LL & (temp.toInt(&ok, 16) >> 5));
                AWCAN_KB << (1LL & (temp.toInt(&ok, 16) >> 6));
                ERRSTKA << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes485h[4];
                ERRSTKB << (1LL & (temp.toInt(&ok, 16) >> 0));
                ERRSTNS << (1LL & (temp.toInt(&ok, 16) >> 3));
                RA_KA << (1LL & (temp.toInt(&ok, 16) >> 4));
                RB_KA << (1LL & (temp.toInt(&ok, 16) >> 5));
                RA_KB << (1LL & (temp.toInt(&ok, 16) >> 6));
                RB_KB << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes485h[5];
                RAB_A << (1LL & (temp.toInt(&ok, 16) >> 0));
                RAB_B << (1LL & (temp.toInt(&ok, 16) >> 1));
                brWYBORU_TK << (1LL & (temp.toInt(&ok, 16) >> 2));
                brWYBORU_TT << (1LL & (temp.toInt(&ok, 16) >> 3));
                MED << (1LL & (temp.toInt(&ok, 16) >> 4));
                EP << (1LL & (temp.toInt(&ok, 16) >> 5));
                PN << (1LL & (temp.toInt(&ok, 16) >> 6));
                PS << (1LL & (temp.toInt(&ok, 16) >> 7));
                temp = bytes485h[6];
                TW << (1LL & (temp.toInt(&ok, 16) >> 0));
                AK2 << (1LL & (temp.toInt(&ok, 16) >> 1));
            }

        }
}
