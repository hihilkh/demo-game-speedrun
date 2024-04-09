[![en](https://img.shields.io/badge/lang-en-red.svg)](./GameLibraryDetails.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./GameLibraryDetails.jp.md)

# More About Game Library

## Basic Information

* A simple and rough 2D game library.
* Mainly refer to Unity's structure.
* Language : `C++`
* Source Code : [here](../src/GE)
* Namespace : `GE` (To order to keep the names short, some names are given alias (Reference : [here](../src/GE/Utils/TypeDef.h)))

## Structures

* `GameObject` : The basic objects that compose the game. ([Source Code](../src/GE/Core/GameObject.h))
* `Component` : Add to a `GameObject` to add features to it. ([Source Code](../src/GE/Core/Component.h))
* `Scene` : The object that keeps and manages `GameObjects`. When moving from one `Scene` to another `Scene`, all the `GameObjects` of the old `Scene` would be destroyed (disposed). ([Source Code](../src/GE/Scene), [Example](../src/Scene))
* `Transform2D` : The class that represents the position and rotation of a `GameObject`. It does not contain scale for simplicity sake (To prevent shear mapping). A `GameObject` must have one and only one `Transform2D`. `Transform2D` is not a `Component`, which is different from Unity. ([Source Code](../src/GE/Core/Transform2D.h))
* `Image` : The `Component` that render a 2D image. ([Source Code](../src/GE/Render/Image.h))
* `Camera2D` : The `Component` that is responsible to render all the `Images` correctly to the game screen. ([Source Code](../src/GE/Core/Camera2D.h))
* `Prefab` : A preset that groups multiple `GameObjects` and `Components` and can be instantiated as if it is a single object. ([Source Code](../src/GE/Core/Prefab.h), [Example](../src/Prefab))
* Hierarchy of `GameObject` : A `GameObject` can be assigned as another `GameObject`'s `Child`. ([Source Code](../src/GE/Core/GameObject.h))
* `GESafePtr` : You can use `GESafePtr` to prevent the use of 
dangling pointer of `GameObject` or `Component` after they are destroyed. ([Source Code](../src/GE/Memory/GESafePtr.h), Example : [Animator::image](../src/GE/Animation/Animator.h))
* Input System : The system to get user inputs. Currently only keyboard input is supported. ([Source Code](../src/GE/Input))
* `Collider` : The `Component` that can check for collision. ([Source Code](../src/GE/Collision/Collider.h))
* Collision System : The system that is responsible for collision detection and collision response between different `Colliders`. ([Source Code](../src/GE/Collision))
* Animation System : The system to change the rendering of an `Image` along time. ([Source Code](../src/GE/Animation), [Example](../src/Prefab/Character/Player/PlayerPrefab.cpp))
* Particle System : The system to simulate and render particles based on different particle module. ([Source Code](../src/GE/Particle), [Example](../src/Prefab/Map/Tile/WeakWallTilePrefab.cpp))

### More Details By Module

* [Collision System](./GameLibraryModule/Collision.md)
* [Animation System](./GameLibraryModule/Animation.md)
* [Particle System](./GameLibraryModule/Particle.md)
* [Common Modules](./GameLibraryModule/Common.md)

## Game Loop

Below game loop will be called on each frame. ([GameEngine::RunGameLoop](../src/GE/Core/GameEngine.cpp))

* `TimeUpdatePhase` : Update the game time.
* `InputUpdatePhase` : Update `InputSystem` with the cached user input.
* `StartPhase` : Call the `Start()` methods of the newly instantiated `Components`.
* `UpdatePhase` : Call the `Update()` methods of all `Components`. After that, call the `LateUpdate()` methods of all `Components`.
* `CollisionPhase` : Do the collision checking and adjust the position of the `Colliders` if necessary. The `onCollided` and `onTriggered` `GE::Event` of corresponding `Colliders` will also be triggered in this phase.
* `AnimationUpdatePhase` : For the sake of latter `RenderPhase`, update the details about animations.
* `RenderPhase` : Render the graphic into the game screen (Call the `Render()` methods of `Renderers`).
* `DestroyPhase` : Destroy (Dispose) the `GameObjects` and `Components` that are requested to be destroy. Right before destroying, `PreDestroy()` method will be called.
* `ChangeScenePhase` : If it is requested to change the `Scene`, the `Scene` will be changed in this phase.

### The Game Loop methods of `Component`

Each `Component` has below methods for the game loop ([Source Code](../src/GE/Core/Component.h)). The behaviour is similar to those of Unity, but may have some difference.

* `Awake()` : The first game loop method to be called after instantiation. No matter the `GameObject` or `Component` is active (enable) or inactive (disable) (which is different from Unity), it will be called once and only once.
* `Start()` : In `StartPhase`, no matter the `GameObject` or `Component` is active (enable) or inactive (disable) (which is different from Unity), it will be called once and only once. For this reason, the `Components` instantiated in `UpdatePhase` will be called `Start()` methods in next frame.
* `Update()` : It is called on each frame. It will be called only if the `Start()` method of a `Component` has been called and the `Component` is enabled.
* `LateUpdate()` : The next handling after the `Update()` methods is called for all `Components` (For the sake of simplicity, there is no other handling between `Update()` and `LateUpdate()`, which is different from Unity). It will be called only if the `Component` is enabled.
* `PreDestroy()` : The handling right before being destroyed, just like the `OnDestroy()` method in Unity. To align the naming (Do not use prefix `On`), a name that is different from Unity's is used.

## Used Techniques

I made this game library because I want to practice my C++ skills. For this reason, I tried to write it from scratch and use third-party plugins as least as possible when development.

Below are the techniques I have used during development.

* STL Container
* STL Algorithm
* Smart Pointer
* Rvalue Reference
* Template (Example : [Vector2](../src/GE/DataType/Vector2.h))
	* Explicit instantiation (Example : [Vector2](../src/GE/DataType/Vector2.cpp))
	* type_traits and concepts (Example : [GEConcept](../src/GE/Utils/GEConcept.h))
	* Perfect Forwarding (Example : [GameObject::AddComponent](../src/GE/Core/GameObject.h))
* Pimpl Idiom (Example : [Collision::Detection::RectDetector](../src/GE/Collision/Detection/RectDetector.h))
* About Function
	* Lambda Function
	* Function Object (Example : [Particle::Internal::VelocityUpdateFunc](../src/GE/Particle/Module/UpdateFunc/VelocityUpdateFunc.h))
	* Observer Pattern (Example : [Event](../src/GE/Core/Event.h))
* Adapter Pattern (Example : [EnumUtils](../src/GE/Utils/EnumUtils.h))
* Visitor Pattern (Example : [Collision::Detection::Detector::CheckCollision](../src/GE/Collision/Detection/Detector.h))
* Macro (Example : [Debug::Logging](../src/GE/Debug/Log.h))
* Preprocessor (Example : [Implementation of RenderSystem](../src/GE/Render/Impl/DG2014RenderSystem.cpp))
* Precompiled Header (Example : [GEHeader](../src/GE/GEHeader.h))

Below are the techniques I have used within the game, but not the game library.

* Factory Pattern(Example : [MapFactory](../src/Map/MapFactory.h))
* State Pattern(Example : [PlayerStateMachine](../src/Character/Player/State/PlayerStateMachine.h))

### Plugins

Although I have said that I want to use third-party plugins as least as possible, I still use a few of them.

The used plugins are listed [here](./PluginDependency.md).

## Insufficiency

* [Oustanding Issues and Enhancements](https://github.com/hihilkh/demo-game-speedrun/labels/game%20engine) (Japanese only)
* There is no audio system.
* In order to make some member functions only be used within the game library, I have used quite a lot of `private` methods together with `friend` classes. It seems to make the codes even more messy and maybe it will be better to just use `public` method.
* I have not made an editor like Unity Editor. So, for the constructions of `Scene` and `Prefab`, they are done by raw C++ codes. Besides inconvenience, there may be some incorrect handling (especially related to the game loop) during the constructions.
* The features related to `GameObject::isActive` and `Component::isEnable` are not sufficient.
* The collision system is too rough. There are many bugs.
* The collision system only support collisions between non-rotated `RectColliders`.
* The animation system only manipulate the rendering of `Image`. It is far not ready for generic usage.
* The detail implementation of particle system is using `Component`. I think it is not a good design. There would be performance issues, and everyone can use `GetComponent()` method to get and change them.
* I have not written any unit tests or integration tests, so sometimes bugs are not discovered during developing the game library, but until developing the game (especially C++ template related codes and some complicated structures such as the hierarchy of `GameObject`).