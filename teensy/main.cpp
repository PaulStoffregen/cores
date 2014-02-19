#include <WProgram.h>

//int main(void) __attribute__((noreturn));
int main(void) __attribute__((weak));
int main(void)
{
	_init_Teensyduino_internal_();

	setup();

	while (1) {
		loop();
	}
}

