#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T15:07:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Steghide-GUI
TEMPLATE = app

DEFINES += "USE_LIBJPEG=1"\
           "USE_LIBMCRYPT=1"\
           "USE_ZLIB=1"

QMAKE_CXXFLAGS += -fpermissive
LIBS += -lz\
        -lmhash\
        -lmcrypt\
        -ljpeg

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    FilesToAddListModel.cpp \
    FilesToAdd.cpp \
    steghide-src/Arg.cc \
    steghide-src/Arguments.cc \
    steghide-src/AssertionFailed.cc \
    steghide-src/AuFile.cc \
    steghide-src/AuSampleValues.cc \
    steghide-src/BFSAPHeuristic.cc \
    steghide-src/BinaryIO.cc \
    steghide-src/BitString.cc \
    steghide-src/BmpFile.cc \
    steghide-src/BmpPaletteSampleValue.cc \
    steghide-src/BmpRGBSampleValue.cc \
    steghide-src/BmpSampleValue.cc \
    steghide-src/CvrStgFile.cc \
    steghide-src/DFSAPHeuristic.cc \
    steghide-src/DMDConstructionHeuristic.cc \
    steghide-src/Edge.cc \
    steghide-src/EdgeIterator.cc \
    steghide-src/EmbData.cc \
    steghide-src/Embedder.cc \
    steghide-src/EncryptionAlgorithm.cc \
    steghide-src/EncryptionMode.cc \
    steghide-src/error.cc \
    steghide-src/Extractor.cc \
    steghide-src/Graph.cc \
    steghide-src/JpegFile.cc \
    steghide-src/JpegSampleValue.cc \
    steghide-src/Matching.cc \
    steghide-src/MatchingAlgorithm.cc \
    steghide-src/MCryptPP.cc \
    steghide-src/MHashKeyGen.cc \
    steghide-src/MHashPP.cc \
    steghide-src/msg.cc \
    steghide-src/ProgressOutput.cc \
    steghide-src/PseudoRandomSource.cc \
    steghide-src/RandomSource.cc \
    steghide-src/RGBTriple.cc \
    steghide-src/SampleValue.cc \
    steghide-src/SampleValueAdjacencyList.cc \
    steghide-src/Selector.cc \
    steghide-src/Session.cc \
    steghide-src/SMDConstructionHeuristic.cc \
    steghide-src/SteghideError.cc \
    steghide-src/Terminal.cc \
    steghide-src/Utils.cc \
    steghide-src/Vertex.cc \
    steghide-src/WavChunk.cc \
    steghide-src/WavChunkHeader.cc \
    steghide-src/WavChunkUnused.cc \
    steghide-src/WavFile.cc \
    steghide-src/WavFormatChunk.cc \
    steghide-src/WavPCMSampleValue.cc \
    steghide-src/WKSConstructionHeuristic.cc

HEADERS  += mainwindow.h \
    dialog.h \
    FilesToAddListModel.h \
    FilesToAdd.h \
    steghide-src/Arg.h \
    steghide-src/Arguments.h \
    steghide-src/AssertionFailed.h \
    steghide-src/AuData.h \
    steghide-src/AudioData.h \
    steghide-src/AudioSampleValue.h \
    steghide-src/AuFile.h \
    steghide-src/AuSampleValues.h \
    steghide-src/AUtils.h \
    steghide-src/BFSAPHeuristic.h \
    steghide-src/BinaryIO.h \
    steghide-src/BitString.h \
    steghide-src/BmpFile.h \
    steghide-src/BmpPaletteSampleValue.h \
    steghide-src/BmpRGBSampleValue.h \
    steghide-src/BmpSampleValue.h \
    steghide-src/ColorPalette.h \
    steghide-src/common.h \
    steghide-src/CvrStgFile.h \
    steghide-src/CvrStgObject.h \
    steghide-src/DFSAPHeuristic.h \
    steghide-src/DMDConstructionHeuristic.h \
    steghide-src/Edge.h \
    steghide-src/EdgeIterator.h \
    steghide-src/EmbData.h \
    steghide-src/Embedder.h \
    steghide-src/EncryptionAlgorithm.h \
    steghide-src/EncryptionMode.h \
    steghide-src/error.h \
    steghide-src/Extractor.h \
    steghide-src/gettext.h \
    steghide-src/Globals.h \
    steghide-src/Graph.h \
    steghide-src/JpegFile.h \
    steghide-src/JpegSampleValue.h \
    steghide-src/Matching.h \
    steghide-src/MatchingAlgorithm.h \
    steghide-src/MCryptPP.h \
    steghide-src/MHashKeyGen.h \
    steghide-src/MHashPP.h \
    steghide-src/msg.h \
    steghide-src/ProgressOutput.h \
    steghide-src/PseudoRandomSource.h \
    steghide-src/RandomSource.h \
    steghide-src/RGBTriple.h \
    steghide-src/SampleOccurence.h \
    steghide-src/SampleValue.h \
    steghide-src/SampleValueAdjacencyList.h \
    steghide-src/Selector.h \
    steghide-src/Session.h \
    steghide-src/SMDConstructionHeuristic.h \
    steghide-src/SteghideError.h \
    steghide-src/Terminal.h \
    steghide-src/Utils.h \
    steghide-src/Vertex.h \
    steghide-src/WavChunk.h \
    steghide-src/WavChunkHeader.h \
    steghide-src/WavChunkUnused.h \
    steghide-src/WavFile.h \
    steghide-src/WavFormatChunk.h \
    steghide-src/WavPCMSampleValue.h \
    steghide-src/WKSConstructionHeuristic.h \
    steghide-src/wrapper_hash_map.h \
    steghide-src/wrapper_hash_set.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES +=

RESOURCES += \
    imageresources.qrc
