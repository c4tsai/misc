#ifndef __CELLS_H__
#define __CELLS_H__

#include <vector>
#include <memory>
#include <utility>


class PT {
  protected: 
    int id;
    std::vector<std::pair<int, int>> cells;
  public:
    PT();
    virtual ~PT();
    int get_id() const;
    std::vector<std::pair<int, int>> get_cells() const;
};

class Cell {
    int row;
    int col;
    std::vector<int> ids;
  public:
    Cell(int row, int col);
    virtual ~Cell();
    
    void add_id(int new_id);
    bool id_exist(int new_id) const;
    int count_claims() const;
};


class Board {
    int length;
    int height;
    std::unique_ptr<std::vector<std::vector<std::unique_ptr<Cell>>>> board;
    
  public: 
    Board(int length, int height);
    virtual ~Board();
    
    void add_id(int id, int x, int y);
    std::pair<int, int> get_dims();
    Cell* get_cell(int x, int y) const;
    Cell* get_cell(const std::pair<int, int> &p) const;
};

#endif