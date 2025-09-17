#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <oset.h>
#include <vector>
#include <set>
#include <random>

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
    nmg::OSet<int> oset;
    REQUIRE(oset.empty());
    REQUIRE(oset.size() == 0);
}

TEST_CASE("adding items to oset increases size")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

    int size = 0;
    for(auto a : data)
    {
        auto result = oset.add(a);
        REQUIRE(result);
        REQUIRE(oset.size() == ++size);
    }
    REQUIRE(oset.size() == data.size());
}

TEST_CASE("oset does not add duplicates")
{
    auto data = generate_testdata(10);
    std::vector<int> copy(data);
    nmg::OSet<int> oset;

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
    }
}

TEST_CASE("oset is iterable")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

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
}

TEST_CASE("oset iterates in order")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    auto osit = oset.begin();
    auto vecit = data.begin();
    while(vecit != data.end())
    {
        REQUIRE(*osit == *vecit);
        ++vecit;
        ++osit;
    }
}

TEST_CASE("OSet iterates in reverse")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

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
}

TEST_CASE("OSet clears")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

    for(auto a : data)
    {
        oset.add(a);
    }

    REQUIRE(oset.size() == data.size());

    oset.clear();

    REQUIRE(oset.size() == 0);
}

TEST_CASE("OSet removes items")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

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

    for(auto a : oset)
    {
        REQUIRE(a != target);
    }
}

TEST_CASE("OSet does not remove nonexistent items")
{
    auto data = generate_testdata(101);
    nmg::OSet<int> oset;

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
}

TEST_CASE("OSet can re-add items after removal")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

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
}

TEST_CASE("OSet removal maintains order")
{
    auto data = generate_testdata(100);
    nmg::OSet<int> oset;

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
}
