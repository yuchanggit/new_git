ALL_SUBSYSTEMS+=DataFormats
subdirs_src_DataFormats = src_DataFormats_JetReco
ALL_PACKAGES += DataFormats/JetReco
subdirs_src_DataFormats_JetReco := src_DataFormats_JetReco_src
ALL_SUBSYSTEMS+=RecoJets
subdirs_src_RecoJets = src_RecoJets_JetProducers
ALL_PACKAGES += RecoJets/JetProducers
subdirs_src_RecoJets_JetProducers := src_RecoJets_JetProducers_plugins src_RecoJets_JetProducers_doc src_RecoJets_JetProducers_interface src_RecoJets_JetProducers_python src_RecoJets_JetProducers_src src_RecoJets_JetProducers_data src_RecoJets_JetProducers_test
ifeq ($(strip $(PyRecoJetsJetProducers)),)
PyRecoJetsJetProducers := self/src/RecoJets/JetProducers/python
src_RecoJets_JetProducers_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoJets/JetProducers/python)
PyRecoJetsJetProducers_files := $(patsubst src/RecoJets/JetProducers/python/%,%,$(wildcard $(foreach dir,src/RecoJets/JetProducers/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoJetsJetProducers_LOC_USE := self  
PyRecoJetsJetProducers_PACKAGE := self/src/RecoJets/JetProducers/python
ALL_PRODS += PyRecoJetsJetProducers
PyRecoJetsJetProducers_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoJetsJetProducers,src/RecoJets/JetProducers/python,src_RecoJets_JetProducers_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoJetsJetProducers,src/RecoJets/JetProducers/python))
endif
ALL_COMMONRULES += src_RecoJets_JetProducers_python
src_RecoJets_JetProducers_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_python,src/RecoJets/JetProducers/python,PYTHON))
ifeq ($(strip $(test-large-voronoi-area)),)
test-large-voronoi-area_files := $(patsubst src/RecoJets/JetProducers/test/%,%,$(foreach file,test-large-voronoi-area.cc,$(eval xfile:=$(wildcard src/RecoJets/JetProducers/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoJets/JetProducers/test/$(file). Please fix src/RecoJets/JetProducers/test/BuildFile.))))
test-large-voronoi-area := self/src/RecoJets/JetProducers/test
test-large-voronoi-area_TEST_RUNNER_CMD :=  test-large-voronoi-area 
test-large-voronoi-area_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoJets/JetProducers/test/BuildFile
test-large-voronoi-area_LOC_USE := self  RecoJets/JetProducers RecoJets/JetAlgorithms FWCore/Framework DataFormats/JetReco DataFormats/VertexReco Geometry/CaloGeometry Geometry/Records CommonTools/UtilAlgos fastjet
test-large-voronoi-area_PACKAGE := self/src/RecoJets/JetProducers/test
ALL_PRODS += test-large-voronoi-area
test-large-voronoi-area_INIT_FUNC        += $$(eval $$(call Binary,test-large-voronoi-area,src/RecoJets/JetProducers/test,src_RecoJets_JetProducers_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_TEST),test,$(SCRAMSTORENAME_LOGS)))
test-large-voronoi-area_CLASS := TEST
else
$(eval $(call MultipleWarningMsg,test-large-voronoi-area,src/RecoJets/JetProducers/test))
endif
ALL_COMMONRULES += src_RecoJets_JetProducers_test
src_RecoJets_JetProducers_test_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_test,src/RecoJets/JetProducers/test,TEST))
