
#include "gtest/gtest.h"
#include "ArrayEepromAccess.h"

TEST(ArrayEepromAccessTest, sspromLengthIs1024) {
    ArrayEepromAccess sut;
    EXPECT_EQ(1024, sut.eepromLength()) << "Array size should be 1024";
}

TEST(ArrayEepromAccessTest, eepromDataInitialized) {
    ArrayEepromAccess sut;
    EXPECT_FALSE(sut.changed()) << "Eeprom should be unchanged after initialization";
    for (int i=0; i<sut.eepromLength(); i++)
        ASSERT_EQ(255, sut.readByte(i)) << "expected value -1 at offset " << i;
}

TEST(ArrayEepromAccessTest, readInvalidOffsetReturnsZero) {
    ArrayEepromAccess sut;
    EXPECT_EQ(0, sut.readByte(sut.eepromLength()+10)) << "Invalid offset should be returned as 0";
}

TEST(ArrayEepromAccessTest, eepromChangedAfterWrite) {
    ArrayEepromAccess sut;
    EXPECT_FALSE(sut.changed()) << "Eeprom should be unchanged after construction";
    sut.writeByte(10, 20);
    EXPECT_TRUE(sut.changed()) << "Eeprom should be changed after writeByte";
    EXPECT_FALSE(sut.changed()) << "Eeprom should be unchanged";    
}

TEST(ArrayEepromAccessTest, eepromChangedAfterWriteBlock) {
    ArrayEepromAccess sut;
    EXPECT_FALSE(sut.changed()) << "Eeprom should be unchanged after construction";
    char buf[20];
    sut.writeBlock(0, &buf, sizeof(buf));
    EXPECT_TRUE(sut.changed()) << "Eeprom should be changed after writeBlock";
    EXPECT_FALSE(sut.changed()) << "Eeprom should be unchanged";    
}



// todo - complete