#ifndef _CREATURE_FACTORY
#define _CREATURE_FACTORY

#include <map>
#include <string>
#include <functional>

#include "util.h"
#include "creature_attributes.h"
#include "tribe.h"
#include "view_object.h"
#include "item_factory.h"
#include "monster_ai.h"

class Creature;
class ItemFactory;


class CreatureFactory {
  public:
  static PCreature fromId(CreatureId, Tribe*, MonsterAIFactory = MonsterAIFactory::monster());
  static vector<PCreature> getFlock(int size, CreatureId, Creature* leader);
  static CreatureFactory humanVillage(double armedPercent);
  static CreatureFactory elvenVillage(double armedPercent);
  static CreatureFactory forrest();
  static CreatureFactory crypt();
  static CreatureFactory hellLevel();
  static CreatureFactory dwarfTown();
  static CreatureFactory dwarfTownPeaceful();
  static CreatureFactory vikingTown();
  static CreatureFactory vikingAttackers();
  static CreatureFactory castleAttackers();
  static CreatureFactory elfAttackers();
  static CreatureFactory lizardAttackers();
  static CreatureFactory goblinTown(int num);
  static CreatureFactory level(int num);
  static CreatureFactory splash();
  static CreatureFactory singleType(Tribe*, CreatureId);
  static CreatureFactory pyramid(int level);
  PCreature random(MonsterAIFactory = MonsterAIFactory::monster());

  static PCreature getShopkeeper(Location* shopArea, Tribe*);
  static PCreature getRollingBoulder(Vec2 direction);
  static PCreature getGuardingBoulder(Tribe* tribe);

  static PCreature addInventory(PCreature c, const vector<ItemId>& items);

  static void init();
 
  template <class Archive>
  static void registerTypes(Archive& ar);

  private:
  CreatureFactory(Tribe* tribe, const vector<CreatureId>& creatures, const vector<double>& weights,
      const vector<CreatureId>& unique);
  Tribe* tribe;
  vector<CreatureId> creatures;
  vector<double> weights;
  vector<CreatureId> unique;
};

#endif
