A very simple PAM module that ask 2FA code and pass to later modules.

Config example:

# prompt for 2FA code
auth      required  pam_2fa_prompt.so
# code will be stored at AUTHTOK, should be able to reuse the same code
# for most module with use_first_pass param
auth [success=1 default=ignore] pam_first_2fa.so use_first_pass
auth      required  pam_second_2fa.so use_first_pass
# this module clears out AUTHTOK
auth      optional  pam_2fa_clear.so
