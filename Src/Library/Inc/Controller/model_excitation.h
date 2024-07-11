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
 * @return uint8_t: 1: execution finished, 0: not finished
 */
uint8_t step_model_excitation(void);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _cplusplus
}
#endif
#endif // !__MODEL_EXCITATION_H__