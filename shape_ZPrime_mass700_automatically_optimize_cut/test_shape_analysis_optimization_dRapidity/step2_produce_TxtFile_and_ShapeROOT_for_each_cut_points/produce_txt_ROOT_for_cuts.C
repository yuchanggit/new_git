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

using namespace std;

void produce_txt_ROOT_for_cuts(){


  // basic definition
//  TString variable_name = "Ele_1st_pt" ;
  TString variable_name = "Abs_dRapidity_ZH";   //"Abs_dEta_ZH" ;
  cout<<"variable_name: " << variable_name << endl;

  const int N_cut_points = 10;
  const int N_signal_mass_points = 11;
  const int N_DYJetsHTbin_background_points = 4;

  double luminosity = 3000; // in pb^-1

  // define cuts
//  int cut_point[N_cut_points];
  double cut_point[N_cut_points];

  double lowest_cut=0.5 ;
  double scan_width = 0.5;

  for(int i=0;i<N_cut_points;i++){

	cut_point[i] = lowest_cut + scan_width*i;
	cout<<"cut_point[i]: "<< cut_point[i] << endl;
  }


  // define mass points
  int Zprime_mass[N_signal_mass_points]={800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000};



  // define the total number
  double total_number_signal[N_signal_mass_points];
  double total_number_DYJetHT[N_DYJetsHTbin_background_points];


// ---------------------------------------------------

  // define signal histogram for cuts
  TH1D* h_Zprime_mass_of_signal_sample_and_cut[N_signal_mass_points][N_cut_points];
  TString signal_histo_name[N_signal_mass_points][N_cut_points];

  double histo_start = 0, histo_end = 5000;
  double histo_width = 25;
  int Nbins = (histo_end - histo_start)/ histo_width; 
  cout<<"histo_start: "<< histo_start << endl;
  cout<<"histo_end: " << histo_end << endl;
  cout<<"Nbins: " << Nbins << endl;
 
  for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){
    for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
	signal_histo_name[signal_index][cut_index] = Form("h_Zprime_mass_in_signal_%d_cut_index_%d_for_", Zprime_mass[signal_index],cut_index); 
        signal_histo_name[signal_index][cut_index] = signal_histo_name[signal_index][cut_index] + variable_name;
//	cout<< signal_histo_name[signal_index][cut_index] << endl;
	h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index] = new TH1D(signal_histo_name[signal_index][cut_index],"",Nbins,histo_start,histo_end);
//      h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index] = new TH1D(signal_histo_name[signal_index][cut_index],"",200,0,5000);
    }
  }

  // define background DYJet HT histogram for cuts
  TH1D* h_Zprime_mass_of_DYJetHT_sample_and_cut[N_DYJetsHTbin_background_points][N_cut_points];
  TString DYJetHT_histo_name[N_DYJetsHTbin_background_points][N_cut_points];

  for(int DYJetHT_index=0;DYJetHT_index<N_DYJetsHTbin_background_points; DYJetHT_index++){
    for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
        DYJetHT_histo_name[DYJetHT_index][cut_index] = Form("h_Zprime_mass_in_DYJetHT_%d_cut_index_%d_for_", DYJetHT_index,cut_index);
        DYJetHT_histo_name[DYJetHT_index][cut_index] = DYJetHT_histo_name[DYJetHT_index][cut_index] + variable_name;
        h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index] = new TH1D(DYJetHT_histo_name[DYJetHT_index][cut_index],"",Nbins,histo_start,histo_end);

    }
  }


// ---------------------------------------------------
   


  // define the input files
  TString path = "../step1_apply_PreSelection_save_TTree/plot/";

  // signal
  TString inputFile_signal[N_signal_mass_points];
  for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){
    inputFile_signal[signal_index] = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[signal_index]);
    inputFile_signal[signal_index] = path + inputFile_signal[signal_index];
//    cout<< inputFile_signal[signal_index] << endl;
  }

  // DYJet HT bins background
  TString inputFile_DYJetHT[N_DYJetsHTbin_background_points];

  for(int DYJetHT_index=0;DYJetHT_index<N_DYJetsHTbin_background_points; DYJetHT_index++){
    inputFile_DYJetHT[DYJetHT_index] = "background_shape_DYJets_HT";

    TString DYJetHT_middle_name;
    if(DYJetHT_index==0){DYJetHT_middle_name = "100to200";}
    if(DYJetHT_index==1){DYJetHT_middle_name = "200to400";}
    if(DYJetHT_index==2){DYJetHT_middle_name = "400to600";}
    if(DYJetHT_index==3){DYJetHT_middle_name = "600toInf";}

    TString DYJetHT_last_name = "_in_Zprime_M-600.root";
    inputFile_DYJetHT[DYJetHT_index] = inputFile_DYJetHT[DYJetHT_index] + DYJetHT_middle_name + DYJetHT_last_name; 
    inputFile_DYJetHT[DYJetHT_index] = path + inputFile_DYJetHT[DYJetHT_index];
//    cout<< inputFile_DYJetHT[DYJetHT_index]  << endl;
  }








//------------------- open TTree and save events in histograms of each cuts ---------------------




  // open TTree for signal
  for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){
//    if(signal_index>1)continue;

    cout<<" read ROOT file:"<< inputFile_signal[signal_index]<< endl; 
 
    // input files
    TString inputFile = inputFile_signal[signal_index];
    TreeReader data(inputFile.Data());


    // Event loop
    for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

      if (jEntry % 50000 == 0)
        fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

      data.GetEntry(jEntry);

      Float_t   the_variable   = data.GetFloat(variable_name);	
      Float_t   Zprime_mass    = data.GetFloat("Zprime_mass");	

      // fill histogram for each cut points
      for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
	if(the_variable < cut_point[cut_index])
	  {h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index]->Fill(Zprime_mass);}

      }// end cut_index

    }// end event loop


    // test
    for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
//	cout<<"cut point: "<< cut_point[cut_index] << endl;
//	cout<<"histo total #: " << h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index]->Integral()<<endl;
    }// end cut_index

    // get total event
    TFile *file = new TFile (inputFile  );
    TH1D *h_eventWeight = (TH1D*) file -> Get("h_eventWeight");
    total_number_signal[signal_index] = h_eventWeight->Integral();
    delete h_eventWeight;
    file->Close();
    delete file;
    cout<<"total #:" << total_number_signal[signal_index] << endl;

  }// end signal_index 





  // open TTree for DYJetHT
  for(int DYJetHT_index=0;DYJetHT_index<N_DYJetsHTbin_background_points; DYJetHT_index++){
//    if(DYJetHT_index>1)continue;

    cout<<" read ROOT file:"<< inputFile_DYJetHT[DYJetHT_index]<< endl;
   
    // input files
    TString inputFile = inputFile_DYJetHT[DYJetHT_index];
    TreeReader data(inputFile.Data());

    // Event loop
    for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

      if (jEntry % 50000 == 0)
        fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

      data.GetEntry(jEntry);

      Float_t   the_variable   = data.GetFloat(variable_name);
      Float_t   Zprime_mass    = data.GetFloat("Zprime_mass");

      // fill histogram for each cut points
      for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
        if(the_variable < cut_point[cut_index])
          {h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index]->Fill(Zprime_mass);}

      }// end cut_index
    }// end event loop

     // test
         for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
//         cout<<"cut point: "<< cut_point[cut_index] << endl;
//         cout<<"histo total #: " << h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index]->Integral()<<endl;
         }// end cut_index

    // get total event
    TFile *file = new TFile (inputFile  );
    TH1D *h_eventWeight = (TH1D*) file -> Get("h_eventWeight");
    total_number_DYJetHT[DYJetHT_index] = h_eventWeight->Integral();
    delete h_eventWeight;
    file->Close();
    delete file;
    cout<<"total #:" << total_number_DYJetHT[DYJetHT_index] << endl;


  }// end DYJetHT_index 





// ---------------------------------------------------------------------



  // input the cross section text file

  // signal
  string xsect_file_th = "./13TeV_xsec_Zhllbb.txt"; 

  ifstream xsect_file(xsect_file_th.c_str(), ios::in);
  if (! xsect_file.is_open()) {
//    cout << "Failed to open file with xsections: " << xsect_file_th << endl;
  }

  float mZprime, CS;
  vector<float> v_mZprime, v_xs;


  int loop_counter =1;
  while (xsect_file.good()) {
    if(loop_counter>N_signal_mass_points)break;
    xsect_file >> mZprime >> CS;

    v_mZprime.push_back(mZprime);
    v_xs.push_back(CS);
    loop_counter = loop_counter +1;
  }
  cout << "Size of theory Zprime xsects vector " << v_mZprime.size() << endl;
  xsect_file.close();

  // test
  for(int i=0;i<v_mZprime.size();i++){
//    cout<< v_mZprime[i] <<" "<< v_xs[i]<<endl;
  }



  // DYJetHT background
  xsect_file_th = "./13TeV_xsec_DYJetHT.txt";

  ifstream xsect_file2(xsect_file_th.c_str(), ios::in);
  if (! xsect_file2.is_open()) {
    cout << "Failed to open file with xsections: " << xsect_file_th << endl;
  }

  string HT_range;  
  vector<string>  v_DYJetHT_range;
  vector<float>  v_xs_DYJetHT;

  loop_counter =1;
  while (xsect_file2.good()) {
    if(loop_counter> N_DYJetsHTbin_background_points)break;
    xsect_file2 >> HT_range >> CS;

    v_DYJetHT_range.push_back(HT_range);
    v_xs_DYJetHT.push_back(CS);
    loop_counter = loop_counter +1;
  }
  cout << "Size of theory DYJetHT xsects vector " << v_DYJetHT_range.size() << endl;
  xsect_file2.close();  

  // test and apply k-factor to correct the DYJet xsec
  double k_factor = 1.23;
  for(int i=0;i<v_DYJetHT_range.size();i++){
    v_xs_DYJetHT[i] = v_xs_DYJetHT[i] * k_factor; 
//    cout<< v_DYJetHT_range[i] <<" "<< v_xs_DYJetHT[i]<<endl;
  }

// ---------------------------------------------------


  // calcualte the weight

  double weight_signal[N_signal_mass_points];
  double weight_DYJetHT[N_DYJetsHTbin_background_points];

  // signal
  for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){
     weight_signal[signal_index] = v_xs[signal_index]/total_number_signal[signal_index];
     weight_signal[signal_index] = weight_signal[signal_index] * luminosity;  
//     cout<< weight_signal[signal_index] << endl;
  }

  // DYJetHt
  for(int DYJetHT_index=0;DYJetHT_index<N_DYJetsHTbin_background_points; DYJetHT_index++){
     weight_DYJetHT[DYJetHT_index] = v_xs_DYJetHT[DYJetHT_index]/total_number_DYJetHT[DYJetHT_index];
     weight_DYJetHT[DYJetHT_index] = weight_DYJetHT[DYJetHT_index] * luminosity;
//     cout<< weight_DYJetHT[DYJetHT_index] << endl;
  }





// ---------------------------------------------------




  // get the event yield and shape in corresponding luminosity 

  // signal
  double Event_yield_signal_sample_and_cut[N_signal_mass_points][N_cut_points];

  for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){
    for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){
      h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index]->Sumw2();
      h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index]->Scale( weight_signal[signal_index]   );
      double temp = h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index]->Integral();
      Event_yield_signal_sample_and_cut[signal_index][cut_index] = temp;
    }

    // test
//    cout<< Event_yield_signal_sample_and_cut[signal_index][0] << endl;
  }

  // DYJetHT
  double Event_yield_DYJetHT_sample_and_cut[N_DYJetsHTbin_background_points][N_cut_points];
  double Event_yield_DYJetHT_and_cut[N_cut_points] = {0};
  TH1D* h_Zprime_mass_of_DYJetHT_and_cut[N_cut_points];
  TString DYJetHT_histo_name_combine[N_cut_points];

  for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){ // the order of two loop is different to signal
    
    DYJetHT_histo_name_combine[cut_index] = Form("DYJetHT_cut_index_%f",cut_index);
    h_Zprime_mass_of_DYJetHT_and_cut[cut_index] = new TH1D(DYJetHT_histo_name_combine[cut_index],"",Nbins,histo_start,histo_end);
    h_Zprime_mass_of_DYJetHT_and_cut[cut_index]->Sumw2();

    for(int DYJetHT_index=0;DYJetHT_index<N_DYJetsHTbin_background_points; DYJetHT_index++){

      h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index]->Sumw2();
      h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index]->Scale( weight_DYJetHT[DYJetHT_index] );
      double temp = h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index]->Integral();
      Event_yield_DYJetHT_sample_and_cut[DYJetHT_index][cut_index] = temp;

      h_Zprime_mass_of_DYJetHT_and_cut[cut_index]->Add( h_Zprime_mass_of_DYJetHT_sample_and_cut[DYJetHT_index][cut_index]);
      Event_yield_DYJetHT_and_cut[cut_index] = Event_yield_DYJetHT_and_cut[cut_index] + Event_yield_DYJetHT_sample_and_cut[DYJetHT_index][cut_index];
    }

    // test
//    cout<<"cut: "<< cut_point[cut_index] << endl; 
//    cout<< Event_yield_DYJetHT_and_cut[cut_index] << endl;
//    cout<< h_Zprime_mass_of_DYJetHT_and_cut[cut_index]->Integral() << endl; 
  }

  // data
  double Event_yield_data = Event_yield_DYJetHT_and_cut[N_cut_points-1] + 2;
//  cout<< Event_yield_data << endl; 
  TH1D *h_data = (TH1D*) h_Zprime_mass_of_DYJetHT_and_cut[N_cut_points-1] ->Clone("data_obs");
  h_data->Sumw2();
  h_data->Scale( Event_yield_data / h_data->Integral()    );
//  cout<< h_data->Integral() << endl;




// ---------------------------------------------------




  // save the text file and the ROOT file

  TString save_dir = "text_and_ROOT_files/";
  TString data_name = "DATA";
  TString background_DYJets_name = "DYJETS";

  //ROOT file
  TString ROOT_name[N_cut_points];
  TString histo_name_signal[N_signal_mass_points];

  for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){ 

    ROOT_name[cut_index] = Form("_cut_%f",cut_point[cut_index]);
    ROOT_name[cut_index] = save_dir + "Zprime_shape_" + variable_name  + ROOT_name[cut_index] +".root";
//////    cout<< ROOT_name[cut_index] <<endl;

    TFile *myFile = new TFile(ROOT_name[cut_index],"recreate");

    // data
    h_data-> SetName("data_obs");
    h_data->Write();

    // signal
    for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){

      histo_name_signal[signal_index] = Form("M%d",Zprime_mass[signal_index]  );
      TString histo_name_signal_final = "SIG_" + histo_name_signal[signal_index] ;
      h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index] -> SetName(histo_name_signal_final );
      h_Zprime_mass_of_signal_sample_and_cut[signal_index][cut_index] ->Write();
    }

    // DYJetsHT background
    h_Zprime_mass_of_DYJetHT_and_cut[cut_index]-> SetName(background_DYJets_name);
    h_Zprime_mass_of_DYJetHT_and_cut[cut_index]-> Write();

    myFile->Close();
    delete myFile;
  }



  // text files

  TString text_name[N_cut_points];
  for(int cut_index=0;cut_index<N_cut_points; cut_index++ ){

    text_name[cut_index] = Form("_cut_%f",cut_point[cut_index]);
    text_name[cut_index] = save_dir + "YuHsiang_DY_" + variable_name + text_name[cut_index] + ".txt";
//    cout<< text_name[cut_index] << endl;

    // write text
    ofstream fout;
    fout.open( text_name[cut_index] );
    cout << endl << text_name[cut_index]  << endl<<endl;

    cout << data_name  << " " << Event_yield_data  << endl;
    fout << data_name  << " " << Event_yield_data  << endl;

    cout << background_DYJets_name << " " << Event_yield_DYJetHT_and_cut[cut_index]  << endl;
    fout << background_DYJets_name << " " << Event_yield_DYJetHT_and_cut[cut_index]  << endl;

    for(int signal_index=0;signal_index<N_signal_mass_points; signal_index++){

          cout << histo_name_signal[signal_index]   << " " << Event_yield_signal_sample_and_cut[signal_index][cut_index]  << endl;
          fout << histo_name_signal[signal_index]   << " " << Event_yield_signal_sample_and_cut[signal_index][cut_index]  << endl;
    }

    fout.close();

  }




}// end codes


















