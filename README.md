# Brick Game

Welcome to my classic brick-breaking game developed using C++ and the SFML library! The objective is to destroy all the bricks by bouncing the ball off the platform and walls.

## Table of Contents
- Features
- Installation
- Usage
- Controls
- Precompiled Binaries

## Features
- Classic 2D brick-breaking gameplay
- Aim the ball at the start of the game
- Bounce the ball off the platform and walls
- Destroy all the bricks and earn points to win the game

## Installation
To set up the game locally, follow these steps:

1. **Clone the Repository:**
    ```bash
    git clone https://github.com/GeHa6yKuH/SFMLGame.git
    ```
2. **Download SFML:** Download the appropriate SFML package from the SFML website: https://www.sfml-dev.org/download/sfml/2.6.1/.
3. **Configure Solution Paths:**
    - Open your solution in your IDE (e.g., Visual Studio).
    - Go to the project properties.
    - Set your Configuration to Release and Platform to x64
    - Navigate to C/C++ General.
    - Add the path to SFML include files to Additional Include Directories (for example: C:\SFML\SFML-2.6.1\include).
    - Navigate to Linker General.
    - Add the path to SFML library files to Additional Library Directories (for example: C:\SFML\SFML-2.6.1\lib).
4. **Add SFML Libraries as Additional Dependencies:**
    - In the project properties, navigate to Linker > Input.
    - Add the following SFML libraries to Additional Dependencies:
        ```vbnet
        sfml-main.lib
        sfml-graphics.lib
        sfml-window.lib
        sfml-system.lib
        ```
5. **Build the Solution:** Build the project in your IDE.
6. **Move Assets and DLLs:**
    - Move all .png files from the main directory to GameSFML/x64/Release.
    - Copy all .dll files YOUR DOWNLOADED SFML folder's bin directory to GameSFML/x64/Release.
7. **Run the Game:**
    - Navigate to GameSFML/x64/Release.
    - Run GameSFML.exe.

## Usage
- **Aim the Ball:** At the beginning of the game, use the Left and Right arrows to aim the ball in the desired direction.
- **Start the Game:** Launch the ball by pressing SPACE and start breaking the bricks and collecting bonuses. You will only have 3 lives.
- **Bounce the Ball:** Move the platform to bounce the ball and direct it towards the bricks.
- **Pause the game** You can pause the game by simply pressing P key.
- **Win the Game:** Destroy all the bricks to win.
- **Reset:** You can reset the game any time by pressing R key.

## Controls
- Left Arrow Key: Move the platform left; change ball's velocity to the left before launched;
- Right Arrow Key: Move the platform right; change ball's velocity to the right before launched;
- Spacebar: Launch the ball

## Precompiled Binaries
If you prefer not to build the game from source, you can download the precompiled binaries. This includes the executable, necessary DLLs, PDB, and images. The archive is compatible with Windows.

Download Precompiled Binaries

Feel free to explore, modify, and have fun with the game! If you encounter any issues or have suggestions, please open an issue or submit a pull request. Happy gaming!

!game_image.png
