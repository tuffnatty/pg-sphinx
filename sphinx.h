#ifndef SPHINX_H_INCLUDED
#define SPHINX_H_INCLUDED

#include "pstring.h"
#include "dict.h"

typedef int SPH_BOOL;
#define SPH_TRUE (1)
#define SPH_FALSE (0)

typedef struct {
  char            id_field[64];
  char            host[128];
  unsigned short  port;
  char            username[64];
  char            password[64];
  char            prefix[64];
} sphinx_config;

void default_config(sphinx_config *config);

typedef struct sphinx_context *sphinx_context;

sphinx_context sphinx_select(sphinx_config *config,
                             const PString *index,
                             const PString *match,
                             const PString *condition,
                             const PString *order,
                             int offset,
                             int limit,
                             const PString *options,
                             char **error);
SPH_BOOL sphinx_context_next(sphinx_context ctx,
                             /*OUT*/ int64_t *id,
                             /*OUT*/ int *weight);
void sphinx_context_free(sphinx_context ctx);

void sphinx_replace(sphinx_config *config,
                    const PString *index,
                    int64_t id,
                    const Dict *data,
                    char **error);

void sphinx_delete(sphinx_config *config,
                   const PString *index,
                   int64_t id,
                   char **error);

typedef void (*return_data_callback)(void *data, size_t size, void *user_data);

void sphinx_snippet(sphinx_config *config,
                    const PString *index,
                    const PString *match,
                    const PString *data,
                    const Dict *options,
                    return_data_callback callback,
                    void *user_data,
                    char **error);

#endif

