#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "state.h"
#include "menustate.h"


class GameState : public State {
public:

	/* GameState:
	* State class that runs the main game.
	* the constructor of GameState class, takes the following parameters:
	* - window @ Assigns class protected member window.
	* - states @ Assigns class protected std::stack states_ that holds states of the program.
	* This function also calls all the initializers for game objects and sounds.
	* When calling this function, chests are also created.
	*/
	GameState(sf::RenderWindow* window, std::stack<State*> *states);

	/* ~GameState:
	* virtual Destructor.
	*/
	virtual ~GameState();

	/* UpdateInput:
	* A function that updates states of pausemenu and inventory.
	* Controls the boolean values depending of the result of buttons pressed on menus.
	* Also controls playing the sounds of footsteps and monsters shooting.
	* If given correct if statements, pops the current state and pushes MenuState to states_.
	*/
	void UpdateInput(const float& dt);

	/* Update:
	* Assigns the values to clock variables.
	* Updates mousepositions on different windows depending which one is enabled.
	* Updates the state of inventory and its slots.
	* Updates the states of projectiles.
	* Updates the hud and its variables.
	* Handles the sound management.
	* Checks if the player has killed the any of the bosses and adds the specific items to characters inventory
	* if that has been happened.
	* Checks if player is colliding with door shapes and handles the movement if that happens.
	* Calls updateEnemyMakeDamage
	*/
	void Update(const float& dt);

	/* Render:
	* Assigns the view to follow the player in specific range.
	* Handles rendering the map.
	* Handles rendering all the monsters.
	* Handles rendering the character.
	* Handles rendering the chest window.
	* Handles rendering the inventory window.
	* Handles rendering the other HUD shapes.
	* Handles rendering the pausemenu.
	* Handles rendering the deathscreen.
	* Handles rendering the winscreen.
	* Handles damagesystem and its shapes if player has been attacked.
	* Handles damagesystem and its shapes if monster has been attacked.
	*/
	void Render(sf::RenderTarget* target = nullptr);

	/* UpdateChestsSlotRemoval:
	* Iterates through all the chests in the map and if removed slot is string is non-empty, adds it to
	* characters inventory.
	*/
	void UpdateChestsSlotRemoval();

	/* UpdateChests:
	* Calls Update function for every chest.
	*/
	void UpdateChests();

	/* UpdateInventorySlotRemoval:
	* Handles calling UpdateRemoveInventorySlot function which checks if the item is health potion or
	* water potion, if so player will get more health/experience.
	*/
	void UpdateInventorySlotRemoval();

	/* CheckForCombatMusic:
	* Checks if the player's current position is in the specific area and if so combat flag will be changed to true.
	*/
	void CheckForCombatMusic();

	/* InitPlayer:
	* Initialises the characters spawn position.
	* Loads characters texture from a file.
	* Constructs the player class.
	*/
	void InitPlayer();

	/* InitFireball:
	* Loads fireball texture from a file.
	* Constructs the fireball class.
	*/
	void InitFireball();

	/* InitToxicBall:
	* Loads Toxicball texture from a file.
	* Constructs the Toxicball class.
	*/
	void InitToxicBall();

	/* InitInventory:
	* Initialises the inventory size, color and font.
	* Loads inventory texture from a file.
	* Assigns the inventory shape texture with the loaded texture.
	*/
	void InitInventory();

	/* InitChests:
	* Initialises all the chests in the map with specific sizes, colors and fonts.
	*/
	void InitChests();

	/* InitMonsters:
	* Constructs monster classes with specific parameters.
	* Loads textures from a files.
	* Adds the created monsters to monsters array.
	*/
	void InitMonsters();

	/* InitFonts:
	* Initialises the font.
	*/
	void InitFonts();

	/* InitPauseMenu:
	* Initialises the pausemenu with specific size, color and font.
	* Loads pausemenu texture from a file.
	* Assigns the pausemenu shape texture with the loaded texture.
	*/
	void InitPauseMenu();

	/* InitDeathWindow:
	* Constructs the DeathWindow class
	* Loads deathwindow texture from a file.
	* Sets the texture for the DeathWindow shape.
	*/
	void InitDeathWindow();

	/* InitVictoryWindow:
	* Constructs the VictoryWindow class
	* Loads victorywindow texture from a file.
	* Sets the texture for the victorywindow shape.
	*/
	void InitVictoryWindow();

	/* InitDoors:
	* Constructs the doors for the map
	* Loads texture from a file.
	* Sets the texture for the doors.
	*/
	void InitDoors();

	/* updateEnemyMakeDamage:
	* Iterates through monster array and detects if the monster is in the correct range,
	* if so takeDamage function will be called and damageshapes will be rendered on the screen.
	*/
	void updateEnemyMakeDamage();

	/* updateEnemyProjectiles:
	* Handles the projectile collision and changes the state of enemyHit if collission happens.
	* Handles removing the enemyprojectiles if lifetime is zero or less.
	* Handles the damagesystem if collision is detected.
	*/
	void updateEnemyProjectiles(float dt);

protected:
	float enemyDt;
	sf::Texture wizardBlueTexture;
	sf::Texture wizardGreenTexture;
	sf::Texture fireballTexture;
	Projectile fireball_;
	sf::Texture toxicballTexture;
	Projectile toxicball_;

	int damageTaken;
	std::string damageTakenString;
	sf::Text damageTakenText;
	bool enemyHit = false;
	bool spidersoundBool = false;
	Hud hud;

	Door door1;
	Door door2;
	Door door3;
	Door door4;

	sf::Texture doorUpTexture;
	sf::Texture doorDownTexture;

	bool opendoors = false;

	float timer = 0;
	sf::Music music;
	sf::Music combatmusic;
	sf::SoundBuffer combatmusicBuffer;
	bool combat = false;
	bool first = true;

	sf::SoundBuffer footstepsBuffer;
	sf::Sound footsteps;
	sf::SoundBuffer piuBuffer;
	sf::Sound piu;
	sf::SoundBuffer slurpBuffer;
	sf::Sound slurp;
	sf::SoundBuffer moanBuffer;
	sf::Sound moan;
	sf::SoundBuffer stabBuffer;
	sf::Sound stab;
	sf::SoundBuffer spidersoundBuffer;
	sf::Sound spidersound;
	sf::SoundBuffer KeySoundBuffer;
	sf::Sound KeySound;

	sf::RectangleShape blur;
	sf::Texture blurTexture;
	sf::Texture inventoryTexture;
	sf::Texture pauseTexture;
	sf::Texture deathWindowTexture_;
	sf::Texture victoryWindowTexture_;

	MonsterCave* monsters_ = new MonsterCave();

	sf::View followPlayer;
	TileMap map;
	Player* player_;
	sf::Texture playerTexture;
	sf::Texture zombiTexture;
	sf::Texture boss1Texture;

	PauseMenu pauseMenu_;
	bool pauseOn = false;

	DeathWindow* deathWindow_;
	VictoryWindow* victoryWindow_;

	Inventory inventory_;
	bool invOn = false;
	sf::Font font;

	int chestNumber;
	bool chestOn = false;
	std::map<int, Chest*> chests_;
	int chestCollided = 25;
	int chestindex = 0;

	int result = 0;
	int deadresult = 0;
	int victoryresult = 0;
	sf::Time time;
	sf::Clock clock_;
	sf::Clock clockEnemy_;
	sf::Clock clockGUI_;
	sf::Clock clockPlayer_;
	sf::Clock clockEnemyHit_;
	sf::Clock clockHit_;

	bool dead = false;
	bool victory = false;

	float timedelay = 0;


};

#endif