#! /usr/bin/perl -w

use File::Copy;
use Time::localtime;
use File::stat;
use FileHandle;
use Cwd;

# $SIG{'USR1'} = 'wakeup';
$SIG{'USR1'} = \&wakeup;

$mypid=$$;
$lock="$$.runmonitor";
$lockfile="$lock.lock";

print "lockfile :".$lockfile."\n";
open (theLockFile, ">>".$lockfile);
theLockFile->autoflush(1);

sub wakeup;
sub parseFileName;

# current dir
$dir = cwd;

print "ARGV $#ARGV \n";
# read inputs
if ( $#ARGV !=0 ) {
	print " Usage : hltRunMonitor.pl configfile \n";
	exit;
}

my $configfile = shift if defined @ARGV;

# read in configurations
copy("$dir/$configfile","$mypid.config.lock") or die "copy of config file failed: $!";
open (configFile, "< $dir/$configfile") or die "can't open config file \n";

while (<configFile>){
	chomp;                          # no newline
		s/#.*//;                        # no comments
		s/^\s+//;                       # no leading white
		s/\s+$//;                       # no trailing white
		next unless length;             # anything left?
		my ($var, $value) = split (/\s*:\s*/, $_,2);
	$ConfigMap{$var} = $value;
}
close(configFile);

my $logFile         = $ConfigMap{"logFile"};
my $runRootFile     = $ConfigMap{"runRootFile"};
my $sleepHours      = $ConfigMap{"sleepHours"};

# run loop
#for (my $i = 0; $i < 480; $i++) # test loop
for (;;) # infinite loop
{
    open (theLogFile, ">>$logFile");
    theLogFile->autoflush(1);
    print theLogFile "########### ".ctime()." : starting the procedure. \n";
    close theLogfile;
#	system("cp -r ./rootfiles ./tmp");
    system("mkdir tmp");
    system("scp -r l4evp.starp.bnl.gov:/a/l4jevp/rootfiles/run_18\* ./tmp/rootfiles/");
    system("scp -r l4evp.starp.bnl.gov:/a/l4jevp/client/HLT_paras/18\*.dat ./HLT_paras/");
    system("touch ./tmp/all.dat");
    system("find ./HLT_paras/*.dat >> ./tmp/all.dat");
    system("sort -r ./tmp/all.dat -o ./tmp/all.dat");
    my @tmpAllRootFiles = <./tmp/rootfiles/*.root>; 
    for(@tmpAllRootFiles) {
	my ($day, $runnumber) = parseFileName($_);
#	print $runnumber,"\n";
	my $runFileName = "$runRootFile/run_".$runnumber.".root";
	unless (-e "$runFileName") {
	    unless( $runnumber < 18000000){
		print $runnumber,"\n";
		copy ($_, $runFileName) or die "File cannot be copied.";}
	}
    }
    my @AllRootFiles =<./rootfiles/*.root>;
    for(@AllRootFiles){
	my($day, $runnumber) = parseFileName($_);
	my $runFileName = "$runRootFile/run_".$runnumber.".root";
	unless( $runnumber > 18000000){
	unlink $runFileName;
	}
    }
    
    system("perl ./hltMakeDayHists.pl");    
    system("perl ./hltMakeRunHist.pl");
    system("perl ./hltMakeWebpage.pl");
    
    #if (-e "./tmp") {`rm -rf ./tmp`;}
    
    open (theLogFile, ">>$logFile");
    theLogFile->autoflush(1);
    print theLogFile "########### ".ctime()." : finished updating the webpage. Now I am going to sleep ... \n";
    close theLogfile;
    
    sleep $sleepHours*3600;
#sleep $sleepHours*10;
}

# wake up signal handler
sub wakeup {
    open (theLogFile, ">>$logFile");
    theLogFile->autoflush(1);
    print theLogFile "########### ".ctime()." : received kill -USR1, waking up ... \n";
    close theLogFile;
    exit0;
}

sub parseFileName ()
{ # get the day, as well as filename without path
    my $filename=shift;
    my $temp1 = `echo $filename | sed 's%^.*run_%%' | sed 's%\([0-9]*\).*%\1%'`;
    my $temp2 =	`echo $filename | sed 's%^.*/%%'`;
    $temp2 =~ s/\.daq//; # now no postfix left in filename.
    chomp $temp2;
    return (substr($temp1,2,3), substr($temp1,0,8)); # day, runnumber, filenameNoPath
}

exit;
