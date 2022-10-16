#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags, int argc, const char **argv )
{
    if (pam_set_item(pamh, PAM_AUTHTOK, NULL) != PAM_SUCCESS)
        return PAM_AUTH_ERR;

    return PAM_SUCCESS;
}

#ifndef UNUSED_ATTR
# if __GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
#  define UNUSED_ATTR __attribute__((__unused__))
# else
#  define UNUSED_ATTR
# endif
#endif

PAM_EXTERN int pam_sm_setcred (pam_handle_t *pamh UNUSED_ATTR, int flags UNUSED_ATTR, int argc UNUSED_ATTR, const char **argv UNUSED_ATTR)
{
    return PAM_SUCCESS;
}
