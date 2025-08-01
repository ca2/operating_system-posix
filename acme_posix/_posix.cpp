//
//  _posix.h
//  acme_posix
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-12-22.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to replace environment variable expressions ($ENV_VAR) in a string
// by chat gpt on 2024-12-22.
char *c_expand_environment_variables(const_char_pointer input) {
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1); // Allocate memory for the result string
    if (!result) {
        return NULL; // Memory allocation failed
    }

    size_t i = 0, j = 0;
    while (i < len) {
        if (input[i] == '$' && i + 1 < len && isalpha(input[i + 1])) {
            // Found a '$' followed by a valid environment variable name
            size_t var_start = i + 1;
            size_t var_len = 0;

            // Find the length of the environment variable name
            while (i + 1 + var_len < len && (isalnum(input[i + 1 + var_len]) || input[i + 1 + var_len] == '_')) {
                var_len++;
            }

            // Extract the environment variable name
            char *var_name = strndup(input + var_start, var_len);
            if (!var_name) {
                free(result);
                return NULL; // Memory allocation failed
            }

            // Get the environment variable value
            char *env_value = getenv(var_name);
            free(var_name);

            // If the environment variable exists, append its value to the result string
            if (env_value) {
                while (*env_value) {
                    result[j++] = *env_value++;
                }
            } else {
                // If the environment variable doesn't exist, just append the '$' and variable name
                result[j++] = '$';
                result[j++] = '$';
                for (size_t k = 0; k < var_len; k++) {
                    result[j++] = input[i + 1 + k];
                }
            }

            // Move past the environment variable in the input string
            i += var_len + 1;
        } else {
            // Copy the current character to the result string
            result[j++] = input[i++];
        }
    }

    result[j] = '\0'; // Null-terminate the result string
    return result;
}
