#include "array.h"

//------------------------------
// Arrayを使ったQueue
//------------------------------
struct ArrayQueue {
  Array arr; // backing array
  int base;
  int size;

  // 構築
  ArrayQueue(int len): arr(Array(len)), base(0), size(0) {}

  // 末尾に値を追加
  void add(T x) {
    // backing arrayが足りなくなったら拡張
    if (size + 1 > arr.length) {
      cout << "resize by add x:[" << x << "] size:[" << size << "]" << endl;
      resize();
    }
    // 循環配列の起点(base)から見て末尾に当たる場所に値を格納
    // (p34の図を参照)
    arr[(base + size) % arr.length] = x;
    ++size;
  }

  // 最初に格納した(=最も古い)値を削除
  void remove() {
    T x = arr[base];
    // baseを1個ずらす
    // (p34の図を参照)
    base = (base + 1) % arr.length;
    --size;
    // backing arrayのサイズが実際に要素数の3倍以上になったら縮小
    if (arr.length >= size * 3) {
      cout << "resize by remove x:[" << x << "] size:[" << size << "]" << endl;
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
  auto queue = ArrayQueue(6);
  T iniArr[] = {'0', '1', 'a', 'b', 'c'};
  for(int i = 0; i < sizeof(iniArr)/sizeof(*iniArr); ++i) {
    queue.add(iniArr[i]);
  }
  queue.remove();
  queue.remove();
  queue.print();

  queue.add('d');
  queue.print();
  queue.add('e');
  queue.print();
  queue.remove();
  queue.print();
  queue.add('f');
  queue.print();
  queue.add('g');
  queue.print();
  queue.add('h');
  queue.print();
  queue.remove();
  queue.print();
  return 0;
}
