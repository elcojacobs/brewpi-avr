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

#ifndef SENSOR_HISTORY_H_
#define SENSOR_HISTORY_H_

#define SENSOR_HISTORY_LENGTH 4

#include "TemperatureFormats.h"
#include "Ticks.h"

/*! \class sensorHistory sensorHistory.h "inc/sensorHistory.h"
* \brief This class keeps a history of time stamped changes (usually LSB changes) of sensor values to calculate the slope
*
* TODO 
*/

/**
* \brief This bit mask defines which bits of the input value are significant enough to log a time stamp.
* 
* Default is the 12 bits from the DS18B20 sensor
*/
#define SENSOR_HISTORY_PRECISION_MASK TEMP_FIXED_POINT_MASK

/**
* \brief This defines the maximum number of seconds to take into account for to calculate the history.
*
* This value should only influence the result when there have been no changes for a while: the slope is near zero.
*/
#define SENSOR_HISTORY_MAX_SECONDS 3600

class sensorHistory
{
public:
	/**
	* \brief Constructor, initializes time stamps to 0-SENSOR_HISTORY_MAX_SECONDS, so they won't be used until overwritten.
	*
	* Also initializes lastValue to INVALID_TEMP, which will trigger the first diff to be registered as zero.
	*/
	sensorHistory(){		
		for(uint8_t i=0; i < SENSOR_HISTORY_LENGTH-1; i++){
			times[i] = ticks_seconds_t(0)-SENSOR_HISTORY_MAX_SECONDS;
			lastValue = INVALID_TEMP;
		}
		
	};
	~sensorHistory();
protected:
	
private:
	/**
	* \brief list of time stamps in seconds for changes in the sensor data
	*/
	ticks_seconds_t times [SENSOR_HISTORY_LENGTH];
	/**
	* \brief list of difference between previous value and new value at each time stamp, in the unmasked bits.
	*/
	int8_t diffs[SENSOR_HISTORY_LENGTH];
	temperature lastValue;
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
void sensorHistory::add(temperature newTemp){
	// mask lower bits
	temperature maskedTemp = newTemp & SENSOR_HISTORY_PRECISION_MASK;
	// if unmasked bits are different, log a time stamp and store the difference
	if(maskedTemp != lastValue){
		// shift old data back one position, oldest is discarded
		for(uint8_t i=1; i < SENSOR_HISTORY_LENGTH; i++){
			times[i] = times[i-1];
			times[i] = diffs[i-1];
		}
		if(lastValue == INVALID_TEMP){
			diffs[0] = 0;
		}
		else{
			diffs[SENSOR_HISTORY_LENGTH] = maskedTemp - lastValue;
		}
		// add difference between newest and previous value
		
		// add time stamp for latest difference
		times[0] = ticks.seconds();
		// remember full value for latest time stamp
		lastValue = newTemp;
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

void sensorHistory::getSlope(temperature currentTemp){
	ticks_seconds_t timeStamp = ticks.seconds();
	int16_t totalDiff = currentTemp - lastValue;
	uint32_t totalTime = 0;
	
	ticks.seconds() - times[0];	
	
	for(uint8_t i=0; i < SENSOR_HISTORY_LENGTH-1; i++){
		ticks_seconds_t timeDiff = times[i] - timeStamp;
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
}

#endif /* SENSOR_HISTORY_H_ */