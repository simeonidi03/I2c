
#include "ssd1306_i2c.h"

/* Private variables */
static uint32_t ssd1306_I2C_Timeout;

/* Private defines */
#define I2C_TRANSMITTER_MODE   0
#define I2C_RECEIVER_MODE      1
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0

/*Add define from stm32 */
#define  I2C_SR1_SB                          ((uint16_t)0x0001)            /*!< Start Bit (Master mode) */

/*******************  Bit definition for I2C_OAR1 register  *******************/
#define  I2C_OAR1_ADD1_7                     ((uint16_t)0x00FE)            /*!< Interface Address */
#define  I2C_OAR1_ADD8_9                     ((uint16_t)0x0300)            /*!< Interface Address */

#define  I2C_OAR1_ADD0                       ((uint16_t)0x0001)            /*!< Bit 0 */
#define  I2C_OAR1_ADD1                       ((uint16_t)0x0002)            /*!< Bit 1 */
#define  I2C_OAR1_ADD2                       ((uint16_t)0x0004)            /*!< Bit 2 */
#define  I2C_OAR1_ADD3                       ((uint16_t)0x0008)            /*!< Bit 3 */
#define  I2C_OAR1_ADD4                       ((uint16_t)0x0010)            /*!< Bit 4 */
#define  I2C_OAR1_ADD5                       ((uint16_t)0x0020)            /*!< Bit 5 */
#define  I2C_OAR1_ADD6                       ((uint16_t)0x0040)            /*!< Bit 6 */
#define  I2C_OAR1_ADD7                       ((uint16_t)0x0080)            /*!< Bit 7 */
#define  I2C_OAR1_ADD8                       ((uint16_t)0x0100)            /*!< Bit 8 */
#define  I2C_OAR1_ADD9                       ((uint16_t)0x0200)            /*!< Bit 9 */

void ssd1306_I2C_Init() {
	gpio_init_type gpio; //другой аналог
	i2c_type i2c;


	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_I2C1_PERIPH_CLOCK, TRUE);

    i2c_init(I2C1, I2C_FSMODE_DUTY_2_1, 400000);
    // by default home-mode is I2C mode. We use this way.
    i2c_own_address2_set(I2C1, 0x15);
    i2c_ack_enable(I2C1, FALSE);
    i2c_7bit_address_send(I2C1, 0x15, I2C_DIRECTION_TRANSMIT);
    i2c_enable(I2C1, TRUE);

    gpio.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7;
    gpio.gpio_mode = GPIO_MODE_MUX;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init(GPIOB, &gpio);

  }





void ssd1306_I2C_WriteMulti(i2c_type* I2Cx, uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	uint8_t i;
	ssd1306_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	ssd1306_I2C_WriteData(I2Cx, reg);
	for (i = 0; i < count; i++) {
		ssd1306_I2C_WriteData(I2Cx, data[i]);
	}
	ssd1306_I2C_Stop(I2Cx);
}




/* Private functions */
int16_t ssd1306_I2C_Start(i2c_type* i2c_x, uint8_t address, uint8_t direction, uint8_t ack) {
	/* Generate I2C start pulse */
	i2c_x->ctrl1_bit.genstart = 1;

	/* Wait till I2C is busy */
	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while (!(i2c_x->sts1_bit.startf & I2C_SR1_SB)) {
		if (--ssd1306_I2C_Timeout == 0x00) {
			return 1;
		}
	}

	/* Enable ack if we select it */
	if (ack) {
		i2c_x->ctrl1_bit.acken = 1;
	}

	/* Send write/read bit */
	if (direction == I2C_TRANSMITTER_MODE) {
	    /* Send address with zero last bit */
	    i2c_x->dt = (address << 1) & 0xFF;  // Shift address left by 1 and clear upper bits

	    /* Wait till finished */
	    ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	    while (!(i2c_x->sts1_bit.addr7f)) {
	        if (--ssd1306_I2C_Timeout == 0x00) {
	            return 1;
	        }
	    }
	}

	if (direction == I2C_RECEIVER_MODE) {
		/* Send address with 1 last bit */
		i2c_x->dt = address | I2C_OAR1_ADD0;
		/* Wait till finished */
		ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
		while (!I2C_CheckEvent(i2c_x, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
			if (--ssd1306_I2C_Timeout == 0x00) {
				return 1;
			}
		}
	}

	/* Read status register to clear ADDR flag */
	i2c_x->sts2_bit;

	/* Return 0, everything ok */
	return 0;
}

void ssd1306_I2C_WriteData(i2c_type* i2c_x, uint8_t data) {
	/* Wait till I2C is not busy anymore */
	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while (!(i2c_x->sts1_bit.tdbe) && ssd1306_I2C_Timeout) {
		ssd1306_I2C_Timeout--;
	}

	/* Send I2C data */
	i2c_x->dt = data;
}

void ssd1306_I2C_Write(i2c_type* i2c_x, uint8_t address, uint8_t reg, uint8_t data) {
	ssd1306_I2C_Start(i2c_x, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	ssd1306_I2C_WriteData(i2c_x, reg);
	ssd1306_I2C_WriteData(i2c_x, data);
	ssd1306_I2C_Stop(i2c_x);
}


uint8_t ssd1306_I2C_Stop(i2c_type* i2c_x) {
	/* Wait till transmitter not empty */
	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while (((!i2c_x->sts1_bit.tdbe) || (!(i2c_x->sts1_bit.tdc)))) {
		if (--ssd1306_I2C_Timeout == 0x00) {
			return 1;
		}
	}

	/* Generate stop */
	i2c_x->ctrl1_bit.genstop = 1;


	/* Return 0, everything ok */
	return 0;
}

uint8_t ssd1306_I2C_IsDeviceConnected(i2c_type* I2Cx, uint8_t address) {
	uint8_t connected = 0;
	/* Try to start, function will return 0 in case device will send ACK */
	if (!ssd1306_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE)) {
		connected = 1;
	}

	/* STOP I2C */
	ssd1306_I2C_Stop(I2Cx);

	/* Return status */
	return connected;
}
