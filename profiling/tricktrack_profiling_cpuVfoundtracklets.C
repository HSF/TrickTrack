
void tricktrack_profiling_cpuVfoundtracklets() {
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
//gStyle->SetCanvasDefH(100);
//gStyle->SetCanvasDefW(100); 
  //gStyle->SetPaperSize(40, 40);

  std::string filename = "tricktrack_profiling_cpuVfoundtracklets.dat";
  int foundTracklets;
  double cpu_duration;
  int barrel0_size;

  std::vector<double>* foundTrackletsVec = new std::vector<double>();
  std::vector<double>* cpu_duration_microsec_Vec = new std::vector<double>();

  std::ifstream in;
  in.open(filename);
  while (in.good()) {
    in >> foundTracklets >> cpu_duration >> barrel0_size;
    foundTrackletsVec->push_back(foundTracklets);
    cpu_duration_microsec_Vec->push_back(cpu_duration * 1e6);
  }

  TGraph* g = new TGraph(foundTrackletsVec->size(), &((*foundTrackletsVec)[0]), &((*cpu_duration_microsec_Vec)[0]));
  g->SetMarkerColor(kBlue+2);
  g->SetMarkerSize(1);
  g->SetMarkerStyle(20);
  g->SetLineWidth(2);
  //gStyle->SetLabelOffset(0.07, "X");
  gStyle->SetTitleXOffset(1.4);



  g->SetTitle(";Found Tracklets;CPU time [#mus]");

    TLatex t(.15,0.92," on Intel(R) Core(TM) Skylake CPU @ 2.2GHz");
    t.SetTextSize(0.025);
   t.SetNDC(kTRUE);

  TCanvas* C1 = new TCanvas();
  C1->SetLogy();
  C1->SetLogx();
  C1->SetGrid(true);
  g->Draw();
  t.Draw();
  C1->Print("tricktrack_profiling_cpuVfoundtracklets.png");
  C1->Print("tricktrack_profiling_cpuVfoundtracklets.pdf");
  C1->Print("tricktrack_profiling_cpuVfoundtracklets.svg");

  TCanvas* C2 = new TCanvas();
  C1->SetLogy(false);
  C1->SetLogx(false);
  C1->SetGrid(true);
  g->Draw();
  t.Draw();
  C2->Print("tricktrack_profiling_cpuVfoundtracklets_loglin.png");
  C2->Print("tricktrack_profiling_cpuVfoundtracklets_loglin.pdf");
  C2->Print("tricktrack_profiling_cpuVfoundtracklets_loglin.svg");
 gApplication->Terminate(); 


}
