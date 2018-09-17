//
// Created by alvar on 9/1/2018.
//

#ifndef GAME_API_GAME_API_H
#define GAME_API_GAME_API_H
#include "includes/json.hpp"

#define BASE_MOVEMENT_COUNTER 7
#define INIT_PLAYER_HEALTH 10

using std::string;
using std::vector;
using json = nlohmann::json;

typedef int node_id_t;
class Game_Api {

private:
    // struct Unit { //make everything const
    //     Unit(string name, int h, int k, int s, node_id_t loc, Game_Api* api);
    //     void update(json unit_json);
    //     string _name;
    //     int _health;
    //     int _kung_fu;
    //     int _speed;
    //     int _movement_counter;
    //     node_id_t _location;
    //     node_id_t _destination;
    //     int _exp;
    //     int _victory_points;
    //     Game_Api* _api;
    // };

    struct DeathEffects {
        int _rock;
        int _paper;
        int _scissors;
        int _speed;
        int _health;
    };

    struct Monster {
        Monster(string name, int health, string stance, int speed, node_id_t location, int attack, json deathfx, Game_Api * api);
        void update(json unit_json);
        bool _dead;
        string _name;
        int _health;
        int _base_health;
        string _stance;
        int _respawn_counter;
        int _respawn_rate;
        node_id_t _location;
        int _attack;
        DeathEffects _death_effects;
        Game_Api* _api;
    };

    struct Player {
        Player(string name, int health, int speed, node_id_t location, int movement_counter, Game_Api* api);
        void update(json unit_json);
        bool _dead;
        string _name;
        int _health;
        string _stance;
        int _speed;
        node_id_t _location;
        node_id_t _destination;
        DeathEffects _death_effects;
        int _movement_counter;
        int _rock;
        int _paper;
        int _scissors;
        Game_Api* _api;
    };

    struct Node {
        vector<node_id_t> adjacent;
        vector<Player*> players;
        vector<Monster*> monsters;
    };

public:
    Player * _player1;
    Player * _player2;
    vector<Monster> all_monsters; //doesnt include players
    vector<Node> nodes;
    explicit Game_Api(int player_number, string json_str);
    void update(json json_str);
    void print();
    void submit_decision(int destination, string stance);
    Player* get_self();
    Player* get_opponent();
    vector<int> get_adjacent_nodes(int location);
private:
    int _this_player_number;
};


#endif //MM2018_GAME_LOGIC_GAME_API_H
