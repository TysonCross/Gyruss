# Release Notes
***
***
# <center>ELEN3009 Project 2017 - Gyruss </center>
***
***
<br>
# Game Features and Development
## *Whats New*
* Game plays fullscreen, 1920x1080
* Added Perlin noise implementations
* Start splash screen tribute to the original game
* Added additional animation to splash screen
* Added an additional enemy variant: Wanderer, using 2D perlin noise
* Adjusted Game speed to start slower
* Increased max enemies at any time
* Added Victory condition score to HUD: enemy deaths count down from 100
* Engine refactoring for seperation of concerns
* Technical documentation now included with game ( in docs/html.index.html )

### SplashScreen:
* Player ship image now floats about (procedurally animated with Perlin noise)

### PlayerShip/HUD:
* PlayerShip state in HUD now reflects weapon upgrade

### Entity behavior:
* Entities no longer group horizontally.
* Sattelite texture changes to be more visually distinct
* Additional enemy variant (Wanderer) with new texture

### Object-Oriented design:
* All audio, including music, now the responsibility of Soundcontroller
* Removed player move sound from PLayerShip (No classes derived from Entity have any sound methods at all)
* Entity now inherits from two Base classes: Moveable and Animatable
* Moveable Class: All movement and translation/dimensional members and methods
* Animatable Class: All texture and tile-set animation members and methods

### Technical documentation
* Nicer enum formatting (including entity texture images in documentation)
* All objects documented (complete)

### Other Application features:
* New Highscore!
* Improved Game art assets and sound.
* Developer mode (in OSX only) has permenant ivulnerability mode
* Added "Spawn Enemy" developer keys
* Developer keys (in debug mode only) : <br>		[ : slow down game speed <br>
		] : speed up game speed <br>
		l : upgrade gun <br>
		k : kill (lose player life) <br>
		p : godmode (invulnerability)
		o : turn off invulnerability

## *What's Fixed*
* Explosion bug (large explosion appearing at centre of screen, due to enemy spawning on player bullet) fixed.

---
## *Testing*
### New Unit tests
* Entity controller public interface tested
* All "common" functions tested
* Score class tested

---
##### *Free Game Art Asset Credits:*
Royalty-free Music by Eric Matyas [www.http://soundimage.org]()

Free Game Art by Kenney [www.kenney.nl]()

Royalty-free SoundFX from [www.freesound.org]()

All other art and assets by Tyson Cross [www.tysoncross.com]()