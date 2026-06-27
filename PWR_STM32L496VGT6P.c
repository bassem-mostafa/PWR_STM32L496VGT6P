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

typedef struct PWR_STM32L496VGT6P_InstanceContext
{
    PWR_STM32L496VGT6P_Mode_t Mode;
} PWR_STM32L496VGT6P_InstanceContext_t;

typedef struct PWR_STM32L496VGT6P_Context
{
    PWR_STM32L496VGT6P_InstanceContext_t Context[ PWR_STM32L496VGT6P_Count ];
} PWR_STM32L496VGT6P_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Context_Initialize( void );
static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Context_Cycle( void );
static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Context_DeInitialize( void );

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_Initialize( PWR_STM32L496VGT6P_t PWRx );
static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_Cycle( PWR_STM32L496VGT6P_t PWRx );
static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_DeInitialize( PWR_STM32L496VGT6P_t PWRx );

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_SetMode( PWR_STM32L496VGT6P_t PWRx, PWR_STM32L496VGT6P_Mode_t Mode );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static PWR_STM32L496VGT6P_Context_t PWR_STM32L496VGT6P_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Context_Initialize( void )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( PWR_STM32L496VGT6P_Context );
    }
    while ( 0 );

    return Status;
}

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Context_Cycle( void )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( PWR_STM32L496VGT6P_Context );
    }
    while ( 0 );

    return Status;
}

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Context_DeInitialize( void )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( PWR_STM32L496VGT6P_Context );
    }
    while ( 0 );

    return Status;
}

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_Initialize( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );

        PWR_STM32L496VGT6P_InstanceContext_t * Context = &PWR_STM32L496VGT6P_Context.Context[ PWRx ];

        Context->Mode = PWR_STM32L496VGT6P_Mode_Run;

        // FIXME Review the following
        // HAL_PWREx_EnableBORPVD_ULP();
        __HAL_FLASH_SLEEP_POWERDOWN_ENABLE( );
        // __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);

        // TODO: Disable peripherals clock before enter sleep mode (IF POSSIBLE)
        __HAL_RCC_FLASH_CLK_SLEEP_DISABLE( );
        __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE( );
        __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE( );
        __HAL_RCC_PWR_CLK_SLEEP_DISABLE( );
        __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE( );

        HAL_DBGMCU_DisableDBGSleepMode( );
        HAL_DBGMCU_DisableDBGStopMode( );
        HAL_DBGMCU_DisableDBGStandbyMode( );

        KERNEL_Status_t KERNEL_Status = KERNEL_Status_Success;
        KERNEL_ResetReason_t KERNEL_ResetReason = KERNEL_ResetReason_Cleared;
        if ( ( KERNEL_Status = KERNEL_GetResetReason( PLATFORM_DEFAULT_KERNEL, &KERNEL_ResetReason ) ) != KERNEL_Status_Success )
        {
            // FIXME Couldn't get reset reason !
        }

        // TODO On Power-up Handling
        // TODO Notify KERNEL of exiting power mode
        // TODO Restore Modules Contexts/Configurations
    }
    while ( 0 );

    return Status;
}

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_Cycle( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );

        // TODO Determine these operation location, possible location to be into the PORT itself
        // TODO Retrieve Hardware Status

        UTIL_UNUSED( PWR_STM32L496VGT6P_Mode_Shutdown );

        // FIXME Check USB if active
        //    if(__HAL_RCC_USB_IS_CLK_ENABLED())
        //    {
        //      UTIL_UNUSED(PWR_STM32L496VGT6P_Mode_Sleep);
        //    }

        // FIXME Check ADC if active
        if ( __HAL_RCC_ADC_IS_CLK_ENABLED( ) )
        {
            UTIL_UNUSED( PWR_STM32L496VGT6P_Mode_LPSleep );
        }

        // FIXME Check LPTIM2 if active
        if ( __HAL_RCC_LPTIM2_IS_CLK_ENABLED( ) )
        {
            UTIL_UNUSED( PWR_STM32L496VGT6P_Mode_Stop2 );
        }

        // FIXME Check IO if need to be active (MUST be retained)
        if ( GPIO_Null )
        {
            UTIL_UNUSED( PWR_STM32L496VGT6P_Mode_Stop2 );
        }

        // FIXME Check Kernel performance configuration (Selected Clocks, ...etc)
        if ( KERNEL_Status_Busy )
        {
            UTIL_UNUSED( PWR_STM32L496VGT6P_Mode_Sleep );
        }

        // TODO Save Modules Contexts
        // TODO Enter Lowest ALLOWED power mode
        // TODO On Wake-up Handling
        // TODO Restore Modules Contexts
    }
    while ( 0 );

    return Status;
}

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_DeInitialize( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );
    }
    while ( 0 );

    return Status;
}

static PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Instance_SetMode( PWR_STM32L496VGT6P_t PWRx, PWR_STM32L496VGT6P_Mode_t Mode )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d, Mode=%d )", __FUNCTION__, PWRx, Mode );

        switch ( Mode )
        {
            case PWR_STM32L496VGT6P_Mode_Run:
                HAL_PWREx_DisableLowPowerRunMode( );
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
                break;

            case PWR_STM32L496VGT6P_Mode_Shutdown:
                HAL_PWREx_EnterSHUTDOWNMode( );
                break;

            default:
                Status = PWR_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Initialize( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;

    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );

        if ( ( Status = PWR_STM32L496VGT6P_Context_Initialize( ) ) != PWR_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = PWR_STM32L496VGT6P_Instance_Initialize( PWRx ) ) != PWR_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

PWR_STM32L496VGT6P_Status_t PWR_STM32L496VGT6P_Cycle( PWR_STM32L496VGT6P_t PWRx )
{
    PWR_STM32L496VGT6P_Status_t Status = PWR_STM32L496VGT6P_Status_Success;
    do
    {
        PWR_Trace( "%s( PWRx=%d )", __FUNCTION__, PWRx );

        if ( ( Status = PWR_STM32L496VGT6P_Context_Cycle( ) ) != PWR_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = PWR_STM32L496VGT6P_Instance_Cycle( PWRx ) ) != PWR_STM32L496VGT6P_Status_Success )
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

        if ( ( Status = PWR_STM32L496VGT6P_Instance_DeInitialize( PWRx ) ) != PWR_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = PWR_STM32L496VGT6P_Context_DeInitialize( ) ) != PWR_STM32L496VGT6P_Status_Success )
        {
            break;
        }
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

        Status = PWR_STM32L496VGT6P_Instance_SetMode( PWRx, Mode );
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
