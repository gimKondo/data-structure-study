#include "array.h"

//------------------------------
// Arrayを使ったDeque(双方向キュー)
//------------------------------
struct ArrayDeque {
  Array arr; // backing array
  int base;
  int size;

  // 構築
  ArrayDeque(int len): arr(Array(len)), base(0), size(0) {}

  // get/set
  T get(int i) {
    return arr[(base + i) % arr.length];
  }
  void set(int i, T x) {
    arr[(base + i) % arr.length] = x;
  }

  // 要素の追加
  // iが小さい(0に近い)とき、大きい(sizeに近い)ときに効率よくなるように実装
  void add(int i, T x) {
    if (size + 1 > arr.length) {
      cout << "resize by add i:[" << i << "] x:[" << x << "] size:[" << size << "]" << endl;
      resize();
    }
    // iが小さい場合
    if (i < size / 2) {
      // 0～i-1番目を左に1つずらす
      base = (base == 0) ? arr.length - 1 : base - 1;
      for (int k = 0; k <= i - 1; ++k) {
        arr[(base + k) % arr.length] = arr[(base + k + 1) % arr.length];
      }
    }
    // iが大きい場合
    else {
      // 0～i-1番目を右に1つずらす
      for (int k = size; k > i; --k) {
        arr[(base + k) % arr.length] = arr[(base + k - 1) % arr.length];
      }
    }
    arr[(base + i) % arr.length] = x;
    ++size;
  }

  // 要素の削除
  void remove(int i) {
    // iが小さい場合
    if (i < size / 2) {
      // 0～i-1番目を右に1つずらす
      for (int k = i; k > 0; --k) {
        arr[(base + k) % arr.length] = arr[(base + k - 1) % arr.length];
      }
      // 起点を1個右にずらす
      base = (base + 1) % arr.length;
    }
    // iが大きい場合
    else {
      // i+1～size-1番目を左に1つずらす
      for (int k = i; k < size - 1; ++k) {
        arr[(base + k) % arr.length] = arr[(base + k + 1) % arr.length];
      }
      // 要素をずらしたので、起点はずらさなくて良い
    }
    --size;
    if (arr.length > size * 3) {
      cout << "resize by remove i:[" << i << "] size:[" << size << "]" << endl;
      resize();
    }
  }

  // デバッグ用print
  void print() {
    for (int i = 0; i < size; ++i) {
      cout << arr[(base + i) % arr.length];
    }
    cout << endl;
  }

private:
  // backing arrayのリサイズ(拡張or縮小)
  void resize() {
    // 2倍のサイズのbacking arrayを作成(サイズ0の場合はサイズ1で作成)
    Array newArr(max(size * 2, 1));
    // 要素のコピー
    for (int i = 0; i < size; ++i) {
      newArr[i] = arr[i];
    }
    // 新しく作った配列に置き換え
    arr = newArr;
    base = 0;
  }
};

int main() {
  auto deque = ArrayDeque(12);
  T iniArr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  for(int i = 0; i < sizeof(iniArr)/sizeof(*iniArr); ++i) {
    deque.add(i, iniArr[i]);
  }
  deque.print();

  deque.remove(2);
  deque.print();
  deque.add(4, 'x');
  deque.print();
  deque.add(3, 'y');
  deque.print();
  deque.add(3, 'z');
  deque.print();
}
