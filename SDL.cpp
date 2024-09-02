#include "SDL.h"

// Главное окно приложения со всеми входящими в него штуками.
// ***********************************************************
void Main_Window()
{
    // Создание объектов Shape и Sphere.
    //***********************************
    Sphere* newSphere = nullptr;
    newFields newSphereFields;
    std::vector<Shape*> vectShapes;
    unsigned int currentSphere = 0;
    // Инициализация необходимых SDL библиотек.
    //******************************************
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    // Переключатель, заставляющй объекты окна SDL реагировать по первому клику мыши.
    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
    // Переменные для контроля частоты кадров (60 fps).
    // Для снижение нагрузки на процессор и видеокарту.
    //**************************************************
    const int frameRate = 60;
    const int frameDelay = 1000 / frameRate;
    unsigned int frameStart = 0;
    unsigned int frameTime = 0;
    // Переменные для состояния курсора мыши.
    //****************************************
    int mouseX = 0;
    int mouseY = 0;
    int mouseButtonID = 0;
    // Флаги активации кнопок.
    //*************************
    bool sphereButtonActivated = false;
    bool createButtonActivated = false;
    bool nextButtonActivated = false;
    // Объявление переменных для отображения текста параметров "fields" в окне mainWindow.
    // ************************************************************************************
    // Переменные для текста "fieldsName".
    TTF_Font* fieldsNameFont = nullptr;
    SDL_Color fieldsNameColor = { 255, 255, 255, 255 };
    SDL_Surface* fieldsNameTemp = nullptr;
    SDL_Texture* fieldsNameTextImage = nullptr;
    SDL_Rect fieldsNamePos = {};
    // Переменные для текста "fieldsR".
    TTF_Font* fieldsRFont = nullptr;
    SDL_Color fieldsRColor = { 255, 255, 255, 255 };
    SDL_Surface* fieldsRTemp = nullptr;
    SDL_Texture* fieldsRTextImage = nullptr;
    SDL_Rect fieldsRPos = {};
    // Создание mainWindow.
    //**********************
    int width1 = 800;
    int height1 = 600;
    SDL_Window* mainWindow = SDL_CreateWindow("mainWindow",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width1, height1,
        SDL_WINDOW_SHOWN);
    // Создание mainWindowRenderer для mainWindow.
    SDL_Renderer* mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    // Загрузка изображения кнопки SphereButton(png).
    SDL_Surface* sphereButtonSurface = IMG_Load("C:/ImagesForCppProjects/SphereButton.png");
    // Текстура кнопки с изображением SphereButton.
    SDL_Texture* sphereButtonTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, sphereButtonSurface);
    // Освобождение памяти.
    SDL_FreeSurface(sphereButtonSurface);
    // Задания координат расположения кнопки и размеров (кнопка прямоугольная).
    SDL_Rect sphereButtonRect = { 20, 20, 50, 50 };
    // Загрузка изображения кнопки NextButton(png).
    SDL_Surface* nextButtonSurface = IMG_Load("C:/ImagesForCppProjects/NextButton.png");
    // Текстура кнопки с изображением NextButton.
    SDL_Texture* nextButtonTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, nextButtonSurface);
    // Освобождение памяти.
    SDL_FreeSurface(nextButtonSurface);
    // Задания координат расположения кнопки и размеров (кнопка прямоугольная).
    SDL_Rect nextButtonRect = { 100, 300, 100, 50 };
    // Объявление всех переменных для createSphereWindow.
    //****************************************************
    int width2 = 400;
    int height2 = 200;
    SDL_Window* createSphereWindow = nullptr;
    SDL_Renderer* createSphereRenderer = nullptr;
    SDL_Surface* createSphereButtonSurface = nullptr;
    SDL_Texture* createSphereButtonTexture = nullptr;
    // Задание координат расположения кнопки и размеров.
    SDL_Rect createSphereButtonRect = { width2 - 70, height2 - 70, 50, 50 }; // Центрировать по горизонтали и снизу.
    // Максимальное количество символов для ввода в поля окна.
    const size_t maxTextLength = 18;
    // Переключатель между полями ввода текста.
    bool switchTextFrame = false;
    // Объявление переменных для ввода текста в поле "name" окна createSphereWindow.
    // ******************************************************************************
    // Переменные для текста "Sphere Name".
    TTF_Font* sphereNameFont = nullptr;
    SDL_Color sphereNameColor = { 255, 255, 255, 255 };
    SDL_Surface* sphereNameTemp = nullptr;
    SDL_Texture* sphereNameTextImage = nullptr;
    SDL_Rect sphereNamePos = {};
    // Переменные для рамки "name".
    // Размеры рамки.
    const int sphereNameFrameWidth = 200;
    const int sphereNameFrameHeight = 30;
    const int sphereNameFrameMarginTop = 15;
    // Определение позиции и размера рамки.
    int sphereNameFrameX = ((width2 - sphereNameFrameWidth) / 2) + 70;
    int sphereNameFrameY = sphereNameFrameMarginTop;
    SDL_Rect sphereNameFrameRect = { sphereNameFrameX, sphereNameFrameY, sphereNameFrameWidth, sphereNameFrameHeight };
    // Переменные для ввода текста в поле рамки "name".
    std::string inputTextName = " ";
    // Рендеринг текста поля "name".
    SDL_Surface* textNameSurface = nullptr;
    SDL_Texture* textNameTexture = nullptr;
    // Определение позиции текста внутри рамки "name".
    SDL_Rect textNameRect = {};
    // Объявление переменных для ввода текста в поле "radius" окна createSphereWindow.
    // ********************************************************************************
    // Переменные для текста "Sphere Radius".
    TTF_Font* sphereRadiusFont = nullptr;
    SDL_Color sphereRadiusColor = { 255, 255, 255, 255 };
    SDL_Surface* sphereRadiusTemp = nullptr;
    SDL_Texture* sphereRadiusTextImage = nullptr;
    SDL_Rect sphereRadiusPos = {};
    // Переменные для рамки "radius".
    // Размеры рамки.
    const int sphereRadiusFrameWidth = 200;
    const int sphereRadiusFrameHeight = 30;
    const int sphereRadiusFrameMarginTop = 65;
    // Определение позиции и размера рамки.
    int sphereRadiusFrameX = ((width2 - sphereRadiusFrameWidth) / 2) + 70;
    int sphereRadiusFrameY = sphereRadiusFrameMarginTop;
    SDL_Rect sphereRadiusFrameRect = { sphereRadiusFrameX, sphereRadiusFrameY, sphereRadiusFrameWidth, sphereRadiusFrameHeight };
    // Переменные для ввода текста в поле рамки "radius".
    std::string inputTextRadius = " ";
    // Рендеринг текста поля "radius".
    SDL_Surface* textRadiusSurface = nullptr;
    SDL_Texture* textRadiusTexture = nullptr;
    // Определение позиции текста внутри рамки "radius".
    SDL_Rect textRadiusRect = {};
    // Главный цикл программы mainWindow.
    //************************************
    bool running = true; // Флаг для выхода из главного цикла.
    SDL_Event e; // Переменная для хранения событий SDL.
    // Цикл, который работает пока running == true.
    while (running)
    {
        // SDL_GetTicks: используется для получения времени в миллисекундах, прошедшего с момента запуска SDL.
        frameStart = SDL_GetTicks();
        // Проверяет наличие событий в очереди и обрабатывает их.
        while (SDL_PollEvent(&e))
        {
            // Событие SDL для окна mainWindow.
            // ID текущего окна, в котором происходит событие: e.window.windowID.
            //********************************************************************
            if (SDL_GetWindowID(mainWindow) == e.window.windowID)
            {
                // Событие SDL для mainWindow: НАЖАТИЕ МЫШИ.
                //*******************************************
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    // Получаем координаты курсора мыши и индекс нажатой кнопки.
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                    mouseButtonID = e.button.button;
                    // Если нажатие мыши по кнопке sphereButton, активировать эту кнопку.
                    //********************************************************************
                    if (mouseButtonID == 1 &&
                        createSphereWindow == nullptr &&
                        createSphereRenderer == nullptr &&
                        mouseX >= sphereButtonRect.x &&
                        mouseX <= sphereButtonRect.x + sphereButtonRect.w &&
                        mouseY >= sphereButtonRect.y &&
                        mouseY <= sphereButtonRect.y + sphereButtonRect.h) { sphereButtonActivated = true; }
                    // Если нажатие мыши по кнопке nextButton, активировать эту кнопку.
                    //******************************************************************
                    if (mouseButtonID == 1 &&
                        mouseX >= nextButtonRect.x &&
                        mouseX <= nextButtonRect.x + nextButtonRect.w &&
                        mouseY >= nextButtonRect.y &&
                        mouseY <= nextButtonRect.y + nextButtonRect.h) { nextButtonActivated = true; }
                }
                // Событие SDL для mainWindow: ОТЖАТИЕ МЫШИ.
                //*******************************************
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    // Получаем координаты курсора мыши и индекс отжатой кнопки.
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                    mouseButtonID = e.button.button;
                    // При отжатии кнопки sphereButton создать createSphereWindow.
                    //*************************************************************
                    if (sphereButtonActivated == true &&
                        mouseButtonID == 1 &&
                        createSphereWindow == nullptr &&
                        createSphereRenderer == nullptr &&
                        mouseX >= sphereButtonRect.x &&
                        mouseX <= sphereButtonRect.x + sphereButtonRect.w &&
                        mouseY >= sphereButtonRect.y &&
                        mouseY <= sphereButtonRect.y + sphereButtonRect.h)
                    {
                        // Создание createSphereWindow.
                        //*******************************
                        createSphereWindow = SDL_CreateWindow("createSphereWindow",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width2, height2,
                            SDL_WINDOW_SHOWN);
                        // Создание createSphereRenderer для createSphereWindow.
                        createSphereRenderer = SDL_CreateRenderer(createSphereWindow, -1, SDL_RENDERER_ACCELERATED);
                        // Загрузка изображения кнопки для окна createSphereWindow.
                        createSphereButtonSurface = IMG_Load("C:/ImagesForCppProjects/CreateButton.png");
                        // Создание текстуры кнопки с изображением CreateButton(png).
                        createSphereButtonTexture = SDL_CreateTextureFromSurface(createSphereRenderer, createSphereButtonSurface);
                        // Освобождение памяти.
                        SDL_FreeSurface(createSphereButtonSurface);
                        // Создание надписи "Sphere Name".
                        sphereNameFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                        sphereNameTemp = TTF_RenderText_Solid(sphereNameFont, "Sphere Name", sphereNameColor);
                        sphereNameTextImage = SDL_CreateTextureFromSurface(createSphereRenderer, sphereNameTemp);
                        sphereNamePos = { 20, 20, sphereNameTemp->w, sphereNameTemp->h };
                        SDL_FreeSurface(sphereNameTemp);
                        // Создание надписи "Sphere Radius".
                        sphereRadiusFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                        sphereRadiusTemp = TTF_RenderText_Solid(sphereRadiusFont, "Sphere Radius", sphereRadiusColor);
                        sphereRadiusTextImage = SDL_CreateTextureFromSurface(createSphereRenderer, sphereRadiusTemp);
                        sphereRadiusPos = { 20, 70, sphereRadiusTemp->w, sphereRadiusTemp->h };
                        SDL_FreeSurface(sphereRadiusTemp);
                    }
                    // При отжатии кнопки nextButton показать параметры следующего элемента вектора Shape.
                    //*************************************************************************************
                    if (vectShapes.size() > 0 &&
                        nextButtonActivated == true &&
                        mouseButtonID == 1 &&
                        mouseX >= nextButtonRect.x &&
                        mouseX <= nextButtonRect.x + nextButtonRect.w &&
                        mouseY >= nextButtonRect.y &&
                        mouseY <= nextButtonRect.y + nextButtonRect.h)
                    {
                        if (currentSphere < (vectShapes.size() - 1)) currentSphere += 1;
                        else currentSphere = 0;
                        // Отображение "fields" объекта вектора Shapes (индекс currentSphere).
                        //*****************************************************************
                        vectShapes[currentSphere]->Get(newSphereFields);
                        fieldsNameFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                        fieldsNameTemp = TTF_RenderText_Solid(fieldsNameFont, newSphereFields.name.c_str(), fieldsNameColor);
                        fieldsNameTextImage = SDL_CreateTextureFromSurface(mainWindowRenderer, fieldsNameTemp);
                        fieldsNamePos = { 200, 50, fieldsNameTemp->w, fieldsNameTemp->h };
                        SDL_FreeSurface(fieldsNameTemp);
                        fieldsRFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                        fieldsRTemp = TTF_RenderText_Solid(fieldsRFont, std::to_string(newSphereFields.r).c_str(), fieldsRColor);
                        fieldsRTextImage = SDL_CreateTextureFromSurface(mainWindowRenderer, fieldsRTemp);
                        fieldsRPos = { 200, 100, fieldsRTemp->w, fieldsRTemp->h };
                        SDL_FreeSurface(fieldsRTemp);
                    }
                    // Возвращаем флаг активации кнопки sphereButton в изначальное состояние.
                    sphereButtonActivated = false;
                    // Возвращаем флаг активации кнопки sphereButton в изначальное состояние.
                    nextButtonActivated = false;
                }
                // Событие SDL для mainWindow: ЗАКРЫТЬ ОКНО.
                //*******************************************
                if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) { running = false; }
                // Событие SDL для mainWindow: НАЖАТИЕ КЛАВИШИ.
                //**********************************************
                if (e.type == SDL_KEYDOWN)
                {
                    // Если нажата клавиша "Esc", завершить цикл mainWindow (закрыть приложение).
                    if (e.key.keysym.sym == SDLK_ESCAPE) { running = false; }
                }
            }
            // Событие SDL для createSphereWindow.
            // ID текущего окна, в котором происходит событие: e.window.windowID.
            //********************************************************************
            if (SDL_GetWindowID(createSphereWindow) == e.window.windowID)
            {
                // Событие SDL для createSphereWindow: НАЖАТИЕ МЫШИ.
                //***************************************************
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    // Получаем координаты курсора мыши и индекс нажатой кнопки.
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                    mouseButtonID = e.button.button;
                    // Если нажатие мыши по кнопке createButton, активировать эту кнопку.
                    if (mouseButtonID == 1 &&
                        mouseX >= createSphereButtonRect.x &&
                        mouseX <= createSphereButtonRect.x + createSphereButtonRect.w &&
                        mouseY >= createSphereButtonRect.y &&
                        mouseY <= createSphereButtonRect.y + createSphereButtonRect.h)
                    { createButtonActivated = true; }
                }
                // Событие SDL для createSphereWindow: ОТЖАТИЕ МЫШИ.
                //***************************************************
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    // Получаем координаты курсора мыши и индекс отжатой кнопки.
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                    mouseButtonID = e.button.button;
                    // При отжатии кнопки sphereButtonRect закрыть createSphereWindow.
                    if (createButtonActivated == true &&
                        mouseButtonID == 1 &&
                        mouseX >= createSphereButtonRect.x &&
                        mouseX <= createSphereButtonRect.x + createSphereButtonRect.w &&
                        mouseY >= createSphereButtonRect.y &&
                        mouseY <= createSphereButtonRect.y + createSphereButtonRect.h)
                    {
                        // Перед закрытием окна сохраняем данные полей Sphere и добавляем новый объект в вектор Shapes.
                        if ((from_str_to_uint(inputTextRadius) > 0) && (inputTextName.size() > 0)) // Убедимся, что name и r введены корректно.
                        {
                            newSphere = new Sphere();
                            newSphere->Set(inputTextName, from_str_to_uint(inputTextRadius));
                            vectShapes.push_back(newSphere);
                            // Отображение "fields" первого объекта вектора Shapes (индекс 0).
                            //*****************************************************************
                            vectShapes[0]->Get(newSphereFields);
                            fieldsNameFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                            fieldsNameTemp = TTF_RenderText_Solid(fieldsNameFont, newSphereFields.name.c_str(), fieldsNameColor);
                            fieldsNameTextImage = SDL_CreateTextureFromSurface(mainWindowRenderer, fieldsNameTemp);
                            fieldsNamePos = { 200, 50, fieldsNameTemp->w, fieldsNameTemp->h };
                            SDL_FreeSurface(fieldsNameTemp);
                            fieldsRFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                            fieldsRTemp = TTF_RenderText_Solid(fieldsRFont, std::to_string(newSphereFields.r).c_str(), fieldsRColor);
                            fieldsRTextImage = SDL_CreateTextureFromSurface(mainWindowRenderer, fieldsRTemp);
                            fieldsRPos = { 200, 100, fieldsRTemp->w, fieldsRTemp->h };
                            SDL_FreeSurface(fieldsRTemp);
                        }
                        // Закрытие окна createSphereWindow с обнулением переменных.
                        SDL_DestroyWindow(createSphereWindow);
                        SDL_DestroyRenderer(createSphereRenderer);
                        SDL_DestroyTexture(createSphereButtonTexture);
                        createSphereWindow = nullptr;
                        createSphereRenderer = nullptr;
                        createSphereButtonTexture = nullptr;
                        sphereNameFont = nullptr;
                        sphereNameTemp = nullptr;
                        sphereNameTextImage = nullptr;
                        sphereNamePos = {};
                        textNameSurface = nullptr;
                        textNameTexture = nullptr;
                        textNameRect = {};
                        inputTextName = " ";
                        sphereRadiusFont = nullptr;
                        sphereRadiusTemp = nullptr;
                        sphereRadiusTextImage = nullptr;
                        sphereRadiusPos = {};
                        textRadiusSurface = nullptr;
                        textRadiusTexture = nullptr;
                        textRadiusRect = {};
                        inputTextRadius = " ";
                        switchTextFrame = false;
                        currentSphere = 0;
                    }
                    // Возвращаем флаг активации кнопки createButton в изначальное состояние.
                    createButtonActivated = false;
                }
                // Событие SDL для createSphereWindow: ЗАКРЫТЬ ОКНО.
                //***************************************************
                if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    SDL_DestroyWindow(createSphereWindow);
                    SDL_DestroyRenderer(createSphereRenderer);
                    SDL_DestroyTexture(createSphereButtonTexture);
                    createSphereWindow = nullptr;
                    createSphereRenderer = nullptr;
                    createSphereButtonTexture = nullptr;
                    sphereNameFont = nullptr;
                    sphereNameTemp = nullptr;
                    sphereNameTextImage = nullptr;
                    sphereNamePos = {};
                    textNameSurface = nullptr;
                    textNameTexture = nullptr;
                    textNameRect = {};
                    inputTextName = " ";
                    sphereRadiusFont = nullptr;
                    sphereRadiusTemp = nullptr;
                    sphereRadiusTextImage = nullptr;
                    sphereRadiusPos = {};
                    textRadiusSurface = nullptr;
                    textRadiusTexture = nullptr;
                    textRadiusRect = {};
                    inputTextRadius = " ";
                    switchTextFrame = false;
                }
                // Событие SDL для createSphereWindow: НАЖАТИЕ КЛАВИШИ.
                //******************************************************
                if (e.type == SDL_KEYDOWN)
                {  
                    // Если нажат "Enter".
                    //*********************
                    if (e.key.keysym.sym == SDLK_RETURN)
                    {
                        if (!switchTextFrame) { switchTextFrame = true; }
                        else
                        {
                            // Перед закрытием окна сохраняем данные полей Sphere и добавляем новый объект в вектор Shapes.
                            if ((from_str_to_uint(inputTextRadius) > 0) && (inputTextName.size() > 0)) // Убедимся, что name и r введены корректно.
                            {
                                newSphere = new Sphere();
                                newSphere->Set(inputTextName, from_str_to_uint(inputTextRadius));
                                vectShapes.push_back(newSphere);
                                // Отображение "fields" первого объекта вектора Shapes (индекс 0).
                                //*****************************************************************
                                vectShapes[0]->Get(newSphereFields);
                                fieldsNameFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                                fieldsNameTemp = TTF_RenderText_Solid(fieldsNameFont, newSphereFields.name.c_str(), fieldsNameColor);
                                fieldsNameTextImage = SDL_CreateTextureFromSurface(mainWindowRenderer, fieldsNameTemp);
                                fieldsNamePos = { 200, 50, fieldsNameTemp->w, fieldsNameTemp->h };
                                SDL_FreeSurface(fieldsNameTemp);
                                fieldsRFont = TTF_OpenFont("C:/ImagesForCppProjects/arialunicodems.ttf", 20);
                                fieldsRTemp = TTF_RenderText_Solid(fieldsRFont, std::to_string(newSphereFields.r).c_str(), fieldsRColor);
                                fieldsRTextImage = SDL_CreateTextureFromSurface(mainWindowRenderer, fieldsRTemp);
                                fieldsRPos = { 200, 100, fieldsRTemp->w, fieldsRTemp->h };
                                SDL_FreeSurface(fieldsRTemp);
                            }
                            // Закрыть окно и обнулить переменные.
                            SDL_DestroyWindow(createSphereWindow);
                            SDL_DestroyRenderer(createSphereRenderer);
                            SDL_DestroyTexture(createSphereButtonTexture);
                            createSphereWindow = nullptr;
                            createSphereRenderer = nullptr;
                            createSphereButtonTexture = nullptr;
                            sphereNameFont = nullptr;
                            sphereNameTemp = nullptr;
                            sphereNameTextImage = nullptr;
                            sphereNamePos = {};
                            textNameSurface = nullptr;
                            textNameTexture = nullptr;
                            textNameRect = {};
                            inputTextName = " ";
                            sphereRadiusFont = nullptr;
                            sphereRadiusTemp = nullptr;
                            sphereRadiusTextImage = nullptr;
                            sphereRadiusPos = {};
                            textRadiusSurface = nullptr;
                            textRadiusTexture = nullptr;
                            textRadiusRect = {};
                            inputTextRadius = " ";
                            switchTextFrame = false;
                            currentSphere = 0;
                        }
                    }
                    // Если нажата клавиша "Esc", закрытие окна createSphereWindow с обнулением переменных.
                    //**************************************************************************************
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        SDL_DestroyWindow(createSphereWindow);
                        SDL_DestroyRenderer(createSphereRenderer);
                        SDL_DestroyTexture(createSphereButtonTexture);
                        createSphereWindow = nullptr;
                        createSphereRenderer = nullptr;
                        createSphereButtonTexture = nullptr;
                        sphereNameFont = nullptr;
                        sphereNameTemp = nullptr;
                        sphereNameTextImage = nullptr;
                        sphereNamePos = {};
                        textNameSurface = nullptr;
                        textNameTexture = nullptr;
                        textNameRect = {};
                        inputTextName = " ";
                        sphereRadiusFont = nullptr;
                        sphereRadiusTemp = nullptr;
                        sphereRadiusTextImage = nullptr;
                        sphereRadiusPos = {};
                        textRadiusSurface = nullptr;
                        textRadiusTexture = nullptr;
                        textRadiusRect = {};
                        inputTextRadius = " ";
                        switchTextFrame = false;
                    }
                    // Если нажат "BackSpace".
                    //*************************
                    if (e.key.keysym.sym == SDLK_BACKSPACE && !switchTextFrame && (inputTextName.size() > 1)) { inputTextName.pop_back(); }
                    if (e.key.keysym.sym == SDLK_BACKSPACE && switchTextFrame && (inputTextRadius.size() > 1)) { inputTextRadius.pop_back(); }
                    else if (e.key.keysym.sym == SDLK_BACKSPACE && switchTextFrame && (inputTextRadius.size() == 1)) { switchTextFrame = false; }
                }
                // Событие SDL для createSphereWindow: ВВОД ТЕКСТА.
                //**************************************************
                if (e.type == SDL_TEXTINPUT)
                {
                    // Проверка длины текста перед добавлением нового символа в поле "name".
                    if (!switchTextFrame && inputTextName.length() < maxTextLength) { inputTextName += e.text.text; }
                    // Проверка длины текста перед добавлением нового символа в поле "radius".
                    if (switchTextFrame && inputTextRadius.length() < maxTextLength) { inputTextRadius += e.text.text; }
                }
            }
        }
        // Обновление отображения окон.
        //******************************
        // Задание цвета окна.
        SDL_SetRenderDrawColor(mainWindowRenderer, 0x00, 0x00, 0x00, 0xFF);
        // Очищает текущий рендерер.
        SDL_RenderClear(mainWindowRenderer);
        // Отрисовка текстуры кнопки с учетом прозрачности.
        SDL_RenderCopy(mainWindowRenderer, sphereButtonTexture, nullptr, &sphereButtonRect);
        SDL_RenderCopy(mainWindowRenderer, nextButtonTexture, nullptr, &nextButtonRect);
        SDL_RenderCopy(mainWindowRenderer, fieldsNameTextImage, NULL, &fieldsNamePos);
        SDL_RenderCopy(mainWindowRenderer, fieldsRTextImage, NULL, &fieldsRPos);
        if (createSphereRenderer)
        {
            SDL_SetRenderDrawColor(createSphereRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(createSphereRenderer);
            SDL_RenderCopy(createSphereRenderer, createSphereButtonTexture, nullptr, &createSphereButtonRect);
            SDL_RenderCopy(createSphereRenderer, sphereNameTextImage, NULL, &sphereNamePos);
            SDL_RenderCopy(createSphereRenderer, sphereRadiusTextImage, NULL, &sphereRadiusPos);
            SDL_SetRenderDrawColor(createSphereRenderer, 255, 255, 255, 255); // Установка белого цвета для рамки.
            SDL_RenderDrawRect(createSphereRenderer, &sphereNameFrameRect); // Рисование рамки "name".
            SDL_RenderDrawRect(createSphereRenderer, &sphereRadiusFrameRect); // Рисование рамки "radius".
            // Отображение напечатанного текста в поле "name".
            textNameSurface = TTF_RenderText_Solid(sphereNameFont, inputTextName.c_str(), sphereNameColor);
            textNameTexture = SDL_CreateTextureFromSurface(createSphereRenderer, textNameSurface);
            textNameRect = { sphereNameFrameX, sphereNameFrameY, textNameSurface->w, textNameSurface->h }; // С небольшим отступом.
            SDL_RenderCopy(createSphereRenderer, textNameTexture, nullptr, &textNameRect); // Отображение текста.
            SDL_FreeSurface(textNameSurface);
            SDL_DestroyTexture(textNameTexture);
            // Отображение напечатанного текста в поле "radius".
            textRadiusSurface = TTF_RenderText_Solid(sphereRadiusFont, inputTextRadius.c_str(), sphereRadiusColor);
            textRadiusTexture = SDL_CreateTextureFromSurface(createSphereRenderer, textRadiusSurface);
            textRadiusRect = { sphereRadiusFrameX, sphereRadiusFrameY, textRadiusSurface->w, textRadiusSurface->h }; // С небольшим отступом.
            SDL_RenderCopy(createSphereRenderer, textRadiusTexture, nullptr, &textRadiusRect); // Отображение текста.
            SDL_FreeSurface(textRadiusSurface);
            SDL_DestroyTexture(textRadiusTexture);
            SDL_RenderPresent(createSphereRenderer);
        }
        // Обновляет экран, отображая рендерер.
        SDL_RenderPresent(mainWindowRenderer);
        // Управление частотой кадров.
        //*****************************
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
    }
    // Очистка ресурсов перед завершением работы программы.
    //*******************************************************
    // Уничтожает окно.
    SDL_DestroyWindow(mainWindow);
    // Уничтожает рендерер.
    SDL_DestroyRenderer(mainWindowRenderer);
    // Уничтожает текстуру кнопки.
    SDL_DestroyTexture(sphereButtonTexture);
    SDL_DestroyTexture(nextButtonTexture);
    SDL_DestroyTexture(fieldsNameTextImage);
    SDL_DestroyTexture(fieldsRTextImage);
    if (createSphereButtonTexture)
    {
        SDL_DestroyWindow(createSphereWindow);
        SDL_DestroyRenderer(createSphereRenderer);
        SDL_DestroyTexture(createSphereButtonTexture);
        SDL_DestroyTexture(sphereNameTextImage);
        SDL_DestroyTexture(sphereRadiusTextImage);
    }
    // Завершает работу SDL.
    //***********************
    TTF_Quit(); // Завершаем работу SDL_ttf.
    IMG_Quit(); // Завершаем работу SDL_image.
    SDL_Quit(); // Завершаем работу SDL.
}