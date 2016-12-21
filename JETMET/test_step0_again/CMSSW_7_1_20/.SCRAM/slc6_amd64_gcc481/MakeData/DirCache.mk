ifeq ($(strip $(DataFormats/JetReco)),)
ALL_COMMONRULES += src_DataFormats_JetReco_src
src_DataFormats_JetReco_src_parent := DataFormats/JetReco
src_DataFormats_JetReco_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_DataFormats_JetReco_src,src/DataFormats/JetReco/src,LIBRARY))
DataFormatsJetReco := self/DataFormats/JetReco
DataFormats/JetReco := DataFormatsJetReco
DataFormatsJetReco_files := $(patsubst src/DataFormats/JetReco/src/%,%,$(wildcard $(foreach dir,src/DataFormats/JetReco/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
DataFormatsJetReco_BuildFile    := $(WORKINGDIR)/cache/bf/src/DataFormats/JetReco/BuildFile
DataFormatsJetReco_LOC_USE := self  DataFormats/CaloTowers DataFormats/ParticleFlowCandidate DataFormats/Candidate DataFormats/Common DataFormats/HepMCCandidate DataFormats/ParticleFlowReco DataFormats/TrackReco FWCore/Utilities rootrflx
DataFormatsJetReco_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,DataFormatsJetRecoCapabilities,DataFormatsJetReco,$(SCRAMSTORENAME_LIB),src/DataFormats/JetReco/src))
DataFormatsJetReco_LCGDICTS  := x x1 x2 x3 
DataFormatsJetReco_PRE_INIT_FUNC += $$(eval $$(call LCGDict,DataFormatsJetReco,src/DataFormats/JetReco/src/classes_3.h src/DataFormats/JetReco/src/classes_4.h src/DataFormats/JetReco/src/classes_1.h src/DataFormats/JetReco/src/classes_2.h,src/DataFormats/JetReco/src/classes_def_3.xml src/DataFormats/JetReco/src/classes_def_4.xml src/DataFormats/JetReco/src/classes_def_1.xml src/DataFormats/JetReco/src/classes_def_2.xml,$(SCRAMSTORENAME_LIB),$(GENREFLEX_ARGS) --fail_on_warnings,Capabilities))
DataFormatsJetReco_EX_LIB   := DataFormatsJetReco
DataFormatsJetReco_EX_USE   := $(foreach d,$(DataFormatsJetReco_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
DataFormatsJetReco_PACKAGE := self/src/DataFormats/JetReco/src
ALL_PRODS += DataFormatsJetReco
DataFormatsJetReco_CLASS := LIBRARY
DataFormats/JetReco_forbigobj+=DataFormatsJetReco
DataFormatsJetReco_INIT_FUNC        += $$(eval $$(call Library,DataFormatsJetReco,src/DataFormats/JetReco/src,src_DataFormats_JetReco_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(RecoJetsJetProducers_plugins)),)
RecoJetsJetProducers_plugins := self/src/RecoJets/JetProducers/plugins
PLUGINS:=yes
RecoJetsJetProducers_plugins_files := $(patsubst src/RecoJets/JetProducers/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/RecoJets/JetProducers/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoJets/JetProducers/plugins/$(file). Please fix src/RecoJets/JetProducers/plugins/BuildFile.))))
RecoJetsJetProducers_plugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoJets/JetProducers/plugins/BuildFile
RecoJetsJetProducers_plugins_LOC_USE := self  RecoJets/JetProducers RecoJets/JetAlgorithms FWCore/Framework DataFormats/JetReco DataFormats/VertexReco Geometry/CaloGeometry Geometry/Records CommonTools/UtilAlgos CondFormats/JetMETObjects JetMETCorrections/Objects fastjet fastjet-contrib
RecoJetsJetProducers_plugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoJetsJetProducers_plugins,RecoJetsJetProducers_plugins,$(SCRAMSTORENAME_LIB),src/RecoJets/JetProducers/plugins))
RecoJetsJetProducers_plugins_PACKAGE := self/src/RecoJets/JetProducers/plugins
ALL_PRODS += RecoJetsJetProducers_plugins
RecoJets/JetProducers_forbigobj+=RecoJetsJetProducers_plugins
RecoJetsJetProducers_plugins_INIT_FUNC        += $$(eval $$(call Library,RecoJetsJetProducers_plugins,src/RecoJets/JetProducers/plugins,src_RecoJets_JetProducers_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
RecoJetsJetProducers_plugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoJetsJetProducers_plugins,src/RecoJets/JetProducers/plugins))
endif
ALL_COMMONRULES += src_RecoJets_JetProducers_plugins
src_RecoJets_JetProducers_plugins_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_plugins,src/RecoJets/JetProducers/plugins,PLUGINS))
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
