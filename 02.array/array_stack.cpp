// ArrayStack
#include "array.h"

//------------------------------
// Arrayを使ったStack
//------------------------------
struct ArrayStack {
  Array arr; // backing array
  int size;  // 値の入っている配列の長さ

  // 構築
  // len: backing arrayの長さ
  ArrayStack(int len): arr(Array(len)), size(0) {}

  // get/set
  T get(int i) {
    return arr[i];
  }
  void set(int i, T x) {
    arr[i] = x;
  }

  // 要素の追加
  void add(int i, T x) {
    cout << "add size:[" << size << "]" << endl;
    // backing arrayが足りなくなったら拡張
    if (size + 1 > arr.length) {
      cout << "resize by add i:[" << i << "] x:[" << x << "] size:[" << size << "]" << endl;
      resize();
    }
    for (int j = size; j > i; j--) {
      // i以降の要素を1個ずつ後ろにずらす
      arr[j] = arr[j - 1];
    }
    // iの位置にxを入れる
    arr[i] = x;
    ++size;
  }

  // 要素の削除
  void remove(int i) {
    for (int j = i; j < size - 1; ++j) {
      // i以降を1個ずつ前にずらす
      arr[j] = arr[j + 1];
    }
    --size;
    // backing arrayのサイズが実際に要素数の3倍以上になったら縮小
    if (arr.length >= size * 3) {
      cout << "resize by remove i:[" << i << "] size:[" << size << "]" << endl;
      resize();
    }
  }

private:
  // backing arrayのリサイズ(拡張or縮小)
  void resize() {
    // 2倍のサイズのbacking arrayを作成(サイズ0の場合はサイズ1で作成)
    Array newArr(max(2 * size, 1));
    // 要素のコピー
    for (int i = 0; i < size; ++i) {
      newArr[i] = arr[i];
    }
    // 新しく作った配列に置き換え
    arr = newArr;
  }
};

int main() {
  auto stack = ArrayStack(6);
  T iniArr[] = {'b', 'r', 'e', 'd'};
  for(int i = 0; i < sizeof(iniArr)/sizeof(*iniArr); ++i) {
    stack.add(i, iniArr[i]);
  }
  stack.arr.print();

  stack.add(2, 'e');
  stack.arr.print();
  stack.add(5, 'r');
  stack.arr.print();
  stack.add(5, 'e');
  stack.arr.print();
  stack.remove(4);
  stack.arr.print();
  stack.remove(4);
  stack.arr.print();
  // 
  stack.remove(4);
  stack.arr.print();
  stack.set(2, 'i');
  stack.arr.print();
  return 0;
}
