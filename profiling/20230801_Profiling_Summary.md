# まとめ

## テスト環境

* 私のMacパソコン
	* MacBook Pro (13-inch, 2019, Two Thunderbolt 3 ports)
	* macOS 12.6.1
	* プロセッサ：1.4 GHz Quad-Core Intel Core i5
	* メモリー：8 GB 2133 MHz LPDDR3
	* Windows 仮想マシン (Windows 10 Home) (Parallels Desktop for Mac)
* Visual Studioの`デバッグ開始`でテストしていた
	* Visual Studio Community 2022 (64-bit) Version 17.5.1

## テスト項目

* デバッグ x64 fps制限なし (`デバッグ fpsなし`)
* リリース x64 fps制限なし (`リリース fpsなし`)
* デバッグ x64 60fps制限あり (`デバッグ fps60`)
* リリース x64 60fps制限あり (`リリース fps60`)

## テストの流れ

`タイトル` -> `ゲーム` -> `エンディング` -> `ゲーム` -> `エンディング` -> `タイトル` -> `ゲーム` -> `エンディング`

## データ (コミット`0705750`と比べる)

### fps (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | -------------  | -------------- | ------------ |
| タイトル       | 898 (<span style="color:blue">+361</span>) | 1258 (<span style="color:blue">+347</span>) | 73 (<span style="color:blue">+10</span>) | 62 (<span style="color:red">-1</span>) |
| ゲーム         | 174 (<span style="color:red">-308</span>) | 423 (<span style="color:red">-262</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング    | 1268 (<span style="color:blue">+583</span>) | 715 (<span style="color:blue">+20</span>) | 61 (<span style="color:green">0</span>) | 63 (<span style="color:blue">+2</span>) |
| ゲーム         | 104 (<span style="color:red">-364</span>) | 455 (<span style="color:red">-259</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング    | 697 (<span style="color:blue">+32</span>) | 633 (<span style="color:red">-159</span>) | 61 (<span style="color:green">0</span>) | 62 (<span style="color:blue">+1</span>) |
| タイトル       | 942 (<span style="color:blue">+167</span>) | 1017 (<span style="color:blue">+163</span>) | 64 (<span style="color:blue">+3</span>) | 68 (<span style="color:blue">+7</span>) |
| ゲーム        | 118 (<span style="color:red">-375</span>) | 466 (<span style="color:red">-199</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:blue">+1</span>) |
| エンディング   | 789 (<span style="color:blue">+159</span>) | 729 (<span style="color:red">-15</span>) | 62 (<span style="color:blue">+1</span>) | 61 (<span style="color:green">0</span>) |

#### 比較分析

* `タイトル`と`エンディング`のfpsは以前より大体良かったまたは同じようになりましたが、`ゲーム`は以前より明らかに悪かったです
	* 原因の一つは、今プログラム全般的にシステム化とかモジュール化をしていまして、パフォーマンスが若干減るに決まっていると思います
	* 他には、`GE`フォルダのコードの最適化があまり良くないと思います(例えば、画面外の`GE::Render::Image`はカリングされていない)

### メモリー (mb) (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | ------------- | -------------- | ------------ |
| タイトル       | 11.8 (<span style="color:red">+0.9</span>) | 10.7 (<span style="color:red">+0.7</span>) | 11.6 (<span style="color:red">+1.1</span>) | 10.4 (<span style="color:red">+0.7</span>) |
| ゲーム         | 15.8 (<span style="color:red">+2.8</span>) | 12.8 (<span style="color:red">+0.9</span>) | 15.1 (<span style="color:red">+2.3</span>) | 12.6 (<span style="color:red">+0.9</span>) |
| エンディング    | 22.6 (<span style="color:red">+2.2</span>) | 21.4 (<span style="color:red">+3.5</span>) | 21.9 (<span style="color:red">+2.5</span>) | 20.5 (<span style="color:red">+2.3</span>) |
| ゲーム         | 18.2 (<span style="color:blue">-2.4</span>) | 14.9 (<span style="color:blue">-3.6</span>) | 18.0 (<span style="color:blue">-1.7</span>) | 14.6 (<span style="color:blue">-4.1</span>) |
| エンディング    | 22.5 (<span style="color:red">+2.1</span>) | 20.9 (<span style="color:red">+2.5</span>)| 22.3 (<span style="color:red">+2.7</span>) | 20.3 (<span style="color:red">+1.7</span>) |
| タイトル       | 19.7 (<span style="color:blue">-1.0</span>) | 16.8 (<span style="color:blue">-1.8</span>) | 18.9 (<span style="color:blue">-0.9</span>) | 17.5 (<span style="color:blue">-1.4</span>) |
| ゲーム        | 16.2 (<span style="color:blue">-4.5</span>) | 14.1 (<span style="color:blue">-4.4</span>) | 16.4 (<span style="color:blue">-3.2</span>) | 13.7 (<span style="color:blue">-5.1</span>) |
| エンディング   | 23.1 (<span style="color:red">+2.6</span>) | 22.1 (<span style="color:red">+3.8</span>) | 22.7 (<span style="color:red">+3.2</span>) | 20.9 (<span style="color:red">+2.2</span>) |

#### 比較分析

* 第一回の`タイトル`と`ゲーム`と`エンディング`のメモリーは以前より増やしました
	* 以前、画像のサイズは半分であって、描画する時二倍に拡大するという形でした。今、画像のサイズのまま描画します。つまり、現在画像のサイズは以前の二倍になりました
* 第二回以降の`タイトル`と`ゲーム`のメモリーは以前より減りました
	* 以前、フォントはグローバル変数で、生成したらずっと破棄しないでした。今、フォントは使わない際に破棄されます。そういうわけで、`エンディング`で使うフォントは他のシーンへ遷移する時に破棄されて、メモリーを減らします

### CPU (%) (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | ------------- | -------------- | ------------ |
| タイトル       | 11.3 (<span style="color:blue">-7.8</span>) | 15.7 (<span style="color:blue">-7.3</span>) | 1.8 (<span style="color:blue">-0.9</span>) | 1.8 (<span style="color:blue">-1.1</span>) |
| ゲーム         | 24.1 (<span style="color:red">+0.3</span>) | 19.7 (<span style="color:blue">-4.1</span>) | 10.4 (<span style="color:red">+5.5</span>) | 4.1 (<span style="color:red">+0.3</span>) |
| エンディング    | 16.9 (<span style="color:blue">-0.9</span>) | 14.4 (<span style="color:blue">-9.0</span>) | 3.1 (<span style="color:blue">-1.8</span>) | 2.7 (<span style="color:blue">-1.0</span>) |
| ゲーム         | 23.9 (<span style="color:blue">-0.1</span>) | 20.0 (<span style="color:blue">-3.6</span>) | 10.8 (<span style="color:red">+5.1</span>) | 4.3 (<span style="color:red">+0.5</span>) |
| エンディング    | 16.6 (<span style="color:blue">-7.5</span>) | 12.4 (<span style="color:blue">-11.3</span>) | 3.3 (<span style="color:blue">-1.4</span>) | 2.4 (<span style="color:blue">-1.2</span>) |
| タイトル       | 18.3 (<span style="color:blue">-3.3</span>) | 13.7 (<span style="color:blue">-9.5</span>) | 2.3 (<span style="color:blue">-2.3</span>) | 2.1 (<span style="color:blue">-1.1</span>) |
| ゲーム        | 23.6 (<span style="color:blue">-0.4</span>) | 19.8 (<span style="color:blue">-3.9</span>) | 11.2 (<span style="color:red">+5.6</span>) | 4.2 (<span style="color:red">+0.1</span>) |
| エンディング   | 17.3 (<span style="color:blue">-6.8</span>) | 12.3 (<span style="color:blue">-11.2</span>) | 3.3 (<span style="color:blue">-1.2</span>) | 2.2 (<span style="color:blue">-1.5</span>) |

#### 比較分析

* CPU使用量は以前より大体改善しました
	* これは私の予想外でした。システム化とモジュール化をして、きっとCPU使用量が増えると思いました
	* 以前のゲームエンジンプラグインの中で、このプロジェクトの使わない色々な計算が含まれていたかもしれません
* `ゲーム`のCPU使用量は以前より大きくなりました
	* 今のシステムにいうと、Game Objectの位置の計算とか、Collision Systemの計算は多いと思います
	* 以前、マップは一つのタスクで管理しました。今、マップのタイルは全部独立的なGame Objectになりました
	* `GE`フォルダのコードをもっと最適化したら、CPU使用量が改善できると思います

### プロジェクトのリビルド時間

* デバッグ x64：約131秒 (<span style="color:red">+1秒</span>)
* リリース x64：約114秒 (<span style="color:blue">-5秒</span>)

#### 比較分析

* 大した変化はありません
* でも、以前cppファイルの数は59だしたが、現在総計136(`lib`と`GE`フォルダ：79、その他：57)になりました
	* `lib`と`GE`フォルダ以外のcppファイルはprecompiled header(`src/GE/GEHeader.h`)を使って、コンパイル時間を減らせました