#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "utils.h"

using std::vector, std::map, std::string;

const string camel_cards = "23456789TJQKA"; // Lowest to highest
const string camel_cards_b = "J23456789TQKA"; // Lowest to highest
const string input = "input";
const string test = "test";

struct Hand {
    string hand;
    int points;
    int sort_score;
};

void print_hands(vector<Hand> const& hands) {
    for (auto hand : hands) cout << hand.hand << " - " << hand.points << " sort_score " << hand.sort_score << endl;
}

int index_camel_cards(char card) {
    for (int i = 0; i < camel_cards.size(); i++) {
        if (card == camel_cards[i]) return i;
    }

    return -1;
}

int index_camel_cards_b(char card) {
    for (int i = 0; i < camel_cards_b.size(); i++) {
        if (card == camel_cards_b[i]) return i;
    }

    return -1;
}

vector<Hand> get_hands(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content);
    vector<Hand> hands;

    for (string line : lines) {
        auto vecs = utils::split(line, " ");
        string hand = vecs[0];
        int point = std::stoi(vecs[1]);

        hands.push_back({hand, point, 0});
    }
    
    return hands;
}

int count_jokers(Hand& hand) {
    int count = 0;
    for (auto c : hand.hand) {
        if (c == 'J') count++;
    }

    return count;
}

int match(Hand& hand) {
    string hand_str = hand.hand;

    int hand_score = 0;

    for (int i = 0; i < hand_str.size() - 1; i++) {
        for (int j = i+1; j < hand_str.size(); j++) {
            if (hand_str[i] == hand_str[j]) hand_score++;
        }
    }

    hand.sort_score = hand_score;

    int njokers = count_jokers(hand);

    return hand_score;
}

int match_b(Hand& hand) {
    string hand_str = hand.hand;

    int hand_score = 0;

    for (int i = 0; i < hand_str.size() - 1; i++) {
        for (int j = i+1; j < hand_str.size(); j++) {
            if (hand_str[i] == hand_str[j]) hand_score++;
        }
    }

    int njokers = count_jokers(hand);

    if (njokers == 1) {
        if (hand_score == 0) hand_score++;
        else if (hand_score == 1) hand_score = 3;
        else if (hand_score == 2) hand_score = 4;
        else if (hand_score == 3) hand_score = 6;
        else if (hand_score == 6) hand_score = 10;
    } else if (njokers == 2) {
        if (hand_score == 1) hand_score = 3;
        else if (hand_score == 2) hand_score = 6;
        else if (hand_score == 3) hand_score; // is this possible?
        else if (hand_score == 4) hand_score = 10;
    } else if (njokers == 3) {
        if (hand_score == 3) hand_score = 6;
        else if (hand_score == 4) hand_score = 10;
    } else if (njokers == 4) {
        hand_score = 10;
    }

    hand.sort_score = hand_score;

    return hand_score;
}

bool compare(Hand& first, Hand& second) {
    int score_first = match(first);
    int score_second = match(second);

    if (score_first == score_second) {
        for (int i = 0; i < first.hand.size(); i++) {
            if (first.hand[i] != second.hand[i]) {
                return index_camel_cards(first.hand[i]) < index_camel_cards(second.hand[i]);
            }
        }
    }

    return score_first < score_second;
}

bool compare_b(Hand& first, Hand& second) {
    int score_first = match_b(first);
    int score_second = match_b(second);

    if (score_first == score_second) {
        for (int i = 0; i < first.hand.size(); i++) {
            if (first.hand[i] != second.hand[i]) {
                return index_camel_cards_b(first.hand[i]) < index_camel_cards_b(second.hand[i]);
            }
        }
    }

    return score_first < score_second;
}

int part_A(string input_file) {
    vector<Hand> hands = get_hands(input_file);

    std::sort(hands.begin(), hands.end(), compare);

    int score = 0;

    for (int i = 0; i < hands.size(); i++) {
        score += hands[i].points * (i+1);
    }

    return score;
}

int part_B(string input_file) {
    vector<Hand> hands = get_hands(input_file);

    std::sort(hands.begin(), hands.end(), compare_b);

    int score = 0;

    for (int i = 0; i < hands.size(); i++) {
        score += hands[i].points * (i+1);
    }

    print_hands(hands);

    return score;
}

void test_A() {
    auto val = part_A(test);
    cout << "[test A] " << val << endl;
}

void test_B() {
    auto val = part_B(test);
    cout << "[test B] " << val << endl;
}

int main() {
    // test_A(); 
    // test_B();

    // auto val_A = part_A(input);
    // cout << "(A) " << val_A << endl;
    auto val_B = part_B(input);
    cout << "(B) " << val_B << endl;
}
