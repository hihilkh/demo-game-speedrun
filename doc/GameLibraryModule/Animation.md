[![en](https://img.shields.io/badge/lang-en-red.svg)](./Animation.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./Animation.jp.md)

# About Animation System

* To control animation of a `GameObject`.
* The features are very limited. It only supports changing the images.

## Structures

* `AnimationSystem` : Record all references (to be precise, raw pointers) of all `Animator` components of the scene, and call `OnAnimationUpdate()` method on each frame to update the `Animator` components.
* `Animator` : The component that controls animation, like the `Animator` in Unity. However, the behaviour of a `Animator` cannot be changed by other component (e.g., changing the animation to play). The behaviour of a `Animator` can be controlled by `AnimationDecision` only. From this point of view, it is more closer to the `Animation Blueprint` in Unreal.
* `AnimationDecision` : An abstract class that decide which `AnimationClip` to play. It is necessary to write a derived class when using. It is similar to a combination of `Event Graph` and `Anim Graph` of `Animation Blueprint` in Unreal.
* `AnimationClip` : A class that store `AnimationKey` data. Each `AnimationClip` can be viewed as one animation. It is similar to the `AnimationClip` in Unity.
* `AnimationKey` : A keyframe of an animation.
* `AnimationClipSet` : A class that store all the `AnimationClip` of a `GameObject`.
* `AnimationFile` : A JSON file that stores all the data of a `AnimationClipSet`.
* `AnimationClipSetLoader` : A loader to load a `AnimationFile` and deserialize to a `AnimationClipSet` instance. It also caches and manages the loaded `AnimationFile`.

## Example of a `AnimationFile`

```json
{
    "clips": [					// Array of AnimationClips
        {
            "name": "idle",			// The name of the AnimationClip. Work as an ID
            "loop": true,			// Is it a loop animation?
            "frames": [				// The AnimationKeys corresponding to number of frame
                {
                    "start_frame": 0,		// The starting number of frame
                    "key": {			// The details of the AnimationKey
                        "anim_type": 0,		// The interpolation type to next AnimationKey. 0 : No interpolation, 1 : Linear
                        "img_src_rect": {	// The details of image's Rect
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

## References

* [Source Code](../../src/GE/Animation)
* [Example of `Animator`](../../src/Prefab/Character/Player/PlayerPrefab.cpp)
* [Example of `AnimationDecision`](../../src/Character/Player/PlayerAnimationDecision.cpp)
* [Example of `AnimationFile`](../../data/Animation)