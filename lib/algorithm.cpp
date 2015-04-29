#include "algorithm.h"

template<typename T, int X, int Y>
TGraph bene::quickTGraph(const std::vector<T> & v)
{
	const size_t num_elem = v.size();
	TGraph g(num_elem);
	for (size_t i = 0; i < num_elem; ++i)
	{
		g.SetPoint(i, std::get<X>(v), std::get<Y>(v));
	}
	return g;
}

template<typename T, int X, int Y, int Err>
TGraph bene::quickTGraphError(const std::vector<T> & v)
{
	const size_t num_elem = v.size();
	TGraphErrors g(num_elem);
	for (size_t i = 0; i < num_elem; ++i)
	{
		g.SetPoint(i, std::get<X>(v), std::get<Y>(v));
		g.SetPointError(i, std::get<Err>(v));
	}
	return g;
}

template<typename T, int bins> 
TH1F bene::quickHist(const std::vector<T> & v) 
{
	const size_t num_elem = v.size();
	double min_v = min(v);
	double min = min_v < 0 ? min_v * 1.1 : min_v * 0.9;
	double max_v = max(v);
	double max = max_v < 0 ? max_v * 0.9 : max_v * 1.1;
	TH1F h("", "", bins, min, max);
	for(const auto & e : v) {
		h.Fill(e);
	}
}