# Release Notes {#mainpage}
<img align="left" src="Gyruss_logo.png" hspace="20" vspace="10"> <br> <br>
***
***
# <center>ELEN3009 Project 2017 - Gyruss </center>
***
***
<br>
# Game Features and Development
## *Core Features*
* Player ship moves smoothly around perimeter of circular game area, can fire bullets to destroy enemy entities.
* Collision detection between all relevant entities.
* Explosions indicate collisions on relevant events.
* Enemy ships spawn two variants. Either of these variants can appear either at edge of game circle, or from at centre in distance.
* Enemies change behaviour, and exhibit different flying patterns.
* After leaving screen, enemy respawns.
* Player has three lives. Upon losing last life, game ends.
* If the player kills 100 enemies, then the game ends, with a different Game Over screen, indicating victory.
* Meteoroids randomly fly out from centre, they are indestructible and kill the player upon collision.
* Satellite enemy types spawn more rarely, in a group of three. Killing all of them upgrades the player weapon. If the player dies, any surviving satellites disapper. Upon death, the player weapon reverts to the basic lazer gun.
* The game speed starts slow, and scales up the longer a player lives. Upon death, the game speeds resets down.
* Visual window effects and sounds upon player death event.

### SplashScreen:
* Implements splash screen on application load.
* User Controls information displayed.
* Application icon (multiplatform).
* Window can be closed in SplashScreen.
* Instructions on how to proceed ( no longer "any key", to prevent accidental start).
* SplashScreen is animated (visual cue that game is not frozen).
* Quit hot-key (Ctrl-Q) works in SplashScreen and main application
* SplashScreen is frame-limited to 60 fps.

### PlayerShip:
* PlayerShip rotates around circle on screen in response to player keyboard input, with visual cues of movment (animated sprite) and sound for actions.
* Bullets can be fired, originating from the player location towards the centre.
* Bullets are correctly oriented to angle of firing.
* Bullets are animated.
* Player dies if hit by a bullet, meteoroid or enemy ship.
* Upon respawn, the player is briefly invulnerable. A visual shield animation indicates this temporary state.

### HUD:
* A score is shown during gameplay.
* HUD shows player state (alive/invulnerable/dead).
* HUD shows how long the player has been alive.
* Killing enemies awards points (depending on enemy type).
* Score also accumulates according to length of life.

### Entity behavior:
* Bullets and Enemies scale when moving around play arena.
* Enemies orient to direction of movement.
* Behaviours include Hovering, spiralling in, spiralling out, and circling around.

### Object-Oriented design:
* ResourceHolder template class for flexible handling of different resource types.
* Seperate SoundHolder object controls and plays all sounds and music.
* InputHandler only handles keyboard press/release events.
* PlayerShip/EnemyShip/Bullet/Meteoroid all derived classed from Base Entity class.

### Other Application features:
* Highscore stored and displayed between games.
* Player performance metrics shown on Game Over Screen.
* StarField effect (immersion and visual complexity.)
* Improved Game art assets and sound.
* Varied, looping music soundtrack.
* Frame limited by explicit time-step (60 frames per second) and uses VSync.
* Basic separation of entity/setPlayerShipMove/draw methods.
* Early Doxygen documentation (incomplete)
* Included CMakeLists.txt for ease of compiling (works multiplatform OSX and Win32.)
* Developer mode (in OSX only) has "cheat" hotkeys for adjusting gameplay

---
## *Testing*
### Unit tests
* Movement unit tests for all Entities
* Logic tests for collision
* Resource loading and exception tests
* Entity spawning and functionality tests
* Death and score logic tests

### Interactive (user) tests
* SplashScreen interactive tests (user must follow instructions to complete UI tests) 
* Added images to instruct tester visually


---
##### *Free Game Art Asset Credits:*
Royalty-free Music by Eric Matyas [www.http://soundimage.org]()

Free Game Art by Kenney [www.kenney.nl]()

Royalty-free SoundFX from [www.freesound.org]()

All other art and assets by Tyson Cross [www.tysoncross.com]()