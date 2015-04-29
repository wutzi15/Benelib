#include "bene_file.h"
#include "bene_quickRoot.h"
#include "TCanvas.h"

TH1F bene::plotHistFromFile(const std::string & s)
{
	auto v = bene::readToVector<double, 3, 1, 2>(s);
	auto h = bene::quickHist<double, 100,2>(v);
	TCanvas c("","", 500, 500);
	h.Draw();
	c.Print((s+".pdf").c_str());
}

TGraph bene::plotTGraphFromFile(const std::string & s)
{
	auto v = bene::readToVector<double, 3, 1, 2>(s);
	auto g = bene::quickTGraph<double, 1,2>(v);
	TCanvas c("","", 500, 500);
	g.Draw("AL");
	c.Print((s+".pdf").c_str());
}

TGraphErrors bene::plotTGraphErrorsFromFile(const std::string & s)
{
	auto v = bene::readToVector<double, 3, 1, 2,3>(s);
	auto g = bene::quickTGraphError<double, 1,2,3>(v);
	TCanvas c("","", 500, 500);
	g.Draw("AL");
	c.Print((s+".pdf").c_str());
}