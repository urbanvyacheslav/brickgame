/**
 * @file tetris_controller.h
 * @brief Заголовочный файл класса TetrisController
 * @defgroup Tetris Группа классов Тетриса
 *
 * Определяет контроллер для игры "Тетрис", реализующий интерфейс
 * VirtualController. Служит прослойкой между логикой игры и пользовательским
 * интерфейсом.
 */

#ifndef TETRIS_CONTROLLER_H
#define TETRIS_CONTROLLER_H

#include "virtualcontroller.h"
extern "C" {
#include "../brick_game/tetris/fsm.h" ///< Внешний C-интерфейс конечного автомата Тетриса
}

namespace s21 {

/**
 * @class TetrisController
 * @brief Контроллер для игры "Тетрис"
 * @ingroup Tetris
 *
 * Наследуется от VirtualController и реализует:
 * - Обработку пользовательского ввода
 * - Управление игровым процессом
 * - Взаимодействие с конечным автоматом игры (FSM)
 *
 * @note Для работы использует C-реализацию конечного автомата (fsm.h)
 */
class TetrisController : public VirtualConroller {
public:
  /**
   * @brief Основной игровой цикл
   * @param act Действие пользователя (ввод с клавиатуры)
   * @return GameInfo_t Текущее состояние игры для отрисовки
   *
   * Обрабатывает пользовательский ввод и возвращает актуальное состояние игры.
   * Реализует абстрактный метод базового класса VirtualController.
   *
   * @see VirtualController::play()
   */
  GameInfo_t play(UserAction_t act) override;
};

} // namespace s21

#endif