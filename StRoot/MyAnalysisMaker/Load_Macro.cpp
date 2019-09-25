//Dylan Edited 06/25/19

#include <string>
#include <sstream>

#include "TROOT.h"
#include "TString.h"


int Load_Macro(TString InputFileList, TString OutputDir, int energy) {
	gROOT->ProcessLine(".L DEvent.cpp+");
	gROOT->ProcessLine(".L Track.cpp+");
	gROOT->ProcessLine(".L Class_Test.cpp+");
	ostringstream energy_str;
	energy_str << energy;
	std::string line = ".x Class_Test(\"" + InputFileList + "\", \"" + OutputDir + "\", ";
	line += energy_str.str() + ")";
	gROOT->ProcessLine(line.data());
	return(0);
}
