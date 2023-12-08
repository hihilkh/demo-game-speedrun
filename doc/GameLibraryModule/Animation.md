# アニメーションシステムについて

* ゲームのアニメーションを表現するシステムです。
* 機能はすごく限ります。画像を変えることだけ支援します。

## 仕組み

* `AnimationSystem`：シーンの中のすべての`Animator`コンポーネントの参照(厳密に言うと生ポインタ)を記録し、毎フレームに`OnAnimationUpdate()`関数を行い、`Animator`を更新します。
* `Animator`：アニメーションを制御するコンポーネントです。Unityの`Animator`と似ています。ただし、他のコンポーネントから`Animator`の再生アニメーションを変えることができません。`AnimationDecision`しか`Animator`を制御できません。このポイントから言うと、Unrealの`Animation Blueprint`ともっと似ていると思います。
* `AnimationDecision`：どの`AnimationClip`を再生することを決める抽象クラスです。使いたい時、継承クラスを作ることが必要です。Unrealの`Animation Blueprint`の`Event Graph`と`Anim Graph`の組み合わせと似ています。
* `AnimationClip`：`AnimationKey`の資料を格納し、一つのアニメーションに構成するクラスです。Unityの`AnimationClip`と似ています。
* `AnimationKey`：アニメーションのキーフレームです。
* `AnimationClipSet`：一つの`GameObject`のすべての`AnimationClip`を集めるクラスです。
* `AnimationFile`：`AnimationClipSet`の資料を格納するJsonファイルです。
* `AnimationClipSetLoader`：`AnimationFile`を読み込んでからデシリアライズして`AnimationClipSet`を生成するクラスです。読み込んだ`AnimationFile`をキャッシュして管理することもします。

## `AnimationFile`の仕組みの例

```json
{
	"clips": [	// AnimationClipの配列
		{
			"name": "idle",	// AnimationClipの名前。IDのような役割です
			"loop": true,	// ループをするかどうか
			"frames": [	// フレームと対応するAnimationKeyの配列
				{
					"start_frame": 0,	// 開始のフレーム
					"key": {	// AnimationKeyの詳細
						"anim_type": 0,	// 次のAnimationKeyとの補間。0：補間しない、1：線形補間
						"img_src_rect": {	// 画像のRect詳細
							"x": 0,
							"y": 0,
							"w": 64,
							"h": 64
						}
					}
				}
			]
		}
	]
}
```

## 参照

* [ソースコード](../../src/GE/Animation)
* [`Animator`の使用例](../../src/Prefab/Character/Player/PlayerPrefab.cpp)
* [`AnimationDecision`の使用例](../../src/Character/Player/PlayerAnimationDecision.cpp)
* [`AnimationFile`の例](../../data/Animation)