// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : bitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
}

TSet::operator TBitField()
{
    return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return bitField.GetLength();
}

bool TSet::IsMember(const int elem) const // элемент множества?
{
    return bitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
    bitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
    bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    bitField = s.bitField;
    return FAKE_SET;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    return bitField == s.bitField;
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    return bitField != s.bitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet(bitField | s.bitField);
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
    TSet newSet(*this);
    newSet.InsElem(elem);
    return newSet;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
TSet newSet(*this);
    newSet.DelElem(elem);
    return newSet;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return TSet(bitField & s.bitField);
}

TSet TSet::operator~(void) // дополнение
{
    return TSet(~bitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    return ostr;
}
