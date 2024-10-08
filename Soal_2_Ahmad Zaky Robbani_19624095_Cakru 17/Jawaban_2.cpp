#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
using namespace std;

class Robot {
    private:

    public:
    string name;
    int HP;
    int ATK;
    int DEF = 0;
    int SPD = 1;
    void attack(Robot& opp) {
        this_thread::sleep_for(chrono::milliseconds(1000/SPD - SPD));
        int damage = ATK * (100 - opp.DEF) / 100;
        while (opp.HP > 0 && HP > 0) {
            if (damage == 0) {
                cout << name << " attacks " << opp.ID << " for " << 1 << " damage!" << endl;
                opp.HP -= 1;
                this_thread::sleep_for(chrono::milliseconds(5000/SPD - SPD));
            } else {
                cout << name << " attacks " << opp.ID << " for " << damage << " damage!" << endl;
                opp.HP -= damage;
                this_thread::sleep_for(chrono::milliseconds(5000/SPD - SPD));
            }
        }
    }
};

class Battle {
    private:

    public:
    Robot player1, player2;
    void start_fight() {
        thread player_1_attack(player1.attack, ref(player2));
        thread player_2_attack(player2.attack, ref(player1));
        player_1_attack.join();
        player_2_attack.join();
        if (player1.HP <= 0 && player2.HP <= 0) {
            cout << player1.ID << " is Defeated!" << endl;
            cout << player2.ID << " is Defeated!" << endl;
            cout << "It is a tie!" << endl;
        } else if (player1.HP <= 0) {
            cout << player1.ID << " is Defeated!" << endl;
            cout << player2.ID << " has " << player2.HP << " HP remaining..." << endl;
            cout << player2.ID << " wins!" << endl;
        } else {
            cout << player2.ID << " is Defeated!" << endl;
            cout << player1.ID << " has " << player1.HP << " HP remaining..." << endl;
            cout << player1.ID << " wins!" << endl;
        }
    }
};

class Game {
    public:
    vector <Robot> robot_list = {};
    vector <Battle> battle_log = {};
    void add_robot() {
        cout << "---------------------------------------------" << endl;
        Robot robo;
        cout << "Register the name of the robot : "; cin >> robo.name;
        int stat_points = 400;
        while (stat_points != 0) {
            int hp, atk, def, spd = 0;
            cout << "You have " << stat_points << " stat points, allocate it to your likings!" << endl;
            cout << "HP = "; cin >> hp; robo.HP = hp;
            cout << "ATK = "; cin >> atk; robo.ATK = atk;
            cout << "DEF = "; cin >> def; robo.DEF = def;
            cout << "SPD = "; cin >> spd; robo.SPD = spd;
            stat_points -= hp + atk + def + spd;
        }
        robot_list.push_back(robo);
    }

    void show_robots() {
        cout << robot_list.size() << " robots available" << endl;
        for (Robot robots : robot_list) {
            cout << robots.name;
            printf(" (HP: %d, ATK: %d, DEF: %d, SPD: %d)\n", 
            robots.HP, robots.ATK, robots.DEF, robots.SPD);
        }
    }

    Game() {
        cout << "Welcome to Robot Battle!" << endl;
        if (robot_list.size() == 0) {
            cout << "No robots registered currently" << endl;
        }
        char reg = 'Y';
        while (reg == 'Y') {
            add_robot();
            cout << "---------------------------------------------" << endl;
            cout << "Would you like to register a new robot? (Y/N)" << endl;
            cin >> reg;
        }
        cout << "---------------------------------------------" << endl;
    }

    void start_game() {
        Battle fight;
        string roboID1, roboID2;
        show_robots();
        cout << "Select the first robot: ";
        cin >> roboID1;
        for (Robot option : robot_list) {
            if (option.name == roboID1) {
                fight.player1 = option;
            }
        }
        cout << endl << "Select the second robot: ";
        cin >> roboID2;
        for (Robot option : robot_list) {
            if (option.name == roboID2) {
                fight.player1 = option;
            }
        }
        cout << endl;
        fight.start_fight();
        battle_log.push_back(fight);
        char yesorno;
        cout << "Would you like to have another battle? (Y/N)" << endl;
        cin >> char;
        if (char == 'Y') {
            start_game();
        } else {cout << "Game ends" << endl;}
    }
};


int main() {
    Game game;
    game.start_game();
}