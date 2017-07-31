#include <math.h>
#include "../def/type.h"
#include "../def/global_data.h"


/*======================================================================*/
void convertSphericalToCartesian(void)
/*======================================================================*/
{
    U16 i;

    // convert spherical coordinates to cartesian coordinates
    //     long -> x: alt * cos(lat) * sin(long)
    //     lat  -> y: alt * sin(lat)
    //     alt  -> z: alt * cos(lat) * cos(long)
    for (i = 0; i < u16RoutePointNum; i++) {
        F32 longSpherical = LongitudeDataStructure.f32LongitudeInputs[i];
        F32 latSpherical  = LatitudeDataStructure.f32LatitudeInputs[i];
        F32 altSpherical  = AltitudeDataStructure.f32AltitudeInputs[i];
        if (altSpherical != 0) {
            LongitudeDataStructure.f32LongitudeX[i] = altSpherical * cos(latSpherical) * sin(longSpherical);
            LatitudeDataStructure.f32LatitudeY[i] = altSpherical * sin(latSpherical);
            AltitudeDataStructure.f32AltitudeZ[i] = altSpherical * cos(latSpherical) * cos(longSpherical);
        }
        else {
            LongitudeDataStructure.f32LongitudeX[i] = 0;
            LatitudeDataStructure.f32LatitudeY[i]   = 0;
            AltitudeDataStructure.f32AltitudeZ[i]   = 0;
        }
    }
}
/**********  End Function ***********************************************/


/*======================================================================*/
void calculateDistanceBetweenPoints(void)
/*======================================================================*/
{
    U16 i;

    // extend Pythagorean Theorem to three dimensions using
    // the Cartesian points:
    //   distance = sqrt( (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
    for (i = 1; i < u16RoutePointNum; i++) {
        F32 xDiff = (LongitudeDataStructure.f32LongitudeX[i] - LongitudeDataStructure.f32LongitudeX[i-1]);
        F32 yDiff = (LatitudeDataStructure.f32LatitudeY[i] - LatitudeDataStructure.f32LatitudeY[i-1]);
        F32 zDiff = (AltitudeDataStructure.f32AltitudeZ[i] - AltitudeDataStructure.f32AltitudeZ[i-1]);

        f32DistanceTraveled[i] = sqrt( (xDiff*xDiff) + (yDiff*yDiff) + (zDiff*zDiff) );
    }
}
/**********  End Function ***********************************************/


/*======================================================================*/
void calculateSpeedBetweenPoints(void)
/*======================================================================*/
{
    U16 i;
    F32 f32TimeOffset = 0;

    // calculate speed needed to reach next point in specified time
    for (i = 0; i < u16RoutePointNum - 1; i++) {
        F32 f32TimeBetweenPoints = TimeDataStructure.f32TimeInputs[i + 1] - f32TimeOffset;

        if (f32TimeBetweenPoints != 0) {
            f32SpeedToNextPoint[i] = f32DistanceTraveled[i + 1] / f32TimeBetweenPoints;
        }
        // shouldn't ever be the case, but better safe than sorry
        else {
            f32SpeedToNextPoint[i] = 0;
        }

        f32TimeOffset += TimeDataStructure.f32TimeInputs[i + 1];
    }
}
/**********  End Function ***********************************************/
