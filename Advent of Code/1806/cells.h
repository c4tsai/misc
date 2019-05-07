#ifndef __CELLS_H__
#define __CELLS_H__

#include <vector>
#include <memory>
#include <utility>

class Cell {
    int row;
    int col;
    std::vector<int> ids;
  public:
    Cell(int row, int col);
    virtual ~Cell();
    
    void add_id(int new_id);
    bool id_exist(int new_id) const;
    int count_id() const;
};


class Board {
    int length;
    int height;
    std::unique_ptr<std::vector<std::vector<std::unique_ptr<Cell>>>> board;
    
  public: 
    Board(int length, int height);
    virtual ~Board();
    
    void add_id(int id, int x, int y);
    std::pair<int, int> get_dims() const;
    Cell* get_cell(int x, int y) const;
    Cell* get_cell(const std::pair<int, int> &p) const;
};

#endif
