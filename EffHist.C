// Eff 1D Histogram Plotting Code
// Stephen Trembath-Reichert

#include "TH2.h"
#include "TH1F.h"
#include "stdio.h"

bool EXCLUDEDCHAMBERS[20][36] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+42
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+41
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+32
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+31
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+22
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+21
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+13
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+12
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+11B
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME+11A
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-11A
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-11B
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-12
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-13
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-21
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-22
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-31
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-32
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ME-41
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  //ME-42
};

void EffHist(const char *LCTname, const char *SEGname) {

  // load CMS Style
  gROOT->ProcessLine(" .L CMSStyle.C");
  gROOT->ProcessLine("CMSStyle()");
  gROOT->LoadMacro("CMSStyle.C");
  CMSStyle();

  TFile fLCT(LCTname);
  TFile fSEG(SEGname);
  TFile fout("EffHist.root", "RECREATE");

  TH2F *histinLCT = (TH2F*)fLCT.Get("LCTEff");
  TH2F *histinSEG = (TH2F*)fSEG.Get("SEGEff");

  TH1F *histLCT = new TH1F("EffLCT", "", 100, 0, 100);
  TH1F *histSEG = new TH1F("EffSEG", "", 100, 0, 100);

  TH1F *histcutLCT = new TH1F("EffLCTcut", "", 40, 80, 100);
  TH1F *histcutSEG = new TH1F("EffSEGcut", "", 40, 80, 100);

  TH1F *histLCTexc = new TH1F("EffLCTexc", "", 100, 0, 100);
  TH1F *histSEGexc = new TH1F("EffSEGexc", "", 100, 0, 100);

  TH1F *histcutLCTexc = new TH1F("EffLCTcutexc", "", 40, 80, 100);
  TH1F *histcutSEGexc = new TH1F("EffSEGcutexc", "", 40, 80, 100);

  // Fill hists
  double LCTpt = 0;
  double SEGpt = 0;
  for(int xbin = 1; xbin <= (hist2017LCT->GetNbinsX()); xbin++) {
    for(int ybin = 1; ybin <= (hist2017LCT->GetNbinsY()); ybin++) {
      if(!((ybin == 2 || ybin == 4 || ybin == 6 || ybin == 15 || ybin == 17 || ybin == 19) && (xbin > 18))) { 
	LCTpt = histinLCT->GetBinContent(xbin, ybin);
	SEGpt = histinSEG->GetBinContent(xbin, ybin);

	histLCT->Fill(LCTpt);
	histSEG->Fill(SEGpt);
	histcutLCT->Fill(LCTpt);
        histcutSEG->Fill(SEGpt);

	if(!(EXCLUDEDCHAMBERS[ybin-1][xbin-1])) {
	  histLCTexc->Fill(LCTpt);
	  histSEGexc->Fill(SEGpt);
	  histcutLCTexc->Fill(LCTpt);
	  histcutSEGexc->Fill(SEGpt);
	}
      }
    }
  }


  TPaveText *pt1 = new TPaveText(0.165, 0.94, 0.315, 0.99, "NDC");
  pt1->SetFillStyle(0);
  pt1->SetBorderSize(0);
  pt1->SetTextSize(0.04);
  pt1->SetTextAlign(12);
  pt1->AddText("CMS Preliminary 2017");

  TPaveText *pt2 = new TPaveText(0.835, 0.94, 0.965, 0.99, "NDC");
  pt2->SetFillStyle(0);
  pt2->SetBorderSize(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(12);
  pt2->AddText("#sqrt{s}=13 TeV");

  TIter next(gDirectory->GetList());
  TObject *obj;
  while ((obj=next())) {
    if (obj->InheritsFrom("TH1")) {
      TH1 *h = (TH1*)obj;
      h->GetXaxis()->SetTitle("Chamber Efficiency (%)");
      h->GetYaxis()->SetTitle("Number of CSCs");
      h->SetStats(1);
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

  fout.Write();
  
}
