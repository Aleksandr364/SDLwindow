#pragma once

#include "Global.h"

// Абстрактный базовый класс Shape.
class Shape
{
protected:

	// Поля класса.
	struct Fields
	{
		std::string name = ""; // Имя.
		unsigned int r = 0; // Размер.
	};

public:

	// Добавление виртуального деструктора в абстрактный базовый класс НЕОБХОДИМО для корректного удаления производных объектов через указатель на базовый класс.
	virtual ~Shape() = default;

	virtual void Set(std::string Name, unsigned int R) = 0;
	virtual void Get(newFields& fieldsStruct) = 0;
};

// Класс-наследник Sphere.
class Sphere : public Shape
{
private:

	// Экземпляр структуры Fields.
	Fields fields;

public:

	// Перегрузка операторов для класса Sphere.
	//******************************************
	Sphere& operator+(unsigned int R)
	{
		fields.r = fields.r + R;
		return *this;
	}
	Sphere& operator+=(unsigned int R)
	{
		fields.r += R;
		return *this;
	}
	bool operator==(const Sphere& R) const { return IntEquality(fields.r, R.fields.r); }
	bool operator!=(const Sphere& R) const { return !operator==(R); }

	// Установить значение полей.
	void Set(std::string Name, unsigned int R)
	{
		fields.name = Name;
		fields.r = R;
	}

	// Предоставить значение полей.
	void Get(newFields& fieldsStruct)
	{
		fieldsStruct.name = fields.name;
		fieldsStruct.r = fields.r;
	}
};