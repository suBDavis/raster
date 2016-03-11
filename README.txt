,-.----.                             ___                                                        
\    /  \    By Brandon Davis      ,--.'|_                       ,--,                           
;   :    \   With C++ / Ubuntu     |  | :,'             __  ,-.,--.'|          ,----,           
|   | .\ :               .--.--.   :  : ' :           ,' ,'/ /||  |,         .'   .`|           
.   : |: |   ,--.--.    /  /    '.;__,'  /     ,---.  '  | |' |`--'_      .'   .'  .'   ,---.   
|   |  \ :  /       \  |  :  /`./|  |   |     /     \ |  |   ,',' ,'|   ,---, '   ./   /     \  
|   : .  / .--.  .-. | |  :  ;_  :__,'| :    /    /  |'  :  /  '  | |   ;   | .'  /   /    /  | 
;   | |  \  \__\/: . .  \  \    `. '  : |__ .    ' / ||  | '   |  | :   `---' /  ;--,.    ' / | 
|   | ;\  \ ," .--.; |   `----.   \|  | '.'|'   ;   /|;  : |   '  : |__   /  /  / .`|'   ;   /| 
:   ' | \.'/  /  ,.  |  /  /`--'  /;  :    ;'   |  / ||  , ;   |  | '.'|./__;     .' '   |  / | 
:   : :-' ;  :   .'   \'--'.     / |  ,   / |   :    | ---'    ;  :    ;;   |  .'    |   :    | 
|   |.'   |  ,     .-./  `--'---'   ---`-'   \   \  /          |  ,   / `---'         \   \  /  
`---'      `--`---'                           `----'            ---`-'                 `----'
====================================== Compile Instructions =====================================
|
|	+ fulfill build requirements below
|	+ unzip this archive
|	+ open a terminal and cd to the source directory
|	+ run "./build.sh" (or double-click in a file manager)
|	+ run "./run.sh"   (or double-click in a file manager)
|	+ images will be located in ./Images
|
======================================= Build Requirements ======================================
|
|   + Any OS with a BASH shell
|   + The g++ compiler (I used version 5.2.1)
|       * Can be installed on ubuntu-based systems via "sudo apt-get install build-essential"
|	+ IMPORTANT : armadillo matrix and linear algebra library
|		* Install libarmadillo from via the PPA: https://launchpad.net/ubuntu/+source/armadillo/
|		* "sudo apt-get install libarmadillo-dev" (~55MB)
|       * Because the library has other dependencies, a package manager is STRONGLY recommended
|   + An image viewer that supports the .ppm format (Already included with Ubuntu)
|       * Alternatively, use imagemagick to create a .png from the .ppm output
|       * "sudo apt-get install imagemagick"
|       * "cd Images"
|       * "./convert.sh"
|   + OpenGL is NOT required.
|
======================================= Description of Parts ====================================