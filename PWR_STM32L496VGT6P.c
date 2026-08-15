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

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef STM32L496xx

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include "../../PWR_Internal.h"
    #include "PWR_STM32L496VGT6P.h"

    #include "stm32l4xx.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct PWR_STM32L496VGT6P_Instance
{
    PWR_STM32L496VGT6P_Mode_t Mode;
} PWR_STM32L496VGT6P_Instance_t;

typedef struct PWR_STM32L496VGT6P_Context
{
    PWR_STM32L496VGT6P_Instance_t Instance[ PWR_STM32L496VGT6P_Count ];
} PWR_STM32L496VGT6P_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static PWR_STM32L496VGT6P_Context_t PWR_STM32L496VGT6P_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Initialize( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );

        PWR_STM32L496VGT6P_Instance_t * Instance = &PWR_STM32L496VGT6P_Context.Instance[ PWRx ];

        // FIXME Review the following
        // HAL_PWREx_EnableBORPVD_ULP();
        __HAL_FLASH_SLEEP_POWERDOWN_ENABLE( );
        __HAL_RCC_WAKEUPSTOP_CLK_CONFIG( RCC_STOP_WAKEUPCLOCK_MSI );

        // Disable peripherals clock before enter sleep mode (IF POSSIBLE)
        __HAL_RCC_FLASH_CLK_SLEEP_DISABLE( );
        __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE( );
        __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE( );
        __HAL_RCC_PWR_CLK_SLEEP_DISABLE( );
        __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE( );

        HAL_DBGMCU_DisableDBGSleepMode( );
        HAL_DBGMCU_DisableDBGStopMode( );
        HAL_DBGMCU_DisableDBGStandbyMode( );

        // TODO The following block should exist in every module that has a context the must persist after shutdown mode exits
        // TODO By which every module could determine the reset reason either it was from a shutdown or else
        // TODO In case of shutdown reset, every module should restore its own context (if any)
        //
        //     KERNEL_Status_t KERNEL_Status = KERNEL_Status_Success;
        //     KERNEL_ResetReason_t KERNEL_ResetReason = KERNEL_ResetReason_Cleared;
        //     if ( ( KERNEL_Status = KERNEL_GetResetReason( PLATFORM_DEFAULT_KERNEL, &KERNEL_ResetReason ) ) != KERNEL_Status_Success )
        //     {
        //         // IF couldn't get reset reason, consider it as power reset
        //         PWR_Warning( "KERNEL_GetResetReason Failed, Status %d", KERNEL_Status );
        //         KERNEL_ResetReason = KERNEL_ResetReason_Power;
        //     }

        Instance->Mode = PWR_STM32L496VGT6P_Mode_Run;
    }
    while ( 0 );

    return Status;
}

PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Cycle( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;
    HAL_StatusTypeDef HAL_Status = HAL_OK;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );

        PWR_STM32L496VGT6P_Instance_t * Instance = &PWR_STM32L496VGT6P_Context.Instance[ PWRx ];

        // TODO Verify the following HW lowest power mode checks
        // TODO MUST be in descending order
        // - Shutdown (Target)
        // - Standby
        // - Stop-2
        // - Stop-1/0
        // - Low-Power Sleep
        // - Low-Power Run
        // - Sleep
        // - Run (Default)
        PWR_STM32L496VGT6P_Mode_t Mode_Lowest = PWR_STM32L496VGT6P_Mode_Shutdown;

        if ( __HAL_RCC_LPTIM1_IS_CLK_ENABLED( ) )
        {
            // TODO Stop-2 is the lowest possible if
            // - Low-Power timer-1 is active
            Mode_Lowest = PWR_STM32L496VGT6P_Mode_Stop2;
        }

        if ( __HAL_RCC_LPTIM2_IS_CLK_ENABLED( ) )
        {
            // TODO Stop-1 is the lowest possible if
            // - Low-Power timer-2 is active
            Mode_Lowest = PWR_STM32L496VGT6P_Mode_Stop1;
        }

        if ( __HAL_RCC_ADC_IS_CLK_ENABLED( ) )
        {
            // TODO Low-Power Sleep is the lowest possible if
            // - ADC is active
            Mode_Lowest = PWR_STM32L496VGT6P_Mode_LPSleep;
        }

        if ( __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED( ) || __HAL_RCC_USB_OTG_FS_IS_CLK_SLEEP_ENABLED( ) )
        {
            // TODO Sleep is the lowest possible if
            // - USB is active
            Mode_Lowest = PWR_STM32L496VGT6P_Mode_Sleep;
        }

        PWR_Debug( "Power mode %d (selected), %d (lowest)", Instance->Mode, Mode_Lowest );

        if ( Mode_Lowest > Instance->Mode )
        {
            PWR_Warning( "Power mode %d could be set to %d", Instance->Mode, Mode_Lowest );
            // FIXME Power mode could be set to a lower mode
        }
        else
        {
            PWR_Error( "Power mode %d is below lowest %d ", Instance->Mode, Mode_Lowest );
            PWR_Warning( "Power mode fall-back from %d to %d", Instance->Mode, Mode_Lowest );
            Instance->Mode = Mode_Lowest;
        }

        switch ( Instance->Mode )
        {
            case PWR_STM32L496VGT6P_Mode_Run:
                if ( ( HAL_Status = HAL_PWREx_DisableLowPowerRunMode( ) ) != HAL_OK )
                {
                    // TODO Is there something could be done ?
                    Status = PWR_STM32L496VGT6P_Status_Error;
                    break;
                }
                break;

            case PWR_STM32L496VGT6P_Mode_LPRun:
                HAL_PWREx_EnableLowPowerRunMode( );
                break;

            case PWR_STM32L496VGT6P_Mode_Sleep:
                HAL_PWR_EnterSLEEPMode( PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI );
                break;

            case PWR_STM32L496VGT6P_Mode_LPSleep:
                HAL_PWR_EnterSLEEPMode( PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI );
                break;

            case PWR_STM32L496VGT6P_Mode_Stop0:
                HAL_PWREx_EnterSTOP0Mode( PWR_STOPENTRY_WFI );
                break;

            case PWR_STM32L496VGT6P_Mode_Stop1:
                HAL_PWREx_EnterSTOP1Mode( PWR_STOPENTRY_WFI );
                break;

            case PWR_STM32L496VGT6P_Mode_Stop2:
                HAL_PWREx_EnterSTOP2Mode( PWR_STOPENTRY_WFI );
                break;

            case PWR_STM32L496VGT6P_Mode_Standby:
                HAL_PWR_EnterSTANDBYMode( );
                // code unreachable
                // previous call is followed by a reset on wake-up
                break;

            case PWR_STM32L496VGT6P_Mode_Shutdown:
                HAL_PWREx_EnterSHUTDOWNMode( );
                // code unreachable
                // previous call is followed by a reset on wake-up
                break;

            default:
                Status = PWR_STM32L496VGT6P_Status_NotSupported;
                break;
        }
        if ( Status != PWR_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_DeInitialize( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );
    }
    while ( 0 );

    return Status;
}

PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_SetMode( PWR_STM32L496VGT6P_t PWRx, PWR_STM32L496VGT6P_Mode_t Mode )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d, Mode=%d )", __FUNCTION__, PWRx, Mode );

        PWR_STM32L496VGT6P_Instance_t * Instance = &PWR_STM32L496VGT6P_Context.Instance[ PWRx ];

        Instance->Mode = Mode;
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* STM32L496xx */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
