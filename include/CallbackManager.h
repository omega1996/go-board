#pragma once
#include <functional> // Для std::function

class CallbackManager
{
public:
    CallbackManager();
    bool next();
    bool prev();
    bool select();

    void setNextCallback(std::function<void()> callback);   // Принимает указатель на функцию типа CallbackFunction
    void setPrevCallback(std::function<void()> callback);   // Принимает указатель на функцию типа CallbackFunction
    void setSelectCallback(std::function<void()> callback); // Принимает указатель на функцию типа CallbackFunction

private:
    std::function<void()> nextCallback;
    std::function<void()> prevCallback;
    std::function<void()> selectCallback;
};
