# Mechmania C++ Starter Pack

Here's all the code you need to get started with making a bot for Mechmania in C++. Just do these steps:

# Pre-Setup

1. Make sure you have Node installed. The easiest way to do this is `curl -sL install-node.now.sh | sh`, otherwise get it [here](https://nodejs.org/en/download/)
2. Make sure you have Docker installed. Instructions are [here](https://docs.docker.com/install/) and feel free to get our help with this.
3. Get the `mm` cli tools. You're going to need these when developing and submitting you bot for the tournament.
 * Make sure to get Node first
 * Then, simply run `npm install -g mechmania`
 * Test your installation by running `mm version`

# Setup

1. Clone this repo (or fork it or download it somewhere as a ZIP)
2. Modify the script at `MyBot.cpp`. 
  * You may add other files or dependencies, just make sure to update the `.dockerignore` and `Dockerfile`s accordingly. We're here to help!
3. Run `mm play .`
  * This will build the bot in the given directory and then start a game where your bot fights against itself. 

Use `mm help` for more information!
