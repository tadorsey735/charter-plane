#include "type.h"

#if !defined(GLOBAL_DATA_H_)
#define GLOBAL_DATA_H_

/*======================================================================*/
/* General                                                              */
/*======================================================================*/
#define FALSE (0)
#define TRUE  (1)

#define METERS (0)  // default for altitude
#define MILES  (1)

/*======================================================================*/
/* Route Data                                                           */
/*======================================================================*/
#define MAX_ROUTE_POINTS  (30)

typedef struct LAT_DATA_STRUCT {
    F32 f32LatitudeInputs[MAX_ROUTE_POINTS];  // Spherical (degrees)
    F32 f32LatitudeY[MAX_ROUTE_POINTS];       // Cartesian
} LAT_DATA_STRUCT;

typedef struct LONG_DATA_STRUCT {
    F32 f32LongitudeInputs[MAX_ROUTE_POINTS];  // Sperical (degrees)
    F32 f32LongitudeX[MAX_ROUTE_POINTS];       // Cartesian
} LONG_DATA_STRUCT;

U16 altitudeMeasurementType;

typedef struct ALT_DATA_STRUCT {
    F32 f32AltitudeInputs[MAX_ROUTE_POINTS];  // Spherical (meters)
    F32 f32AltitudeZ[MAX_ROUTE_POINTS];       // Cartesian
} ALT_DATA_STRUCT;

typedef struct TIME_DATA_STRUCT {
    F32 f32TimeInputs[MAX_ROUTE_POINTS];       // Total Elapsed Time (seconds)
} TIME_DATA_STRUCT;

U16 u16RoutePointNum;

LAT_DATA_STRUCT LatitudeDataStructure;
LONG_DATA_STRUCT LongitudeDataStructure;
ALT_DATA_STRUCT AltitudeDataStructure;
TIME_DATA_STRUCT TimeDataStructure;

F32 f32DistanceTraveled[MAX_ROUTE_POINTS];
F32 f32SpeedToNextPoint[MAX_ROUTE_POINTS];

/*======================================================================*/
/* Functions                                                            */
/*======================================================================*/
// main.c
void dataInit(void);

// process_inputs.c
BOOL processInputData(void);
void setRetrievedData(F32, F32, F32, F32);
void outputRoutePointsResults(void);

// calculate.c
void convertPolarToCartesian(void);
void calculateDistanceBetweenPoints(void);
void calculateSpeedBetweenPoints(void);

#endif