#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <stdlib.h>
#include "TSystem.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "TFile.h"
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include "TNtuple.h"
#include "TH3D.h"
#include "TH1I.h"
#include "TH1D.h"
#include "TH2F.h"
#include "string"
#include "TObjArray.h"
#include "TObjString.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TPDF.h"
#include "TKey.h"
#include "TAttMarker.h"


using namespace std;

int nP = 11900 ;
double pMin = 0.1 ;
double pMax = 12. ; 
double pBin = (pMax - pMin)/nP ;

double dedxElec[11901] ; double dedxPion[11901] ;
double dedxKaon[11901] ; double dedxPron[11901] ;
double dedxDeu[11901] ; double dedxTri[11901] ;
double dedxHe3[11901] ; double dedxHe4[11901] ;
char Currentdir[256];
char particle[10][256];


int mkQAPdfFile(char* inputFile) ;
void inputdEdxThLine() ;
double getDedxFunElecP(double *x, double *par);
double getDedxFunElecN(double *x, double *par);
double getDedxFunPionP(double *x, double *par);
double getDedxFunPionN(double *x, double *par);
double getDedxFunKaonP(double *x, double *par);
double getDedxFunKaonN(double *x, double *par);
double getDedxFunPronP(double *x, double *par);
double getDedxFunPronN(double *x, double *par);
double getDedxFunDeuP(double *x, double *par);
double getDedxFunDeuN(double *x, double *par);
double getDedxFunTriP(double *x, double *par);
double getDedxFunTriN(double *x, double *par);
double getDedxFunHe3P(double *x, double *par);
double getDedxFunHe3N(double *x, double *par);
double getDedxFunHe4P(double *x, double *par);
double getDedxFunHe4N(double *x, double *par);


int main(int argc, char *argv[])
{
	//gStyle->SetOptStat(00000);
	gStyle->SetOptFit(111);
	gStyle->SetOptDate(0);

	gStyle->SetCanvasColor(10);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFrameFillColor(10);
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(10);
	gStyle->SetStatColor(10);
	gStyle->SetLabelSize(.05,"X");
	gStyle->SetLabelSize(.05,"Y");
	gStyle->SetLabelColor(1,"X");
	gStyle->SetLabelColor(1,"Y");
	gStyle->SetTitleTextColor(1);

	getcwd(Currentdir,256);
	char tmp[256];
	getcwd(tmp,256);
	strcpy(Currentdir,tmp);

	sprintf(particle[0],"%s/dedx/dedx_mean_Pion",Currentdir);
	sprintf(particle[1],"%s/dedx/dedx_mean_Kaon",Currentdir);
	sprintf(particle[2],"%s/dedx/dedx_mean_Proton",Currentdir); 
	sprintf(particle[3],"%s/dedx/dedx_mean_Electron",Currentdir);
	sprintf(particle[4],"%s/dedx/dedx_mean_Deuteron",Currentdir);
	sprintf(particle[5],"%s/dedx/dedx_mean_He3",Currentdir);
	sprintf(particle[6],"%s/dedx/dedx_mean_Triton",Currentdir);
	sprintf(particle[7],"%s/dedx/dedx_mean_He4",Currentdir);

	char *inputFile = argv[argc-1];
	printf("using file : %s \n",inputFile);
	printf("producing hlt QA plots PDF... \n");

	inputdEdxThLine();
	mkQAPdfFile(inputFile) ;

	printf("done ! \n");

}

int mkQAPdfFile(char* inputFile)
{
	TF1 *FunElecP = new TF1("FunElecP",getDedxFunElecP,0.1,5,0);
	TF1 *FunElecN = new TF1("FunElecN",getDedxFunElecN,-5,-0.1,0);
	TF1 *FunPionP = new TF1("FunPionP",getDedxFunPionP,0.1,5,0);
	TF1 *FunPionN = new TF1("FunPionN",getDedxFunPionN,-5,-0.1,0);
	TF1 *FunKaonP = new TF1("FunKaonP",getDedxFunKaonP,0.1,5,0);
	TF1 *FunKaonN = new TF1("FunKaonN",getDedxFunKaonN,-5,-0.1,0);
	TF1 *FunPronP = new TF1("FunPronP",getDedxFunPronP,0.1,5,0);
	TF1 *FunPronN = new TF1("FunPronN",getDedxFunPronN,-5,-0.1,0);
	TF1 *FunDeuP = new TF1("FunDeuP",getDedxFunDeuP,0.1,5,0);
	TF1 *FunDeuN = new TF1("FunDeuN",getDedxFunDeuN,-5,-0.1,0);
	TF1 *FunTriP = new TF1("FunTriP",getDedxFunTriP,0.1,5,0);
	TF1 *FunTriN = new TF1("FunTriN",getDedxFunTriN,-5,-0.1,0);
	TF1 *FunHe3P = new TF1("FunHe3P",getDedxFunHe3P,0.1,5,0);
	TF1 *FunHe3N = new TF1("FunHe3N",getDedxFunHe3N,-5,-0.1,0);
	TF1 *FunHe4P = new TF1("FunHe4P",getDedxFunHe4P,0.1,5,0);
	TF1 *FunHe4N = new TF1("FunHe4N",getDedxFunHe4N,-5,-0.1,0);
	TF1 *DauFunElecP = new TF1("DauFunElecP",getDedxFunElecP,0.1,10,0); 
	TF1 *DauFunPionP = new TF1("DauFunPionP",getDedxFunPionP,0.1,10,0);
	DauFunElecP->SetLineWidth(1) ;DauFunElecP->SetLineColor(kBlack) ; DauFunPionP->SetLineWidth(1) ;
	FunElecP->SetLineWidth(1) ; FunElecN->SetLineWidth(1) ;
	FunPionP->SetLineWidth(1) ; FunPionN->SetLineWidth(1) ;
	FunKaonP->SetLineWidth(1) ; FunKaonN->SetLineWidth(1) ;
	FunPronP->SetLineWidth(1) ; FunPronN->SetLineWidth(1) ;
	FunDeuP->SetLineWidth(1) ; FunDeuN->SetLineWidth(1) ; 
	FunTriP->SetLineWidth(1) ; FunTriN->SetLineWidth(1) ;
	FunHe3P->SetLineWidth(1) ; FunHe3N->SetLineWidth(1) ;
	FunHe4P->SetLineWidth(1) ; FunHe4N->SetLineWidth(1) ;

	FunElecP->SetLineColor(kBlack) ; FunElecN->SetLineColor(kBlack) ;
	FunPionP->SetLineColor(kBlack) ; FunPionN->SetLineColor(kBlack) ; 
	FunKaonP->SetLineColor(kBlack) ; FunKaonN->SetLineColor(kBlack) ; 
	FunPronP->SetLineColor(kBlack) ; FunPronN->SetLineColor(kBlack) ; 
	FunDeuP->SetLineColor(kBlack) ; FunDeuN->SetLineColor(kBlack) ;  
	FunTriP->SetLineColor(kBlack) ; FunTriN->SetLineColor(kBlack) ;
	FunHe3P->SetLineColor(kBlack) ; FunHe3N->SetLineColor(kBlack) ;
	FunHe4P->SetLineColor(kBlack) ; FunHe4N->SetLineColor(kBlack) ;


	TH1D *hBeamX = new TH1D("BeamX","BeamX",100,0.,100.);
	TH1D *hBeamY = new TH1D("BeamY","BeamY",100,0.,100.);
	TH1D *hInnerGain = new TH1D("innerGain","innerGain",100,0.,100.);
	TH1D *hOuterGain = new TH1D("outerGain","outerGain",100,0.,100.);
	TH1D *hMeanDcaXy = new TH1D("meanDcaXy","meanDcaXy",100,0.,100.);
	hBeamX->SetMarkerColor(kBlue);
	hBeamX->SetMarkerSize(0.35);
	hBeamX->SetMarkerStyle(20);
	hBeamY->SetMarkerColor(kRed);
	hBeamY->SetMarkerStyle(20);
	hBeamY->SetMarkerSize(0.35);
	hInnerGain->SetMarkerColor(kBlue);
	hInnerGain->SetMarkerSize(0.35);
	hInnerGain->SetMarkerStyle(20);
	hOuterGain->SetMarkerColor(kRed);
	hOuterGain->SetMarkerSize(0.35);
	hOuterGain->SetMarkerStyle(20);
	hMeanDcaXy->SetMarkerColor(kRed);
	hMeanDcaXy->SetMarkerSize(0.35);
	hMeanDcaXy->SetMarkerStyle(20);
	/*
	char file[256];
	sprintf(file,"%s","./tmp/all.dat");
	
	ifstream fin("./tmp/all.dat");
	const int LINE_LENGTH = 100;
	char str[LINE_LENGTH];
	fin.getline(str,LINE_LENGTH);
	//char str[] = "./hlt_paras/15095016.dat";
	int len=strlen(str);
	char buf[100];
	int a[3];
	*/

        char str[100];
        sprintf(str,"%s",inputFile);
	int len=strlen(str);
	char buf[100];
	int a[3];
	int i = 0;

	while ( str[i] != '\0' )
	  {
	    if (isdigit(str[i]))
	      buf[i] = str[i];
	    else buf[i] = ' ';
	    ++i;
	  }
	buf[i] = '\0';
	//printf ("%s \n", buf);
	sscanf (buf,"%d %d %d", &a[0], &a[1], &a[2]);
	//printf ("%d %d %d\n", a[0], a[1], a[2]);
	int temp = 0;
	if(a[2]>0.1) temp = a[2];
	if(a[2]<0.1&&a[1]>0.1) temp = a[1];
	if(a[2]<0.1&&a[1]<0.1) temp = a[0];
	printf ("%d \n", temp);
	int tmprunnum = temp;

	if(temp>1000)
	  {
	    ifstream indata; string paraname;
	    char inum[256]; char labels[256];
	    int icount=100;
	    
	    for(int i=0; i<200000; i++){
	      sprintf(inum,"/net/onlldap.starp.bnl.gov/ldaphome/tb/Display_2017/HLT_paras/%i.dat",tmprunnum);
	      sprintf(labels,"%i",tmprunnum);
	      tmprunnum--;

	      double beamX , beamY; double innerGain, outerGain; double dcaXy;
	      
	      indata.open(inum);
	      if(indata.good()){
		while(!indata.eof()){
		  indata>>paraname;
		  if(paraname == "beamX") indata>>beamX;
		  if(paraname == "beamY") indata>>beamY;
		  if(paraname == "innerGain") indata>>innerGain;
		  if(paraname == "outerGain") indata>>outerGain;
		  if(paraname == "dcaXy") indata>>dcaXy;
		}
	      } else continue; 
	      indata.close();
	      indata.clear();
	      
	      hBeamX->SetBinContent(icount,beamX);
	      hBeamY->SetBinContent(icount,beamY);
	      hInnerGain->SetBinContent(icount,innerGain);
	      hOuterGain->SetBinContent(icount,outerGain);
	      if((dcaXy>8)||(dcaXy<-8)){dcaXy=0;}
	      hMeanDcaXy->SetBinContent(icount,dcaXy);
	      if((icount-1)%5==0){
		hBeamX->GetXaxis()->SetBinLabel(icount,labels);
		hBeamY->GetXaxis()->SetBinLabel(icount,labels);
		hInnerGain->GetXaxis()->SetBinLabel(icount,labels);
		hOuterGain->GetXaxis()->SetBinLabel(icount,labels);
		hMeanDcaXy->GetXaxis()->SetBinLabel(icount,labels);
	      }
	      icount--;
	      if(icount<=0) break;
	    }
	  }

	gStyle->SetPalette(1);

	TDatime datetime;

	TFile* f2 = new TFile(inputFile, "READ");

	TH1I* EvtsAccpt = (TH1I *)f2->Get("EvtsAccpt");
	int nevents = EvtsAccpt->GetEntries();
	cout << "number of events selected in this run : " <<  nevents <<endl; 
	
	if(!nevents && temp > 18056000 && temp < 18150000)//skip runnum for cosmic in run17 
	  { 
	    cout << temp <<endl;
	    cout <<"skip QA this run ! because no entries there !" << endl;
	    return 0;
	  }

	TH1I* nHits = (TH1I *)f2->Get("nHits");
	TH1I* nDedx = (TH1I*)f2->Get("nDedx");
	TH1D* DcaXy = (TH1D*)f2->Get("DcaXy");
	TH1D* DcaZ = (TH1D*)f2->Get("DcaZ");
	TH1D* DcaXy_TofMatch = (TH1D*)f2->Get("DcaXy_TofMatch");
	TH1D* DcaZ_TofMatch = (TH1D*)f2->Get("DcaZ_TofMatch");
	TH1D* DcaXy_EMCMatch = (TH1D*)f2->Get("DcaXy_EMCMatch");
	TH1D* DcaZ_EMCMatch = (TH1D*)f2->Get("DcaZ_EMCMatch");
	TH2F* dEdx = (TH2F *)f2->Get("dEdx");
	TH1D* Ln_dEdx = (TH1D *)f2->Get("Ln_dEdx");
	TH1D* Glob_Pt = (TH1D *)f2->Get("Glob_Pt");  
	TH1D* Glob_Phi = (TH1D *)f2->Get("Glob_Phi");
	TH1D* Glob_Eta = (TH1D*)f2->Get("Glob_Eta");
	TH2F* Glob_dEdx = (TH2F *)f2->Get("Glob_dEdx");
	//TH2F* HFM_dEdx = (TH2F *)f2->Get("HFM_dEdx");
	TH1D* Prim_Pt = (TH1D *)f2->Get("Prim_Pt");
	TH1D* Prim_Phi = (TH1D *)f2->Get("Prim_Phi");
	TH1D* Prim_Eta = (TH1D*)f2->Get("Prim_Eta");
	TH2F* Prim_dEdx = (TH2F *)f2->Get("Prim_dEdx");
	TH1D* VertexX = (TH1D*)f2->Get("VertexX");
	TH1D* VertexY = (TH1D*)f2->Get("VertexY");
	TH1D* VertexZ = (TH1D*)f2->Get("VertexZ"); 
	TH2D* VertexXY = (TH2D*)f2->Get("VertexXY");
	TH1D* VertexR = (TH1D*)f2->Get("VertexR");
	TH1D* Lm_VertexX = (TH1D*)f2->Get("Lm_VertexX");
	TH1D* Lm_VertexY = (TH1D*)f2->Get("Lm_VertexY");
	TH1D* Lm_VertexZ = (TH1D*)f2->Get("Lm_VertexZ");
	TH1I* globalMult = (TH1I *)f2->Get("globalMult");
	TH1I* primaryMult = (TH1I *)f2->Get("primaryMult");
	TH1D* Emc_matchPhiDiff = (TH1D*)f2->Get("Emc_matchPhiDiff");
	TH1D* Emc_towerEnergy = (TH1D*)f2->Get("Emc_towerEnergy");
	TH1I* Emc_towerDaqId = (TH1I*)f2->Get("Emc_towerDaqId");
	TH1I* Emc_towerSoftId = (TH1I*)f2->Get("Emc_towerSoftId");
	TH1D* Emc_zEdge = (TH1D*)f2->Get("Emc_zEdge");
	TH1D* Emc_towerEtaPhi = (TH1D*)f2->Get("Emc_towerEtaPhi");
	TH1D* Tof_LocalZ = (TH1D*)f2->Get("Tof_LocalZ");
	TH1D* Tof_LocalY = (TH1D*)f2->Get("Tof_LocalY");
	TH2F* Tof_InverseBeta = (TH2F*)f2->Get("Tof_InverseBeta");
	TH2F* Tof_matchId_fireId = (TH2F*)f2->Get("Tof_matchId_fireId");
	TH2F* Tof_TrayID_TrgTime = (TH2F*)f2->Get("Tof_TrayID_TrgTime");
	TH1D* Tof_channelID = (TH1D*)f2->Get("Tof_channelID");
	TH2F* Vzvpd_Vz = (TH2F*)f2->Get("Vzvpd_Vz");
	TH1D* VzDiff = (TH1D*)f2->Get("VzDiff");
	TH2D* BesMonitor_VertexXY = (TH2D*)f2->Get("BesMonitor_VertexXY");
	TH1D* BesMonitor_Vr = (TH1D*)f2->Get("BesMonitor_Vr");
	TH2D* HLTGood2_VertexXY = (TH2D*)f2->Get("HLTGood2_VertexXY");
	TH1D* HLTGood2_VertexZ = (TH1D*)f2->Get("HLTGood2_VertexZ");
	TH1D* HLTGood2_Vr = (TH1D*)f2->Get("HLTGood2_Vr");
	TH1I* HLTGood2_primaryMult = (TH1I *)f2->Get("HLTGood2_primaryMult");
	TH2F* HeavyFragment_dEdx = (TH2F*)f2->Get("HeavyFragment_dEdx");
	TH1D* DiElectronInvMassTpxEmc = (TH1D*)f2->Get("DiElectronInvMassTpxEmc");
	TH1D* DiElectronInvMassTpxEmcBG = (TH1D*)f2->Get("DiElectronInvMassTpxEmcBG");
	TH1D* DiElectronInvMassCut = (TH1D*)f2->Get("DiElectronInvMassCut");
	TH1D* DiElectronInvMassCutBG = (TH1D*)f2->Get("DiElectronInvMassCutBG");
	TH1D* DiElectronInvMassFullRange = (TH1D*)f2->Get("DiElectronInvMassFullRange");
	TH1D* DiElectronInvMassFullRangeBG = (TH1D*)f2->Get("DiElectronInvMassFullRangeBG");
	TH2F* dEdx_P1 = (TH2F*)f2->Get("dEdx_P1");
	TH1D* Daughter1P_TowerEnergy = (TH1D*)f2->Get("Daughter1P_TowerEnergy");
	TH1D* Daughter1TpxEmcInverseBeta = (TH1D*)f2->Get("Daughter1TpxEmcInverseBeta");
	TH2F* dEdx_P2 = (TH2F*)f2->Get("dEdx_P2");
	TH1D* Daughter2P_TowerEnergy = (TH1D*)f2->Get("Daughter2P_TowerEnergy");
	TH1D* Daughter2TpxEmcInverseBeta = (TH1D*)f2->Get("Daughter2TpxEmcInverseBeta");
	TH1D* DiLeptonRapidity = (TH1D*)f2->Get("DiLeptonRapidity");
	TH1F* hInvMassLS = (TH1F*)f2->Get("hInvMassLS");
	TH1F* hInvMassUS = (TH1F*)f2->Get("hInvMassUS");
	TH2F* hMtdHitMap = (TH2F*)f2->Get("hMtdHitMap");
	TH2F* hMtdMatchHitMap = (TH2F*)f2->Get("hMtdMatchHitMap");
	TH2F* hMtdDeltaZvsModule = (TH2F*)f2->Get("hMtdDeltaZvsModule");
	TH1F* hMtdDeltaZ = (TH1F*)f2->Get("hMtdDeltaZ");
	TH2F* hMtdDeltaYvsModule = (TH2F*)f2->Get("hMtdDeltaYvsModule");
	TH1F* hMtdDeltaY = (TH1F*)f2->Get("hMtdDeltaY");	
	TH1F* hMTDQmInvMassUS = (TH1F*)f2->Get("hMTDQmInvMassUS");
	TH1F* hMTDQmInvMassLS = (TH1F*)f2->Get("hMTDQmInvMassLS");
	//TH1F* hMTDQmJpsiMassUS = (TH1F*)f2->Get("hMTDQmJpsiMassUS");
	//TH1F* hMTDQmJpsiMassLS = (TH1F*)f2->Get("hMTDQmJpsiMassLS");
	TH1F* hMTDQmUpsilonMassUS = (TH1F*)f2->Get("hMTDQmUpsilonMassUS");
	TH1F* hMTDQmUpsilonMassLS = (TH1F*)f2->Get("hMTDQmUpsilonMassLS");

	TH1F*	hMTDQmJpsiMass_ptcut0_US = (TH1F*)f2->Get("hMTDQmJpsiMass_ptcut0_US");
	TH1F*	hMTDQmJpsiMass_ptcut0_LS = (TH1F*)f2->Get("hMTDQmJpsiMass_ptcut0_LS");
	TH1F*	hMTDQmJpsiMass_ptcut2_US = (TH1F*)f2->Get("hMTDQmJpsiMass_ptcut2_US");
	TH1F*	hMTDQmJpsiMass_ptcut2_LS = (TH1F*)f2->Get("hMTDQmJpsiMass_ptcut2_LS");
	TH1F*	hMTDQmJpsiMass_ptcut4_US = (TH1F*)f2->Get("hMTDQmJpsiMass_ptcut4_US");
	TH1F*	hMTDQmJpsiMass_ptcut4_LS = (TH1F*)f2->Get("hMTDQmJpsiMass_ptcut4_LS");
	TH1F*	hMTDDiMuonJpsiMassUS = (TH1F*)f2->Get("hMTDDiMuonJpsiMassUS");
	TH1F*	hMTDDiMuonJpsiMassLS = (TH1F*)f2->Get("hMTDDiMuonJpsiMassLS");
	TH1F*	hMTDDiMuonUpsilonMassUS = (TH1F*)f2->Get("hMTDDiMuonUpsilonMassUS");	
	TH1F*	hMTDDiMuonUpsilonMassLS	= (TH1F*)f2->Get("hMTDDiMuonUpsilonMassLS"); 



	TH1D*	DiElectronInvMassTpxEmc_Twr = (TH1D*)f2->Get("DiElectronInvMassTpxEmc_Twr");
	TH1D*	DiElectronInvMassTpxEmcBG_Twr = (TH1D*)f2->Get("DiElectronInvMassTpxEmcBG_Twr");
	TH1D*	DiElectronInvMassCut_Twr = (TH1D*)f2->Get("DiElectronInvMassCut_Twr");
	TH1D*	DiElectronInvMassCutBG_Twr = (TH1D*)f2->Get("DiElectronInvMassCutBG_Twr");
	TH1D*	DiElectronInvMassFullRange_Twr = (TH1D*)f2->Get("DiElectronInvMassFullRange_Twr");
	TH1D*	DiElectronInvMassFullRangeBG_Twr = (TH1D*)f2->Get("DiElectronInvMassFullRangeBG_Twr");
	TH2F*	dEdx_P1_Twr = (TH2F*)f2->Get("dEdx_P1_Twr");
	TH1D*	Daughter1P_TowerEnergy_Twr = (TH1D*)f2->Get("Daughter1P_TowerEnergy_Twr");
	TH1D*	Daughter1TpxEmcInverseBeta_Twr = (TH1D*)f2->Get("Daughter1TpxEmcInverseBeta_Twr");
	TH2F*	dEdx_P2_Twr = (TH2F*)f2->Get("dEdx_P2_Twr");
	TH1D*	Daughter2P_TowerEnergy_Twr = (TH1D*)f2->Get("Daughter2P_TowerEnergy_Twr");
	TH1D*	Daughter2TpxEmcInverseBeta_Twr = (TH1D*)f2->Get("Daughter2TpxEmcInverseBeta_Twr");
	TH1D*	DiLeptonRapidity_Twr = (TH1D*)f2->Get("DiLeptonRapidity_Twr");

	TH2D* BesGood_VertexXY = (TH2D*)f2->Get("BesGood_VertexXY");
	TH1D* BesGood_VertexZ = (TH1D*)f2->Get("BesGood_VertexZ");
	TH1D* BesGood_Vr = (TH1D*)f2->Get("BesGood_Vr");
	TH1I* BesGood_primaryMult = (TH1I*)f2->Get("BesGood_primaryMult");
	TH2D* BesGood_VrVsVz = (TH2D*)f2->Get("BesGood_VrVsVz");

	TCanvas *c1 = new TCanvas("c1","canvas",600,800);
	TCanvas *c2 = new TCanvas("c2","canvas",600,800);
	TCanvas *c3 = new TCanvas("c3","canvas",600,800);
	TCanvas *c4 = new TCanvas("c4","canvas",600,800);
	TCanvas *c5 = new TCanvas("c5","canvas",600,800);
	TCanvas *c6 = new TCanvas("c6","canvas",600,800);
	TCanvas *c7 = new TCanvas("c7","canvas",600,800);
	TCanvas *c8 = new TCanvas("c8","canvas",600,800);
	TCanvas *c9 = new TCanvas("c9","canvas",600,800);
	TCanvas *c10 = new TCanvas("c10","canvas",600,800);
	TCanvas *c11 = new TCanvas("c11","canvas",600,800);
	TCanvas *c12 = new TCanvas("c12","canvas",600,800);
	TCanvas *c13 = new TCanvas("c13","canvas",600,800);
	TCanvas *c14 = new TCanvas("c14","canvas",600,800);
	TCanvas *c15 = new TCanvas("c15","canvas",600,800);
	TCanvas *c16 = new TCanvas("c16","canvas",600,800);
	TCanvas *c17 = new TCanvas("c17","canvas",600,800);


	float low = -13.12;
        float high = -12.8;
	TF1 *fit_LndEdx = new TF1("fit_LndEdx", "gaus", low, high);
        fit_LndEdx->SetParName(0, "Apt");
        fit_LndEdx->SetParName(1, "Pos");
        fit_LndEdx->SetParName(2, "Sig");
        fit_LndEdx->SetParameter(0,10000);
        fit_LndEdx->SetParameter(1, -12.92);
        fit_LndEdx->SetParameter(2, 0.08);
        //hLn_dEdx->Fit(fit, "EMR");
        
	/*
	TF1 *fit_DcaXy = new TF1("fit_DcaXy", "gaus", -1.5, 1.5);
        fit_DcaXy->SetParName(0, "Apt");
        fit_DcaXy->SetParName(1, "Pos");
        fit_DcaXy->SetParName(2, "Sig");
        fit_DcaXy->SetParameter(0,10000);
        fit_DcaXy->SetParameter(1, 0);
        fit_DcaXy->SetParameter(2, 0.08);
	*/
       
	TF1 *fit_DcaXy = new TF1("fit_DcaXy","[0]*1.0/(sqrt(2*3.1415926)*[2])*exp(-1*(x-[1])*(x-[1])/(2*[2]*[2]))+[3]*1.0/(sqrt(2*3.1415926)*[5])*exp(-1*(x-[4])*(x-[4])/(2*[5]*[5]))",-5.0,5.0);
	
	/*
	TF1* fitSig=new TF1("fitSig","[0]*1.0/(sqrt(2*3.14159)*[2])*exp(-1*(x-[1])*(x-[1])/(2*[2]*[2]))",-5.0,5.0);
	fitSig->SetParameter(0,fit_DcaXy->GetParameter(0));
	fitSig->SetParameter(1,fit_DcaXy->GetParameter(1));
	fitSig->SetParameter(2,fit_DcaXy->GetParameter(2));
	fitSig->SetLineColor(2);
	fitSig->Draw("same");
	
	TF1* fitBg=new TF1("fitBg","[0]*1.0/(sqrt(2*3.14159)*[2])*exp(-1*(x-[1])*(x-[1])/(2*[2]*[2]))",-5.0,5.0);
	fitBg->SetParameter(0,fit_DcaXy->GetParameter(3));
	fitBg->SetParameter(1,fit_DcaXy->GetParameter(4));
	fitBg->SetParameter(2,fit_DcaXy->GetParameter(5));
	fitBg->SetLineColor(4);
	fitBg->Draw("same");
	*/

	TF1 *fit_HLTGood2_VertexZ = new TF1("fit_HLTGood2_VertexZ", "gaus", -5.9, 5.9);
        fit_HLTGood2_VertexZ->SetParName(0, "Apt");
        fit_HLTGood2_VertexZ->SetParName(1, "Pos");
        fit_HLTGood2_VertexZ->SetParName(2, "Sig");
        fit_HLTGood2_VertexZ->SetParameter(0,10000);
        fit_HLTGood2_VertexZ->SetParameter(1, 0);
        fit_HLTGood2_VertexZ->SetParameter(2, 0.08);

	TString outPdfFileName(inputFile);
	outPdfFileName.ReplaceAll(".root",".pdf");

	gSystem->Exec(("rm -f "+outPdfFileName).Data());
	TPDF *pdfFile = new TPDF(outPdfFileName.Data(),111);

	TPaveText *titlePave = new TPaveText(.1,.1,.9,0.9,"brNDC");
	titlePave->AddText("This file is produced on ");
	titlePave->AddText(datetime.AsString());
	titlePave->SetBorderSize(1);
	titlePave->SetTextAlign(22);
	titlePave->SetFillColor(kWhite);

	TLegend *leg1 = new TLegend(0.75,0.5,0.99,0.7);
	leg1->SetTextSize(0.06);
	leg1->SetLineColor(4);
	leg1->SetLineStyle(1);
	leg1->SetLineWidth(3.5);
	leg1->SetFillColor(0);
	leg1->SetMargin(0.1);
	leg1->SetFillStyle(0);
	leg1->SetTextAlign(12);
	leg1->SetBorderSize(0);
	leg1->AddEntry(DiElectronInvMassFullRange, "US","pl");
	leg1->AddEntry(DiElectronInvMassFullRangeBG, "LS","pl");

	TLegend *leg2 = new TLegend(0.75,0.5,0.99,0.7);
	leg2->SetTextSize(0.06);
	leg2->SetLineColor(4);
	leg2->SetLineStyle(1);
	leg2->SetLineWidth(3.5);
	leg2->SetFillColor(0);
	leg2->SetMargin(0.1);
	leg2->SetFillStyle(0);
	leg2->SetTextAlign(12);
	leg2->SetBorderSize(0);
	leg2->AddEntry(hBeamX, " BeamX","pl");
	leg2->AddEntry(hBeamY, " BeamY","pl");

	TLegend *leg3 = new TLegend(0.75,0.5,0.99,0.7);
	leg3->SetTextSize(0.06);
	leg3->SetLineColor(4);
	leg3->SetLineStyle(1);
	leg3->SetLineWidth(3.5);
	leg3->SetFillColor(0);
	leg3->SetMargin(0.1);
	leg3->SetFillStyle(0);
	leg3->SetTextAlign(12);
	leg3->SetBorderSize(0);
	leg3->AddEntry(hInnerGain, " innerGainSector","pl");
	leg3->AddEntry(hOuterGain, " outerGainSector","pl");

	TLegend *leg4 = new TLegend(0.75,0.5,0.99,0.7);
	leg4->SetTextSize(0.06);
	leg4->SetLineColor(4);
	leg4->SetLineStyle(1);
	leg4->SetLineWidth(3.5);
	leg4->SetFillColor(0);
	leg4->SetMargin(0.1);
	leg4->SetFillStyle(0);
	leg4->SetTextAlign(12);
	leg4->SetBorderSize(0);
	leg4->AddEntry(hMTDQmInvMassUS, "US","l");
	leg4->AddEntry(hMTDQmInvMassLS, "LS","l");


	TLegend *leg6 = new TLegend(0.75,0.5,0.99,0.7);
	leg6->SetTextSize(0.06);
	leg6->SetLineColor(4);
	leg6->SetLineStyle(1);
	leg6->SetLineWidth(3.5);
	leg6->SetFillColor(0);
	leg6->SetMargin(0.1);
	leg6->SetFillStyle(0);
	leg6->SetTextAlign(12);
	leg6->SetBorderSize(0);
	leg6->AddEntry(hMTDQmUpsilonMassUS, "US","l");
	leg6->AddEntry(hMTDQmUpsilonMassLS, "LS","l");

	TLegend *leg7 = new TLegend(0.75,0.5,0.99,0.7);
	leg7->SetTextSize(0.06);
	leg7->SetLineColor(4);
	leg7->SetLineStyle(1);
	leg7->SetLineWidth(3.5);  
	leg7->SetFillColor(0);
	leg7->SetMargin(0.1);
	leg7->SetFillStyle(0);
	leg7->SetTextAlign(12);
	leg7->SetBorderSize(0);
	leg7->AddEntry(hInvMassUS, "US","l");
	leg7->AddEntry(hInvMassLS, "LS","l");

	TLegend *leg8 = new TLegend(0.75,0.5,0.99,0.7);
	leg8->SetTextSize(0.06);
	leg8->SetLineColor(4);
	leg8->SetLineStyle(1);
	leg8->SetLineWidth(3.5);
	leg8->SetFillColor(0);
	leg8->SetMargin(0.1);
	leg8->SetFillStyle(0);
	leg8->SetTextAlign(12);
	leg8->SetBorderSize(0);
	leg8->AddEntry(hMTDDiMuonJpsiMassUS, "US","l");
	leg8->AddEntry(hMTDDiMuonJpsiMassLS, "LS","l");

	TLegend *leg9 = new TLegend(0.75,0.5,0.99,0.7);
	leg9->SetTextSize(0.06);
	leg9->SetLineColor(4);
	leg9->SetLineStyle(1);
	leg9->SetLineWidth(3.5);
	leg9->SetFillColor(0);
	leg9->SetMargin(0.1);
	leg9->SetFillStyle(0);
	leg9->SetTextAlign(12);
	leg9->SetBorderSize(0);
	leg9->AddEntry(hMTDDiMuonUpsilonMassUS, "US","l");
	leg9->AddEntry(hMTDDiMuonUpsilonMassLS, "LS","l");

	TLegend *leg10 = new TLegend(0.75,0.5,0.99,0.7);
	leg10->SetTextSize(0.06);
	leg10->SetLineColor(4);
	leg10->SetLineStyle(1);
	leg10->SetLineWidth(3.5);
	leg10->SetFillColor(0);
	leg10->SetMargin(0.1);
	leg10->SetFillStyle(0);
	leg10->SetTextAlign(12);
	leg10->SetBorderSize(0);
	leg10->AddEntry(hMTDQmJpsiMass_ptcut0_US, "US","l");
	leg10->AddEntry(hMTDQmJpsiMass_ptcut0_LS, "LS","l");


	TLegend *leg11 = new TLegend(0.75,0.5,0.99,0.7);
	leg11->SetTextSize(0.06);
	leg11->SetLineColor(4);
	leg11->SetLineStyle(1);
	leg11->SetLineWidth(3.5);
	leg11->SetFillColor(0);
	leg11->SetMargin(0.1);
	leg11->SetFillStyle(0);
	leg11->SetTextAlign(12);
	leg11->SetBorderSize(0);
	leg11->AddEntry(hMTDQmJpsiMass_ptcut2_US, "US","l");
	leg11->AddEntry(hMTDQmJpsiMass_ptcut2_LS, "LS","l");

	TLegend *leg12 = new TLegend(0.75,0.5,0.99,0.7);
	leg12->SetTextSize(0.06);
	leg12->SetLineColor(4);
	leg12->SetLineStyle(1);
	leg12->SetLineWidth(3.5);
	leg12->SetFillColor(0);
	leg12->SetMargin(0.1);
	leg12->SetFillStyle(0);
	leg12->SetTextAlign(12);
	leg12->SetBorderSize(0);
	leg12->AddEntry(hMTDQmJpsiMass_ptcut4_US, "US","l");
	leg12->AddEntry(hMTDQmJpsiMass_ptcut4_LS, "LS","l");

	TLegend *leg13 = new TLegend(0.75,0.5,0.99,0.7);
        leg13->SetTextSize(0.06);
        leg13->SetLineColor(4);
        leg13->SetLineStyle(1);
        leg13->SetLineWidth(3.5);
        leg13->SetFillColor(0);
        leg13->SetMargin(0.1);
        leg13->SetFillStyle(0);
        leg13->SetTextAlign(12);
        leg13->SetBorderSize(0);
        leg13->AddEntry(DiElectronInvMassFullRange_Twr, "US","pl");
        leg13->AddEntry(DiElectronInvMassFullRangeBG_Twr, "LS","pl");

	if(EvtsAccpt!=NULL)
	  {
	    c1->cd();
	    c1->Divide(2,3);
	    c1->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    titlePave->Draw();
	    c1->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogy(1);
	    EvtsAccpt->SetMaximum();
	    EvtsAccpt->Draw();
	    c1->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    nHits->SetMaximum();
	    nHits->Draw(); 
	    c1->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    nDedx->SetBinContent(1,0);
	    nDedx->SetMaximum();
	    nDedx->Draw(); 
	    c1->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);
	    DcaXy->SetMaximum();
	    
	    fit_DcaXy->SetParLimits(1,-1+(-6.0+0.1*DcaXy->GetMaximumBin()),1+(-6.0+0.1*DcaXy->GetMaximumBin()));
	    fit_DcaXy->SetParameter(1,-6.0+0.1*DcaXy->GetMaximumBin());
	    fit_DcaXy->SetParLimits(2,0.3,2.5);
	    fit_DcaXy->SetParLimits(5,2.8,10);
	    fit_DcaXy->SetParLimits(4,-1,1);
	   
	    DcaXy->Fit(fit_DcaXy, "EMR","",-5.1,5.1);
	    DcaXy->Draw(); 
	    
	    c1->cd(6); gPad->SetGridx(0); gPad->SetGridy(0);
	    DcaZ->SetMaximum();
	    DcaZ->Draw();
	    //HFM_dEdx->SetMarkerStyle(30); HFM_dEdx->SetMarkerSize(0.1); dEdx->Draw("colz"); FunElecP->Draw("SAME"); FunElecN->Draw("SAME"); FunPionP->Draw("SAME"); FunPionN->Draw("SAME"); FunKaonP->Draw("SAME"); FunKaonN->Draw("SAME"); FunDeuP->Draw("SAME"); FunDeuN->Draw("SAME");FunPronP->Draw("SAME"); FunPronN->Draw("SAME");FunTriP->Draw("SAME"); FunTriN->Draw("SAME");FunHe3P->Draw("SAME"); FunHe3N->Draw("SAME");FunHe4P->Draw("SAME"); FunHe4N->Draw("SAME");
	    c1->Update();
	    c1->cd();
	    c1->Update();
	  }
	delete c1;

	if(DcaXy_TofMatch!=NULL)
	  {
	    pdfFile->NewPage();
	    //c17->cd();
	    c17->Divide(2,2);
	    c17->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    DcaXy_TofMatch->SetMaximum();
	    DcaXy_TofMatch->Draw(); 
	    c17->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    DcaZ_TofMatch->SetMaximum();
	    DcaZ_TofMatch->Draw();
	    c17->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    DcaXy_EMCMatch->SetMaximum();
	    DcaXy_EMCMatch->Draw(); 
	    c17->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    DcaZ_EMCMatch->SetMaximum();
	    DcaZ_EMCMatch->Draw();
	    c17->Update();
	    c17->cd();
	    c17->Update();
	  }

	if(dEdx!=NULL)
	  {
	    pdfFile->NewPage();
	    // c2->cd();
	    c2->Divide(2,3);
	    c2->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    dEdx->Draw("colz"); FunElecP->Draw("SAME"); FunElecN->Draw("SAME"); FunPionP->Draw("SAME"); FunPionN->Draw("SAME"); FunKaonP->Draw("SAME"); FunKaonN->Draw("SAME"); FunPronP->Draw("SAME"); FunPronN->Draw("SAME");
	    c2->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogz(1);
	    Ln_dEdx->SetMaximum();
	    Ln_dEdx->Fit(fit_LndEdx, "EMR");
	    Ln_dEdx->Draw();
	    c2->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1);
	    Glob_Pt->SetMaximum();
	    Glob_Pt->Draw();
	    c2->cd(4); gPad->SetGridx(0); gPad->SetGridy(0); Glob_Phi->SetMinimum(0.) ; 
	    Glob_Phi->SetMaximum();
	    Glob_Phi->Draw();
	    c2->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);
	    Glob_Eta->SetMaximum();
	    Glob_Eta->Draw();
	    c2->cd(6); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    Glob_dEdx->Draw("colz"); FunElecP->Draw("SAME"); FunElecN->Draw("SAME"); FunPionP->Draw("SAME"); FunPionN->Draw("SAME"); FunKaonP->Draw("SAME"); FunKaonN->Draw("SAME"); FunPronP->Draw("SAME"); FunPronN->Draw("SAME");
	    c2->Update();
	    c2->cd();
	    c2->Update();
	  }
	delete c2;

	if(Prim_Pt!=NULL)
	  {
	    pdfFile->NewPage();
	    c3->Divide(2,3);
	    c3->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1); 
	    Prim_Pt->SetMaximum(); 
	    gPad->SetLogy(1); 
	    Prim_Pt->Draw();
	    c3->cd(2); gPad->SetGridx(0); gPad->SetGridy(0); Prim_Phi->SetMinimum(0.);
	    Prim_Phi->SetMaximum();
	    Prim_Phi->Draw();
	    c3->cd(3); gPad->SetGridx(0); gPad->SetGridy(0); 
	    Prim_Eta->SetMaximum();
	    Prim_Eta->Draw();
	    c3->cd(4); gPad->SetGridx(0); gPad->SetGridy(0); gPad->SetLogz(1);
	    Prim_dEdx->Draw("colz"); FunElecP->Draw("SAME"); FunElecN->Draw("SAME"); FunPionP->Draw("SAME"); FunPionN->Draw("SAME"); FunKaonP->Draw("SAME"); FunKaonN->Draw("SAME"); FunPronP->Draw("SAME"); FunPronN->Draw("SAME");
	    c3->cd(5); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    VertexX->SetMaximum();
	    VertexX->Draw();
	    c3->cd(6); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    VertexY->SetMaximum();
	    VertexY->Draw();
	    c3->Update();
	    c3->cd();
	    c3->Update();
	  }
	delete c3;

	if(VertexZ!=NULL)
	  {
	    pdfFile->NewPage();
	    c4->Divide(2,3);
	    c4->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1);
	    VertexZ->SetMaximum();
	    VertexZ->Draw();
	    c4->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);// Prim_Phi->SetMinimum(0.) ;
	    VertexXY->Draw("colz");
	    c4->cd(3); gPad->SetGridx(0); gPad->SetGridy(0); 
	    VertexR->SetMaximum();
	    VertexR->Draw();
	    c4->cd(4); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogz(1);
	    Lm_VertexX->SetMaximum();
	    Lm_VertexX->Draw();
	    c4->cd(5); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    Lm_VertexY->SetMaximum();
	    Lm_VertexY->Draw();
	    c4->cd(6); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    Lm_VertexZ->SetMaximum();
	    Lm_VertexZ->Draw();
	    c4->Update();
	    c4->cd();
	    c4->Update();
	  }
	delete c4;

	if(globalMult!=NULL)
	  {
	    pdfFile->NewPage();
	    c5->Divide(2,3);
	    c5->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1);
	    globalMult->SetMaximum();  
	    gPad->SetLogy(1);
	    globalMult->Draw();
	    c5->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1);
	    primaryMult->SetMaximum();
	    gPad->SetLogy(1);
	    primaryMult->Draw();
	    c5->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    Emc_matchPhiDiff->SetMaximum();
	    Emc_matchPhiDiff->Draw();
	    c5->cd(4); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogz(1);
	    Emc_towerEnergy->SetMaximum();
	    Emc_towerEnergy->Draw();
	    c5->cd(5); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    Emc_towerDaqId->SetMaximum();
	    Emc_towerDaqId->Draw();
	    c5->cd(6); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    Emc_towerSoftId->SetMaximum();
	    Emc_towerSoftId->Draw();
	    c5->Update();
	    c5->cd();
	    c5->Update();
	  }
	delete c5;

	if(Emc_zEdge!=NULL)
	  {
	    pdfFile->NewPage();
	    c6->Divide(2,3);
	    c6->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    Emc_zEdge->SetMaximum();
	    Emc_zEdge->Draw();
	    c6->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1);
	    Emc_towerEtaPhi->Draw("colz");
	    c6->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    Tof_LocalZ->SetMaximum();
	    Tof_LocalZ->Draw();
	    c6->cd(4); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogz(1);
	    Tof_LocalY->SetMaximum();
	    Tof_LocalY->Draw();
	    c6->cd(5); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    Tof_InverseBeta->Draw("colz");
	    c6->cd(6); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogy(1);
	    Tof_matchId_fireId->Draw("colz");
	    c6->Update();
	    c6->cd();
	    c6->Update();
	  }
	delete c6;

	if(Tof_TrayID_TrgTime!=NULL)
	  {
	    pdfFile->NewPage();
	    c7->Divide(2,3);
	    c7->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    Tof_TrayID_TrgTime->Draw("colz");
	    c7->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);//gPad->SetLogy(1);
	    Tof_channelID->SetMaximum();
	    Tof_channelID->Draw();
	    c7->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    Vzvpd_Vz->Draw("colz");
	    c7->cd(4); gPad->SetGridx(0); gPad->SetGridy(0); //gPad->SetLogz(1);
	    VzDiff->SetMaximum();
	    VzDiff->Draw();
	    c7->Update();
	    c7->cd();
	    c7->Update();
	  }
	delete c7;

	if(HLTGood2_VertexXY!=NULL)
	  {
	    pdfFile->NewPage();
	    c8->Divide(2,3);
	    c8->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    HLTGood2_VertexXY->Draw("colz");
	    c8->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    HLTGood2_VertexZ->SetMaximum();
	    HLTGood2_VertexZ->Fit("fit_HLTGood2_VertexZ","EMR");
	    HLTGood2_VertexZ->Draw();
	    c8->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    HLTGood2_Vr->SetMaximum();
	    HLTGood2_Vr->Draw();
	    c8->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    HLTGood2_primaryMult->SetMaximum();
	    gPad->SetLogy(1);
	    HLTGood2_primaryMult->Draw();
	    c8->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiElectronInvMassTpxEmc->SetMaximum();
	    DiElectronInvMassTpxEmcBG->SetMaximum();
	    DiElectronInvMassTpxEmc->Draw();DiElectronInvMassTpxEmc->SetLineColor(kBlue);
	    DiElectronInvMassTpxEmcBG->Draw("same");
	    c8->cd(6); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiElectronInvMassCut->SetMaximum();
	    DiElectronInvMassCutBG->SetMaximum();
	    DiElectronInvMassCut->Draw();DiElectronInvMassCutBG->Draw("same");
	    c8->Update();
	    c8->cd();
	    c8->Update();
	  }
	delete c8;

	if(DiElectronInvMassFullRange!=NULL)
	  {
	    pdfFile->NewPage();
	    c9->Divide(2,3);
	    c9->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiElectronInvMassFullRange->SetMaximum();
	    DiElectronInvMassFullRangeBG->SetMaximum();
	    DiElectronInvMassFullRange->Draw();DiElectronInvMassFullRange->SetLineColor(kBlue);
	    DiElectronInvMassFullRangeBG->Draw("same");
	    leg1->Draw("same");
	    c9->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiLeptonRapidity->SetMaximum();
	    DiLeptonRapidity->Draw();  
	    c9->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    dEdx_P1->Draw("colz"); FunElecP->Draw("SAME");FunPionP->Draw("SAME");
	    c9->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter1P_TowerEnergy->SetMaximum();
	    Daughter1P_TowerEnergy->Draw();
	    c9->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter1TpxEmcInverseBeta->Draw();
	    c9->cd(6); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    dEdx_P2->Draw("colz"); FunElecP->Draw("SAME");FunPionP->Draw("SAME");
	    c9->Update();
	    c9->cd();
	    c9->Update();
	  }
	delete c9; 

	if(Daughter2P_TowerEnergy!=NULL)
	  {
	    pdfFile->NewPage();
	    c10->Divide(2,3);
	    c10->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter2P_TowerEnergy->SetMaximum();
	    Daughter2P_TowerEnergy->Draw();
	    c10->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter2TpxEmcInverseBeta->Draw();
	    c10->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    dEdx->Draw("colz"); 
	    HeavyFragment_dEdx->SetMarkerSize(0.35);
	    HeavyFragment_dEdx->Draw("SAME");FunElecP->Draw("SAME"); FunElecN->Draw("SAME"); FunPionP->Draw("SAME"); FunPionN->Draw("SAME"); FunKaonP->Draw("SAME"); FunKaonN->Draw("SAME"); FunPronP->Draw("SAME"); FunPronN->Draw("SAME");
	    c10->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    hInvMassLS->SetMaximum();
	    hInvMassLS->Draw();
	    hInvMassUS->SetMaximum();
	    hInvMassUS->SetLineColor(kBlue);
	    hInvMassUS->Draw("SAME");
	    leg7->Draw("same");
	    c10->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMtdHitMap->Draw("colz");
	    c10->cd(6);gPad->SetGridx(0); gPad->SetGridy(0);
	    hMtdMatchHitMap->Draw("colz");
	    c10->Update();
	    c10->cd();
	    c10->Update();
	  }
	delete c10;

	if(hMtdDeltaZvsModule!=NULL)
	  {
	    pdfFile->NewPage();
	    c11->Divide(2,3);
	    c11->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMtdDeltaZvsModule->Draw("colz");
	    c11->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMtdDeltaZ->SetMaximum();
	    hMtdDeltaZ->Draw();
	    c11->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMtdDeltaYvsModule->Draw("colz");
	    c11->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMtdDeltaY->SetMaximum();
	    hMtdDeltaY->Draw();
	    c11->cd(5);gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDDiMuonJpsiMassUS->SetMaximum();
	    hMTDDiMuonJpsiMassLS->SetMaximum();
	    hMTDDiMuonJpsiMassUS->Draw();hMTDDiMuonJpsiMassUS->SetLineColor(kBlue);
	    hMTDDiMuonJpsiMassLS->SetLineColor(kBlack);
	    hMTDDiMuonJpsiMassLS->Draw("same");
	    leg8->Draw("same");
	    c11->cd(6);gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDDiMuonUpsilonMassUS->SetMaximum();
	    hMTDDiMuonUpsilonMassLS->SetMaximum();
	    hMTDDiMuonUpsilonMassUS->SetLineColor(kBlue);
	    hMTDDiMuonUpsilonMassUS->Draw();
	    hMTDDiMuonUpsilonMassLS->SetLineColor(kBlack);
	    hMTDDiMuonUpsilonMassLS->Draw("same");
	    leg9->Draw("same");
	    c11->Update();
	    c11->cd();
	    c11->Update();
	  }
	delete c11;

	if(hMTDQmInvMassUS!=NULL)
	  {
	    pdfFile->NewPage();
	    c12->Divide(2,3);
	    c12->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDQmInvMassUS->SetMaximum();
	    hMTDQmInvMassLS->SetMaximum();
	    hMTDQmInvMassUS->Draw();hMTDQmInvMassUS->SetLineColor(kBlue);
	    hMTDQmInvMassLS->SetLineColor(kBlack);
	    hMTDQmInvMassLS->Draw("same");
	    leg4->Draw("same");
	    c12->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDQmUpsilonMassUS->SetMaximum();
	    hMTDQmUpsilonMassLS->SetMaximum();
	    hMTDQmUpsilonMassUS->Draw();hMTDQmUpsilonMassUS->SetLineColor(kBlue);
	    hMTDQmUpsilonMassLS->SetLineColor(kBlack);
	    hMTDQmUpsilonMassLS->Draw("same");	
	    leg6->Draw("same");
	    c12->cd(3);gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDQmJpsiMass_ptcut0_US->SetMaximum();
	    hMTDQmJpsiMass_ptcut0_LS->SetMaximum();
	    hMTDQmJpsiMass_ptcut0_US->SetLineColor(kBlue);
	    hMTDQmJpsiMass_ptcut0_US->Draw();
	    hMTDQmJpsiMass_ptcut0_LS->SetLineColor(kBlack);
	    hMTDQmJpsiMass_ptcut0_LS->Draw("same");
	    leg10->Draw("same");
	    c12->cd(4);gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDQmJpsiMass_ptcut2_US->SetMaximum();
	    hMTDQmJpsiMass_ptcut2_LS->SetMaximum();
	    hMTDQmJpsiMass_ptcut2_US->SetLineColor(kBlue);
	    hMTDQmJpsiMass_ptcut2_US->Draw();
	    hMTDQmJpsiMass_ptcut2_LS->SetLineColor(kBlack);
	    hMTDQmJpsiMass_ptcut2_LS->Draw("same");
	    leg11->Draw("same");
	    c12->cd(5);gPad->SetGridx(0); gPad->SetGridy(0);
	    hMTDQmJpsiMass_ptcut4_US->SetMaximum();
	    hMTDQmJpsiMass_ptcut4_LS->SetMaximum();
	    hMTDQmJpsiMass_ptcut4_US->SetLineColor(kBlue);
	    hMTDQmJpsiMass_ptcut4_US->Draw();
	    hMTDQmJpsiMass_ptcut4_LS->SetLineColor(kBlack);
	    hMTDQmJpsiMass_ptcut4_LS->Draw("same");
	    leg12->Draw("same");
	    c12->Update();
	    c12->cd();
	    c12->Update();
	  }
	delete c12;

	if(DiElectronInvMassTpxEmc_Twr!=NULL)
	  {
	    pdfFile->NewPage();
	    c13->Divide(2,3);
	    c13->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiElectronInvMassTpxEmc_Twr->SetMaximum();
	    DiElectronInvMassTpxEmcBG_Twr->SetMaximum();
	    DiElectronInvMassTpxEmc->SetLineColor(kBlue);
	    DiElectronInvMassTpxEmc_Twr->Draw();
	    DiElectronInvMassTpxEmcBG_Twr->Draw("same");
	    c13->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiElectronInvMassCut_Twr->SetMaximum();
	    DiElectronInvMassCutBG_Twr->SetMaximum();
	    DiElectronInvMassCut_Twr->Draw();DiElectronInvMassCutBG_Twr->Draw("same");
	    c13->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiElectronInvMassFullRange_Twr->SetMaximum();
	    DiElectronInvMassFullRangeBG_Twr->SetMaximum();
	    DiElectronInvMassFullRange_Twr->Draw();DiElectronInvMassFullRange_Twr->SetLineColor(kBlue);
	    DiElectronInvMassFullRangeBG_Twr->Draw("same");
	    leg13->Draw("same");
	    c13->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    DiLeptonRapidity_Twr->SetMaximum();
	    DiLeptonRapidity_Twr->Draw();
	    c13->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    dEdx_P1_Twr->Draw("colz"); FunElecP->Draw("SAME");FunPionP->Draw("SAME");
	    c13->cd(6); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter1P_TowerEnergy_Twr->SetMaximum();
	    Daughter1P_TowerEnergy_Twr->Draw();
	    c13->Update();
	    c13->cd();
	    c13->Update();
	  }
	delete c13;

	if(Daughter1TpxEmcInverseBeta_Twr!=NULL)
	  {
	    pdfFile->NewPage();
	    c14->Divide(2,3);
	    c14->cd(1); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter1TpxEmcInverseBeta_Twr->Draw();
	    c14->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);gPad->SetLogz(1);
	    dEdx_P2_Twr->Draw("colz"); FunElecP->Draw("SAME");FunPionP->Draw("SAME");
	    c14->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter2P_TowerEnergy_Twr->SetMaximum();
	    Daughter2P_TowerEnergy_Twr->Draw();
	    c14->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    Daughter2TpxEmcInverseBeta_Twr->Draw();
	    c14->Update();
	    c14->cd();
	    c14->Update();
	  }
	delete c14;

	if(BesGood_VertexXY!=NULL)
	  {
	    pdfFile->NewPage();
	    c15->Divide(2,3);
	    c15->cd(1);gPad->SetGridx(0); gPad->SetGridy(0);
	    BesGood_VertexXY->Draw("colz");
	    c15->cd(2); gPad->SetGridx(0); gPad->SetGridy(0);
	    BesGood_VertexZ->SetMaximum();
	    BesGood_VertexZ->Draw();
	    c15->cd(3); gPad->SetGridx(0); gPad->SetGridy(0);
	    BesGood_Vr->SetMaximum();
	    BesGood_Vr->Draw();
	    c15->cd(4); gPad->SetGridx(0); gPad->SetGridy(0);
	    BesGood_primaryMult->SetMaximum();
	    gPad->SetLogy(1);
	    BesGood_primaryMult->Draw();
	    c15->cd(5); gPad->SetGridx(0); gPad->SetGridy(0);
	    BesGood_VrVsVz->Draw("colz");
	    c15->Update();
	    c15->cd();
	    c15->Update();
	  }
        delete c15;
    

	if(temp>1000)
	  {
	    pdfFile->NewPage(); //only for runnumber.root, not day.root or all.root
	    
	    double lowestB, highestB;
	    double lowestBeamX = hBeamX->GetBinContent(hBeamX->GetMinimumBin());
	    double lowestBeamY = hBeamY->GetBinContent(hBeamY->GetMinimumBin());
	    double highestBeamX = hBeamX->GetBinContent(hBeamX->GetMaximumBin());
	    double highestBeamY = hBeamY->GetBinContent(hBeamY->GetMaximumBin());
	    if(lowestBeamX>lowestBeamY) lowestB = lowestBeamY;
	    else lowestB = lowestBeamX;
	    if(highestBeamX>highestBeamY) highestB = highestBeamX;
	    else highestB = highestBeamY;
	    if(lowestB<0) lowestB = lowestB*1.4;
	    else lowestB = lowestB*0.8;
	    if(highestB<0) highestB = highestB*0.8;
	    else highestB = highestB*1.4;
	    
	    c16->Divide(1,3);
	    c16->cd(1); gPad->SetGridx(0); gPad->SetGridy(0); gPad->SetBottomMargin(0.2);
	    hBeamX->GetXaxis()->SetTitleOffset(2.5);
	    hBeamY->GetXaxis()->SetTitleOffset(2.5);
	    hBeamX->GetYaxis()->SetRangeUser(lowestB,highestB);
	    hBeamY->GetYaxis()->SetRangeUser(lowestB,highestB);
	    hBeamX->SetLineColor(kBlue); hBeamY->SetLineColor(kRed);
	    hBeamX->Draw("p"); hBeamY->Draw("pSAME"); leg2->Draw("SAME");
	    hBeamX->SetName("beam position");hBeamX->SetTitle("beam position");
	    
	    double lowestG, highestG;
	    double lowestInner = hInnerGain->GetBinContent(hInnerGain->GetMinimumBin());
	    double lowestOuter = hOuterGain->GetBinContent(hOuterGain->GetMinimumBin());
	    double highestInner = hInnerGain->GetBinContent(hInnerGain->GetMaximumBin());
	    double highestOuter = hOuterGain->GetBinContent(hOuterGain->GetMaximumBin());
	    if(lowestInner>lowestOuter) lowestG = lowestOuter;
	    else lowestG = lowestInner;
	    if(highestInner>highestOuter) highestG = highestInner;
	    else highestG = highestOuter;
	    lowestG = lowestG*0.6;
	    highestG = highestG*1.4;
	    
	    c16->cd(2); gPad->SetGridx(0); gPad->SetGridy(0); gPad->SetBottomMargin(0.2);
	    hInnerGain->GetYaxis()->SetRangeUser(0.,highestG);
	    hOuterGain->GetYaxis()->SetRangeUser(0.,highestG);
	    hInnerGain->GetXaxis()->SetTitleOffset(2.5);
	    hOuterGain->GetXaxis()->SetTitleOffset(2.5);
	    hInnerGain->SetLineColor(kBlue); hOuterGain->SetLineColor(kRed);
	    hInnerGain->Draw("p"); hOuterGain->Draw("pSAME"); leg3->Draw("SAME");
	    hInnerGain->SetName("gain parameters"); hOuterGain->SetTitle("gain parameters");
	    
	    double lowestD, highestD;
	    lowestD = hMeanDcaXy->GetBinContent(hMeanDcaXy->GetMinimumBin());
	    highestD = hMeanDcaXy->GetBinContent(hMeanDcaXy->GetMaximumBin());
	    if(lowestD<0) lowestD = lowestD*1.2;
	    else lowestD = lowestD*0.8;
	    if(highestD<0) highestD = highestD*0.8;
	    else highestD = highestD*1.2;
	    
	    c16->cd(3); gPad->SetGridx(0); gPad->SetGridy(0); gPad->SetBottomMargin(0.2);
	    hMeanDcaXy->GetYaxis()->SetRangeUser(lowestD,highestD);
	    hMeanDcaXy->GetXaxis()->SetTitleOffset(2.5);
	    hMeanDcaXy->SetStats(0);
	    hMeanDcaXy->Draw("p");
	    hMeanDcaXy->SetName("dcaXy mean value");
	    hMeanDcaXy->SetTitle("dcaXy mean value");
	    c16->Update();
	    c16->cd();
	    c16->Update();
	  }
	delete c16;
	

	pdfFile->Close();

	f2->Close();

	if (f2) delete f2;  
	if (titlePave) delete titlePave;
	// if (c4) delete c4;
	// if (leg1) delete leg1;

	return 1;
}

double getDedxFunElecP(double *x, double *par)
{ 
	int plndex  = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxElec[plndex] + dx/pBin*dedxElec[plndex+1];
}
double getDedxFunElecN(double *x, double *par)
{
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxElec[plndex] + dx/pBin*dedxElec[plndex+1];
}
double getDedxFunPionP(double *x, double *par)
{ 
	int  plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxPion[plndex] + dx/pBin*dedxPion[plndex+1];
}
double getDedxFunPionN(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxPion[plndex] + dx/pBin*dedxPion[plndex+1];
}
double getDedxFunKaonP(double *x, double *par)
{ 
	int plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxKaon[plndex] + dx/pBin*dedxKaon[plndex+1];
}
double getDedxFunKaonN(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxKaon[plndex] + dx/pBin*dedxKaon[plndex+1];
}
double getDedxFunPronP(double *x, double *par)
{ 
	int plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxPron[plndex] + dx/pBin*dedxPron[plndex+1];
}
double getDedxFunPronN(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxPron[plndex] + dx/pBin*dedxPron[plndex+1];
}
double getDedxFunDeuP(double *x, double *par)
{ 
	int plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxDeu[plndex] + dx/pBin*dedxDeu[plndex+1];
}
double getDedxFunDeuN(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxDeu[plndex] + dx/pBin*dedxDeu[plndex+1];
}
double getDedxFunTriP(double *x, double *par)
{ 
	int plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxTri[plndex] + dx/pBin*dedxTri[plndex+1];
}
double getDedxFunTriN(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxTri[plndex] + dx/pBin*dedxTri[plndex+1];
}
double getDedxFunHe3P(double *x, double *par)
{ 
	int plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxHe3[plndex] + dx/pBin*dedxHe3[plndex+1];
}
double getDedxFunHe3N(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxHe3[plndex] + dx/pBin*dedxHe3[plndex+1];
}
double getDedxFunHe4P(double *x, double *par)
{ 
	int plndex = (int)((x[0]-pMin)/pBin) ; 
	double dx = x[0] - pMin - plndex*pBin ;
	return (1. - dx/pBin)*dedxHe4[plndex] + dx/pBin*dedxHe4[plndex+1];
}
double getDedxFunHe4N(double *x, double *par)
{ 
	int plndex = (int)((-pMin - x[0])/pBin) ;
	double dx  = -pMin - x[0] - plndex*pBin ;
	return (1. - dx/pBin)*dedxHe4[plndex] + dx/pBin*dedxHe4[plndex+1];
}

void inputdEdxThLine()
{       
	ifstream ifsElec(particle[3]);
	string tem;
	getline(ifsElec,tem);
	for(int j=0;j<11901;j++) { ifsElec>>tem>>dedxElec[j];  dedxElec[j] *= 1.e-06; }

	ifstream ifsPion(particle[0]);
	string tem1;
	getline(ifsPion,tem1);
	for(int j=0;j<11901;j++) { ifsPion>>tem1>>dedxPion[j];  dedxPion[j] *= 1.e-06; }

	ifstream ifsKaon(particle[1]);
	string tem2;
	getline(ifsKaon,tem2);
	for(int j=0;j<11901;j++) { ifsKaon>>tem2>>dedxKaon[j]; dedxKaon[j] *= 1.e-06; }

	ifstream ifsPro(particle[2]);
	string tem3;
	getline(ifsPro,tem3);
	for(int j=0;j<11901;j++) { ifsPro>>tem3>>dedxPron[j]; dedxPron[j] *= 1.e-06; }

	ifstream ifsDeu(particle[4]);
	string tem4;
	getline(ifsDeu,tem4);
	for(int j=0;j<11901;j++) { ifsDeu>>tem4>>dedxDeu[j]; dedxDeu[j] *= 1.e-06; }

	ifstream ifsHe3(particle[5]);
	string tem5;
	getline(ifsHe3,tem5);
	for(int j=0;j<11901;j++) { ifsHe3>>tem5>>dedxHe3[j]; dedxHe3[j] *= 1.e-06; }

	ifstream ifsTri(particle[6]);
	string tem6;
	getline(ifsTri,tem6);
	for(int j=0;j<11901;j++) { ifsTri>>tem6>>dedxTri[j]; dedxTri[j] *= 1.e-06; }

	ifstream ifsHe4(particle[7]);
	string tem7;
	getline(ifsHe4,tem7);
	for(int j=0;j<11901;j++) { ifsHe4>>tem7>>dedxHe4[j]; dedxHe4[j] *= 1.e-06; }
}


