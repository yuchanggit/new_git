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


using namespace std;

void select_electrons(TreeReader &, vector<int> * );


void xAna_ele_subleading_ele_pt_optimize(TString inputFile, TCanvas *c1 , TCanvas *c2 , TCanvas *c3 ,TCanvas *c4 ,TCanvas *c5 , TCanvas *c6 ,
int mass_point ,double eff,double eff_err, TString dir_name, int dir_flag ,int signal_background_flag, int background_file_index ){


  // define histograms

  TString title2 = Form("ele pT for Zprime mass = %d",mass_point);
  TString title3 = Form("lepton pairs' pT for Zprime mass = %d",mass_point);
  TString title4 = Form("SD mass for Zprime mass = %d",mass_point);
  TString title5 = Form("Z mass for Zprime mass = %d",mass_point);
  TString title6 = Form("Zprime mass for Zprime mass = %d",mass_point);

  TH1D* h_ele_pT = new TH1D("h_ele_pT", title2 ,3000 , 0,3000 );
  TH1D* h_lepton_pair_pT = new TH1D("h_lepton_pair_pT", title3 ,400 , 0,4000 );
  TH1D* h_SD =new TH1D("h_SD",title4 ,100,0,200);
  TH1D* h_Z_mass= new TH1D("h_Z_mass",title5 ,250,0,500);
  TH1D* h_Zprime_mass= new TH1D("h_Zprime_mass",title6 ,1000,0,5000);

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

/*
    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");
    Int_t* genDa1      = data.GetPtrInt("genDa1");
    Int_t* genDa2      = data.GetPtrInt("genDa2");
    Int_t* genMo1      = data.GetPtrInt("genMo1");
    Int_t* genMo2      = data.GetPtrInt("genMo2");

    bool hasLepton=false;

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=23)continue;


      int da1=genDa1[ig];
      int da2=genDa2[ig];


      if(da1<0 || da2<0)continue;
      int da1pdg = genParId[da1];
      int da2pdg = genParId[da2];


      if(abs(da1pdg)==11)
     	hasLepton=true;

      if(hasLepton)break;

    }
*/

/*
    // 1. make sure there is a h-> bb, Yu-Hsiang change it
    bool hasHadron=false;

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=25)continue;
      int da1=genDa1[ig];
      int da2=genDa2[ig];

      if(da1<0 || da2<0)continue;
      int da1pdg = genParId[da1];
      int da2pdg = genParId[da2];

      if(abs(da1pdg)==5)
     	hasHadron=true;

      if(hasHadron)break;

    }
*/  
  
 //   if(!hasLepton)continue;
    nPass[0]++;
//    if(!hasHadron)continue;
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
    Int_t nEle         = data.GetInt("nEle");
    Int_t run          = data.GetInt("runId");
    Int_t lumi         = data.GetInt("lumiSection");
    Int_t event        = data.GetInt("eventId");
    vector<bool> &passHEEPID = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    vector<bool> &passLoose = *((vector<bool>*) data.GetPtr("eleIsPassLoose"));
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
    Float_t* eleSCEt          = data.GetPtrFloat("eleScEt");
    Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");
    Int_t*   eleCharge        = data.GetPtrInt("eleCharge");

    //5. select good electrons

    // save index of electron accepted by ElectronSelection.h
    std::vector<int> accepted;
    select_electrons(data, &accepted);

    std::vector<int> goodElectrons;

    for(int ie=0; ie< nEle; ie++)
      {

        TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

        if(fabs(thisEle->Eta())>2.5)continue;

        if(! (fabs(eleSCEta[ie])<1.442 || fabs(eleSCEta[ie])>1.566))continue;

	float ele_pt = thisEle->Pt();
//	cout<<"ie: "<< ie <<endl;
//        cout<<"before accepted" <<endl;
//        cout<<"ele_pt: "<< ele_pt <<endl;

//        if      (dir_flag == 1) {if(!passHEEPID[ie])continue;}
//        else if (dir_flag == 2) {if(!passLoose[ie])continue;}

	// using the cut in ElectronSelection.h
        bool has_accepted = false;
	for(int j=0; j< accepted.size();j++)
		{ if(ie == accepted[j]){has_accepted=true; break;}  }
	if(!has_accepted)continue;

//        cout<<"after accepted" <<endl;
//        cout<<"ele_pt: "<< ele_pt <<endl;

        if(eleMiniIso[ie]>0.1)continue;

        goodElectrons.push_back(ie);
      }

    // 

	
    //6. select a good Z boson
    bool findEPair=false;
    TLorentzVector l4_Z(0,0,0,0);
    std::vector<double> LeptonPairPt;
    std::vector<double> LeptonPairM;
    std::vector<int> leading_ele_index;
    std::vector<int> subleading_ele_index;


    for(unsigned int i=0; i< goodElectrons.size(); i++)
      {
        int ie = goodElectrons[i];
        TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

        for(unsigned int j=0; j< i; j++)
          {
            int je= goodElectrons[j];

            if(eleCharge[ie]*eleCharge[je]>0)continue;


            TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);

//	    float pt1 = thisEle->Pt();
//          float pt2 = thatEle->Pt();

            float pt1 = eleSCEt[ie];// use Super Cluster Et to replace using pt
            float pt2 = eleSCEt[je];

            float ptmax = TMath::Max(pt1,pt2);
            float ptmin = TMath::Min(pt1,pt2);
            if(ptmax<115)continue;
//            if(ptmin<35)continue;
            if(ptmin<10)continue;

            int leadingIndex = pt1>pt2? ie : je;
            int subleadingIndex = pt1 > pt2? je : ie;

            Float_t ptll = (*thisEle+*thatEle).Pt();
            Float_t mll  = (*thisEle+*thatEle).M();
            if(mll<70 || mll>110)continue;
//	    if(ptll<100)continue;
            if(ptll<120)continue;

            leading_ele_index.push_back(leadingIndex);
            subleading_ele_index.push_back(subleadingIndex);

            LeptonPairPt.push_back(ptll);
            LeptonPairM.push_back(mll);


            if(!findEPair)l4_Z=(*thisEle+*thatEle);

            findEPair=true;
          }
      }


    if(!findEPair)
      continue;
    nPass[4]++;


    //7.select a good CA8 and cleaned jet

    // first select muons for cleaning against jet
    std::vector<int> goodMuons;
    Int_t nMu          = data.GetInt("nMu");
    vector<bool> &isHighPtMuon = *((vector<bool>*) data.GetPtr("isHighPtMuon"));
    vector<bool> &isCustomTrackerMuon = *((vector<bool>*) data.GetPtr("isCustomTrackerMuon"));
    TClonesArray* muP4 = (TClonesArray*) data.GetPtrTObject("muP4");
    Float_t* muMiniIso       = data.GetPtrFloat("muMiniIso");

    for(int im=0; im< nMu; im++)
      {

    	TLorentzVector* thisMu = (TLorentzVector*)muP4->At(im);

    	if(!isHighPtMuon[im] && !isCustomTrackerMuon[im])continue;
    	
    	if(muMiniIso[im]>0.1)continue;	

        if ( goodMuons.size()==1 ) {
	  bool highPt_AND_tracker = isHighPtMuon[0] && isCustomTrackerMuon[im];
	  bool tracker_AND_highPt = isHighPtMuon[im] && isCustomTrackerMuon[0]; 
            if ( !(highPt_AND_tracker or tracker_AND_highPt) ) continue; 
        }

    	if(fabs(thisMu->Eta())>2.1)continue;

    	if(thisMu->Pt() < 50)continue;

    	goodMuons.push_back(im);
      }

	
    Int_t nJet         = data.GetInt("FATnJet");
    TClonesArray* jetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  jetSDmass = data.GetPtrFloat("FATjetSDmass");
    Float_t*  jetPRmass = data.GetPtrFloat("FATjetPRmass");

    std::vector<double> SD_Mass;
    TLorentzVector l4_leadingJet(0,0,0,0);
    bool findAJet=false;
    for(int ij=0; ij<nJet; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)jetP4->At(ij);


//        double SD_low = 60, SD_high = 140;
//        if(jetSDmass[ij]<SD_low || jetSDmass[ij]>SD_high)continue;

        double PR_low = 95, PR_high = 130;
        if(jetPRmass[ij]<PR_low || jetPRmass[ij]>PR_high)continue;


	bool hasOverLap=false;

{
        TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(leading_ele_index[0]);
        if(thisEle->DeltaR(*thisJet)<0.8)hasOverLap=true;

        TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(subleading_ele_index[0]);
        if(thatEle->DeltaR(*thisJet)<0.8)hasOverLap=true;
}
	for(unsigned int im=0; im < goodMuons.size(); im++)
	  {
	    TLorentzVector* thisMuo = (TLorentzVector*)muP4->At(goodMuons[im]);
	    if(thisMuo->DeltaR(*thisJet)<0.8)hasOverLap=true;
	    if(hasOverLap)break;
	    
	  }
	
	if(hasOverLap)continue;
	
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;

     	if(!findAJet)
	  {
	    l4_leadingJet = *thisJet;
//	    h_SD->Fill(jetSDmass[ij]);
            SD_Mass.push_back( jetSDmass[ij] );
	  }
	    
     	findAJet=true;
//        SD_Mass.push_back( jetSDmass[ij] ); // change to this place so that loop to all jets passing cuts    	

      }
    
    if(!findAJet)
      continue;
    nPass[5]++;

     Float_t MGrav = (l4_leadingJet + l4_Z).M();

     double Mass_Point = mass_point;
     double mass_upper = Mass_Point + Mass_Point*0.15;
     double mass_lower = Mass_Point - Mass_Point*0.15;
//     cout<<"Mass_Point: "<<Mass_Point  <<" mass_upper: "<< mass_upper <<" mass_lower: "<< mass_lower <<endl;

     if( MGrav< mass_lower || MGrav>mass_upper )continue;
     h_Zprime_mass->Fill( MGrav );
     nPass[6]++;

  // if event can go here, then fill the histograms to plot the distributions. Yu-Hsiang add 


{

//    int ie = leading_ele_index[0];
    int ie = subleading_ele_index[0];
//    TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);
//    h_ele_pT->Fill( thisEle->Pt() );
//    if(eleSCEt[ie]<10){    cout<<"eleSCEt[ie]: "<< eleSCEt[ie] << endl;}
//   cout<<"eleSCEt[ie]: "<< eleSCEt[ie] << endl;
    h_ele_pT->Fill( eleSCEt[ie] );

//cout<<endl;
//cout<< "jEntry: "<< jEntry <<endl;

//cout<<"ie: " << ie<< endl;
//cout<<"thisEle->Pt(): " << thisEle->Pt()<< endl;


}
/*
    for(unsigned int i=0; i< LeadingElectrons.size(); i++)
      {         int ie = LeadingElectrons[i];
		TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);
		h_ele_pT->Fill( thisEle->Pt() );
      }
*/
    for(unsigned int i=0; i< LeptonPairPt.size(); i++)
      {         
                
                h_lepton_pair_pT->Fill( LeptonPairPt[i] );
      }

    for(unsigned int i=0; i< LeptonPairM.size(); i++)
      {

                h_Z_mass->Fill( LeptonPairM[i] );
      }

    for(unsigned int i=0; i< SD_Mass.size(); i++)
      {

                h_SD->Fill( SD_Mass[i] );
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
