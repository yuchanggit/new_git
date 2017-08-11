#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <deque>
#include <list>

#include <TPaveStats.h>
#include <TH1D.h>
#include <TFile.h>
#include <TF1.h>
#include <TPad.h>
#include <TFile.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TTree.h>
#include "TObject.h"
#include "TColor.h"
#include "TFile.h"
#include "TMarker.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TString.h"
#include "TMath.h"
#include "TChain.h"
#include "TCut.h"

#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooExtendPdf.h"
#include "RooAbsReal.h"
#include "RooDataHist.h"
#include "RooGenericPdf.h"

using namespace RooFit ;
using namespace std;

//#include "cut_value.h"
//#include "make_histogram.C"
//#include "supportHeader.h"
//#include "predict_ZH.C"

//double Xmin,Xmax,Ymin,Ymax;
//TString XTitle,YTitle;

void bumpHuntingFit(){


  // get the RooDataSet of Signle Ele data and Single Mu data
  // -------------------------------------------------------

  TString path_eleData = "root:///Users/index0192/alphabet_plot/skimTTree_sample/output_ele_20170310/SingleElectron_Run2016BCDEFGH_MiniTree.root";

  TString path_muData = "root:///Users/index0192/alphabet_plot/skimTTree_sample/output_mu_20170307/SingleMuon_Run2016BCDEFGH_MiniTree.root";

  TFile* f_eleData = TFile::Open( path_eleData );
  TFile* f_muData  = TFile::Open( path_muData  );


  TTree* tree_eleData = (TTree*) f_eleData ->Get("new_tree");
  TTree* tree_muData  = (TTree*) f_muData  ->Get("new_tree");

  RooRealVar SDmass        ("Jet_SDmass_corrected" ,"Jet_SDmass_corrected" ,0 ,500) ;
  RooRealVar DoubleBTagger ("Double_bTagger_ADDjet","Double_bTagger_ADDjet",-1,1) ;
  RooRealVar ZHmass        ("ZHmass"               ,"ZHmass"               ,0 ,8000) ;

  ZHmass.setRange(0,8000);
  ZHmass.setBins(160);

  // convert TTree to RooDataSet, the RooRealVar's title name must be identical with Branch's name in TTree 
  RooDataSet eleData ("eleData","eleData", tree_eleData ,RooArgSet( SDmass , DoubleBTagger , ZHmass ) );
  RooDataSet muData  ("muData" ,"muData" , tree_muData  ,RooArgSet( SDmass , DoubleBTagger , ZHmass ) );

  RooDataSet combineData ("combineData","ele + mu data", tree_eleData ,RooArgSet( SDmass , DoubleBTagger , ZHmass ) );
  combineData.append(muData) ;

  TCut SR_Cut = " Jet_SDmass_corrected>65 && Jet_SDmass_corrected<135 && Double_bTagger_ADDjet>0.3 && ZHmass>700 ";
  TCut CR_Cut = " Jet_SDmass_corrected>65 && Jet_SDmass_corrected<135 && Double_bTagger_ADDjet<0.3 && ZHmass>700 ";

  RooDataSet* SR_Data = (RooDataSet*) combineData.reduce( Cut( SR_Cut  ) );
  RooDataSet* CR_Data = (RooDataSet*) combineData.reduce( Cut( CR_Cut  ) );



  // plot SR, CR dataset

  RooPlot* test_frame1 = SDmass.frame(Title("SR in SDmass")) ;
  SR_Data->plotOn(test_frame1 ); SR_Data->statOn(test_frame1) ;
  TCanvas* c1 = new TCanvas("c1","c1",800,600) ;
  c1->cd(); test_frame1->Draw() ;


  RooPlot* test_frame2 = DoubleBTagger.frame(Title("SR in doubleBTagger")) ;
  SR_Data->plotOn(test_frame2 );SR_Data->statOn(test_frame2) ;
  TCanvas* c2 = new TCanvas("c2","c2",800,600) ;
  c2->cd(); test_frame2->Draw() ;


  RooPlot* test_frame3 = ZHmass.frame(Title("SR in ZHmass")) ;
  SR_Data->plotOn(test_frame3 );SR_Data->statOn(test_frame3) ;
  TCanvas* c3 = new TCanvas("c3","c3",800,600) ;
  c3->cd(); test_frame3->Draw() ;

  RooPlot* test_frame4 = SDmass.frame(Title("CR in SDmass")) ;
  CR_Data->plotOn(test_frame4 );CR_Data->statOn(test_frame4) ;
  TCanvas* c4 = new TCanvas("c4","c4",800,600) ;
  c4->cd(); test_frame4->Draw() ;


  RooPlot* test_frame5 = DoubleBTagger.frame(Title("CR in doubleBTagger")) ;
  CR_Data->plotOn(test_frame5 );CR_Data->statOn(test_frame5) ;
  TCanvas* c5 = new TCanvas("c5","c5",800,600) ;
  c5->cd(); test_frame5->Draw() ;


  RooPlot* test_frame6 = ZHmass.frame(Title("CR in ZHmass")) ;
  CR_Data->plotOn(test_frame6 );CR_Data->statOn(test_frame6) ;
  TCanvas* c6 = new TCanvas("c6","c6",800,600) ;
  c6->cd(); test_frame6->Draw() ;




  // build PDF and fit
  // --------------------------------------------------------

  RooRealVar p1 ("p1","p1",-10 ,10) ;
  RooRealVar p2 ("p2","p2",-10 ,10) ;

  RooGenericPdf CR_model = RooGenericPdf("CR_mode","exp(-@0*@2/(1+(@0*@1*@2)))",RooArgList( ZHmass , p1, p2 ) );

  RooFitResult* fit_res1 = CR_model.fitTo(*CR_Data, RooFit::Minimizer("Minuit2"), RooFit::Range(700, 2000), RooFit::SumW2Error(kTRUE), RooFit::Save());

  cout<<"fit_res1->status(): "<< fit_res1->status() << endl;


  RooPlot* test_frame7 = ZHmass.frame(Title("fit CR in ZHmass")) ;

  CR_Data->plotOn(test_frame7 ,RooFit::Range(700, 2000) );
  CR_model.plotOn(test_frame7 ,RooFit::Range(700, 2000) );

  CR_Data->statOn(test_frame7) ;


  TCanvas* c7 = new TCanvas("c7","c7",800,600) ;
  c7->cd(); test_frame7->Draw() ;










  // -----------------------------------------------------
  // Part-I: make histogram
//  cout<<endl<<" Part-I: make histogram "<<endl<<endl; 


/*
  // use TChain to combine ele + mu dataset
  TChain* tree = new TChain("new_tree");

  std::string open_root;

  open_root="root:///Users/index0192/alphabet_plot/skimTTree_sample/output_mu_20170307/SingleMuon_Run2016BCDEFGH_MiniTree.root"  ;
  tree->Add( open_root.c_str()  );

  open_root="root:///Users/index0192/alphabet_plot/skimTTree_sample/output_ele_20170310/SingleElectron_Run2016BCDEFGH_MiniTree.root";
  tree->Add( open_root.c_str()  );

  cout<<"tree->GetEntries: "<< tree->GetEntries() << endl;
  std::string sample_name = "combine_ele_mu_Run2016";
*/



// --------------------------------------------------------------------------------------------------------------------------------------------------------//


/*

  // define histogram
  const int NXbins4 = 9;
  double xbins4[NXbins4+1]={ 50, 54, 65, 80, 100,120,135 ,155, 175,200 };

  TH1F* h_passDoubleBTagger_Jmass_wideBinning_diff = new TH1F("h_passDoubleBTagger_Jmass_wideBinning_diff" ,"passDoubleBTagger Jmass wideBinning ",NXbins4, xbins4);

  TH1F* h_failDoubleBTagger_Jmass_wideBinning_diff = (TH1F*) h_passDoubleBTagger_Jmass_wideBinning_diff ->Clone("h_failDoubleBTagger_Jmass_wideBinning_diff");
  h_failDoubleBTagger_Jmass_wideBinning_diff->Reset();

  TH1F* h_Ratio_wideBinning = (TH1F*) h_passDoubleBTagger_Jmass_wideBinning_diff ->Clone("h_Ratio_wideBinning");
  h_Ratio_wideBinning->Reset();

  make_histogram( sample_name,
		  tree , 
		  h_passDoubleBTagger_Jmass_wideBinning_diff,
		  h_failDoubleBTagger_Jmass_wideBinning_diff,
		  h_Ratio_wideBinning
  		);




  // ----------------------------------------------------------
  // part-II: fit pass/fail ratio
  cout<<endl<<" Part-II: fit pass/fail ratio "<<endl<<endl;



  Xmin= 30; Xmax=200; Ymin= -1; Ymax= 1;
  XTitle= "Corrected Soft Drop Mass [GeV]";

  YTitle= "Pass / Fail Ratio";
  Set_h1_Style( h_Ratio_wideBinning , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );

  h_Ratio_wideBinning ->GetYaxis ()->SetRangeUser(0 ,1 );

  // Draw
  TCanvas* c3 = new TCanvas("c3","c3",10,10,800,600);
  c3->cd(); h_Ratio_wideBinning -> Draw();

  // Fit
  gStyle->SetOptFit(11111111);
  double parameters[10];   TF1* fn_1;

//  fn_1 = new TF1("fn_1", fline_Linear ,50,200,2);
//  parameters[0] = 0.00002; parameters[1] = -0.0032; 
//  Fit_TwoRange( h_Ratio_wideBinning , fn_1 , "Linear", parameters );


  fn_1 = new TF1("fn_1", fline_Quadric ,50,200,3);
  parameters[0] = 0.00002; parameters[1] = -0.0032; parameters[2] = 0.15;
  Fit_TwoRange( h_Ratio_wideBinning , fn_1 , "Quadric", parameters );

//  fn_1 = new TF1("fn_1", fline_Cubic ,50,200,4);
//  parameters[0] = -0.00000068; parameters[1] = 0.00024; parameters[2] = -0.026; parameters[3] = 0.98;
//  Fit_TwoRange( h_Ratio_wideBinning , fn_1 , "Cubic", parameters );


  double mychi2 = GetMyChisquare ( h_Ratio_wideBinning , fn_1 );
  cout<<"mychi2: "<< mychi2 << endl;
*/

  // F-test
/*
  TF1* fn_power1; TF1* fn_power2; TF1* fn_power3 ;

  fn_power1 = new TF1("fn_power1", fline_Linear ,50,200,2);
  parameters[0] = 0.00002; parameters[1] = -0.0032; 
  Fit_TwoRange( h_Ratio_wideBinning , fn_power1 , "Linear", parameters );

  fn_power2 = new TF1("fn_power2", fline_Quadric ,50,200,3);
  parameters[0] = 0.00002; parameters[1] = -0.0032; parameters[2] = 0.15;
  Fit_TwoRange( h_Ratio_wideBinning , fn_power2 , "Quadric", parameters );

  fn_power3 = new TF1("fn_power3", fline_Cubic ,50,200,4);
  parameters[0] = -0.00000068; parameters[1] = 0.00024; parameters[2] = -0.026; parameters[3] = 0.98;
  Fit_TwoRange( h_Ratio_wideBinning , fn_power3 , "Cubic", parameters );


  double f_value_test = 0; double f_result_test = 0;

  cout<<endl<<"fn_power1 to fn_power2"<< endl;
  My_Ftest( h_Ratio_wideBinning , fn_power1 , fn_power2 , f_value_test, f_result_test);
  cout<<"f_value_test: "<< f_value_test << endl; cout<<"f_result_test: "<< f_result_test << endl;

  double chi2_fn1 = GetMyChisquare ( h_Ratio_wideBinning , fn_power1 );
  double chi2_fn2 = GetMyChisquare ( h_Ratio_wideBinning , fn_power2 );
  cout<<"fn_power1's chi2: "<< chi2_fn1 << endl;
  cout<<"fn_power2's chi2: "<< chi2_fn2 << endl;

*/

/*
  cout<<endl<<"fn_power2 to fn_power3"<< endl;
  My_Ftest( h_Ratio_wideBinning , fn_power2 , fn_power3 , f_value_test, f_result_test);
  cout<<"f_value_test: "<< f_value_test << endl; cout<<"f_result_test: "<< f_result_test << endl;

  double chi2_fn2 = GetMyChisquare ( h_Ratio_wideBinning , fn_power2 );
  double chi2_fn3 = GetMyChisquare ( h_Ratio_wideBinning , fn_power3 );
  cout<<"fn_power2's chi2: "<< chi2_fn2 << endl;
  cout<<"fn_power3's chi2: "<< chi2_fn3 << endl;
*/


/*
  // estimate area in validation region

  double Area_histo = GetMyHisto_Area(h_Ratio_wideBinning , Vmin , Vmax);
  double Area_fit   = fn_1->Integral(Vmin,Vmax);

  cout<<" Area in Validate of h_Ratio["<<Vmin<<","<<Vmax<<"]: "<< Area_histo<< endl ;
  cout<<" Area in Validate of fit ["<<Vmin<<","<<Vmax<<"]: "<< Area_fit<< endl ;
  cout<<"diff: "<< (Area_fit - Area_histo)/Area_histo << endl;
*/



/*

  // ----------------------------------------------------------
  // Part-III: predict ZH mass
  cout<<endl<<" Part-III: predict ZH mass "<<endl<<endl;


  // define histogram
  
  TH1F* h_ZH_mass_pass = new TH1F("h_ZH_mass_pass" ,"h_ZH_mass_pass",100,0,5000);

  TH1F* h_ZH_mass_fail = (TH1F*) h_ZH_mass_pass -> Clone("h_ZH_mass_fail");
  h_ZH_mass_fail->Reset();

  TH1F* h_ZH_mass_pass_predict = (TH1F*) h_ZH_mass_pass -> Clone("h_ZH_mass_pass_predict");
  h_ZH_mass_pass_predict->Reset();


  h_ZH_mass_pass ->Sumw2();
  h_ZH_mass_fail ->Sumw2();
  h_ZH_mass_pass_predict ->Sumw2();


  predict_ZH(    h_ZH_mass_pass,
                 h_ZH_mass_fail,
                 h_ZH_mass_pass_predict,
                 fn_1,
		 sample_name,
                 tree
               );

*/

  // estimate difference in ZH mass

/*
  double pass_area = h_ZH_mass_pass->Integral(); 
  double pass_area_predict = h_ZH_mass_pass_predict->Integral();

  cout<<" Area in h_ZH_mass_pass: "<< pass_area << endl ;
  cout<<" Area in h_ZH_mass_pass_predict:: "<< pass_area_predict << endl ;
  cout<<"relative difference in ZH mass : "<< (pass_area_predict - pass_area)/pass_area << endl;
*/

/*
  // ----------------------------------------
  // part-IV: plot
  cout<<endl<<" Part-IV: plot "<<endl<<endl;


  // Pass and fail Soft Drop mass
  YTitle= "Number of Events / GeV";
  Set_h1_Style( h_passDoubleBTagger_Jmass_wideBinning_diff , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );
  Set_h1_Style( h_failDoubleBTagger_Jmass_wideBinning_diff , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );

  h_failDoubleBTagger_Jmass_wideBinning_diff-> SetTitle("failDoubleBTagger Jmass wideBinning differential");

  // fail ZH mass 
  h_ZH_mass_fail ->SetTitle("");
  h_ZH_mass_fail ->SetStats(0);

  h_ZH_mass_fail ->GetXaxis ()->SetTitle("ZH invariant mass [GeV]");
  h_ZH_mass_fail ->GetYaxis ()->SetTitle("Events");

  h_ZH_mass_fail ->GetYaxis()->SetTitleSize(0.04);
  h_ZH_mass_fail ->GetYaxis()->SetTitleOffset(0.9);

  h_ZH_mass_fail ->SetLineColor(4); // blue
  h_ZH_mass_pass ->SetLineColor(3); // green
  h_ZH_mass_pass_predict->SetLineColor(2); //red

*/

/*
  // predicted/pass ratio 
  TString ratio_name = "h_Ratio";
  TH1F* h_ratio  = (TH1F*) h_ZH_mass_pass_predict ->Clone( ratio_name );
  h_ratio  ->Sumw2();
  h_ratio  ->Divide( h_ZH_mass_pass );

  h_ratio ->SetStats(0);
  h_ratio ->SetTitle("");
  h_ratio ->GetYaxis()->SetRangeUser(-1, 3);
  h_ratio ->GetYaxis()->SetNdivisions(505);
  h_ratio ->GetXaxis()->SetLabelSize(0.10);
  h_ratio ->GetYaxis()->SetLabelSize(0.10);
  h_ratio ->GetXaxis()->SetTitle("ZH invariant mass");
  h_ratio ->GetYaxis()->SetTitle("Predict / Pass");
  h_ratio ->GetYaxis()->SetTitleOffset(0.33);
  h_ratio ->GetXaxis()->SetTitleSize(0.11);
  h_ratio ->GetYaxis()->SetTitleSize(0.11);
*/

/*
  // draw  

  TCanvas* c1 = new TCanvas("c1","c1",10,10,800,600);
  c1->cd(); h_passDoubleBTagger_Jmass_wideBinning_diff -> Draw();


  TCanvas* c2 = new TCanvas("c2","c2",10,10,800,600);
  c2->cd(); h_failDoubleBTagger_Jmass_wideBinning_diff -> Draw();


  TCanvas* c4 = new TCanvas("c4","c4",10,10,800,600);

//  TPad* pad1   = new TPad("pad1","pad1",0.0, 0.3, 1.0, 1.0);
//  TPad* pad2   = new TPad("pad2","pad2",0.0, 0.0, 1.0, 0.3);

  c4->cd();

//  pad1->SetBottomMargin(0.01);
//  pad1->Draw();
//  pad1->cd();

  TLegend* leg = new TLegend(0.5, 0.6, 0.9, 0.9);

  h_ZH_mass_fail -> Draw();  
//  h_ZH_mass_pass -> Draw("same");
  h_ZH_mass_pass_predict -> Draw("same");

  leg->AddEntry(h_ZH_mass_fail,"h_ZH_mass_fail","l");
//  leg->AddEntry(h_ZH_mass_pass,"h_ZH_mass_pass","l");
  leg->AddEntry(h_ZH_mass_pass_predict,"h_ZH_mass_pass_predict","l");

  leg->Draw();

*/

/*
  c4->cd();

    pad2  ->SetTopMargin(0.9);
    pad2  ->SetBottomMargin(0.3);
    pad2  ->Draw();
    pad2  ->cd();

    h_ratio->Draw("E0PX0");
    TLine* OLine = new TLine( 0.0, 1. , 2000 , 1.);
    OLine ->SetLineColor(801);
    OLine ->SetLineWidth(2);
    OLine ->Draw();
*/
 
  // Save plot

/*

  TString save_path ="plot/validate_data1.pdf";
  c1->Print( save_path );

  save_path ="plot/validate_data2.pdf";
  c2->Print( save_path      );

  save_path ="plot/validate_data3.pdf";
  c3->Print( save_path      );

  save_path ="plot/validate_data4.pdf";
  c4->Print( save_path );

  save_path ="plot/validate_data.pdf";
  c1->Print( save_path +"(");
  c2->Print( save_path );
  c3->Print( save_path );
  c4->Print( save_path +")");

  // Save TH1F in ROOT file

  save_path = "output_alphabet/ZHmass_predicted_background.root";
  TFile* outFile = new TFile( save_path , "recreate");

  h_ZH_mass_pass_predict->Write();

  outFile->Write();
  delete outFile;

  return;
*/

}


