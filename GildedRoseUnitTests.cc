#include <gtest/gtest.h>

#include "GildedRose.h"

TEST(GildedRose, BrieQualityUpdate) {
    std::vector<Item> items;
    items.emplace_back(Item("Aged Brie", 30, 15));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 16);
}

TEST(GildedRose, BrieSellInUpdate) {
    std::vector<Item> items;
    items.emplace_back(Item("Aged Brie", 30, 15));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.sellIn, 29);
}

TEST(GildedRose, PassesSellInUpdateGTZero) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 22, 44));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.sellIn, 21);
}

TEST(GildedRose, PassesSellInUpdateEQZero) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 0, 44));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.sellIn, -1);
}

TEST(GildedRose, PassesSellInUpdateLTZero) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", -5, 44));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.sellIn, -6);
}

TEST(GildedRose, PassesQualityUpdateGTTenDays) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 22, 44));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 45);
}

TEST(GildedRose, PassesQualityUpdateLTTenDays) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 9, 44));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 46);
}

TEST(GildedRose, PassesQualityUpdateEQTenDays) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 10, 44));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 46);
}

TEST(GildedRose, PassesQualityUpdateEQFiveDays) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 5, 22));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 25);
}

TEST(GildedRose, PassesQualityUpdateLTFiveDays) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 2, 36));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 39);
}

TEST(GildedRose, PassesQualityUpdateZeroDays) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 0, 42));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    ASSERT_EQ(firstItem.sellIn, -1);
    EXPECT_EQ(firstItem.quality, 0);
}

TEST(GildedRose, PassesQualityUpdateGTTenDaysWith50Quality) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 22, 50));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 50);
}

TEST(GildedRose, PassesQualityUpdateLTTenDaysWith50Quality) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 9, 50));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 50);
}

TEST(GildedRose, PassesQualityUpdateLTFiveDaysWith50Quality) {
    std::vector<Item> items;
    items.emplace_back(Item("Backstage passes to a TAFKAL80ETC concert", 10, 50));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 50);
}

TEST(GildedRose, SulfurasSellInUpdate) {
    std::vector<Item> items;
    items.emplace_back(Item("Sulfuras, Hand of Ragnaros", 36, 80));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.sellIn, 35);
}

TEST(GildedRose, SulfurasNEVERHasToBeSold) {
    std::vector<Item> items;
    items.emplace_back(Item("Sulfuras, Hand of Ragnaros", -5, 80));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    ASSERT_EQ(firstItem.quality, 80);
    EXPECT_EQ(firstItem.sellIn, -6);
}

TEST(GildedRose, SulfurasNEVERDecreasesQuality) {
    std::vector<Item> items;
    items.emplace_back(Item("Sulfuras, Hand of Ragnaros", 36, 80));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 80);
}

TEST(GildedRose, ConjuredSellIn) {
    std::vector<Item> items;
    items.emplace_back(Item("Conjured", 42, 25));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.sellIn, 41);
}

TEST(GildedRose, ConjuredQualityDecreaseTwiceTheRate) {
    std::vector<Item> items;
    items.emplace_back(Item("Conjured", 12, 45));
    GildedRose gr(items);
    gr.updateQuality();

    Item firstItem = gr.items[0];
    EXPECT_EQ(firstItem.quality, 43);
}
