#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags, int argc, const char **argv )
{
    struct pam_conv *pam_convp;
    struct pam_message *pam_msgp;
    struct pam_response *pam_resp = NULL;

    int retval = pam_get_item(pamh, PAM_CONV, (const void **)&pam_convp);
    if (retval != PAM_SUCCESS)
        return retval;

    pam_msgp = (struct pam_message *)calloc(1, sizeof(struct pam_message));
    pam_msgp->msg_style = PAM_PROMPT_ECHO_OFF;
    pam_msgp->msg = "Input your 2FA code: ";
    (pam_convp->conv)(1, (const struct pam_message **)&pam_msgp, &pam_resp, pam_convp->appdata_ptr);

    if (pam_resp == NULL || pam_resp->resp == NULL)
        return PAM_AUTH_ERR;

    if (pam_set_item(pamh, PAM_AUTHTOK, pam_resp->resp) != PAM_SUCCESS)
        return PAM_AUTH_ERR;

    free(pam_msgp);
    free(pam_resp);
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
