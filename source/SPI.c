/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    SPI.c.
 */


#include "SPI.h"

/*It activate the clock gating*/
static void SPI_clk(spi_channel_t spiName)
{
	switch(spiName)
	{
		case (SPI_0):
			SIM->SCGC6 |= SPI0_CLOCK_GATING;
			break;
		case (SPI_1):
			SIM->SCGC6 |= SPI1_CLOCK_GATING;
			break;
		case (SPI_2):
			SIM->SCGC3 |= SPI2_CLOCK_GATING;
			break;
		default:
			break;
	}
}



/*it enable the clock module of the SPI by modifying the MDIS bits*/
static void SPI_enable(spi_channel_t spiName){
	switch(spiName)
	{
		case (SPI_0):
		SPI0->MCR|=SPI_MCR_MDIS_MASK;
			break;
		case (SPI_1):
		SPI1->MCR|=SPI_MCR_MDIS_MASK;
			break;
		case (SPI_2):
		SPI2->MCR|=SPI_MCR_MDIS_MASK;
			break;
		default:
			break;
	}

}

/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave)
{
	switch(channel)
	{
		case (SPI_0):
				if (masterOrSlave)
				{
					SPI0->MCR |= SPI_MCR_MSTR_MASK;
				}
				else
					SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);
				break;

		case (SPI_1):
				if (masterOrSlave)
				{
					SPI1->MCR |= SPI_MCR_MSTR_MASK;
				}
				else
					SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);
				break;

		case (SPI_2):
				if (masterOrSlave)
				{
					SPI2->MCR |= SPI_MCR_MSTR_MASK;
				}
				else
					SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);
				break;

		default:
			break;
	}
}


/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable){
	switch(channel)
		{
			case (SPI_0):
					if (enableOrDisable)
					{
						SPI0->MCR |= SPI_FIFO_ENABLE;
					}
					else
						SPI0->MCR &= SPI_FIFO_DIS;
					break;

			case (SPI_1):
					if (enableOrDisable)
					{
						SPI1->MCR |= SPI_FIFO_ENABLE;
					}
					else
						SPI1->MCR &= SPI_FIFO_DIS;
					break;

			case (SPI_2):
					if (enableOrDisable)
					{
						SPI2->MCR |= SPI_FIFO_ENABLE;
					}
					else
						SPI2->MCR &= SPI_FIFO_DIS;
					break;

			default:
				break;
		}
}

/*It selects the clock polarity depending on the value of cpol*/
static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
{
	switch (channel)
	{
		case (SPI_0):
				if (cpol)
				{
					SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
				}
				else
					SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
				break;
		case (SPI_1):
				if (cpol)
				{
					SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
				}
				else
					SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
				break;
		case (SPI_2):
				if (cpol)
				{
					SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
				}
				else
					SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK);
				break;
		default:
			break;
	}
}

/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize)
{
	frameSize <<= SPI_CTAR_FMSZ_SHIFT;
	switch (channel)
	{
		case (SPI_0):
			SPI0->CTAR[SPI_CTAR_0] |= frameSize;
			break;
		case (SPI_1):
			SPI1->CTAR[SPI_CTAR_0] |= frameSize;
			break;
		case (SPI_2):
			SPI2->CTAR[SPI_CTAR_0] |= frameSize;
			break;
		default:
			break;
	}
}
/*It selects the clock phase depending on the value of cpha*/
static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
{
	switch (channel)
	{
		case (SPI_0):
			if (cpha)
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
			}
			else
				SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
			break;

		case (SPI_1):
			if (cpha)
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
			}
			else
				SPI1->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
			break;

		case (SPI_2):
			if (cpha)
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK;
			}
			else
				SPI2->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK);
			break;

		default:
			break;
 	}
}
/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate){
baudRate<<=SPI_CTAR_PBR_SHIFT;

		switch (channel)
		{
			case (SPI_0):
				SPI0->CTAR[SPI_CTAR_0]=baudRate;
				break;
			case (SPI_1):
				SPI0->CTAR[SPI_CTAR_0]=baudRate;
				break;
			case (SPI_2):
				SPI0->CTAR[SPI_CTAR_0]=baudRate;
				break;
			default:
				break;
		}
}
/*It selects if MSB or LSM bits is first transmitted*/
static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb){
	switch(channel)
			{
				case (SPI_0):
						if (msb)
						{
							SPI0->MCR = SPI_CTAR_LSBFE_MASK;
						}
						else
							SPI0->MCR = ~SPI_CTAR_LSBFE_MASK;
						break;

				case (SPI_1):
						if (msb)
						{
							SPI1->MCR = SPI_CTAR_LSBFE_MASK;
						}
						else
							SPI1->MCR =~SPI_CTAR_LSBFE_MASK;
						break;

				case (SPI_2):
						if (msb)
						{
							SPI2->MCR = SPI_CTAR_LSBFE_MASK;
						}
						else
							SPI2->MCR = ~SPI_CTAR_LSBFE_MASK;
						break;

				default:
					break;
			}
}
/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_start_tranference(spi_channel_t channel)
{
	switch(channel)
		{
			case (SPI_0):
				SPI0->SR &= ~(SPI_SR_EOQF_MASK);
				SPI0->MCR &= ~(SPI_MCR_FRZ_MASK);
				SPI0->MCR &= ~(SPI_MCR_HALT_MASK);
				break;

			case (SPI_1):
				SPI1->SR &= ~(SPI_SR_EOQF_MASK);
				SPI1->MCR &= ~(SPI_MCR_FRZ_MASK);
				SPI1->MCR &= ~(SPI_MCR_HALT_MASK);
				break;

			case (SPI_2):
				SPI2->SR &= ~(SPI_SR_EOQF_MASK);
				SPI2->MCR &= ~(SPI_MCR_FRZ_MASK);
				SPI2->MCR &= ~(SPI_MCR_HALT_MASK);
				break;

			default:
				break;
		}
}


/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel)
{
	switch(channel)
			{
				case (SPI_0):
					SPI0->SR |= SPI_SR_EOQF_MASK;
					SPI0->MCR |= SPI_MCR_FRZ_MASK;
					SPI0->MCR |= SPI_MCR_HALT_MASK;
					break;
				case (SPI_1):
					SPI1->SR |= SPI_SR_EOQF_MASK;
					SPI1->MCR |= SPI_MCR_FRZ_MASK;
					SPI1->MCR |= SPI_MCR_HALT_MASK;
					break;
				case (SPI_2):
					SPI2->SR |= SPI_SR_EOQF_MASK;
					SPI2->MCR |= SPI_MCR_FRZ_MASK;
					SPI2->MCR |= SPI_MCR_HALT_MASK;
					break;
				default:
					break;
			}
}
/*It transmits the information contained in data*/
void SPI_send_one_byte(uint8_t Data){
	SPI0->PUSHR = Data;
		while(0 == (SPI0->SR & SPI_SR_TCF_MASK));
		SPI0->SR |= SPI_SR_TCF_MASK;
}
/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const spi_config_t*);

