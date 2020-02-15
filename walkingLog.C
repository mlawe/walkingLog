#include <string>

void plot_time_hist(TTree * tree, const char * vars, const char * cuts, const char * yaxis)
{
  int n = tree->Draw(vars,cuts,"goff");
  TGraph *g = new TGraph(n, tree->GetV2(), tree->GetV1());
  g->SetMarkerStyle(20);
  g->GetXaxis()->SetTimeDisplay(1);
  g->GetXaxis()->SetTimeOffset(0);
  g->GetXaxis()->SetTitle("Date (UTC)");
  g->GetYaxis()->SetTitle(yaxis);
  g->GetXaxis()->SetTitleSize(.05);
  g->GetYaxis()->SetTitleSize(.05);
  g->GetXaxis()->SetLabelSize(.05);
  g->GetYaxis()->SetLabelSize(.05);
  g->SetTitle("");
  g->Draw();
}

void plot_text(double x, double y, const char * text)
{
  TText *t = new TText(x, y, text);
  t->SetNDC();
  t->SetTextAlign(22);
  t->SetTextColor(kRed+2);
  t->SetTextFont(43);
  t->SetTextSize(50);
  t->SetTextAngle(45);
  t->Draw();
}

void walkingLog(std::string year, double goal=500.0)
{
  const double km_to_miles = 0.621371;
  const double goal_distance = goal;

  TString dir = gSystem->UnixPathName(__FILE__);
  dir.ReplaceAll("walkingLog.C","");
  dir.ReplaceAll("/./","/");
  ifstream infile;
  infile.open(Form("%swalks_log_%s.txt",dir.Data(),year.c_str()));

  int date;
  double km, miles, totalmiles;

  TFile *output = new TFile("output.root","RECREATE");
  TTree *tree = new TTree("tree","tree");

  tree->Branch("date",&date);
  tree->Branch("km", &km);
  tree->Branch("miles",&miles);
  tree->Branch("totalmiles", &totalmiles);
  
  while (infile >> date >> km){
    miles = km * km_to_miles;
    totalmiles+=miles;
    tree->Fill();
  }
  tree->Write();

  std::cout << totalmiles << " miles" << std::endl;
  
  //plot the progress
  TCanvas * c = new TCanvas("c","c",1400,700);

  plot_time_hist(tree, "totalmiles:date", "", "Mileage");
  plot_text(.35,.5, Form("Total: %.1f miles", totalmiles));
  plot_text(.7,.5, Form("%.1f%% of target", 100*totalmiles/goal_distance, goal_distance));

  output->Close();
}
