DESCRIPTION OF THE GAME- FLAPPY BIRD!
1. Display Initialization:

    We will set up the LED matrix to represent the game screen. Define a 2D array to represent the pixels on the LED matrix.

2. Bird and Obstacle Movement:

    Represent the bird's position on the matrix. We will update its position to simulate flying (by changing its vertical position).
    Generate and move obstacles (pipes or obstacles represented by LED pixels) from right to left.

3. Game Loop:

    Inside the loop, continuously update the display to show the bird's movement and obstacles.
    Check for collisions between the bird and the obstacles. If a collision occurs, end the game.

4. User Controls:

    Use buttons or switches connected to the Arduino to control the bird's movement. For instance, pressing a button could make the bird jump or move upwards.


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
