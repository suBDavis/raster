,-.----.                             ___                                                        
\    /  \    By Brandon Davis      ,--.'|_                       ,--,                           
;   :    \   With C++ / G++        |  | :,'             __  ,-.,--.'|          ,----,           
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
| 
| Main:
|     * Creates the room, the spheres, and puts them into worldspace.
|     * Specifies the shading type.
| 
| Mesh:
|    * code for shading a mesh (given lights, a point, and a normal)
|    * unit sphere generation code, since it produces a Mesh object
|    * Transform method - takes 44 matrix and applies it on all triangles in the mesh
|    * Each mesh has its own phong properties.
|
| Room:
|    * Contains the main rasterization code, including the transfom pipeline and actual rasterization code
|    * Does edge function computation
|    * Contains top level transform funciton, which transforms all lights and meshes in the room
|
| Triangle:
|    * Contains the actual code to do a transform.
|    * Contains 3 v3's that correspond to the 3 triangle points
|    * Contains 3 c++ std::vectors of normals that are used to compute the vertex normals
| 
| v3:
|    * Base vector class
|    * implements vector/matrix transforms using armadillo library
|
| Renderer:
|    * pixel color array buffer
|    * Code for gamma correction, applied when the image is written to file
|
================================================================================================