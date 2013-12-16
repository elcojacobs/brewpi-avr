/*
 * Copyright 2012-2013 BrewPi/Elco Jacobs.
 * Copyright 2013 Matthew McGowan.
 *
 * This file is part of BrewPi.
 * 
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SensorHistory.h"
#include "TemperatureFormats.h"
#include "Ticks.h"

/**
 * \brief Constructor, initializes time stamps to 0-SENSOR_HISTORY_MAX_SECONDS, so they won't be used until overwritten.
 *
 * Also initializes lastValue to INVALID_TEMP, which will trigger the first diff to be registered as zero.
 */

SensorHistory::SensorHistory(){		
        for(uint8_t i=0; i < SENSOR_HISTORY_LENGTH; i++){
                diffs[i] = 0;
		times[i] = -SENSOR_HISTORY_MAX_SECONDS;
        }
        lastValue = INVALID_TEMP;
};

/**
 * \brief Checks whether the temperature to be added is different from previous temperature and adds it to the transition list
 *
 * This function will take a temperature and will compare it to the previous temperature that was added, masked with the precision bits.
 * The default precision is the native DS18B20 sensor resolution. When the value is different, it stores a timestamp in seconds and 
 * the difference with the previous value. Previous history is shifted back, discarding the oldest.
 *
 * @param newTemp A new temperature value to update the change history.
 */

void SensorHistory::add(temperature newTemp, ticks_seconds_t currentTime){
	if(newTemp == INVALID_TEMP){
		return;
	}	
	// mask lower bits after rounding
	temperature shiftedTemp = (newTemp + (1<<SENSOR_HISTORY_IGNORED_BITS-1)) >> SENSOR_HISTORY_IGNORED_BITS;
	// if unmasked bits are different, log a time stamp and store the difference
	if(shiftedTemp != lastValue){
		// shift old data back one position, oldest is discarded
		for(uint8_t i=SENSOR_HISTORY_LENGTH-1; i > 0; i--){
			times[i] = times[i-1];
			diffs[i] = diffs[i-1];
		}
		if(lastValue == INVALID_TEMP){
			diffs[0] = 0;
		}
		else{
                        // add difference between newest and previous value
                    diffs[0] = shiftedTemp - lastValue;
		}
		
		
		// add time stamp for latest difference
		times[0] = currentTime;
		// remember full value for latest time stamp
		lastValue = shiftedTemp;
	}
}

/**
 * \brief Calculates the slope from sensor history
 *
 * This function will calculate the slope of the signal based on the stored timestamped differences.
 * 
 * The full list is used if the oldest sample is newer than SENSOR_HISTORY_MAX_SECONDS. Otherwise, only
 * the samples newer than SENSOR_HISTORY_MAX_SECONDS are used.
 * 
 * @param currentTemp The current temperature in the internal temperature format
 * @param currentTime The current time in seconds
 * @return the slope of the temperature sensor, in dT/h
 */

temperature SensorHistory::getSlope(temperature currentTemp, ticks_seconds_t currentTime){
	int16_t totalTempDiff = 0;
	ticks_seconds_t totalTimeDiff=1;
        ticks_seconds_t time = currentTime;
	for(uint8_t i=0;i < SENSOR_HISTORY_LENGTH; i++){                
		if(totalTimeDiff < SENSOR_HISTORY_MAX_SECONDS){
			totalTempDiff += diffs[i];
                        totalTimeDiff = currentTime - times[i];                
		}
                else{
                    totalTimeDiff = SENSOR_HISTORY_MAX_SECONDS;
                    break;
                }                
	}
        ticks_seconds_t newestPeriod = currentTime-times[0];
        ticks_seconds_t oldestPeriod = times[SENSOR_HISTORY_LENGTH-2] - times[SENSOR_HISTORY_LENGTH-1];        
        if(newestPeriod < oldestPeriod){
            // Time between two oldest values is larger than time since newest point
            // Add difference to total time to smooth out the transition
            // This basically uses the expected period for the newest value if the slope is constant.
            totalTimeDiff += oldestPeriod - newestPeriod;
        }
        // return slope per hour
        return (totalTempDiff * (3600<<SENSOR_HISTORY_IGNORED_BITS)) / totalTimeDiff;
}

/**
 * \brief Returns the sum of the stored temperature differences. Mainly used for testing.
 *
 * This function sums the stored differences and shifts it back to normal precision before returning the value.
 *
 * @return sum of temperature differences stored in history.
 */

temperature SensorHistory::getSum(){
    int32_t totalDiff = 0;
    for(uint8_t i=0; i < SENSOR_HISTORY_LENGTH; i++){
		totalDiff += diffs[i];		
    }        
    // Scale result back to normal precision before returning it
    return totalDiff<<SENSOR_HISTORY_IGNORED_BITS;
}

/**
 * \brief Returns the last value stored in the history
 *
 * @return last stored temperature.
 */

temperature SensorHistory::getLastValue(){
    return (lastValue == INVALID_TEMP) ? INVALID_TEMP : lastValue<<SENSOR_HISTORY_IGNORED_BITS;
}