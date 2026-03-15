/**
 * @file game_controller.h
 * @brief Заголовочный файл класса GameController
 *
 * Определяет интерфейс для управления различными игровыми режимами
 */

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

// #include "../common_objects/objects.h"
#include "snakecontroller.h"
#include "tetriscontroller.h"

namespace s21 {

/**
 * @class GameController
 * @brief Основной контроллер для управления игровыми режимами
 *
 * Реализует паттерн "Стратегия" для переключения между разными играми
 */
class GameController {
public:
  /// @brief Конструктор по умолчанию
  GameController() {}

  /// @brief Удаленный конструктор копирования
  GameController(const GameController &) = delete;

  /// @brief Удаленный оператор присваивания
  GameController &operator=(const GameController &) = delete;

  /// @brief Деструктор
  ~GameController();

  /**
   * @brief Установка текущей игры
   * @param game Идентификатор игры (1 - Змейка, 2 - Тетрис и т.д.)
   */
  void setGame(int game);

  /**
   * @brief Основной игровой цикл
   * @param act Действие пользователя
   * @return Информация о текущем состоянии игры
   */
  GameInfo_t play(UserAction_t act);

private:
  VirtualConroller *controller_ =
      nullptr; ///< Указатель на текущий игровой контроллер
};

} // namespace s21

#endif