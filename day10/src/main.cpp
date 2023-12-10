#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include "utils.h"

using std::string, std::vector, std::make_pair;
using llint = long long int;
using coord = std::pair<int, int>;

const string input = "input";
const string test = "test";

std::map<char, vector<coord>> char_relative_coords = {
    {'|', {make_pair(0, 1), make_pair(0, -1)}},
    {'-', {make_pair(-1, 0), make_pair(1, 0)}},
    {'L', {make_pair(0, -1), make_pair(1, 0)}},
    {'J', {make_pair(0, -1), make_pair(-1, 0)}},
    {'7', {make_pair(-1, 0), make_pair(0, 1)}},
    {'F', {make_pair(0, 1), make_pair(1, 0)}},
    {'.', {}}
};

struct Tile {
    vector<coord> poss_steps;
    char tile_type;
};

void print_coord(coord& c) {
    cout << "coord x: " << c.first << " y: " << c.second << endl;
}

bool eq_coord(coord& one, coord& two) {
    return (one.first == two.first && one.second == two.second);
}

vector<coord> get_tiles_opts(char tile, coord loc) {
    vector<coord> rel_poss = char_relative_coords[tile];

    for (std::pair<int, int>& pos : rel_poss) {
        pos.first += loc.first;
        pos.second += loc.second;
    }

    return rel_poss;
}

Tile create_tile(char tile, coord loc) {
    return Tile{get_tiles_opts(tile, loc), tile};
}

vector<vector<Tile>> parse_map(string input_file) {
    vector<string> lines = utils::read_lines(input_file);
    vector<vector<Tile>> map;

    for (int y = 0; y < lines.size(); y++) {
        vector<Tile> row;
        for (int x = 0; x < lines[0].size(); x++) {
            coord pos = make_pair(x, y);
            row.push_back(create_tile(lines[y][x], pos));
        }

        map.push_back(row);
    }

    return map;
}

coord get_starting_pos(vector<vector<Tile>> const& tilemap) {
    coord start;
    for (int y = 0; y < tilemap.size(); y++) {
        for (int x = 0; x < tilemap[0].size(); x++) {
            if (tilemap[y][x].tile_type == 'S') {
                start = make_pair(x, y);
                return start;
            }
        }
    }

    return start;
}



int traverse(vector<vector<Tile>> const& tilemap, coord now, coord next) {
    coord last = next;

    Tile to_traverse = tilemap[next.second][next.first];

    if (to_traverse.tile_type == 'S') return 1;

    vector<coord> tile_opts = to_traverse.poss_steps;

    for (auto copt : tile_opts) {
        if (!eq_coord(copt, now)) {
            next = copt;
            break;
        }
    }

    return 1+traverse(tilemap, last, next);
}

void get_loop_path(vector<vector<Tile>> const& tilemap, coord now, coord next, std::map<coord, Tile>& loop) {
    coord last = next;

    Tile to_traverse = tilemap[next.second][next.first];
    
    loop[next] = tilemap[next.second][next.first];

    if (to_traverse.tile_type == 'S') {
        return;
    }

    vector<coord> tile_opts = to_traverse.poss_steps;
    for (auto copt : tile_opts) {
        if (!eq_coord(copt, now)) {
            next = copt;
            break;
        }
    }

    get_loop_path(tilemap, last, next, loop);
}

bool poss_moves_contains_poss(vector<coord> const& p1s, coord p2) {
    for (auto p1 : p1s) {
        if (p1.first == p2.first && p1.second == p2.second) return true;
    }
    return false;
}

vector<coord> get_poss_first(vector<vector<Tile>> const& tilemap, coord start) {
    vector<coord> opts;
    int sx = start.first;
    int sy = start.second;

    int low = 0;
    int highy = tilemap.size();
    int highx = tilemap[0].size();

    vector<int> rels = {-1, 0, 1};
    for (auto x : rels) {
        for (auto y : rels) {

            if (x==0 && y==0) continue;

            int cx = x+sx;
            int cy = y+sy;

            int clamp_x = std::clamp(cx, low, highx);
            int clamp_y = std::clamp(cy, low, highy);

            coord ccoord = make_pair(clamp_x, clamp_y);

            vector<coord> move_opts = tilemap[clamp_y][clamp_x].poss_steps;

            if (poss_moves_contains_poss(move_opts, start)) {
                opts.push_back(ccoord);
            } 
        }
    }

    return opts;
}


void part_A(string input_file) {
    vector<vector<Tile>> tilemap = parse_map(input_file);

    coord start = get_starting_pos(tilemap);
    coord next = get_poss_first(tilemap, start)[0];

    int count = traverse(tilemap, start, next);

    cout << "total: " << count << " farthest point: " << count/2 << endl;
}

bool map_has_element(std::map<coord,Tile> &m, coord k) {
    for (auto const& [key, tile] : m) {
        if (key.first == k.first && key.second == k.second && tile.tile_type != '\0') {
            // cout << " " << key.first << " " << key.second << " = " << k.first<< " " << k.second << " : " << tile.tile_type << endl;
            return true;
        }
    }

    return false;
}

void part_B(string input_file) {
    vector<vector<Tile>> tilemap = parse_map(input_file);

    cout << "Printing tile map" << endl;

    for (int y = 0; y < tilemap.size(); y++) {
        for (int x = 0; x < tilemap[0].size(); x++) {
            cout << tilemap[y][x].tile_type;
        }
        cout << endl;
    }

    cout << endl;

    coord start = get_starting_pos(tilemap);
    vector<coord> start_opts = get_poss_first(tilemap, start);
    coord next = start_opts[0];

    int start_opts_up = 0;
    int start_opts_down = 0;

    int tot_vert = 0;

    for (auto start_opt : start_opts) {
        tot_vert += start_opt.second;
    }

    if (tot_vert > 0) start_opts_down++;
    if (tot_vert < 0) start_opts_up++;

    std::map<coord, Tile> path;
    get_loop_path(tilemap, start, next, path);

    cout << endl << "path" << endl;
    for (auto const& [key, val] : path) {
        cout << key.first << " " << key.second << " - " << val.tile_type << endl;
    }

    int enclosed = 0;

    cout << "[MAP ANSWS HIGHLIGHTED]" << endl;

    for (int y = 0; y < tilemap.size(); y++) {
        int vert_bar_count = 0; // |
        int up = 0; // J L
        int down = 0; // F 7
        cout << endl;

        for (int x = 0; x < tilemap[0].size(); x++) {
            coord current = make_pair(x, y);
            char tile_type = path[current].tile_type;

            // cout << vert_bar_count;
            if (map_has_element(path, current) == true) {
                cout << tile_type;
                // cout << "#";
                if (tile_type == '|') vert_bar_count++; 
                if (tile_type == 'S') {
                    up += start_opts_up;
                    down += start_opts_down;
                }
                if (tile_type == 'J' || tile_type == 'L') up++;
                if (tile_type == 'F' || tile_type == '7') down++;
                
                if (up != 0 && down != 0) {
                    vert_bar_count++;
                    up = 0;
                    down = 0;
                }

                if (up == 2 || down == 2) {
                    up = 0;
                    down = 0;
                }
            } else {
                // cout << vert_bar_count << endl;
                if (vert_bar_count%2 != 0) {
                    cout << '#';
                    // cout << " is in: " << tile_type << " " << current.first << " " << current.second << endl;
                    enclosed++;
                } else {
                    cout << ' ';
                }
            }
        }
    }

    cout << "enclosed: "<< enclosed << endl;
}

int main() {
    part_B("input");
    // part_A(input);

}
