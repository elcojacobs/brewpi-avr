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

#pragma once

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
#define SENSOR_HISTORY_IGNORED_BITS 4
#define SENSOR_HISTORY_MIN_DIFF (1<<SENSOR_HISTORY_IGNORED_BITS)

/**
* \brief This defines the maximum number of seconds to take into account for to calculate the history.
*
* This value should only influence the result when there have been no changes for a while: the slope is near zero.
*/
#define SENSOR_HISTORY_MAX_SECONDS 3600

class SensorHistory
{
public:
	/**
	* \brief Constructor, initializes time stamps to 0-SENSOR_HISTORY_MAX_SECONDS, so they won't be used until overwritten.
	*
	* Also initializes lastValue to INVALID_TEMP, which will trigger the first diff to be registered as zero.
	*/
	SensorHistory();
	~SensorHistory(){};
        void add(temperature newTemp, ticks_seconds_t currentTime);
        temperature getSlope(temperature currentTemp, ticks_seconds_t currentTime);
        temperature getSum();
//protected:
	
//private:
	/**
	* \brief list of time stamps in seconds for changes in the sensor data
	*/
	ticks_seconds_t times [SENSOR_HISTORY_LENGTH];
	/**
	* \brief list of difference between previous value and new value at each time stamp, in the unmasked bits.
	*/
	temperature diffs[SENSOR_HISTORY_LENGTH];
	temperature lastValue;
};