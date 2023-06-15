#include <sys/io.h>
#define WHITE_TXT 0x07

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);
void disable_cursor();
void k_keyboard();

void k_main()
{
	disable_cursor();
	k_clear_screen();
	k_printf("Hello, world! Welcome to my kernel.", 0);
	k_keyboard();
	k_clear_screen();
};

void k_clear_screen()
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;
	while (i < (80 * 25 * 2))
	{
		vidmem[i] = ' ';
		i++;
		vidmem[i] = WHITE_TXT;
		i++;
	};
};

unsigned int k_printf(char *message, unsigned int line)
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;

	i = (line * 80 * 2);

	while (*message != 0)
	{
		if (*message == '\n')
		{
			line++;
			i = (line * 80 * 2);
			*message++;
		}
		else
		{
			vidmem[i] = *message;
			*message++;
			i++;
			vidmem[i] = WHITE_TXT;
			i++;
		};
	};

	return (1);
}

void k_keyboard()
{
	char *c = 0;
	do
	{

		if (inb(0x60) != c) // PORT FROM WHICH WE READ
		{
			c = inb(0x60);
			if (c > 0)
			{

				k_printf(c, 2); // print on screen
			}
		}

	} while (c != 1); // 1= ESCAPE
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}
/*
Draft keyboard handler:
switch (scancode) {
    case 0x00:
        k_printf("ERROR");
        break;
    case 0x01:
        k_printf("ESC");
        break;
    case 0x02:
        k_printf("1");
        break;
    case 0x03:
        k_printf("2");
        break;
    case 0x04:
        k_printf("3");
        break;
    case 0x05:
        k_printf("4");
        break;
    case 0x06:
        k_printf("5");
        break;
    case 0x07:
        k_printf("6");
        break;
    case 0x08:
        k_printf("7");
        break;
    case 0x09:
        k_printf("8");
        break;
    case 0x0A:
        k_printf("9");
        break;
    case 0x0B:
        k_printf("0");
        break;
    case 0x10:
        k_printf("q");
        break;
    case 0x11:
        k_printf("w");
        break;
    case 0x12:
        k_printf("e");
        break;
    case 0x13:
        k_printf("r");
        break;
    case 0x14:
        k_printf("t");
        break;
    case 0x15:
        k_printf("y");
        break;
    case 0x16:
        k_printf("u");
        break;
    case 0x17:
        k_printf("i");
        break;
    case 0x18:
        k_printf("o");
        break;
    case 0x19:
        k_printf("p");
        break;
    case 0x1A:
        k_printf("¨");
        break;
    case 0x1B:
        k_printf("'");
        break;
    case 0x1C:
        k_printf("ENTER");
        break;
    case 0x1E:
        k_printf("a");
        break;
    case 0x1F:
        k_printf("s");
        break;
    case 0x20:
        k_printf("d");
        break;
    case 0x21:
        k_printf("f");
        break;
    case 0x22:
        k_printf("g");
        break;
    case 0x23:
        k_printf("h");
        break;
    case 0x24:
        k_printf("j");
        break;
    case 0x25:
        k_printf("k");
        break;
    case 0x26:
        k_printf("l");
        break;
    case 0x27:
        k_printf("ç");
        break;
    case 0x28:
        k_printf("`");
        break;
    case 0x2C:
        k_printf("z");
        break;
    case 0x2D:
        k_printf("x");
        break;
    case 0x2E:
        k_printf("c");
        break;
    case 0x2F:
        k_printf("v");
        break;
    case 0x30:
        k_printf("b");
        break;
    case 0x31:
        k_printf("n");
        break;
    case 0x32:
        k_printf("m");
        break;
    case 0x33:
        k_printf(",");
        break;
    case 0x34:
        k_printf(".");
        break;
    case 0x35:
        k_printf("-");
        break;
    case 0x1D:
        k_printf("CTRL");
        break;
    case 0x2A:
        k_printf("SHIFT");
        break;
    case 0x39:
        k_printf(" ");
        break;
    default:
        if (scancode <= 0x7f) {
            k_printf("Unknown key down");
        } else if (scancode <= 0x39 + 0x80) {
            k_printf("key up ");
            print_letter(scancode - 0x80);
        } else {
            k_printf("Unknown key up");
        }
        break;
}

*/
