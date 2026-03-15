/**
 * @file fsm.h
 * @brief Заголовочный файл конечного автомата для игры Тетрис
 *
 * Содержит объявления функций и структур для управления игровым процессом
 */

#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../common_objects/defines.h"
#include "../../common_objects/objects.h"

/**
 * @brief Структура параметров игры
 */
typedef struct game_params {
  GameInfo_t info;    ///< Текущее состояние игры
  Figure_t block;     ///< Текущая фигура
  time_info time;     ///< Временные параметры
  Figure_t nextblock; ///< Следующая фигура
  int rand_number; ///< Случайное число для генерации
} params_t;

/* Основные игровые функции */

/// @brief Постановка игры на паузу
void pause();

/// @brief Генерация новой фигуры
void spawn();

/// @brief Движение фигуры вниз
void movedown();

/// @brief Движение фигуры вправо
void moveright();

/// @brief Движение фигуры влево
void moveleft();

/// @brief Сдвиг фигуры
void shifting();

/// @brief Вращение фигуры
void rotate();

/// @brief Движение фигуры вверх (ускоренное падение)
void moveup();

/// @brief Обработка завершения игры
void gameover();

/// @brief Выход из игры
void exitstate();

/// @brief Инициализация игры
void InitGame();

/**
 * @brief Получение игровых данных
 * @return Указатель на структуру параметров игры
 */
params_t *data();

/**
 * @brief Обработка пользовательского ввода
 * @param action Действие пользователя
 * @param hold Флаг удержания клавиши
 */
void userInput(UserAction_t action, int hold);

/* Функции работы с игровым полем */

/**
 * @brief Инициализация игрового поля
 * @param width Ширина поля
 * @param height Высота поля
 * @return Указатель на созданное поле
 */
int **InitField(int width, int height);

/**
 * @brief Освобождение памяти игрового поля
 * @param field Указатель на поле
 * @param height Высота поля
 */
void RemoveField(int **field, int height);

/// @brief Очистка игровых данных
void RemoveGame();

/* Функции работы с фигурами */

/**
 * @brief Создание новой фигуры
 * @param figure Указатель на структуру фигуры
 * @param new_fig Тип новой фигуры
 */
void CreateBlock(Figure_t *figure, int new_fig);

/**
 * @brief Проверка столкновения фигуры
 * @param figure Проверяемая фигура
 * @param info Информация о игровом поле
 * @return Результат проверки (1 - столкновение, 0 - нет)
 */
int collision(Figure_t figure, GameInfo_t *info);

/**
 * @brief Копирование фигуры
 * @param figure Исходная фигура
 * @param newfigure Новая фигура
 */
void CopyBlock(Figure_t *figure, Figure_t *newfigure);

/**
 * @brief Очистка поля от фигуры
 * @param field Игровое поле
 * @param height Высота поля
 * @param width Ширина поля
 */
void FigureTakeNul(int **field, int height, int width);

/* Вспомогательные функции */

/**
 * @brief Проверка заполненных линий (тетрис)
 * @param info Информация о игровом поле
 * @return Количество заполненных линий
 */
int checkTetris(GameInfo_t *info);

/// @brief Загрузка статистики
void LoadStat(GameInfo_t *info);

/// @brief Сохранение статистики
void SaveStat(const GameInfo_t *info);

/**
 * @brief Проверка возможности вращения
 * @param figure Фигура для проверки
 * @param info Информация о игровом поле
 * @return Результат проверки (1 - можно вращать, 0 - нельзя)
 */
int checkRotate(Figure_t figure, GameInfo_t *info);

/**
 * @brief Проверка "прилипания" фигуры
 * @param figure Текущая фигура
 * @param old_figure Предыдущая фигура
 * @param info Информация о игровом поле
 * @return Результат проверки (1 - прилипла, 0 - нет)
 */
int checkStick(Figure_t figure, Figure_t old_figure, const GameInfo_t *info);

/**
 * @brief Обработка прилипания фигуры
 * @param figure Фигура
 * @param info Информация о игровом поле
 */
void attachment(Figure_t figure, GameInfo_t *info);

/**
 * @brief Обновление игрового состояния
 * @return Текущее состояние игры
 */
GameInfo_t updateCurrentState();

/// @brief Альтернативное обновление состояния
void updateCurrentState_2();

/**
 * @brief Проверка столкновения при завершении игры
 * @param figure Фигура
 * @param info Информация о игровом поле
 * @return Результат проверки (1 - столкновение, 0 - нет)
 */
int GameOverCollision(Figure_t figure, const GameInfo_t *info);

/**
 * @brief Обновление уровня игры
 * @param score Текущий счет
 * @param level Указатель на текущий уровень
 * @param level_time Указатель на время уровня
 */
void newLevel(int score, int *level, double *level_time);

/**
 * @brief Вращение фигуры
 * @param rotFig Указатель на повернутую фигуру
 * @param block Указатель на исходную фигуру
 */
void rotFigure(Figure_t *rotFig, Figure_t *block);

/**
 * @brief Расчет игрового времени
 * @param end Время окончания
 * @param cpu_time_used Указатель на переменную времени
 * @param start Время начала
 */
void time_calcul(clock_t end, double *cpu_time_used, clock_t start);

#endif