make: pam_2fa_prompt.o pam_2fa_clear.o

pam_2fa_prompt.o: pam_2fa_prompt.c
	gcc -fPIC -fno-stack-protector -c pam_2fa_prompt.c

pam_2fa_clear.o: pam_2fa_clear.c
	gcc -fPIC -fno-stack-protector -c pam_2fa_clear.c

install: pam_2fa_prompt.o pam_2fa_clear.o
	ld -x --shared -o /lib64/security/pam_2fa_prompt.so pam_2fa_prompt.o
	ld -x --shared -o /lib64/security/pam_2fa_clear.so pam_2fa_clear.o

uninstall:
	rm -f /lib64/security/pam_2fa_prompt.so
	rm -f /lib64/security/pam_2fa_clear.so
	@echo -e "\n\n      Remove any entry related to this module in /etc/pam.d/ files,\n      otherwise you're not going to be able to login.\n\n"
debug:
	gcc -E -fPIC -fno-stack-protector -c pam_2fa_prompt.c
	gcc -E -fPIC -fno-stack-protector -c pam_2fa_clear.c
clean:
	rm -rf *.o
