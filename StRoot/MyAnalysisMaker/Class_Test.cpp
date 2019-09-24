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


void vec_tree_test();
void real_tree_test();


int Class_Test(TString InputFileList, TString OutputDir, int energy) {
//	gROOT->ProcessLine(".L DEvent.cpp+");
//	gROOT->ProcessLine(".L Track.cpp+");
//	vec_tree_test();
	cout << "InputFileList: " << InputFileList << endl;
	cout << "OutputDir: " << OutputDir << endl;
	cout << "Energy:" << energy << endl;
	real_tree_test();
	return(0);
}

void vec_tree_test() {
	TFile *file = new TFile("/star/u/dneff/Documents/vec_tree_test.root", "RECREATE");

	if(!file) { cout << "Could not open file" << endl; return; }

	vector<double> track_vec;

	TTree *tree = new TTree("vec_test_tree", "Test Tree");
	tree->Branch("test_vec", &track_vec);

	TRandom3 *rand = new TRandom3(0);

	for(int i=0; i<10000; i++) {
		track_vec.clear();
		for(int j=0; j<rand->Gaus(15, 0.5); j++) {
			track_vec.push_back(rand->Gaus(10, 0.2));
		}
		tree->Fill();
	}
	file->Write();
	delete file;
}


void real_tree_test() {
	// Write
	TFile *file = new TFile("/star/u/dneff/Documents/real_tree_test.root", "RECREATE");

	if(!file) { cout << "Could not open file" << endl; return; }

	DEvent event;
	vector<Track> tracks;

	TTree *tree = new TTree("test_tree", "Test Tree");
	tree->Branch("event", &event);
	tree->Branch("track_vec", &tracks);

	int ntracks = 0;

	TRandom3 *rand = new TRandom3(0);

	for(int i=0; i<10000; i++) {
		tracks.clear();
		event.set_event(rand->Gaus(0,5), rand->Gaus(0,4), rand->Gaus(1, 6), (unsigned) rand->Gaus(20,2), (unsigned) rand->Gaus(40,3), (unsigned) rand->Gaus(60,5), (unsigned) rand->Gaus(80,7));
		for(int j=0; j<rand->Gaus(15, 0.5); j++) {
			Track track;
			track.set_track(rand->Gaus(10, 2), rand->Gaus(15, 3), rand->Gaus(3, 2), rand->Gaus(0, 3), rand->Gaus(0, 3), rand->Gaus(2, 0.5), rand->Gaus(0.5, 0.1), (short)rand->Gaus(0, 0.5));
			tracks.push_back(track);
			ntracks++;
		}
		tree->Fill();
	}
	file->Write();
	delete file;

	cout << ntracks << endl;


	// Read
	TFile *rfile = new TFile("/star/u/dneff/Documents/real_tree_test.root", "READ");

	if(!rfile) { cout << "Could not open file" << endl; return; }

	TTree *rtree = (TTree*) rfile->Get("test_tree");

//	Event *revent;
//	vector<Track> *rtracks;

	DEvent *revent = new DEvent;
	vector<Track> *rtracks = new vector<Track>;

	TBranch* bevent = rtree->GetBranch("event");
	TBranch* btrack_vec = rtree->GetBranch("track_vec");

	bevent->SetAddress(&revent);
	btrack_vec->SetAddress(&rtracks);

	int nevent = rtree->GetEntries();
	cout << nevent << endl;

//	rtree->GetEvent(100);
//	cout << revent.get_vtx_x() << endl;
//	cout << rtracks.size() << endl;

	rtree->GetEvent(100);
	cout << revent->get_vtx_x() << endl;
	cout << rtracks->size() << endl;
	for(unsigned i=0; i<rtracks->size(); i++) {
		cout << (*rtracks)[i].get_pt() << endl;
	}

	cout << endl << endl;

	rtree->GetEvent(103);
	cout << revent->get_vtx_x() << endl;
	cout << rtracks->size() << endl;
	for(unsigned i=0; i<rtracks->size(); i++) {
		cout << (*rtracks)[i].get_pt() << endl;
	}

	delete rfile;
}