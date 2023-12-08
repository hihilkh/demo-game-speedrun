# パーティクルシステムについて

## 仕組み

* `ParticleSystem`：パーティクルを制御するコンポーネントです。Unityの`ParticleSystem`と似ています。
* `Internal/ParticleComponent`：`ParticleSystem`を再生する時、生成したパーティクル`GameObject`につけるコンポーネントです。`ParticleSystem`に設定した`Module`の`UpdateFunc`のインスタンスを持ち、毎フレームに呼び出します。
* `CoreConfig`：`ParticleSystem`にとっては必須な設定です。
* `Module`：パーティクルのある振る舞いを制御する設定です。Unityの`Particle System Modules`と似ています。下記の`Module`を支援しています。
	* `ColorOverLifetimeModule`：時間に従ってパーティクルの色を変更します。
	* `EmissionModule`：パーティクルの生成位置と回転角度を決めます。
		* `RectEmissionModule`：四角形範囲でパーティクルを生成する`EmissionModule`です。
	* `VelocityModule`：パーティクルの速度を制御します。
* `ModuleSet`：`Module`を集めるクラスです。
* `UpdateFunc`：毎フレームにパーティクルに与える効果です。
* `ParticleSystemFile`：`ParticleSystem`の設定の資料を格納するJsonファイルです。
* `ParticleSystemLoader`：`ParticleSystemFile`を読み込んでからデシリアライズして`CoreConfig`と`ModuleSet`を生成するクラスです。読み込んだ`ParticleSystemFile`をキャッシュして管理することもします。

## `ParticleSystemFile`の仕組みの例

```json
{
	"core": {
		"img": "./data/Image/WallFragment.png",		// パーティクルの画像のソース
		"render_priority": 200,						// パーティクルの画像の描画優先度
		"no_of_particle": 20,						// ParticleSystemを再生する時、パーティクルの生成数
		"life": 1.0									// パーティクルの生存期間
	},
	"modules": [									// Moduleの配列
		{
			"name": "rectEmission",					// Moduleの名前。IDのような役割です
			"detail": {								// Moduleの詳細。Moduleによって違います
				"rot": {
					"from": 0.0,
					"to": 360.0
				},
				"x": -16.0,
				"y": -16.0,
				"w": 32.0,
				"h": 32.0
			}
		}
	]
}
```

## 参照

* [ソースコード](../../src/GE/Particle)
* [`ParticleSystem`の使用例](../../src/Prefab/Map/Tile/WeakWallTilePrefab.cpp)
* [`ParticleSystemFile`の例](../../data/ParticleSystem/WeakWallBreak.json)