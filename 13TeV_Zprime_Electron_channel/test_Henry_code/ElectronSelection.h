
Float_t geteIDEA(Int_t i, Float_t SCEta) {

  Float_t EffectiveArea = 0;

  if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.013 + 0.122;
  if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.021 + 0.147 ;
  if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.013 + 0.055;
  if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.010 + 0.106;
  if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.024 + 0.138;
  if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 ) EffectiveArea = 0.020 + 0.221;
  if (fabs(SCEta) >= 2.4 ) EffectiveArea = 0.019 + 0.211;

  return EffectiveArea;
}

// HEEP v5.1 ID
void select_electrons(TreeReader &data, vector<int> *accepted) {

  accepted->clear();

  // load relevant branches from TTree/TChain
  Int_t    nEle             = data.GetInt("nEle");
  TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
  Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
  Float_t* eleSCEn         = data.GetPtrFloat("eleScEn");

  vector<bool> & eleEcalDrivenSeed = *((vector<bool>*) data.GetPtr("eleEcalDrivenSeed"));
  Float_t* eleEtaseedAtVtx  = data.GetPtrFloat("eleEtaseedAtVtx");
  Float_t* eledPhiAtVtx     = data.GetPtrFloat("eledPhiAtVtx");

  Float_t* eleHoverE        = data.GetPtrFloat("eleHoverE");

  Float_t* eleE1x5Full5x5   = data.GetPtrFloat("eleE1x5Full5x5");
  Float_t* eleE2x5Full5x5   = data.GetPtrFloat("eleE2x5Full5x5");
  Float_t* eleE5x5Full5x5   = data.GetPtrFloat("eleE5x5Full5x5");

  Float_t* eleDr03EcalRecHitSumEt = data.GetPtrFloat("eleDr03EcalRecHitSumEt");
  Float_t* eleDr03HcalDepth1TowerSumEt = data.GetPtrFloat("eleDr03HcalDepth1TowerSumEt");
  Float_t* eleDr03TkSumPt= data.GetPtrFloat("eleDr03TkSumPt");

  Float_t* eleSigmaIEtaIEta = data.GetPtrFloat("eleSigmaIEtaIEta");
  Int_t*   eleMissHits      = data.GetPtrInt("eleMissHits");
  Float_t* eleD0            = data.GetPtrFloat("eleD0");
  Float_t  rho              = data.GetFloat("eleRho");
  Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");


  // loop over lepton candidates
  for (int i = 0; i < nEle; ++i) {

    Float_t  scEta=eleSCEta[i];

    if(! (fabs(scEta) < 1.4442) &&
       ! (fabs(scEta) < 2.5   &&
	  fabs(scEta) > 1.566)
       )continue;


    if(! (fabs(scEta)<1.4442 || fabs(scEta)>1.566))continue;
    
    TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(i);
    Float_t Et = thisEle->Et();
    Float_t E = eleSCEn[i];

    if(fabs(thisEle->Eta())>2.5)continue;
    
//    if(thisEle->Pt()<115)continue;

//    if(Et < 35)continue;

    if(!eleEcalDrivenSeed[i])continue;

//    if(eleMiniIso[i]>0.1)continue; // I cut the Mini-Iso still in other place 
    
//    Float_t caliso = eleDr03EcalRecHitSumEt[i]+ 
//      eleDr03HcalDepth1TowerSumEt[i];

    
    if (fabs(scEta) < 1.4442) {
      if (fabs(eleEtaseedAtVtx[i])>0.004)continue;
      if (fabs(eledPhiAtVtx[i])>0.06)continue;
      if (eleHoverE[i] > (1/E + 0.05))continue;

      if( eleE2x5Full5x5[i]/eleE5x5Full5x5[i] < 0.94 && eleE1x5Full5x5[i]/eleE5x5Full5x5[i] < 0.83)continue;
      

      if (eleMissHits[i] > 1) continue;
      if (fabs(eleD0[i])>0.02)continue;
    }
   else {
      if (fabs(eleEtaseedAtVtx[i])>0.006)continue;
      if (fabs(eledPhiAtVtx[i])>0.06)continue;
      if (eleHoverE[i] > (5/E + 0.05))continue;

      if (eleSigmaIEtaIEta[i] > 0.03) continue;
      
      if (eleMissHits[i] > 1) continue;
      if (fabs(eleD0[i])>0.05)continue;


   }
    accepted->push_back(i);
  }

}



