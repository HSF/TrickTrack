

void tricktrack_profiling_cpuVriemannmatrixsize() {

  TColor *color0 = new TColor(2000,  27. / 256., 158. / 256., 119. / 256.);
  TColor *color1 = new TColor(2001, 217. / 256.,  95. / 256.,   2. / 256.);
  TColor *color2 = new TColor(2002, 117. / 256., 112. / 256., 179. / 256.);

  TColor *color3 = new TColor(2015, 228. / 256.,  26. / 256.,  28. / 256.);
  TColor *color4 = new TColor(2011,  55. / 256., 126. / 256., 184. / 256.);
  TColor *color5 = new TColor(2012,  77. / 256., 175. / 256.,  74. / 256.);
  TColor *color6 = new TColor(2013, 152. / 256.,  78. / 256., 163. / 256.);
  TColor *color7 = new TColor(2014, 255. / 256., 127. / 256.,   0. / 256.);


    
  gStyle->SetOptStat(0);

  std::string filename1 = "tricktrack_profiling_cpuVriemannmatrixsize_32.dat";
  std::string filename2 = "tricktrack_profiling_cpuVriemannmatrixsize_08.dat";
  int riemann_matrix_size;
  double cpu_duration;

  std::vector<double>* riemann_matrix_size_32_Vec = new std::vector<double>();
  std::vector<double>* cpu_duration_microsec_32_Vec = new std::vector<double>();

  std::vector<double>* riemann_matrix_size_08_Vec = new std::vector<double>();
  std::vector<double>* cpu_duration_microsec_08_Vec = new std::vector<double>();

  TH2F* h1 = new TH2F("h1", ";Number of Hits in Fit;CPU time [#mus]", 32, 0.5, 33.5, 100, 0.1, 15);
  TH2F* h2 = new TH2F("h2", ";Number of Hits in Fit;CPU time [#mus]", 32, 0.5, 33.5, 100, 0.1, 15);

  std::ifstream in;
  in.open(filename1);
  while (in.good()) {
    in >> riemann_matrix_size >> cpu_duration;
    riemann_matrix_size_32_Vec->push_back(riemann_matrix_size);
    cpu_duration_microsec_32_Vec->push_back(cpu_duration * 1e6);
    h1->Fill(riemann_matrix_size, cpu_duration * 1e6);
  }

  std::ifstream in2;
  in2.open(filename2);
  while (in2.good()) {
    in2 >> riemann_matrix_size >> cpu_duration;
    riemann_matrix_size_08_Vec->push_back(riemann_matrix_size);
    cpu_duration_microsec_08_Vec->push_back(cpu_duration * 1e6);
    h2->Fill(riemann_matrix_size, cpu_duration * 1e6);
  }

  TProfile*  g;

  TCanvas* C1 = new TCanvas();
  gPad->SetTicks();
  C1->SetLogy();
  C1->SetGrid(true);

  g = h1->ProfileX("tpf1", 1, -1, "s");
  //TGraph* g = new TGraph(riemann_matrix_size_08_Vec->size(), &((*riemann_matrix_size_08_Vec)[0]), &((*cpu_duration_microsec_08_Vec)[0]));
  //g->GetXaxis()->SetLimits(0, 32);
  //g->GetYaxis()->SetRange(0.01, 20.);
  //g->GetHistogram()->SetMaximum(20.);
  g->SetMarkerColor(2015);
  g->SetMarkerStyle(8);
  g->SetMarkerSize(1);
  g->SetLineColor(kGray + 3);
  g->SetTitle(";Number of Hits in Fit;CPU time [#mus]");
  g->Draw("E");

  //g = new TGraph(riemann_matrix_size_32_Vec->size(), &((*riemann_matrix_size_32_Vec)[0]), &((*cpu_duration_microsec_32_Vec)[0]));
  g = h2->ProfileX("tpf2", 1, -1, "s");
  g->SetMarkerColor(2014);
  g->SetLineColor(kGray + 3);
  //g->SetLineWidth(0);
  g->SetMarkerStyle(21);
  g->SetMarkerSize(1);
  g->SetTitle(";Number of Hits in Fit;CPU time [#mus]");
  g->Draw("same e");


  TLegend *leg = new TLegend(
 0.688172    ,//        X1 point in NDC coordinates
 0.266481    ,//        Y1 point in NDC coordinates
 0.91816     ,//        X2 point in NDC coordinates
 0.494893    ,//        Y2 point in NDC coordinates

  
   NULL,"brNDC");

	leg->SetHeader("Riemann Fit");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->SetTextSize(0.04);

  TLegendEntry* entry;
   entry =leg->AddEntry("NULL","Max. matrix dim.: 8","lpf");

   entry->SetLineWidth(0);
   entry->SetMarkerColor(2014);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.03);

   entry=leg->AddEntry("NULL","Max. matrix dim.: 32","lpf");

   entry->SetLineWidth(0);
   entry->SetMarkerColor(2015);
   entry->SetMarkerStyle(8);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.03);

    TLegendEntry *header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
   header->SetTextSize(.04);
	leg->Draw();


     TLatex t(.12,0.92," on Intel(R) Core(TM) Skylake CPU @ 2.2GHz");
    t.SetTextSize(0.025);
   t.SetNDC(kTRUE);
   t.Draw();





  C1->Print("tricktrack_profiling_cpuVriemannmatrixsize.png");
  C1->Print("tricktrack_profiling_cpuVriemannmatrixsize.pdf");
  C1->Print("tricktrack_profiling_cpuVriemannmatrixsize.svg");


gApplication->Terminate();
}
