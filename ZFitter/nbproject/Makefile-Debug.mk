#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ZFitter.o

# Test Directory
TESTDIR=build/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-MacOSX/libzfitter.a

dist/Debug/GNU-MacOSX/libzfitter.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-MacOSX
	${RM} dist/Debug/GNU-MacOSX/libzfitter.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libzfitter.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/GNU-MacOSX/libzfitter.a

${OBJECTDIR}/src/ZFitter.o: src/ZFitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../StandardModel/src -I../gslpp/src -I../Utils/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ZFitter.o src/ZFitter.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}

${TESTDIR}/tests/ZFitterTest.o: tests/ZFitterTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I../StandardModel/src -I../gslpp/src -I../Utils/src -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ZFitterTest.o tests/ZFitterTest.cpp


${TESTDIR}/tests/ZFitterTest-2.o: tests/ZFitterTest-2.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I../StandardModel/src -I../gslpp/src -I../Utils/src -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ZFitterTest-2.o tests/ZFitterTest-2.cpp


${OBJECTDIR}/src/ZFitter_nomain.o: ${OBJECTDIR}/src/ZFitter.o src/ZFitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ZFitter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../StandardModel/src -I../gslpp/src -I../Utils/src -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ZFitter_nomain.o src/ZFitter.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ZFitter.o ${OBJECTDIR}/src/ZFitter_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-MacOSX/libzfitter.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc