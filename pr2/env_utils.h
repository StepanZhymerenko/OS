#ifndef ENV_UTILS_H
#define ENV_UTILS_H

void print_help();
void print_env();
void print_var_info(const char *var);
void set_var(const char *assignment);
void assign_var(const char *var, const char *value);
void delete_var(const char *var);
void clear_env();

#endif // ENV_UTILS_H
