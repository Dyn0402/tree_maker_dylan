//Dylan Edited 06/25/19

#include "TROOT.h"


int Load_Macro() {
	gROOT->ProcessLine(".L DEvent.cpp+");
	gROOT->ProcessLine(".L Track.cpp+");
	gROOT->ProcessLine(".L Class_Test.cpp+");
	gROOT->ProcessLine("Class_Test()");
	return(0);
}
