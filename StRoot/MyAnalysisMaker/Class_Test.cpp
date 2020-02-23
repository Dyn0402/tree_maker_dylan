//Dylan Edited 06/25/19

#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TBranch.h"
#include "TROOT.h"
#include "TString.h"

#include "Track.h"
#include "Event.h"


using namespace std;


void real_event_tree_test();


int Class_Test() {
	gROOT->ProcessLine(".L Track.h");
	gROOT->ProcessLine(".L Event.h");
	gROOT->ProcessLine(".L Track.cpp");
	gROOT->ProcessLine(".L Event.cpp");
	real_event_tree_test();
	cout << "donzo" << endl;
	return(0);
}


//int Class_Test(TString InputFileList, TString OutputDir, int energy) {
////	gROOT->ProcessLine(".L Event.cpp+");
////	gROOT->ProcessLine(".L Track.cpp+");
////	vec_tree_test();
//	cout << "InputFileList: " << InputFileList << endl;
//	cout << "OutputDir: " << OutputDir << endl;
//	cout << "Energy:" << energy << endl;
//	real_tree_test();
//	return(0);
//}



void real_event_tree_test() {
	// Write
	TFile *file = new TFile("real_tree_test.root", "RECREATE");

	if(!file) { cout << "Could not open file" << endl; return; }

	Event event;

	TTree *tree = new TTree("test_tree", "Test Tree");
	tree->Branch("event", &event);

	int ntracks = 0;

	TRandom3 *r = new TRandom3(0);

	for(int i=0; i<10000; i++) {
		event.set_event(r->Gaus(0,5), r->Gaus(0,4), r->Gaus(1, 6), (unsigned) r->Gaus(20,2), (unsigned) r->Gaus(40,3), (unsigned) r->Gaus(60,5), (unsigned) r->Gaus(80,7));
		vector<Track> tracks;
		for(int j=0; j<r->Gaus(15, 0.5); j++) {
			Track track;
			track.set_track(r->Gaus(10, 2), r->Gaus(15, 3), r->Gaus(3, 2), r->Gaus(0, 3), r->Gaus(0, 3), r->Gaus(2, 0.5), r->Gaus(0.5, 0.1), (short)r->Gaus(0, 0.5));
			tracks.push_back(track);
			ntracks++;
		}
		if(i == 100) {
			cout << endl << "Event 100: " << endl;
			for(auto t:tracks) { cout << t.get_pt() << endl; }
		}
		if(i == 101) {
			cout << endl << "Event 101: " << endl;
			for(auto t:tracks) { cout << t.get_pt() << endl; }
		}
		event.set_protons(tracks);
		tree->Fill();
	}

	file->Write();
	delete file;

	cout << ntracks << endl;


	// Read
	TFile *rfile = new TFile("real_tree_test.root", "READ");

	if(!rfile) { cout << "Could not open file" << endl; return; }

	TTree *rtree = (TTree*) rfile->Get("test_tree");

//	Event *revent;
//	vector<Track> *rtracks;

	Event *revent = new Event;

	auto bevent = rtree->GetBranch("event");

	bevent->SetAddress(&revent);

	auto nevent = rtree->GetEntries();
	cout << nevent << endl;

//	rtree->GetEvent(100);
//	cout << revent.get_vtx_x() << endl;
//	cout << rtracks.size() << endl;

	rtree->GetEvent(100);
	cout << endl << "Event 100" << endl;
	vector<Track> protons = revent->get_protons();
	cout << "vx: " << revent->get_vx() << endl;
	cout << "Num Protons: " << protons.size() << endl;
	for(unsigned i=0; i<protons.size(); i++) {
		cout << "Proton " << i << ": " << protons[i].get_pt() << endl;
	}

	cout << endl << endl;

	rtree->GetEvent(101);
	cout << endl << "Event 101" << endl;
	protons = revent->get_protons();
	cout << "vx: " << revent->get_vx() << endl;
	cout << "Num Protons: " << protons.size() << endl;
	for(unsigned i=0; i<protons.size(); i++) {
		cout << "Proton " << i << ": " << protons[i].get_pt() << endl;
	}

	delete rfile;
}
