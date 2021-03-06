#include "stdafx.h"

#include "poison_gas.h"
#include "level.h"


template <class Archive> 
void PoisonGas::serialize(Archive& ar, const unsigned int version) {
  ar & SVAR(amount);
  CHECK_SERIAL;
}

SERIALIZABLE(PoisonGas);

void PoisonGas::addAmount(double a) {
  CHECK(a > 0);
  amount = min(3., a + amount);
}

const double decrease = 0.001;
const double spread = 0.10;

void PoisonGas::tick(Level* level, Vec2 pos) {
  if (amount < 0.1) {
    amount = 0;
    return;
  }
  for (Vec2 v : Vec2::directions8(true)) {
    Square* square = level->getSquare(pos + v);
    if (square->canSeeThru() && amount > 0 && square->getPoisonGasAmount() < amount) {
      double transfer = v.isCardinal4() ? spread : spread / 2;
      transfer = min(amount, transfer);
      transfer = min((amount - square->getPoisonGasAmount()) / 2, transfer);
      amount -= transfer;
      level->getSquare(v + pos)->addPoisonGas(transfer);
    }
  }
  amount = max(0.0, amount - decrease);
}

double PoisonGas::getAmount() const {
  return amount;
}

