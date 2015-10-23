#include <vector>
#include <string>
#include <iostream>
#include <TH1D.h>
#include <TH1F.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include "untuplizer.h"
//#include "ElectronSelection.h"

using namespace std;

int ZtoEEfinder(TreeReader &, vector<Int_t> *);

int ZtoEEfinder(TreeReader &data, vector<Int_t> *Z_electron_index)
{


    Int_t nEle         = data.GetInt("nEle");
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
    Float_t* eleSCEt          = data.GetPtrFloat("eleScEt");
    Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");
    Int_t*   eleCharge        = data.GetPtrInt("eleCharge");
    vector<bool>& eleIsPassHEEPNoIso = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));

    //5. select good electrons

    // save index of electron accepted by ElectronSelection.h
    std::vector<int> accepted;
//    select_electrons(data, &accepted);

    std::vector<int> goodElectrons;


    for(int ie=0; ie< nEle; ie++)
      {

        TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

//        if(fabs(thisEle->Eta())>2.5)continue;
        if( fabs(eleSCEta[ie]) > 2.5 ) continue;
        if(! (fabs(eleSCEta[ie])<1.4442 || fabs(eleSCEta[ie])>1.566))continue;

        float ele_pt = thisEle->Pt();
//	if(ele_pt<35)continue; // test

/*
        bool has_accepted = false;
        for(int j=0; j< accepted.size();j++)
                { if(ie == accepted[j]){has_accepted=true; break;}  }
        if(!has_accepted)continue;
*/

        if( !eleIsPassHEEPNoIso[ie] ) continue;
        if(eleMiniIso[ie]>0.1)continue;

        goodElectrons.push_back(ie);
      }


    //6. select a good Z boson
    bool findEPair=false;
    TLorentzVector l4_Z(0,0,0,0);

    for(unsigned int i=0; i< goodElectrons.size(); i++)
      {
        int ie = goodElectrons[i];
        TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

        for(unsigned int j=0; j< i; j++)
          {
            int je= goodElectrons[j];

            if(eleCharge[ie]*eleCharge[je]>0)continue;


            TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);

            float pt1 = thisEle->Pt();// use pt
            float pt2 = thatEle->Pt(); 


            float ptmax = TMath::Max(pt1,pt2);
            float ptmin = TMath::Min(pt1,pt2);
            if(ptmax<115)continue;
            if(ptmin<35)continue; // test

            int leadingIndex = pt1>pt2? ie : je;
            int subleadingIndex = pt1 > pt2? je : ie;

            Float_t ptll = (*thisEle+*thatEle).Pt();
            Float_t mll  = (*thisEle+*thatEle).M();
            if(mll<70 || mll>110)continue;
            if(ptll<200)continue;

 	    Z_electron_index->push_back( leadingIndex  );
            Z_electron_index->push_back( subleadingIndex  );

            if(!findEPair)l4_Z=(*thisEle+*thatEle);

            findEPair=true;
          }
      }

    if(findEPair){ return 1;}
    else if(!findEPair){ return 0;}
}














