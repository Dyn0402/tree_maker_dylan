#! /opt/star/bin/perl -w

use File::Basename;
use Getopt::Std;
use Cwd 'abs_path';     # aka realpath()
my $resubmit = "resub.sh";
my $pre = "sched";
my $suf = "auau\_";

@jobDirs = (
"//gpfs01/star/pwg/dneff/scratch/trees/script/62GeV/"
);

@outputDirs = (
"//gpfs01/star/pwg/dneff/scratch/trees/output/62GeV/"
);


#foreach $eachCent (@flowCents) {
    
    $totalJobs=0.;
    $finishedJobs=0.;
    
    foreach $jobDir (@jobDirs) {
        
        foreach $outputDir (@outputDirs) {
            
            if (-e "$outputDir/$resubmit") { print `rm $outputDir/$resubmit \n`;}
            
            foreach (glob ("$jobDir/sched*.csh") ){
                
                my $eachScript = $_;
                chomp $eachScript;
                @fields = split(/\//,$eachScript) ;
                $eachScriptNoPath= $fields[$#fields];
                ($eachJOBID = $eachScriptNoPath) =~ s/\.csh// ;
                chomp $eachJOBID;
		$eachSCHEDID = $eachJOBID;
		$eachJOBID =~ s/$pre/$suf/g;
                
                if ( (!(-s "$outputDir/$eachJOBID.root")) ) {
                    
                    print "$eachSCHEDID.root \n";
                    
                    if (-e "$jobDir/$eachJOBID.run.log") { print `rm $jobDir/$eachJOBID.run.log \n`; }
                    
                    $submitCommand = "cd $jobDir; condor_submit $eachSCHEDID.condor";
                    
                    #open(macroFile,">>$outputDir/$resubmit");
		    open(macroFile, ">>$resubmit");
                    print macroFile "$submitCommand \n";
                }
            }
            
            my @tempScripts = glob( "$jobDir/sched*.csh" );
            my @tempFinished = glob( "$outputDir/*.root" ) ;
            
            $totalJobs +=scalar(@tempScripts);
            $finishedJobs +=scalar(@tempFinished);
        }
        
        my $perCentFinished = 0.;
        if ($totalJobs != 0) {$perCentFinished = ($finishedJobs/$totalJobs)*100.;}
        print "for $jobDir, finished $finishedJobs jobs out of $totalJobs, ".$perCentFinished."% completed \n";
    }
#}

exit;

