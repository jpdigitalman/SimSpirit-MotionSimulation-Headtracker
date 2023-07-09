
#include <Marksim_SensorLab.h>

/**************************************************************************/
/*!
  @brief Mapper helper function for floating point values
  @param x Value to map
  @param in_min Input range minimum for x
  @param in_max Input range maximum for x
  @param out_min Ouput range maximum for return
  @param out_max Ouput range maximum for return
  @returns Mapped value
*/

/**************************************************************************/
float Adafruit_SensorLab::mapf(float x, float in_min, float in_max,
                               float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**************************************************************************/
/*!
  @brief Instantiate the SensorLab object
  @param i2c The I2C hardware interface, default is Wire
*/
/**************************************************************************/
Adafruit_SensorLab::Adafruit_SensorLab(TwoWire *i2c) { _i2c = i2c; }

/**************************************************************************/
/*!
  @brief Initialize the sensorlab manager and begin I2C
  @param I2C_Frequency desired I2C clock rate - default is 100KHz
*/
/**************************************************************************/
void Adafruit_SensorLab::begin(uint32_t I2C_Frequency) {
  _i2c->begin();
  _i2c->setClock(I2C_Frequency);
  yield();
}



/**************************************************************************/
/*!
    @brief  Detect if we have a valid LSM6DS33 sensor attached and sets
    the default temperature, accelerometer and gyroscope sensors if so
    @return True if found
*/
/**************************************************************************/
bool Adafruit_SensorLab::detectLSM6DS33(void) {
  bool addr6A = scanI2C(0x6A);
  bool addr6B = scanI2C(0x6B);

  if (!addr6A && !addr6B) {
    return false; // no I2C device that could possibly work found!
  }

  _lsm6ds33 = new Adafruit_LSM6DS33();

  if ((addr6A && _lsm6ds33->begin_I2C(0x6A, _i2c)) ||
      (addr6B && _lsm6ds33->begin_I2C(0x6B, _i2c))) {
    // yay found a LSM6DS33
    Serial.println(F("Found a LSM6DS33 IMU"));

    if (!accelerometer)
      accelerometer = _lsm6ds33->getAccelerometerSensor();
    if (!gyroscope)
      gyroscope = _lsm6ds33->getGyroSensor();
    if (!temperature) {
      temperature = _lsm6ds33->getTemperatureSensor();
    }
    return true;
  }

  delete _lsm6ds33;
  return false;
}

/**************************************************************************/
/*!
    @brief  Detect if we have a valid LSM6DS3TR-C sensor attached and sets
    the default temperature, accelerometer and gyroscope sensors if so
    @return True if found
*/
/**************************************************************************/
bool Adafruit_SensorLab::detectLSM6DS3TRC(void) {
  bool addr6A = scanI2C(0x6A);
  bool addr6B = scanI2C(0x6B);

  if (!addr6A && !addr6B) {
    return false; // no I2C device that could possibly work found!
  }

  _lsm6ds3trc = new Adafruit_LSM6DS3TRC();

  if ((addr6A && _lsm6ds3trc->begin_I2C(0x6A, _i2c)) ||
      (addr6B && _lsm6ds3trc->begin_I2C(0x6B, _i2c))) {
    // yay found a LSM6DS3TR-C
    Serial.println(F("Found a LSM6DS3TR-C IMU"));

    if (!accelerometer)
      accelerometer = _lsm6ds3trc->getAccelerometerSensor();
    if (!gyroscope)
      gyroscope = _lsm6ds3trc->getGyroSensor();
    if (!temperature) {
      temperature = _lsm6ds3trc->getTemperatureSensor();
    }
    return true;
  }

  delete _lsm6ds3trc;
  return false;
}

/**************************************************************************/
/*!
    @brief  Detect if we have a valid LSM6DSOX sensor attached and sets
    the default temperature, accelerometer and gyroscope sensors if so
    @return True if found
*/
/**************************************************************************/
bool Adafruit_SensorLab::detectLSM6DSOX(void) {
  bool addr6A = scanI2C(0x6A);
  bool addr6B = scanI2C(0x6B);

  if (!addr6A && !addr6B) {
    return false; // no I2C device that could possibly work found!
  }

  _lsm6dsox = new Adafruit_LSM6DSOX();

  if ((addr6A && _lsm6dsox->begin_I2C(0x6A, _i2c)) ||
      (addr6B && _lsm6dsox->begin_I2C(0x6B, _i2c))) {
    // yay found a LSM6DSOX
    Serial.println(F("Found a LSM6DSOX IMU"));

    if (!accelerometer)
      accelerometer = _lsm6dsox->getAccelerometerSensor();
    if (!gyroscope)
      gyroscope = _lsm6dsox->getGyroSensor();
    if (!temperature) {
      temperature = _lsm6dsox->getTemperatureSensor();
    }
    return true;
  }

  delete _lsm6dsox;
  return false;
}





/**************************************************************************/
/*!
    @brief  Detect if we have a valid ISM330DHC sensor attached and sets
    the default temperature, accelerometer and gyroscope sensors if so
    @return True if found
*/
/**************************************************************************/
bool Adafruit_SensorLab::detectISM330DHCX(void) {
  bool addr6A = scanI2C(0x6A);
  bool addr6B = scanI2C(0x6B);

  if (!addr6A && !addr6B) {
    return false; // no I2C device that could possibly work found!
  }

  _ism330dhcx = new Adafruit_ISM330DHCX();

  if ((addr6A && _ism330dhcx->begin_I2C(0x6A, _i2c)) ||
      (addr6B && _ism330dhcx->begin_I2C(0x6B, _i2c))) {
    // yay found a ISM330
    Serial.println(F("Found a ISM330DHCX IMU"));

    if (!accelerometer)
      accelerometer = _ism330dhcx->getAccelerometerSensor();
    if (!gyroscope)
      gyroscope = _ism330dhcx->getGyroSensor();
    if (!temperature) {
      temperature = _ism330dhcx->getTemperatureSensor();
    }
    return true;
  }

  delete _ism330dhcx;
  return false;
}


/**************************************************************************/
/*!
    @brief  Look for any known accelerometer-providing sensor on I2C
    @return A pointer to the Adafruit_Sensor device that can be queried
    for sensor events. NULL on failure to find any matching sensor.
*/
/**************************************************************************/
Adafruit_Sensor *Adafruit_SensorLab::getAccelerometer(void) {
  if (accelerometer) {
    return accelerometer; // we already did this process
  }
  if (detectLSM6DS33() || detectLSM6DS3TRC() || detectLSM6DSOX()) {
    return accelerometer;
  }
  
  // Nothing detected
  return NULL;
}

/**************************************************************************/
/*!
    @brief  Look for any known magnetometer-providing sensor on I2C
    @return A pointer to the Adafruit_Sensor device that can be queried
    for sensor events. NULL on failure to find any matching sensor.
*/
/**************************************************************************/
Adafruit_Sensor *Adafruit_SensorLab::getMagnetometer(void) {
  if (magnetometer) {
    return magnetometer; // we already did this process
  }
  // Nothing detected
  return NULL;
}

/**************************************************************************/
/*!
    @brief  Look for any known gyroscope-providing sensor on I2C
    @return A pointer to the Adafruit_Sensor device that can be queried
    for sensor events. NULL on failure to find any matching sensor.
*/
/**************************************************************************/
Adafruit_Sensor *Adafruit_SensorLab::getGyroscope(void) {
  if (gyroscope) {
    return gyroscope; // we already did this process
  }
  if (detectLSM6DS33() || detectLSM6DS3TRC() || detectLSM6DSOX()) {
    return gyroscope;
  }
  
  // Nothing detected
  return NULL;
}

/**************************************************************************/
/*!
    @brief  Look for any known barometric pressure-providing sensor on I2C
    @return A pointer to the Adafruit_Sensor device that can be queried
    for sensor events. NULL on failure to find any matching sensor.
*/
/**************************************************************************/
Adafruit_Sensor *Adafruit_SensorLab::getPressureSensor(void) {
  if (pressure) {
    return pressure; // we already did this process
  }  
  // Nothing detected
  return NULL;
}

/**************************************************************************/
/*!
    @brief  Look for any known temperature-providing sensor on I2C
    @return A pointer to the Adafruit_Sensor device that can be queried
    for sensor events. NULL on failure to find any matching sensor.
*/
/**************************************************************************/
Adafruit_Sensor *Adafruit_SensorLab::getTemperatureSensor(void) {
  if (temperature) {
    return temperature; // we already did this process
  }  
  
  // Nothing detected
  return NULL;
}

/**************************************************************************/
/*!
    @brief  Look for any known humidity-providing sensor on I2C
    @return A pointer to the Adafruit_Sensor device that can be queried
    for sensor events. NULL on failure to find any matching sensor.
*/
/**************************************************************************/
Adafruit_Sensor *Adafruit_SensorLab::getHumiditySensor(void) {
  if (humidity) {
    return humidity; // we already did this process
  }  
  // Nothing detected
  return NULL;
}

/*!
 * @brief Calculates the approximate altitude using barometric pressure and the
 * supplied 'zero' point (e.g. sea level) hPa as a reference.
 * @param currentPressure_hPa The pressure at your current location
 * @param originPressure_hPa The pressure at your 'zero' point
 * @return The approximate altitude in meters.
 */
float Adafruit_SensorLab::calculateAltitude(float currentPressure_hPa,
                                            float originPressure_hPa) {
  return 44330 * (1.0 - pow(currentPressure_hPa / originPressure_hPa, 0.1903));
}

bool Adafruit_SensorLab::scanI2C(uint8_t addr) {
  yield();

  // A basic scanner, see if it ACK's
  _i2c->beginTransmission(addr);
  bool f = (_i2c->endTransmission() == 0);
  if (f) {
    // Serial.print("Found addr 0x");
    // Serial.println(addr, HEX);
  }
  return f;
}
