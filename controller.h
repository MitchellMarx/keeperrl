#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "enums.h"
#include "util.h"

class Creature;
class Location;
class MapMemory;
class Item;
class Level;

class Controller {
  public:
  virtual void grantIdentify(int numItems) {};

  virtual bool isPlayer() const = 0;

  virtual void you(MsgType type, const string& param) const = 0;
  virtual void you(const string& param) const = 0;
  virtual void privateMessage(const string& message) const {}

  virtual void onKilled(const Creature* attacker) {}
  virtual void onItemsAppeared(vector<Item*> items, const Creature* from) { }
  virtual const MapMemory& getMemory() const = 0;

  virtual void learnLocation(const Location*) { }

  virtual void makeMove() = 0;
  virtual void sleeping() {}

  virtual int getDebt(const Creature* debtor) const { return 0; }

  virtual void onBump(Creature*) = 0;

  virtual ~Controller() {}

  protected:
  SERIALIZATION_DECL(Controller);
};

class DoNothingController : public Controller {
  public:
  DoNothingController(Creature* c) : creature(c) {}

  virtual bool isPlayer() const override;
  virtual void you(MsgType type, const string& param) const override;
  virtual void you(const string& param) const override;
  virtual const MapMemory& getMemory() const override;
  virtual void makeMove() override;
  virtual void onBump(Creature*) override;

  protected:
  SERIALIZATION_DECL(DoNothingController);

  private:
  Creature* creature;
};

class ControllerFactory {
  public:
  ControllerFactory(function<Controller* (Creature*)>);
  PController get(Creature*);

  private:
  function<Controller* (Creature*)> fun;
};

#endif
