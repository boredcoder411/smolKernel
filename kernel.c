#include <sys/io.h>
#include <string.h>
#define WHITE_TXT 0x07

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);
void disable_cursor();
void k_keyboard();
int k_keyboard_handler(int scancode);

void k_main()
{
	k_clear_screen();
	k_printf("Hello, world! Welcome to my kernel.", 0);
	k_keyboard();
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
	do
	{
		k_keyboard_handler(inb(0x60));
	} while (inb(0x60) != 1);
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

int k_keyboard_handler(int scancode)
{
	switch (scancode)
	{
	case 0x00:
		k_printf("ERROR", 2);
		break;
	case 0x01:
		k_printf("ESC", 2);
		break;
	case 0x02:
		k_printf("1", 2);
		break;
	case 0x03:
		k_printf("2", 2);
		break;
	case 0x04:
		k_printf("3", 2);
		break;
	case 0x05:
		k_printf("4", 2);
		break;
	case 0x06:
		k_printf("5", 2);
		break;
	case 0x07:
		k_printf("6", 2);
		break;
	case 0x08:
		k_printf("7", 2);
		break;
	case 0x09:
		k_printf("8", 2);
		break;
	case 0x0A:
		k_printf("9", 2);
		break;
	case 0x0B:
		k_printf("0", 2);
		break;
	case 0x10:
		k_printf("q", 2);
		break;
	case 0x11:
		k_printf("w", 2);
		break;
	case 0x12:
		k_printf("e", 2);
		break;
	case 0x13:
		k_printf("r", 2);
		break;
	case 0x14:
		k_printf("t", 2);
		break;
	case 0x15:
		k_printf("y", 2);
		break;
	case 0x16:
		k_printf("u", 2);
		break;
	case 0x17:
		k_printf("i", 2);
		break;
	case 0x18:
		k_printf("o", 2);
		break;
	case 0x19:
		k_printf("p", 2);
		break;
	case 0x1A:
		k_printf("¨", 2);
		break;
	case 0x1B:
		k_printf("'", 2);
		break;
	case 0x1C:
		k_printf("ENTER", 2);
		break;
	case 0x1E:
		k_printf("a", 2);
		break;
	case 0x1F:
		k_printf("s", 2);
		break;
	case 0x20:
		k_printf("d", 2);
		break;
	case 0x21:
		k_printf("f", 2);
		break;
	case 0x22:
		k_printf("g", 2);
		break;
	case 0x23:
		k_printf("h", 2);
		break;
	case 0x24:
		k_printf("j", 2);
		break;
	case 0x25:
		k_printf("k", 2);
		break;
	case 0x26:
		k_printf("l", 2);
		break;
	case 0x27:
		k_printf("ç", 2);
		break;
	case 0x28:
		k_printf("`", 2);
		break;
	case 0x2C:
		k_printf("z", 2);
		break;
	case 0x2D:
		k_printf("x", 2);
		break;
	case 0x2E:
		k_printf("c", 2);
		break;
	case 0x2F:
		k_printf("v", 2);
		break;
	case 0x30:
		k_printf("b", 2);
		break;
	case 0x31:
		k_printf("n", 2);
		break;
	case 0x32:
		k_printf("m", 2);
		break;
	case 0x33:
		k_printf(",", 2);
		break;
	case 0x34:
		k_printf(".", 2);
		break;
	case 0x35:
		k_printf("-", 2);
		break;
	case 0x1D:
		k_printf("CTRL", 2);
		break;
	case 0x2A:
		k_printf("SHIFT", 2);
		break;
	case 0x39:
		k_printf(" ", 2);
		break;
	default:
		if (scancode <= 0x39 + 0x80)
		{
		}
		else
		{
			k_printf("Unknown key up", 3);
		}
		break;
	}
}