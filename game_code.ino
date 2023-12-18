#include "presets.h"
#include "letters.h"
#include "numbers.h"
#include <LedControl.h>
#include <Timer.h>
#include <LiquidCrystal.h>
// Initialize LCD with the given pin configuration
LiquidCrystal lcd(12,11,5,4,3,6);
// Define constant values for pins
#define LED_PIN 13
#define BUTTON_PIN 2
#define DIN 8
#define CS 9
#define CLK 10
int intensity = 1;  // Set initial LED intensity 


// Initialize LedControl, Gameplay, and Timer objects
LedControl MX = LedControl(DIN, CLK, CS, 1);
Gameplay game;
Timer timer;
// Global variables
boolean running = true;

int Update;
int Pipe1MoveTimer;
int Pipe2MoveTimer;
int difficulty;

// Constants for bird physics
const float grav = 0.005;
const float up = -0.05;
const byte BirdX = 1;
// Setup function, runs once at the beginning
void setup()
{
  // Initialize the LCD
  MX.setIntensity(0, intensity);
  lcd.begin(16, 2);               // Initialize the LCD
  lcd.setCursor(0, 0);
  lcd.print("Player:Ana");  // Replace YourName with the actual player name
  Serial.println("Ana");
  lcd.setCursor(0, 1);
  lcd.print("Flappy Bird");  // Replace Flappy Bird with the actual game name
  Serial.println("game flappy bird");

  // Set up your LCD messages (player name, game name, etc.)
  //lcd.clear();

  Serial.begin(9600);
  MX.shutdown(0, false);
  MX.setIntensity(0, intensity);
  MX.clearDisplay(0);
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  randomSeed(analogRead(0));
  game.status  = OFF;
  timer.every(30, ButtonPressScan);
  GameStart(true);
}

void MoveBird()    // Function to move the bird based on physics
{
	static float y = 0.5; // Bird physics calculations
	game.BirdVel = game.BirdVel + grav;
	float initY = game.BirdCrd;

  	game.BirdCrd = game.BirdCrd + game.BirdVel;

  if (game.BirdCrd > 1)  // Ensure bird stays within screen boundaries
  {
    game.BirdCrd = 1;
    game.BirdVel = 0;
  }
  else if (game.BirdCrd < 0) 
  {
    game.BirdCrd = 0;
    game.BirdVel = 0;
  }

  byte yCrd = 7 * game.BirdCrd;  

  Dir dir;           // Determine bird direction and update display
  if (abs(initY - game.BirdCrd) < 0.01) 
  {
    dir = STRAIGHT;
  }
  else if (initY < game.BirdCrd) 
  {
    dir = UP;
  }
  else 
  {
    dir = DOWN;
  }
  // Update LCD with score
  BirdForm(dir, yCrd);
  lcd.clear();
   lcd.setCursor(0, 0);  // Adjust the cursor position based on your LCD layout
  lcd.print("Score: " + String(game.score));
   lcd.setCursor(0, 1);  // Adjust the cursor position based on your LCD layout
  lcd.println("Player:Burhan");
  Serial.println("Score: " + String(game.score));
}
// Function to start the game
void GameStart(boolean ask)
{
  if (ask) 
  {	
  	game.score = 0;
    game.status = ON;
    game.BirdCrd = 0.5;
    game.pipe1.Xcrd = 7;
    game.pipe1.parts = PipeGen();
    game.pipe2.Xcrd = 7;
    game.pipe2.parts = PipeGen();
    Update = timer.every(50, MoveBird);
	timer.after(2500, Pipe1Start);
    timer.after(4500, Pipe2Start);
    lcd.clear();
    lcd.setCursor(0, 0);  // Adjust the cursor position based on your LCD layout
  lcd.println("Player:Burhan");
  
    lcd.print(game.score);
  Serial.println("Score: " + String(game.score));
  } 
  else 
  {
    // Stop the game and associated timers
    game.status = OFF;
    timer.stop(Update);
    timer.stop(Pipe1MoveTimer);
    timer.stop(Pipe2MoveTimer);
  }
}


// Function to start the movement of the first pipe
void Pipe1Start()
{

  Pipe1MoveTimer = timer.every(200, Pipe1Move);
}
// Function to start the movement of the second pipe
void Pipe2Start()
{	
  Serial.println(difficulty);
  Pipe2MoveTimer = timer.every(200, Pipe2Move);
}
// Function to move the first pipe
void Pipe1Move()
{
  PipeMove(&game.pipe1);
}
// Function to move the second pipe
void Pipe2Move()
{
  PipeMove(&game.pipe2);
}
// Function to create a burst effect on the screen
void screenburst()
{
  for (int i = 0; i < 15; ++i) 
  {
    allOn(true);
    delay(20);
    allOn(false);
    delay(20);
  }
}
// Function to handle game over scenario
void gameOver()
{
    // Display the final score and restart the game
  displayScore(game.score);	
  GameStart(false);
  
  lcd.clear();
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Score: " + String(game.score));
  delay (2000);
   lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("Your Score:");
  lcd.print(game.score);
  lcd.setCursor(0,1);
  lcd.println("*Press To Start*");
}
// Function to turn on or off all LEDs
void allOn(boolean on) 
{
  byte val = on ? 0xff : 0;
  for (byte n = 0; n < 8; ++n) 
  {
    MX.setRow(0, n, val);
  }
}
// Function to display the score on the LED matrix

void displayScore(byte num)
{
  if (num > 99) {
    error();
    return ;
  }
  byte tens = num / 10;
  byte ones = num % 10;
  for(int row = 0;row < 8;row++){
    byte composite = nums[tens][row] | (nums[ones][row] >> 4);
    updateFrameRow(row, composite);    
  }
}
// Function to move the LED matrix display buffer
void bufferMove()
{
  for(int step = 0;step < 8;step++)
  {
    for (int row = 0; row < 8; row++) 
    {
      byte pixels = game.framebuffer[row];
      if (row % 2) 
      {
        pixels = pixels >> 1;        
      }
      else 
      {
        pixels = pixels << 1;      
      }
      updateFrameRow(row, pixels);
    }
    
    delay(50);
  }  
}
// Function to update a row in the LED matrix display buffer
void updateFrameRow(byte row, byte pixels) 
{
  MX.setRow(0, row, pixels);
  game.framebuffer[row] = pixels;
}
// Function to move the first or second pipe
void PipeMove(Pipe *pipe)
{
  if (pipe->Xcrd == 255) 
  {
    PipeDelete(pipe, 0);
    pipe->parts = PipeGen();
    pipe->Xcrd = 7;
  }
  else if (pipe->Xcrd < 7) 
  {
    PipeDelete(pipe, pipe->Xcrd + 1);    
  }

  PipeDraw(pipe, pipe->Xcrd);

    if (pipe->Xcrd == 2) 
    {
    byte yCrd = 7 * game.BirdCrd;  
    if (pipe->parts & (0x80 >> yCrd)) 
    {
      screenburst();
      gameOver();
    }
    else 
    {
      game.score++;

     }
  }

  pipe->Xcrd = pipe->Xcrd - 1;
}

// Function to draw the pipe on the LED matrix
void PipeDraw(Pipe *pipe, byte x) 
{
  for (byte row = 0; row < 8; row++) 
  {
    if (pipe->parts & (0x80 >> row)) 
    {
      MX.setLed(0, row, x, HIGH);
    }
  }
}
// Function to clear the pipe from the LED matrix
void PipeDelete(Pipe *pipe, byte x) 
{
  for (byte row = 0; row < 8; row++) 
  {
    if (pipe->parts & (0x80 >> row)) 
    {
      MX.setLed(0, row, x, LOW);
    }
  }
}
// Function to generate a random pipe configuration
byte PipeGen()
{
  byte hole = random(4, 7);
  byte holeBits = (1 << hole) - 1;
  byte offset = random(1, 8 - hole);
  return 0xff & ~(holeBits << offset);
}

// Function to scan for button presses
void ButtonPressScan()
{
  static boolean init = false;
  boolean ButtonPress = !digitalRead(BUTTON_PIN);

  if (ButtonPress) 
  {
    if (game.status == ON) 
    {
      
      if (!init) 
      {
     	  if (game.BirdVel > 0) 
        {
          game.BirdVel = up;  
        }
        else 
        {
          game.BirdVel += up;   
        }       
      }      
    }
    else 
    {
      bufferMove();
      GameStart(true); 
    }
  }
  init = ButtonPress;
  digitalWrite(LED_PIN, ButtonPress);
}

void BirdForm(Dir dir, byte BirdHead)
{
  
  static byte TailPixel, HeadPixel;
  byte BirdTail;
  BirdTail = constrain(BirdHead - dir, 0, 7);

  
  MX.setLed(0, TailPixel, BirdX, LOW);
  MX.setLed(0, HeadPixel, BirdX + 1, LOW);

  
  MX.setLed(0, BirdTail, BirdX, HIGH);
  MX.setLed(0, BirdHead, BirdX + 1, HIGH);

  
  TailPixel = BirdTail;
  HeadPixel = BirdHead;
}

void error()
{
 for(int row = 0;row < 8;row++){
    MX.setRow(0, row, lett[0][row]);
  }
}
// Function to update the timer and handle events in the loop
void loop() 
{
  

  timer.update();


}
