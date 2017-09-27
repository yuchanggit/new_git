#include <vector>
#include <string>
#include <iostream>

#include <TH1D.h>
#include <TFile.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TMath.h"

double errorfunc(double*v, double* p) {
  double x= v[0];
  return 1/(1+exp(-p[0]*(x-p[1])));
}

double errorfuncThreePar(double*v, double* p) {
  double x= v[0];
  return p[2]/(1+exp(-p[0]*(x-p[1])));
}


void fit_Eff(){

  // open the efficiency histogram

  std::string sample_path = "output_ROOT/SingleMuon_Run2016H_NCUGlobalTuples_1.root";
  TFile* file   = TFile::Open( sample_path.c_str() );

  TH1F* h_eff = (TH1F*) file->FindObjectAny("h_MuTriggerEff");

  // fit with Error function

  // initial par
  double p0 =  0.1; // steep or slow to grow up
  double p1 = 50  ; // the turning point position in x axis
  double p2 =  1  ; // change the height of plateau

//  TF1* f_fittrigg1 = new TF1("f_fittrigg1",errorfunc,0,100,2);
  TF1* f_fittrigg1 = new TF1("f_fittrigg1",errorfuncThreePar,0,100,3);

  f_fittrigg1 ->SetParameter(0, p0 );
  f_fittrigg1 ->SetParameter(1, p1 );
  f_fittrigg1 ->SetParameter(2, p2 );

  h_eff ->Fit(f_fittrigg1);


//  TF1* f_function = new TF1("f_function",errorfunc,0,100,2);
  TF1* f_function = new TF1("f_function",errorfuncThreePar,0,100,3);

  // par after fit
  cout<<"p0: "<< f_fittrigg1->GetParameter(0)<<" p1: "<< f_fittrigg1->GetParameter(1)<<" p2: "<< f_fittrigg1->GetParameter(2) << endl;
  f_function ->SetParameters( f_fittrigg1->GetParameters() ) ;


  // draw

  h_eff->GetYaxis ()->SetRangeUser(-0.1 ,1.2 );

  TCanvas* c1 = new TCanvas("c1","c1",10,10,800,600); c1->cd(); 
  h_eff -> Draw();

  f_function ->GetYaxis ()->SetRangeUser(-0.1 ,1.2 );

  TCanvas* c2 = new TCanvas("c2","c2",10,10,800,600); c2->cd(); 
  f_function -> Draw();

}
