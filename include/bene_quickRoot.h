#ifndef BENE_QUICKROOT
#define BENE_QUICKROOT 
#include "bene_algorithm.h"
#include <tuple>

namespace bene {
	template<typename T, int X, int Y>
	TGraph quickTGraph(const std::vector<std::tuple<T,T>> & v)
	{
		const size_t num_elem = v.size();
		TGraph g(num_elem);
		for (size_t i = 0; i < num_elem; ++i)
		{
			g.SetPoint(i, std::get<X-1>(v[i]), std::get<Y-1>(v[i]));
		}
		return g;
	}

	template<typename T, int X, int Y>
	TGraph quickTGraph(const  std::vector<std::tuple<T,T,T>> & v)
	{
		const size_t num_elem = v.size();
		TGraph g(num_elem);
		for (size_t i = 0; i < num_elem; ++i)
		{	
			g.SetPoint(i, std::get<X-1>(v[i]), std::get<Y-1>(v[i]) );
		}
		return g;
	}


	template<typename T, int X, int Y, int Err>
	TGraphErrors quickTGraphError(const  std::vector<std::tuple<T,T,T>> & v)
	{
		const size_t num_elem = v.size();
		TGraphErrors g(num_elem);
		for (size_t i = 0; i < num_elem; ++i)
		{	
			g.SetPoint(i, std::get<X-1>(v[i]), std::get<Y-1>(v[i]) );
			g.SetPointError(i,0, std::get<Err-1>(v[i]));
		}
		return g;
	}

	template<typename T, int bins> 
	TH1F quickHist(const std::vector<T> & v)
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

	template<typename T, int bins, int col> 
	TH1F quickHist(const std::vector<std::tuple<T,T>> & v)
	{
		const size_t num_elem = v.size();
		double min_v = min<T,col-1>(v);
		double min = min_v < 0 ? min_v * 1.1 : min_v * 0.9;
		double max_v = max<T,col-1>(v);
		double max = max_v < 0 ? max_v * 0.9 : max_v * 1.1;
		TH1F h("", "", bins, min, max);
		for(const auto & e : v) {
			h.Fill(std::get<col-1>(e));
		}
		return h;
	}

	template<typename T, int bins, int col> 
	TH1F quickHist(const std::vector<std::tuple<T,T,T>> & v)
	{
		const size_t num_elem = v.size();
		double min_v = min<T,col-1>(v);
		double min = min_v < 0 ? min_v * 1.1 : min_v * 0.9;
		double max_v = max<T,col-1>(v);
		double max = max_v < 0 ? max_v * 0.9 : max_v * 1.1;
		TH1F h("", "", bins, min, max);
		for(const auto & e : v) {
			h.Fill(std::get<col-1>(e));
		}
		return h;
	}

	
}
#endif