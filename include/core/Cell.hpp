#pragma once

#include <cstdint>

namespace minesweeper {

    class Cell {
    private:
        enum BitMask : uint8_t {
            MINE_BIT = 0x01,
            REVEALED_BIT = 0x02,
            FLAGGED_BIT = 0x04,
            NEIGHBORS_MASK = 0xF8
        };

        uint8_t data_;

        void setBit(BitMask mask, bool value) {
            data_ = value ? (data_ | mask) : (data_ & ~mask);
        }

        bool checkBit(BitMask mask) const {
            return data_ & mask;
        }

    public:
        Cell() : data_(0) {}

        bool isMine() const { return checkBit(MINE_BIT); }
        bool isRevealed() const { return checkBit(REVEALED_BIT); }
        bool isFlagged() const { return checkBit(FLAGGED_BIT); }
        uint8_t neighborMines() const { return data_ >> 3; }

        void setMine(bool mine) { setBit(MINE_BIT, mine); }
        void setRevealed(bool revealed) { setBit(REVEALED_BIT, revealed); }
        void setFlagged(bool flagged) { setBit(FLAGGED_BIT, flagged); }
        void setNeighborMines(uint8_t count) { data_ = (data_ & ~NEIGHBORS_MASK) | ((count & 0x1F) << 3); }

        void incrementNeighborMines() {
            if (neighborMines() < 8) {
                setNeighborMines(neighborMines() + 1);
            }
        }

        void decrementNeighborMines() {
            if (neighborMines() > 0) {
                setNeighborMines(neighborMines() - 1);
            }
        }

        bool isValidState() const {
            return !(isRevealed() && isFlagged());
        }
    };

}  // namespace minesweeper
