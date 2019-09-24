//Dylan Edited 06/25/19

#include <string>

#include "TROOT.h"
#include "TString.h"

using namespace std;


int Load_Macro(TString InputFileList, TString OutputDir, int energy) {
	gROOT->ProcessLine(".L DEvent.cpp+");
	gROOT->ProcessLine(".L Track.cpp+");
	gROOT->ProcessLine(".L Class_Test.cpp+");
	string line = ".x Class_Test(\"" + InputFileList + "\", \"" + OutputDir + "\", " + to_string(energy) + ")";
	gROOT->ProcessLine(line.data());
	return(0);
}
