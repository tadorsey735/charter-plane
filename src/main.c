#include "../def/type.h"
#include "../def/global_data.h"


/*======================================================================*/
void main(void)
/*======================================================================*/
{
    BOOL result = FALSE;

    // initialize program data
    dataInit();

    // get input data & perform calculations
    result = processInputData();

    if (result == TRUE) {
        printf("\nProgram complete\n");
    }
    else {
        printf("\nSorry, something went wrong\n");
    }
    printf("\n   Press enter to exit ...");
    getchar();
}
/**********  End Function ***********************************************/


/*======================================================================*/
void dataInit(void)
/*======================================================================*/
{
    U16 i;

    u16RoutePointNum = 0;
    for (i = 0; i < MAX_ROUTE_POINTS; i++) {
        LatitudeDataStructure.f32LatitudeInputs[i]   = 0;
        LongitudeDataStructure.f32LongitudeInputs[i] = 0;
        AltitudeDataStructure.f32AltitudeInputs[i]   = 0;
        TimeDataStructure.f32TimeInputs[i]           = 0;

        LatitudeDataStructure.f32LatitudeY[i]        = 0;
        LongitudeDataStructure.f32LongitudeX[i]      = 0;
        AltitudeDataStructure.f32AltitudeZ[i]        = 0;

        f32DistanceTraveled[i] = 0;
        f32SpeedToNextPoint[i] = 0;
    }

    // default altitude measurement type to meters
    altitudeMeasurementType = METERS;
}
/**********  End Function ***********************************************/