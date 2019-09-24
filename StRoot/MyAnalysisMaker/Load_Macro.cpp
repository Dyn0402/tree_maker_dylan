//Dylan Edited 06/25/19

#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TBranch.h"
#include "TROOT.h"
#include "TSystem.h"

#include "Track.h"
#include "DEvent.h"


using namespace std;

int Class_Test();


int Load_Macro() {
	gROOT->ProcessLine(".L DEvent.cpp+");
	gROOT->ProcessLine(".L Track.cpp+");
	gROOT->ProcessLine(".L Class_Test.cpp");
	gSystem->Load("DEvent_cpp.so");
	gSystem->Load("Track_cpp.so");
//	vec_tree_test();
	Class_Test();
	return(0);
}
