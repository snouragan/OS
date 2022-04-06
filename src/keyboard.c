#include <keyboard.h>

#include <libc.h>
#include <i686.h>

char K[256] = {
        [KEY_1_PRESSED] = '1',
        [KEY_2_PRESSED] = '2',
        [KEY_3_PRESSED] = '3',
        [KEY_4_PRESSED] = '4',
        [KEY_5_PRESSED] = '5',
        [KEY_6_PRESSED] = '6',
        [KEY_7_PRESSED] = '7',
        [KEY_8_PRESSED] = '8',
        [KEY_9_PRESSED] = '9',
        [KEY_0_PRESSED] = '0',
        [KEY_MINUS_PRESSED] = '-',
        [KEY_EQUALS_PRESSED] = '=',
	[KEY_BACKSPACE_PRESSED] = '\b',
	[KEY_TAB_PRESSED] = '\t',
        [KEY_Q_PRESSED] = 'q',
        [KEY_W_PRESSED] = 'w',
        [KEY_E_PRESSED] = 'e',
        [KEY_R_PRESSED] = 'r',
        [KEY_T_PRESSED] = 't',
        [KEY_Y_PRESSED] = 'y',
        [KEY_U_PRESSED] = 'u',
        [KEY_I_PRESSED] = 'i',
        [KEY_O_PRESSED] = 'o',
        [KEY_P_PRESSED] = 'p',
        [KEY_LBRACKET_PRESSED] = '[',
        [KEY_RBRACKET_PRESSED] = ']',
        [KEY_ENTER_PRESSED] = '\n',
        [KEY_A_PRESSED] = 'a',
        [KEY_S_PRESSED] = 's',
        [KEY_D_PRESSED] = 'd',
        [KEY_F_PRESSED] = 'f',
        [KEY_G_PRESSED] = 'g',
        [KEY_H_PRESSED] = 'h',
        [KEY_J_PRESSED] = 'j',
        [KEY_K_PRESSED] = 'k',
        [KEY_L_PRESSED] = 'l',
        [KEY_SEMICOLON_PRESSED] = ';',
        [KEY_APOSTROPHE_PRESSED] =  '\'',
        [KEY_BACKSLASH_PRESSED] = '\\',
        [KEY_Z_PRESSED] = 'z',
        [KEY_X_PRESSED] = 'x',
        [KEY_C_PRESSED] = 'c',
        [KEY_V_PRESSED] = 'v',
        [KEY_B_PRESSED] = 'b',
        [KEY_N_PRESSED] = 'n',
        [KEY_M_PRESSED] = 'm',
        [KEY_COMMA_PRESSED] = ',',
        [KEY_DOT_PRESSED] = '.',
        [KEY_SLASH_PRESSED] = '/',
        [KEY_SPACE_PRESSED] = ' ',
	[KEY_UPCURSOR_PRESSED] = 17,
	[KEY_LFTCURSOR_PRESSED] = 18,
	[KEY_RGTCURSOR_PRESSED] = 19,
	[KEY_CURSORDOWN_PRESSED] = 20,
	[KEY_LFTSHIFT_PRESSED] = -1,
	[KEY_LFTSHIFT_RELEASED] = -2,
};
void keyboard_init()
{
	/* TODO: verifica ACK */

	outb(0x60, 0xED); // LED
	outb(0x60, 0);
	keyboard_poll();

	outb(0x60, 0xF0); // Code set
	outb(0x60, 2);
	keyboard_poll();

	outb(0x60, 0xF3); // typemetric
	outb(0x60, 0);
	keyboard_poll();
	
	outb(0x60, 0xF4);
	outb(0x60, 0);
	keyboard_poll();
}

uint8_t keyboard_poke()
{
	return inb(0x60);
}

uint8_t keyboard_poll()
{
	if ((inb(0x64) & 1) == 1)
		return inb(0x60);
	return 255;
}


// Un jeg, dar merge
static bool shift;
uint8_t keyboard_key()
{
	uint8_t ret;
#ifdef QEMU_NU_ESTE_EMULATORUL_MEU_PREFERAT
	static uint8_t last;
	
BEGIN:
#endif

	while ((ret = keyboard_poll()) != 255)
		;

#ifdef QEMU_NU_ESTE_EMULATORUL_MEU_PREFERAT
	if ((ret = inb(0x60)) == last || ret == KEY_LFTSHIFT_PRESSED || ret == KEY_LFTSHIFT_RELEASED) 
	{
	
		if(ret == KEY_LFTSHIFT_PRESSED) shift = 1;
		else if (ret == KEY_LFTSHIFT_RELEASED) shift = 0;
		
		goto BEGIN;
	}
	
		
	return last = ret;
#else
	return ret;
#endif
}
char keyboard_showKey()
{
	char key;
	if(shift == 1 && (key = K[keyboard_key()]) == 'a') 
		 return key - 32; 
		
	
	return K[keyboard_key()];
} 
