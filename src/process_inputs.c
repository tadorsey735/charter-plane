#include <stdio.h>
#include "../def/type.h"
#include "../def/global_data.h"

/************************************************************************/
BOOL processInputData(void)
/*======================================================================*/
{
    U16 i;
    FILE *fp;
    CHAR str[3];
    F32 latitude, longitude, altitude, minutes;

    fp = fopen("inputs.txt", "r");

    if (!fp) {
        printf("\nError opening inputs file\n");
        return FALSE;
    }
    printf("\nRetrieving inputs ...\n");

    //read file line by line
    U16 inputCount = 0;
    while (fgets(str, 2, fp) != NULL ) {
        fscanf(fp, "%7f %7f %10f %7f", &latitude, &longitude, &altitude, &minutes);
        setRetrievedData(latitude, longitude, altitude, minutes);
        inputCount++;
        if (inputCount >= MAX_ROUTE_POINTS) {
            break;
        }
    }
    
    printf("\nWow, that was a great read! Here's what I gathered:\n");

    // convert retrieved data points to cartesian points
    convertSphericalToCartesian();
    calculateDistanceBetweenPoints();
    calculateSpeedBetweenPoints();

    outputRoutePointsResults();

    fclose(fp);
    return TRUE;
}
/**********  End Function ***********************************************/


/*======================================================================*/
void setRetrievedData(
    F32 inputLat,
    F32 inputLong,
    F32 inputAlt,
    F32 inputMins)
/*======================================================================*/
{
    // Limit Latitude to a range of 0 and 360 inclusive
    if (inputLat < 0.0) {
        inputLat = 0.0;
    }
    else if (inputLat > 360.0) {
        inputLat = 360.0;
    }
    // Limit Longitude to a range of 0 and 360 inclusive
    if (inputLong < 0.0) {
        inputLong = 0.0;
    }
    else if (inputLong > 360.0) {
        inputLat = 360.0;
    }
    // Limit Time to positive values
    if (inputMins < 0.0) {
        inputMins = 0.0;
    }
    // Don't set data if all inputs are zero (assume input read error)
    if ((inputLat != 0.0) || (inputLong != 0.0) || (inputAlt != 0.0) || (inputMins != 0.0)) {
        LatitudeDataStructure.f32LatitudeInputs[u16RoutePointNum]   = inputLat;
        LongitudeDataStructure.f32LongitudeInputs[u16RoutePointNum] = inputLong;
        AltitudeDataStructure.f32AltitudeInputs[u16RoutePointNum]   = inputAlt;
        TimeDataStructure.f32TimeInputs[u16RoutePointNum]           = inputMins;
        u16RoutePointNum++;
    }
}
/**********  End Function ***********************************************/


/*======================================================================*/
void outputRoutePointsResults(void)
/*======================================================================*/
{
    U16 i;

    for (i = 0; i < u16RoutePointNum; i++) {
        printf("\nRoute Point ");
        printf("%d", i + 1);
        printf(" Set:\n");

        printf("    Spherical Latitude:  ");
        printf("%7.3f", LatitudeDataStructure.f32LatitudeInputs[i]);
        printf(" [Cartesian (Y): ");
        printf("%7.3f", LatitudeDataStructure.f32LatitudeY[i]);
        printf("]\n");

        printf("    Spherical Longitude: ");
        printf("%7.3f", LongitudeDataStructure.f32LongitudeInputs[i]);
        printf(" [Cartesian (X): ");
        printf("%7.3f", LongitudeDataStructure.f32LongitudeX[i]);
        printf("]\n");

        printf("    Spherical Altitude:  ");
        printf("%7.3f", AltitudeDataStructure.f32AltitudeInputs[i]);
        printf(" [Cartesian (Z): ");
        printf("%7.3f", AltitudeDataStructure.f32AltitudeZ[i]);
        printf("]\n");

        if (i != 0) {
            printf("    Distance From Last Point: ");
            printf("%7.3f", f32DistanceTraveled[i]);
            printf(" meters");
            printf("\n");
        }

        printf("    Total Time Elapsed: ");
        printf("%7.3f", TimeDataStructure.f32TimeInputs[i]);
        printf(" seconds");
        printf("\n");

        if (i != (u16RoutePointNum - 1)) {
            printf("    Average Speed To Reach Next Point: ");
            printf("%7.3f", f32SpeedToNextPoint[i]);
            printf(" meters per second");
            printf("\n");
        }
    }
}
/**********  End Function ***********************************************/
