      ___         ___          ___                 ___          ___                   ___          ___          ___     
     /  /\       /  /\        /  /\        ___    /  /\        /  /\      ___        /  /\        /  /\        /  /\    
    /  /::\     /  /::\      /  /:/_      /  /\  /  /:/_      /  /::\    /  /\      /  /::|      /  /:/_      /  /::\   
   /  /:/\:\   /  /:/\:\    /  /:/ /\    /  /:/ /  /:/ /\    /  /:/\:\  /  /:/     /  /:/:|     /  /:/ /\    /  /:/\:\  
  /  /:/~/:/  /  /:/~/::\  /  /:/ /::\  /  /:/ /  /:/ /:/_  /  /:/~/:/ /__/::\    /  /:/|:|__  /  /:/ /:/_  /  /:/~/:/  
 /__/:/ /:/__/__/:/ /:/\:\/__/:/ /:/\:\/  /::\/__/:/ /:/ /\/__/:/ /:/__\__\/\:\__/__/:/ |:| /\/__/:/ /:/ /\/__/:/ /:/___
 \  \:\/:::::|  \:\/:/__\/\  \:\/:/~/:/__/:/\:\  \:\/:/ /:/\  \:\/:::::/  \  \:\/\__\/  |:|/:/\  \:\/:/ /:/\  \:\/:::::/
  \  \::/~~~~ \  \::/      \  \::/ /:/\__\/  \:\  \::/ /:/  \  \::/~~~~    \__\::/   |  |:/:/  \  \::/ /:/  \  \::/~~~~ 
   \  \:\      \  \:\       \__\/ /:/      \  \:\  \:\/:/    \  \:\        /__/:/    |  |::/    \  \:\/:/    \  \:\     
    \  \:\      \  \:\        /__/:/        \__\/\  \::/      \  \:\       \__\/     |  |:/      \  \::/      \  \:\    
     \__\/       \__\/        \__\/               \__\/        \__\/                 |__|/        \__\/        \__\/    
                        

====================================== Compile Instructions =====================================
|
|	+ filfill the build requirements below
|	+ unzip this archive
|	+ open a terminal and cd to the source directory
|	+ run "./build.sh"
|	+ run "./run.sh"
|	+ images will be located in ./Images
|
======================================== Build Requirements =====================================
|
|   + Any OS with a BASH shell
|   + The g++ compiler (I used version 5.2.1)
|       * Can be installed on ubuntu-based systems via "sudo apt-get install build-essential"
|	+ IMPORTANT : libarmadillo matrix and linear algebra library
|		* Install libarmadillo from via the PPA ( https://launchpad.net/ubuntu/+source/armadillo/ )
|			* "sudo apt-get install libarmadillo-dev" (~55MB)
|   + An image viewer that supports the .ppm format
|       * Alternatively, use imagemagick to create a .png from the .ppm output
|       * "sudo apt-get install imagemagick"
|       * "cd Images"
|       * "./convert.sh"
|   + OpenGL is NOT required.
|
======================================= Description of Parts ====================================