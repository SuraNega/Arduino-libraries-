//
//  FILE: i2c7seg.cpp
//  AUTHOR: Aditya Chaudhary
//  DATE: 25-06-2023
//  VERSION: 0.0.1
//  PURPOSE: Arduino library for Driving 7 segment displays with PCF8575 - 16 channel I2C IO expander.
//  URL: Arduino library for Seven Segment Display with I2C Communication Interface.

#include "i2cdisplaycontroller.h"

/*
	@desc: Constructor
	@param wire: Pointer to the Wire object for I2C communication
*/

I2CDisplayController::I2CDisplayController(TwoWire *wire)
{
	_wire = wire;
	_commonAnode = false; // CC-CA Configurations
	_dataIn = 0xFF;		  // default value to write to the port.
	_switching_value = 0xFF;
	_port0select = true; // by default it is true, basically digits are on P0-P7.

	milli_delay = 3;				// delay
	_error = i2c7seg_I2C_ERROR;		// 0x82
	_pin_error = i2c7seg_PIN_ERROR; // 0x81
	_OK = i2c7seg_OK;
}

/*
 * @brief Performs automatic address detection for the I2C display controller.
 * @return True if a valid address is found, false otherwise.
 */

bool I2CDisplayController::autoAddressDetection(){
	uint8_t address;

	_wire->begin();

	// Iterate through the specified address range (0x20 to 0x
	for(address = 0x20; address <= 0x27; address++){ 
		_wire->beginTransmission(address);

		if(!(_wire->endTransmission())){
			_address = address; // address found
			return true;
		}
	}

	return false; // no address found.
}

/*
	@desc: Initializes the library and checks the connection with the PCF8575
	@return: true if the PCF8575 is connected, false otherwise
*/
bool I2CDisplayController::begin()
{
	_wire->begin();

	if (!autoAddressDetection())
		return false; // If slave doesn't acknowledges.

	return true;	  // if slave acknowledges.
}

/*
	@desc: Sets the I2C address of the PCF8575
	@param deviceAddress: The I2C address to set
	@return: true if the address was set successfully
*/
bool I2CDisplayController::setAddress(const uint8_t deviceAddress)
{
	_address = deviceAddress;
	return true;
}

/*
	@desc: Returns the I2C address of the PCF8575
	@return: The current I2C address
*/
uint8_t I2CDisplayController::getAddress()
{
	return _address;
}

/*
	@desc: Sets the delay in milliseconds
	@param m_delay: The delay value to set
*/
void I2CDisplayController::setDelay(int m_delay)
{
	milli_delay = m_delay;
}

/*
 * @desc: creates a delay.
 */
void I2CDisplayController::getdelay()
{
	delay(milli_delay);
}

/*
  @desc: Sets the port for digits
  @param portselect: true to select port 0, false to select port 1
*/
void I2CDisplayController::setDigitsPort(bool portselect)
{
	_port0select = portselect;
}

/*
  @desc: Sets the CA-CC Configuration
  @param commonAnode: true to select CA configuration, false to select CC Configuration.
*/
void I2CDisplayController::setDisplayConfiguration(bool commonAnode){
	_commonAnode = commonAnode;
}

/*
 * @desc: executes I2C transactions for both ports.
 */
void I2CDisplayController::executeI2C_Commands()
{
	uint8_t port0_value, port1_value;

	_wire->begin();
	_wire->beginTransmission(_address);

	port0_value = _commonAnode ? (_port0select ? ~_dataIn : ~_switching_value) : (_port0select ? _dataIn : _switching_value);

	port1_value = _commonAnode ? (_port0select ? ~_switching_value : ~_dataIn) : (_port0select ? _switching_value : _dataIn);

	_wire->write(port0_value);
	_wire->write(port1_value);

	_wire->endTransmission();
}

/*
  @desc: Prints a character on the display
  @param display_value: The value to display (0-9, A-F)
  @param switching_pin: The pin number of the switching pin (0-7)
  @return: The status code indicating success or failure
*/
uint8_t I2CDisplayController::print(const uint8_t display_value, const uint8_t switching_pin)
{
	if (switching_pin > 7)
		return _pin_error; // returns error when pin>7.

	_dataIn = display_value; // store the display value

	// calculate switching value.
	_switching_value = _switching_value & ~(1 << switching_pin);

	executeI2C_Commands();

	return _OK;
}

/*
  @desc: Turns off the display for a specific switching pin
  @param switching_pin: The pin number of the switching pin (0-7)
  @return: The status code indicating success or failure
*/
uint8_t I2CDisplayController::turnOff(const uint8_t switching_pin)
{
	if (switching_pin > 7)
		return _pin_error;

	_dataIn = 0x00;
	_switching_value = _switching_value | (1 << switching_pin); // set particular pin;

	executeI2C_Commands();

	return _OK;
}

/*
  @desc: Sets or removes the decimal point for a specific switching pin
  @param decimal_pin: The pin number of the decimal point (0-7)
  @param switching_pin: The pin number of the switching pin (0-7)
  @param status: true to set the decimal point, false to remove it
  @return: The status code indicating success or failure
*/
uint8_t I2CDisplayController::setDecimalPoint(const uint8_t decimal_pin, const uint8_t switching_pin, bool status)
{

	if (switching_pin > 7)
		return _pin_error;

	_dataIn = status ? (_dataIn | (1 << decimal_pin)) : (_dataIn & ~(1 << decimal_pin));

	// calculate switching value.
	_switching_value = _switching_value & ~(1 << switching_pin);

	executeI2C_Commands();

	return _OK;
}

/*
  @desc: Clears the display
*/
void I2CDisplayController::clear()
{
	_switching_value = _commonAnode ? 0x00 : 0xFF; // set switching value.
	_dataIn = _commonAnode ? 0xFF : 0x00; // set empty data.

	executeI2C_Commands(); // execute i2c commands.
}