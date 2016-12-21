############## All Tools Variables ################
CUDASRC_FILES_SUFFIXES := 
CXXSRC_FILES_SUFFIXES     := cxx cc C cpp
CSRC_FILES_SUFFIXES       := c
FORTRANSRC_FILES_SUFFIXES := F f77 f F77
SRC_FILES_SUFFIXES        := $(CXXSRC_FILES_SUFFIXES) $(CSRC_FILES_SUFFIXES) $(FORTRANSRC_FILES_SUFFIXES) $(CUDASRC_FILES_SUFFIXES)
SCRAM_ADMIN_DIR           := .SCRAM/$(SCRAM_ARCH)
SCRAM_TOOLS_DIR           := $(SCRAM_ADMIN_DIR)/timestamps
CFLAGS:=
LIBRARY_CFLAGS:=
TEST_CFLAGS:=
BINARY_CFLAGS:=
EDM_CFLAGS:=
CAPABILITIES_CFLAGS:=
LCGDICT_CFLAGS:=
ROOTDICT_CFLAGS:=
PRECOMPILE_CFLAGS:=
DEV_CFLAGS:=
RELEASE_CFLAGS:=
REM_CFLAGS:=
REM_LIBRARY_CFLAGS:=
REM_TEST_CFLAGS:=
REM_BINARY_CFLAGS:=
REM_EDM_CFLAGS:=
REM_CAPABILITIES_CFLAGS:=
REM_LCGDICT_CFLAGS:=
REM_ROOTDICT_CFLAGS:=
REM_PRECOMPILE_CFLAGS:=
REM_DEV_CFLAGS:=
REM_RELEASE_CFLAGS:=
CPPDEFINES:=
LIBRARY_CPPDEFINES:=
TEST_CPPDEFINES:=
BINARY_CPPDEFINES:=
EDM_CPPDEFINES:=
CAPABILITIES_CPPDEFINES:=
LCGDICT_CPPDEFINES:=
ROOTDICT_CPPDEFINES:=
PRECOMPILE_CPPDEFINES:=
DEV_CPPDEFINES:=
RELEASE_CPPDEFINES:=
REM_CPPDEFINES:=
REM_LIBRARY_CPPDEFINES:=
REM_TEST_CPPDEFINES:=
REM_BINARY_CPPDEFINES:=
REM_EDM_CPPDEFINES:=
REM_CAPABILITIES_CPPDEFINES:=
REM_LCGDICT_CPPDEFINES:=
REM_ROOTDICT_CPPDEFINES:=
REM_PRECOMPILE_CPPDEFINES:=
REM_DEV_CPPDEFINES:=
REM_RELEASE_CPPDEFINES:=
CPPFLAGS:=
LIBRARY_CPPFLAGS:=
TEST_CPPFLAGS:=
BINARY_CPPFLAGS:=
EDM_CPPFLAGS:=
CAPABILITIES_CPPFLAGS:=
LCGDICT_CPPFLAGS:=
ROOTDICT_CPPFLAGS:=
PRECOMPILE_CPPFLAGS:=
DEV_CPPFLAGS:=
RELEASE_CPPFLAGS:=
REM_CPPFLAGS:=
REM_LIBRARY_CPPFLAGS:=
REM_TEST_CPPFLAGS:=
REM_BINARY_CPPFLAGS:=
REM_EDM_CPPFLAGS:=
REM_CAPABILITIES_CPPFLAGS:=
REM_LCGDICT_CPPFLAGS:=
REM_ROOTDICT_CPPFLAGS:=
REM_PRECOMPILE_CPPFLAGS:=
REM_DEV_CPPFLAGS:=
REM_RELEASE_CPPFLAGS:=
CSHAREDOBJECTFLAGS:=
LIBRARY_CSHAREDOBJECTFLAGS:=
TEST_CSHAREDOBJECTFLAGS:=
BINARY_CSHAREDOBJECTFLAGS:=
EDM_CSHAREDOBJECTFLAGS:=
CAPABILITIES_CSHAREDOBJECTFLAGS:=
LCGDICT_CSHAREDOBJECTFLAGS:=
ROOTDICT_CSHAREDOBJECTFLAGS:=
PRECOMPILE_CSHAREDOBJECTFLAGS:=
DEV_CSHAREDOBJECTFLAGS:=
RELEASE_CSHAREDOBJECTFLAGS:=
REM_CSHAREDOBJECTFLAGS:=
REM_LIBRARY_CSHAREDOBJECTFLAGS:=
REM_TEST_CSHAREDOBJECTFLAGS:=
REM_BINARY_CSHAREDOBJECTFLAGS:=
REM_EDM_CSHAREDOBJECTFLAGS:=
REM_CAPABILITIES_CSHAREDOBJECTFLAGS:=
REM_LCGDICT_CSHAREDOBJECTFLAGS:=
REM_ROOTDICT_CSHAREDOBJECTFLAGS:=
REM_PRECOMPILE_CSHAREDOBJECTFLAGS:=
REM_DEV_CSHAREDOBJECTFLAGS:=
REM_RELEASE_CSHAREDOBJECTFLAGS:=
CXXFLAGS:=
LIBRARY_CXXFLAGS:=
TEST_CXXFLAGS:=
BINARY_CXXFLAGS:=
EDM_CXXFLAGS:=
CAPABILITIES_CXXFLAGS:=
LCGDICT_CXXFLAGS:=
ROOTDICT_CXXFLAGS:=
PRECOMPILE_CXXFLAGS:=
DEV_CXXFLAGS:=
RELEASE_CXXFLAGS:=
REM_CXXFLAGS:=
REM_LIBRARY_CXXFLAGS:=
REM_TEST_CXXFLAGS:=
REM_BINARY_CXXFLAGS:=
REM_EDM_CXXFLAGS:=
REM_CAPABILITIES_CXXFLAGS:=
REM_LCGDICT_CXXFLAGS:=
REM_ROOTDICT_CXXFLAGS:=
REM_PRECOMPILE_CXXFLAGS:=
REM_DEV_CXXFLAGS:=
REM_RELEASE_CXXFLAGS:=
CXXSHAREDFLAGS:=
LIBRARY_CXXSHAREDFLAGS:=
TEST_CXXSHAREDFLAGS:=
BINARY_CXXSHAREDFLAGS:=
EDM_CXXSHAREDFLAGS:=
CAPABILITIES_CXXSHAREDFLAGS:=
LCGDICT_CXXSHAREDFLAGS:=
ROOTDICT_CXXSHAREDFLAGS:=
PRECOMPILE_CXXSHAREDFLAGS:=
DEV_CXXSHAREDFLAGS:=
RELEASE_CXXSHAREDFLAGS:=
REM_CXXSHAREDFLAGS:=
REM_LIBRARY_CXXSHAREDFLAGS:=
REM_TEST_CXXSHAREDFLAGS:=
REM_BINARY_CXXSHAREDFLAGS:=
REM_EDM_CXXSHAREDFLAGS:=
REM_CAPABILITIES_CXXSHAREDFLAGS:=
REM_LCGDICT_CXXSHAREDFLAGS:=
REM_ROOTDICT_CXXSHAREDFLAGS:=
REM_PRECOMPILE_CXXSHAREDFLAGS:=
REM_DEV_CXXSHAREDFLAGS:=
REM_RELEASE_CXXSHAREDFLAGS:=
CXXSHAREDOBJECTFLAGS:=
LIBRARY_CXXSHAREDOBJECTFLAGS:=
TEST_CXXSHAREDOBJECTFLAGS:=
BINARY_CXXSHAREDOBJECTFLAGS:=
EDM_CXXSHAREDOBJECTFLAGS:=
CAPABILITIES_CXXSHAREDOBJECTFLAGS:=
LCGDICT_CXXSHAREDOBJECTFLAGS:=
ROOTDICT_CXXSHAREDOBJECTFLAGS:=
PRECOMPILE_CXXSHAREDOBJECTFLAGS:=
DEV_CXXSHAREDOBJECTFLAGS:=
RELEASE_CXXSHAREDOBJECTFLAGS:=
REM_CXXSHAREDOBJECTFLAGS:=
REM_LIBRARY_CXXSHAREDOBJECTFLAGS:=
REM_TEST_CXXSHAREDOBJECTFLAGS:=
REM_BINARY_CXXSHAREDOBJECTFLAGS:=
REM_EDM_CXXSHAREDOBJECTFLAGS:=
REM_CAPABILITIES_CXXSHAREDOBJECTFLAGS:=
REM_LCGDICT_CXXSHAREDOBJECTFLAGS:=
REM_ROOTDICT_CXXSHAREDOBJECTFLAGS:=
REM_PRECOMPILE_CXXSHAREDOBJECTFLAGS:=
REM_DEV_CXXSHAREDOBJECTFLAGS:=
REM_RELEASE_CXXSHAREDOBJECTFLAGS:=
FFLAGS:=
LIBRARY_FFLAGS:=
TEST_FFLAGS:=
BINARY_FFLAGS:=
EDM_FFLAGS:=
CAPABILITIES_FFLAGS:=
LCGDICT_FFLAGS:=
ROOTDICT_FFLAGS:=
PRECOMPILE_FFLAGS:=
DEV_FFLAGS:=
RELEASE_FFLAGS:=
REM_FFLAGS:=
REM_LIBRARY_FFLAGS:=
REM_TEST_FFLAGS:=
REM_BINARY_FFLAGS:=
REM_EDM_FFLAGS:=
REM_CAPABILITIES_FFLAGS:=
REM_LCGDICT_FFLAGS:=
REM_ROOTDICT_FFLAGS:=
REM_PRECOMPILE_FFLAGS:=
REM_DEV_FFLAGS:=
REM_RELEASE_FFLAGS:=
FOPTIMISEDFLAGS:=
LIBRARY_FOPTIMISEDFLAGS:=
TEST_FOPTIMISEDFLAGS:=
BINARY_FOPTIMISEDFLAGS:=
EDM_FOPTIMISEDFLAGS:=
CAPABILITIES_FOPTIMISEDFLAGS:=
LCGDICT_FOPTIMISEDFLAGS:=
ROOTDICT_FOPTIMISEDFLAGS:=
PRECOMPILE_FOPTIMISEDFLAGS:=
DEV_FOPTIMISEDFLAGS:=
RELEASE_FOPTIMISEDFLAGS:=
REM_FOPTIMISEDFLAGS:=
REM_LIBRARY_FOPTIMISEDFLAGS:=
REM_TEST_FOPTIMISEDFLAGS:=
REM_BINARY_FOPTIMISEDFLAGS:=
REM_EDM_FOPTIMISEDFLAGS:=
REM_CAPABILITIES_FOPTIMISEDFLAGS:=
REM_LCGDICT_FOPTIMISEDFLAGS:=
REM_ROOTDICT_FOPTIMISEDFLAGS:=
REM_PRECOMPILE_FOPTIMISEDFLAGS:=
REM_DEV_FOPTIMISEDFLAGS:=
REM_RELEASE_FOPTIMISEDFLAGS:=
FSHAREDOBJECTFLAGS:=
LIBRARY_FSHAREDOBJECTFLAGS:=
TEST_FSHAREDOBJECTFLAGS:=
BINARY_FSHAREDOBJECTFLAGS:=
EDM_FSHAREDOBJECTFLAGS:=
CAPABILITIES_FSHAREDOBJECTFLAGS:=
LCGDICT_FSHAREDOBJECTFLAGS:=
ROOTDICT_FSHAREDOBJECTFLAGS:=
PRECOMPILE_FSHAREDOBJECTFLAGS:=
DEV_FSHAREDOBJECTFLAGS:=
RELEASE_FSHAREDOBJECTFLAGS:=
REM_FSHAREDOBJECTFLAGS:=
REM_LIBRARY_FSHAREDOBJECTFLAGS:=
REM_TEST_FSHAREDOBJECTFLAGS:=
REM_BINARY_FSHAREDOBJECTFLAGS:=
REM_EDM_FSHAREDOBJECTFLAGS:=
REM_CAPABILITIES_FSHAREDOBJECTFLAGS:=
REM_LCGDICT_FSHAREDOBJECTFLAGS:=
REM_ROOTDICT_FSHAREDOBJECTFLAGS:=
REM_PRECOMPILE_FSHAREDOBJECTFLAGS:=
REM_DEV_FSHAREDOBJECTFLAGS:=
REM_RELEASE_FSHAREDOBJECTFLAGS:=
LDFLAGS:=
LIBRARY_LDFLAGS:=
TEST_LDFLAGS:=
BINARY_LDFLAGS:=
EDM_LDFLAGS:=
CAPABILITIES_LDFLAGS:=
LCGDICT_LDFLAGS:=
ROOTDICT_LDFLAGS:=
PRECOMPILE_LDFLAGS:=
DEV_LDFLAGS:=
RELEASE_LDFLAGS:=
REM_LDFLAGS:=
REM_LIBRARY_LDFLAGS:=
REM_TEST_LDFLAGS:=
REM_BINARY_LDFLAGS:=
REM_EDM_LDFLAGS:=
REM_CAPABILITIES_LDFLAGS:=
REM_LCGDICT_LDFLAGS:=
REM_ROOTDICT_LDFLAGS:=
REM_PRECOMPILE_LDFLAGS:=
REM_DEV_LDFLAGS:=
REM_RELEASE_LDFLAGS:=
LD_UNIT:=
LIBRARY_LD_UNIT:=
TEST_LD_UNIT:=
BINARY_LD_UNIT:=
EDM_LD_UNIT:=
CAPABILITIES_LD_UNIT:=
LCGDICT_LD_UNIT:=
ROOTDICT_LD_UNIT:=
PRECOMPILE_LD_UNIT:=
DEV_LD_UNIT:=
RELEASE_LD_UNIT:=
REM_LD_UNIT:=
REM_LIBRARY_LD_UNIT:=
REM_TEST_LD_UNIT:=
REM_BINARY_LD_UNIT:=
REM_EDM_LD_UNIT:=
REM_CAPABILITIES_LD_UNIT:=
REM_LCGDICT_LD_UNIT:=
REM_ROOTDICT_LD_UNIT:=
REM_PRECOMPILE_LD_UNIT:=
REM_DEV_LD_UNIT:=
REM_RELEASE_LD_UNIT:=
ALL_COMPILER_FLAGS := CFLAGS CPPDEFINES CPPFLAGS CSHAREDOBJECTFLAGS CXXFLAGS CXXSHAREDFLAGS CXXSHAREDOBJECTFLAGS FFLAGS FOPTIMISEDFLAGS FSHAREDOBJECTFLAGS LDFLAGS LD_UNIT 
SCRAM_MULTIPLE_COMPILERS := yes
SCRAM_DEFAULT_COMPILER    := gcc
SCRAM_COMPILER            := $(SCRAM_DEFAULT_COMPILER)
ifdef COMPILER
SCRAM_COMPILER            := $(COMPILER)
endif
CXX_TYPE_COMPILER := cxxcompiler
C_TYPE_COMPILER := ccompiler
F77_TYPE_COMPILER := f77compiler
ifndef SCRAM_IGNORE_MISSING_COMPILERS
$(if $(wildcard $(SCRAM_TOOLS_DIR)/$(SCRAM_COMPILER)-$(CXX_TYPE_COMPILER)),,$(info ****WARNING: You have selected $(SCRAM_COMPILER) as compiler but there is no $(SCRAM_COMPILER)-$(CXX_TYPE_COMPILER) tool setup. Default compiler $(SCRAM_DEFAULT_COMPILER)-$(CXX_TYPE_COMPILER) will be used to comple CXX files))
$(if $(wildcard $(SCRAM_TOOLS_DIR)/$(SCRAM_COMPILER)-$(C_TYPE_COMPILER)),,$(info ****WARNING: You have selected $(SCRAM_COMPILER) as compiler but there is no $(SCRAM_COMPILER)-$(C_TYPE_COMPILER) tool setup. Default compiler $(SCRAM_DEFAULT_COMPILER)-$(C_TYPE_COMPILER) will be used to comple C files))
$(if $(wildcard $(SCRAM_TOOLS_DIR)/$(SCRAM_COMPILER)-$(F77_TYPE_COMPILER)),,$(info ****WARNING: You have selected $(SCRAM_COMPILER) as compiler but there is no $(SCRAM_COMPILER)-$(F77_TYPE_COMPILER) tool setup. Default compiler $(SCRAM_DEFAULT_COMPILER)-$(F77_TYPE_COMPILER) will be used to comple F77 files))
endif
GCC_CXXCOMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1
CXX:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1/bin/c++
GCC_CCOMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1
CC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1/bin/gcc
GCC_F77COMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1
FC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1/bin/gfortran
ALL_TOOLS  += cxxcompiler
cxxcompiler_EX_USE    := $(if $(strip $(wildcard $(LOCALTOP)/$(SCRAM_TOOLS_DIR)/$(SCRAM_COMPILER)-cxxcompiler)),$(SCRAM_COMPILER)-cxxcompiler,$(SCRAM_DEFAULT_COMPILER)-cxxcompiler)
ALL_TOOLS  += ccompiler
ccompiler_EX_USE    := $(if $(strip $(wildcard $(LOCALTOP)/$(SCRAM_TOOLS_DIR)/$(SCRAM_COMPILER)-ccompiler)),$(SCRAM_COMPILER)-ccompiler,$(SCRAM_DEFAULT_COMPILER)-ccompiler)
ALL_TOOLS  += f77compiler
f77compiler_EX_USE    := $(if $(strip $(wildcard $(LOCALTOP)/$(SCRAM_TOOLS_DIR)/$(SCRAM_COMPILER)-f77compiler)),$(SCRAM_COMPILER)-f77compiler,$(SCRAM_DEFAULT_COMPILER)-f77compiler)
CMSSW_BASE:=/afs/cern.ch/work/y/yuchang/service_work/JETMET/test_download_7_1_20_cmsswcode_/test_step0_again/CMSSW_7_1_20
PROTOBUF_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/protobuf/2.4.1
BINDIR:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/protobuf/2.4.1/bin
GLIBC_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/glibc/2.12-2
CLHEP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/clhep/2.1.4.1-cms
LIBTIFF_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libtiff/3.9.4
HERWIG_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/herwig/6.521-ddibom2
LAPACK_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/lapack/3.3.1-cms
LIBHEPML_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libhepml/0.2.1
GSL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gsl/1.10
BOOST_PYTHON_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/boost/1.51.0-cms2
PYSTE_EXEC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/boost/1.51.0-cms2/lib/python2.7/site-packages/Pyste/pyste.py
DOXYGEN_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/doxygen/1.8.5-cms5
QTEXTRA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/qt/4.8.1
QT3SUPPORT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/qt/4.8.1
PY2_CJSON_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-cjson/1.0.5-cms2
ROOTRFLX_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/lcg/root/5.34.18-cms5
RIVET_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/rivet/1.8.2-cms8
QTDESIGNER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/qt/4.8.1
DPM_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/dpm/1.8.0.1
XROOTD_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/xrootd/3.2.4-cms2
GEANT4DATA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external
MAKE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gmake/3.81
ifeq ($(strip $(SCRAM_COMPILER)),distcc)
CXX:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/distcc/3.2rc1-cms3/bin/c++
endif
OPENLOOPS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/openloops/1.1.1
HEPMC_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/hepmc/2.06.07-cms4
DCAP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/dcap/2.47.8-cms2
JIMMY_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/jimmy/4.2-ddibom2
LIBUUID_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libuuid/2.22.2
FRONTIER_CLIENT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/frontier_client/2.8.10-cms
EVTGENLHC_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/evtgenlhc/9.1-cms3
LLVM_CCOMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2
ifeq ($(strip $(SCRAM_COMPILER)),llvm)
CC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2/bin/clang
endif
BLACKHAT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/blackhat/0.9.9-cms3
PACPARSER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pacparser/1.3.1
CASCADE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/cascade/2.2.04-ddibom2
MCTESTER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/mctester/1.25.0a-cms19
BOOSTHEADER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/boost/1.51.0-cms2
PYTHIA6_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pythia6/426
PY2_IPYTHON_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-ipython/0.10-cms2
CASTOR_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/castor/2.1.13.9-cms
TOPREX_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/toprex/4.23
PY2_MATPLOTLIB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-matplotlib/1.2.1-cms2
BOOST_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/boost/1.51.0-cms2
TCMALLOC_MINIMAL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/google-perftools/1.6
ORACLE_ADMINDIR:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/oracle-env/29-cms/etc
SIP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/sip/4.11.2-cms2
LCOV_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/lcov/1.9
FASTJET_CONTRIB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/fastjet-contrib/1.009-cms3
PYTHON_LDAP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/python-ldap/2.4.10-cms2
PYTHON_LDAP_PYPATH:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/python-ldap/2.4.10-cms2/lib/python2.7/site-packages
ZLIB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/zlib/1.2.8
PYMINUIT2_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pyminuit2/0.0.1-cms19
YAML_CPP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/yaml-cpp/0.5.1-cms
XZ_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/xz/5.0.3__5.1.2alpha-cms5
LLVM_ANALYZER_CXXCOMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2
ifeq ($(strip $(SCRAM_COMPILER)),llvm-analyzer)
CXX:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2/bin/c++-analyzer
endif
LIBXML2_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libxml2/2.7.7
XERCES_C_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/xerces-c/2.8.0
LLVM_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2
PHOTOSPP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/photospp/3.56
MCDB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/mcdb/1.0.2-cms
DB4_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/db4/4.4.20
SHERPA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/sherpa/2.1.1-ddibom3
PYTHIA6_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pythia6/426
ifeq ($(strip $(SCRAM_COMPILER)),distcc)
CC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/distcc/3.2rc1-cms3/bin/gcc
endif
GEANT4CORE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/geant4/10.00.p02-ddibom
G4LIB:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/geant4/10.00.p02-ddibom/lib
FASTJET_CONTRIB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/fastjet-contrib/1.009-cms3
GCCXML_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gccxml/0.9.0-20140124-0
FFTW3_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/fftw3/3.3.2
THEPEG_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/thepeg/1.9.2p1-ddibom2
LLVM_ANALYZER_CCOMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2
ifeq ($(strip $(SCRAM_COMPILER)),llvm-analyzer)
CC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2/bin/ccc-analyzer
endif
QT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/qt/4.8.1
SIGCPP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/sigcpp/2.2.10-cms4
HEPMC_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/hepmc/2.06.07-cms4
PYQT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pyqt/4.8.1-cms2
TAUOLA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/tauola/27.121.5
PCRE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pcre/7.9__8.33
LHAPDF_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/lhapdf/6.1.5-ddibom2
ifeq ($(strip $(SCRAM_COMPILER)),ccache)
CC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/ccache/3.1.8/bin/gcc
endif
ifeq ($(strip $(SCRAM_COMPILER)),ccache)
CXX:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/ccache/3.1.8/bin/c++
export CCACHE_BASEDIR:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/cmssw/CMSSW_7_1_20
endif
ifeq ($(strip $(SCRAM_COMPILER)),llvm)
FC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gcc/4.8.1/bin/gfortran
endif
MILLEPEDE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/millepede/V04-00-02
ROOTCINT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/lcg/root/5.34.18-cms5
OPENSSL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/openssl/0.9.8e__1.0.1-cms
CURL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/curl/7.28.0-cms
GNUPLOT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gnuplot/4.6.1
TBB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/tbb/42_20131118oss
GEANT4STATIC_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/geant4/10.00.p02-ddibom
DMTCP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/dmtcp/2.0-2212
ifeq ($(strip $(SCRAM_COMPILER)),ccache)
FC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/ccache/3.1.8/bin/gfortran
endif
ALPGEN_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/alpgen/214-cms
PYDATA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pythia6/426
PYCLANG_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2
LIBUNGIF_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libungif/4.1.4
PY2_CX_ORACLE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-cx-oracle/5.1-cms3
GRAPHVIZ_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/graphviz/2.16.1-cms
CMSSWDATA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms
CMSSW_DATA_PATH:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms
PY2_NUMPY_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-numpy/1.6.1-cms2
HECTOR_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/hector/1_3_4-cms19
CVS2GIT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/cvs2git/5419-cms2
QTBASE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/qt/4.8.1
GEANT4_PARFULLCMS:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/geant4-parfullcms/2014.01.27-ddibom
JEMALLOC_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/jemalloc/3.5.0
TAUOLA_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/tauola/27.121.5
PYTHON_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/python/2.7.6
PYTHON_COMPILE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/python/2.7.6/lib/python2.7/compileall.py
TKONLINESW_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/tkonlinesw/2.7.0-cms2
PY2_NETWORKX:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-networkx/1.8.1-cms
KTJET_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/ktjet/1.06-cms3
VDT_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/vdt/v0.3.2-cms
VDT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/vdt/v0.3.2-cms
PYTHIA8_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/pythia8/212
BZ2LIB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/bz2lib/1.0.5
GDB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gdb/7.7-cms4
LIBJPEG_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libjpg/8b
ifeq ($(strip $(SCRAM_COMPILER)),distcc)
FC:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/distcc/3.2rc1-cms3/bin/gfortran
endif
CASCADE_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/cascade/2.2.04-ddibom2
QD_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/qd/2.3.13
SLOCCOUNT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/sloccount/2.26-cms4
DBS_CLIENT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/dbs-client/DBS_2_1_9-cms2
PY2_PYGITHUB:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-pygithub/1.23.0-cms
GDBM_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gdbm/1.10
CPPUNIT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/cppunit/1.12.1
FFTJET_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/fftjet/1.5.0
EXPAT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/expat/2.0.1
PY2_PYCURL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-pycurl/7.19.0-cms2
PROFESSOR_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/professor/1.0.0-cms19
HERWIGPP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/herwigpp/2.7.1-ddibom2
ROOT_INTERFACE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/lcg/root/5.34.18-cms5
CASTOR_HEADER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/castor/2.1.13.9-cms
TAUOLAPP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/tauolapp/1.1.4-ddibom3
HEPPDT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/heppdt/3.03.00
PY2_SQLALCHEMY_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-sqlalchemy/0.8.2-cms3
PY2_LINT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-lint/0.25.1-cms2
CORAL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/coral/CORAL_2_3_21-ddibom
OPENLDAP_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/openldap/2.4.34-cms
DAS_CLIENT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/das_client/v02.05.00
LIBPNG_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/libpng/1.6.0-cms
PHOTOS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/photos/215.5
CYTHON_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/cython/0.19.1-cms
SQLITE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/sqlite/3.7.17
CLHEPHEADER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/clhep/2.1.4.1-cms
JIMMY_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/jimmy/4.2-ddibom2
CGAL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/cgal/4.2-cms6
EVTGEN_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/evtgen/1.3.0-ddibom3
GIT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/git/1.8.3.1-ddibom
PY2SHIPY_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-scipy/0.8.0-cms2
CLASSLIB_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/classlib/3.1.3-cms5
VALGRIND_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/valgrind/3.9.0-cms4
IGPROF_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/igprof/5.9.10
TCMALLOC_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/google-perftools/1.6
LLVM_CXXCOMPILER_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2
ifeq ($(strip $(SCRAM_COMPILER)),llvm)
CXX:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/llvm/3.4-cms2/bin/clang++
endif
MESCHACH_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/meschach/1.2.pCMS1
ORACLE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/oracle/11.2.0.3.0__10.2.0.4.0
TOPREX_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/toprex/4.23
ROOFIT_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/lcg/roofit/5.34.18-cms4
GLIMPSE_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/glimpse/4.18.5
PHOTOS_HEADERS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/photos/215.5
CHARYBDIS_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/charybdis/1.003-ddibom2
FASTJET_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/fastjet/3.0.3-cms2
PY2_PYTHON_DATEUTIL_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/py2-python-dateutil/1.1-cms2
YODA_BASE:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/yoda/1.0.4-cms
############## All SCRAM ENV variables ################
LOCALTOP:=/afs/cern.ch/work/y/yuchang/service_work/JETMET/test_download_7_1_20_cmsswcode_/test_step0_again/CMSSW_7_1_20
SCRAM_TMP:=tmp
SCRAM_INIT_LOCALTOP:=/afs/cern.ch/work/y/yuchang/service_work/JETMET/test_download_7_1_20_cmsswcode_/test_step0_again/CMSSW_7_1_20
SCRAM_BUILDFILE:=BuildFile
RELEASETOP:=/afs/cern.ch/cms/slc6_amd64_gcc481/cms/cmssw/CMSSW_7_1_20
SCRAM_INTlog:=logs
SCRAM_GMAKE_PATH:=/afs/cern.ch/cms/slc6_amd64_gcc481/external/gmake/3.81/bin/
SCRAM_INTwork:=tmp/slc6_amd64_gcc481
SCRAM_PROJECTNAME:=CMSSW
SCRAM_ARCH:=slc6_amd64_gcc481
SCRAM_SOURCEDIR:=src
SCRAM_RTBOURNE_SET:=CMSSW:CMSSW_7_1_20:slc6_amd64_gcc481:V2_2_7_pre1:SRT_
SCRAM_CONFIGCHKSUM:=V05-04-06
SCRAM_LOOKUPDB_WRITE:=/afs/.cern.ch/cms
SCRAM_PROJECTVERSION:=CMSSW_7_1_20
SCRAM_CONFIGDIR:=config
################ ALL SCRAM Stores #######################
ALL_PRODUCT_STORES:=
SCRAMSTORENAME_LOGS:=logs/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_LOGS)
SCRAMSTORENAME_LIB:=lib/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_LIB)
SCRAMSTORENAME_INCLUDE:=include
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_INCLUDE)
SCRAMSTORENAME_CFIPYTHON:=cfipython/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_CFIPYTHON)
SCRAMSTORENAME_BIGLIB:=biglib/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_BIGLIB)
SCRAMSTORENAME_OBJS:=objs/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_OBJS)
SCRAMSTORENAME_DOC:=doc
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_DOC)
SCRAMSTORENAME_TEST:=test/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_TEST)
SCRAMSTORENAME_PYTHON:=python
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_PYTHON)
SCRAMSTORENAME_BIN:=bin/slc6_amd64_gcc481
ALL_PRODUCT_STORES+=$(SCRAMSTORENAME_BIN)
