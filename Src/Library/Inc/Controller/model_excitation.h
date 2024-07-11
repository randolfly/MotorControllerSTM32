#ifndef __MODEL_EXCITATION_H__
#define __MODEL_EXCITATION_H__

#include <stdlib.h>
#include "Excitation.h"

#include "Util/type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

/**
 * @brief init the model
 */
void init_model_excitation(void);

/**
 * @brief execute 1 step of excitation model
 * @return uint8_t: 1: execution finished, 0: not finished, 2: overrun error
 */
uint8_t step_model_excitation(void);

/**
 * @brief Set the model params, output = (+-1 binary_signal)  * magnitude * gain
 * @param  magnitude: magnitude of the signal, such as 200
 * @param  gain: gain of the signal, such as 1 , 1.1
 */
void set_model_excitation_params(real_T magnitude, real_T gain);

/**
 * @brief Get the model output object
 * @param  output: binary signal output
 */
float get_model_excitation_output();

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _cplusplus
}
#endif
#endif // !__MODEL_EXCITATION_H__