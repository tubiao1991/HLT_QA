#! /usr/bin/perl -w

use Time::localtime;
use File::stat;
use FileHandle;
use Cwd;

sub parseFileName;

# current dir
$dir = cwd;

print $dir,"\n";

# read in configurations

open (configFile, "< $dir/hltMonitor.config") or die "can't open config file \n";
while (<configFile>)
{
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
my $plotsPath       = $ConfigMap{"plotsPath"};
my $htmlFileName    = $ConfigMap{"htmlFileName"};

open (theLogFile, ">>".$logFile);
theLogFile->autoflush(1);

print "finished reading config file \n";
print theLogFile "finished reading config file \n";


%tmp = ();
my @totalRunsProcessed = <$runRootFile/*.root>;
#my @totalDaysProcessed = <./current/run17_hlt_day???_current_hist.root>;

for(@totalRunsProcessed)
{
    my ($day, $runnumber) = parseFileName($_);
    push (@{$tmp{$day}},$_);
}

foreach $day (keys %tmp)
{
    unless(-d '$plotsPath/$day' )
    {
	`mkdir -p $plotsPath/$day`;
    }

    my @hltdayroots = <$runRootFile/run_??$day*.root>;
    my @hltruns = ();
    for(@hltdayroots)
    {
	my ($day, $runnumber) = parseFileName($_);
	push (@hltruns,$runnumber);
    }
    
    my $num_hltDayRoots = scalar(@hltdayroots);
    my $dayFileName = "run17_hlt_day".$day."_current_hist";

    if($num_hltDayRoots >0)
    {
	print $day.": "."@hltruns \n";	  

	my @hltfiles =();
	my $need_to_update_dayfile = 0;

	my $dayFileTime = 0;
	if( -e "$dir/current/$dayFileName.root" )
	{
	    $dayFileTime = stat("$dir/current/$dayFileName.root")->mtime;
	}
	
	foreach(@hltruns)
	{   	      
	    push (@hltfiles,"$runRootFile/run_".$_.".root");
	    my $runfiletime = stat("$runRootFile/run_".$_.".root")->mtime;
	    
	    print "daytime : $dayFileTime     runtime : $runfiletime \n";
	    
	    if( $runfiletime > $dayFileTime ) 
	    { 
		$need_to_update_dayfile = 1;
	    }
	}

	if( $need_to_update_dayfile )
	{
	    print "Day file $dir/current/$dayFileName.pdf is outdated, will update \n";
 	    `tools/myhadd -f ./current/$dayFileName.root @hltfiles`;
		print "test_11";
	    `tools/mkQAPdf ./current/$dayFileName.root`;
		print "test_22";
	if( -e  "$dir/current/$dayFileName.pdf" )
	    {
		`mv -f  $dir\/current\/$dayFileName.pdf $plotsPath\/$day\/$dayFileName.pdf`;
		`cp  $dir\/current\/$dayFileName.root $plotsPath\/$day\/$dayFileName.root`;
	    }
	    else
	    {
		print "Could not find pdf file for day $day\n";
		print theLogFile "Could not find pdf file for day $day\n";
	    }
	}
	else
	{
	    print "Day file $dir/current/$dayFileName.pdf is up to day \n";
	}
    }
}

system("mkdir tmp_day");
system("mv current/run17_hlt_day036_current_hist.root tmp_day/");
system("mv current/run17_hlt_day037_current_hist.root tmp_day/");
system("mv current/run17_hlt_day038_current_hist.root tmp_day/");
system("mv current/run17_hlt_day039_current_hist.root tmp_day/");
system("mv current/run17_hlt_day055_current_hist.root tmp_day/");
system("mv current/run17_hlt_day150_current_hist.root tmp_day/");
system("mv current/run17_hlt_day151_current_hist.root tmp_day/");
system("mv current/run17_hlt_day153_current_hist.root tmp_day/");


my $need_to_update_allfile = 0;
my $allFileName = "run17_hlt_all_current_hist";
my $allFileTime = 0;
if( -e "$dir/current/$allFileName.root" )
{
    $allFileTime = stat("$dir/current/$allFileName.root")->mtime;
}
my @totalDaysProcessed = <./current/run17_hlt_day???_current_hist.root>;
foreach(@totalDaysProcessed)
{   	      
    my $dayRootFileTime = stat($_)->mtime;   
    print "$_ daytime : $dayRootFileTime     alltime : $allFileTime \n";
    if( $dayRootFileTime > $allFileTime ) 
    { 
	$need_to_update_allfile = 1;
    }
}

if( $need_to_update_allfile )
{
    print "All file $dir/current/$allFileName.pdf is outdated, will update \n";
    print "testMake11";
    `tools/myhadd -f ./current/$allFileName.root @totalDaysProcessed`;
    print "testMake22";
    `tools/mkQAPdf ./current/$allFileName.root`;
    print "testMake33";
    if( -e  "$dir/current/$allFileName.pdf" )
    {
	`mv -f  $dir\/current\/$allFileName.pdf $plotsPath\/$allFileName.pdf`;
        `cp  $dir\/current\/$allFileName.root $plotsPath\/$allFileName.root`;
    }
    else
    {
	print "Could not find  pdf file for all\n";
	print theLogFile  "Could not find pdf file for all\n";
    }
}
else
{
    print "All file $dir/current/$allFileName.pdf is up to day \n";
}

system("mv tmp_day/run17_hlt_day036_current_hist.root current/");
system("mv tmp_day/run17_hlt_day037_current_hist.root current/");
system("mv tmp_day/run17_hlt_day038_current_hist.root current/");
system("mv tmp_day/run17_hlt_day039_current_hist.root current/");
system("mv tmp_day/run17_hlt_day055_current_hist.root current/");
system("mv tmp_day/run17_hlt_day150_current_hist.root current/");
system("mv tmp_day/run17_hlt_day151_current_hist.root current/");
system("mv tmp_day/run17_hlt_day153_current_hist.root current/");

system("rm -rf tmp_day/");

#print theLogFile "finished updating $htmlFileName \n";

close theLogFile;

####################################
########## subroutines #############
####################################

sub parseFileName ()
{ # get the day, as well as filename without path
    my $filename=shift;
# my @temp1 = split (/gl3_/,$filename); # MN use sed instead of split
# my @temp1 = split (/hlt_/,$filename); # MN use sed instead of split
# my @temp2 = split (/\//,$filename); # MN use sed instead of split
    my $temp1 = `echo $filename | sed 's%^.*run_%%' | sed 's%\([0-9]*\).*%\1%'`;
    my $temp2 =	`echo $filename | sed 's%^.*/%%'`;
    $temp2 =~ s/\.daq//; # now no postfix left in filename.
    chomp $temp2;
    return (substr($temp1,2,3), substr($temp1,0,8)); # day, runnumber, filenameNoPath
# return (substr($temp1[1],2,3), substr($temp1[1],0,8), $temp2[-1]); # day, runnumber, filenameNoPath # MN use sed instead of split
}

exit;

