#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <oset.h>
#include <vector>
#include <set>
#include <random>
#include "gravedata.h"

using gint = nmg::GraveData;
using gset = nmg::OSet<gint>;


static std::default_random_engine randomVar;

static std::vector<int> generate_testdata(int count)
{
    std::uniform_int_distribution<int> dist(0, count * 1000);
    std::set<int> numbers;

    for(int i = 0; i < count; ++i)
    {
        int n;
        do
        {
            n = dist(randomVar);
        }
        while(numbers.contains(n));
        numbers.insert(n);        
    }

    return std::vector<int>(numbers.begin(), numbers.end());
}

TEST_CASE("created oset contains no data")
{
    gint::init();

    gset oset;
    REQUIRE(oset.empty());
    REQUIRE(oset.size() == 0);
    REQUIRE_EQ(0, gint::count());
}

TEST_CASE("adding items to oset increases size")
{
    gint::init();
    auto data = generate_testdata(5);
    gset oset;

    int size = 0;
    for(auto a : data)
    {
        auto result = oset.add(a);
        REQUIRE(result);
        REQUIRE(oset.size() == ++size);
        REQUIRE_EQ(size, gint::count());
    }
    REQUIRE(oset.size() == data.size());
    REQUIRE_EQ(gint::count(), data.size());
}

TEST_CASE("oset does not add duplicates")
{
    gint::init();

    auto data = generate_testdata(11);
    std::vector<int> copy(data);
    gset oset;

    for(auto a : data)
    {
        auto result = oset.add(a);
        REQUIRE(result);
    }
    REQUIRE(oset.size() == data.size());

    for(auto a : copy)
    {
        auto result = oset.add(a);
        REQUIRE(!result);
        REQUIRE(oset.size() == data.size());
        REQUIRE_EQ(gint::count(), data.size());
    }
}

TEST_CASE("oset is iterable")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    bool iterated = false;
    for(auto a : oset)
    {
        iterated = true;
    }
    REQUIRE(iterated);
    REQUIRE_EQ(gint::count(), data.size());
}

TEST_CASE("oset iterates in order")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    auto osit = oset.begin();
    auto vecit = data.begin();
    while(vecit != data.end())
    {
        REQUIRE_EQ(*osit, *vecit);
        ++vecit;
        ++osit;
    }
    REQUIRE_EQ(osit, oset.end());
    REQUIRE_EQ(gint::count(), data.size());
}

TEST_CASE("OSet iterates in reverse")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    auto osit = oset.rbegin();
    auto vecit = data.rbegin();
    while(vecit != data.rend())
    {
        REQUIRE(*osit == *vecit);
        ++vecit;
        ++osit;
    }
    REQUIRE_EQ(gint::count(), data.size());
}

TEST_CASE("OSet clears")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    REQUIRE(oset.size() == data.size());

    oset.clear();

    REQUIRE(oset.size() == 0);
    REQUIRE_EQ(gint::count(), 0);
}

TEST_CASE("OSet removes items")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    REQUIRE(oset.size() == data.size());

    auto target = data[data.size()/2];

    auto result = oset.remove(target);

    REQUIRE(result);
    REQUIRE(oset.size() == data.size()-1);
    REQUIRE(!oset.contains(target));
    REQUIRE(gint::count() == oset.size());

    for(auto a : oset)
    {
        REQUIRE(a != target);
    }
}

TEST_CASE("OSet does not remove nonexistent items")
{
    gint::init();
    auto data = generate_testdata(101);
    gset oset;

    auto target = data.back();
    data.pop_back();

    for(auto a : data)
    {
        oset.add(a);
    }

    REQUIRE(oset.size() == data.size());

    auto result = oset.remove(target);

    REQUIRE(!result);
    REQUIRE(oset.size() == data.size());
    REQUIRE_EQ(gint::count(), data.size());
}

TEST_CASE("OSet can re-add items after removal")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    for(int i = 0; i < data.size(); ++i)
    {
        oset.add(data[i]);
    }

    auto target = data[data.size()/2];

    REQUIRE(oset.size() == data.size());

    auto rmResult = oset.remove(target);

    REQUIRE(rmResult);
    REQUIRE(oset.size() == data.size()-1);

    for(auto a : oset)
    {
        REQUIRE(a != target);
    }

    REQUIRE(!oset.contains(target));

    auto adResult = oset.add(target);

    REQUIRE(adResult);

    REQUIRE(oset.size() == data.size());

    REQUIRE(*(oset.rbegin()) == target);
    REQUIRE_EQ(gint::count(), data.size());
}

TEST_CASE("OSet removal maintains order")
{
    gint::init();
    auto data = generate_testdata(100);
    gset oset;

    auto target_index = data.size()/2;
    auto target = data[target_index];

    for(auto a : data)
    {
        oset.add(a);
    }

    REQUIRE(oset.size() == data.size());

    data.erase(data.begin()+target_index);

    oset.remove(target);

    REQUIRE(oset.size() == data.size());

    auto osit = oset.begin();
    auto vecit = data.begin();
    while(vecit != data.end())
    {
        REQUIRE(*osit == *vecit);
        ++vecit;
        ++osit;
    }
    REQUIRE_EQ(gint::count(), data.size());
}
