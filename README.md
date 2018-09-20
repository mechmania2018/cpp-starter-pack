# Mechmania C++ Starter Pack

Here's all the code you need to get started with making a bot for Mechmania in C++. Just do these steps:

* Pre-Setup -- install Docker, Node, and the `mm` command line tools
* Setup -- Clone this repository and start running your bot!

# Windows Pre-Setup

1. First, install Node. To do this, go [here](https://nodejs.org/en/download/) and download the Windows Installer.

2. Next, install Docker Toolbox for Windows.
   * Go to [this](https://docs.docker.com/toolbox/toolbox_install_windows/) site and click the button that says "Get Docker Toolbox for Windows".
   * Open the installer and follow the instructions to install Docker
   * If you don't already have Oracle VM VirtualBox, you will also go through a series of prompts to install VirtualBox.
   * Once Docker is installed, open the "Docker Quickstart Terminal" application (It will take a few minutes to get set up the first time you start it.  This process may involve more Windows prompts for permissions.)
3. Within Docker, run `npm install -g mechmania`.  This gets the `mm` command line tools, which are used to test and submit bots for the tournament.

# Mac Pre-Setup


# Setup

1. Clone this repo (or fork it or download it somewhere as a ZIP)
2. Modify the script at `MyBot.cpp`.
    * You may add other files or dependencies, just make sure to update the `.dockerignore` and `Dockerfile`s accordingly. If you have any questions about this, we're here to help!
3. Run `mm play .`
    * This will build the bot in the given directory (`.`) and then starts a game in which your bot fights against itself.

TODO: add basic instructions for other mm commands

Use `mm help` for more information!
