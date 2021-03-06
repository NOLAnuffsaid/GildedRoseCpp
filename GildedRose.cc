#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include "GildedRose.h"

/*
 * Strings we care about:
 *
 * "Aged Brie"
 * "Backstage passes to a TAFKAL80ETC concert"
 * "Sulfuras, Hand of Ragnaros"
 * "Conjured"
 *
 *
 * Items:
 *
 * - Sellin: # of days we have to sell the item
 * - Quality: value of the item
 * -- never negative
 * -- never more than 50
 *
 * - "Aged Brie" INCREASES in Quality as it gets older
 * - "Sulfuras" never DECREASES in Quality
 * - "Backstage passes" INCREASES in Quality as it gets older
 * -- INCREASES by 2 when 10>= days
 * -- INCREASES by 3 when 5>= days
 * -- EQUALS 0 after concert
 * - "Conjured" DECREASES in Quality 2x as fast as normal items
 *
 */

enum SpecialItemType {
    Brie = 0,
    Passes = 1,
    Sulfuras = 2,
    Conjured = 3
};

std::map<std::string, SpecialItemType> itemDict = {
{"Aged Brie", SpecialItemType::Brie},
{"Backstage passes to a TAFKAL80ETC concert", SpecialItemType::Passes},
{"Sulfuras, Hand of Ragnaros", SpecialItemType::Sulfuras},
{"Conjured", SpecialItemType::Conjured}
};

void updateBrieQuality(Item& item) {
    item.quality = item.quality == 50 ? item.quality : item.quality + 1;
}

int determinePassDecreaseRate( int a ) {
    if ( a > 10 ) { return 1; }
    else if (( a <= 10 ) && ( a > 5 )) { return 2; }
    else if ( (a <= 5) && (a > 0) ) { return 3; }
    else { return 0; }
}

int getUpdatedQuality(const Item item) {
    int increaseBy = determinePassDecreaseRate(item.sellIn);
    int updatedQuality = item.quality + increaseBy;

    return updatedQuality > 50 ? 50 : updatedQuality;
}

void updatePassesQuality(Item& item) {
    item.quality = item.sellIn <= 0 ? 0 : getUpdatedQuality(item);
}

void updateConjuredQuality(Item& item) {
    item.quality = item.quality == 0 ? item.quality : item.quality - 2;
}

void updateItemQuality(Item& item) {
    switch(itemDict[item.name]) {
        case SpecialItemType::Brie:
            updateBrieQuality(item);
            return;
        case SpecialItemType::Passes:
            updatePassesQuality(item);
            return;
        case SpecialItemType::Conjured:
            updateConjuredQuality(item);
            return;
        case SpecialItemType::Sulfuras:
            return;
        default:
            item.quality -= 1;
            return;
    }
}

void updateItem(Item& item) {
    updateItemQuality(item);
    item.sellIn--;
}

void GildedRose::updateQuality() {
    std::for_each(items.begin(), items.end(), updateItem);
}
