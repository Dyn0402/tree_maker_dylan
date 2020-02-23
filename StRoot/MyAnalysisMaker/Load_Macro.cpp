//Dylan Edited 06/25/19

#include <string>
#include <sstream>

#include "TROOT.h"
#include "TString.h"

int Class_Test();


int Load_Macro() {
//	gSystem->Load("Track.h");
//	gSystem->Load("Event.h");
//	gSystem->Load("Track.cpp");
//	gSystem->Load("Event.cpp");
//	gSystem->Load("Class_Test.cpp");

	gROOT->ProcessLine(".L Track.h");
	gROOT->ProcessLine(".L Event.h");
	gROOT->ProcessLine(".L Track.cpp");
	gROOT->ProcessLine(".L Event.cpp");
	gROOT->ProcessLine(".L Class_Test.cpp");

	Class_Test();

	cout << "donzo" << endl;
	return(0);
}


//int Load_Macro(TString InputFileList, TString OutputDir, int energy) {
//	gROOT->ProcessLine(".L Event.cpp+");
//	gROOT->ProcessLine(".L Track.cpp+");
//	gROOT->ProcessLine(".L Class_Test.cpp+");
//	ostringstream energy_str;
//	energy_str << energy;
//	std::string line = "Class_Test(\"" + InputFileList + "\", \"" + OutputDir + "\", ";
//	line += energy_str.str() + ")";
//	cout << line << endl;
//	gROOT->ProcessLine(line.data());
//	return(0);
//}
