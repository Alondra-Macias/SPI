/*
 * SPI.c
 *
 *  Created on: 30/09/2018
 *      Author: AlondraItzel
 */
#include "SPI.h"

static void SPI_enable(spi_channel_t){}
/*It activate the clock gating*/
static void SPI_clk(spi_channel_t){}
/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave){}
/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable){}
/*It selects the clock polarity depending on the value of cpol*/
static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol){}
/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize){}
/*It selects the clock phase depending on the value of cpha*/
static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha){}
/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate){}
/*It selects if MSB or LSM bits is first transmitted*/
static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb){}
/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_start_tranference(spi_channel_t channel){}
/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel){}
/*It transmits the information contained in data*/
void SPI_send_one_byte(uint8_t Data){}
/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const spi_config_t*){}
