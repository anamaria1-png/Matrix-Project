#include "presets.h"
#include "letters.h"
#include "numbers.h"
#include <LedControl.h>
#include <Timer.h>
#include <LiquidCrystal.h>

const byte rs = 9; const byte en = 8; const byte d4 = 7; const byte d5 = 6; const byte d6 = 5; const byte d7 = 4;
// Define the LCD pin connections
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LED_PIN 13
#define BUTTON_PIN 2

#define DIN 12
#define CS 11
#define CLK 10
int intensity = 1;

LedControl MX = LedControl(12,11,10, 1);
Gameplay game;
Timer timer;

boolean running = true;

int Update;
int Pipe1MoveTimer;
int Pipe2MoveTimer;
int difficulty;

const float grav = 0.005;
const float up = -0.05;
const byte BirdX = 1;

void setup()
{
  // Initialize the LCD
  
  MX.setIntensity(0, intensity);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");  
  Serial.println("");
  lcd.setCursor(0, 1);
  lcd.print("How to Play:");  
  delay (3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fly and dont");
  lcd.setCursor(0, 1);
  lcd.print("hit the pipe");
  
  Serial.println("game flappy bird");

  // Set up your LCD messages (player name, game name, etc.)
  //lcd.clear();

  Serial.begin(9600);
  MX.shutdown(0, false);
  MX.setIntensity(0, intensity);
  MX.clearDisplay(0);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use INPUT_PULLUP to enable the internal pull-up resistor
  pinMode(LED_PIN, OUTPUT);
  randomSeed(analogRead(0));
  game.status = OFF;
  timer.every(30, ButtonPressScan);
  // GameStart(true); // Remove this line from setup
}

void MoveBird()
{
  static float y = 0.5;
  game.BirdVel = game.BirdVel + grav;
  float initY = game.BirdCrd;

  game.BirdCrd = game.BirdCrd + game.BirdVel;

  if (game.BirdCrd > 1)
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

  Dir dir;
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

  BirdForm(dir, yCrd);
  lcd.clear();
  lcd.setCursor(0, 0); // Adjust the cursor position based on your LCD layout
  lcd.print("Score: " + String(game.score));
  lcd.setCursor(0, 1); // Adjust the cursor position based on your LCD layout
  lcd.println("Player:Ana");
  Serial.println("Score: " + String(game.score));
}

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
    lcd.setCursor(0, 0); // Adjust the cursor position based on your LCD layout
    lcd.println("Player:Ana");

    lcd.print(game.score);
    Serial.println("Score: " + String(game.score));
  }
  else
  {
    game.status = OFF;
    timer.stop(Update);
    timer.stop(Pipe1MoveTimer);
    timer.stop(Pipe2MoveTimer);
  }
}

void Pipe1Start()
{
  Pipe1MoveTimer = timer.every(200, Pipe1Move);
}

void Pipe2Start()
{
  Serial.println(difficulty);
  Pipe2MoveTimer = timer.every(200, Pipe2Move);
}

void Pipe1Move()
{
  PipeMove(&game.pipe1);
}

void Pipe2Move()
{
  PipeMove(&game.pipe2);
}

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

void gameOver()
{
  displayScore(game.score);
  GameStart(false);

  lcd.clear();
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Score: " + String(game.score));
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Score:");
  lcd.print(game.score);
  lcd.setCursor(0, 1);
  lcd.println("*Press To Start*");
}

void allOn(boolean on)
{
  byte val = on ? 0xff : 0;
  for (byte n = 0; n < 8; ++n)
  {
    MX.setRow(0, n, val);
  }
}

void displayScore(byte num)
{
  if (num > 99)
  {
    error();
    return;
  }
  byte tens = num / 10;
  byte ones = num % 10;
  for (int row = 0; row < 8; row++)
  {
    byte composite = nums[tens][row] | (nums[ones][row] >> 4);
    updateFrameRow(row, composite);
  }
}

void bufferMove()
{
  for (int step = 0; step < 8; step++)
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

void updateFrameRow(byte row, byte pixels)
{
  MX.setRow(0, row, pixels);
  game.framebuffer[row] = pixels;
}

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

byte PipeGen()
{
  byte hole = random(4, 7);
  byte holeBits = (1 << hole) - 1;
  byte offset = random(1, 8 - hole);
  return 0xff & ~(holeBits << offset);
}

void ButtonPressScan()
{
  static boolean buttonState = HIGH;  // Current state of the button
  static boolean lastButtonState = HIGH;  // Previous state of the button
  static unsigned long lastDebounceTime = 0;  // Last time the button state changed
  static unsigned long debounceDelay = 30;  // Debounce time in milliseconds

  // Read the state of the button
  boolean currentButtonState = digitalRead(BUTTON_PIN);

  // Check if the button state has changed
  if (currentButtonState != lastButtonState)
  {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }

  // Check if the debounce delay has passed
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // Check if the current button state is different from the recorded state
    if (currentButtonState != buttonState)
    {
      // Update the button state
      buttonState = currentButtonState;

      // Check if the button is pressed
      if (buttonState == LOW)
      {
        // Button is pressed, perform the necessary actions
        if (game.status == ON)
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
        else
        {
          bufferMove();
          GameStart(true);
        }
      }
    }
  }

  // Save the current button state for the next iteration
  lastButtonState = currentButtonState;
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
  for (int row = 0; row < 8; row++)
  {
    MX.setRow(0, row, lett[0][row]);
  }
}

void loop()
{
  timer.update();
  
}
