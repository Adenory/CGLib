#include "gtest/gtest.h"

#include "StringTable.h"

using namespace Crystal::IO;

TEST(StringTableTest, TestAdd)
{
	StringTable table;
	table.add( "ID_HELLO", "����ɂ���");
	const auto actual = table.get("ID_HELLO");
	EXPECT_EQ("����ɂ���", actual);
	table.changeLocale("English");
	table.add("ID_HELLO", "Hello!");
	EXPECT_EQ("Hello!", table.get("ID_HELLO"));
}


TEST(StringTableTest, TestRead)
{
	StringTable table;
	EXPECT_TRUE( table.read(Crystal::File("../TestFile/IO/StringTable/TestWriteStringTable.xml")) );
	table.changeLocale("English");
	EXPECT_EQ("Hello!", table.get("ID_HELLO"));
	table.changeLocale("Japanese");
	EXPECT_EQ("����ɂ���!", table.get("ID_HELLO"));

}

TEST(StringTableTest, TestWrite)
{
	StringTable table;
	table.add("ID_HELLO", "Hello!");
	table.changeLocale("Japanese");
	table.add("ID_HELLO", "����ɂ���!");
	table.write("../TestFile/IO/StringTable", "TestWriteStringTable.xml");
}