#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"

#include <cstring>

using namespace std;



void collect_Event_Number(){

TString path = "plot/";
double corresponding_luminosity = 3000;// 3000/pb







// data
TString data_name = "DATA";
double n_Fianl_data = 0;// put zero by hand  









// Zprime the signal

  const int N_signal_mass_points = 13;
  int Zprime_mass[N_signal_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};

  TString signal_name[N_signal_mass_points];

  double n_Total_signal[N_signal_mass_points];
  TString ROOT_name_signal[N_signal_mass_points];

  double n_Pass_signal[N_signal_mass_points];

  double cross_section_signal[N_signal_mass_points]={ // unit in pb
0  //  M=600 I don't have 
,0.0282665
,0.0153743
,0.00790857
,0.00421385
,0.00233319
,0.00133522
,0.000785119
,0.000227178
,7.1426e-05
,2.35715e-05
,7.97489e-06
,0}; // M=4500 I don't have

  double n_Fianl_signal[N_signal_mass_points];

  for(int i=0;i<N_signal_mass_points;i++){

  	signal_name[i] = Form("M%d",Zprime_mass[i]);
//	cout<<"signal_name[i]: "<< signal_name[i] <<endl;

	ROOT_name_signal[i] = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[i]); 
	ROOT_name_signal[i] = path + ROOT_name_signal[i];

        TFile *f_1 = new TFile ( ROOT_name_signal[i] );

        TString histo_name1= "h_eventWeight" ;
        TH1D *h_1 = (TH1D*) f_1 -> Get(histo_name1);

	n_Total_signal[i] = h_1 ->Integral();// total number of event
//	cout<<"n_Total_signal[i]:" << n_Total_signal[i] << endl;

        TString histo_name2= "h_Zprime_mass" ;
        TH1D *h_2 = (TH1D*) f_1 -> Get(histo_name2);
	
	n_Pass_signal[i] = h_2 ->Integral();// number of event passing
//        cout<<"n_Pass_signal[i]:" << n_Pass_signal[i] << endl;
 
//	cout<<"cross_section_signal[i]"<< cross_section_signal[i] <<endl;

	n_Fianl_signal[i] = n_Pass_signal[i] * cross_section_signal[i] / n_Total_signal[i] * corresponding_luminosity; 
//        cout<<"n_Fianl_signal[i]:" << n_Fianl_signal[i] <<endl;
  }








// DYJetsHTbin background
const int N_DYJetsHTbin_background_points = 4;

  TString background_DYJets_name = "DYJETS";

  double n_Total_background_DYJets[N_DYJetsHTbin_background_points];
  TString ROOT_name_background_DYJets[N_DYJetsHTbin_background_points];

  double n_Pass_background_DYJets[N_DYJetsHTbin_background_points];

  double cross_section_background_DYJets[N_DYJetsHTbin_background_points]={ // unit in pb
  139.4 , 42.75 , 5.497 , 2.21};

  double n_Fianl_background_DYJets;
  double n_temp_background_DYJets = 0;// for combine # of 4 DYJets HT samples

  for(int i=0;i<N_DYJetsHTbin_background_points;i++){

     if(i==0 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT100to200_in_Zprime_M-600.root";}
     if(i==1 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT200to400_in_Zprime_M-600.root";}
     if(i==2 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT400to600_in_Zprime_M-600.root";}
     if(i==3 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT600toInf_in_Zprime_M-600.root";}

     ROOT_name_background_DYJets[i] = path + ROOT_name_background_DYJets[i];
//  cout<<"ROOT_name_background_DYJets[i]:"<< ROOT_name_background_DYJets[i] <<endl;

     TFile *f_1 = new TFile ( ROOT_name_background_DYJets[i] );

     TString histo_name1= "h_eventWeight" ;
     TH1D *h_1 = (TH1D*) f_1 -> Get(histo_name1);

     n_Total_background_DYJets[i] = h_1 ->Integral();// total number of event
//     cout<<"n_Total_background_DYJets[i]:" << n_Total_background_DYJets[i] << endl;

     TString histo_name2= "h_Zprime_mass" ;
     TH1D *h_2 = (TH1D*) f_1 -> Get(histo_name2);

     n_Pass_background_DYJets[i] = h_2 ->Integral();// number of event passing
//     cout<< "n_Pass_background_DYJets[i]:" << n_Pass_background_DYJets[i] << endl; 

     cross_section_background_DYJets[i] = cross_section_background_DYJets[i] * 1.23 ;// apply the k-factor
//     cout<<"cross_section_background_DYJets[i]:"<< cross_section_background_DYJets[i] <<endl;

     n_temp_background_DYJets = n_temp_background_DYJets + (n_Pass_background_DYJets[i]*cross_section_background_DYJets[i]/n_Total_background_DYJets[i]); 

//  cout<<""<< <<endl;
  }

n_Fianl_background_DYJets = n_temp_background_DYJets * corresponding_luminosity ;
//  cout<<"n_Fianl_background_DYJets: "<< n_Fianl_background_DYJets <<endl;








// save number to txt file

  ofstream fout;
  fout.open("YuHsiang_DY.txt");

  fout << data_name  << " " << n_Fianl_data  << endl;

  fout << background_DYJets_name << " " << n_Fianl_background_DYJets  << endl;

  for(int i=0;i<N_signal_mass_points;i++){
	if(i==0)continue;
        if(i==12)continue;
	fout << signal_name[i]   << " " << n_Fianl_signal[i]  << endl;
  }

  fout.close();

//  fout <<   << " " <<   << endl;

/*












//  prepare the weights for 4 background samples

const int N_background_points = 4;
double background_cross_section[N_background_points] = { 139.4 , 42.75 , 5.497 , 2.21 };
double background_number_of_events[N_background_points] =   { 2327916 , 955972 , 1038512 , 974623 };
double background_weights[N_background_points];

for(int i=0;i<N_background_points;i++) 
{
 background_cross_section[i] = background_cross_section[i] * 1.23 ;// apply the k-factor in xsection of DYJet sample
  
 background_weights[i] = background_cross_section[i] / background_number_of_events[i];  

}

 int rebin_times = 1;
// int rebin_times = 16;


 // prepare all thing used in below

  const int N_mass_points = 13;
  int Zprime_mass[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
  TString path = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/plot_SubLedaing_ele_pt_optimize/";

  double Zprime_cross_sections[N_mass_points]={
0  //  M=600 I don't have 


,0.0282665
,0.0153743
,0.00790857
,0.00421385
,0.00233319
,0.00133522
,0.000785119
,0.000227178
,7.1426e-05
,2.35715e-05
,7.97489e-06
,0}; // M=4500 I don't have

  double Zprime_number_of_events[N_mass_points]={
49400,
48400,
50000,
50000,
50000,
50000,
50000,
50000,
50000,
50000,
49800,
50000,
50000};


double Zprime_weights[N_mass_points];

for(int i=0;i<N_mass_points;i++)
{ Zprime_weights[i] = Zprime_cross_sections[i] / Zprime_number_of_events[i];}


double Event_number_Zprime[N_mass_points] = {0};








  // combine the 4 background shape to get the Zprime mass distribution 

  TH1D *h_background_ZH_mass_combine;
  double Event_number_DYJets = 0;// weight to L = 1/pb

bool Zprime_mass_combined_background = false;
Zprime_mass_combined_background = true;
if(Zprime_mass_combined_background)
  {     // Zprime_mass[0] is M = 600 

  for(int i=0;i<13;i++){// mass point
  if(i!=0)continue;

	// prepare the background sample name
        TString background_shape_file[N_background_points];
        for(int l=0 ; l<N_background_points ; l++ ){
                if(l==0 ){ background_shape_file[l] = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[i]);}
                if(l==1 ){ background_shape_file[l] = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[i]);}
                if(l==2 ){ background_shape_file[l] = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[i]);}
                if(l==3 ){ background_shape_file[l] = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[i]);}
        }// loop l background shape file 

	// prepare a template histogram and reset it 
        TString template_name = path + background_shape_file[i] ;
        TFile *f_template = new TFile ( template_name );
        TString histo_name= "h_Zprime_mass" ;
        TH1D *h_template;
        h_template = (TH1D*) f_template -> Get(histo_name);

        TH1D *h_background_2nd_ele_pT_combine = (TH1D*) h_template ->Clone("");
        h_background_2nd_ele_pT_combine->Reset();
	h_background_2nd_ele_pT_combine->Sumw2();

	// loop background sample, open, weight, and add
        for(int i=0; i<N_background_points;i++){

		// open
		cout<<"open background sample: "<< background_shape_file[i] << endl;
                background_shape_file[i] = path + background_shape_file[i];
                TFile *f_background = new TFile ( background_shape_file[i] );
                TH1D *h_background_2nd_ele_pT;
                h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);
		h_background_2nd_ele_pT->Sumw2();

		// weight
                double event_number_sample = 0;
                event_number_sample = h_background_2nd_ele_pT->Integral();
		h_background_2nd_ele_pT->Scale(background_weights[i]  );
//		event_number_sample = h_background_2nd_ele_pT->Integral();
		cout<<"event_number_sample: "<<event_number_sample << endl; 
//		event_number_sample = event_number_sample * background_weights[i]* 3000; 
                event_number_sample = event_number_sample * background_weights[i]; 
                cout<<"event_number_sample after weighted to L=1/pb: "<<event_number_sample << endl;


		// add
                h_background_2nd_ele_pT_combine ->Add(h_background_2nd_ele_pT);
		Event_number_DYJets = Event_number_DYJets +event_number_sample;



        }// loop i background shape file

//        TCanvas *c6 = new TCanvas("background_Zprime_mass","",200,10,700,500);
//	c6->cd();
	h_background_2nd_ele_pT_combine->Rebin(rebin_times);
//	h_background_2nd_ele_pT_combine->Draw();

     h_background_ZH_mass_combine = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("h_background_ZH_mass_combine");// bring the histogram to outside the if 
     h_background_ZH_mass_combine->SetStats(0);
     h_background_ZH_mass_combine->SetTitle("");
     h_background_ZH_mass_combine->GetXaxis()->SetTitle("M_{ZH} [ GeV]");

     }// loop i



  }// end if


//h_background_ZH_mass_combine->Draw();



  // open signal

  TH1D *h_signal_ZH_mass[N_mass_points]; 
  TH1D *h_signal_ZH_mass_new_name[N_mass_points];

  bool open_signal_flag = false;
  open_signal_flag = true;
  if(open_signal_flag){

  for(int i=0;i<13;i++){// mass point

        // open the signal ROOT file
        TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[i]);
        signal_shape_file = path + signal_shape_file ;
        TFile *f_signal = new TFile (signal_shape_file);

        // open the signal histogram
        TString histo_name= "h_Zprime_mass" ;
        h_signal_ZH_mass[i] = (TH1D*) f_signal -> Get(histo_name);
//	h_signal_ZH_mass[i]->Draw();

	// number and weight
        double event_number_sample = 0;
        event_number_sample = h_signal_ZH_mass[i]->Integral();
        Event_number_Zprime[i] = event_number_sample * Zprime_weights[i];


	// set new name
        TString new_signal_name = Form("h_signal_ZH_mass_for_Zprime_M_%d",Zprime_mass[i]); 
	h_signal_ZH_mass_new_name[i] = (TH1D*) h_signal_ZH_mass[i] ->Clone(new_signal_name);
	h_signal_ZH_mass_new_name[i]->SetStats(0);
     	h_signal_ZH_mass_new_name[i]->SetTitle("");
        h_signal_ZH_mass_new_name[i]->GetXaxis()->SetTitle("M_{ZH} [ GeV]");

	

  }// end loop

  }// end if






  // cout the Event number of sample after selection and weighted to L=1/pb

  bool event_collect_flag = false;
  event_collect_flag = true;
if(event_collect_flag){

  double luminosity = 3000; // L=3/fb


  cout<<"cout the Event number of sample after selection and weighted to L=3000/pb"<<endl;

  Event_number_DYJets = Event_number_DYJets * luminosity;
  cout<<"DYJets: "<< Event_number_DYJets <<endl;  

  for(int i=0; i<N_mass_points;i++){
    if(i==0 || i==12)continue;

    Event_number_Zprime[i] = Event_number_Zprime[i] * luminosity;	
//    cout<<"signal sample index i: "<< i << endl;
    cout<<"Zprime_mass[i]= "<< Zprime_mass[i] <<" Event number:  "<< Event_number_Zprime[i] <<endl;


  }

}










  // save the ZH mass histogram 

  TString ROOT_name = "ZH_invariant_mass.root";
  ROOT_name = path + ROOT_name;

  bool save_flag = false;
//  save_flag = true;
  if(save_flag){

  	TFile *myFile = new TFile(ROOT_name,"recreate");
	h_background_ZH_mass_combine->Write();

	for(int i=0;i<13;i++){
        	h_signal_ZH_mass_new_name[i]->Write();
	}

   myFile->Close();
   delete myFile;

  }//end if

*/


}





