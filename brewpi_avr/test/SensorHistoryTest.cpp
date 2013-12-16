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

TEST(SensorHistoryTest, lastValueTest){
    SensorHistory history;
    
    ASSERT_EQ(INVALID_TEMP, history.getLastValue()) <<  "last value should return INVALID_TEMP after init";
    
    // Store two values. Keep in mind that the stored value is rounded.   
    history.add(intToTemp(20),1);
    history.add(intToTemp(21),2);
    ASSERT_EQ(intToTemp(21), history.getLastValue());
}

TEST(SensorHistoryTest, addConstantTempAfterInit){
    SensorHistory history;
    for(int i=0;i < SENSOR_HISTORY_LENGTH; i++){
        history.add(intToTemp(20), i*20);
    }
    ASSERT_EQ(0, history.getSum()) << "Adding same temperature 5 times should give 0 as sum of differences";
    ASSERT_EQ(0, history.getSlope(intToTemp(20), 200)) << "Adding same temperature 5 times should give 0 as slope";       
}

TEST(SensorHistoryTest, addRisingTempAfterInitInMinDiffSteps){
    SensorHistory history;
    for(int i=0;i < SENSOR_HISTORY_LENGTH + 5; i++){
        // add minimal significant difference a few times
        history.add(intToTemp(20)+ i*(1*SENSOR_HISTORY_MIN_DIFF), i*200);        
         if(i>0){
            ASSERT_EQ(1, history.diffs[0]) << "Last diff should be 1";
            ASSERT_EQ(i*200, history.times[0]) << "Last timestamp should be i*200 = " << i*200;
        }
    }
    for(int i=0;i < SENSOR_HISTORY_LENGTH -1; i++){
        ASSERT_EQ(1, history.diffs[i]) << "All diffs should be 1, failed at i = " << i;
        ASSERT_EQ((SENSOR_HISTORY_LENGTH+5-1-i)*200, history.times[i]) << "Times[i] incorrect at i = " << i;
    }
    temperature expectedSlope = SENSOR_HISTORY_MIN_DIFF*3600/200;
    ASSERT_EQ(expectedSlope, history.getSlope(intToTempDiff(1), 1601)) << 
            "Adding MIN_DIFF (" << SENSOR_HISTORY_MIN_DIFF << 
            ") per 200 seconds should give a slope of 3600/200*MIN_DIFF (" << 
            expectedSlope << ") per hour" <<
            "Full history: " << history;
}

TEST(SensorHistoryTest, addRisingTempAfterInitIn1CSteps){
    SensorHistory history;
    for(int i=0;i < SENSOR_HISTORY_LENGTH + 5; i++){
        // add minimal significant difference a few times
        history.add(intToTemp(20)+ intToTempDiff(i), i*200);        
    }
    temperature expectedSlope = intToTempDiff(1)*3600/200;
    ASSERT_EQ(expectedSlope, history.getSlope(intToTempDiff(1), 1600)) << 
            "Adding 1C (" << SENSOR_HISTORY_MIN_DIFF << 
            ") per 200 seconds should give a slope of 3600/200*1C (" << 
            expectedSlope << ") per hour" <<
            "Full history: " << history;
    
    ASSERT_EQ(expectedSlope, history.getSlope(intToTempDiff(1), 1700)) << 
            "Slope should still read the same 100s after adding the last point";
        
    ASSERT_LT(history.getSlope(intToTempDiff(1), 1900), expectedSlope) << 
            "Slope should decline if no new point is added after the expected time";    
}