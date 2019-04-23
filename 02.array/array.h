#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;

// templateを使うと本質でない部分が煩雑になるのでTを固定
using T = char;

// ベースとなる配列(backing array)
struct Array{
  T* ptr;
  int length;

  // 構築
  Array(int len): ptr(new T[length]), length(len) {}

  // 要素へのアクセス
  T& operator[](int i) {
    assert(i >= 0 && i < length);
    return ptr[i];
  }

  // 割り当て
  // - srcの配列は以降使えなくなる
  // - 実用的なコンテナとしては一般的な仕様・実装ではないこと付記しておく
  Array& operator=(Array& src) {
    if (ptr != NULL) delete[] ptr;
    ptr = src.ptr;
    src.ptr = NULL;
    length = src.length;
    return *this;
  }

  // デバッグ用print
  void print() const {
    for(int i = 0; i < length; ++i) {
      if (ptr[i] == 0) break;
      cout << ptr[i];
    }
    cout << endl;
  }
};

