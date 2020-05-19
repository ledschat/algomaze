# The Algorithmic maze

The *Algorithmic maze* is a computer science installation exposed at [**Le Palais de la Découverte**](http://www.palais-decouverte.fr), Paris. 
Its aims at introduce algorithms to relsolve mazes. Three robots are displayed on the maze, and the visitor can control them using different methods, with touchscreens and push buttons. 

## How to compile and test

The recommended way to compile the code is to use [**cmake**](https://cmake.org/), which automatically generates project files for your favourite IDE or build system:
```
git clone https://github.com/ledschat/algomaze
cd algomaze/binary
mkdir build
cd build
cmake ..
cmake --build .
```

To test the application you need to download [**Visual Studio Code**](https://code.visualstudio.com/) and the **Mozaïk extension**, which can be get here:

- [Ubuntu >= 18.04](https://store.leds-chat.com/vsplugin/file/linux/)
- [Windows 10 64bits](https://store.leds-chat.com/vsplugin/file/win64/)
- [OSX >= 9](https://store.leds-chat.com/vsplugin/file/osx/)

To Install the extension, go to the Extensions tab of Visual Studio Code, then click on the **Install from VSIX...** button of the **...** menu.
Open the algomaze folder with Visual Studio Code, and check that the file **app.json** is located at the root of the folder. Start the application by calling the comand **Led's Chat: Start**. When asked, start the simulator.
Finally, you can use the **Led's Chat: Open the frontend** command to open the user interface.  
