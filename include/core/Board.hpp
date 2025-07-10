#pragma once

#include <stdexcept>
#include <vector>

#include "Cell.hpp"

namespace minesweeper {

    class Board {
    private:
        std::vector<Cell> cells_;
        uint16_t width_, height_;

        constexpr bool inBounds(uint16_t x, uint16_t y) const noexcept {
            return x < width_ && y < height_;
        }

    public:
        Board(uint16_t width, uint16_t height)
                : width_(width), height_(height), cells_(width * height) {}

        constexpr Cell &at(uint16_t x, uint16_t y) {
            if (!inBounds(x, y)) {
                throw std::out_of_range("Cell coordinates out of bounds");
            }
            return cells_[x + y * width_];
        }

        constexpr const Cell &at(uint16_t x, uint16_t y) const {
            if (!inBounds(x, y)) {
                throw std::out_of_range("Cell coordinates out of bounds");
            }
            return cells_[x + y * width_];
        }

        constexpr uint16_t width() const noexcept { return width_; }

        constexpr uint16_t height() const noexcept { return height_; }

        void placeMine(uint16_t x, uint16_t y) noexcept {
            cells_[y * width_ + x].setMine(true);
        }

        void removeMine(uint16_t x, uint16_t y) noexcept {
            cells_[y * width_ + x].setMine(false);
        }

        void toggleFlag(uint16_t x, uint16_t y) noexcept {
            cells_[y * width_ + x].toggleFlag();
        }

        bool revealCell(uint16_t x, uint16_t y) noexcept {
            return cells_[y * width_ + x].reveal();
        }

        void reset() {
            for (auto &cell: cells_) {
                cell.reset();
            }
        }
    };

}  // namespace minesweeper
