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
| タイトル       | 1565 (<span style="color:blue">+667</span>) | 2231 (<span style="color:blue">+973</span>) | 62 (<span style="color:red">-11</span>) | 71 (<span style="color:blue">+9</span>) |
| ゲーム         | 172 (<span style="color:red">-2</span>) | 982 (<span style="color:blue">+559</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング    | 676 (<span style="color:red">-592</span>) | 1296 (<span style="color:blue">+581</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:red">-2</span>) |
| ゲーム         | 137 (<span style="color:blue">+33</span>) | 891 (<span style="color:blue">+436</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング    | 1023 (<span style="color:blue">+326</span>) | 825 (<span style="color:blue">+192</span>) | 61 (<span style="color:green">0</span>) | 62 (<span style="color:green">0</span>) |
| タイトル       | 1261 (<span style="color:blue">+319</span>) | 1028 (<span style="color:blue">+11</span>) | 61 (<span style="color:red">-3</span>) | 64 (<span style="color:red">-4</span>) |
| ゲーム        | 143 (<span style="color:red">+25</span>) | 623 (<span style="color:blue">+157</span>) | 61 (<span style="color:green">0</span>) | 61 (<span style="color:green">0</span>) |
| エンディング   | 988 (<span style="color:blue">+199</span>) | 939 (<span style="color:blue">+210</span>) | 60 (<span style="color:red">-2</span>) | 61 (<span style="color:green">0</span>) |

#### 比較分析

* 主に画像のカリング機能のおかげで、パフォーマンスが改善されました
* 今回の測りは、シーンごとのデータ変化は激しすぎると思います。この結果はあまり正しくないかもしれません。でも、以前よりパフォーマンスが良くなることは明らかだと思います。

### メモリー (mb) (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | ------------- | -------------- | ------------ |
| タイトル       | 11.9 (<span style="color:red">+0.1</span>) | 10.7 (<span style="color:green">0.0</span>) | 11.6 (<span style="color:green">0.0</span>) | 10.3 (<span style="color:blue">-0.1</span>) |
| ゲーム         | 15.4 (<span style="color:blue">-0.4</span>) | 13.0 (<span style="color:red">+0.2</span>) | 15.2 (<span style="color:red">+0.1</span>) | 12.2 (<span style="color:blue">-0.4</span>) |
| エンディング    | 22.4 (<span style="color:blue">-0.2</span>) | 20.8 (<span style="color:blue">-0.6</span>) | 22.2 (<span style="color:red">+0.3</span>) | 20.2 (<span style="color:blue">-0.3</span>) |
| ゲーム         | 17.1 (<span style="color:blue">-1.1</span>) | 14.3 (<span style="color:blue">-0.6</span>) | 17.7 (<span style="color:blue">-0.3</span>) | 14.1 (<span style="color:blue">-0.5</span>) |
| エンディング    | 22.5 (<span style="color:green">0.0</span>) | 20.5 (<span style="color:blue">-0.4</span>) | 22.2 (<span style="color:blue">-0.1</span>) | 20.3 (<span style="color:green">0.0</span>) |
| タイトル       | 19.1 (<span style="color:blue">-0.6</span>) | 15.3 (<span style="color:blue">-1.5</span>) | 18.7 (<span style="color:blue">-0.2</span>) | 15.9 (<span style="color:blue">-1.6</span>) |
| ゲーム        | 16.3 (<span style="color:red">+0.1</span>) | 13.4 (<span style="color:blue">-0.7</span>) | 16.3 (<span style="color:blue">-0.1</span>) | 13.5 (<span style="color:blue">-0.2</span>) |
| エンディング   | 22.7 (<span style="color:blue">-0.4</span>) | 21.4 (<span style="color:blue">-0.7</span>) | 22.6 (<span style="color:blue">-0.1</span>) | 21.0 (<span style="color:red">+0.1</span>) |

#### 比較分析

* 大した変化はありません

### CPU (%) (平均)

|               | デバッグ fpsなし | リリース fpsなし | デバッグ fps60 | リリース fps60 |
| ------------- | ------------- | ------------- | -------------- | ------------ |
| タイトル       | 15.5 (<span style="color:red">+4.2</span>) | 12.4 (<span style="color:blue">-3.3</span>) | 1.8 (<span style="color:green">0.0</span>) | 1.5 (<span style="color:blue">-0.3</span>) |
| ゲーム         | 24.1 (<span style="color:green">0.0</span>) | 15.6 (<span style="color:blue">-4.1</span>) | 9.5 (<span style="color:blue">-0.9</span>) | 3.6 (<span style="color:blue">-0.5</span>) |
| エンディング    | 15.0 (<span style="color:blue">-1.9</span>) | 12.6 (<span style="color:blue">-1.8</span>) | 2.5 (<span style="color:blue">-0.6</span>) | 2.3 (<span style="color:blue">-0.4</span>) |
| ゲーム         | 24.1 (<span style="color:red">+0.2</span>) | 17.1 (<span style="color:blue">-2.9</span>) | 9.1 (<span style="color:blue">-1.7</span>) | 3.8 (<span style="color:blue">-0.5</span>) |
| エンディング    | 16.9 (<span style="color:red">+0.3</span>) | 13.0 (<span style="color:red">+0.6</span>) | 3.1 (<span style="color:blue">-0.2</span>) | 2.6 (<span style="color:red">+0.2</span>) |
| タイトル       | 16.9 (<span style="color:blue">-1.4</span>) | 10.1 (<span style="color:blue">-3.6</span>) | 2.4 (<span style="color:red">+0.1</span>) | 1.8 (<span style="color:blue">-0.3</span>) |
| ゲーム        | 24.3 (<span style="color:red">+0.7</span>)| 17.5 (<span style="color:blue">-2.3</span>) | 10.0 (<span style="color:blue">-1.2</span>) | 4.1 (<span style="color:blue">-0.1</span>) |
| エンディング   | 16.5 (<span style="color:blue">-0.8</span>) | 13.5 (<span style="color:red">+1.2</span>) | 2.9 (<span style="color:blue">-0.4</span>) | 2.4 (<span style="color:red">+0.2</span>) |

#### 比較分析

* ちょっと改善しました