#pragma once
#include <cstdint>
#include <Windows.h>
class vmt {
public:
    vmt() {
        this->original_vft = nullptr;
        this->base = nullptr;
        this->shadow_vft = nullptr;
        this->methods = 0;
        this->protect = 0;
    }
private:
    void change_protect(DWORD protect) {
        VirtualProtect(base, sizeof(uintptr_t) * methods, protect, &this->protect);
    }
public:
    void init(void* _base)//адрес класса
    {
        if (!_base)abort();//проверка на nullptr
        this->base = (uintptr_t**)(_base);//присваиваем к значению поля base аргумент _base
        this->original_vft = *(uintptr_t**)(this->base);
        while (reinterpret_cast<uintptr_t*>(this->original_vft)[methods])//подсчет кол-ва методов в виртуальной таблице
        {
            methods++;
        }
        this->shadow_vft = new uintptr_t[methods];
        memcpy(this->shadow_vft, this->original_vft, methods * sizeof(uintptr_t));//дамп из оригинальной таблицы в нашу теневую
    }
    template<typename T>
    void hookAt(int index, T hkFunction)
    {
        if (!this->shadow_vft || methods < index)return;
        this->shadow_vft[index] = uintptr_t(hkFunction);
    }
    template<typename T>
    T getOriginalFunction(int index)
    {
        return (T)(this->original_vft[index]);
    }
    void join() {
        if (!this->base || !this->shadow_vft || !this->original_vft)return;
        change_protect(PAGE_EXECUTE_READWRITE);
        *this->base = this->shadow_vft;
        change_protect(this->protect);
    }
    void split()
    {
        if (!this->base || !this->shadow_vft || !this->original_vft)return;
        change_protect(PAGE_EXECUTE_READWRITE);
        *this->base = this->original_vft;
        change_protect(this->protect);
    }
private:
    uintptr_t* original_vft;//ориг.таблица
    uintptr_t** base;//указатель на класс
    uintptr_t* shadow_vft;//теневая(рабочая)таблица
    int methods;//кол-во методов в ориг.таблице
    DWORD protect;
};
