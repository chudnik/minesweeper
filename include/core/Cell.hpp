#pragma once

class Cell {
private:
    bool is_mine_ = false;
    bool is_revealed_ = false;
    bool is_flagged_ = false;
    int count_neighbor_mines_ = 0;

public:
    bool isMine() const { return is_mine_; };
    bool isRevealed() const { return is_revealed_; }
    bool isFlagged() const { return is_flagged_; }
    int getCountNeighborMines() const { return count_neighbor_mines_; }

    void setMine(bool mine) { is_mine_ = mine; }
    void reveal() { is_revealed_ = true; }
    void hide() { is_revealed_ = false; }
    void toggleFlag() { is_flagged_ = !is_flagged_; }
    void setCountNeighborMines(int count) { count_neighbor_mines_ = count; }
    void addNeighborMine() { count_neighbor_mines_++; }

    bool isValid() const {
        return !(is_revealed_ && is_flagged_);
    }
};
