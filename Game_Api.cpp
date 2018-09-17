//
// Created by alvar on 9/1/2018.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "Game_Api.h"
using std::cout;

Game_Api::Player::Player(string name, int health, int speed, node_id_t location, int movement_counter, Game_Api* api) {
    this->_name = name;
    this->_health = health;
    this->_speed = speed;
    this->_location = location;
    this->_destination = location;
    this->_movement_counter = movement_counter;
    this->_api = api;
    this->_stance = "no_stance";
    this->_rock = 0;
    this->_paper = 0;
    this->_scissors = 0;
}

Game_Api::Monster::Monster(string name, int health, string stance, int speed,  node_id_t location, int attack, json deathfx_json, Game_Api * api) {
    json death_fx = deathfx_json;
    this->_death_effects._health = deathfx_json["Health"];
    this->_death_effects._paper = deathfx_json["Paper"];
    this->_death_effects._scissors = deathfx_json["Scissors"];
    this->_death_effects._rock = deathfx_json["Rock"];
    this->_death_effects._speed = deathfx_json["Speed"];

    this->_name = name;
    this->_health = health;
    this->_location = location;
    this->_respawn_counter = 7 - speed;
    this->_respawn_rate = 7 - speed;
    this->_attack = attack;
    this->_stance = stance;
    this->_dead = false;
    this->_api = api;
}

void Game_Api::Player::update(json player_json) {
    //remove unit from previous location in case it has moved
    if (player_json["Location"] != this->_location) {
      std::cerr << "location changed" << "\n";
        Node& prev_location = _api->nodes[_location];
        for (unsigned i = 0; i < prev_location.players.size(); i++) {
            if (prev_location.players[i] == this) {
                prev_location.players.erase(prev_location.players.begin() + i);
            }
        }
        _location = player_json["Location"];
        _api->nodes[_location].players.push_back(this);
    }
    this->_dead = player_json["Dead"];
    this->_destination = player_json["Destination"];
    this->_health = player_json["Health"];
    this->_movement_counter = player_json["Movement Counter"];
    this->_name = player_json["Name"];
    this->_paper = player_json["Paper"];
    this->_rock = player_json["Rock"];
    this->_scissors = player_json["Scissors"];
    this->_speed = player_json["Speed"];
    this->_stance = player_json["Stance"];

    //missing exp and victory points
}

void Game_Api::Monster::update(json monster_json) {
    int counter = monster_json["Movement Counter"];
    int speed = monster_json["Speed"];

    this->_attack = monster_json["Attack"];
    this->_base_health = monster_json["Base Health"];
    this->_dead = monster_json["Dead"];

    json deathfx_json = monster_json["Death Effects"];
    this->_death_effects._health = deathfx_json["Health"];
    this->_death_effects._paper = deathfx_json["Paper"];
    this->_death_effects._scissors = deathfx_json["Scissors"];
    this->_death_effects._rock = deathfx_json["Rock"];
    this->_death_effects._speed = deathfx_json["Speed"];

    this->_health = monster_json["Health"];
    this->_location = monster_json["Location"];
    this->_respawn_counter = counter - speed;
    this->_respawn_rate = 7 - speed;
    this->_name = monster_json["Name"];
    this->_stance = monster_json["Stance"];
}

Game_Api::Game_Api(int player_number, string json_string) {
    _this_player_number = player_number;
    json map = json::parse(json_string);
    json nodes_json = map["Nodes"];
    json edges_json = map["Edges"];
    json monsters_json = map["Monsters"];

    for (node_id_t i = 0; i < (int)nodes_json.size(); i++) {
        nodes.push_back(Node());
    }

    _player1 = new Player("player1", INIT_PLAYER_HEALTH, 0, 0, 7, this);
    _player2 = new Player("player2", INIT_PLAYER_HEALTH, 0, 0, 7, this);

    nodes[0].players.push_back(_player1);
    nodes[0].players.push_back(_player2);

    for (json edge : edges_json) {
        json adj = edge["Adjacents"];
        nodes[adj[0]].adjacent.push_back(adj[1]);
        nodes[adj[1]].adjacent.push_back(adj[0]);
    }

    for (json mon : monsters_json) {
        Monster monster(mon["Name"], mon["Health"], mon["Stance"], mon["Speed"], mon["Location"], mon["Attack"], mon["Death Effects"], this);
        all_monsters.push_back(monster);
    }

    for (unsigned i = 0; i < all_monsters.size(); i ++) {
        Monster* m = &(all_monsters[i]);
        nodes[m->_location].monsters.push_back(m);
    }
}

// void Game_Api::print() {
//     for (Monster mon : all_monsters) {
//         std::cerr << mon._name << "\n";
//         std::cerr << mon._location << "\n";
//         std::cerr << mon._destination << "\n";
//     }
//     int idx = 0;
//     for (Node node : nodes) {
//         for (node_id_t i : node.adjacent) {
//             std::cerr << "Node " << idx << " adjacent: " << i << "\n";
//         }
//         for (Monster* mon : node.monsters) {
//             std::cerr << "This node contains: " << mon->_name << "\n";
//         }
//         for (Player* player : node.Players) {
//             std::cerr << "This node contains: " << player->_name << "\n";
//         }
//         idx++;
//     }
// }

void Game_Api::update(json json_string) {
    _player1->update(json_string[0]);
    _player2->update(json_string[1]);
    for (unsigned i = 2; i < all_monsters.size(); i++) {
          all_monsters[i - 2].update(json_string[i]);
    }
}

vector<int> Game_Api::get_adjacent_nodes(int node_location) {
    vector<int> adjacent;
    for (node_id_t node_id : nodes[node_location].adjacent) {
      adjacent.push_back(node_id);
    }
    return adjacent;
}

void Game_Api::submit_decision(int destination, string stance) {
    printf("{\"Stance\": \"%s\", \"Dest\": %d}\n", stance.c_str(), destination);
}

Game_Api::Player* Game_Api::get_self() {
    if (_this_player_number == 1) {
        return _player1;
    } else {
        return _player2;
    }
}

Game_Api::Player* Game_Api::get_opponent() {
    if (_this_player_number == 1) {
        return _player2;
    } else {
        return _player1;
    }
}
