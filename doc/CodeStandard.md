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
* 一般的にポインタの命名規則はポインタではないものと同じである。区別しやすくなりたい場合、`p`+`PascalCase`(例：`pPointer`)という形で命名する。

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
* 初期化の書き方：
	* `T name;`
	* `T name(arg1, arg2);`
		* 文字列を除く(原因は習慣)：
			* `std::string name = "a";`
			* コピー初期化についてのパフォーマンス問題はコンパイラーの`コピー省略`(`Copy Elision`)に任せる
		* また、組み込み型変数の初期化は下記になる：
			* `bool name = true;`
			* `int name = 1;`
			* `float name = 1.0f;`
			* `char name = 'a';`
	* コピーコンストラクター：`T instance2 = instance1;`
	* `T* name = new T(arg1, arg2);`
	* 一般的に`一様初期化`(`Uniform Initialization`)を使わない。でも、場合によって、`auto`を使うことも許す。例えば、
		* `std::vector<int> v{1, 2, 3, 4, 5};`
		* `構造体`：`Vector2 a; a = {1.0f, 2.0f};`とか、`player.Move({1.0f, 2.0f});`とか

## enum

* 一般的に`enum`を使わなくて、`enum class`を使う。
* 例外：局部的な範囲でコードを見やすくなりたい時。

## ヌル

* `NULL`と`0`を使わなくて、`nullptr`を使う。

## ポインタ/参照

* `*`と`&`は型の方に近づけられる：
	* O：`int* a`
	* X：`int *a`
* 一般的にスマートポインタを使う。でも、Rawポインタを使うことも許す。
* 特に、下記の場合にRawポインタを使う：
	* パフォーマンスが大事になる時
		* `GameObject`と`Component`は`unique_ptr`を使って格納されているので、`GameObject`と`Component`をたいていRawポインタまたは参照型で参照する。(ダングリングポインタを防ぐように、`EndOfFrame()`でチェックできる)
	* 局部的な範囲でコードを見やすくなりたい時

## inline

* 必須ではない場合、`inline`を使わない。インラインコードの処理はコンパイラに任せる。
* つまり、`inline`はOne Definition Rule (ODR)だけのために使う。
* 例外：数式とかの小さいヘルパー関数は習慣的に`inline`を付ける。

## include

* `#include`の使う時、`std`または`lib`フォルダの中のヘッダーファイルに`<>`を使う。他のヘッダーファイルに`""`を使う。例えば、
	* `#include <string>`
	* `#include <magic_enum.hpp>`
	* `#include "GE/GEHeader.h"`

## auto

* 一般的に明示的なタイプを書く。でも、`auto`を使うことも許す。
* 特に、下記の場合に`auto`を使う：
	* タイプの名前は長すぎる時
	* タイプがはっきり分かる時(例：`auto& image = gameObject.AddComponent<GE::Render::Image>();`)
	* 範囲for文の変数宣言
	* 構造化束縛(Structured Bindings)

## マクロ

* できれば、`マクロ`の使用を避ける。使いたい時、下記の点に気を付ける：
	* 名前を重複しやすくないように命名する(例：名前空間の名前をプレフィックスとして付ける)
	* できれば、`マクロ`の使用完了後、`#undef`で`マクロ`の定義を取り消す

## プリコンパイル済みヘッダー

* `src/CommonHeader.h`
* 主にいくつかのよく使われるSTLのヘッダーファイルとGameEngineのヘッダーファイルを含んでいる

## その他
* `using namespace`の使用を避ける：
	* `.h`で使わないように
	* 使いたい時、なるべく局部的な範囲で使う
* 列挙する時、できれば、最後のものも`,`を付ける(例：列挙型の値)
* `typedef`より、`using`を使う
* Visual Studioのフィルダー機能を使わない