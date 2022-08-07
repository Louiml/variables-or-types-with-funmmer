#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
typedef unsigned char uint8_t;
typedef short int16_t;
#define ARRAY(T) struct {\
    int16_t size;\
    int16_t capacity;\
    T *data;\
} *
#define ARRAY_CREATE(array, init_capacity, init_size) {\
    array = malloc(sizeof(*array)); \
    array->data = malloc((init_capacity) * sizeof(*array->data)); \
    assert(array->data != NULL); \
    array->capacity = init_capacity; \
    array->size = init_size; \
}
#define ARRAY_PUSH(array, item) {\
    if (array->size == array->capacity) {  \
        array->capacity *= 2;  \
        array->data = realloc(array->data, array->capacity * sizeof(*array->data)); \
        assert(array->data != NULL); \
    }  \
    array->data[array->size++] = item; \
}
#define STR_INT16_T_BUFLEN ((CHAR_BIT * sizeof(int16_t) - 1) / 3 + 2)
enum var_type {VAR_NULL, VAR_UNDEFINED, VAR_NAN, VAR_BOOL, VAR_INT16, VAR_STRING, VAR_ARRAY, VAR_DICT};
struct var {
    enum var_type type;
    int16_t number;
    void *data;
};
struct array_var_t {
    int16_t size;
    int16_t capacity;
    struct var *data;
};
struct var var_from_str(const char *s) {
    struct var v;
    v.type = VAR_STRING;
    v.data = (void *)s;
    return v;
}
struct var str_to_int16_t(const char * str) {
    struct var v;
    const char *p = str;
    int r;

    v.data = NULL;

    while (*p && isspace(*p))
        p++;

    if (*p == 0)
        str = "0";

    if (*p == '-' && *(p+1))
        p++;

    while (*p) {
        if (!isdigit(*p)) {
            v.type = VAR_NAN;
            return v;
        }
        p++;
    }

    sscanf(str, "%d", &r);
    v.type = VAR_INT16;
    v.number = (int16_t)r;
    return v;
}
const char * var_to_str(struct var v, uint8_t *need_dispose)
{
    char *buf;
    int16_t i;
    *need_dispose = 0;

    if (v.type == VAR_INT16) {
        buf = malloc(STR_INT16_T_BUFLEN);
        assert(buf != NULL);
        *need_dispose = 1;
        sprintf(buf, "%d", v.number);
        return buf;
    } else if (v.type == VAR_BOOL)
        return v.number ? "true" : "false";
    else if (v.type == VAR_STRING)
        return (const char *)v.data;
    else if (v.type == VAR_ARRAY) {
        struct array_var_t * arr = (struct array_var_t *)v.data;
        uint8_t dispose_elem = 0;
        buf = malloc(1);
        assert(buf != NULL);
        *need_dispose = 1;
        buf[0] = 0;
        for (i = 0; i < arr->size; i++) {
            const char * elem = var_to_str(arr->data[i], &dispose_elem);
            buf = realloc(buf, strlen(buf) + strlen(elem) + 1 + (i != 0 ? 1 : 0));
            assert(buf != NULL);
            if (i != 0)
                strcat(buf, ",");
            strcat(buf, elem);
            if (dispose_elem)
                free((void *)elem);
        }
        return buf;
    }
    else if (v.type == VAR_DICT)
        return "[object Object]";
    else if (v.type == VAR_NAN)
        return "NaN";
    else if (v.type == VAR_NULL)
        return "null";
    else if (v.type == VAR_UNDEFINED)
        return "undefined";

    return NULL;
}

struct var var_to_number(struct var v)
{
    struct var result;
    result.type = VAR_INT16;
    result.number = 0;

    if (v.type == VAR_INT16)
        result.number = v.number;
    else if (v.type == VAR_BOOL)
        result.number = v.number;
    else if (v.type == VAR_STRING)
        return str_to_int16_t((const char *)v.data);
    else if (v.type == VAR_ARRAY) {
        struct array_var_t * arr = (struct array_var_t *)v.data;
        if (arr->size == 0)
            result.number = 0;
        else if (arr->size > 1)
            result.type = VAR_NAN;
        else
            result = var_to_number(arr->data[0]);
    } else if (v.type != VAR_NULL)
        result.type = VAR_NAN;

    return result;
}
struct var var_inc(struct var * v, int16_t by) {
    struct var result;

    result = var_to_number(*v);
    if (result.type == VAR_INT16) {
        (*v).type = VAR_INT16;
        (*v).number = result.number + by;
        (*v).data = NULL;
    } else
        (*v).type = VAR_NAN;
    return result;
}
static ARRAY(void *) gc_main;

struct var var_plus(struct var left, struct var right)
{
    struct var result, left_to_number, right_to_number;
    const char *left_as_string, *right_as_string;
    uint8_t need_dispose_left, need_dispose_right;
    result.data = NULL;

    if (left.type == VAR_STRING || right.type == VAR_STRING 
        || left.type == VAR_ARRAY || right.type == VAR_ARRAY
        || left.type == VAR_DICT || right.type == VAR_DICT)
    {
        left_as_string = var_to_str(left, &need_dispose_left);
        right_as_string = var_to_str(right, &need_dispose_right);
        
        result.type = VAR_STRING;
        result.data = malloc(strlen(left_as_string) + strlen(right_as_string) + 1);
        assert(result.data != NULL);
        ARRAY_PUSH(gc_main, result.data);

        strcpy(result.data, left_as_string);
        strcat(result.data, right_as_string);

        if (need_dispose_left)
            free((void *)left_as_string);
        if (need_dispose_right)
            free((void *)right_as_string);
        return result;
    }

    left_to_number = var_to_number(left);
    right_to_number = var_to_number(right);

    if (left_to_number.type == VAR_NAN || right_to_number.type == VAR_NAN) {
        result.type = VAR_NAN;
        return result;
    }

    result.type = VAR_INT16;
    result.number = left_to_number.number + right_to_number.number;
    return result;
}
int16_t gc_i;

static const char * b;
static struct j_var a;
static const char * aa;
static const char * aaa;
static struct var tmp_result;
static const char * tmp_str;
static uint8_t tmp_need_dispose;
int main(void) {
    ARRAY_CREATE(gc_main, 2, 0);

    b = "b";
    a = var_from_str("a");
    aa = "a";
    aaa = "a";
    tmp_result = var_plus(var_from_str(b), var_inc(&a, 1));
    printf("%s", tmp_str = var_to_str(tmp_result, &tmp_need_dispose));
    if (tmp_need_dispose)
        free((void *)tmp_str);
    printf(" %s", aa);
    printf("%s\n", aaa);
    for (gc_i = 0; gc_i < gc_main->size; gc_i++)
        free(gc_main->data[gc_i]);
    free(gc_main->data);
    free(gc_main);

    return 0;
}
