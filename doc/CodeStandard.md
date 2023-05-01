# コードスタンダード

## 命名規則

| 種類 | スタイル | 備考 |
| ---- | ---- | ---- |
| 名前空間 | PascalCase | |
| クラス / 構造体 | PascalCase | |
| 列挙型 | PascalCase | |
| 列挙型の値 | PascalCase | |
| 関数 / メンバ関数 | PascalCase | |
| 変数 / メンバ変数 | camelCase | |
| ローカル変数 | camelCase | |
| 関数の引数 | camelCase | |
| マクロ | snake_case(大文字) | 例：DEBUG_COLLIDER |
| Visual Studio開発環境によってのプリプロセッサの定義 | snake_case(大文字)、プレフィックス `_` | 例：_DEBUG |

* `const`や`static`などが命名規則に影響を与えない
* `ハンガリアン記法`を使わない
* 一般的に`_`を使わない。下記の例外を許す：
	* 上記の`snake_case`スタイル。
	* 似ているものを明らかに分けるように(**変数**のみを許す)。この場合、`_`の後で`PascalCase`で命名する。
		* 例：`command_Hit`、`command_Jump`

## スペース（空白文字、改行、インデント）についてのルール
``` cpp
namespace MyNamespace
{
	class MyClass
	{
	public:
		enum class MyEnum
		{
			Left,
			Right,
		};

		void MyMethod(MyEnum myEnum)
		{
			if (true) {
				for (int i = 0; i < 10; ++i) {

				}
			} else {

			}

			switch (myEnum) {
				case MyEnum::Left:
					break;
				case MyEnum::Right: {
					int localVariable = 1;
					break;
				}
				default:
					break;
			}
		}
	};
}
```

* `{`と`}`を省略しないように
* 場合によって、複数の行を一行にまとめることを許す

## クラス / 構造体

* 一般的に`クラス`を使う。データを持つや渡すだけの場合、`構造体`を使う
* 一般的に`構造体`の変数と関数は全て`public`になる(場合によって、`private`になることも許す)。そのため、一般的に`構造体`の中のアクセス指定子を省略する
* `クラス`の中のアクセス指定子を省略しないように
* `クラス`の関数定義を`.cpp`に入れる。下記の場合は`.h`に入れる：
	* = 0
	* = default
	* = delete
	* ゲッター
	* セッター
	* {}
	* 簡単なコンストラクター定義/関数定義(主に`.cpp`ファイルを作成したくない場合)
* 関数オーバライド時、`override`キーワードを付ける
	* デストラクタを除く
* コンストラクターの使い方：
	* `T name;`
	* `T name(arg1, arg2);`
		* 文字列を除く：
			* `std::string name = "a";`
		* また、組み込み型変数の初期化は下記になる：
			* `bool name = true;`
			* `int name = 1;`
			* `float name = 1.0f;`
			* `char name = 'a';`
	* コピーコンストラクター：`T instance2 = instance1;`
	* `T* name = new T(arg1, arg2);`
* 一般的に`一様初期化`を使わない
	* 場合によって、使うことを許す。例えば、`std::vector<int> v{1, 2, 3, 4, 5};`

## プリコンパイル済みヘッダー

* `src/CommonHeader.h`
* 主にいくつかのよく使われるSTLのヘッダーファイルとGameEngineのヘッダーファイルを含んでいる

## その他

* `*`と`&`は型の方に近づけられる：
	* O：`int* a`
	* X：`int *a`
* `using namespace`の使用を避ける：
	* `.h`で使わないように
	* 使いたい時、局部的な範囲で使う
* 一般的に`enum class`を使う。下記の場合に`enum`を使える：
	* 局部的な範囲でコードを見やすくなりたい時
* 一般的に明示的なタイプを書く。でも、場合によって、`auto`を使うことも許す。それに、下記の場合に`auto`を使う：
	* タイプの名前は長すぎる時
	* 範囲for文の変数宣言
* ヌルポインタの場合は、`nullptr`を使う。`NULL`と`0`を使わないように
* 列挙する時、できれば、最後のものも`,`を付ける(例：列挙型の値)
* できれば、`マクロ`の使用を避ける。使いたい時、下記の点に気を付ける：
	* 名前を重複しやすくないように命名する(例：名前空間の名前をプレフィックスとして付ける)
	* できれば、`マクロ`の使用完了後、`#undef`で`マクロ`の定義を取り消す
* `typedef`より、`using`を使う