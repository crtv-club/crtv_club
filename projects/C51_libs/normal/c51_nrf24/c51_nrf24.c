// c51_nrf24.c

#include "c51_nrf24.h"

/*
 * * * * * * * * * * * * * * * * * * * * * *
 *	Lasciate ogni speranza, voi ch'entrate *
 * * * * * * * * * * * * * * * * * * * * * * 
 */


//=============== NRF24L01+ BLOCK START =================
// get the value of a nRF24L01 register
unsigned char nrf24_read_reg(unsigned char reg_addr)
{
    unsigned char read_data = 0;

  	spi0_start();
	spi0_send((reg_addr & RF24_CMD_RW_MASK) | RF24_CMD_R_REGISTER);
	read_data = spi0_send(0);
	spi0_end();
	
	return read_data;
}

// set the value of a nRF24L01 register
void nrf24_write_reg(unsigned char reg_addr, unsigned char reg_value)
{
  	spi0_start();
	spi0_send((reg_addr & RF24_CMD_RW_MASK) | RF24_CMD_W_REGISTER);
	spi0_send(reg_value);
	spi0_end();
}

// Write one byte to nRF24L01 TX FIFO
// \param[in] value Data byte to write
void nrf24_fifo_write_byte(unsigned char value )
{
	spi0_start();
	spi0_send( RF24_CMD_W_TX_PAYLOAD_NO_ACK );
	spi0_send(value);
	spi0_end();
}

// Write several bytes [1..32] to nRF24L01 TX FIFO
// \param[in] values Pointer to array of data to send 
// \param[in] bytes_count Number of bytes to write
void nrf24_fifo_write_data(unsigned char *values, unsigned char bytes_count)
{
	unsigned char i;
	spi0_start();
	spi0_send( RF24_CMD_W_TX_PAYLOAD_NO_ACK );
	for (i=0; i<bytes_count; i++)
	{
		spi0_send(values[i]);
	}
	spi0_end();
}

//DEBUG:
void nrf24_fifo_write_data_test(unsigned char values)
{
	unsigned char i;
	spi0_start();
	spi0_send( RF24_CMD_W_TX_PAYLOAD_NO_ACK );
	for (i=0; i<32; i++)
	{
		spi0_send(values);
	}
	spi0_end();
}

// Read one byte from nRF24L01 RX FIFO
// \return Read byte value
unsigned char nrf24_fifo_read_byte( void )
{
	unsigned char read_byte;
	spi0_start();
	spi0_send( RF24_CMD_R_RX_PAYLOAD );
	read_byte = spi0_send(0);
	spi0_end();
	return read_byte;
}

// Write several bytes [1..32] to nRF24L01 TX FIFO
// \param[in] values Pointer to array of data to send 
// \param[in] bytes_count Number of bytes to write
// \return Count of read bytes
unsigned char nrf24_fifo_read_data(unsigned char *values)
{
	unsigned char bytes_count = 32; // temporary work-around because we do not know actual received bytes count
	unsigned char i=0;
	spi0_start();
	spi0_send( RF24_CMD_R_RX_PAYLOAD );
	for (i=0; i<bytes_count; i++) 
	{
		values[i] = spi0_send(0);
	}
	spi0_end();
	return bytes_count;
}

// power up the nRF24L01 chip
void nrf24_power_up(void)
{
  unsigned char reg_config_value = nrf24_read_reg(REG_NRF24_CONFIG);
  nrf24_write_reg(REG_NRF24_CONFIG, reg_config_value | BIT_NRF24_CONFIG_PWR_UP); 
  delay_us(130); // recommended delay 130us for normal PLL settling
}

// switch nRF24L01 off
void nrf24_power_down(void)
{
  unsigned char reg_config_value = nrf24_read_reg(REG_NRF24_CONFIG);
  nrf24_write_reg(REG_NRF24_CONFIG, reg_config_value & ~BIT_NRF24_CONFIG_PWR_UP); 
}

// enable RX and TX
void nrf24_rf_enable(void)
{
	RF24_CE = 1;
}

// disable RX and TX
void nrf24_rf_disable(void)
{
	RF24_CE = 0;
}

// switch nRF24L01 to TX mode until it finishes transmitting a packet (send ONE packet); send data represented in TX FIFO 
void nrf24_tx_send(void)
{
  nrf24_rf_enable();
  delay_us(10); // recommended delay
  nrf24_rf_disable();
}

// setup RX Mode of nRF24L01 and start receive data
void nrf24_set_rx_mode(void)
{
  unsigned char reg_config_value = nrf24_read_reg(REG_NRF24_CONFIG);
  nrf24_write_reg(REG_NRF24_CONFIG, reg_config_value | BIT_NRF24_CONFIG_PRIM_RX);
  nrf24_rf_enable(); // start receive data immediately
  delay_us(130); // recommended delay 130us for normal PLL settling 
}

// setup TX Mode of nRF24L01
void nrf24_set_tx_mode(void)
{
  unsigned char reg_config_value;
  nrf24_rf_disable(); // disable RX
  reg_config_value = nrf24_read_reg(REG_NRF24_CONFIG);
  nrf24_write_reg(REG_NRF24_CONFIG, reg_config_value & ~BIT_NRF24_CONFIG_PRIM_RX);
}

// setup nRF24L01 channel - 0..125
// Fout = 2400 + RF_CH [MHz]
void nrf24_set_channel(unsigned char rf_channel)
{
  nrf24_write_reg(REG_NRF24_RF_CH, rf_channel & BIT_NRF24_RF_CH_MASK);
}

// setup nRF24L01 data rate:
// [RF_DR_LOW, RF_DR_HIGH]:
// '00' – 1Mbps
// '01' – 2Mbps
// '10' – 250kbps
// '11' – Reserved
void nrf24_set_data_rate(unsigned char data_rate)
{
  unsigned char reg_value = nrf24_read_reg(REG_NRF24_RF_SETUP);
  reg_value = (data_rate & 0x01) ? (reg_value | BIT_NRF24_RF_SETUP_RF_DR_HIGH) : (reg_value & ~BIT_NRF24_RF_SETUP_RF_DR_HIGH) ;
  reg_value = (data_rate & 0x02) ? (reg_value | BIT_NRF24_RF_SETUP_RF_DR_LOW) : (reg_value & ~BIT_NRF24_RF_SETUP_RF_DR_LOW) ;
  nrf24_write_reg(REG_NRF24_RF_SETUP, reg_value);
}

// Set nRF24L01 RF output power in TX mode: 
// '00' – -18dBm
// '01' – -12dBm
// '10' – -6dBm
// '11' – 0dBm
void nrf24_set_rf_power(unsigned char rf_power)
{
  unsigned char reg_value = nrf24_read_reg(REG_NRF24_RF_SETUP);
  reg_value &= ~BIT_NRF24_RF_SETUP_RF_PWR;
  reg_value	|= BIT_NRF24_RF_SETUP_RF_PWR & (rf_power << 1); 
  nrf24_write_reg(REG_NRF24_RF_SETUP, reg_value);	 
}

// Returns nRF24L01 Received Power Detector measurements value
// Triggers at received power levels above -64 dBm that are present in the RF channel you receive on. 
// If the received power is less than -64 dBm, RDP = 0.
unsigned char nrf24_get_rpd(void)
{
  return nrf24_read_reg(REG_NRF24_RPD);
}

// TODO: write other functions due to spec
//=============== NRF24L01+ BLOCK END =================


//=============== NRF24L01+ TEST FUNC BLOCK START =================
// scanning all channels in the 2.4GHz band
void nrf24_scan_channels(void)
{
  unsigned char c_rf_ch;

  nrf24_rf_disable();
  	   
  for( c_rf_ch=0 ; c_rf_ch<RF24_CHANNELS_MAX ; c_rf_ch++)
  {
    unsigned char channel_lvl = 0;
	unsigned char count;
    // display current channel
    Display_LSB(c_rf_ch);
    // select a new channel
    nrf24_set_channel(c_rf_ch);
	// measure signal level in current channel
	for (count=0 ; count<255 ; count++)
	{
      // switch on RX
      nrf24_set_rx_mode();
      // wait enough for RX things to settle
      delay_us(60);	// recommended delay 40us for RPD settle
      // this is actually the point where the RPD-flag is set, when CE goes low
      nrf24_rf_disable();
	  delay_us(10);
      // read out RPD flag; set to 1 if received power > -64dBm
      if ( nrf24_get_rpd() ) { ++channel_lvl; }
	  delay_us(10);
	}
	Display_MSB(channel_lvl); // display level
	delay_ms(1000);
  }
}

// scanning wi-fi channels in the 2.4GHz band
// Ch:  Min Freq:  Avarage Freq:   Max Freq:
//  1   2.401      2.412           2.423
//  2   2.406      2.417           2.428
//  3   2.411      2.422           2.433
//  4   2.416      2.427           2.438
//  5   2.421      2.432           2.443
//  6   2.426      2.437           2.448
//  7   2.431      2.442           2.453
//  8   2.436      2.447           2.458
//  9   2.441      2.452           2.463
// 10   2.446      2.457           2.468
// 11   2.451      2.462           2.473
// 12   2.456      2.467           2.478
// 13   2.461      2.472           2.483
void nrf24_show_wifi_lvl(void)
{
  // channels to scan:        2	  3   4	  5	  6	  7	  8	  9
  unsigned char ch_list[8] = {17, 22, 27, 32, 37, 42, 47, 52}; 
  unsigned char c_rf_ch;
  static unsigned char dec_cnt = 0; // decrement counter - make level down for lost channels

  nrf24_rf_disable();
  	   
  for( c_rf_ch=0 ; c_rf_ch<8 ; c_rf_ch++)
  {
    // select a new channel
    nrf24_set_channel(ch_list[c_rf_ch]);
	// measure signal level in current channel
    // switch on RX
    nrf24_set_rx_mode();
    // wait enough for RX things to settle
    delay_us(40);	// recommended delay 40us for RPD settle
    // this is actually the point where the RPD-flag is set, when CE goes low
    nrf24_rf_disable();
    delay_us(4);
    // read out RPD flag; set to 1 if received power > -64dBm
    if ( nrf24_get_rpd() && (digit_values[7-c_rf_ch] < 15)) { ++digit_values[7-c_rf_ch]; }
	if (((dec_cnt % 128) == 0) && (digit_values[7-c_rf_ch] > 0)) {--digit_values[7-c_rf_ch];} // set to dynamic avarage level
    delay_us(4);
  }
  ++dec_cnt;
  delay_ms(50);
}
//=============== NRF24L01+ TEST FUNC BLOCK END =================
