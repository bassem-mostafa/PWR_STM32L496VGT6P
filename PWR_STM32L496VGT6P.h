// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifndef PWR_STM32L496VGT6P_H_
    #define PWR_STM32L496VGT6P_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    /**
     *  @brief PWR STM32L496VGT6P Operation Status
     *
     *  @enum PWR_STM32L496VGT6P_Status_t
     */
    typedef enum PWR_STM32L496VGT6P_Status
    {
        PWR_STM32L496VGT6P_Status_Success = 0,     ///< Success
        PWR_STM32L496VGT6P_Status_ArgumentInvalid, ///< Argument Invalid
        PWR_STM32L496VGT6P_Status_NotSupported,    ///< Not Supported
        PWR_STM32L496VGT6P_Status_Error,           ///< General Error
        PWR_STM32L496VGT6P_Status_Busy,            ///< Busy
        PWR_STM32L496VGT6P_Status_Timeout,         ///< Timeout
    } PWR_STM32L496VGT6P_Status_t;

    /**
     *  @brief PWR STM32L496VGT6P
     *
     *  @enum PWR_STM32L496VGT6P_t
     */
    typedef enum PWR_STM32L496VGT6P
    {
        PWR_STM32L496VGT6P_1 = 0, ///< PWR 1
        PWR_STM32L496VGT6P_Count, ///< Count
    } PWR_STM32L496VGT6P_t;

    /**
     *  @brief PWR STM32L496VGT6P Mode
     *
     *  @enum PWR_STM32L496VGT6P_Mode_t
     */
    typedef enum PWR_STM32L496VGT6P_Mode
    {
        PWR_STM32L496VGT6P_Mode_Run = 0,  ///< Run
        PWR_STM32L496VGT6P_Mode_LPRun,    ///< Low Power Run
        PWR_STM32L496VGT6P_Mode_Sleep,    ///< Sleep
        PWR_STM32L496VGT6P_Mode_LPSleep,  ///< Low Power Sleep
        PWR_STM32L496VGT6P_Mode_Stop0,    ///< Stop 0
        PWR_STM32L496VGT6P_Mode_Stop1,    ///< Stop 1
        PWR_STM32L496VGT6P_Mode_Stop2,    ///< Stop 2
        PWR_STM32L496VGT6P_Mode_Standby,  ///< Standby
        PWR_STM32L496VGT6P_Mode_Shutdown, ///< Shutdown
    } PWR_STM32L496VGT6P_Mode_t;

    /**
     *  @brief PWR STM32L496VGT6P Instance Context
     *
     *  @struct PWR_STM32L496VGT6P_Instance_Context_t
     */
    typedef struct PWR_STM32L496VGT6P_Instance_Context PWR_STM32L496VGT6P_Instance_Context_t;

    /**
     *  @brief PWR STM32L496VGT6P Instance
     *
     *  @struct PWR_STM32L496VGT6P_Instance_t
     */
    typedef struct PWR_STM32L496VGT6P_Instance
    {
        PWR_STM32L496VGT6P_t PWRx;

        // Managed Internally
        PWR_STM32L496VGT6P_Instance_Context_t * Context;
    } PWR_STM32L496VGT6P_Instance_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Initialize( PWR_STM32L496VGT6P_Instance_t * Instance );
    PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Cycle( PWR_STM32L496VGT6P_Instance_t * Instance );
    PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_DeInitialize( PWR_STM32L496VGT6P_Instance_t * Instance );

    PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_SetMode( PWR_STM32L496VGT6P_Instance_t * Instance, PWR_STM32L496VGT6P_Mode_t Mode );

    // TODO Add More APIs

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* PWR_STM32L496VGT6P_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
