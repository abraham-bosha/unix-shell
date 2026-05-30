#ifndef EXEC_H
#define EXEC_H

#include "pipeline.h"

int execute_pipeline(pipeline_t *pipeline);

void exec_command_or_die(command_t *cmd);

void report_status(int status);

int decode_exit_status(int status);

#endif
