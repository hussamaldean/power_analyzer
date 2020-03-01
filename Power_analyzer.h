
#ifndef Power_analyzer
#define Power_analyzer

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#ifndef READVCC_CALIBRATION_CONST
#define READVCC_CALIBRATION_CONST 1126400L
#endif

#if defined(__arm__)
#define ADC_BITS    12
#else
#define ADC_BITS    10
#endif

#define ADC_COUNTS  (1<<ADC_BITS)


class power_analyzer
{
  public:

    void voltage(unsigned int _inPinV, double _VCAL, double _PHASECAL);
    void current(unsigned int _inPinI, double _ICAL);

    void voltageTX(double _VCAL, double _PHASECAL);
    void currentTX(unsigned int _channel, double _ICAL);

    void calcVI(unsigned int crossings, unsigned int timeout);
    double calcIrms(unsigned int NUMBER_OF_SAMPLES);
    void serialprint();

    long readVcc();
    //Useful value variables
    double realPower,
      apparentPower,
      powerFactor,
      Vrms,
      Irms;

  private:

    //Set Voltage and current input pins
    unsigned int inPinV;
    unsigned int inPinI;
    //Calibration coefficients
    //These need to be set in order to obtain accurate results
    double VCAL;
    double ICAL;
    double PHASECAL;


    int sampleV;                        //sample_ holds the raw analog read value
    int sampleI;

    double lastFilteredV,filteredV;          //Filtered_ is the raw analog value minus the DC offset
    double filteredI;
    double offsetV;                          //Low-pass filter output
    double offsetI;                          //Low-pass filter output

    double phaseShiftedV;                             //Holds the calibrated phase shifted voltage.

    double sqV,sumV,sqI,sumI,instP,sumP;              //sq = squared, sum = Sum, inst = instantaneous

    int startV;                                       //Instantaneous voltage at start of sample window.

    boolean lastVCross, checkVCross;                  //Used to measure number of times threshold is crossed.


};

#endif
