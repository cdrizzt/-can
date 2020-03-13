#include "HardwareSerial.h"
#include "Communication.h"
#include "stm32f4xx.h"
ring_buffer rx_buffer = { { 0 }, 0, 0};
ring_buffer tx_buffer = { { 0 }, 0, 0};

ring_buffer rx_buffer2 = { { 0 }, 0, 0};
ring_buffer tx_buffer2 = { { 0 }, 0, 0};

ring_buffer rx_buffer3 = { { 0 }, 0, 0};
ring_buffer tx_buffer3 = { { 0 }, 0, 0};

ring_buffer rx_buffer4 = { { 0 }, 0, 0};
ring_buffer tx_buffer4 = { { 0 }, 0, 0};

ring_buffer rx_buffer5 = { { 0 }, 0, 0};
ring_buffer tx_buffer5 = { { 0 }, 0, 0};

ring_buffer rx_buffer6 = { { 0 }, 0, 0};
ring_buffer tx_buffer6 = { { 0 }, 0, 0};

void store_char(unsigned char c, ring_buffer *buffer)
{
    unsigned int i = (unsigned int)(buffer->head + 1) % SERIAL_BUFFER_SIZE;

    // if we should be storing the received character into the location
    // just before the tail (meaning that the head would advance to the
    // current location of the tail), we're about to overflow the buffer
    // and so we don't write the character or advance the head.
    if (i != buffer->tail) {
        buffer->buffer[buffer->head] = c;
        buffer->head = i;
    }
}
unsigned int Serial_available(void)
{
    return (SERIAL_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % SERIAL_BUFFER_SIZE;
}
unsigned int Serial2_available(void)
{
    return (SERIAL_BUFFER_SIZE + rx_buffer2.head - rx_buffer2.tail) % SERIAL_BUFFER_SIZE;
}
unsigned int Serial3_available(void)
{
    return (SERIAL_BUFFER_SIZE + rx_buffer3.head - rx_buffer3.tail) % SERIAL_BUFFER_SIZE;
}
unsigned int Serial4_available(void)
{
	return (RX4_SIZE + RX4_SIZE - DMA_GetCurrDataCounter(DMA1_Stream2) - rx4_tail) % RX4_SIZE;
}
unsigned int Serial5_available(void)
{
    return (SERIAL_BUFFER_SIZE + rx_buffer5.head - rx_buffer5.tail) % SERIAL_BUFFER_SIZE;
}
unsigned int Serial6_available(void)
{
    return (SERIAL_BUFFER_SIZE + rx_buffer6.head - rx_buffer6.tail) % SERIAL_BUFFER_SIZE;
}


int Serial_read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (rx_buffer.head == rx_buffer.tail)
    {
        return -1;
    }
    else
    {
        unsigned char c = rx_buffer.buffer[rx_buffer.tail];
        rx_buffer.tail = (unsigned int)(rx_buffer.tail + 1) % SERIAL_BUFFER_SIZE;
        return c;
    }
}
int Serial2_read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (rx_buffer2.head == rx_buffer2.tail) {
        return -1;
    } else {
        unsigned char c = rx_buffer2.buffer[rx_buffer2.tail];
        rx_buffer2.tail = (unsigned int)(rx_buffer2.tail + 1) % SERIAL_BUFFER_SIZE;
        return c;
    }
}
int Serial3_read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (rx_buffer3.head == rx_buffer3.tail) {
        return -1;
    } else {
        unsigned char c = rx_buffer3.buffer[rx_buffer3.tail];
        rx_buffer3.tail = (unsigned int)(rx_buffer3.tail + 1) % SERIAL_BUFFER_SIZE;
        return c;
    }
}
int Serial4_read(void)
{
	unsigned char c = rx4_buf[rx4_tail];
	rx4_tail = (unsigned int)(rx4_tail + 1) % RX4_SIZE;
	return c;
}

int Serial5_read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (rx_buffer5.head == rx_buffer5.tail) {
        return -1;
    } else {
        unsigned char c = rx_buffer5.buffer[rx_buffer5.tail];
        rx_buffer5.tail = (unsigned int)(rx_buffer5.tail + 1) % SERIAL_BUFFER_SIZE;
        return c;
    }
}
int Serial6_read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (rx_buffer6.head == rx_buffer6.tail)
    {
        return -1;
    }
    else
    {
        unsigned char c = rx_buffer6.buffer[rx_buffer6.tail];
        rx_buffer6.tail = (unsigned int)(rx_buffer6.tail + 1) % SERIAL_BUFFER_SIZE;
        return c;
    }
}
unsigned char Serial_write(unsigned char c)
{
    int i = (tx_buffer.head + 1) % SERIAL_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer.tail);

    tx_buffer.buffer[tx_buffer.head] = c;
    tx_buffer.head = i;

    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

    return 1;
}
unsigned char Serial2_write(unsigned char c)
{
    int i = (tx_buffer2.head + 1) % SERIAL_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer2.tail);

    tx_buffer2.buffer[tx_buffer2.head] = c;
    tx_buffer2.head = i;

    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

    return 1;
}
unsigned char Serial3_write(unsigned char c)
{
    int i = (tx_buffer3.head + 1) % SERIAL_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer3.tail);

    tx_buffer3.buffer[tx_buffer3.head] = c;
    tx_buffer3.head = i;

    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

    return 1;
}
unsigned char Serial4_write(unsigned char c)
{
    int i = (tx_buffer4.head + 1) % SERIAL_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer4.tail);

    tx_buffer4.buffer[tx_buffer4.head] = c;
    tx_buffer4.head = i;

    USART_ITConfig(UART4, USART_IT_TXE, ENABLE);

    return 1;
}
unsigned char Serial5_write(unsigned char c)
{
    int i = (tx_buffer5.head + 1) % SERIAL_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer5.tail);

    tx_buffer5.buffer[tx_buffer5.head] = c;
    tx_buffer5.head = i;

    USART_ITConfig(UART5, USART_IT_TXE, ENABLE);

    return 1;
}
unsigned char Serial6_write(unsigned char c)
{
    int i = (tx_buffer6.head + 1) % SERIAL_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer6.tail);

    tx_buffer6.buffer[tx_buffer6.head] = c;
    tx_buffer6.head = i;

    USART_ITConfig(USART6, USART_IT_TXE, ENABLE);

    return 1;
}

/************************ (C) COPYRIGHT KIKTechRobotics *****END OF FILE****/
