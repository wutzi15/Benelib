#ifndef BENE_ALGORITHM
#define BENE_ALGORITHM 
#include <vector>
#include <algorithm>
#include <tuple>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TROOT.h"


namespace bene {
	
	template<typename T>
	T min(const std::vector<T> &v){
		return *std::min_element(v.begin(), v.end());
	}

	template<typename T>
	T max(const std::vector<T> &v){
		return *std::max_element(v.begin(), v.end());
	}

	template<typename T, int X, int Y>
	TGraph quickTGraph(const std::vector<T> & v);

	template<typename T, int X, int Y, int Err>
	TGraphErrors quickTGraphError(const std::vector<T> & v);

	template<typename T, int bins> 
	TH1F quickHist(const std::vector<T> & v);
}

#endif