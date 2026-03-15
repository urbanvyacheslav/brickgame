/**
 * @file virtual_controller.h
 * @brief Заголовочный файл абстрактного класса VirtualController
 * @defgroup AbstractControllers Абстрактные контроллеры
 *
 * Определяет базовый интерфейс для всех игровых контроллеров в проекте.
 * Реализует паттерн "Интерфейс" для единообразного управления разными играми.
 */

#ifndef VIRTUAL_CONTROLLER_H
#define VIRTUAL_CONTROLLER_H

#include "../common_objects/defines.h" ///< Заголовочный файл с определениями типов

/**
 * @class VirtualConroller
 * @brief Абстрактный базовый класс игровых контроллеров
 * @ingroup AbstractControllers
 *
 * Предоставляет чистый виртуальный интерфейс для:
 * - Управления игровым процессом
 * - Обработки пользовательского ввода
 * - Получения состояния игры
 *
 * @note Все конкретные реализации игровых контроллеров должны наследовать этот
 * класс и реализовывать его методы.
 */
class VirtualConroller {
public:
  /**
   * @brief Виртуальный деструктор
   *
   * Обеспечивает корректное удаление производных классов
   * через указатель на базовый класс.
   */
  virtual ~VirtualConroller() {}

  /**
   * @brief Основной игровой цикл (чисто виртуальная функция)
   * @param act Действие пользователя (enum UserAction_t)
   * @return GameInfo_t Текущее состояние игры
   *
   * @warning Должен быть реализован в производных классах.
   * @see SnakeController, TetrisController
   */
  virtual GameInfo_t play(UserAction_t act) = 0;
};

#endif