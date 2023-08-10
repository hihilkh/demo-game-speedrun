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

## データ (コミット`4806962`(ブランチ`profiling/after_engine_reconstruct`)と比べる)

### fps (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | -------------  | -------------- | ------------ |
| タイトル       | 1358 (<span style="color:blue">+460</span>) | 1496 (<span style="color:blue">+238</span>) | 72 (<span style="color:red">-1</span>) | 68 (<span style="color:blue">+6</span>) |
| ゲーム         | 217 (<span style="color:blue">+43</span>) | 616 (<span style="color:blue">+193</span>) | 61 (<span style="color:green">0</span>) | 60 (<span style="color:red">-1</span>) |
| エンディング    | 568 (<span style="color:red">-700</span>) | 947 (<span style="color:blue">+232</span>) | 60 (<span style="color:red">-1</span>) | 64 (<span style="color:blue">+1</span>) |
| ゲーム         | 135 (<span style="color:blue">+31</span>) | 657 (<span style="color:blue">+202</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング    | 1088 (<span style="color:blue">+391</span>) | 965 (<span style="color:blue">+332</span>) | 60 (<span style="color:red">-1</span>) | 61 (<span style="color:red">-1</span>) |
| タイトル       | 1184 (<span style="color:blue">+242</span>) | 1258 (<span style="color:blue">+241</span>) | 61 (<span style="color:red">-3</span>) | 61 (<span style="color:red">-7</span>) |
| ゲーム        | 143 (<span style="color:blue">+25</span>) | 716 (<span style="color:blue">+250</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング   | 1090 (<span style="color:blue">+301</span>) | 673 (<span style="color:red">-56</span>) | 62 (<span style="color:green">0</span>) | 62 (<span style="color:blue">+1</span>) |

#### 比較分析

* `ゲーム`シーンのfpsは以前より大体改善しました
* ですが、予想外になぜか`タイトル`と`エンディング`シーンのfpsも以前より大体改善しました

### メモリー (mb) (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | ------------- | -------------- | ------------ |
| タイトル       | 12.0 (<span style="color:red">+0.2</span>) | 10.7 (<span style="color:green">0</span>) | 11.6 (<span style="color:green">0</span>) | 10.3 (<span style="color:blue">-0.1</span>) |
| ゲーム         | 15.5 (<span style="color:blue">-0.3</span>) | 13.1 (<span style="color:red">+0.3</span>) | 15.0 (<span style="color:blue">-0.1</span>) | 12.5 (<span style="color:blue">-0.1</span>) |
| エンディング    | 19.2 (<span style="color:blue">-3.4</span>) | 20.7 (<span style="color:blue">-0.7</span>) | 21.4 (<span style="color:blue">-0.5</span>) | 19.1 (<span style="color:blue">-1.4</span>) |
| ゲーム         | 17.5 (<span style="color:blue">-0.7</span>) | 15.7 (<span style="color:red">+0.8</span>) | 17.6 (<span style="color:blue">-0.4</span>) | 14.1 (<span style="color:blue">-0.5</span>) |
| エンディング    | 22.8 (<span style="color:red">+0.3</span>) | 21.1 (<span style="color:red">+0.2</span>) | 22.0 (<span style="color:blue">-0.3</span>) | 20.4 (<span style="color:red">+0.1</span>) |
| タイトル       | 19.0 (<span style="color:blue">-0.7</span>) | 16.2 (<span style="color:blue">-0.6</span>) | 18.8 (<span style="color:blue">-0.1</span>) | 17.1 (<span style="color:blue">-0.4</span>) |
| ゲーム        | 16.4 (<span style="color:red">+0.2</span>) | 13.8 (<span style="color:blue">-0.3</span>) | 16.4 (<span style="color:green">0</span>) | 13.6 (<span style="color:blue">-0.1</span>) |
| エンディング   | 22.7 (<span style="color:blue">-0.4</span>) | 21.0 (<span style="color:blue">-1.1</span>) | 22.5 (<span style="color:blue">-0.2</span>) | 20.7 (<span style="color:blue">-0.2</span>) |

#### 比較分析

* 大した変化はありません

### CPU (%) (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | ------------- | -------------- | ------------ |
| タイトル       | 15.3 (<span style="color:red">+4.0</span>) | 11.9 (<span style="color:blue">-3.8</span>) | 2.3 (<span style="color:red">+0.5</span>) | 1.8 (<span style="color:green">0</span>) |
| ゲーム         | 24.3 (<span style="color:red">+0.2</span>) | 19.4 (<span style="color:blue">-0.3</span>) | 9.8 (<span style="color:blue">-0.6</span>) | 3.6 (<span style="color:blue">-0.5</span>) |
| エンディング    | 20.6 (<span style="color:red">+3.7</span>) | 14.6 (<span style="color:red">+0.2</span>) | 3.1 (<span style="color:green">0</span>) | 2.1 (<span style="color:blue">-0.6</span>) |
| ゲーム         | 24.0 (<span style="color:red">+0.1</span>) | 18.8 (<span style="color:blue">-1.2</span>) | 10.9 (<span style="color:red">+0.1</span>) | 3.6 (<span style="color:blue">-0.7</span>) |
| エンディング    | 16.8 (<span style="color:blue">-0.2</span>) | 14.7 (<span style="color:red">+2.3</span>) | 3.3 (<span style="color:green">0</span>) | 2.2 (<span style="color:blue">-0.2</span>) |
| タイトル       | 19.0 (<span style="color:red">+0.7</span>) | 9.0 (<span style="color:blue">-4.7</span>) | 2.5 (<span style="color:red">+0.2</span>) | 1.9 (<span style="color:blue">-0.2</span>) |
| ゲーム        | 23.8 (<span style="color:red">+0.2</span>) | 18.2 (<span style="color:blue">-1.6</span>) | 10.7 (<span style="color:blue">-0.5</span>) | 3.5 (<span style="color:blue">-0.7</span>) |
| エンディング   | 16.8 (<span style="color:blue">-0.5</span>) | 15.3 (<span style="color:red">+3.0</span>) | 3.7 (<span style="color:red">+0.4</span>) | 2.0 (<span style="color:blue">-0.2</span>) |

#### 比較分析

* 結論が出せません