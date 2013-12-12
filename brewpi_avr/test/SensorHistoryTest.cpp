#include "gtest/gtest.h"
#include "TemperatureFormats.h"
#include "SensorHistory.h"


// Teach Google test to print an instance of SensorHistory
::std::ostream& operator<<(::std::ostream& os, const SensorHistory& sensorHistory) {
    os << "\nContent of SensorHistory:";
    os << "diff \t timestamp\n";
    for(uint8_t i=0;i < SENSOR_HISTORY_LENGTH; i++){
        os << ::testing::PrintToString(sensorHistory.diffs[i]) << "\t"
            << ::testing::PrintToString(sensorHistory.times[i]) << "\n";
    }
    os << "lastValue: " << ::testing::PrintToString(sensorHistory.lastValue) << "\n";
}

TEST(SensorHistoryTest, init){
    SensorHistory history;
    ASSERT_EQ(0, history.getSum()) << "All diffs are initialized to 0, sum should be 0" << history;
    ASSERT_EQ(0, history.getSlope(intToTemp(0), 0)) << "The slope should be zero after init" << history;
}

TEST(SensorHistoryTest, addConstantTempAfterInit){
    SensorHistory history;
    for(uint8_t i=0;i < SENSOR_HISTORY_LENGTH; i++){
        history.add(intToTemp(20), i*20);
    }
    ASSERT_EQ(0, history.getSum()) << "Adding same temperature 5 times should give 0 as sum of differences";
    ASSERT_EQ(0, history.getSlope(intToTemp(20), 200)) << "Adding same temperature 5 times should give 0 as slope";       
}

TEST(SensorHistoryTest, addRisingTempAfterInit){
    SensorHistory history;
    for(uint8_t i=0;i < SENSOR_HISTORY_LENGTH + 5; i++){
        // add minimal significant difference a few times
        history.add(intToTemp(20)+ i*SENSOR_HISTORY_MIN_DIFF, i*20);        
        //std::cout << "Storing diff " << ::testing::PrintToString(history.diffs[0]) << 
        //        " at time " << ::testing::PrintToString(history.times[0]) << std::endl;
        if(i>0){
            ASSERT_EQ(1, history.diffs[0]) << "Last diff should be 1";
        }
    }    
    ASSERT_EQ(SENSOR_HISTORY_MIN_DIFF/20, history.getSlope(intToTempDiff(1), 120)) << "Adding same temperature 5 times should give 0 as slope";       
}