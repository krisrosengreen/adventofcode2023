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
    cout << "traverse: " << now.first << " " << now.second << endl;

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

bool poss_moves_contains_poss(vector<coord> const& p1s, coord p2) {
    for (auto p1 : p1s) {
        if (p1.first == p2.first && p1.second == p2.second) return true;
    }
    return false;
}

coord get_poss_first(vector<vector<Tile>> const& tilemap, coord start) {
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
                return ccoord;
            } 
        }
    }

    return coord{-1,-1};
}


void part_A(string input_file) {
    vector<vector<Tile>> tilemap = parse_map(input_file);

    coord start = get_starting_pos(tilemap);
    coord next = get_poss_first(tilemap, start);

    print_coord(start);
    print_coord(next);

    int count = traverse(tilemap, start, next);

    cout << "total: " << count << " farthest point: " << count/2 << endl;
}

int main() {
    part_A(input);
}
