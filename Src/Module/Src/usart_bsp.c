#include "usart_bsp.h"

/* ================== COMMAND ====================*/

// send and receive frame data(public handler)
protocol_frame_parser_t command_parser;

protocol_frame_t command_send_frame    = {0};
protocol_frame_t command_receive_frame = {0};

char command_param_name_string_array[PROTOCOL_FRAME_MAX_SIZE] = {0};
uint8_t command_param_data_array[PROTOCOL_FRAME_MAX_SIZE]     = {0};

// private send/receive data buffer(single frame byte data)
static uint8_t command_receive_frame_data[PROTOCOL_FRAME_MAX_SIZE] = {0};
static uint8_t command_send_frame_data[PROTOCOL_FRAME_MAX_SIZE]    = {0};

/* ================== DATALOG ====================*/
protocol_frame_t datalog_send_frame                       = {0};
float datalog_param_float_array[PROTOCOL_FRAME_MAX_SIZE]  = {0};
uint8_t datalog_param_data_array[PROTOCOL_FRAME_MAX_SIZE] = {0};

static uint8_t datalog_send_frame_data[PROTOCOL_FRAME_MAX_SIZE] = {0};

void Init_Command_Protocol_Parser(void)
{
    protocol_parser_init(&command_parser);
}

void DeInit_Command_Protocol_Parser(void)
{
    protocol_parser_deinit(&command_parser);
}

void Send_Command_Frame_Data(protocol_frame_t *frame)
{
    serialize_frame_data(command_send_frame_data, frame);
    HAL_UART_Transmit_DMA(&UART_COMMAND, command_send_frame_data, frame->len);
}

void Start_Command_Frame_Receive(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(&UART_COMMAND, command_receive_frame_data, PROTOCOL_FRAME_MAX_SIZE);
    __HAL_DMA_DISABLE_IT(UART_COMMAND.hdmarx, DMA_IT_HT);
}

void Parse_Command_Frame(void)
{
    protocol_data_handler(&command_parser);
    deep_copy_frame(&command_receive_frame, command_parser.frame);
}

void Send_Datalog_Frame_Data(protocol_frame_t *frame)
{
    serialize_frame_data(datalog_send_frame_data, frame);
    HAL_UART_Transmit_DMA(&UART_DATALOG, datalog_send_frame_data, frame->len);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == &UART_COMMAND) {
        // write data into receive frame data buffer
        protocol_data_receive(&command_parser, command_receive_frame_data, Size);
#ifdef DEBUG
        HAL_UART_Transmit_DMA(&UART_COMMAND, command_receive_frame_data, Size);
#endif // DEBUG
        HAL_UARTEx_ReceiveToIdle_DMA(huart, command_receive_frame_data, PROTOCOL_FRAME_MAX_SIZE);
        // stop dma half transfer interrupt
        __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
        // HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    }
}

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit_DMA(&UART_COMMAND, (uint8_t *)&ch, 1);
    while (__HAL_UART_GET_FLAG(&UART_COMMAND, UART_FLAG_TC) == RESET);
    return ch;
}

int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++) {
        __io_putchar(*ptr++);
    }
    return len;
}