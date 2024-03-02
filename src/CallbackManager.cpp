#include "CallbackManager.h"

// Реализация методов класса CallbackManager
CallbackManager::CallbackManager()
{
    // Инициализация указателей на колбэки как nullptr
    nextCallback = nullptr;
    prevCallback = nullptr;
    selectCallback = nullptr;
}

void CallbackManager::setNextCallback(std::function<void()> callback)
{
    nextCallback = callback;
}

void CallbackManager::setPrevCallback(std::function<void()> callback)
{
    prevCallback = callback;
}

void CallbackManager::setSelectCallback(std::function<void()> callback)
{
    selectCallback = callback;
}

bool CallbackManager::next()
{
    // Проверяем, установлен ли указатель на колбэк next
    if (nextCallback)
    {
        // Вызываем колбэк next
        nextCallback();
        return true;
    }
    else
    {
        // Если колбэк не установлен, выполняем какую-то другую логику по умолчанию
        return false;
    }
}

bool CallbackManager::prev()
{
    // Проверяем, установлен ли указатель на колбэк prev
    if (prevCallback != nullptr)
    {
        // Вызываем колбэк prev
        prevCallback();
        return true;
    }
    else
    {
        // Если колбэк не установлен, выполняем какую-то другую логику по умолчанию
        return false;
    }
}

bool CallbackManager::select()
{
    // Проверяем, установлен ли указатель на колбэк select
    if (selectCallback != nullptr)
    {
        // Вызываем колбэк select
        selectCallback();
        return true;
    }
    else
    {
        // Если колбэк не установлен, выполняем какую-то другую логику по умолчанию
        return false;
    }
}
