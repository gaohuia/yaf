
#include "php.h"
#include "functions.h"

zend_string *standard_path(zend_string *str)
{
    zend_string *ret;
    char *buf = malloc(ZSTR_LEN(str) + 1);
    char *p = ZSTR_VAL(str);
    int i = 0;

    for (i=0; i< ZSTR_LEN(str); i++) {
        if (p[i] == '\\') {
            buf[i] = '/';
        } else {
            buf[i] = p[i];
        }
    }

    ret = zend_string_init(buf, ZSTR_LEN(str), 0);
    zend_string_release(str);

    free(buf);
    return ret;
}

