//Dylan Edited 06/25/19

#include <string>
#include <sstream>

#include "TROOT.h"
#include "TString.h"


int Load(TString InputFileList, TString OutputDir, int energy) {
//	gROOT->ProcessLine(".L ./StRoot/MyAnalysisMaker/Event.cpp+");
//	gROOT->ProcessLine(".L ./StRoot/MyAnalysisMaker/Track.cpp+");
//	gROOT->ProcessLine(".L readMuDst.C+");
	ostringstream energy_str;
	energy_str << energy;
	std::string line = ".x readMuDst.C(\"" + InputFileList + "\", \"" + OutputDir + "\", ";
	line += energy_str.str() + ")";
	cout << line << endl;
	gROOT->ProcessLine(line.data());
	return(0);
}
