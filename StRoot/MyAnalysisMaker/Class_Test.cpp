//Dylan Edited 06/25/19

#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TBranch.h"
#include "TROOT.h"

#include "Track.h"
#include "DEvent.h"


using namespace std;

int Class_Test();


int Load_Macro() {
	gROOT->ProcessLine(".L DEvent.cpp+");
	gROOT->ProcessLine(".L Track.cpp+");
//	vec_tree_test();
	Class_Test();
	return(0);
}
