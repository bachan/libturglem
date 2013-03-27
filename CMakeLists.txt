CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (libturglem)

SET (LIBTURGLEM_VERSION 0.2.30)
SET (LIBTURGLEM_RPM_RELEASE 30)

SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -pipe -O3 -fomit-frame-pointer -funroll-loops -DNDEBUG -Wall -Werror")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -Wno-deprecated")

SET (FIND_LIBRARY_USE_LIB64_PATHS TRUE)
SET (CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_SUFFIX})
SET (CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_STATIC_LIBRARY_PREFIX} ${CMAKE_SHARED_LIBRARY_PREFIX})

SET (LIBDIR lib)
IF (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    SET (LIBDIR lib64)
ENDIF (${CMAKE_SIZEOF_VOID_P} EQUAL 8)

ADD_DEFINITIONS (-D__STDC_FORMAT_MACROS) # for PRIdPTR support

FIND_PATH    (ICODA coda/coda.h)
FIND_LIBRARY (LCODA coda)
FIND_PATH    (IMAFSA MAFSA/automaton.h)
FIND_LIBRARY (LMAFSA MAFSA)
FIND_PATH    (IEXPAT expat.h)
FIND_LIBRARY (LEXPAT expat)

CONFIGURE_FILE (include/config.h.in ${CMAKE_BINARY_DIR}/auto/config.h)

INCLUDE_DIRECTORIES (include ${CMAKE_BINARY_DIR})
INCLUDE_DIRECTORIES (${IMAFSA} ${IEXPAT})

AUX_SOURCE_DIRECTORY (src/turglem         SRC_TURG)
AUX_SOURCE_DIRECTORY (src/turglem/default SRC_TURGDEF)
AUX_SOURCE_DIRECTORY (src/turglem/english SRC_TURGENG)
AUX_SOURCE_DIRECTORY (src/turglem/russian SRC_TURGRUS)

ADD_LIBRARY (turglem         SHARED ${SRC_TURG})
ADD_LIBRARY (turglem-default SHARED ${SRC_TURGDEF})
ADD_LIBRARY (turglem-english SHARED ${SRC_TURGENG})
ADD_LIBRARY (turglem-russian SHARED ${SRC_TURGRUS})

ADD_EXECUTABLE (lemc_english src/utils/english/lemc.cpp)
ADD_EXECUTABLE (lemq_english src/utils/english/lemq.c)
ADD_EXECUTABLE (lemc_russian src/utils/russian/lemc.cpp)
ADD_EXECUTABLE (lemq_russian src/utils/russian/lemq.c)
ADD_EXECUTABLE (auto_utility src/utils/auto.c)

TARGET_LINK_LIBRARIES (lemc_english turglem-english coda ${LEXPAT})
TARGET_LINK_LIBRARIES (lemq_english turglem-english turglem ${LMAFSA})
TARGET_LINK_LIBRARIES (lemc_russian turglem-russian coda ${LEXPAT})
TARGET_LINK_LIBRARIES (lemq_russian turglem-russian turglem ${LMAFSA})
TARGET_LINK_LIBRARIES (auto_utility turglem-default turglem-english turglem-russian ${LMAFSA})

#SET (MC_OUAENG ${MC_OUAENG} ${CMAKE_BINARY_DIR}/dict_english.auto)
#SET (MC_OUAENG ${MC_OUAENG} ${CMAKE_BINARY_DIR}/paradigms_english.bin)
#SET (MC_OUAENG ${MC_OUAENG} ${CMAKE_BINARY_DIR}/prediction_english.auto)
#SET (MC_INAENG ${MC_INAENG} ${CMAKE_SOURCE_DIR}/share/turglem/english/paradigms.xml)
#SET (MC_INAENG ${MC_INAENG} ${CMAKE_SOURCE_DIR}/share/turglem/english/lemmas.xml)
#SET (MC_OUARUS ${MC_OUARUS} ${CMAKE_BINARY_DIR}/dict_russian.auto)
#SET (MC_OUARUS ${MC_OUARUS} ${CMAKE_BINARY_DIR}/paradigms_russian.bin)
#SET (MC_OUARUS ${MC_OUARUS} ${CMAKE_BINARY_DIR}/prediction_russian.auto)
#SET (MC_INARUS ${MC_INARUS} ${CMAKE_SOURCE_DIR}/share/turglem/russian/paradigms.xml)
#SET (MC_INARUS ${MC_INARUS} ${CMAKE_SOURCE_DIR}/share/turglem/russian/lemmas.xml)

LIST (APPEND MC_OUAENG ${CMAKE_BINARY_DIR}/dict_english.auto)
LIST (APPEND MC_OUAENG ${CMAKE_BINARY_DIR}/paradigms_english.bin)
LIST (APPEND MC_OUAENG ${CMAKE_BINARY_DIR}/prediction_english.auto)
LIST (APPEND MC_INAENG ${CMAKE_SOURCE_DIR}/share/turglem/english/paradigms.xml)
LIST (APPEND MC_INAENG ${CMAKE_SOURCE_DIR}/share/turglem/english/lemmas.xml)
LIST (APPEND MC_OUARUS ${CMAKE_BINARY_DIR}/dict_russian.auto)
LIST (APPEND MC_OUARUS ${CMAKE_BINARY_DIR}/paradigms_russian.bin)
LIST (APPEND MC_OUARUS ${CMAKE_BINARY_DIR}/prediction_russian.auto)
LIST (APPEND MC_INARUS ${CMAKE_SOURCE_DIR}/share/turglem/russian/paradigms.xml)
LIST (APPEND MC_INARUS ${CMAKE_SOURCE_DIR}/share/turglem/russian/lemmas.xml)

ADD_CUSTOM_COMMAND (TARGET lemc_english POST_BUILD COMMAND echo "Compiling english dictionaries...")
ADD_CUSTOM_COMMAND (TARGET lemc_english POST_BUILD COMMAND ${CMAKE_BINARY_DIR}/lemc_english ${MC_INAENG} ${MC_OUAENG})
ADD_CUSTOM_COMMAND (TARGET lemc_russian POST_BUILD COMMAND echo "Compiling russian dictionaries...")
ADD_CUSTOM_COMMAND (TARGET lemc_russian POST_BUILD COMMAND ${CMAKE_BINARY_DIR}/lemc_russian ${MC_INARUS} ${MC_OUARUS})

INSTALL (TARGETS turglem         DESTINATION ${LIBDIR})
INSTALL (TARGETS turglem-default DESTINATION ${LIBDIR})
INSTALL (TARGETS turglem-english DESTINATION ${LIBDIR})
INSTALL (TARGETS turglem-russian DESTINATION ${LIBDIR})

INSTALL (TARGETS lemc_english DESTINATION bin)
INSTALL (TARGETS lemq_english DESTINATION bin)
INSTALL (TARGETS lemc_russian DESTINATION bin)
INSTALL (TARGETS lemq_russian DESTINATION bin)
INSTALL (TARGETS auto_utility DESTINATION bin)

INSTALL (DIRECTORY include/turglem DESTINATION include PATTERN ".*" EXCLUDE)
INSTALL (DIRECTORY share/turglem   DESTINATION share   PATTERN ".*" EXCLUDE)

INSTALL (FILES ${CMAKE_BINARY_DIR}/dict_english.auto       DESTINATION share/turglem/english)
INSTALL (FILES ${CMAKE_BINARY_DIR}/paradigms_english.bin   DESTINATION share/turglem/english)
INSTALL (FILES ${CMAKE_BINARY_DIR}/prediction_english.auto DESTINATION share/turglem/english)
INSTALL (FILES ${CMAKE_BINARY_DIR}/dict_russian.auto       DESTINATION share/turglem/russian)
INSTALL (FILES ${CMAKE_BINARY_DIR}/paradigms_russian.bin   DESTINATION share/turglem/russian)
INSTALL (FILES ${CMAKE_BINARY_DIR}/prediction_russian.auto DESTINATION share/turglem/russian)

