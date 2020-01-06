#include <Wire.h>
#include <elapsedMillis.h>
#include "konfig.h"
#include "matrix.h"
#include "ukf.h"


/* Just example */
#define P_INIT      (1000.)
#define Rv_INIT     (0.001)
#define Rn_INIT     (0.001)


bool Main_bUpdateNonlinearX(Matrix &X_Next, Matrix &X, Matrix &U);
bool Main_bUpdateNonlinearY(Matrix &Y, Matrix &X, Matrix &U);

elapsedMillis timerLed, timerUKF;
uint64_t u64compuTime;

Matrix X(SS_X_LEN, 1);
Matrix Y(SS_Z_LEN, 1);
Matrix U(SS_U_LEN, 1);
UKF UKF_IMU(X, Main_bUpdateNonlinearX, Main_bUpdateNonlinearY, P_INIT, Rv_INIT, Rn_INIT);

char bufferTxSer[100];


void setup() {
    /* serial to display data */
    Serial.begin(115200);
    while(!Serial) {}
    
    X.vIsiNol();
    UKF_IMU.vReset(X, P_INIT, Rv_INIT, Rn_INIT);
}

void loop() {
    if (timerUKF > SS_DT_MILIS) {
        /* ================== Read the sensor data / simulate the system here ================== */
        /* ------------------ Read the sensor data / simulate the system here ------------------ */
        
        
        
        /* ============================= Update the Kalman Filter ============================== */
        u64compuTime = micros();
        if (!UKF_IMU.bUpdate(Y, U)) {
            X.vIsiNol();
            UKF_IMU.vReset(X, P_INIT, Rv_INIT, Rn_INIT);
            Serial.println("Whoop ");
        }
        u64compuTime = (micros() - u64compuTime);
        /* ----------------------------- Update the Kalman Filter ------------------------------ */
        
        
        
        /* =========================== Print to serial (for plotting) ========================== */
        #if (1)
            /* Print: Computation time, X_Est */
            snprintf(bufferTxSer, sizeof(bufferTxSer)-1, "%.3f %.3f ", ((float)u64compuTime)/1000., UKF_IMU.GetX()[0][0]);
            Serial.print(bufferTxSer);
        #endif
        Serial.print('\n');
        /* --------------------------- Print to serial (for plotting) -------------------------- */
        
        
        timerUKF = 0;
    }
}

bool Main_bUpdateNonlinearX(Matrix &X_Next, Matrix &X, Matrix &U)
{
    /* Insert the nonlinear update transformation here
     *          x(k+1) = f[x(k), u(k)]
     */
    
    return true;
}

bool Main_bUpdateNonlinearY(Matrix &Y, Matrix &X, Matrix &U)
{
    /* Insert the nonlinear measurement transformation here
     *          y(k)   = h[x(k), u(k)]
     */
    
    return true;
}



