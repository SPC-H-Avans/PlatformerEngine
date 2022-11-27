# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.0.2] - To be released

Added multiplayer support, mario physics and a camera.

### Changes
- SPCH-59 Basic multiplayer setup

### Bug Fixes
None

## [0.0.1] - 21-11-2022

Set up the project and add the first version of the code.

### Changes
- SPCH-35: Added MarioRigidBody with specific Mario physics
- SPCH-35: Updated the collision system and collisionbehavior to prevent mario from getting stuck in other objects
- SPCH-38: Added Collision Unit tests and fixed bugs where the wrong CollisionPoint was detected.
- SPCH-42: Added sprites which can be added to a Game Object
- SPCH-10: Added animated sprites and render system
- SPCH-30: Added the ability to render a TileSet on the screen
- SPCH-1: Added GameLevel that contains all map layers
- SPCH-29: Added a TMX reader with a strategy pattern
- SPCH-3: Added scenes, scene builder and a way to switch from active scene
- SPCH-41: Added Doxygen action for development branch
- SPCH-40: Implemented functions of GameObject and Component
- SPCH-40: Added Multiton pattern, Children and Parent to GameObject (insunated by API docs)
- SPCH-40: Added Builder for creating GameObjects 
- SPCH-39: Added window, engine and graphics facade classes
- SPCH-31: Added SPIC-API as submodule
- SPCH-41: Created GitHub Actions
- SPCH-31: Added Google Test
- SPCH-4: Added Methods to check if mouse/keyboard inputs are being pressed, and get the mouse position
- SPCH-31: Added Google Test 
- SPCH-38: Added Collision Detection with direction of collision.
- SPCH-35: Added weak pointer to GameObject from component

### Bug Fixes
- SPCH-50: Fixed the freezing window issue