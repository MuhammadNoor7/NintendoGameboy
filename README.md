
# Introduction
This project explores the development of a Nintendo GameBoy-inspired framework featuring the classic games Snake and Wordle, implemented using C++ and the SFML library. Drawing from student-created code and object-oriented design principles, it investigates how inheritance, polymorphism, and composition optimize game logic, user interaction, and graphical rendering. The study assesses the effectiveness of these techniques in building modular and engaging gaming experiences, with respective sounds played at key events to enhance immersion.

# Explanation 

# 1.Snake Game

The Snake game is a classic arcade-style game where the player controls a snake that navigates a 20x20 grid, growing longer by eating food while avoiding collisions with hurdles and its own body. The UML diagram illustrates the SnakeGame class inheriting from the abstract Game class and composing the Snake, Food, and Hurdle classes. The Snake class manages the snake's position (initially set at coordinates [10,10], [10,11], [10,12], [10,13]), length (starting at 4), and movement direction (initially [0, -1]), with methods like moveSnake(), changeDirection(), and increaseLength() handling dynamics. The Food class generates up to five food items with random positions and statuses, triggering an "eat.wav" sound when consumed. The Hurdle class places five obstacles, causing a "lose.wav" sound on collision. The game runs at 150ms intervals, regenerates food and hurdles every 5 seconds, and ends with a "lose.wav" sound upon boundary or self-collision, all rendered with SFML graphics.

# 2.Wordle Game

The Wordle game challenges players to guess a five-letter word within three attempts, displayed on a 6x5 grid via the Grid class. The UML diagram shows the WordleGame class inheriting from Game, composing Grid, Dictionary, Menu, PlayingKeyboard, and Word classes. The Dictionary class loads 14,860 words from "dictionary.txt" and selects a random word, while the PlayingKeyboard class handles input, with a "tiledrop.wav" sound for each key press. The Word class checks guesses, coloring them green (correct position), yellow (correct letter, wrong position), or cyan (incorrect), and displays a score with a congratulatory message on a win. The Menu class provides options (Play, Score, Exit) with a "font.ttf" font, and the game tracks attempts, pausing with Space/Escape keys, enhancing interactivity with event-driven sounds.

# Mechanism of the UML Diagram
The UML diagram represents the class structure and relationships for the Nintendo GameBoy project, focusing on object-oriented design. Here's how it works:
# a)Game (Abstract Class):
Serves as the base class with pure virtual methods playGame() and stopGame(), inherited by SnakeGame, WordleGame, and HangmanGame, enabling polymorphic behavior.

# b)GameBoy Class: 
Acts as the main controller, composing a Game* pointer (SelectedGame) and using SFML for rendering (e.g., sf::RenderWindow). It manages the menu and game selection process, dynamically allocating instances of SnakeGame or WordleGame based on user input (e.g., 'S' for Snake, 'W' for Wordle).

# c)SnakeGame and Related Classes:
# 1.Snake: 
Manages the snake's state (position array, length, direction) with methods like moveSnake() and changeDirection(), linked to user input via arrow keys.

# 2.Food: 
Handles food generation and status, connected to SnakeGame for collision detection and length increase.
# 3.Hurdle: 
Defines obstacle positions, integrated with SnakeGame to detect collisions.

Relationships show composition, where SnakeGame contains instances of Snake, Food, and Hurdle, facilitating modular game logic.


# d)WordleGame and Related Classes:
# 1.Grid:
Defines the 6x5 grid structure, linked to WordleGame for rendering guesses.

# 2.Dictionary: 
Loads and provides random words, used by Word and WordleGame for game setup.

# 3.PlayingKeyboard:
Manages user input, tied to WordleGame for guess processing.

# 4.Word:
Checks guesses and assigns colors, integrated with PlayingKeyboard and Dictionary.

# 5.Menu:
Provides the interface, aggregated by WordleGame for navigation.

Relationships indicate composition and usage, ensuring WordleGame orchestrates all components.


#e)Sound Class:
Composes audio buffers and sounds (e.g., StartingSound, snakeEatingSound), used across GameBoy and games to play event-specific sounds like "eat.wav" or "tiledrop.wav".

#f)Other Classes (HangmanGame, etc.):
Included but not detailed here, following similar inheritance and composition patterns.

.The diagram uses arrows to denote inheritance (e.g., SnakeGame → Game) and composition/aggregation (e.g., GameBoy → Game*), illustrating how classes interact. This structure supports modularity, allowing independent development and testing of each game while maintaining a unified GameBoy interface, with sound effects enhancing user feedback at critical events.
