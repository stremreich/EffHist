// Eff 1D Histogram Plotting Code
// Stephen Trembath-Reichert

#include "TH2.h"
#include "TH1F.h"
#include "stdio.h"

bool EXCLUDEDCHAMBERS[20][36] = {
  //       5         10        15        20        25        30        35 
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}, //ME+42
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+41
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}, //ME+32
  {0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+31
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+22
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+21
  {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+13
  {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}, //ME+12
  {0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}, //ME+11B
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+11A
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-11A
  {0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-11B
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0}, //ME-12
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-13
  {0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-21
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-22
  {0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-31
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-32
  {1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-41
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0}  //ME-42
};

void EffHist(const char *LCTname, const char *SEGname) {

  // load CMS Style
  //gROOT->ProcessLine(" .L CMSStyle.C");
  //gROOT->ProcessLine("CMSStyle()");
  //gROOT->LoadMacro("CMSStyle.C");
  //CMSStyle();

  gStyle->SetHistFillColor(5);
  gStyle->SetOptStat(11111);
  gStyle->SetStatX(0.4);
  gStyle->SetStatY(0.7);

  TFile fLCT(LCTname);
  TFile fSEG(SEGname);
  TFile fout("EffHist.root", "RECREATE");

  TH2F *histinLCT = (TH2F*)fLCT.Get("LCTEff");
  TH2F *histinSEG = (TH2F*)fSEG.Get("SEGEff");

  TH1F *histLCT = new TH1F("EffLCT", "LCT Efficiency", 100, 0, 100);
  TH1F *histSEG = new TH1F("EffSEG", "Segment Efficiency", 100, 0, 100);

  TH1F *histcutLCT = new TH1F("EffLCTcut", "LCT Efficiency", 60, 70, 100);
  TH1F *histcutSEG = new TH1F("EffSEGcut", "Segment Efficiency", 60, 70, 100);

  TH1F *histLCTexc = new TH1F("EffLCTexc", "LCT Eff. (Excluding known problems)", 100, 0, 100);
  TH1F *histSEGexc = new TH1F("EffSEGexc", "SEG Eff. (Excluding known problems)", 100, 0, 100);

  TH1F *histcutLCTexc = new TH1F("EffLCTcutexc", "LCT Eff. (Excluding known problems)", 60, 70, 100);
  TH1F *histcutSEGexc = new TH1F("EffSEGcutexc", "SEG Eff. (Excluding known problems)", 60, 70, 100);

  // Plots for each ring

  TH1F *histcut42LCT = new TH1F("42LCTcut", "ME4/2", 60, 70, 100);
  TH1F *histcut42SEG = new TH1F("42SEGcut", "ME4/2", 60, 70, 100);

  TH1F *histcut41LCT = new TH1F("41LCTcut", "ME4/1", 60, 70, 100);
  TH1F *histcut41SEG = new TH1F("41SEGcut", "ME4/1", 60, 70, 100);

  TH1F *histcut32LCT = new TH1F("32LCTcut", "ME3/2", 60, 70, 100);
  TH1F *histcut32SEG = new TH1F("32SEGcut", "ME3/2", 60, 70, 100);

  TH1F *histcut31LCT = new TH1F("31LCTcut", "ME3/1", 60, 70, 100);
  TH1F *histcut31SEG = new TH1F("31SEGcut", "ME3/1", 60, 70, 100);

  TH1F *histcut22LCT = new TH1F("22LCTcut", "ME2/2", 60, 70, 100);
  TH1F *histcut22SEG = new TH1F("22SEGcut", "ME2/2", 60, 70, 100);

  TH1F *histcut21LCT = new TH1F("21LCTcut", "ME2/1", 60, 70, 100);
  TH1F *histcut21SEG = new TH1F("21SEGcut", "ME2/1", 60, 70, 100);

  TH1F *histcut13LCT = new TH1F("13LCTcut", "ME1/3", 60, 70, 100);
  TH1F *histcut13SEG = new TH1F("13SEGcut", "ME1/3", 60, 70, 100);

  TH1F *histcut12LCT = new TH1F("12LCTcut", "ME1/3", 60, 70, 100);
  TH1F *histcut12SEG = new TH1F("12SEGcut", "ME1/3", 60, 70, 100);

  TH1F *histcut11bLCT = new TH1F("11bLCTcut", "ME1/1B", 60, 70, 100);
  TH1F *histcut11bSEG = new TH1F("11bSEGcut", "ME1/1B", 60, 70, 100);

  TH1F *histcut11aLCT = new TH1F("11aLCTcut", "ME1/1A", 60, 70, 100);
  TH1F *histcut11aSEG = new TH1F("11aSEGcut", "ME1/1A", 60, 70, 100);

  // Special plots

  TH1F *histcut42topLCT = new TH1F("42topLCTcut", "ME4_2_top", 60, 70, 100);
  TH1F *histcut42topSEG = new TH1F("42topSEGcut", "ME4_2_top", 60, 70, 100);

  TH1F *histcut42restLCT = new TH1F("42restLCTcut", "Rest_of_ME4_2", 60, 70, 100);
  TH1F *histcut42restSEG = new TH1F("42restSEGcut", "Rest_of_ME4_2", 60, 70, 100);

  TH1F *histcut11aoddLCT = new TH1F("11aoddLCTcut", "ME1_1A_odd", 60, 70, 100);
  TH1F *histcut11aoddSEG = new TH1F("11aoddSEGcut", "ME1_1A_odd", 60, 70, 100);

  TH1F *histcut11aevenLCT = new TH1F("11aevenLCTcut", "ME1_1A_even", 60, 70, 100);
  TH1F *histcut11aevenSEG = new TH1F("11aevenSEGcut", "ME1_1A_even", 60, 70, 100);

  // Fill hists
  double LCTpt = 0;
  double SEGpt = 0;
  for(int xbin = 1; xbin <= (histinLCT->GetNbinsX()); xbin++) {
    for(int ybin = 1; ybin <= (histinLCT->GetNbinsY()); ybin++) {
      if(!((ybin == 2 || ybin == 4 || ybin == 6 || ybin == 15 || ybin == 17 || ybin == 19) && (xbin > 18))) { 
	LCTpt = histinLCT->GetBinContent(xbin, ybin);
	SEGpt = histinSEG->GetBinContent(xbin, ybin);

	histLCT->Fill(LCTpt);
	histSEG->Fill(SEGpt);
	histcutLCT->Fill(LCTpt);
        histcutSEG->Fill(SEGpt);

	// Fill ring hists

	switch(ybin) {
	case 1:
	case 20:
	  histcut42LCT->Fill(LCTpt);
	  histcut42SEG->Fill(SEGpt);

	  if(xbin == 7 ||
	     xbin == 8 ||
	     xbin == 9 ||
	     xbin == 10 ||
	     xbin == 11 ||
	     xbin == 12 ||
	     xbin == 13) {
	    histcut42topLCT->Fill(LCTpt);
	    histcut42topSEG->Fill(SEGpt);
	  } else {
	    histcut42restLCT->Fill(LCTpt);
	    histcut42restSEG->Fill(SEGpt);
	  }

	  break;
	case 2:
	case 19:
	  histcut41LCT->Fill(LCTpt);
	  histcut41SEG->Fill(SEGpt);
	  break;
	case 3:
	case 18:
	  histcut32LCT->Fill(LCTpt);
	  histcut32SEG->Fill(SEGpt);
	  break;
	case 4:
	case 17:
	  histcut31LCT->Fill(LCTpt);
	  histcut31SEG->Fill(SEGpt);
	  break;
	case 5:
	case 16:
	  histcut22LCT->Fill(LCTpt);
	  histcut22SEG->Fill(SEGpt);
	  break;
	case 6:
	case 15:
	  histcut21LCT->Fill(LCTpt);
	  histcut21SEG->Fill(SEGpt);
	  break;
	case 7:
	case 14:
	  histcut13LCT->Fill(LCTpt);
	  histcut13SEG->Fill(SEGpt);
	  break;
	case 8:
	case 13:
	  histcut12LCT->Fill(LCTpt);
	  histcut12SEG->Fill(SEGpt);
	  break;
	case 9:
	case 12:
	  histcut11bLCT->Fill(LCTpt);
	  histcut11bSEG->Fill(SEGpt);
	  break;
	case 10:
	case 11:
	  histcut11aLCT->Fill(LCTpt);
	  histcut11aSEG->Fill(SEGpt);

	  if(xbin%2) {
	    histcut11aoddLCT->Fill(LCTpt);
	    histcut11aoddSEG->Fill(SEGpt);
	  } else {
	    histcut11aevenLCT->Fill(LCTpt);
	    histcut11aevenSEG->Fill(SEGpt);
	  }

	  break;
	default :
	  cout << "Something's wrong!" << endl;
	}

	if(!(EXCLUDEDCHAMBERS[(ybin-20)*-1][xbin-1])) {
	  //cout << "Chamber[" << ybin-1 << "][" << xbin-1 << "] not excluded.\n";
	  histLCTexc->Fill(LCTpt);
	  histSEGexc->Fill(SEGpt);
	  histcutLCTexc->Fill(LCTpt);
	  histcutSEGexc->Fill(SEGpt);
	} else {
	  //cout << "Chamber[" << ybin-1 << "][" << xbin-1 << "] excluded.\n";
	  //cout << "LCTEff: " << LCTpt << endl;
	  //cout << "SEGEff: " << SEGpt << endl;
	}
      }
    }
  }


  TPaveText *pt1 = new TPaveText(0.165, 0.93, 0.315, 1.0, "NDC");
  pt1->SetFillStyle(0);
  pt1->SetBorderSize(0);
  pt1->SetTextSize(0.04);
  pt1->SetTextAlign(12);
  pt1->AddText("CMS Preliminary 2018");

  TPaveText *pt2 = new TPaveText(0.835, 0.93, 0.965, 1.0, "NDC");
  pt2->SetFillStyle(0);
  pt2->SetBorderSize(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(12);
  pt2->AddText("#sqrt{s}=13 TeV");

  

  TIter next(gDirectory->GetList());
  TObject *obj;
  int LCTorSEG = 0;
  while ((obj=next())) {
    if (obj->InheritsFrom("TH1")) {
      TH1 *h = (TH1*)obj;
      if (LCTorSEG % 2) {
	h->GetXaxis()->SetTitle("Chamber Segment Efficiency (%)");
      } else {
	h->GetXaxis()->SetTitle("Chamber LCT Efficiency (%)");
      }
      h->GetYaxis()->SetTitle("No. chambers");
      //h->SetStats(1);
      LCTorSEG += 1;
    }
  }

  // Draw and save histograms
  TCanvas *histLCTCanvas = new TCanvas();
  histLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histLCTCanvas->SaveAs("histLCT.png");

  TCanvas *histcutLCTCanvas = new TCanvas();
  histcutLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcutLCTCanvas->SaveAs("histcutLCT.png");

  TCanvas *histLCTexcCanvas = new TCanvas();
  histLCTexc->Draw();
  pt1->Draw();
  pt2->Draw();
  histLCTexcCanvas->SaveAs("histLCTexc.png");

  TCanvas *histcutLCTexcCanvas = new TCanvas();
  histcutLCTexc->Draw();
  pt1->Draw();
  pt2->Draw();
  histcutLCTexcCanvas->SaveAs("histcutLCTexc.png");

  TCanvas *histSEGCanvas = new TCanvas();
  histSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histSEGCanvas->SaveAs("histSEG.png");

  TCanvas *histcutSEGCanvas = new TCanvas();
  histcutSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcutSEGCanvas->SaveAs("histcutSEG.png");

  TCanvas *histSEGexcCanvas = new TCanvas();
  histSEGexc->Draw();
  pt1->Draw();
  pt2->Draw();
  histSEGexcCanvas->SaveAs("histSEGexc.png");

  TCanvas *histcutSEGexcCanvas = new TCanvas();
  histcutSEGexc->Draw();
  pt1->Draw();
  pt2->Draw();
  histcutSEGexcCanvas->SaveAs("histcutSEGexc.png");

  // ring plots

  TCanvas *histcut42LCTCanvas = new TCanvas();
  histcut42LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut42LCTCanvas->SaveAs("histcut42LCT.png");

  TCanvas *histcut42SEGCanvas = new TCanvas();
  histcut42SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut42SEGCanvas->SaveAs("histcut42SEG.png");

  TCanvas *histcut41LCTCanvas = new TCanvas();
  histcut41LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut41LCTCanvas->SaveAs("histcut41LCT.png");

  TCanvas *histcut41SEGCanvas = new TCanvas();
  histcut41SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut41SEGCanvas->SaveAs("histcut41SEG.png");

  TCanvas *histcut32LCTCanvas = new TCanvas();
  histcut32LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut32LCTCanvas->SaveAs("histcut32LCT.png");

  TCanvas *histcut32SEGCanvas = new TCanvas();
  histcut32SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut32SEGCanvas->SaveAs("histcut32SEG.png");

  TCanvas *histcut31LCTCanvas = new TCanvas();
  histcut31LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut31LCTCanvas->SaveAs("histcut31LCT.png");

  TCanvas *histcut31SEGCanvas = new TCanvas();
  histcut31SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut31SEGCanvas->SaveAs("histcut31SEG.png");

  TCanvas *histcut22LCTCanvas = new TCanvas();
  histcut22LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut22LCTCanvas->SaveAs("histcut22LCT.png");

  TCanvas *histcut22SEGCanvas = new TCanvas();
  histcut22SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut22SEGCanvas->SaveAs("histcut22SEG.png");

  TCanvas *histcut21LCTCanvas = new TCanvas();
  histcut21LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut21LCTCanvas->SaveAs("histcut21LCT.png");

  TCanvas *histcut21SEGCanvas = new TCanvas();
  histcut21SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut21SEGCanvas->SaveAs("histcut21SEG.png");

  TCanvas *histcut13LCTCanvas = new TCanvas();
  histcut13LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut13LCTCanvas->SaveAs("histcut13LCT.png");

  TCanvas *histcut13SEGCanvas = new TCanvas();
  histcut13SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut13SEGCanvas->SaveAs("histcut13SEG.png");

  TCanvas *histcut12LCTCanvas = new TCanvas();
  histcut12LCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut12LCTCanvas->SaveAs("histcut12LCT.png");

  TCanvas *histcut12SEGCanvas = new TCanvas();
  histcut12SEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut12SEGCanvas->SaveAs("histcut12SEG.png");

  TCanvas *histcut11bLCTCanvas = new TCanvas();
  histcut11bLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11bLCTCanvas->SaveAs("histcut11bLCT.png");

  TCanvas *histcut11bSEGCanvas = new TCanvas();
  histcut11bSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11bSEGCanvas->SaveAs("histcut11bSEG.png");

  TCanvas *histcut11aLCTCanvas = new TCanvas();
  histcut11aLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11aLCTCanvas->SaveAs("histcut11aLCT.png");

  TCanvas *histcut11aSEGCanvas = new TCanvas();
  histcut11aSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11aSEGCanvas->SaveAs("histcut11aSEG.png");

  // special plots

  TCanvas *histcut42topLCTCanvas = new TCanvas();
  histcut42topLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut42topLCTCanvas->SaveAs("histcut42topLCT.png");

  TCanvas *histcut42topSEGCanvas = new TCanvas();
  histcut42topSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut42topSEGCanvas->SaveAs("histcut42topSEG.png");

  TCanvas *histcut42restLCTCanvas = new TCanvas();
  histcut42restLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut42restLCTCanvas->SaveAs("histcut42restLCT.png");

  TCanvas *histcut42restSEGCanvas = new TCanvas();
  histcut42restSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut42restSEGCanvas->SaveAs("histcut42restSEG.png");

  TCanvas *histcut11aoddLCTCanvas = new TCanvas();
  histcut11aoddLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11aoddLCTCanvas->SaveAs("histcut11aoddLCT.png");

  TCanvas *histcut11aoddSEGCanvas = new TCanvas();
  histcut11aoddSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11aoddSEGCanvas->SaveAs("histcut11aoddSEG.png");

  TCanvas *histcut11aevenLCTCanvas = new TCanvas();
  histcut11aevenLCT->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11aevenLCTCanvas->SaveAs("histcut11aevenLCT.png");

  TCanvas *histcut11aevenSEGCanvas = new TCanvas();
  histcut11aevenSEG->Draw();
  pt1->Draw();
  pt2->Draw();
  histcut11aevenSEGCanvas->SaveAs("histcut11aevenSEG.png");

  fout.Write();
  
}
