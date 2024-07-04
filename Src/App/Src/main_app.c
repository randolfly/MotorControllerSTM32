#include "main_app.h"

// the variables can be logged
dictionary_t datalog_available_symbol_dict;
char *datalog_target_symbol_name[DICT_MAX_SIZE];
int datalog_target_symbol_size = 0;

// motor instance
motor_t motor1;

/* =============== MAIN WORK ====================*/
static void MAIN_WORK(void);

/* =============== TASK SCHEDULER ====================*/
/**
 * @brief init the main application tasks
 */
static void Init_Task_Scheduler_Tasks(void);

/* =============== PROTOCOL ====================*/

/**
 * @brief process the command frames
 */
static void Command_Frames_Handler(void);

/**
 * @brief init the command frames to be sent
 */
static void Init_Command_Send_Frame(void);

/**
 * @brief collect and send the datalog frames
 */
static void Datalog_Frames_Handler(void);

/**
 * @brief Init the datalog parameters dictionary
 */
static void Init_Datalog_Param_Dict(void);

/**
 * @brief init the data log frames to be sent
 */
static void Init_Datalog_Send_Frame(void);

void Init_App_Functions()
{
    // init bsp layer
    Init_Task_Scheduler();
    Init_Command_Protocol_Parser();

    // init app layer
    Init_Command_Send_Frame();     // init the command send frame
    Init_Datalog_Send_Frame();     // init the datalog send frame
    Start_Command_Frame_Receive(); // command uart receive dma frames
    init_motor(&motor1);           // init the motor1

    // log data params(place after all params are initialized)
    Init_Datalog_Param_Dict(); // init the datalog parameters dictionary

    // init timers and tasks
    Start_Task_Scheduler_Timer(); // start the tasks scheduler timer
    Start_Encoder_Timer();        // start the encoder timer
    Init_Task_Scheduler_Tasks();  // init the tasks scheduler tasks
}

void Run_App_Functions(void)
{
    task_scheduler_run();
}

/* =============== MAIN WORK ====================*/

static void MAIN_WORK(void)
{
    // update motor1 encoder info
    encoder_update(motor1.encoder, __HAL_TIM_GET_COUNTER(&ENCODER_TIMER));
}

/* =============== TASK SCHEDULER ====================*/

static void Init_Task_Scheduler_Tasks(void)
{
    // send/receive command frames with 10Hz frequency
    task_scheduler_add_task(Command_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(10), 1);
    // log data with 2kHz frequency
    // task_scheduler_add_task(Datalog_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(2000), 0);
    task_scheduler_add_task(Datalog_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(1000), 0);

    task_scheduler_add_task(MAIN_WORK, GET_TASK_SCHEDULER_IDEAL_TICKS(5000), 1);
}

/* =============== PROTOCOL ====================*/

static void Init_Datalog_Param_Dict(void)
{
    init_dictionary(&datalog_available_symbol_dict);
    add_key_value_pair(&datalog_available_symbol_dict, "rotation_num", &(motor1.encoder->rotation_num), INT32_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "encoder_pos", &(motor1.encoder->position), DOUBLE_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "encoder_vel", &(motor1.encoder->velocity), DOUBLE_TYPE_RANDOLF);
}

static void Command_Frames_Handler(void)
{
    // protocol handler
    Parse_Command_Frame();

    // send available log data name list
    if (command_receive_frame.cmd == DATALOG_CHECK_AVAILABLE_DATA_CMD) {
        command_send_frame.cmd = DATALOG_SEND_AVAILABLE_DATA_CMD;
        get_all_keys(&datalog_available_symbol_dict, command_param_name_string_array); // get all keys in the dictionary
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

static void Datalog_Frames_Handler(void)
{
    datalog_send_frame.cmd = DATALOG_RUNNING_CMD;
    for (uint8_t i = 0; i < datalog_target_symbol_size; i++) {
        datalog_param_float_array[i] = (get_value(&datalog_available_symbol_dict, datalog_target_symbol_name[i]));
    }
    float_array_to_uint8_array(datalog_param_float_array, datalog_param_data_array, datalog_target_symbol_size);
    set_frame_data(&datalog_send_frame, datalog_param_data_array, 4 * datalog_target_symbol_size);
    Send_Datalog_Frame_Data(&datalog_send_frame);
}

static void Init_Command_Send_Frame(void)
{
    command_send_frame.cmd      = NULL_CMD;
    command_send_frame.header   = PROTOCOL_FRAME_HEADER;
    command_send_frame.motor_id = MOTOR_ID1;
    command_send_frame.len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
    command_send_frame.data     = (uint8_t *)command_param_data_array;
}

static void Init_Datalog_Send_Frame(void)
{
    datalog_send_frame.cmd      = NULL_CMD;
    datalog_send_frame.header   = PROTOCOL_FRAME_HEADER;
    datalog_send_frame.motor_id = MOTOR_ID1;
    datalog_send_frame.len      = PROTOCOL_FRAME_HEADER_SIZE + PROTOCOL_FRAME_CHECKSUM_SIZE + 0;
    datalog_send_frame.data     = (uint8_t *)datalog_param_data_array;
}