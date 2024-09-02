#pragma once

#include <SDL.h> // Подключаем библиотеку SDL.
#include <SDL_ttf.h> // Подключаем библиотеку SDL_ttf для работы с текстом.
#include <SDL_image.h> // Подключаем библиотеку SDL_image для работы с изображением.
#include "Shapes.h"

#define SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH "SDL_MOUSE_FOCUS_CLICKTHROUGH" // Активируем "переключатель", заставляющй объекты окна SDL реагировать по первому клику мыши.

void Main_Window();