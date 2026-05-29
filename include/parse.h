#ifndef PARSE_H
#define PARSE_H

#include "pipeline.h"

pipeline_t *pipeline_create(const char *line);
void pipeline_destroy(pipeline_t *pipeline);

#endif
