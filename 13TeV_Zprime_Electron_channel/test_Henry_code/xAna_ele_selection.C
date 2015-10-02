#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <string>
#include "TCanvas.h"
#include "ElectronSelection.h"
#include "ZtoEEfinder.h"
#include "isPassZee.h"

using namespace std;

void select_electrons(TreeReader &, vector<int> * );

bool isPassZee(TreeReader &, vector<Int_t>& );

void xAna_ele_selection(TString inputFile, TCanvas *c1 , TCanvas *c2 , TCanvas *c3 ,TCanvas *c4 ,TCanvas *c5 , TCanvas *c6 ,
int mass_point ,double eff,double eff_err, TString dir_name, int dir_flag ,int signal_background_flag, int background_file_index ){


  // define histograms

  TString title2 = Form("ele pT for Zprime mass = %d",mass_point);
  TString title3 = Form("lepton pairs' pT for Zprime mass = %d",mass_point);
  TString title4 = Form("SD mass for Zprime mass = %d",mass_point);
  TString title5 = Form("Z mass for Zprime mass = %d",mass_point);
  TString title6 = Form("Zprime mass for Zprime mass = %d",mass_point);
  TString title7 = Form("|dEta| of ZH for Zprime mass = %d",mass_point);
  TString title8 = Form("|dPhi| of ZH for Zprime mass = %d",mass_point);
  TString title9 = Form("dR of ZH for Zprime mass = %d",mass_point);

  TH1D* h_ele_pT = new TH1D("h_ele_pT", title2 ,3000 , 0,3000 );
  TH1D* h_lepton_pair_pT = new TH1D("h_lepton_pair_pT", title3 ,400 , 0,4000 );
  TH1D* h_SD =new TH1D("h_SD",title4 ,100,0,200);
  TH1D* h_Z_mass = new TH1D("h_Z_mass",title5 ,250,0,500);
  TH1D* h_Zprime_mass = new TH1D("h_Zprime_mass",title6 ,1000,0,5000);
  TH1D* h_abs_dEta_ZH = new TH1D("h_abs_dEta_ZH",title7 ,80,-1,3);
  TH1D* h_abs_dPhi_ZH = new TH1D("h_abs_dPhi_ZH",title8 ,80,0,4);
  TH1D* h_abs_dR_ZH   = new TH1D("h_abs_dR_ZH"  ,title9 ,80,0,4);

  //get TTree from file ...
//  TreeReader data(inputFile.data());
  TreeReader data(inputFile.Data());

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};
  ofstream fout;
  fout.open("ele_Eiko.txt");

  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal ++;

    // 0. check the generator-level information and make sure there is a Z->e+e-

    // 1. make sure there is a h-> bb, Yu-Hsiang change it
  
    nPass[0]++;
    nPass[1]++;
     
    //2. pass electron or muon trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    vector<bool> &trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
 	std::string thisTrig= trigName[it];
 	bool results = trigResult[it];

	// std::cout << thisTrig << " : " << results << std::endl;
	
 	if( (thisTrig.find("HLT_Ele105")!= std::string::npos && results==1)
	    ||
	    (thisTrig.find("HLT_Mu45")!= std::string::npos && results==1)
	    )
 	  {
 	    passTrigger=true;
 	    break;
 	  }


      }


    if(!passTrigger)continue;
    nPass[2]++;


    //3. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[3]++;

    //4. look for good electrons first
    Int_t run          = data.GetInt("runId");
    Int_t lumi         = data.GetInt("lumiSection");
    Int_t event        = data.GetInt("eventId");
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");


    //5. select good electrons
	
    //6. select a good Z boson

    // Z->e e finder 
    vector<Int_t> Z_electron_index;
//    int FindZ_flag =-1;
//    FindZ_flag = ZtoEEfinder( data , &Z_electron_index );
    //
    bool FindZ_flag = false;
    FindZ_flag = isPassZee(data, &Z_electron_index );

//    if( FindZ_flag!=1 )   {  continue;}
    if( !FindZ_flag )   {  continue;}

    TLorentzVector l4_Z(0,0,0,0);

    if(Z_electron_index.size()>0)
    {
        TLorentzVector* Ele1 = (TLorentzVector*)eleP4->At(Z_electron_index[0]);
        TLorentzVector* Ele2 = (TLorentzVector*)eleP4->At(Z_electron_index[1]);

    l4_Z=( *Ele1 + *Ele2);
    }

    nPass[4]++;



    //7.select a good CA8 and cleaned jet
	
    Int_t nJet         = data.GetInt("FATnJet");
    TClonesArray* jetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  jetSDmass = data.GetPtrFloat("FATjetSDmass");
    Float_t*  jetPRmass = data.GetPtrFloat("FATjetPRmass");

    Int_t*   nSubSoftDropJet = data.GetPtrInt("FATnSubSDJet");
    vector<float>   *subjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV", nJet);

    std::vector<int> goodJets;
    std::vector<double> SD_Mass;
    TLorentzVector l4_leadingJet(0,0,0,0);
    bool findAJet=false;
    for(int ij=0; ij<nJet; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)jetP4->At(ij);

        double PR_low = 95, PR_high = 130;
        if(jetPRmass[ij]<PR_low || jetPRmass[ij]>PR_high)continue;


	// overlap with electron pair of Z 
        bool hasOverLap=false;
	{
        TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(Z_electron_index[0]);
        if(thisEle->DeltaR(*thisJet)<0.8)hasOverLap=true;

        TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(Z_electron_index[1]);
        if(thatEle->DeltaR(*thisJet)<0.8)hasOverLap=true;
	}
        if(hasOverLap)continue;
	//

	
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;


	// at least one sub jet CSV> 0.605
	int nSubBTag=0;
//	if( nSubSoftDropJet[ij]!=2){	  continue;}

	for(int is=0; is < nSubSoftDropJet[ij]; is++)
	  {
	    if(subjetSDCSV[ij][is] < 0.605 || subjetSDCSV[ij][is] >1)continue;
	    nSubBTag++;
	  }
	if(nSubBTag<1) continue;
	//


     	if(!findAJet)
	  {
	    l4_leadingJet = *thisJet;
            SD_Mass.push_back( jetSDmass[ij] );
	    goodJets.push_back(ij);// save leading jet
	  }
	    
     	findAJet=true;

      }
    
    if(!findAJet)
      continue;
    nPass[5]++;

     Float_t MGrav = (l4_leadingJet + l4_Z).M();

     double Mass_Point = mass_point;
     double mass_upper = Mass_Point + Mass_Point*0.15;
     double mass_lower = Mass_Point - Mass_Point*0.15;

     if( MGrav< mass_lower || MGrav>mass_upper )continue;
     h_Zprime_mass->Fill( MGrav );
     nPass[6]++;

  // if event can go here, then fill the histograms to plot the distributions. Yu-Hsiang add 


{

      int ie = Z_electron_index[0];
    TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);
    h_ele_pT->Fill( thisEle->Pt() );



}
 

                h_lepton_pair_pT->Fill( l4_Z.Pt() );
                h_Z_mass->Fill( l4_Z.M() );

    for(unsigned int i=0; i< SD_Mass.size(); i++)
      {

                h_SD->Fill( SD_Mass[i] );
      }

    // save delta Eta, delta Phi and delta R BTW reco-Z and reco-H
      {

        int ie_1st = Z_electron_index[0];
        int ie_2nd = Z_electron_index[1];
    	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie_1st);
    	TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(ie_2nd);

	int ij_1st = goodJets[0];
        TLorentzVector* thisJet = (TLorentzVector*)jetP4->At(ij_1st);

	// get Eta, Phi of Z and H
        float eta_H = thisJet->Eta();
        float phi_H = thisJet->Phi();
        float eta_Z = (*thisEle+*thatEle).Eta();
        float phi_Z = (*thisEle+*thatEle).Phi();

	// calculate the |dEta|, |dPhi| and dR
	float abs_dEta = fabs(eta_H - eta_Z);
        float abs_dPhi = -99;
	if(fabs(phi_H - phi_Z) < 3.14){ abs_dPhi = fabs(phi_H - phi_Z); }
        if(fabs(phi_H - phi_Z) > 3.14){ abs_dPhi = 6.28 - fabs(phi_H - phi_Z); }
	float dR_ZH = (*thisEle+*thatEle).DeltaR( *thisJet ); 

	// fill histogram
	h_abs_dEta_ZH ->Fill( abs_dEta );
	h_abs_dPhi_ZH ->Fill( abs_dPhi);
	h_abs_dR_ZH   ->Fill( dR_ZH );

      }


  ////////

    fout << run << " " << lumi << " " << event << endl;
    

  } // end of loop over entries





  fout.close();
  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;




  //  Yu-Hsiang add calulation of total efficiency and eff uncertainty


  double pass =-99,fail=-99,f_over_p=-99,f_over_p_error=-99;
//  double n_total = nTotal;// from int to double
  double n_total = nPass[1];// from int to double

eff = nPass[6]/n_total;
pass = nPass[6];
fail = nTotal -  nPass[6];
f_over_p = fail/pass;
f_over_p_error = f_over_p * sqrt( (1/fail) + (1/pass) );
eff_err = f_over_p_error/pow( 1 + f_over_p ,2);

cout<<"eff: "<< eff << "   eff_err: "<< eff_err <<endl;





  // Yu-Hsiang add cut flow figure


  TString title1 = Form("Cut Flow for Zprime mass = %d, eff=%f +/- %f",mass_point,eff,eff_err);

  TH1D* h_CutFlow = new TH1D("h_CutFlow", title1 ,8 , 0,8 );

  char* cut_name[8] = {"Began","Z->ee in Gen","H->bb in Gen","HLT","Vertex","Leptons","V-jet","Zprime mass"};

	for(int i=1;i<=8;i++){ // i is the index of column of cut flow plot 
		if(i==1) {h_CutFlow->SetBinContent(i,nTotal); }
        	else {h_CutFlow->SetBinContent(i,nPass[i-2]); }
		h_CutFlow->GetXaxis()->SetBinLabel( i , cut_name[i-1] );
	}

//

  TString png1_name = Form("Zprime_Cut_Flow_M_%d.png",mass_point);
  TString png2_name = Form("Zprime_ele_pT_M_%d.png",mass_point);
  TString png3_name = Form("Zprime_ll_pT_M_%d.png",mass_point);
  TString png4_name = Form("Zprime_SD_mass_M_%d.png",mass_point);
  TString png5_name = Form("Zprime_Z_mass_M_%d.png",mass_point);



//   TCanvas *c1 = new TCanvas("c1","try to show cut flow ",200,10,700,500);
  c1->cd();

  gPad->SetGridx();
//  gPad->SetLogy();

  h_CutFlow->SetMarkerStyle(8);
  h_CutFlow->SetMarkerSize(1);
  h_CutFlow->GetXaxis()->SetLabelSize(0.041);
//  h_CutFlow->GetYaxis()->SetLabelSize(0.035);

  h_CutFlow->SetStats(0);
  h_CutFlow->SetMarkerSize(2.0);

  h_CutFlow->Draw();
  h_CutFlow->Draw("HIST TEXT0 SAME");


//
    // Yu-Hsiang add drawing histogram of distributuion

  c2->cd();
  h_ele_pT->Draw();

  c3->cd();
  h_lepton_pair_pT->Draw();

  c4->cd();
  h_SD->Draw();

  c5->cd();
  h_Z_mass->Draw();

  c6->cd();
  h_Zprime_mass->Draw();
  
  TCanvas *c7 = new TCanvas("c7","",200,10,700,500);
  TCanvas *c8 = new TCanvas("c8","",200,10,700,500);
  TCanvas *c9 = new TCanvas("c9","",200,10,700,500);

  c7->cd();
  h_abs_dEta_ZH->Draw();

  c8->cd();
  h_abs_dPhi_ZH->Draw();

  c9->cd();
  h_abs_dR_ZH->Draw();


////

   // Yu-Hsiang add that save TH1D in the ROOT file


   TString ROOT_name;

   // when read signal sample
   if (signal_background_flag ==0){

   ROOT_name = Form("signal_shape_in_Zprime_M-%d.root",mass_point);
   ROOT_name = dir_name + ROOT_name; 
//   ROOT_name = dir_name +"no_zprime_cut_"+ ROOT_name;
   }

   // when read background sample
   if (signal_background_flag ==1){
     if ( background_file_index ==0) { ROOT_name = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",mass_point);}
     if ( background_file_index ==1) { ROOT_name = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",mass_point);}
     if ( background_file_index ==2) { ROOT_name = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",mass_point);}
     if ( background_file_index ==3) { ROOT_name = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",mass_point);}

   ROOT_name = dir_name + ROOT_name;
//   ROOT_name = dir_name +"no_zprime_cut_"+ ROOT_name;
   }


bool save_flag = false;
save_flag = true;
if(save_flag){
 
   TFile *myFile = new TFile(ROOT_name,"recreate");

   h_CutFlow->Write();
   h_ele_pT->Write();
   h_lepton_pair_pT->Write();
   h_SD->Write();
   h_Z_mass->Write();
   h_Zprime_mass->Write();
   h_abs_dEta_ZH->Write();
   h_abs_dPhi_ZH->Write();
   h_abs_dR_ZH->Write();


   myFile->Close();
   delete myFile;
}


   // delete the finished used TH1D so it will not replacing the existing TH1 (no potential memory leak warning) when loop again 
/*
   delete h_CutFlow;
   delete h_ele_pT;
   delete h_lepton_pair_pT;
   delete h_SD;
   delete h_Z_mass;
*/
}
