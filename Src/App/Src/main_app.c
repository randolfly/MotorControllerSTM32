#include "main_app.h"

// the variables can be logged
dictionary_t datalog_available_symbol_dict;
dictionary_t datalog_target_symbol_dict;

char *datalog_target_symbol_name[DICT_MAX_SIZE];
int datalog_target_symbol_size = 0;

// motor instance
motor_t motor1;

// state machine instance
motion_state_machine_t msm;

// task scheduler handles
int datalog_task_handle         = 1;
int main_logic_handle           = 2;
int motion_torque_loop_handle   = 3;
int motion_vel_loop_handle      = 4;
int motion_pos_loop_handle      = 5;
int motion_test_torquebs_handle = 6;

/* =============== MAIN WORK ====================*/
static void Main_Logic(void);

static void Motion_Torque_Loop(void);
static void Motion_Vel_Loop(void);
static void Motion_Pos_Loop(void);

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
    init_dac();
    enable_motor_electric_power(); // power on motor1(electrical switch)

    // init app layer
    Init_Command_Send_Frame();     // init the command send frame
    Init_Datalog_Send_Frame();     // init the datalog send frame
    Start_Command_Frame_Receive(); // command uart receive dma frames
    init_motor(&motor1);           // init the motor1
    init_motion_state_machine(&msm);
    init_model_excitation();

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

static void Main_Logic(void)
{
    // update motor1 encoder info
    encoder_update(motor1.encoder, __HAL_TIM_GET_COUNTER(&ENCODER_TIMER));
    // update motor1 state machine
    update_motion_state_machine(&msm);
}

static void Motion_Torque_Loop(void)
{
    // simple torque loop: just send the target torque to the motor
    static uint16_t torque_dac = 0;
    torque_dac                 = torque_permillage_to_dac(motor1.motor_param->target_torque);
    set_dac_value(DAC_A, torque_dac);
}

static void Motion_Vel_Loop(void)
{
}

static void Motion_Pos_Loop(void)
{
}

static void Motion_Test_TorqueBs(void)
{
    step_model_excitation();
    float model_excitation_output = 0;
    model_excitation_output       = get_model_excitation_output();
}

/* =============== TASK SCHEDULER ====================*/

static void Init_Task_Scheduler_Tasks(void)
{
    // send/receive command frames with 10Hz frequency
    task_scheduler_add_task(Command_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(10), 1);
    // log data with 2kHz frequency
    datalog_task_handle = task_scheduler_add_task(Datalog_Frames_Handler, GET_TASK_SCHEDULER_IDEAL_TICKS(1000), 0);

    main_logic_handle         = task_scheduler_add_task(Main_Logic, GET_TASK_SCHEDULER_IDEAL_TICKS(5000), 1);
    motion_torque_loop_handle = task_scheduler_add_task(Motion_Torque_Loop, GET_TASK_SCHEDULER_IDEAL_TICKS(5000), 0);
    motion_vel_loop_handle    = task_scheduler_add_task(Motion_Vel_Loop, GET_TASK_SCHEDULER_IDEAL_TICKS(4000), 0);
    motion_pos_loop_handle    = task_scheduler_add_task(Motion_Pos_Loop, GET_TASK_SCHEDULER_IDEAL_TICKS(1000), 0);

    // test functions
    motion_test_torquebs_handle = task_scheduler_add_task(Motion_Test_TorqueBs, GET_TASK_SCHEDULER_IDEAL_TICKS(1000), 0);
}

/* =============== PROTOCOL ====================*/

static void Init_Datalog_Param_Dict(void)
{
    init_dictionary(&datalog_available_symbol_dict);

    // encoder
    add_key_value_pair(&datalog_available_symbol_dict, "rotation_num", &(motor1.encoder->rotation_num), INT32_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "encoder_pos", &(motor1.encoder->position), DOUBLE_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "encoder_vel", &(motor1.encoder->velocity), DOUBLE_TYPE_RANDOLF);

    // motor param
    add_key_value_pair(&datalog_available_symbol_dict, "target_torque", &(motor1.motor_param->target_torque), FLOAT_TYPE_RANDOLF);

    // motor state machine
    add_key_value_pair(&datalog_available_symbol_dict, "msm_state", &(msm.state), UINT16_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_init_to_poweron", &(msm.event.init_to_poweron), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_idle_to_exit", &(msm.event.idle_to_exit), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_idle_to_pos", &(msm.event.idle_to_pos), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_idle_to_vel", &(msm.event.idle_to_vel), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_idle_to_torque", &(msm.event.idle_to_torque), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_pos_to_idle", &(msm.event.pos_to_idle), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_vel_to_idle", &(msm.event.vel_to_idle), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_torque_to_idle", &(msm.event.torque_to_idle), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_test_torquebs_to_idle", &(msm.event.test_torquebs_to_idle), UINT8_TYPE_RANDOLF);
    add_key_value_pair(&datalog_available_symbol_dict, "msm_idle_to_test_torquebs", &(msm.event.idle_to_test_torquebs), UINT8_TYPE_RANDOLF);
}

static void Command_Frames_Handler(void)
{
    // protocol handler
    Parse_Command_Frame();
    if (command_receive_frame.cmd == GET_SYMBOL_DATA_CMD) {
        // locate the target symbol name
        static char get_target_symbol_name[PROTOCOL_FRAME_MAX_SIZE] = {0};
        uint8_array_to_name_string(command_receive_frame.data,
                                   get_target_symbol_name,
                                   command_receive_frame.len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
        static float get_target_symbol_value = 0;
        get_target_symbol_value              = get_dictionary_value(&datalog_available_symbol_dict, get_target_symbol_name);

        // send back the symbol data
        command_send_frame.cmd = GET_ECHO_SYMBOL_DATA_CMD;
        float_to_uint8_array(get_target_symbol_value, command_param_data_array);
        set_frame_data(&command_send_frame, command_param_data_array, 4);
        Send_Command_Frame_Data(&command_send_frame);
        memset(get_target_symbol_name, 0, sizeof(get_target_symbol_name));
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);

    } else if (command_receive_frame.cmd == SET_SYMBOL_DATA_CMD) {
        // locate the target symbol name
        static char set_target_symbol_name[PROTOCOL_FRAME_MAX_SIZE] = {0};
        uint8_array_to_name_string(command_receive_frame.data,
                                   set_target_symbol_name,
                                   command_receive_frame.len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE - 4);
        static float set_target_symbol_value = 0;
        set_target_symbol_value              = uint8_array_to_float(command_receive_frame.data + (command_receive_frame.len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE - 4));
        set_dictionary_value(&datalog_available_symbol_dict, set_target_symbol_name, set_target_symbol_value);

        // send back the symbol data
        command_send_frame.cmd = SET_ECHO_SYMBOL_DATA_CMD;
        name_string_to_uint8_array(set_target_symbol_name,
                                   command_param_data_array,
                                   strlen(set_target_symbol_name));
        float_to_uint8_array(set_target_symbol_value, command_param_data_array + strlen(set_target_symbol_name));
        set_frame_data(&command_send_frame, command_param_data_array, 4 + strlen(set_target_symbol_name));
        Send_Command_Frame_Data(&command_send_frame);

        memset(set_target_symbol_name, 0, sizeof(set_target_symbol_name));
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    }

    else if (command_receive_frame.cmd == DATALOG_GET_AVAILABLE_DATA_CMD) {
        command_send_frame.cmd = DATALOG_ECHO_GET_AVAILABLE_DATA_CMD;
        get_all_keys(&datalog_available_symbol_dict, command_param_name_string_array); // get all keys in the dictionary
        name_string_to_uint8_array(command_param_name_string_array,
                                   command_param_data_array,
                                   strlen(command_param_name_string_array));
        set_frame_data(&command_send_frame, command_param_data_array, strlen(command_param_name_string_array));
        Send_Command_Frame_Data(&command_send_frame);
        memset(command_param_name_string_array, 0, sizeof(command_param_name_string_array));

        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    } else if (command_receive_frame.cmd == DATALOG_SET_LOG_DATA_CMD) {
        // set log data
        static char datalog_name_string_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
        memset(datalog_target_symbol_name, 0, sizeof(datalog_target_symbol_name));
        memset(datalog_name_string_array, 0, sizeof(datalog_name_string_array));
        uint8_array_to_name_string(command_receive_frame.data,
                                   datalog_name_string_array,
                                   command_receive_frame.len - PROTOCOL_FRAME_HEADER_SIZE - PROTOCOL_FRAME_CHECKSUM_SIZE);
        seperate_string(datalog_name_string_array, datalog_target_symbol_name, &datalog_target_symbol_size);

        init_dictionary(&datalog_target_symbol_dict);
        for (uint8_t i = 0; i < datalog_target_symbol_size; i++) {
            for (int dict_id = 0; dict_id < datalog_available_symbol_dict.size; dict_id++) {
                if (strcmp(datalog_available_symbol_dict.pairs[dict_id].key,
                           datalog_target_symbol_name[i]) == 0) {
                    add_key_value_pair(&datalog_target_symbol_dict, datalog_target_symbol_name[i],
                                       datalog_available_symbol_dict.pairs[dict_id].value,
                                       datalog_available_symbol_dict.pairs[dict_id].value_type);
                }
            }
        }
        join_string(datalog_target_symbol_name, command_param_name_string_array, datalog_target_symbol_size);

        command_send_frame.cmd = DATALOG_ECHO_SET_LOG_DATA_CMD;
        name_string_to_uint8_array(command_param_name_string_array,
                                   command_param_data_array,
                                   strlen(command_param_name_string_array));
        set_frame_data(&command_send_frame, command_param_data_array, strlen(command_param_name_string_array));
        Send_Command_Frame_Data(&command_send_frame);
        memset(command_param_name_string_array, 0, sizeof(command_param_name_string_array));

        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    } else if (command_receive_frame.cmd == DATALOG_START_LOG_CMD) {
        // start send log data
        task_scheduler_enable_task(datalog_task_handle); // enable datalog task(id = 1)
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    } else if (command_receive_frame.cmd == DATALOG_STOP_LOG_CMD) {
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        task_scheduler_disable_task(datalog_task_handle); // disable datalog task(id = 1)
    }
}

static void Datalog_Frames_Handler(void)
{
    datalog_send_frame.cmd = DATALOG_RUNNING_CMD;
    for (uint8_t i = 0; i < datalog_target_symbol_size; i++) {
        datalog_param_float_array[i] = (get_dictionary_value(&datalog_target_symbol_dict, datalog_target_symbol_name[i]));
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