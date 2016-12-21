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
