[![en](https://img.shields.io/badge/lang-en-red.svg)](./Particle.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./Particle.jp.md)

# About Particle System

## Structures

* `ParticleSystem` : The component that controls the behaviour of particles. It is similar to the `ParticleSystem` of Unity.
* `Internal/ParticleComponent` : The attached component of every generated particles during a `ParticleSystem` is playing. It will store an instance of `UpdateFunc` of the `Modules` set by the `ParticleSystem` and call them on each frame.
* `CoreConfig` : The necessary config of a `ParticleSystem`.
* `Module` : The config to manipulate particles' behaviour. It is similar to the `Particle System Modules` in Unity. Supported `Modules` are listed below.
	* `ColorOverLifetimeModule` : Change particles color by time.
	* `EmissionModule` : Decide the emission position and rotation of particles.
		* `RectEmissionModule` : Emit particles in a rectangle area.
	* `VelocityModule` : Control the velocity of particles.
* `ModuleSet` : The class that store all the `Module` of a `ParticleSystem`.
* `UpdateFunc` : The function that is called on each frame to manipulate particles' behaviour.
* `ParticleSystemFile` : A JSON file that stores all the config data of a `ParticleSystem`.
* `ParticleSystemLoader` : A loader to load a `ParticleSystemFile` and deserialize to `CoreConfig` and `ModuleSet` instances. It also caches and manages the loaded `ParticleSystemFile`.

## Example of a `ParticleSystemFile`

```json
{
    "core": {
        "img": "./data/Image/WallFragment.png",	// The image source of the particle
        "render_priority": 200,			// Thr render priority of the particle image
        "no_of_particle": 20,			// Number of particles to be generated during the ParticleSystem is playing
        "life": 1.0				// The lifetime in seconds of a particle
    },
    "modules": [				// Array of Modules
        {
            "name": "rectEmission",		// The name of the Module. Work as an ID
            "detail": {				// The details of the Module. The structure depends on the Module
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

## References

* [Source Code](../../src/GE/Particle)
* [Example of `ParticleSystem`](../../src/Prefab/Map/Tile/WeakWallTilePrefab.cpp)
* [Example of `ParticleSystemFile`](../../data/ParticleSystem/WeakWallBreak.json)