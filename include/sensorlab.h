
#include <Marksim_SensorLab.h>
#include <Marksim_Sensor_Calibration.h>
#include <Marksim_AHRS.h>

Adafruit_Madgwick filter;  //

#define FILTER_UPDATE_RATE_HZ 100
uint32_t timestamp;

Adafruit_SensorLab lab;
Adafruit_Sensor *accelerometer, *gyroscope, *magnetometer;

#if defined(ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM)
  Adafruit_Sensor_Calibration_EEPROM cal;
#else
  Adafruit_Sensor_Calibration_SDFat cal;
#endif

void sensorsetup() {

  Serial.println(F("Sensor Lab - IMU AHRS!"));
  lab.begin();
  
  if (!cal.begin()) {
    Serial.println("Failed to initialize calibration helper");
  } else if (! cal.loadCalibration()) {
    Serial.println("No calibration loaded/found");
  }

  Serial.println("Looking for a magnetometer");
  magnetometer = lab.getMagnetometer();
  if (! magnetometer) {
    Serial.println(F("Could not find a magnetometer!"));
    //while (1) yield();
  }
  
  Serial.println("Looking for a gyroscope");
  gyroscope = lab.getGyroscope();
  if (! gyroscope) {
    Serial.println(F("Could not find a gyroscope!"));
    while (1) yield();
  }
  
  Serial.println("Looking for a accelerometer");
  accelerometer = lab.getAccelerometer();
  if (! accelerometer) {
    Serial.println(F("Could not find a accelerometer!"));
    while (1) yield();
  }
  
  accelerometer->printSensorDetails();
  gyroscope->printSensorDetails();
  //magnetometer->printSensorDetails();

  filter.begin(FILTER_UPDATE_RATE_HZ);
  timestamp = millis();

  //Wire.setClock(400000); // 400KHz
}


void sensorloop(float &roll, float &pitch, float &heading) {  
    float gx, gy, gz;

    if ((millis() - timestamp) < (1000 / FILTER_UPDATE_RATE_HZ)) {
      return;
    }
    timestamp = millis();
    // Read the motion sensors
    sensors_event_t accel, gyro, mag;
    PRINT("eventing: ");
    accelerometer->getEvent(&accel);
    gyroscope->getEvent(&gyro);
    //magnetometer->getEvent(&mag);
    PRINT("I2C took "); PRINT(millis()-timestamp); PRINTLINE(" ms");
      
    cal.calibrate(mag);
    cal.calibrate(accel);
    cal.calibrate(gyro);
    // Gyroscope needs to be converted from Rad/s to Degree/s
    // the rest are not unit-important
    gx = gyro.gyro.x * SENSORS_RADS_TO_DPS;
    gy = gyro.gyro.y * SENSORS_RADS_TO_DPS;
    gz = gyro.gyro.z * SENSORS_RADS_TO_DPS;

    // Update the SensorFusion filter
    
    filter.update(gx, gy, gz,
                  accel.acceleration.x, accel.acceleration.y, accel.acceleration.z, 
                  mag.magnetic.x, mag.magnetic.y, mag.magnetic.z);
    PRINT("Update took "); PRINT(millis()-timestamp); PRINTLINE(" ms");

    PRINT("Raw: ");
    PRINT(accel.acceleration.x, 4); PRINT(", ");
    PRINT(accel.acceleration.y, 4); PRINT(", ");
    PRINT(accel.acceleration.z, 4); PRINT(", ");
    PRINT(gx, 4); PRINT(", ");
    PRINT(gy, 4); PRINT(", ");
    PRINT(gz, 4); PRINT(", ");
    PRINT(mag.magnetic.x, 4); PRINT(", ");
    PRINT(mag.magnetic.y, 4); PRINT(", ");
    PRINT(mag.magnetic.z, 4); PRINTLINE("");

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = (360.00-filter.getYaw());
    PRINT("Orientation: ");
    PRINT(heading);
    PRINT(" ");
    PRINT(pitch);
    PRINT(" ");
    PRINTLINE(roll);
    PRINT("Took "); PRINT(millis()-timestamp); PRINTLINE(" ms");

  
}
