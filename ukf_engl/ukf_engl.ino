/*************************************************************************************************************
 *  Template project for Discrete Unscented Kalman Filter library
 * 
 * See https://github.com/pronenewbits for more!
 ************************************************************************************************************/
#include <Wire.h>
#include <elapsedMillis.h>
#include "konfig.h"
#include "matrix.h"
#include "ukf.h"


/* ============================================ UKF Variables/function declaration ============================================ */
/* Just example; in konfig.h: 
 *  SS_X_LEN = 2
 *  SS_Z_LEN = 1
 *  SS_U_LEN = 1 
 */
/* UKF initialization constant -------------------------------------------------------------------------------------- */
#define P_INIT      (10.)
#define Rv_INIT     (1e-6)
#define Rn_INIT     (0.0015)
/* P(k=0) variable -------------------------------------------------------------------------------------------------- */
float_prec UKF_PINIT_data[SS_X_LEN*SS_X_LEN] = {P_INIT, 0,
                                                0,      P_INIT};
Matrix UKF_PINIT(SS_X_LEN, SS_X_LEN, UKF_PINIT_data);
/* Rv constant ------------------------------------------------------------------------------------------------------ */
float_prec UKF_RVINIT_data[SS_X_LEN*SS_X_LEN] = {Rv_INIT, 0,
                                                 0,      Rv_INIT};
Matrix UKF_RvINIT(SS_X_LEN, SS_X_LEN, UKF_RVINIT_data);
/* Rn constant ------------------------------------------------------------------------------------------------------ */
float_prec UKF_RNINIT_data[SS_Z_LEN*SS_Z_LEN] = {Rn_INIT};
Matrix UKF_RnINIT(SS_Z_LEN, SS_Z_LEN, UKF_RNINIT_data);
/* Nonlinear & linearization function ------------------------------------------------------------------------------- */
bool Main_bUpdateNonlinearX(Matrix& X_Next, const Matrix& X, const Matrix& U);
bool Main_bUpdateNonlinearY(Matrix& Y, const Matrix& X, const Matrix& U);
/* UKF variables ---------------------------------------------------------------------------------------------------- */
Matrix X(SS_X_LEN, 1);
Matrix Y(SS_Z_LEN, 1);
Matrix U(SS_U_LEN, 1);
/* UKF system declaration ------------------------------------------------------------------------------------------- */
UKF UKF_IMU(X, UKF_PINIT, UKF_RvINIT, UKF_RnINIT, Main_bUpdateNonlinearX, Main_bUpdateNonlinearY);



/* ========================================= Auxiliary variables/function declaration ========================================= */
elapsedMillis timerLed, timerUKF;
uint64_t u64compuTime;
char bufferTxSer[100];



void setup() {
    /* serial to display data */
    Serial.begin(115200);
    while(!Serial) {}
    
    X.vSetToZero();
    UKF_IMU.vReset(X, UKF_PINIT, UKF_RvINIT, UKF_RnINIT);
}


void loop() {
    if (timerUKF >= SS_DT_MILIS) {
        timerUKF = 0;
        
        
        /* ================== Read the sensor data / simulate the system here ================== */
        /* ... */
        /* ------------------ Read the sensor data / simulate the system here ------------------ */
        
        
        /* ============================= Update the Kalman Filter ============================== */
        u64compuTime = micros();
        if (!UKF_IMU.bUpdate(Y, U)) {
            X.vSetToZero();
            UKF_IMU.vReset(X, UKF_PINIT, UKF_RvINIT, UKF_RnINIT);
            Serial.println("Whoop ");
        }
        u64compuTime = (micros() - u64compuTime);
        /* ----------------------------- Update the Kalman Filter ------------------------------ */
        
        
        /* =========================== Print to serial (for plotting) ========================== */
        #if (1)
            /* Print: Computation time, X_Est[0] */
            snprintf(bufferTxSer, sizeof(bufferTxSer)-1, "%.3f %.3f ", ((float)u64compuTime)/1000., UKF_IMU.GetX()[0][0]);
            Serial.print(bufferTxSer);
        #endif
        Serial.print('\n');
        /* --------------------------- Print to serial (for plotting) -------------------------- */
    }
}


bool Main_bUpdateNonlinearX(Matrix& X_Next, const Matrix& X, const Matrix& U)
{
    /* Insert the nonlinear update transformation here
     *          x(k+1) = f[x(k), u(k)]
     */
    
    return true;
}

bool Main_bUpdateNonlinearY(Matrix& Y, const Matrix& X, const Matrix& U)
{
    /* Insert the nonlinear measurement transformation here
     *          y(k)   = h[x(k), u(k)]
     */
    
    return true;
}





void SPEW_THE_ERROR(char const * str)
{
    #if (SYSTEM_IMPLEMENTATION == SYSTEM_IMPLEMENTATION_PC)
        cout << (str) << endl;
    #elif (SYSTEM_IMPLEMENTATION == SYSTEM_IMPLEMENTATION_EMBEDDED_ARDUINO)
        Serial.println(str);
    #else
        /* Silent function */
    #endif
    while(1);
}
