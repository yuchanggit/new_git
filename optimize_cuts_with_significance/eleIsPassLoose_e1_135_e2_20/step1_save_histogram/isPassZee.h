#include <vector>
#include <string>
#include <iostream>
#include <TMath.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include "untuplizer.h"

//bool isPassZee(TreeReader &data, vector<Int_t>& goodEleID){
bool isPassZee(TreeReader &data, vector<Int_t>& goodEleID){
  
  Int_t    nEle       = data.GetInt("nEle");
  Int_t*   eleCharge  = data.GetPtrInt("eleCharge");
  Float_t* eleScEt    = data.GetPtrFloat("eleScEt");
  Float_t* eleScEta   = data.GetPtrFloat("eleScEta");
//  Float_t* eleMiniIso = data.GetPtrFloat("eleMiniIso");
//  Float_t* eleMiniIsoEA = data.GetPtrFloat("eleMiniIsoEA");
  TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
//  vector<bool>& eleIsPassHEEPNoIso = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
//  vector<bool>& eleIsPassVeto = *((vector<bool>*) data.GetPtr("eleIsPassVeto"));
  vector<bool>& eleIsPassLoose = *((vector<bool>*) data.GetPtr("eleIsPassLoose"));

  // select good electrons
        
  std::vector<Int_t> goodElectrons;

  for(Int_t ie = 0; ie < nEle; ie++){

    TLorentzVector* myEle = (TLorentzVector*)eleP4->At(ie);

    if( !(fabs(eleScEta[ie]) < 1.4442 || fabs(eleScEta[ie]) > 1.566) ) continue;
    if( fabs(eleScEta[ie]) > 2.5 ) continue;
    if( myEle->Pt() < 20 ) continue;
//    if( myEle->Pt() < 35 ) continue;
//    if( !eleIsPassHEEPNoIso[ie] ) continue;
//    if( eleMiniIso[ie] > 0.1 ) continue;
//    if( eleMiniIsoEA[ie] > 0.1 ) continue;
//    if( !eleIsPassVeto[ie] ) continue;
    if( !eleIsPassLoose[ie] ) continue;

    goodElectrons.push_back(ie);

  } // end of ele loop

  // select good Z boson

  bool findEPair = false;
  TLorentzVector* thisEle = NULL;
  TLorentzVector* thatEle = NULL;

  for(unsigned int i = 0; i < goodElectrons.size(); i++){

    Int_t ie = goodElectrons[i];
    thisEle = (TLorentzVector*)eleP4->At(ie);

    for(unsigned int j = 0; j < i; j++){

      Int_t je = goodElectrons[j];
      thatEle = (TLorentzVector*)eleP4->At(je);

      Float_t pt1 = thisEle->Pt();
      Float_t pt2 = thatEle->Pt();
      Float_t mll = (*thisEle+*thatEle).M();
      Float_t ptll = (*thisEle+*thatEle).Pt();

      if( eleCharge[ie]*eleCharge[je] > 0 ) continue;   
      if( TMath::Max(pt1,pt2) < 135 ) continue;
      if( mll < 70 || mll > 110 ) continue;
      if( ptll < 200 ) continue;

      if( !findEPair ){

	goodEleID.push_back( (pt1 > pt2) ? ie : je );
	goodEleID.push_back( (pt1 > pt2) ? je : ie );

      }

      findEPair = true;
      break;

    }
  }

  if( !findEPair ) return false;
  return true;

}
