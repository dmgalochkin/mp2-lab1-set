// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField()
{
  bitLen = 0;
  memLen = 0;
  pMem = nullptr;
}

TBitField::TBitField(int len)
{
  if (len < 0)
  {
    throw "Negative length";
  }
  bitLen = len;
  memLen = bitLen / BITS_IN_BLOCK + (bitLen % BITS_IN_BLOCK != 0 ? 1 : 0);
  if (memLen != 0)
  {
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; ++i)
    {
      pMem[i] = 0;
    }
  }
  else
  {
    pMem = nullptr;
  }
}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  if (memLen != 0)
  {
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; ++i)
    {
      pMem[i] = bf.pMem[i];
    }
  }
  else
  {
    pMem = nullptr;
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
  if (n < 0 || n >= bitLen)
  {
    throw "Out of range";
  }
  return n / BITS_IN_BLOCK;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n >= bitLen)
  {
    throw "Out of range";
  }
  return (1 << (n % BITS_IN_BLOCK));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= bitLen)
  {
    throw "Out of range";
  }
  int memIndex = GetMemIndex(n);
  int mask = GetMemMask(n);
  pMem[memIndex] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= bitLen)
  {
    throw "Out of range";
  }
  int memIndex = GetMemIndex(n);
  int mask = GetMemMask(n);
  pMem[memIndex] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= bitLen)
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
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  if (memLen != 0)
  {
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; ++i)
    {
      pMem[i] = bf.pMem[i];
    }
  }
  else
  {
    pMem = nullptr;
  }
  return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bitLen != bf.bitLen || memLen != bf.memLen)
  {
    return false;
  }
  for (int i = 0; i < memLen; ++i)
  {
    if (pMem[i] != bf.pMem[i])
    {
      return false;
    }
  }
  return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int maxBitLen = std::max(bitLen, bf.bitLen);
  TBitField newBitField(maxBitLen);
  for (int i = 0; i < memLen; ++i)
  {
    newBitField.pMem[i] |= pMem[i];
  }
  for (int i = 0; i < bf.memLen; ++i)
  {
    newBitField.pMem[i] |= bf.pMem[i];
  }
  return newBitField;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int maxBitLen = std::max(bitLen, bf.bitLen);
  int minMemLen = std::min(memLen, bf.memLen);

  TBitField newBitField(maxBitLen);
  for (int i = 0; i < minMemLen; ++i)
  {
    newBitField.pMem[i] = pMem[i] & bf.pMem[i];
  }
  return newBitField;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField newBitField(bitLen);
  for (int i = 0; i < memLen; ++i)
  {
    newBitField.pMem[i] = ~pMem[i];
    if (i == memLen - 1 && bitLen % BITS_IN_BLOCK != 0)
    {
      newBitField.pMem[i] &= ((1 << (bitLen % BITS_IN_BLOCK)) - 1);
    }
  }
  return newBitField;
}

// ввод/вывод

istream& operator>>(istream &istr, TBitField &bf) // ввод
{
  string bitString;
  istr >> bitString;
  
  for (char c : bitString)
  {
    if (c != '0' && c != '1')
    {
      throw "Invalid bit string - only 0 and 1 allowed";
    }
  }
  
  TBitField temp(bitString.size());
  
  for (int i = 0; i < bitString.size(); ++i)
  {
    if (bitString[i] == '1')
    {
      temp.SetBit(i);
    }
  }
  
  bf = temp;
  return istr;
}

ostream& operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; ++i)
  {
    ostr << bf.GetBit(i);
  }
  return ostr;
}
