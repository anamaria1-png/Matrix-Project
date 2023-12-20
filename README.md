DESCRIPTION OF THE GAME- FLAPPY BIRD!
How Flappy Bird Works


Flappy Bird is a simple yet captivating game where the player controls a small character named "Flappy Bird" through an environment filled with pipe obstacles. The objective is to navigate through as many pipes as possible without hitting any of them.I have chosen this game because I used to play it very much in my childhood and now I found an opportunity to make such game for myself.


Gameplay Mechanics:

    Controlling Flappy Bird: The player controls the flight of Flappy Bird by pressing a button or a key to make it jump or fly. In the original game, a single button was used to make the bird flap, using gravity and force to propel it upwards.

    Game Environment: While automatically flying towards the right, Flappy Bird must avoid obstacles in the form of pipes. These pipes are positioned to alternate between rising and falling, creating spaces for the bird to pass through.

    Scoring: Players earn points for each set of pipes passed without collision. The more pipes you pass, the higher your score increases.

Failure Mechanics:

    Collision: The game ends when Flappy Bird hits any of the pipes or touches the screen's edges. Once the game ends, the score is displayed, and the player can choose to start again.

Key Elements from the Flappy Bird Code:

    Game Control: Managed through functions that react to button presses, controlling Flappy Bird's jump.
    Bird and Pipe Movement: Functions responsible for the automatic forward movement of the bird and the pipes to create the impression of progression.
    Scoring and Display: Functions that calculate and display the score on the screen.
    Game Over: When the game ends, there are functions that handle displaying the "Game Over" message and restarting the game.


A. MENU REQUIREMENTS

    Introduction:
        Upon powering up the game, display a brief greeting message.
    Categories in the Menu:
    a. Start Game: Begins the initial level of the game.
    b. Highscore:
        Initially set at 0.
        Updates upon completing the game. Ensure the highest possible score starts from a higher level.
        Save the top 3+ values in EEPROM with names and scores.
        c. Settings:
        Enter Player Name: Name shown in the highscore and possibly elsewhere.
        LCD Brightness Control: Modify the LED wire directly connected to 5V. Save settings to EEPROM.
        Matrix Brightness Control: Implement the 'setIntensity' function from the ledControl library. Display confirmation on the matrix when selecting. Save settings to EEPROM.
        Toggle Sounds On/Off: Save preference to EEPROM.
        Optionally, include game-specific settings or system settings.
        d. About:
        Game Details: Include game name, author, and a link to the game's GitHub or creator's details. Use scrolling text if needed.
        e. How to Play:
        Short, informative description explaining gameplay.
    In-Game Display:
        Show relevant information during gameplay:
            Lives
            Level
            Score
            Time (if applicable)
            Player Name (if applicable)
            etc.
    End of Game:
    a. Screen 1:
        Display a message like "Congratulations on reaching level/score X". Inform about the player's performance compared to others. Automatically transitions to screen 2 or upon interaction.
        b. Screen 2:
        Present relevant game details: score, time, remaining lives, etc.
        Notify if the player has achieved a high score.
        Close this menu only by player action, pressing a button.

B.GAME REQUIREMENTS

    Components and Features:
        Utilize minimal components: LCD, joystick, buzzer, and LED matrix.
        Integrate basic sounds for various game events like "eating" food, character death, level completion, etc. Additional: Consider adding theme songs.
        Each level or instance should operate on a 16x16 LED matrix. Implement visibility concepts like "fog of war" (revealing only 8x8 of the total matrix at a time) or use the idea of distinct "rooms." Ensure four rooms per level that the player must navigate through.
    Gameplay Quality:
        Emphasize intuitive and enjoyable gameplay mechanics.
        Ensure coherence within the current setup, integrating all components seamlessly.
    Progression and Difficulty:
        Maintain a sense of escalating difficulty throughout the gameplay. This progression can occur within a single level or across multiple levels.
        Implement dynamic progression within a level or a series of fixed levels leading to an endgame scenario. Introduce elements of randomness to enhance gameplay variability and excitement.


COMPONENTS: 
-an LCD
-a joystick
-a led matrix.

SEE HOW IT WORKS:https://youtube.com/shorts/TqHc-J2d6hU?feature=share


