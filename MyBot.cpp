#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "Game_Api.h"
using json = nlohmann::json;

#define RESPONSE_SECS 1
#define RESPONSE_NSECS 0

#include <iostream>
using namespace std;

int main() {
	Game_Api * api;
	int my_player_num = 0;
	while(1){
		char* buf = NULL;
		size_t size = 0;

		getline(&buf, &size, stdin);
		json data = json::parse(buf);
		if(data["type"] == "map"){
			my_player_num = data["player_id"];
			api = new Game_Api(my_player_num, data["map"]);
		} else {
			 api->update(data["game_data"]);
			 if (my_player_num == 1) {
			 vector<vector<node_id_t>> sp = api->shortest_paths(0, 5);
			 for (vector<node_id_t> vec : sp) {
				 for (node_id_t node : vec ) {
					 api->log(std::to_string(node));
				 }
				 cerr << "\n\n";
			 }

			 vector<Game_Api::Monster> nearest_monsters = api->nearest_monsters(0, 1);
			 for (Game_Api::Monster m : nearest_monsters) {
				 cerr << "monster:" << m._location << "\n";
			 }
		 }
             vector<int> adjacent = api->get_adjacent_nodes(api->get_self()._location);
             api->submit_decision(adjacent[0], "Rock");
		 	 fflush(stdout);
		}

		free(buf);
	}
}
