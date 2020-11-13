__attribute__((fastcall))
uint8_t inb(unsigned int port);
__attribute__((fastcall))
uint16_t inw(unsigned int port);
__attribute__((fastcall))
uint32_t inl(unsigned int port);

__attribute__((fastcall))
void outb(unsigned int port, uint8_t data);
__attribute__((fastcall))
void outw(unsigned int port, uint16_t data);
__attribute__((fastcall))
void outl(unsigned int port, uint32_t data);
