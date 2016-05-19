//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 18 14:01:33 2016 by ROOT version 5.34/36
// from TTree H4treeReco/H4treeReco
// found on file: recoTrees/RECO_3770.root
//////////////////////////////////////////////////////////

#ifndef read_TestBeamData_h
#define read_TestBeamData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class read_TestBeamData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          runNumber;
   UInt_t          spillNumber;
   UInt_t          evtNumber;
   UInt_t          evtTimeDist;
   UInt_t          evtTimeStart;
   UInt_t          nEvtTimes;
   UInt_t          nwc;
   Float_t         wc_recox[2];   //[nwc]
   Float_t         wc_recoy[2];   //[nwc]
   UInt_t          wc_xl_hits[2];   //[nwc]
   UInt_t          wc_xr_hits[2];   //[nwc]
   UInt_t          wc_yu_hits[2];   //[nwc]
   UInt_t          wc_yd_hits[2];   //[nwc]
   UInt_t          maxch;
   Float_t         group[8];   //[maxch]
   Float_t         ch[8];   //[maxch]
   Float_t         pedestal[8];   //[maxch]
   Float_t         pedestalRMS[8];   //[maxch]
   Float_t         pedestalSlope[8];   //[maxch]
   Float_t         wave_max[8];   //[maxch]
   Float_t         wave_max_aft[8];   //[maxch]
   Float_t         wave_aroundmax[8][50];   //[maxch]
   Float_t         time_aroundmax[8][50];   //[maxch]
   Float_t         wave_fit_smallw_ampl[8];   //[maxch]
   Float_t         wave_fit_smallw_amplerr[8];   //[maxch]
   Float_t         wave_fit_smallw_chi2[8];   //[maxch]
   Float_t         wave_fit_smallw_ndof[8];   //[maxch]
   Float_t         wave_fit_largew_ampl[8];   //[maxch]
   Float_t         wave_fit_largew_amplerr[8];   //[maxch]
   Float_t         wave_fit_largew_chi2[8];   //[maxch]
   Float_t         wave_fit_largew_ndof[8];   //[maxch]
   Float_t         charge_integ[8];   //[maxch]
   Float_t         charge_integ_max[8];   //[maxch]
   Float_t         charge_integ_fix[8];   //[maxch]
   Float_t         charge_integ_smallw[8];   //[maxch]
   Float_t         charge_integ_largew[8];   //[maxch]
   Float_t         charge_integ_smallw_mcp[8];   //[maxch]
   Float_t         charge_integ_largew_mcp[8];   //[maxch]
   Float_t         charge_integ_smallw_noise[8];   //[maxch]
   Float_t         charge_integ_largew_noise[8];   //[maxch]
   Float_t         charge_integ_smallw_rnd[8];   //[maxch]
   Float_t         charge_integ_largew_rnd[8];   //[maxch]
   Float_t         t_max[8];   //[maxch]
   Float_t         t_max_frac30[8];   //[maxch]
   Float_t         t_max_frac50[8];   //[maxch]
   Float_t         t_at_threshold[8];   //[maxch]
   Float_t         t_over_threshold[8];   //[maxch]

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_spillNumber;   //!
   TBranch        *b_evtNumber;   //!
   TBranch        *b_evtTimeDist;   //!
   TBranch        *b_evtTimeStart;   //!
   TBranch        *b_nEvtTimes;   //!
   TBranch        *b_nwc;   //!
   TBranch        *b_wc_recox;   //!
   TBranch        *b_wc_recoy;   //!
   TBranch        *b_wc_xl_hits;   //!
   TBranch        *b_wc_xr_hits;   //!
   TBranch        *b_wc_yu_hits;   //!
   TBranch        *b_wc_yd_hits;   //!
   TBranch        *b_maxch;   //!
   TBranch        *b_group;   //!
   TBranch        *b_ch;   //!
   TBranch        *b_pedestal;   //!
   TBranch        *b_pedestalRMS;   //!
   TBranch        *b_pedestalSlope;   //!
   TBranch        *b_wave_max;   //!
   TBranch        *b_wave_max_aft;   //!
   TBranch        *b_wave_aroundmax;   //!
   TBranch        *b_time_aroundmax;   //!
   TBranch        *b_wave_fit_smallw_ampl;   //!
   TBranch        *b_wave_fit_smallw_amplerr;   //!
   TBranch        *b_wave_fit_smallw_chi2;   //!
   TBranch        *b_wave_fit_smallw_ndof;   //!
   TBranch        *b_wave_fit_largew_ampl;   //!
   TBranch        *b_wave_fit_largew_amplerr;   //!
   TBranch        *b_wave_fit_largew_chi2;   //!
   TBranch        *b_wave_fit_largew_ndof;   //!
   TBranch        *b_charge_integ;   //!
   TBranch        *b_charge_integ_max;   //!
   TBranch        *b_charge_integ_fix;   //!
   TBranch        *b_charge_integ_smallw;   //!
   TBranch        *b_charge_integ_largew;   //!
   TBranch        *b_charge_integ_smallw_mcp;   //!
   TBranch        *b_charge_integ_largew_mcp;   //!
   TBranch        *b_charge_integ_smallw_noise;   //!
   TBranch        *b_charge_integ_largew_noise;   //!
   TBranch        *b_charge_integ_smallw_rnd;   //!
   TBranch        *b_charge_integ_largew_rnd;   //!
   TBranch        *b_t_max;   //!
   TBranch        *b_t_max_frac30;   //!
   TBranch        *b_t_max_frac50;   //!
   TBranch        *b_t_at_threshold;   //!
   TBranch        *b_t_over_threshold;   //!

   read_TestBeamData(TTree *tree=0);
   virtual ~read_TestBeamData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef read_TestBeamData_cxx
read_TestBeamData::read_TestBeamData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("recoTrees/RECO_3770.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("recoTrees/RECO_3770.root");
      }
      f->GetObject("H4treeReco",tree);

   }
   Init(tree);
}

read_TestBeamData::~read_TestBeamData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t read_TestBeamData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t read_TestBeamData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void read_TestBeamData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("spillNumber", &spillNumber, &b_spillNumber);
   fChain->SetBranchAddress("evtNumber", &evtNumber, &b_evtNumber);
   fChain->SetBranchAddress("evtTimeDist", &evtTimeDist, &b_evtTimeDist);
   fChain->SetBranchAddress("evtTimeStart", &evtTimeStart, &b_evtTimeStart);
   fChain->SetBranchAddress("nEvtTimes", &nEvtTimes, &b_nEvtTimes);
   fChain->SetBranchAddress("nwc", &nwc, &b_nwc);
   fChain->SetBranchAddress("wc_recox", wc_recox, &b_wc_recox);
   fChain->SetBranchAddress("wc_recoy", wc_recoy, &b_wc_recoy);
   fChain->SetBranchAddress("wc_xl_hits", wc_xl_hits, &b_wc_xl_hits);
   fChain->SetBranchAddress("wc_xr_hits", wc_xr_hits, &b_wc_xr_hits);
   fChain->SetBranchAddress("wc_yu_hits", wc_yu_hits, &b_wc_yu_hits);
   fChain->SetBranchAddress("wc_yd_hits", wc_yd_hits, &b_wc_yd_hits);
   fChain->SetBranchAddress("maxch", &maxch, &b_maxch);
   fChain->SetBranchAddress("group", group, &b_group);
   fChain->SetBranchAddress("ch", ch, &b_ch);
   fChain->SetBranchAddress("pedestal", pedestal, &b_pedestal);
   fChain->SetBranchAddress("pedestalRMS", pedestalRMS, &b_pedestalRMS);
   fChain->SetBranchAddress("pedestalSlope", pedestalSlope, &b_pedestalSlope);
   fChain->SetBranchAddress("wave_max", wave_max, &b_wave_max);
   fChain->SetBranchAddress("wave_max_aft", wave_max_aft, &b_wave_max_aft);
   fChain->SetBranchAddress("wave_aroundmax", wave_aroundmax, &b_wave_aroundmax);
   fChain->SetBranchAddress("time_aroundmax", time_aroundmax, &b_time_aroundmax);
   fChain->SetBranchAddress("wave_fit_smallw_ampl", wave_fit_smallw_ampl, &b_wave_fit_smallw_ampl);
   fChain->SetBranchAddress("wave_fit_smallw_amplerr", wave_fit_smallw_amplerr, &b_wave_fit_smallw_amplerr);
   fChain->SetBranchAddress("wave_fit_smallw_chi2", wave_fit_smallw_chi2, &b_wave_fit_smallw_chi2);
   fChain->SetBranchAddress("wave_fit_smallw_ndof", wave_fit_smallw_ndof, &b_wave_fit_smallw_ndof);
   fChain->SetBranchAddress("wave_fit_largew_ampl", wave_fit_largew_ampl, &b_wave_fit_largew_ampl);
   fChain->SetBranchAddress("wave_fit_largew_amplerr", wave_fit_largew_amplerr, &b_wave_fit_largew_amplerr);
   fChain->SetBranchAddress("wave_fit_largew_chi2", wave_fit_largew_chi2, &b_wave_fit_largew_chi2);
   fChain->SetBranchAddress("wave_fit_largew_ndof", wave_fit_largew_ndof, &b_wave_fit_largew_ndof);
   fChain->SetBranchAddress("charge_integ", charge_integ, &b_charge_integ);
   fChain->SetBranchAddress("charge_integ_max", charge_integ_max, &b_charge_integ_max);
   fChain->SetBranchAddress("charge_integ_fix", charge_integ_fix, &b_charge_integ_fix);
   fChain->SetBranchAddress("charge_integ_smallw", charge_integ_smallw, &b_charge_integ_smallw);
   fChain->SetBranchAddress("charge_integ_largew", charge_integ_largew, &b_charge_integ_largew);
   fChain->SetBranchAddress("charge_integ_smallw_mcp", charge_integ_smallw_mcp, &b_charge_integ_smallw_mcp);
   fChain->SetBranchAddress("charge_integ_largew_mcp", charge_integ_largew_mcp, &b_charge_integ_largew_mcp);
   fChain->SetBranchAddress("charge_integ_smallw_noise", charge_integ_smallw_noise, &b_charge_integ_smallw_noise);
   fChain->SetBranchAddress("charge_integ_largew_noise", charge_integ_largew_noise, &b_charge_integ_largew_noise);
   fChain->SetBranchAddress("charge_integ_smallw_rnd", charge_integ_smallw_rnd, &b_charge_integ_smallw_rnd);
   fChain->SetBranchAddress("charge_integ_largew_rnd", charge_integ_largew_rnd, &b_charge_integ_largew_rnd);
   fChain->SetBranchAddress("t_max", t_max, &b_t_max);
   fChain->SetBranchAddress("t_max_frac30", t_max_frac30, &b_t_max_frac30);
   fChain->SetBranchAddress("t_max_frac50", t_max_frac50, &b_t_max_frac50);
   fChain->SetBranchAddress("t_at_threshold", t_at_threshold, &b_t_at_threshold);
   fChain->SetBranchAddress("t_over_threshold", t_over_threshold, &b_t_over_threshold);
   Notify();
}

Bool_t read_TestBeamData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void read_TestBeamData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t read_TestBeamData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef read_TestBeamData_cxx
