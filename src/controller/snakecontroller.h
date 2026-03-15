/**
 * @file snake_controller.h
 * @brief Заголовочный файл класса SnakeController
 *
 * Определяет контроллер для игры "Змейка", реализующий интерфейс
 * VirtualController
 */

#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include "../brick_game/snake/snake_model.h"
#include "virtualcontroller.h"

namespace s21 {

/**
 * @class SnakeController
 * @brief Контроллер для игры "Змейка"
 *
 * Наследуется от VirtualController и реализует логику управления игрой
 * "Змейка". Служит посредником между моделью игры (Snake) и представлением.
 */
class SnakeController : public VirtualConroller {
public:
  /**
   * @brief Конструктор по умолчанию
   *
   * Инициализирует модель игры "Змейка"
   */
  SnakeController();

  /**
   * @brief Удаленный конструктор копирования
   *
   * Запрещает копирование контроллера
   */
  SnakeController(const SnakeController &) = delete;

  /**
   * @brief Удаленный оператор присваивания
   *
   * Запрещает присваивание контроллеров
   */
  SnakeController &operator=(const SnakeController &) = delete;

  /**
   * @brief Деструктор
   *
   * Освобождает ресурсы, занятые моделью игры
   */
  ~SnakeController();

  /**
   * @brief Основной метод обработки игрового цикла
   * @param act Действие пользователя
   * @return GameInfo_t Структура с текущим состоянием игры
   *
   * Переопределяет виртуальный метод базового класса VirtualController.
   * Обрабатывает пользовательский ввод и возвращает актуальное состояние игры.
   */
  GameInfo_t play(UserAction_t act) override;

private:
  Snake *model_ = nullptr; ///< Указатель на модель игры "Змейка"
};

} // namespace s21

#endif