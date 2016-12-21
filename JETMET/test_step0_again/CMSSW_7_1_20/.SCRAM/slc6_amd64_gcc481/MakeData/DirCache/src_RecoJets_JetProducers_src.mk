ifeq ($(strip $(RecoJets/JetProducers)),)
ALL_COMMONRULES += src_RecoJets_JetProducers_src
src_RecoJets_JetProducers_src_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_src,src/RecoJets/JetProducers/src,LIBRARY))
RecoJetsJetProducers := self/RecoJets/JetProducers
RecoJets/JetProducers := RecoJetsJetProducers
RecoJetsJetProducers_files := $(patsubst src/RecoJets/JetProducers/src/%,%,$(wildcard $(foreach dir,src/RecoJets/JetProducers/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
RecoJetsJetProducers_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoJets/JetProducers/BuildFile
RecoJetsJetProducers_LOC_USE := self  boost FWCore/Framework DataFormats/JetReco Geometry/CaloGeometry Geometry/CaloTopology Geometry/Records Geometry/CommonDetUnit SimDataFormats/CaloHit RecoJets/JetAlgorithms DataFormats/CastorReco CommonTools/Utils fastjet roottmva vdt_headers boost_serialization CondFormats/DataRecord
RecoJetsJetProducers_EX_LIB   := RecoJetsJetProducers
RecoJetsJetProducers_EX_USE   := $(foreach d,$(RecoJetsJetProducers_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
RecoJetsJetProducers_PACKAGE := self/src/RecoJets/JetProducers/src
ALL_PRODS += RecoJetsJetProducers
RecoJetsJetProducers_CLASS := LIBRARY
RecoJets/JetProducers_forbigobj+=RecoJetsJetProducers
RecoJetsJetProducers_INIT_FUNC        += $$(eval $$(call Library,RecoJetsJetProducers,src/RecoJets/JetProducers/src,src_RecoJets_JetProducers_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
