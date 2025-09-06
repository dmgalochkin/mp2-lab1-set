// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

static const int BITS_IN_BYTE = 8;
static const int BITS_IN_BLOCK = BITS_IN_BYTE * sizeof(TELEM);

TBitField::TBitField(int len)
{
  if (len < 0)
  {
    throw "Negative length";
  }
  BitLen = len;
  MemLen = BitLen / BITS_IN_BLOCK + (BitLen % sizeof(TELEM) ? 1 : 0);
  if (MemLen != 0) {
    pMem = new TELEM[MemLen]{0};
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  if (MemLen != 0)
  {
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i)
    {
      pMem[i] = bf.pMem[i];
    }
  }
}

TBitField::~TBitField()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n >= BitLen)
  {
    throw "Out of range";
  }
  return n / BITS_IN_BLOCK;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n >= BitLen)
  {
    throw "Out of range";
  }
  return (1 << (n % BITS_IN_BLOCK));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen)
  {
    throw "Out of range";
  }
  int memIndex = GetMemIndex(n);
  int mask = GetMemMask(n);
  pMem[memIndex] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= BitLen)
  {
    throw "Out of range";
  }
  int memIndex = GetMemIndex(n);
  int mask = GetMemMask(n);
  pMem[memIndex] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= BitLen)
  {
    throw "Out of range";
  }
  int memIndex = GetMemIndex(n);
  return (pMem[memIndex] >> (n % BITS_IN_BLOCK)) & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
  {
    return *this;
  }
  if (pMem != nullptr)
  {
    delete[] pMem;
  }
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  if (MemLen != 0) {
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i)
    {
      pMem[i] = bf.pMem[i];
    }
  }
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen || MemLen != bf.MemLen) {
    return 0;
  }
  for (int i = 0; i < MemLen; ++i)
  {
    if (pMem[i] != bf.pMem[i])
    {
      return 0;
    }
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  if (BitLen != bf.BitLen || MemLen != bf.MemLen)
  {
    throw "Sizes doens't match";
  }
  TBitField newBitField(*this);
  for (int i = 0; i < MemLen; ++i)
  {
    newBitField.pMem[i] |= bf.pMem[i];
  }
  return newBitField;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  if (BitLen != bf.BitLen || MemLen != bf.MemLen)
  {
    throw "Sizes doens't match";
  }
  TBitField newBitField(*this);
  for (int i = 0; i < MemLen; ++i)
  {
    newBitField.pMem[i] &= bf.pMem[i];
  }
  return newBitField;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField newBitField(BitLen);
  for (int i = 0; i < MemLen; ++i)
  {
    newBitField.pMem[i] = ~pMem[i];
  }
  return newBitField;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; ++i)
  {
    ostr << bf.GetBit(i);
  }
  return ostr;
}
