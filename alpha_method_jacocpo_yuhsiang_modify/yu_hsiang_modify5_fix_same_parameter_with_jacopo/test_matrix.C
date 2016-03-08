#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <string>
#include "TCanvas.h"

#include <TMath.h>
#include <TMatrixD.h>


using namespace std;

void test_matrix(){

cout<<"hello" << endl;

TMatrixD posColM(5,1);

posColM(0,0) = 1;
posColM(1,0) = 0;
posColM(2,0) = -1;
posColM(3,0) = -2;
posColM(4,0) = -3;

cout<<"posColM(0,0): "<< posColM(0,0) << endl;
cout<<"posColM(1,0): "<< posColM(1,0) << endl;
cout<<"posColM(2,0): "<< posColM(2,0) << endl;
cout<<"posColM(3,0): "<< posColM(3,0) << endl;
cout<<"posColM(4,0): "<< posColM(4,0) << endl;

posColM.Print();


}














