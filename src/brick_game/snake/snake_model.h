/**
 * @file model.h
 * @brief Заголовочный файл, содержащий объявления классов для игры "Змейка"
 */

#ifndef __MODEL_H__
#define __MODEL_H__

#include "../../common_objects/defines.h"
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

/**
 * @brief Очищает игровое поле
 * @param field Двумерный массив, представляющий игровое поле
 */
void field_clear(int **field);

/**
 * @brief Создает новое игровое поле
 * @return Указатель на созданное игровое поле
 */
int **field_create();

/**
 * @brief Перечисление состояний прикрепления
 */
typedef enum {
  NOTHING = 0,      ///< Нет прикрепления
  EATING,           ///< Состояние поедания
  ATTACHMENT_APPLE, ///< Прикрепленное яблоко
} Attachment_State;

/**
 * @brief Класс, представляющий точку на игровом поле
 */
class Point {
protected:
  int y; ///< Координата Y точки
  int x; ///< Координата X точки

public:
  /**
   * @brief Конструктор точки
   * @param y Координата Y (по умолчанию 0)
   * @param x Координата X (по умолчанию 0)
   */
  Point(int y = 0, int x = 0) : y(y), x(x) {}

  /**
   * @brief Конструктор копирования
   * @param other Другая точка для копирования
   */
  Point(const Point &other) : y(other.y), x(other.x) {}

  /**
   * @brief Оператор присваивания
   * @param other Другая точка для присваивания
   * @return Ссылка на текущую точку
   */
  Point operator=(const Point other) {
    if (*this != other) {
      y = other.y;
      x = other.x;
    }
    return *this;
  }

  /// @brief Получить координату X
  int get_x() const { return x; }

  /// @brief Получить координату Y
  int get_y() const { return y; }

  /// @brief Установить координату X
  void set_x(int x) { this->x = x; }

  /// @brief Установить координату Y
  void set_y(int y) { this->y = y; }

  /// @brief Оператор сравнения на равенство
  bool operator==(const Point other);

  /// @brief Оператор сравнения на неравенство
  bool operator!=(const Point other);

  /// @brief Проверка корректности координат точки
  bool is_no_correct();
};

/**
 * @brief Класс, представляющий яблоко на игровом поле (наследуется от Point)
 */
class ApplePoint : public Point {
public:
  /**
   * @brief Конструктор яблока
   * @param y Координата Y (по умолчанию 0)
   * @param x Координата X (по умолчанию 0)
   */
  ApplePoint(int y = 0, int x = 0) : Point(y, x) {}

  /**
   * @brief Конструктор преобразования из Point
   * @param point Точка для преобразования
   */
  ApplePoint(Point point) : Point(point) {}
};

/**
 * @brief Класс, представляющий змейку в игре
 */
class Snake {
protected:
  Direction dir{LEFT_DIR}; ///< Направление движения змейки
  vector<Point> body;      ///< Тело змейки (вектор точек)
  list<Point> apples_eating; ///< Список съеденных яблок
  ApplePoint apple_in_game;  ///< Текущее яблоко на поле
  GameInfo_t info;    ///< Информация о состоянии игры
  double time_ = 0;   ///< Время игры
  double snake_speed; ///< Скорость змейки
  bool attachment{false}; ///< Флаг прикрепления

  /**
   * @brief Создает змейку в начальном состоянии
   */
  void snake_create();

  /**
   * @brief Устанавливает новое яблоко на поле
   */
  void set_apple_in_game();

public:
  /// @brief Конструктор по умолчанию
  Snake() { snake_create(); }

  /// @brief Деструктор
  ~Snake() { field_clear(info.field); }

  /// @brief Загружает статистику игры
  void LoadStat();

  /// @brief Сохраняет статистику игры
  void SaveStat();

  /// @brief Изменяет состояние игры
  void change_state();

  /// @brief Движение влево
  bool Move_Left();

  /// @brief Движение вправо
  bool Move_Right();

  /// @brief Движение вверх
  bool Move_Up();

  /// @brief Движение вниз
  bool Move_Down();

  /// @brief Сдвиг змейки
  void Shift_Snake();

  /// @brief Расчет времени
  double time_calcul();

  /// @brief Сброс времени
  void time_is_null();

  /// @brief Проверка состояния змейки
  void check_snake();

  /**
   * @brief Проверка прикрепления к точке
   * @param point Точка для проверки
   * @return Состояние прикрепления
   */
  Attachment_State is_attachment(const Point &point);

  /// @brief Обработка начального состояния
  void on_start_state(UserAction_t sig);

  /// @brief Обработка состояния движения
  void on_moving_state(UserAction_t sig);

  /// @brief Обработка состояния прикрепления
  void on_attachment_state();

  /// @brief Обработка состояния появления яблока
  void on_spawn_apple_state();

  /// @brief Обработка состояния паузы
  void on_pause_state(UserAction_t sig);

  /// @brief Обработка состояния выхода
  void on_exit_state();

  /// @brief Обработка состояния завершения игры
  void on_gameover_state(UserAction_t sig);

  /// @brief Обработка состояния победы
  void on_win_state(UserAction_t sig);

  /**
   * @brief Обработка пользовательского ввода
   * @param sig Действие пользователя
   * @param hold Флаг удержания клавиши
   */
  void userInput(UserAction_t sig, bool hold);

  /**
   * @brief Обновление текущего состояния игры
   * @return Информация о текущем состоянии игры
   */
  GameInfo_t updateCurrentState();
};

#endif