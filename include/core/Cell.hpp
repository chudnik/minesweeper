/**
 * @file Cell.hpp
 * @brief Реализация клетки игрового поля "Сапёр"
 */
#pragma once

#include <cstdint>

namespace minesweeper {

/**
 * @class Cell
 * @brief Класс, представляющий одну клетку игрового поля
 */
    class Cell {
    private:
        static constexpr uint8_t MAX_NEIGHBORS = 8;
        static constexpr uint8_t MINE_BIT = 0x01;
        static constexpr uint8_t REVEALED_BIT = 0x02;
        static constexpr uint8_t FLAGGED_BIT = 0x04;
        static constexpr uint8_t NEIGHBORS_MASK = 0xF8;
        static constexpr uint8_t NEIGHBORS_SHIFT = 3;

        uint8_t data_ = 0;

        template<uint8_t Mask>
        constexpr bool checkBit() const noexcept {
            return data_ & Mask;
        }

        template<uint8_t Mask>
        constexpr void setBit(bool state) noexcept {
            data_ = state ? (data_ | Mask) : (data_ & ~Mask);
        }

    public:
        /**
         * @brief Возвращает максимально возможное количество соседей
         */
        static constexpr uint8_t maxNeighbors() noexcept { return MAX_NEIGHBORS; }

        /**
         * @brief Проверяет наличие мины в клетке
         */
        constexpr bool isMine() const noexcept { return checkBit<MINE_BIT>(); }

        /**
         * @brief Проверяет открыта ли клетка
         */
        constexpr bool isRevealed() const noexcept {
            return checkBit<REVEALED_BIT>();
        }

        /**
         * @brief Проверяет наличие флага в клетке
         */
        constexpr bool isFlagged() const noexcept {
            return checkBit<FLAGGED_BIT>();
        }

        /**
         * @brief Устанавливает/убирает мину в клетке
         * @return true если операция выполнена успешно
         */
        constexpr bool setMine(bool mine) noexcept {
            if (isRevealed()) return false;
            setBit<MINE_BIT>(mine);
            return true;
        }

        /**
         * @brief Открывает клетку
         * @return true если клетка была успешно открыта
         */
        constexpr bool reveal() noexcept {
            if (isFlagged()) return false;
            setBit<REVEALED_BIT>(true);
            return true;
        }

        /**
         * @brief Переключает состояние флага в клетке
         * @return true если флаг был изменён
         */
        constexpr bool toggleFlag() noexcept {
            if (isRevealed()) return false;
            setBit<FLAGGED_BIT>(!isFlagged());
            return true;
        }

        /**
         * @brief Возвращает количество мин в соседних клетках
         */
        constexpr uint8_t neighborMines() const noexcept {
            return data_ >> NEIGHBORS_SHIFT;
        }

        /**
         * @brief Устанавливает количество соседних мин
         * @param count Количество мин (0-MAX_NEIGHBORS)
         * @note Если count > MAX_NEIGHBORS, будет установлено MAX_NEIGHBORS
         */
        constexpr void setNeighborMines(uint8_t count) noexcept {
            data_ = (data_ & ~NEIGHBORS_MASK) |
                    ((count > MAX_NEIGHBORS ? MAX_NEIGHBORS : count)
                            << NEIGHBORS_SHIFT);
        }

        /**
         * @brief Сбрасывает состояние клетки (мина, флаг, открытость)
         */
        constexpr void reset() noexcept { data_ &= NEIGHBORS_MASK; }

        /**
         * @brief Полностью перезаписывает состояние клетки
         * @param new_state Состояние клетки
         */
        constexpr void deserialize(uint8_t new_state) noexcept {
            data_ = new_state;
        }

        /**
         * @brief Возвращает состояние клетки
         */
        constexpr uint8_t serialize() const noexcept { return data_; }
    };

}  // namespace minesweeper
