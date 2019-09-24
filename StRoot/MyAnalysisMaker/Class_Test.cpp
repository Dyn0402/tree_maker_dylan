//Dylan Edited 06/25/19

#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"


using namespace std;


void vec_tree_test();


int Class_Test() {
	vec_tree_test();
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
