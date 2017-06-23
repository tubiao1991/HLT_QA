#! /usr/bin/perl -w
use File::Copy;
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



my @tmpAllRootFiles = <./tmp/rootfiles/*.root>;
					for(@tmpAllRootFiles) {
					    my ($day, $runnumber) = parseFileName($_);
					    print $runnumber,"\n";
					    my $runFileName = "$dir/current_run/run_".$runnumber.".root";
					    unless (-e "$runFileName") {
						unless ( $runnumber < 18000000) {
						    print $runnumber,"\n";
						    copy ($_, $runFileName) or die "File cannot be copied.";}
					    }
                                        }
					%tmp_run = ();                        
					my @totalRunsProcessed = <current_run/*.root>;                                                     

					for(@totalRunsProcessed)
					{
					my ($day, $runnumber) = parseFileName($_);
					push (@{$tmp_run{$runnumber}},$_);                                                              
					}    

					foreach $runnumber (keys %tmp_run)
					{

					my @hltrunroots = <$runRootFile/run_$runnumber.root>;


					my $runFileName = "run_".$runnumber."";


					my @hltfiles =();
					my $need_to_update_runfile = 1;

					my $runFileTime = 0;
					if( -e "$dir/current_run/$runFileName.pdf" )
					{
					$need_to_update_runfile = 0;
					}

					if( $need_to_update_runfile )
					{
					print "run  $dir/current_run/$runnumber.pdf is outdated, will update \n";
					`tools/mkQAPdf $dir/current_run/$runFileName.root`;
                                        `cp   $dir\/current_run\/run_$runnumber.pdf \/ceph\/WWW\/HLT2017\/runbyrunplots\/run_$runnumber.pdf`;
					`cp   $dir\/current_run\/run_$runnumber.root \/ceph\/WWW\/HLT2017\/runbyrunplots\/run_$runnumber.root`;
					}
					}






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

