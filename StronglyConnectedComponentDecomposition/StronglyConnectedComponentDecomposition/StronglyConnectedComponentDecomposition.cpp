// StronglyConnectedComponentDecomposition.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"


#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
#endif

// #include <bits/stdc++.h>

using namespace std;

class StronglyConnectedComponentDecomposition
{
private:
	int V; // 頂点数
	vector<vector<int>> G; // グラフの隣接リスト表現
	vector<vector<int>> rG; // 辺の向きを逆にしたグラフ
	vector<int> vs; // 帰りがけ順の並び
	vector<bool> used; // すでに調べたか

	void dfs( int v ) {
		used[v] = true;
		for( int i = 0; i < G[v].size(); i++ ) {
			if( !used[G[v][i]] ) dfs( G[v][i] );
		}
		vs.push_back( v );
	}
	void rdfs( int v, int k ) {
		used[v] = true;
		cmp[v] = k;
		for( int i = 0; i < rG[v].size(); i++ ) {
			if( !used[rG[v][i]] ) rdfs( rG[v][i], k );
		}
	}

public:
	vector<int> cmp; // 属する強連結成分のトポロジカル順序
	StronglyConnectedComponentDecomposition( int N = 0 ) {
		V = N;
		G = vector<vector<int>>( V );
		rG = vector<vector<int>>( V );
		used = vector<bool>( V );
		cmp = vector<int>( V );
	}
	void add_edge( int from, int to ) {
		G[from].push_back( to );
		rG[to].push_back( from );
	}
	
	int scc() {
		used = vector<bool>( V );
		vs.clear();
		for( int v = 0; v < V; v++ ) {
			if( !used[v] ) dfs( v );
		}
		used = vector<bool>( V );
		int k = 0;
		for( int i = vs.size() - 1; i >= 0; i-- ) {
			if( !used[vs[i]] ) rdfs( vs[i], k++ );
		}
		return k;
	}
};

int main() {
	long long int V, E;
	cin >> V >> E;
	StronglyConnectedComponentDecomposition SCCD( V );
	for( size_t i = 0; i < E; i++ ) {
		int s, t;
		cin >> s >> t;
		SCCD.add_edge( s, t );
	}
	SCCD.scc();
	long long int N;
	cin >> N;
	for( size_t i = 0; i < N; i++ ) {
		int u, v;
		cin >> u >> v;
		cout << (SCCD.cmp[u] == SCCD.cmp[v]) << endl;
	}
	return 0;
}
