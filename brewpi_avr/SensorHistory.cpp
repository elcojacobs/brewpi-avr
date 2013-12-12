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
	// mask lower bits
	temperature shiftedTemp = newTemp >> SENSOR_HISTORY_IGNORED_BITS;
	// if unmasked bits are different, log a time stamp and store the difference
	if(shiftedTemp != lastValue){
		// shift old data back one position, oldest is discarded
		for(uint8_t i=0; i < SENSOR_HISTORY_LENGTH-1; i++){
			times[i+1] = times[i];
			diffs[i+1] = diffs[i];
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
  * The full list is used if the oldest sample is newer than SENSOR_HISTORY_MAX_SECONDS. Otherwise, only
  * the samples newer than SENSOR_HISTORY_MAX_SECONDS are used.
  *
  * @return the slope of the temperature sensor, in dT/h
  */

temperature SensorHistory::getSlope(temperature currentTemp, ticks_seconds_t currentTime){
	ticks_seconds_t timeStamp = currentTime;
	int16_t totalDiff = 0;
	uint32_t totalTime = 0;
	
	timeStamp = currentTime - times[0];
	
	for(uint8_t i=0;i < SENSOR_HISTORY_LENGTH-1; i++){
		ticks_seconds_t timeDiff = timeStamp - times[i];
		totalTime += timeDiff;
		if(totalTime > SENSOR_HISTORY_MAX_SECONDS){
			// stop adding points and add SENSOR_HISTORY_MAX_SECONDS to total time, because there has been no change for that time.
			totalTime = SENSOR_HISTORY_MAX_SECONDS;
			break;
		}
		else{
			totalDiff += diffs[i];
			timeStamp = times[i];
		}
	}
        return totalDiff / totalTime;
}

temperature SensorHistory::getSum(){
    int32_t totalDiff = 0;
    for(uint8_t i=0; i < SENSOR_HISTORY_LENGTH; i++){
		totalDiff += diffs[i];		
    }        
    // Scale result back to normal precision before returning it
    return totalDiff<<SENSOR_HISTORY_IGNORED_BITS;
}