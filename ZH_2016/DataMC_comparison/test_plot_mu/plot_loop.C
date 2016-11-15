#include <string>
#include <iostream>
#include "TString.h"
#include "TCanvas.h"
#include "VHPlotter.C"

void plot_loop(){

  const int N_histo = 28; 

  TString Histo_Name[N_histo];

  Histo_Name[0]="nVtx";
  Histo_Name[1]="leadMuPt";
  Histo_Name[2]="leadMuEta";
  Histo_Name[3]="subleadMuPt";
  Histo_Name[4]="subleadMuEta";
  Histo_Name[5]="Zmass";
  Histo_Name[6]="Zpt";
  Histo_Name[7]="Zeta";
  Histo_Name[8]="ZRapidity";
  Histo_Name[9]="FATjetPt";
  Histo_Name[10]="FATjetEta";
  Histo_Name[11]="FATjetSDmass";
  Histo_Name[12]="FATjetSDmassCorr";
  Histo_Name[13]="FATjetPRmass";
  Histo_Name[14]="FATjetPRmassCorr";
  Histo_Name[15]="FATjetCISVV2";
  Histo_Name[16]="FATjetTau1";
  Histo_Name[17]="FATjetTau2";
  Histo_Name[18]="FATjetTau2dvTau1";
  Histo_Name[19]="FATnSubjet";  Histo_Name[20]="FATsubjetLeadingPt";
  Histo_Name[21]="FATsubjetLeadingEta";
  Histo_Name[22]="FATsubjetLeadingSDCSV";
  Histo_Name[23]="FATsubjetSubLeadingPt";
  Histo_Name[24]="FATsubjetSubLeadingEta";
  Histo_Name[25]="FATsubjetSubLeadingSDCSV";
  Histo_Name[26]="ADDjet_DoubleSV";
  Histo_Name[27]="ZHmass";

  TCanvas* c1 = new TCanvas("c","c",10,10,800,600);
  TString save_path = "/afs/cern.ch/user/y/yuchang/www/ZH_2016/MC_Data_comparison/mu_channel.pdf";

  for(int i=0;i<N_histo;i++){

    std::string histo_name = (std::string) Histo_Name[i];

    VHPlotter( histo_name , 0 , c1  ) ;
    
    if(i==0)               c1->Print(save_path + "(");
    else if (i==N_histo-1) c1->Print(save_path + ")");
    else                   c1->Print(save_path      );

    c1->Clear();

  }

}

