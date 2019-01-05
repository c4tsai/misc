#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

#include "cells.h"
using namespace std;

PT::PT() {
    cells = vector<pair<int, int>> {};
}

PT::~PT() {}

int PT::get_id() const {
    return id;
}

vector<pair<int, int>> PT::get_cells() const {
    return cells;
}

Cell::Cell(int row, int col): row{row}, col{col}, ids{vector<int>()} {}

Cell::~Cell() {};

void Cell::add_id(int new_id) {
    ids.emplace_back(new_id);
}

bool Cell::id_exist(int new_id) const {
    int n = count_if(ids.begin(), ids.end(), [&] (int i) {return (i == new_id);});
    return (n > 0);
}

int Cell::count_claims() const {
    int n = ids.size(); return n;
}

Board::Board(int length, int height): length{length}, height{height} {
    vector<vector<unique_ptr<Cell>>> out;
    for (int i = 0; i < length; i++) {
        out.emplace_back(vector<unique_ptr<Cell>>());
        for (int j = 0; j < height; j++) {
            out.at(i).emplace_back(unique_ptr<Cell> (new Cell(i+1, j+1)));
        }
    }
    board = make_unique<vector<vector<unique_ptr<Cell>>>> (move(out));
}

Board::~Board() {}

void Board::add_id(int id, int x, int y) {
    board->at(x).at(y)->add_id(id);
}

pair<int, int> Board::get_dims() const {
    return pair<int,int>(length, height);
}

Cell* Board::get_cell(int x, int y) const {
    return &*(board->at(x).at(y));
}

Cell* Board::get_cell(const pair<int, int> &p) const {
    int x = p.first; int y = p.second;
    return &*(board->at(x).at(y));
}
