/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "Util/string_operator.h"
#include "Util/dictionary.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// test datalog parameters
float kp       = 0.1;
float ki       = 0.2;
float kd       = 0.3;
float setpoint = 0.4;

// the variables can be logged
dictionary_t datalog_avialable_symbol_dict;
char *datalog_target_symbol_name[DICT_MAX_SIZE];
int datalog_target_symbol_size = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

// datalog dictionary
void Init_Datalog_Param_Dict(void);

// tasks
void Init_Task_Scheduler_Tasks(void);

void Command_Frames_Handler(void);
void test_work(void);
void Datalog_Frames_Handler(void);

// test functions
void Init_Command_Send_Frame(void);
void Init_Datalog_Send_Frame(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MPU Configuration--------------------------------------------------------*/
    MPU_Config();

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART3_UART_Init();
    MX_USART1_UART_Init();
    MX_DAC1_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    /* USER CODE BEGIN 2 */
    Start_Command_Frame_Receive(); // command uart receive dma frames
    Start_Task_Scheduler_Timer();  // start the tasks scheduler timer

    HAL_TIM_Encoder_Start(&ENCODER_TIMER, TIM_CHANNEL_ALL);

    Init_Datalog_Param_Dict();   // init the datalog parameters dictionary
    Init_Command_Send_Frame();   // init the command send frame
    Init_Datalog_Send_Frame();   // init the datalog send frame
    Init_Task_Scheduler_Tasks(); // init the tasks scheduler tasks
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        task_scheduler_run();
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Supply configuration update enable
     */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState            = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM            = 4;
    RCC_OscInitStruct.PLL.PLLN            = 60;
    RCC_OscInitStruct.PLL.PLLP            = 2;
    RCC_OscInitStruct.PLL.PLLQ            = 2;
    RCC_OscInitStruct.PLL.PLLR            = 2;
    RCC_OscInitStruct.PLL.PLLRGE          = RCC_PLL1VCIRANGE_3;
    RCC_OscInitStruct.PLL.PLLVCOSEL       = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN        = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

void Init_Datalog_Param_Dict(void)
{
    init_dictionary(&datalog_avialable_symbol_dict);
    add_key_value_pair(&datalog_avialable_symbol_dict, "kp", &kp);
    add_key_value_pair(&datalog_avialable_symbol_dict, "ki", &ki);
    add_key_value_pair(&datalog_avialable_symbol_dict, "kd", &kd);
    add_key_value_pair(&datalog_avialable_symbol_dict, "setpoint", &setpoint);
}

void Init_Task_Scheduler_Tasks(void)
{
    // send/receive command frames with 10Hz frequency
    task_scheduler_add_task(Command_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(10), 1);
    // log data with 2kHz frequency
    task_scheduler_add_task(Datalog_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(2000), 0);

    task_scheduler_add_task(test_work, GET_TASK_SCHEDULER_IDEAL_TICKS(5), 1);
}

void Command_Frames_Handler(void)
{
    // protocol handler
    Parse_Command_Frame();

    // send available log data name list
    if (command_receive_frame.cmd == DATALOG_CHECK_AVAILABLE_DATA_CMD) {
        command_send_frame.cmd = DATALOG_SEND_AVAILABLE_DATA_CMD;
        get_all_keys(&datalog_avialable_symbol_dict, command_param_name_string_array); // get all keys in the dictionary
        name_string_to_uint8_array(command_param_name_string_array,
                                   command_param_data_array,
                                   strlen(command_param_name_string_array));
        set_frame_data(&command_send_frame, command_param_data_array, strlen(command_param_name_string_array));
        Send_Command_Frame_Data(&command_send_frame);
        memset(command_param_name_string_array, 0, sizeof(command_param_name_string_array));

        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    }

    if (command_receive_frame.cmd == DATALOG_SET_LOG_DATA_CMD) {
        // set log data
        static char datalog_name_string_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
        uint8_array_to_name_string(command_receive_frame.data,
                                   datalog_name_string_array,
                                   command_receive_frame.len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
        seperate_string(datalog_name_string_array, datalog_target_symbol_name, &datalog_target_symbol_size);
        join_string(datalog_target_symbol_name, command_param_name_string_array, datalog_target_symbol_size);

        command_send_frame.cmd = DATALOG_ECHO_LOG_DATA_CMD;
        name_string_to_uint8_array(command_param_name_string_array,
                                   command_param_data_array,
                                   strlen(command_param_name_string_array));
        set_frame_data(&command_send_frame, command_param_data_array, strlen(command_param_name_string_array));
        Send_Command_Frame_Data(&command_send_frame);
        memset(command_param_name_string_array, 0, sizeof(command_param_name_string_array));

        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    }

    if (command_receive_frame.cmd == DATALOG_START_LOG_CMD) {
        // send back start log command
        command_send_frame.cmd = DATALOG_ECHO_LOG_START_CMD;
        command_send_frame.len = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
        Send_Command_Frame_Data(&command_send_frame);
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        // start send log data
        task_scheduler_enable_task(1); // enable datalog task(id = 1)
    }

    if (command_receive_frame.cmd == DATALOG_STOP_LOG_CMD) {
        task_scheduler_disable_task(1); // disable datalog task(id = 1)
    }
}

void Datalog_Frames_Handler(void)
{
    datalog_send_frame.cmd = DATALOG_RUNNING_CMD;
    for (uint8_t i = 0; i < datalog_target_symbol_size; i++) {
        datalog_param_float_array[i] = *(get_value(&datalog_avialable_symbol_dict, datalog_target_symbol_name[i]));
    }
    float_array_to_uint8_array(datalog_param_float_array, datalog_param_data_array, datalog_target_symbol_size);
    set_frame_data(&datalog_send_frame, datalog_param_data_array, 4 * datalog_target_symbol_size);
    Send_Datalog_Frame_Data(&datalog_send_frame);
}

void test_work(void)
{
    printf("longint counter: %ld\n", __HAL_TIM_GET_COUNTER(&ENCODER_TIMER));
    kp += 0.1;
    ki += 0.2;
    kd += 0.3;
    setpoint += 0.4;
    // HAL_UART_Transmit_DMA(&UART_DATALOG, (uint8_t *)"hello world\n", strlen("hello world\n"));
}

void Init_Command_Send_Frame(void)
{
    command_send_frame.cmd      = SEND_VEL_PID_CMD;
    command_send_frame.header   = PROTOCOL_FRAME_HEADER;
    command_send_frame.motor_id = MOTOR_ID1;
    command_send_frame.len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
    command_send_frame.data     = (uint8_t *)command_param_data_array;
}

void Init_Datalog_Send_Frame(void)
{
    datalog_send_frame.cmd      = NULL_CMD;
    datalog_send_frame.header   = PROTOCOL_FRAME_HEADER;
    datalog_send_frame.motor_id = MOTOR_ID1;
    datalog_send_frame.len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
    datalog_send_frame.data     = (uint8_t *)datalog_param_data_array;
}
/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct = {0};

    /* Disables the MPU */
    HAL_MPU_Disable();

    /** Initializes and configures the Region and the memory to be protected
     */
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress      = 0x0;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.SubRegionDisable = 0x87;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
