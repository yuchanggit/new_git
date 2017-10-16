
These are the baseline cuts that are applied later in the code.

    // Declare varibles in trees
    DeclareProperty( "IsData",                    m_isData                   = false );
    DeclareProperty( "IsSignal",                  m_isSignal                 = false );

    DeclareProperty( "ElectronName",              m_electronName             = "el" );
    DeclareProperty( "MuonName",                  m_muonName                 = "mu" );
    DeclareProperty( "TauName",                   m_tauName                  = "tau" );
    DeclareProperty( "JetAK4Name",                m_jetAK4Name               = "jetAK4" );
    DeclareProperty( "JetAK8Name",                m_jetAK8Name               = "jetAK8" );
    DeclareProperty( "GenJetAK8Name",             m_genjetAK8Name            = "genjetAK8" );
    DeclareProperty( "MissingEtName",             m_missingEtName            = "MET" );
    DeclareProperty( "GenParticleName",           m_genParticleName          = "genParticle" );
    
    
    DeclareProperty( "Elec1PtCut",                m_Elec1PtCut               =  55. );
    DeclareProperty( "Elec2PtCut",                m_Elec2PtCut               =  20. );
    DeclareProperty( "ElecPtCut",                 m_ElecPtCut                =  10. );
    DeclareProperty( "ElecEtaCut",                m_ElecEtaCut               =  2.5 );
    DeclareProperty( "Muon1PtCut",                m_Muon1PtCut               =  55. );
    DeclareProperty( "Muon2PtCut",                m_Muon2PtCut               =  20. );
    DeclareProperty( "MuonPtCut",                 m_MuonPtCut                =  10. );
    DeclareProperty( "MuonEtaCut",                m_MuonEtaCut               =  2.4 );
    DeclareProperty( "TauPtCut",                  m_TauPtCut                 =  18. );
    DeclareProperty( "TauEtaCut",                 m_TauEtaCut                =  2.3 );
    DeclareProperty( "AK4PtCut",                  m_AK4PtCut                 =  30. );
    DeclareProperty( "AK4EtaCut",                 m_AK4EtaCut                =  2.4 );
    DeclareProperty( "AK8PtCut",                  m_AK8PtCut                 = 200. );
    DeclareProperty( "AK8EtaCut",                 m_AK8EtaCut                =  2.4 );
    DeclareProperty( "MEtPtCut",                  m_MEtPtCut                 = 250. );
    DeclareProperty( "VPtCut",                    m_VPtCut                   = 200. );
    DeclareProperty( "Tau21LowerCut",             m_Tau21LowerCut            = 0.35 );
    DeclareProperty( "Tau21UpperCut",             m_Tau21UpperCut            = 0.75 );
    DeclareProperty( "JMassLowerCut",             m_JMassLowerCut            =  30. );
    DeclareProperty( "JMassUpperCut",             m_JMassUpperCut            = 250. );
    DeclareProperty( "VMassLowerCut",             m_VMassLowerCut            =  65. );
    DeclareProperty( "VMassInterCut",             m_VMassInterCut            =  85. );
    DeclareProperty( "VMassUpperCut",             m_VMassUpperCut            = 105. );
    DeclareProperty( "HMassLowerCut",             m_HMassLowerCut            = 105. );
    DeclareProperty( "HMassUpperCut",             m_HMassUpperCut            = 135. );
    DeclareProperty( "XMassLowerCut",             m_XMassLowerCut            = 750. );
    DeclareProperty( "XTMassLowerCut",            m_XTMassLowerCut           = 650. );
    DeclareProperty( "XJJMassLowerCut",           m_XJJMassLowerCut          = 950. );


These are the trigger lists.


    m_triggerNames["SingleMu"].push_back("HLT_Mu50_v");
    m_triggerNames["SingleMu"].push_back("HLT_TkMu50_v");
    m_triggerNames["SingleIsoMu"].push_back("HLT_IsoMu27_v");
    m_triggerNames["SingleIsoMu"].push_back("HLT_IsoTkMu27_v");
    m_triggerNames["DoubleMu"].push_back("HLT_Mu27_TkMu8_v");
    m_triggerNames["DoubleIsoMu"].push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    m_triggerNames["DoubleIsoMu"].push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    m_triggerNames["SingleEle"].push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT_v");
    m_triggerNames["SingleEle"].push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
    m_triggerNames["SingleIsoEle"].push_back("HLT_Ele32_WPTight_Gsf_v");
    m_triggerNames["SingleIsoEle"].push_back("HLT_Ele32_eta2p1_WPTight_Gsf_v");
    m_triggerNames["SingleIsoEle"].push_back("HLT_Ele27_WPLoose_Gsf_v");
    m_triggerNames["SingleIsoEle"].push_back("HLT_Ele27_WPTight_Gsf_v");
    m_triggerNames["DoubleIsoEle"].push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    m_triggerNames["DoubleEle"].push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v");
    m_triggerNames["METMHTNoMu"].push_back("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v");
    m_triggerNames["METMHTNoMu"].push_back("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v");
    m_triggerNames["METMHTNoMu"].push_back("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v");
    m_triggerNames["METMHTNoMu"].push_back("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v");
    m_triggerNames["METMHTNoMu"].push_back("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
    m_triggerNames["METMHTNoMu"].push_back("HLT_MonoCentralPFJet80_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
    m_triggerNames["METMHT"].push_back("HLT_PFMET110_PFMHT110_IDTight_v");
    m_triggerNames["METMHT"].push_back("HLT_PFMET120_PFMHT120_IDTight_v");
    //m_triggerNames["MET"].push_back("HLT_PFMET120_BTagCSV_p067_v");
    m_triggerNames["MET"].push_back("HLT_PFMET170_NoiseCleaned_v");
    m_triggerNames["MET"].push_back("HLT_PFMET170_HBHECleaned_v");
    m_triggerNames["MET"].push_back("HLT_PFMET170_HBHE_BeamHaloCleaned_v");
    m_triggerNames["JET"].push_back("HLT_PFJet450_v");
    m_triggerNames["JET"].push_back("HLT_AK8PFJet450_v");
    m_triggerNames["HT"].push_back("HLT_PFHT900_v");
    m_triggerNames["HT"].push_back("HLT_PFHT800_v");
    m_triggerNames["HTWJ"].push_back("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v");
    m_triggerNames["HTWJ"].push_back("HLT_PFHT650_WideJetMJJ900_v");
    //m_triggerNames["HT_PS"].push_back("HLT_PFHT400_v");
    //m_triggerNames["HT_PS"].push_back("HLT_PFHT600_v");
    m_triggerNames["HT_PS"].push_back("HLT_PFHT650_v");
    m_triggerNames["HT_PS"].push_back("HLT_PFJet320_v");
    m_triggerNames["SUBJET"].push_back("HLT_AK8PFJet360_TrimMass30_v");
    m_triggerNames["SUBHT"].push_back("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v");
    //m_triggerNames["SUB"].push_back("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_v");
    m_triggerNames["SUBTAG"].push_back("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_v");
    m_triggerNames["SUBTAG"].push_back("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v");
    m_triggerNames["SUB_PS"].push_back("HLT_PFJet320_v");
    


This is the definitions of the historams

    
    // Cutflow
    std::vector<std::string> labelsZtoNN = {"All", "Trigger", "MET > 250", "Lepton veto", "Tau veto", "AK8 jet", "Cleaning", "X mass", "T veto", "H mass", "1 b-tag", "2 b-tag"};
    std::vector<std::string> labelsWtoEN = {"All", "Trigger", "Ele in acc.", "Ele p_{T}", "Ele Id+Iso", "W boost", "AK8 jet", "Cleaning", "X mass", "T veto", "H mass", "1 b-tag", "2 b-tag"};
    std::vector<std::string> labelsWtoMN = {"All", "Trigger", "Muon in acc.", "Muon p_{T}", "Muon Id", "Muon Iso", "W boost", "AK8 jet", "Cleaning", "X mass", "T veto", "H mass", "1 b-tag", "2 b-tag"};
    std::vector<std::string> labelsZtoEE = {"All", "Trigger", "Ele in acc.", "Z(ee) candidate", "Ele p_{T}", "Ele Id+Iso", "Z boost", "AK8 jet", "Cleaning", "X mass", "H mass", "1 b-tag", "2 b-tag"};
    std::vector<std::string> labelsZtoMM = {"All", "Trigger", "Muon in acc.", "Z(#mu#mu) candidate", "Muon p_{T}", "Muon Id", "Muon Iso", "Z boost", "AK8 jet", "Cleaning", "X mass", "H mass", "1 b-tag", "2 b-tag"};
    std::vector<std::string> labelsVtoQQ = {"All", "Trigger", "2 AK8 jets", "Jet Id", "Jet #Delta#eta", "MET veto", "Lepton veto", "X mass", "H mass", "V mass", "W, HP, 1b", "W, LP, 1b", "W, HP, 2b", "W, LP, 2b", "Z, HP, 1b", "Z, LP, 1b", "Z, HP, 2b", "Z, LP, 2b"};
    
    Book( TH1F( "Events", ";;Events;log", labelsZtoNN.size(), 0, labelsZtoNN.size()), "nnqq" );
    Book( TH1F( "Events", ";;Events;log", labelsWtoEN.size(), 0, labelsWtoEN.size()), "enqq" );
    Book( TH1F( "Events", ";;Events;log", labelsWtoMN.size(), 0, labelsWtoMN.size()), "mnqq" );
    Book( TH1F( "Events", ";;Events;log", labelsZtoEE.size(), 0, labelsZtoEE.size()), "eeqq" );
    Book( TH1F( "Events", ";;Events;log", labelsZtoMM.size(), 0, labelsZtoMM.size()), "mmqq" );
    Book( TH1F( "Events", ";;Events;log", labelsVtoQQ.size(), 0, labelsVtoQQ.size()), "qqqq" );
    
    for(unsigned int i = 0; i < labelsZtoNN.size(); i++) Hist("Events", "nnqq")->GetXaxis()->SetBinLabel(i+1, labelsZtoNN[i].c_str());
    for(unsigned int i = 0; i < labelsWtoEN.size(); i++) Hist("Events", "enqq")->GetXaxis()->SetBinLabel(i+1, labelsWtoEN[i].c_str());
    for(unsigned int i = 0; i < labelsWtoMN.size(); i++) Hist("Events", "mnqq")->GetXaxis()->SetBinLabel(i+1, labelsWtoMN[i].c_str());
    for(unsigned int i = 0; i < labelsZtoEE.size(); i++) Hist("Events", "eeqq")->GetXaxis()->SetBinLabel(i+1, labelsZtoEE[i].c_str());
    for(unsigned int i = 0; i < labelsZtoMM.size(); i++) Hist("Events", "mmqq")->GetXaxis()->SetBinLabel(i+1, labelsZtoMM[i].c_str());
    for(unsigned int i = 0; i < labelsVtoQQ.size(); i++) Hist("Events", "qqqq")->GetXaxis()->SetBinLabel(i+1, labelsVtoQQ[i].c_str());
    
    

Now the loop for every event starts.

First, i fill vectors of object with very basic selections (i am applying tighter cuts later).



    // --- Preliminary operations ---
    isMC = !m_isData;
    EventNumber = m_eventInfo.eventNumber;
    LumiNumber = m_eventInfo.lumiBlock;
    RunNumber = m_eventInfo.runNumber;
    nPV = m_eventInfo.PV_N;
    
    // Gen Weight
    if(isMC) {
        GenWeight = (m_eventInfo.genWeight < 0) ? -1 : 1;
        //PUWeight = getPUWeight();
        for(unsigned int v = 0; v < (m_eventInfo.actualIntPerXing)->size(); ++v) {
            if ( (*m_eventInfo.bunchCrossing)[v] == 0 ) {
                int npu( (*m_eventInfo.actualIntPerXing)[v] );
                PUWeight = m_pileupReweightingTool.getPileUpweight( npu );
                PUWeightUp = m_pileupReweightingTool.getPileUpweight( npu, +1 );
                PUWeightDown = m_pileupReweightingTool.getPileUpweight( npu, -1 );
                m_logger << VERBOSE << "Weight: " << PUWeight << " for true: " << (*m_eventInfo.actualIntPerXing)[v] << SLogger::endmsg;
                break;
            }
        }
        EventWeight *= GenWeight;
        EventWeight *= PUWeight;
    }
    // Check JSON
    else {
        if(!isGoodEvent(m_eventInfo.runNumber, m_eventInfo.lumiBlock)) {m_logger << INFO << " - Event not in JSON"  << SLogger::endmsg; throw SError( SError::SkipEvent ); }
    }
    if(!passMETFilters(!isMC)) {m_logger << INFO << " - Event fails MET filters"  << SLogger::endmsg; throw SError( SError::SkipEvent ); }
    
    std::map<std::string, bool> triggerMap;
//    if(!isMC) 
    triggerMap = getTriggerMap();
    
    // --- Electrons ---
    m_logger << INFO << " + Opening Electron collection" << SLogger::endmsg;
    std::vector<UZH::Electron> ElecVect, ElecIsoVect;
    std::vector<TLorentzVector> CalibratedElecVect;
    for(int i = 0; i < m_electron.N; ++i) {
        UZH::Electron el(&m_electron, i);
        if(el.pt() < m_ElecPtCut || fabs(el.eta()) > m_ElecEtaCut) continue;
        if(el.isLooseElectron()) {
            ElecIsoVect.push_back(el);
            ST += el.pt();
        }
        ElecVect.push_back(el);
        TLorentzVector el_tlv;
        el_tlv.SetPtEtaPhiE(el.pt(), el.eta(), el.phi(), el.e());
        CalibratedElecVect.push_back(el_tlv);
    }
    nElectrons = ElecIsoVect.size();
    
    // --- Muons ---
    m_logger << INFO << " + Opening Muon collection" << SLogger::endmsg;
    std::vector<UZH::Muon> MuonVect, MuonIsoVect;
    for(int i = 0; i < m_muon.N; ++i) {
        UZH::Muon mu(&m_muon, i);
        if(mu.pt() < m_MuonPtCut || fabs(mu.eta()) > m_MuonEtaCut) continue;
        if(mu.isLooseMuon()==1 && mu.pfDeltaCorrRelIso()<0.25) {
            MuonIsoVect.push_back(mu);
            ST += mu.pt();
        }
        MuonVect.push_back(mu);
    }
    nMuons = MuonIsoVect.size();
    
    // --- Taus ---
    m_logger << INFO << " + Opening Tau collection" << SLogger::endmsg;
    std::vector<UZH::Tau> TauVect;
    for(int i = 0; i < m_tau.N; ++i) {
        UZH::Tau tau(&m_tau, i);
        if( !(tau.pt() > m_TauPtCut && fabs(tau.eta()) < m_TauEtaCut && tau.byVTightIsolationMVArun2v1PWnewDMwLT()) ) continue; //byVTightIsolationMVArun2v1DBnewDMwLT()
        bool cleanTau(true);
        for(unsigned int e = 0; e < ElecIsoVect.size(); e++) if(ElecIsoVect[e].tlv().DeltaR(tau.tlv()) < 0.4) cleanTau = false;
        for(unsigned int m = 0; m < MuonIsoVect.size(); m++) if(MuonIsoVect[m].tlv().DeltaR(tau.tlv()) < 0.4) cleanTau = false;
        if(!cleanTau) continue;
        nTaus++;
    }
    
    // --- AK8 Jets ---
    m_logger << INFO << " + Opening AK8 collection" << SLogger::endmsg;
    std::vector<UZH::Jet> FatJetsVect;
    std::vector<TLorentzVector> FatJetsVectRes;
    std::vector<TLorentzVector> FatJetsVectScaleUp;
    std::vector<TLorentzVector> FatJetsVectScaleDown;
    std::vector<TLorentzVector> FatJetsVectResUp;
    std::vector<TLorentzVector> FatJetsVectResDown;
    std::vector<TLorentzVector> FatJetsPuppiVect;
    std::vector<int> FatJetsBTagVect;
    std::vector<float> FatJetsTau21Vect;
    std::vector<float> FatJetsMassVect;
    std::vector<float> FatJetsMassGenVect;
    std::vector<float> FatJetsMassVectScaleUp;
    std::vector<float> FatJetsMassVectScaleDown;
    std::vector<float> FatJetsMassVectResUp;
    std::vector<float> FatJetsMassVectResDown;
    
    for(int i = 0; i < m_jetAK8.N; ++i) {
        UZH::Jet jet(&m_jetAK8, i);
        if(jet.pt() < m_AK8PtCut || fabs(jet.eta()) > m_AK8EtaCut || !jet.IDLoose()) continue;
        if(!jet.IDLoose()) continue;
        bool cleanJet(true);
        for(unsigned int e = 0; e < ElecIsoVect.size(); e++) if(ElecIsoVect[e].tlv().DeltaR(jet.tlv()) < 0.8) cleanJet = false;
        for(unsigned int m = 0; m < MuonIsoVect.size(); m++) if(MuonIsoVect[m].tlv().DeltaR(jet.tlv()) < 0.8) cleanJet = false;
        if(!cleanJet) continue;
        //if(jet.subjet_softdrop_N() < 2) continue; // SoftDrop algorithm has failed
        // Count btags
        int nbtag(0);
        for(unsigned int j = 0; j < 2; j++) if(jet.subjet_softdrop_N() > (int)j && m_bTaggingScaleTool.isTagged( jet.subjet_softdrop_csv()[j]) ) nbtag++;
        // Match with PUPPI jet
        float mass(-1.), genmass(-1.), tau21(-1.);
        TLorentzVector jetPuppi_tlv;
        for(unsigned int j = 0; j < (*m_jetAK8Puppi.jetAK8_puppi_pt).size(); ++j) {
            UZH::PuppiJet jetPuppi( &m_jetAK8Puppi, j );
            if(jetPuppi.jetAK8_puppi_pt() <= 0.) continue;
            jetPuppi_tlv.SetPtEtaPhiE(jetPuppi.jetAK8_puppi_pt(), jetPuppi.jetAK8_puppi_eta(), jetPuppi.jetAK8_puppi_phi(), jetPuppi.jetAK8_puppi_e());
            if(jet.tlv().DeltaR(jetPuppi_tlv) < 0.8) {
                mass = jetPuppi.jetAK8_puppi_softdrop_mass();
                tau21 = jetPuppi.jetAK8_puppi_tau1() ? jetPuppi.jetAK8_puppi_tau2() / jetPuppi.jetAK8_puppi_tau1() : -1.;
                break;
            }
        }
        if(mass < 0.) {//continue;
            jetPuppi_tlv = jet.tlv();
            mass = jet.softdrop_mass();
            tau21 = jet.tau1() ? jet.tau2() / jet.tau1() : -1.;
        }
        if(isMC) {
            // gen Jet matching
            for(unsigned int j = 0; j < (*m_genjetAK8.genJetAK8_pt).size(); ++j) {
                UZH::GenJet genjet(&m_genjetAK8, j);
                TLorentzVector gentlv;
                gentlv.SetPtEtaPhiE(genjet.genJetAK8_pt(), genjet.genJetAK8_eta(), genjet.genJetAK8_phi(), genjet.genJetAK8_e());
                if(gentlv.DeltaR(jet.tlv()) < 0.8 && fabs(gentlv.Pt() - jet.pt())/jet.pt() < 0.3 ) genmass = genjet.genJetAK8_softdropmass();
            }
            // is the genjet matching fails, use gen info
            if(m_isSignal && genmass < 0) {
                for(int j = 0; j < m_genParticle.N; ++j) {
                    UZH::GenParticle gen(&m_genParticle, j);
                    if(abs(gen.pdgId()) >= 23 && abs(gen.pdgId()) <= 25 && gen.tlv().DeltaR(jet.tlv()) < 0.8) genmass = gen.m();
                }
            }
        }
        // Correct mass
        float massScaleUp(mass), massScaleDown(mass), massResUp(mass), massResDown(mass);
        if(m_isSignal) {
            massScaleUp = m_CorrectionTool.GetCorrectedMass(massScaleUp, genmass, jetPuppi_tlv.Pt(), jetPuppi_tlv.Eta(), isMC, +1, 0);
            massScaleDown = m_CorrectionTool.GetCorrectedMass(massScaleDown, genmass, jetPuppi_tlv.Pt(), jetPuppi_tlv.Eta(), isMC, -1, 0);
            massResUp = m_CorrectionTool.GetCorrectedMass(massResUp, genmass, jetPuppi_tlv.Pt(), jetPuppi_tlv.Eta(), isMC, 0, +1);
            massResDown = m_CorrectionTool.GetCorrectedMass(massResDown, genmass, jetPuppi_tlv.Pt(), jetPuppi_tlv.Eta(), isMC, 0, -1);
        }
        mass = m_CorrectionTool.GetCorrectedMass(mass, genmass, jetPuppi_tlv.Pt(), jetPuppi_tlv.Eta(), isMC);
        FatJetsVect.push_back(jet);
        FatJetsPuppiVect.push_back(jetPuppi_tlv);
        FatJetsTau21Vect.push_back(tau21);
        FatJetsBTagVect.push_back(nbtag);
        FatJetsMassVect.push_back(mass);
        FatJetsMassGenVect.push_back(genmass);
        FatJetsMassVectScaleUp.push_back(massScaleUp);
        FatJetsMassVectScaleDown.push_back(massScaleDown);
        FatJetsMassVectResUp.push_back(massResUp);
        FatJetsMassVectResDown.push_back(massResDown);
        // JES
        TLorentzVector jetScaleUp(jet.tlv()), jetScaleDown(jet.tlv()), jetResUp(jet.tlv()), jetResDown(jet.tlv()), jetRes(jet.tlv());
        if(m_isSignal) {
            jetScaleUp *= jet.jecUp() / jet.jec();
            jetScaleDown *= jet.jecDown() / jet.jec();
            jetResUp = m_CorrectionTool.GetCorrectedJet(jet.tlv(), float(jet.jer_sigma_pt()), float(jet.jer_sf()), float(jet.jer_sf_up()), float(jet.jer_sf_down()), +1);
            jetResDown = m_CorrectionTool.GetCorrectedJet(jet.tlv(), float(jet.jer_sigma_pt()), float(jet.jer_sf()), float(jet.jer_sf_up()), float(jet.jer_sf_down()), -1);
            jetRes = m_CorrectionTool.GetCorrectedJet(jet.tlv(), float(jet.jer_sigma_pt()), float(jet.jer_sf()), float(jet.jer_sf_up()), float(jet.jer_sf_down()), 0);
        }
        FatJetsVectRes.push_back( jetRes );
        FatJetsVectScaleUp.push_back( jetScaleUp );
        FatJetsVectScaleDown.push_back( jetScaleDown );
        FatJetsVectResUp.push_back( jetResUp );
        FatJetsVectResDown.push_back( jetResDown );
    }
    nFatJets = FatJetsVect.size();
    
    
    // --- AK4 Jets ---
    m_logger << INFO << " + Opening AK4 collection" << SLogger::endmsg;
    std::vector<UZH::Jet> JetsVect, JetsNoFatJetVect, JetsNoFatJetsVect;
    for(int i = 0; i < m_jetAK4.N; ++i) {
        UZH::Jet jet(&m_jetAK4, i);
        if(jet.pt() < m_AK4PtCut || fabs(jet.eta()) > m_AK4EtaCut || !jet.IDLoose()) continue;
        if(!jet.IDLoose()) continue;
        bool cleanJet(true);
        for(unsigned int e = 0; e < ElecIsoVect.size(); e++) if(ElecIsoVect[e].tlv().DeltaR(jet.tlv()) < 0.4) cleanJet = false;
        for(unsigned int m = 0; m < MuonIsoVect.size(); m++) if(MuonIsoVect[m].tlv().DeltaR(jet.tlv()) < 0.4) cleanJet = false;
        if(!cleanJet) continue;
        JetsVect.push_back(jet);
        if(FatJetsVect.size()>0 && FatJetsVect[0].tlv().DeltaR(jet.tlv()) > 1.2) JetsNoFatJetVect.push_back(jet);
        if(FatJetsVect.size()>1 && FatJetsVect[0].tlv().DeltaR(jet.tlv()) > 1.2 && FatJetsVect[1].tlv().DeltaR(jet.tlv()) > 1.2) JetsNoFatJetsVect.push_back(jet);
        ST += jet.pt();
        HT += jet.pt();
        HTx += jet.tlv().Px();
        HTy += jet.tlv().Py();
    }
    nJets = JetsVect.size();
    MHT = sqrt(HTx*HTx + HTy*HTy);
    MHTNoMu = MHT;

    // --- MET ---
    m_logger << INFO << " + Opening MET collection" << SLogger::endmsg;
    UZH::MissingEt MET( &m_missingEt, 0 );
    TLorentzVector MET_tlv;
    MET_tlv.SetPtEtaPhiE(MET.et(), 0., MET.phi(), MET.et());
    //METNoMu = (MuonIsoVect.size() == 1 && MuonIsoVect[0].pt()>30. && fabs(MuonIsoVect[0].eta()) < 2.1 && MuonIsoVect[0].isTightMuon()==1) ? sqrt(pow(MET_tlv.Px() + MuonVect[0].tlv().Px(), 2) + pow(MET_tlv.Py() + MuonVect[0].tlv().Py(), 2)) : MET.et();
    METNoMu = MET.et();
    float METx(MET_tlv.Px()), METy(MET_tlv.Py());
    for(unsigned int i=0; i<MuonIsoVect.size(); i++) {METx += MuonVect[i].tlv().Px(); METy += MuonVect[i].tlv().Py();}
    METNoMu = sqrt(METx*METx + METy*METy);
    MinMETMHT = std::min(float(MET.et()), MHT);
    MinMETNoMuMHTNoMu = std::min(METNoMu, MHTNoMu);
    MaxMETNoMuMHTNoMu = std::max(METNoMu, MHTNoMu);

    
    
    Hist("Events")->Fill(0., GenWeight);
    Hist("Events", "nnqq")->Fill(0., EventWeight);
    Hist("Events", "enqq")->Fill(0., EventWeight);
    Hist("Events", "mnqq")->Fill(0., EventWeight);
    Hist("Events", "eeqq")->Fill(0., EventWeight);
    Hist("Events", "mmqq")->Fill(0., EventWeight);
    Hist("Events", "qqqq")->Fill(0., EventWeight);
    
    // Filter by Trigger
    if(!triggerMap["SingleMu"] && !triggerMap["SingleEle"] && !triggerMap["SingleIsoEle"] && !(MET.et() > m_MEtPtCut)/*!triggerMap["MET"] && !triggerMap["METMHT"] && !triggerMap["METMHTNoMu"]*/ && !triggerMap["HT"] && !triggerMap["HTWJ"] && !triggerMap["SUBJET"] && !triggerMap["SUBHT"] && !triggerMap["SUBTAG"]) {m_logger << INFO << " - No trigger"  << SLogger::endmsg; throw SError( SError::SkipEvent ); }
    
    
    Hist("Events", "nnqq")->Fill(1., EventWeight);
    Hist("Events", "enqq")->Fill(1., EventWeight);
    Hist("Events", "mnqq")->Fill(1., EventWeight);
    Hist("Events", "eeqq")->Fill(1., EventWeight);
    Hist("Events", "mmqq")->Fill(1., EventWeight);
    Hist("Events", "qqqq")->Fill(1., EventWeight);
    
    
    
    // -----------------------------------
    //           VECTOR BOSON
    // -----------------------------------
    m_logger << INFO << " + Vector boson reconstruction" << SLogger::endmsg;
    
    int e1(-1), e2(-1);
    int m1(-1), m2(-1), mHPT(-1), mTHPT(-1);
    TLorentzVector Neutrino;
    // Categorization depending on the number of leptons
    
    // ---------- Z TO LEPTONS ----------
    // Cascade: Zmm -> Zee -> Wmn -> Wen -> Znn -> Zqq
    // --- Z -> mumu ---
    if( MuonVect.size()>=2 || (MuonVect.size()>=2 && ElecVect.size()>=2 && MuonVect.at(0).pt() > ElecVect.at(0).pt()) ) {
        m_logger << INFO << " + Try to reconstruct Z -> mm"  << SLogger::endmsg;
        Hist("Events", "mmqq")->Fill(2., EventWeight);
        // Indentify leptons
        float maxZpt(-1.), Zpt(-1.), Zmass(-1.), dRll(-1.), pTll(-1.);
        for(unsigned int i = 0; i < MuonVect.size(); i++) {
            for(unsigned int j = 1; j < MuonVect.size(); j++) {
                if(i==j || MuonVect[i].charge() == MuonVect[j].charge()) continue;
                Zpt = (MuonVect[i].tlv() + MuonVect[j].tlv()).Pt();
                Zmass = (MuonVect[i].tlv() + MuonVect[j].tlv()).M();
                if(Zmass > 70. && Zmass < 110. && Zpt > maxZpt) {m1 = i; m2 = j; maxZpt = Zpt;}
            }
        }
        // Check suitable muons
        if(m1 < 0 || m2 < 0) {m_logger << INFO << " - No OS muons"  << SLogger::endmsg;}
        else {
            Hist("Events", "mmqq")->Fill(3., EventWeight);
            if( !(MuonVect[m1].pt() > m_Muon1PtCut && MuonVect[m2].pt() > m_Muon2PtCut) ) {m_logger << INFO << " - No muons above threshold" << SLogger::endmsg;}
            else {
                Hist("Events", "mmqq")->Fill(4., EventWeight);
                //fillMuonPlots(MuonVect[m1], MuonVect[m2], LepP, LepM);
                bool isMatched( isMC && LepP.Pt()>0. && LepM.Pt()>0. && (MuonVect[m1].tlv().DeltaR(LepP) < 0.05 || MuonVect[m1].tlv().DeltaR(LepM) < 0.05) && (MuonVect[m2].tlv().DeltaR(LepP) < 0.05 || MuonVect[m2].tlv().DeltaR(LepM) < 0.05));
                if(isMatched) {
                    dRll = LepP.DeltaR(LepM);
                    pTll = (LepP+LepM).Pt();
                    Hist("dR", "Muons")->Fill(dRll); Hist("pT", "Muons")->Fill(pTll); Hist("pT1", "Muons")->Fill(MuonVect[0].pt()); Hist("pT2", "Muons")->Fill(MuonVect[1].pt());
                    if(MuonVect[m1].isHighPtMuon()==1 && MuonVect[m2].isHighPtMuon()==1) {Hist("dR_HighptHighptId", "Muons")->Fill(dRll); Hist("pT_HighptHighptId", "Muons")->Fill(pTll);}
                    if(MuonVect[m1].isLooseMuon()==1 && MuonVect[m2].isLooseMuon()==1) {Hist("dR_LooseLooseId", "Muons")->Fill(dRll); Hist("pT_LooseLooseId", "Muons")->Fill(pTll);}
                    if(MuonVect[m1].isMediumMuon()==1 && MuonVect[m2].isMediumMuon()==1) {Hist("dR_MediumMediumId", "Muons")->Fill(dRll); Hist("pT_MediumMediumId", "Muons")->Fill(pTll);}
                    if(MuonVect[m1].isTightMuon()==1 && MuonVect[m2].isTightMuon()==1) {Hist("dR_TightTightId", "Muons")->Fill(dRll); Hist("pT_TightTightId", "Muons")->Fill(pTll);}
                    if(MuonVect[m1].isHighPtMuon()==1 || MuonVect[m2].isHighPtMuon()==1) Hist("pT1_HighptId", "Muons")->Fill(MuonVect[m1].pt());
                    if(MuonVect[m2].isTrackerHighPtMuon()==1) Hist("pT2_HighptId", "Muons")->Fill(MuonVect[m2].pt());
                }
                // Apply muon Id
                if( !( (MuonVect[m1].isHighPtMuon()==1 && MuonVect[m2].isTrackerHighPtMuon()) || (MuonVect[m2].isHighPtMuon()==1 && MuonVect[m1].isTrackerHighPtMuon()) ) ) {m_logger << INFO << " - No double muon Id" << SLogger::endmsg;}
                else {
                    if(MuonVect[m1].isHighPtMuon()) {mHPT = m1; mTHPT = m2;}
                    else {mHPT = m2; mTHPT = m1;}
                    Hist("Events", "mmqq")->Fill(5., EventWeight);
                    if(isMatched) {Hist("dR_HighptTrackerId", "Muons")->Fill(dRll); Hist("pT_HighptTrackerId", "Muons")->Fill(pTll);}
                    if(isMatched && MuonVect[m1].pfDeltaCorrRelIso() < 0.20 && MuonVect[m2].pfDeltaCorrRelIso() < 0.20) {Hist("dR_HighptTrackerIdPFIso", "Muons")->Fill(dRll); Hist("pT_HighptTrackerIdPFIso", "Muons")->Fill(pTll);}
                    // Correct muon tracker iso UZH::Muon::trackCorrIso()
                    float trackIso1( MuonVect[m1].trackIso() ), trackIso2( MuonVect[m2].trackIso() );
                    if(MuonVect[m1].tlv().DeltaR(MuonVect[m2].tlv()) < 0.3) {
                        trackIso1 -= MuonVect[m2].innerTrack_pt();
                        trackIso2 -= MuonVect[m1].innerTrack_pt();
                    }
                    trackIso1 /= MuonVect[m1].pt();
                    trackIso2 /= MuonVect[m2].pt();
                    if(trackIso1 < 0. || std::isinf(trackIso1) || trackIso1 != trackIso1) trackIso1 = 0.;
                    if(trackIso2 < 0. || std::isinf(trackIso2) || trackIso2 != trackIso2) trackIso2 = 0.;
                    if(maxZpt > m_VPtCut) {
                        Hist("Muon1_trkIso", "mmqq")->Fill(trackIso1, EventWeight);
                        Hist("Muon2_trkIso", "mmqq")->Fill(trackIso2, EventWeight);
                    }
                    // Apply muon iso
                    if( !(trackIso1 < 0.10 && trackIso2 < 0.10) ) {m_logger << INFO << " - No double muon Iso" << SLogger::endmsg;}
                    else {
                        Hist("Events", "mmqq")->Fill(6., EventWeight);
                        Hist("Z_mass", "mm")->Fill(Zmass, EventWeight);
                        Hist("Z_pt", "mm")->Fill(maxZpt, EventWeight);
                        Hist("Muon1_pt", "mm")->Fill(MuonVect[m1].pt(), EventWeight);
                        Hist("Muon2_pt", "mm")->Fill(MuonVect[m2].pt(), EventWeight);
                        if(isMatched) {Hist("dR_HighptTrackerIdTrackerIso", "Muons")->Fill(dRll); Hist("pT_HighptTrackerIdTrackerIso", "Muons")->Fill(pTll);}
                        // Build candidate
                        V = MuonVect[m1].tlv() + MuonVect[m2].tlv();
                        if(maxZpt < m_VPtCut) {m_logger << INFO << " - No V boost" << SLogger::endmsg;}
                        else {
                            // Check trigger consistency
                            if(!triggerMap["SingleMu"] && !triggerMap["MET"] && !triggerMap["METMHT"] && !triggerMap["METMHTNoMu"]) { m_logger << INFO << " - Trigger inconsistency" << SLogger::endmsg; throw SError( SError::SkipEvent ); }
                            if(!isMC && ((sample.find("MET")!=std::string::npos && triggerMap["SingleMu"]) || (sample.find("Muon")!=std::string::npos && !triggerMap["SingleMu"]))) { m_logger << INFO << " - Trigger double counting" << SLogger::endmsg; throw SError( SError::SkipEvent ); }
                            // SF
                            if(isMC) {
                                TriggerWeight *= m_ScaleFactorTool.GetTrigMuonMET(MuonVect[m1].pt(), MuonVect[m1].eta(), MuonVect[m2].pt(), MuonVect[m2].eta(), MaxMETNoMuMHTNoMu);
                                LeptonWeight *= m_ScaleFactorTool.GetMuonHighptId(MuonVect[mHPT].pt(), MuonVect[mHPT].eta());
                                LeptonWeight *= m_ScaleFactorTool.GetMuonTrkId(MuonVect[mTHPT].pt(), MuonVect[mTHPT].eta());
                                LeptonWeight *= m_ScaleFactorTool.GetMuonLooseTrkIso(MuonVect[m1].pt(), MuonVect[m1].eta());
                                LeptonWeight *= m_ScaleFactorTool.GetMuonLooseTrkIso(MuonVect[m2].pt(), MuonVect[m2].eta());
                                LeptonWeight *= pow(m_ScaleFactorTool.GetMuonTrk(nPV), 2);
                                EventWeight *= TriggerWeight * LeptonWeight;
                                //
                                TriggerWeightUp *= m_ScaleFactorTool.GetTrigMuonMET(MuonVect[m1].pt(), MuonVect[m1].eta(), MuonVect[m2].pt(), MuonVect[m2].eta(), MaxMETNoMuMHTNoMu, +1);
                                LeptonWeightUp *= m_ScaleFactorTool.GetMuonHighptId(MuonVect[mHPT].pt(), MuonVect[mHPT].eta(), +1);
                                LeptonWeightUp *= m_ScaleFactorTool.GetMuonTrkId(MuonVect[mTHPT].pt(), MuonVect[mTHPT].eta(), +1);
                                LeptonWeightUp *= m_ScaleFactorTool.GetMuonLooseTrkIso(MuonVect[m1].pt(), MuonVect[m1].eta(), +1);
                                LeptonWeightUp *= m_ScaleFactorTool.GetMuonLooseTrkIso(MuonVect[m2].pt(), MuonVect[m2].eta(), +1);
                                LeptonWeightUp *= pow(m_ScaleFactorTool.GetMuonTrk(nPV, +1), 2);
                                TriggerWeightDown *= m_ScaleFactorTool.GetTrigMuonMET(MuonVect[m1].pt(), MuonVect[m1].eta(), MuonVect[m2].pt(), MuonVect[m2].eta(), MaxMETNoMuMHTNoMu, -1);
                                LeptonWeightDown *= m_ScaleFactorTool.GetMuonHighptId(MuonVect[mHPT].pt(), MuonVect[mHPT].eta(), -1);
                                LeptonWeightDown *= m_ScaleFactorTool.GetMuonTrkId(MuonVect[mTHPT].pt(), MuonVect[mTHPT].eta(), -1);
                                LeptonWeightDown *= m_ScaleFactorTool.GetMuonLooseTrkIso(MuonVect[m1].pt(), MuonVect[m1].eta(), -1);
                                LeptonWeightDown *= m_ScaleFactorTool.GetMuonLooseTrkIso(MuonVect[m2].pt(), MuonVect[m2].eta(), -1);
                                LeptonWeightDown *= pow(m_ScaleFactorTool.GetMuonTrk(nPV, -1), 2);
                            }
                            isZtoMM = true;
                            Hist("Events", "mmqq")->Fill(7., EventWeight);
                            m_logger << INFO << " + Z -> mm candidate reconstructed" << SLogger::endmsg;
                        }
                    }
                }
            }
        }
    }
    // --- Z -> ee ---
    if(!isZtoMM && ElecVect.size()>=2) {
        m_logger << INFO << " + Try to reconstruct Z -> ee"  << SLogger::endmsg;
        Hist("Events", "eeqq")->Fill(2., EventWeight);
        // Indentify leptons
        float maxZpt(-1.), Zpt(-1.), Zmass(-1.), dRll(-1.), pTll(-1.);
        for(unsigned int i = 0; i < ElecVect.size(); i++) {
            for(unsigned int j = 1; j < ElecVect.size(); j++) {
                if(i==j || ElecVect[i].charge() == ElecVect[j].charge()) continue;
                Zpt = (CalibratedElecVect[i] + CalibratedElecVect[j]).Pt();
                Zmass = (CalibratedElecVect[i] + CalibratedElecVect[j]).M();
                if(Zmass > 70. && Zmass < 110. && Zpt > maxZpt) {e1 = i; e2 = j; maxZpt = Zpt;}
            }
        }
        // Check suitable electrons
        if(e1 < 0 || e2 < 0) {m_logger << INFO << " - No OS electrons" << SLogger::endmsg;}
        else {
            Hist("Events", "eeqq")->Fill(3., EventWeight);
            if( !(CalibratedElecVect[e1].Pt() > m_Elec1PtCut && CalibratedElecVect[e2].Pt() > m_Elec2PtCut) ) {m_logger << INFO << " - No electrons above threshold" << SLogger::endmsg;}
            else {
                Hist("Events", "eeqq")->Fill(4., EventWeight);
                //fillElectronPlots(&ElecVect[m1], &ElecVect[m2], LepP, LepM);
                bool isMatched( isMC && LepP.Pt()>0. && LepM.Pt()>0. && (ElecVect[e1].tlv().DeltaR(LepP) < 0.05 || ElecVect[e1].tlv().DeltaR(LepM) < 0.05) && (ElecVect[e2].tlv().DeltaR(LepP) < 0.05 || ElecVect[e2].tlv().DeltaR(LepM) < 0.05));
                if(isMatched) {
                    dRll = LepP.DeltaR(LepM);
                    pTll = (LepP+LepM).Pt();
                    Hist("dR", "Electrons")->Fill(dRll); Hist("pT", "Electrons")->Fill(pTll); Hist("pT1", "Electrons")->Fill(CalibratedElecVect[e1].Pt()); Hist("pT2", "Electrons")->Fill(CalibratedElecVect[e2].Pt());
                    if(ElecVect[e1].isVetoElectron() && ElecVect[e2].isVetoElectron()) {Hist("dR_VetoVetoId", "Electrons")->Fill(dRll); Hist("pT_VetoVetoId", "Electrons")->Fill(pTll);}
                    if(ElecVect[e1].isLooseElectron() && ElecVect[e2].isLooseElectron()) {Hist("dR_LooseLooseId", "Electrons")->Fill(dRll); Hist("pT_LooseLooseId", "Electrons")->Fill(pTll);}
                    if(ElecVect[e1].isMediumElectron() && ElecVect[e2].isMediumElectron()) {Hist("dR_MediumMediumId", "Electrons")->Fill(dRll); Hist("pT_MediumMediumId", "Electrons")->Fill(pTll);}
                    if(ElecVect[e1].isTightElectron() && ElecVect[e2].isTightElectron()) {Hist("dR_TightTightId", "Electrons")->Fill(dRll); Hist("pT_TightTightId", "Electrons")->Fill(pTll);}
                    if(ElecVect[e1].isHeepElectron()==1 && ElecVect[e2].isHeepElectron()==1) {Hist("dR_HeepHeepId", "Electrons")->Fill(dRll); Hist("pT_HeepHeepId", "Electrons")->Fill(pTll);}
                    if(ElecVect[e1].isLooseElectron()) Hist("pT1_LooseId", "Electrons")->Fill(CalibratedElecVect[e1].Pt());
                    if(ElecVect[e2].isLooseElectron()) Hist("pT2_LooseId", "Electrons")->Fill(CalibratedElecVect[e2].Pt());
                }
                if(maxZpt > m_VPtCut) {
                    Hist("Electron1_pfIso", "eeqq")->Fill(ElecVect[e1].pfRhoCorrRelIso03(), EventWeight);
                    Hist("Electron2_pfIso", "eeqq")->Fill(ElecVect[e2].pfRhoCorrRelIso03(), EventWeight);
                }
                // Apply electron Id
                if( !(ElecVect[e1].isLooseElectron() && ElecVect[e2].isLooseElectron()) ) {m_logger << INFO << " - No double electron Id/Iso" << SLogger::endmsg;}
                else {
                    Hist("Events", "eeqq")->Fill(5., EventWeight);
                    Hist("Z_mass", "ee")->Fill(Zmass, EventWeight);
                    Hist("Z_pt", "ee")->Fill(maxZpt, EventWeight);
                    Hist("Electron1_pt", "ee")->Fill(CalibratedElecVect[e1].Pt(), EventWeight);
                    Hist("Electron2_pt", "ee")->Fill(CalibratedElecVect[e2].Pt(), EventWeight);
                    // Build candidate
                    V = CalibratedElecVect[e1] + CalibratedElecVect[e2];
                    if(maxZpt < m_VPtCut) {m_logger << INFO << " - No V boost" << SLogger::endmsg;}
                    else {
                        // Check trigger consistency
                        if(!triggerMap["SingleEle"] && !triggerMap["SingleIsoEle"]) { m_logger << INFO << " - Trigger inconsistency" << SLogger::endmsg; throw SError( SError::SkipEvent ); }
                        // SF
                        if(isMC) {
                            TriggerWeight *= m_ScaleFactorTool.GetTrigEle(ElecVect[e1].pt(), ElecVect[e1].eta(), ElecVect[e2].pt(), ElecVect[e2].eta());
                            LeptonWeight *= m_ScaleFactorTool.GetEleIdLooseWP(ElecVect[e1].pt(), ElecVect[e1].eta());
                            LeptonWeight *= m_ScaleFactorTool.GetEleIdLooseWP(ElecVect[e2].pt(), ElecVect[e2].eta());
                            LeptonWeight *= m_ScaleFactorTool.GetEleReco(ElecVect[e1].pt(), ElecVect[e1].eta());
                            LeptonWeight *= m_ScaleFactorTool.GetEleReco(ElecVect[e2].pt(), ElecVect[e2].eta());
                            EventWeight *= TriggerWeight * LeptonWeight;
                            //
                            TriggerWeightUp *= m_ScaleFactorTool.GetTrigEle(ElecVect[e1].pt(), ElecVect[e1].eta(), ElecVect[e2].pt(), ElecVect[e2].eta(), +1);
                            LeptonWeightUp *= m_ScaleFactorTool.GetEleIdLooseWP(ElecVect[e1].pt(), ElecVect[e1].eta(), +1);
                            LeptonWeightUp *= m_ScaleFactorTool.GetEleIdLooseWP(ElecVect[e2].pt(), ElecVect[e2].eta(), +1);
                            LeptonWeightUp *= m_ScaleFactorTool.GetEleReco(ElecVect[e1].pt(), ElecVect[e1].eta(), +1);
                            LeptonWeightUp *= m_ScaleFactorTool.GetEleReco(ElecVect[e2].pt(), ElecVect[e2].eta(), +1);
                            TriggerWeightDown *= m_ScaleFactorTool.GetTrigEle(ElecVect[e1].pt(), ElecVect[e1].eta(), ElecVect[e2].pt(), ElecVect[e2].eta(), -1);
                            LeptonWeightDown *= m_ScaleFactorTool.GetEleIdLooseWP(ElecVect[e1].pt(), ElecVect[e1].eta(), -1);
                            LeptonWeightDown *= m_ScaleFactorTool.GetEleIdLooseWP(ElecVect[e2].pt(), ElecVect[e2].eta(), -1);
                            LeptonWeightDown *= m_ScaleFactorTool.GetEleReco(ElecVect[e1].pt(), ElecVect[e1].eta(), -1);
                            LeptonWeightDown *= m_ScaleFactorTool.GetEleReco(ElecVect[e2].pt(), ElecVect[e2].eta(), -1);
                        }
                        isZtoEE = true;
                        Hist("Events", "eeqq")->Fill(6., EventWeight);
                        m_logger << INFO << " + Z -> ee candidate reconstructed" << SLogger::endmsg;
                    }
                }
            }
        }
    }


The Z candidates are built, skip events otherwise


    if(!isZtoMM && !isZtoEE) { m_logger << INFO << " - No V candidate" << SLogger::endmsg; throw SError( SError::SkipEvent ); }
    

    // -----------------------------------
    //           HADRONIC HIGGS
    // -----------------------------------

    if(FatJetsVect.size()==0) { m_logger << INFO << " - N Fat Jets = 0" << SLogger::endmsg; throw SError( SError::SkipEvent ); }
    
    if(isZtoNN) Hist("Events", "nnqq")->Fill(5., EventWeight);
    if(isWtoEN) Hist("Events", "enqq")->Fill(6., EventWeight);
    if(isWtoMN) Hist("Events", "mnqq")->Fill(7., EventWeight);
    if(isZtoEE) Hist("Events", "eeqq")->Fill(7., EventWeight);
    if(isZtoMM) Hist("Events", "mmqq")->Fill(8., EventWeight);
    m_logger << INFO << " + N Fat Jets > 0" << SLogger::endmsg;
    
    H = FatJetsVect[0].tlv();
    
    
    // -----------------------------------
    //           X and VARIABLES
    // -----------------------------------
    X = V + H;
    
    
    isTveto = (nBVetoJets==0 && nTaus==0);
    H_mass = FatJetsMassVect[0];
    H_tau21 = FatJetsTau21Vect[0];
    H_ddt = H_mass != 0. ? H_tau21 + 0.063 * log( H_mass*H_mass/H.Pt() ) : -1.;
    H_csv1 = std::max(Hcsv1, Hcsv2);
    H_csv2 = std::min(Hcsv1, Hcsv2);
    H_flav1 = isMC && FatJetsVect[0].subjet_softdrop_N() > 0 ? FatJetsVect[0].subjet_softdrop_partonFlavour()[0] : 0;
    H_flav2 = isMC && FatJetsVect[0].subjet_softdrop_N() > 1 ? FatJetsVect[0].subjet_softdrop_partonFlavour()[1] : 0;
    H_dbt = FatJetsVect[0].Hbbtag();
    H_ntag = FatJetsBTagVect[0];
    H_chf = FatJetsVect[0].chf();
    H_nhf = FatJetsVect[0].nhf();
    H_phf = FatJetsVect[0].phf();
    H_muf = FatJetsVect[0].muf();
    H_emf = FatJetsVect[0].emf();
    H_chm = FatJetsVect[0].chm();
    V_mass = V.M();
    X_mass = X.M();
    
    m_logger << INFO << " - Variables filled, now cleaning" << SLogger::endmsg;
    
    // -----------------------------------
    //           CLEANING
    // -----------------------------------
    
    if(isZtoEE) {
        // N-1 plots
        if(X_mass > m_XMassLowerCut) {
            Hist("ZJetDPhi", "eeqq")->Fill(fabs(V.DeltaPhi(H)), EventWeight);
            Hist("ZJetDEta", "eeqq")->Fill(fabs(V.Eta()-H.Eta()), EventWeight);
        }
        if(!(fabs(V.DeltaPhi(H)) > 2.)) {
            m_logger << INFO << " - ZtoEE event failed noise cleaning" << SLogger::endmsg;
            throw SError( SError::SkipEvent );
        }
        Hist("Events", "eeqq")->Fill(8., EventWeight);
        if(X_mass < m_XMassLowerCut) {
            m_logger << INFO << " - X candidate low mass" << SLogger::endmsg;
            throw SError( SError::SkipEvent );
        }
        Hist("Events", "eeqq")->Fill(9., EventWeight);
        fill4VectPlots(CalibratedElecVect[e1], "Electron1", "eeqq");
        fill4VectPlots(CalibratedElecVect[e2], "Electron2", "eeqq");
        fillJetPlots(FatJetsVect[0], FatJetsMassVect[0], FatJetsTau21Vect[0], "Jet", "eeqq");
        fillMEtPlots(MET, "eeqq");
        fillEventPlots("eeqq");
        if(fabs(ElecVect[e1].eta()) < 1.4442) Hist("Electron1_pt_B", "eeqq")->Fill(CalibratedElecVect[e1].Pt(), EventWeight);
        else if(fabs(ElecVect[e1].eta()) < 1.566) Hist("Electron1_pt_E", "eeqq")->Fill(CalibratedElecVect[e1].Pt(), EventWeight);
        if(fabs(ElecVect[e2].eta()) < 1.4442) Hist("Electron2_pt_B", "eeqq")->Fill(CalibratedElecVect[e2].Pt(), EventWeight);
        else if(fabs(ElecVect[e2].eta()) < 1.566) Hist("Electron2_pt_E", "eeqq")->Fill(CalibratedElecVect[e2].Pt(), EventWeight);
        //Hist("Electron1_pfIso", "eeqq")->Fill(ElecVect[e1].pfRhoCorrRelIso03(), EventWeight);
        //Hist("Electron2_pfIso", "eeqq")->Fill(ElecVect[e2].pfRhoCorrRelIso03(), EventWeight);
        Hist("ElectronElectronDR", "eeqq")->Fill(fabs(CalibratedElecVect[e1].DeltaR(CalibratedElecVect[e2])), EventWeight);
        Hist("Z_pt", "eeqq")->Fill(V.Pt(), EventWeight);
        Hist("Z_mass", "eeqq")->Fill(V.M(), EventWeight);
        Hist("X_mass", "eeqq")->Fill(X_mass, EventWeight);
        if(fabs(ElecVect[e1].eta()) < 1.4442 && fabs(ElecVect[e2].eta()) < 1.4442) Hist("Z_mass_BB", "eeqq")->Fill(V.M(), EventWeight);
        if(fabs(ElecVect[e1].eta()) < 1.4442 && fabs(ElecVect[e2].eta()) > 1.4442) Hist("Z_mass_BE", "eeqq")->Fill(V.M(), EventWeight);
        if(fabs(ElecVect[e1].eta()) > 1.4442 && fabs(ElecVect[e2].eta()) < 1.4442) Hist("Z_mass_EB", "eeqq")->Fill(V.M(), EventWeight);
        if(fabs(ElecVect[e1].eta()) > 1.4442 && fabs(ElecVect[e2].eta()) > 1.4442) Hist("Z_mass_EE", "eeqq")->Fill(V.M(), EventWeight);
        
    }
    if(isZtoMM) {
        // N-1 plots
        if(X_mass > m_XMassLowerCut) {
            Hist("ZJetDPhi", "mmqq")->Fill(fabs(V.DeltaPhi(H)), EventWeight);
            Hist("ZJetDEta", "mmqq")->Fill(fabs(V.Eta()-H.Eta()), EventWeight);
        }
        if(!(fabs(V.DeltaPhi(H)) > 2.)) {
            m_logger << INFO << " - ZtoMM event failed noise cleaning" << SLogger::endmsg;
            throw SError( SError::SkipEvent );
        }
        Hist("Events", "mmqq")->Fill(9., EventWeight);
        if(X_mass < m_XMassLowerCut) {
            m_logger << INFO << " - X candidate low mass" << SLogger::endmsg;
            throw SError( SError::SkipEvent );
        }
        Hist("Events", "mmqq")->Fill(10., EventWeight);
        fill4VectPlots(MuonVect[m1].tlv(), "Muon1", "mmqq");
        fill4VectPlots(MuonVect[m2].tlv(), "Muon2", "mmqq");
        fillJetPlots(FatJetsVect[0], FatJetsMassVect[0], FatJetsTau21Vect[0], "Jet", "mmqq");
        fillMEtPlots(MET, "mmqq");
        fillEventPlots("mmqq");
        if(fabs(MuonVect[m1].eta()) < 1.2) Hist("Muon1_pt_B", "mmqq")->Fill(MuonVect[m1].pt(), EventWeight);
        else Hist("Muon1_pt_E", "mmqq")->Fill(MuonVect[m1].pt(), EventWeight);
        if(fabs(MuonVect[m2].eta()) < 1.2) Hist("Muon2_pt_B", "mmqq")->Fill(MuonVect[m2].pt(), EventWeight);
        else Hist("Muon2_pt_E", "mmqq")->Fill(MuonVect[m2].pt(), EventWeight);
        //Hist("Muon1_trkIso", "mmqq")->Fill(trackIso1, EventWeight); // to be filled together with candidate
        //Hist("Muon2_trkIso", "mmqq")->Fill(trackIso2, EventWeight);
        Hist("MuonMuonDR", "mmqq")->Fill(fabs(MuonVect[m1].DeltaR(MuonVect[m2])), EventWeight);
        Hist("Z_pt", "mmqq")->Fill(V.Pt(), EventWeight);
        Hist("Z_mass", "mmqq")->Fill(V.M(), EventWeight);
        Hist("X_mass", "mmqq")->Fill(X_mass, EventWeight);
        if(fabs(MuonVect[m1].eta()) < 1.2 && fabs(MuonVect[m2].eta()) < 1.2) Hist("Z_mass_BB", "mmqq")->Fill(V.M(), EventWeight);
        if(fabs(MuonVect[m1].eta()) < 1.2 && fabs(MuonVect[m2].eta()) > 1.2) Hist("Z_mass_BE", "mmqq")->Fill(V.M(), EventWeight);
        if(fabs(MuonVect[m1].eta()) > 1.2 && fabs(MuonVect[m2].eta()) < 1.2) Hist("Z_mass_EB", "mmqq")->Fill(V.M(), EventWeight);
        if(fabs(MuonVect[m1].eta()) > 1.2 && fabs(MuonVect[m2].eta()) > 1.2) Hist("Z_mass_EE", "mmqq")->Fill(V.M(), EventWeight);
    }
    

    // Semileptonic analysis categorization
    if(isZtoEE || isZtoMM) {
    
        if(isZtoNN) Hist("Events", "nnqq")->Fill(8., EventWeight);
        if(isWtoEN) Hist("Events", "enqq")->Fill(9., EventWeight);
        if(isWtoMN) Hist("Events", "mnqq")->Fill(10., EventWeight);
        
        // Signal Regions
        if(H_mass > m_HMassLowerCut && H_mass < m_HMassUpperCut) {
            // Cut flow
            if(isZtoNN) Hist("Events", "nnqq")->Fill(9., EventWeight);
            if(isWtoEN) Hist("Events", "enqq")->Fill(10., EventWeight);
            if(isWtoMN) Hist("Events", "mnqq")->Fill(11., EventWeight);
            if(isZtoEE) Hist("Events", "eeqq")->Fill(10., EventWeight);
            if(isZtoMM) Hist("Events", "mmqq")->Fill(11., EventWeight);
            // Single b-tag
            if(H_ntag >= 1) {
                if(isZtoNN) Hist("Events", "nnqq")->Fill(10., EventWeight);
                if(isWtoEN) Hist("Events", "enqq")->Fill(11., EventWeight);
                if(isWtoMN) Hist("Events", "mnqq")->Fill(12., EventWeight);
                if(isZtoEE) Hist("Events", "eeqq")->Fill(11., EventWeight);
                if(isZtoMM) Hist("Events", "mmqq")->Fill(12., EventWeight);
            }
            // Double b-tag
            if(H_ntag == 2) {
                if(isZtoNN) Hist("Events", "nnqq")->Fill(11., EventWeight);
                if(isWtoEN) Hist("Events", "enqq")->Fill(12., EventWeight);
                if(isWtoMN) Hist("Events", "mnqq")->Fill(13., EventWeight);
                if(isZtoEE) Hist("Events", "eeqq")->Fill(12., EventWeight);
                if(isZtoMM) Hist("Events", "mmqq")->Fill(13., EventWeight);
            }
        }
        
        
        
    }
    
    
    
    m_logger << INFO << " + Tree filled" << SLogger::endmsg;
    
    return;
}


