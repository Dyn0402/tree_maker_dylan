#ifndef MyAnalysisMaker_def
#define MyAnalysisMaker_def

#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMaker.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TVector2.h"
#include "TVector3.h"
#include "Track.h"
#include "Event.h"

class StMuDstMaker  ;
class TFile         ;
class TH1I          ;
class TString       ;
class TVector2      ;
class TProfile      ;
class TProfile2D    ;
class TLorentzVector;
class TTree;
class TClonesArray;
class Event;




#define MaxNumberOfCentrality		9

class MyAnalysisMaker : public StMaker
{
public:
    MyAnalysisMaker(StMuDstMaker* maker) ;           //  Constructor
    
    virtual          ~MyAnalysisMaker( ) ;           //  Destructor
    
    Int_t Init    ( ) ;                              //  Initiliaze the analysis tools ... done once
    Int_t Make    ( ) ;                              //  The main analysis that is done on each event
    Int_t Finish  ( ) ;                              //  Finish the analysis, close files, and clean up.
    
    void SetEnergy(int energy_in);
    void SetRefNum(int ref_num_in);

    Bool_t IsBadEvent(StMuEvent *muEvent);
    Bool_t IsBadTrack(StMuTrack * track);
    void SetOutputFileName(TString name) {OutputFileName = name;}  // Make name available to member functions
    
    
    
private:
    StMuDstMaker      *mMuDstMaker;                   //  Make MuDst pointer available to member functions
    TFile*        histogram_output;                   //  Histograms outputfile pointer


    Event* event;
    TTree* tree;
    TH1I* event_cut_hist;
	TH1I* track_cut_hist;


	UInt_t        mEventsRead;                   //  Number of Events read
    UInt_t        mEventsProcessed;                   //  Number of Events read and processed
    TString         OutputFileName;                   //  Name of the histogram output file
    
    Double_t            VertexZPos;
    Float_t               VpdVzPos;
    Int_t                  trigger;
    Int_t                cent_flag;
    Int_t                runnumber;
    Int_t                 refmultn;
    
    int						energy;
    int					   ref_num;

    char name[60];
    
protected:
    
    
    
    ClassDef(MyAnalysisMaker,1)                       //Macro for CINT compatability
    
};

#endif















