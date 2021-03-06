#!/bin/bash

g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtWidgets -I/opt/Qt/5.4/gcc_64/include/QtGui -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o main.o ../WellIndexBenchmark/main.cpp
g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtWidgets -I/opt/Qt/5.4/gcc_64/include/QtGui -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o file_handling.o ../WellIndexBenchmark/src/file_handling.cpp
g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtWidgets -I/opt/Qt/5.4/gcc_64/include/QtGui -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o well_data_pcg.o ../WellIndexBenchmark/src/well_data_pcg.cpp
g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtWidgets -I/opt/Qt/5.4/gcc_64/include/QtGui -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o test_wells.o ../WellIndexBenchmark/src/test_wells.cpp
g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtWidgets -I/opt/Qt/5.4/gcc_64/include/QtGui -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o well_rms.o ../WellIndexBenchmark/src/well_rms.cpp
g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../WellIndexBenchmark -I. -I/opt/Qt/5.4/gcc_64/include -I/opt/Qt/5.4/gcc_64/include/QtWidgets -I/opt/Qt/5.4/gcc_64/include/QtGui -I/opt/Qt/5.4/gcc_64/include/QtCore -I. -I/opt/Qt/5.4/gcc_64/mkspecs/linux-g++ -o well_pcg.o ../WellIndexBenchmark/src/well_pcg.cpp
g++ -Wl,-rpath,/opt/Qt/5.4/gcc_64 -Wl,-rpath,/opt/Qt/5.4/gcc_64/lib -o \
wellindexbenchmark main.o file_handling.o well_data_pcg.o test_wells.o well_rms.o well_pcg.o   \
-L../../WellIndexBenchmark/build-FieldOpt-old-Desktop_Qt_5_4_1_GCC_64bit-Debug/WellIndexCalculator -lWellIndexCalculator \
-L../../WellIndexBenchmark/build-FieldOpt-old-Desktop_Qt_5_4_1_GCC_64bit-Debug/ERTWrapper -lertwrapper \
-L../../WellIndexBenchmark/build-FieldOpt-old-Desktop_Qt_5_4_1_GCC_64bit-Debug/Model -lmodel \
-L../../WellIndexBenchmark/build-FieldOpt-old-Desktop_Qt_5_4_1_GCC_64bit-Debug/Utilities \
-lutilities -larmadillo -lrpoly_plus_plus -L/opt/Qt/5.4/gcc_64/lib -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread

